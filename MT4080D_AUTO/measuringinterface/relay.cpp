#include "relay.h"

#include <QDebug>
#include <QSerialPortInfo>
#include <QTimer>

Relay::Relay(QObject* parent)
    : XrProtokol::Device(parent) {

    registerCallback<SET_CHANNEL>();
    //    m_port = new Port(this);
    //    m_port->moveToThread(&m_portThread);
    //    connect(&m_portThread, &QThread::finished, m_port, &QObject::deleteLater);
    //    connect(this, &Relay::Open, m_port, &Port::Open);
    //    connect(this, &Relay::Close, m_port, &Port::Close);
    //    connect(this, &Relay::Write, m_port, &Port::Write);
    //    m_portThread.start(QThread::NormalPriority);
}

Relay::~Relay() {
    //    m_portThread.quit();
    //    m_portThread.wait();
}

bool Relay::setChannel(uint8_t relay) {
    return exchange(SET_CHANNEL, relay);
}

bool Relay::setEnabledRelay(uint8_t relay) {
    return exchange(SET_CHANNEL, relay);
}

//bool Relay::Ping(const QString& PortName) {
//    QMutexLocker locker(&m_mutex);
//    m_semaphore.acquire(m_semaphore.available());
//    m_connected = false;
//    do {
//        emit Close();
//        if(!m_semaphore.tryAcquire(1, 1000))
//            break;

//        if(!PortName.isEmpty())
//            m_port->setPortName(PortName);

//        emit Open(QIODevice::ReadWrite);
//        if(!m_semaphore.tryAcquire(1, 1000))
//            break;

//        emit Write(parcel(PING));
//        if(!m_semaphore.tryAcquire(1, 1000)) {
//            emit Close();
//            break;
//        }
//        m_connected = true;
//    } while(0);
//    return m_connected;
//}

//bool Relay::IsConnected() const {
//    m_result = false;
//    m_semaphore.acquire(m_semaphore.available());
//    return m_connected;
//}

//bool Relay::SetEnabledRelay(int relay) {
//    QMutexLocker Locker(&m_mutex);
//    if(IsConnected()) {
//        quint8 r = static_cast<quint8>(relay); //32 r = pow(2, relay);
//        emit Write(parcel(SET_CHANNEL, r));
//        if(m_semaphore.tryAcquire(1, 100))
//            m_result = true;
//    }
//    return m_result;
//}

//bool Relay::SetEnabledRelays(quint32 relay) {
//    QMutexLocker Locker(&m_mutex);
//    if(IsConnected()) {
//        emit Write(parcel(SET_CHANNEL, relay));
//        if(m_semaphore.tryAcquire(1, 100))
//            m_result = true;
//    }
//    return m_result;
//}

////bool Relay::GetEnabledRelays(quint32& relay)
////{
////    QMutexLocker Locker(&m_mutex);
////    if (IsConnected()) {
////        emit Write(Parcel(GET_ENABLED_RELAYS, (uint8_t*)&relay, sizeof(quint32)));
////        if (m_semaphore.tryAcquire(100))
////            m_result = true;
////    }
////    return m_result;
////}

////quint32 Relay::GetEnabledRelays()
////{
////    quint32 relay;
////    GetEnabledRelays(relay);
////    return relay;
////}

//void Relay::RxPing(const QByteArray& /*data*/) {
//    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
//    //qDebug() << "PING" << data.toHex().toUpper();
//    m_semaphore.release();
//}

//void Relay::RxSetEnabledRelays(const QByteArray& /*data*/) {
//    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
//    //qDebug() << "SET_ENABLED_RELAYS" << data.toHex().toUpper();
//    m_semaphore.release();
//}

//void Relay::RxGetEnabledRelays(const QByteArray& /*data*/) {
//    //const Parcel_t* p = reinterpret_cast<const Parcel_t*>(data.constData());
//    //qDebug() << "GET_ENABLED_RELAYS" << data.toHex().toUpper();
//    m_semaphore.release();
//}

//void Relay::RxBufferOverflow(const QByteArray& data) {
//    qDebug() << "BUFFER_OVERFLOW" << data.toHex().toUpper();
//    //m_semaphore.release();
//}

//void Relay::RxWrongCommand(const QByteArray& data) {
//    qDebug() << "WRONG_COMMAND" << data.toHex().toUpper();
//    //m_semaphore.release();
//}

//void Relay::RxTextualParcel(const QByteArray& data) {
//    qDebug() << "TEXTUAL_PARCEL" << QString::fromLocal8Bit(data.data(), data.size()).mid(4, data.size() - 5);
//    //m_semaphore.release();
//}

//void Relay::RxCrcError(const QByteArray& data) {
//    qDebug() << "CRC_ERROR" << data.toHex().toUpper();
//    //m_semaphore.release();
//}

//void Relay::RxNullFunction(const QByteArray& data) {
//    qDebug() << "RxNullFunction" << data.toHex().toUpper();
//    //m_semaphore.release();
//}
