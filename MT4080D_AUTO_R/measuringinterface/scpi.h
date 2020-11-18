#ifndef SCPI_H
#define SCPI_H

#include "common_interfaces.h"

#include <QMutex>
#include <QSerialPort>

class SCPI : public QSerialPort, public CommonInterfaces {
    Q_OBJECT
public:
    explicit SCPI(QObject* parent = nullptr);
    bool ping(const QString& potName = QString());

    double getDcVoltage();
    double getAcVoltage();
    double getDcCurrent();
    double getResistance2W();
    double getResistance4W();

    void Write(const QByteArray& data);
    QByteArray& WriteRead(const QByteArray& data);

signals:
    void measureReady(double);

private:
    QByteArray m_data;
    int m_counter;
    QMutex m_mutex;
    double value = 0.0;
};

#endif // SCPI_H
