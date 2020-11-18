#include "scpi.h"
#include <QDebug>
#include <QThread>

SCPI::SCPI(QObject* parent)
    : QSerialPort(parent)
{
    setBaudRate(QSerialPort::Baud9600);
    setParity(QSerialPort::NoParity);
    setFlowControl(QSerialPort::NoFlowControl);
}

bool SCPI::ping(const QString& potName)
{
    QMutexLocker locker(&m_mutex);
    close();
    m_connected = false;
    setPortName(potName);
    if (open(ReadWrite)) {
        waitForReadyRead(100);
        setDataTerminalReady(true);
        setRequestToSend(true);
        waitForReadyRead(100);
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
    while (++m_counter < 100 && !canReadLine())
        waitForReadyRead(100);
    m_data.append(readAll());
    return m_data;
}

double SCPI::getDcVoltage()
{
    QMutexLocker locker(&m_mutex);
    if (isConnected()) {
        WriteRead("MEASure:VOLTage:DC?");
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

void SCPI::Write(const QByteArray& data)
{
    m_data.clear();
    write(data + "\r\n");
    m_counter = 0;
    while (++m_counter < 1000 && !((DataCarrierDetectSignal | DataSetReadySignal) & pinoutSignals()))
        waitForReadyRead(10);
}
