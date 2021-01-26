#include "relay.h"

#include <QDebug>
#include <QSerialPortInfo>
#include <QTimer>

Relay::Relay(QObject* parent)
    : QObject(parent)
{
    m_port = new Port(this);
    m_port->moveToThread(&m_portThread);
    connect(&m_portThread, &QThread::finished, m_port, &QObject::deleteLater);
    connect(this, &Relay::Open, m_port, &Port::Open);
    connect(this, &Relay::Close, m_port, &Port::Close);
    connect(this, &Relay::Write, m_port, &Port::Write);
    m_portThread.start(QThread::NormalPriority);
}

Relay::~Relay()
{
    m_portThread.quit();
    m_portThread.wait();
}

bool Relay::Ping(const QString& PortName)
{
    QMutexLocker locker(&m_mutex);
    m_semaphore.acquire(m_semaphore.available());
    m_connected = false;
    do {
        emit Close();
        if (!m_semaphore.tryAcquire(1, 1000))
            break;

        if (!PortName.isEmpty())
            m_port->setPortName(PortName);

        emit Open(QIODevice::ReadWrite);
        if (!m_semaphore.tryAcquire(1, 1000))
            break;

        emit Write(parcel(PING));
        if (!m_semaphore.tryAcquire(1, 1000)) {
            emit Close();
            break;
        }
        m_connected = true;
    } while (0);
    return m_connected;
}

bool Relay::IsConnected() const
{
    m_result = false;
    m_semaphore.acquire(m_semaphore.available());
    return m_connected;
}

bool Relay::SetEnabledRelay(int relay)
{
    QMutexLocker Locker(&m_mutex);
    if (IsConnected()) {
        quint8 r = static_cast<quint8>(relay); //32 r = pow(2, relay);
        emit Write(parcel(SET_CHANNEL, r));
        if (m_semaphore.tryAcquire(1, 100))
            m_result = true;
    }
    return m_result;
}

bool Relay::SetEnabledRelays(quint32 relay)
{
    QMutexLocker Locker(&m_mutex);
    if (IsConnected()) {
        emit Write(parcel(SET_CHANNEL, relay));
        if (m_semaphore.tryAcquire(1, 100))
            m_result = true;
    }
    return m_result;
}

//bool Relay::GetEnabledRelays(quint32& relay)
//{
//    QMutexLocker Locker(&m_mutex);
//    if (IsConnected()) {
//        emit Write(Parcel(GET_ENABLED_RELAYS, (uint8_t*)&relay, sizeof(quint32)));
//        if (m_semaphore.tryAcquire(100))
//            m_result = true;
//    }
//    return m_result;
//}

//quint32 Relay::GetEnabledRelays()
//{
//    quint32 relay;
//    GetEnabledRelays(relay);
//    return relay;
//}

void Relay::RxPing(const QByteArray& /*data*/)
{
    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
    //qDebug() << "PING" << data.toHex().toUpper();
    m_semaphore.release();
}

void Relay::RxSetEnabledRelays(const QByteArray& /*data*/)
{
    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
    //qDebug() << "SET_ENABLED_RELAYS" << data.toHex().toUpper();
    m_semaphore.release();
}

void Relay::RxGetEnabledRelays(const QByteArray& /*data*/)
{
    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
    //qDebug() << "GET_ENABLED_RELAYS" << data.toHex().toUpper();
    m_semaphore.release();
}

void Relay::RxBufferOverflow(const QByteArray& data)
{
    qDebug() << "BUFFER_OVERFLOW" << data.toHex().toUpper();
    //m_semaphore.release();
}

void Relay::RxWrongCommand(const QByteArray& data)
{
    qDebug() << "WRONG_COMMAND" << data.toHex().toUpper();
    //m_semaphore.release();
}

void Relay::RxTextualParcel(const QByteArray& data)
{
    qDebug() << "TEXTUAL_PARCEL" << QString::fromLocal8Bit(data.data(), data.size()).mid(4, data.size() - 5);
    //m_semaphore.release();
}

void Relay::RxCrcError(const QByteArray& data)
{
    qDebug() << "CRC_ERROR" << data.toHex().toUpper();
    //m_semaphore.release();
}

void Relay::RxNullFunction(const QByteArray& data)
{
    qDebug() << "RxNullFunction" << data.toHex().toUpper();
    //m_semaphore.release();
}

////////////////////////////////
/// \brief SerialPort::SerialPort
/// \param manInterface
///
Port::Port(Relay* manInterface)
    : m_r(manInterface)
    , m_f(QVector<Port::func>(0x100, &Relay::RxNullFunction))
{
    m_f[PING] = &Relay::RxPing;

    m_f[SET_CHANNEL] = &Relay::RxSetEnabledRelays;
    m_f[SET_CUSTOM] = &Relay::RxGetEnabledRelays;

    m_f[BUFFER_OVERFLOW] = &Relay::RxBufferOverflow;
    m_f[WRONG_COMMAND] = &Relay::RxWrongCommand;
    m_f[TEXTUAL_PARCEL] = &Relay::RxTextualParcel;
    m_f[CRC_ERROR] = &Relay::RxCrcError;

    setBaudRate(QSerialPort::Baud9600);
    setParity(QSerialPort::NoParity);
    setFlowControl(QSerialPort::NoFlowControl);
    connect(this, &QSerialPort::readyRead, this, &Port::ReadyRead);
}

void Port::Open(int mode)
{
    if (open(static_cast<OpenMode>(mode)))
        m_r->m_semaphore.release();
}

void Port::Close()
{
    close();
    m_r->m_semaphore.release();
}

void Port::Write(const QByteArray& data)
{
    write(data);
}

void Port::ReadyRead()
{
    QMutexLocker locker(&m_mutex);
    m_data.append(readAll());
    qDebug() << m_data.toHex().toUpper();
    for (int i = 0; i < m_data.size() - 3; ++i) {
        const Parcel* const parcel = reinterpret_cast<const Parcel*>(m_data.constData() + i);
        if (parcel->start == RX) {
            if ((parcel->len + i) <= m_data.size()) {
                m_tmpData = m_data.mid(i, parcel->len);
                if (checkParcel(m_data.mid(i, parcel->len)))
                    (m_r->*m_f[parcel->cmd])(m_tmpData /**parcel*/);
                else {
                    (m_r->*m_f[CRC_ERROR])(m_tmpData /**parcel*/);
                    m_data.clear();
                }
                m_data.remove(0, i + parcel->len);
                i = -1;
            }
        }
    }
    //    QMutexLocker locker(&m_mutex);
    //    m_data.append(readAll());
    //    for (int i = 0; i < m_data.size() - 3; ++i) {
    //        const Parcel_t* p = reinterpret_cast<const Parcel_t*>(m_data.constData() + i);
    //        if (p->Start == 0x55AA) {
    //            if ((i + p->Len) <= m_data.size()) {
    //                m_tmpData = m_data.mid(i, p->Len);
    //                if (CheckData(m_tmpData))
    //                    (m_r->*m_f[p->Cmd])(m_tmpData);
    //                else {
    //                    (m_r->*m_f[CRC_ERROR])(m_tmpData);
    //                    m_data.clear();
    //                }
    //                m_data.remove(0, i + p->Len);
    //                i = -1;
    //            }
    //        }
    //    }
}
