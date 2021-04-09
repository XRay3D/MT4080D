#include "scpi.h"
#include <QDebug>
#include <QThread>
#include <QTime>

SCPI::SCPI(QObject* parent)
    : QSerialPort(parent)
{
    setBaudRate(QSerialPort::Baud9600);
    setParity(QSerialPort::NoParity);
    setFlowControl(QSerialPort::NoFlowControl);
    //    setFlowControl(QSerialPort::HardwareControl);

    //    connect(this, &QSerialPort::baudRateChanged, [](qint32 baudRate, QSerialPort::Directions directions) { qDebug() << baudRate << directions; });
    //    connect(this, &QSerialPort::breakEnabledChanged, [](bool set) { qDebug() << "BE" << set; });
    //    connect(this, &QSerialPort::dataBitsChanged, [](QSerialPort::DataBits dataBits) { qDebug() << dataBits; });
    //    connect(this, &QSerialPort::dataTerminalReadyChanged, [](bool set) { qDebug() << "DTR" << set; });
    //    //    connect(this, &QSerialPort::errorOccurred, [](QSerialPort::SerialPortError error) { qDebug() << error; });
    //    connect(this, &QSerialPort::flowControlChanged, [](QSerialPort::FlowControl flow) { qDebug() << flow; });
    //    connect(this, &QSerialPort::parityChanged, [](QSerialPort::Parity parity) { qDebug() << parity; });
    //    connect(this, &QSerialPort::requestToSendChanged, [](bool set) { qDebug() << "RTS" << set; });
    //    connect(this, &QSerialPort::stopBitsChanged, [](QSerialPort::StopBits stopBits) { qDebug() << stopBits; });

    //    connect(this, &QIODevice::readyRead, [this]() { qDebug() << "readyRead"; s.release(); });
}

SCPI::~SCPI() { }

bool SCPI::ping(const QString& potName)
{
    QMutexLocker locker(&m_mutex);
    close();
    m_connected = false;
    setPortName(potName);
    if (open(ReadWrite)) {
        thread()->msleep(100);
        setDataTerminalReady(true);
        setRequestToSend(true);
        thread()->msleep(100);
        qDebug() << WriteRead("*IDN?");
        if (m_data.endsWith("\r\n")) {
            Write("SYSTem:REMote");
            Write("*CLS");
            //            Write("DETector:BANDwidth 3");
            m_connected = true;
        }
    }
    return m_connected;
}

QByteArray& SCPI::WriteRead(const QByteArray& data)
{
    m_data.clear();
    write(data + "\r\n");
    m_counter = 0;
    while (++m_counter < 1000 && !canReadLine()) {
        waitForReadyRead(100);
    }
    m_data.append(readAll());
    return m_data;
}

void SCPI::Write(const QByteArray& data)
{
    m_data.clear();
    write(data + "\r\n");
    m_counter = 0;
    while (++m_counter < 1000 && !((DataCarrierDetectSignal | DataSetReadySignal) & pinoutSignals())) {
        waitForReadyRead(10);
    }
}

double SCPI::getDcVoltage()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        WriteRead("MEASure:VOLTage:DC? DEF, MIN");
        if (m_data.endsWith("\r\n")) {
            value = m_data.toDouble();
            measureReady(value);
            return value;
        }
    }
    return 0.0;
}

double SCPI::getAcVoltage()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        WriteRead("MEASure:VOLTage:AC?");
        if (m_data.endsWith("\r\n")) {
            value = m_data.toDouble();
            measureReady(value);
            return value;
        }
    }
    return 0.0;
}

double SCPI::getDcCurrent()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        WriteRead("MEASure:CURRent:DC?");
        if (m_data.endsWith("\r\n")) {
            value = m_data.toDouble();
            measureReady(value);
            return value;
        }
    }
    return 0.0;
}

double SCPI::getResistance2W()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        WriteRead("MEASure:RESistance?");
        if (m_data.endsWith("\r\n")) {
            value = m_data.toDouble();
            measureReady(value);
            return value;
        }
    }
    return 0.0;
}

double SCPI::getResistance4W()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        // MEASure:FRESistance? DEF, MIN
        WriteRead("MEASure:FRESistance? DEF, MIN");
        if (m_data.endsWith("\r\n")) {
            value = m_data.toDouble();
            measureReady(value);
            return value;
        }
    }
    return 0.0;
}
