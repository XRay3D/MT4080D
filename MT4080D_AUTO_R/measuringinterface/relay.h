#ifndef MY_PROTOCOL_H
#define MY_PROTOCOL_H

#include "common_interfaces.h"
#include <QComboBox>
#include <QDebug>
#include <QElapsedTimer>
#include <QMutex>
#include <QObject>
#include <QSemaphore>
#include <QSerialPort>
#include <QThread>
#include <QVector>
#include <QWaitCondition>
#include <myprotokol.h>
#include <stdint.h>

enum Command_e {
    // Interface system
    PING,
    // User
    SET_CHANNEL,
    SET_CUSTOM,
    // Interface system
    BUFFER_OVERFLOW = 0xF0,
    WRONG_COMMAND = 0xF1,
    TEXTUAL_PARCEL = 0xF2,
    CRC_ERROR = 0xF3
};

class CallBack {
public:
    virtual ~CallBack() = default;
    // Interface system
    virtual void RxPing(const QByteArray& data) = 0;
    // User
    virtual void RxSetEnabledRelays(const QByteArray& data) = 0;
    virtual void RxGetEnabledRelays(const QByteArray& data) = 0;
    // Interface system
    virtual void RxBufferOverflow(const QByteArray& data) = 0;
    virtual void RxWrongCommand(const QByteArray& data) = 0;
    virtual void RxTextualParcel(const QByteArray& data) = 0;
    virtual void RxCrcError(const QByteArray& data) = 0;
    virtual void RxNullFunction(const QByteArray& data) = 0;
};

class Port;

class Relay : public QObject, private MyProtokol, public CommonInterfaces, private CallBack {
    Q_OBJECT
    friend class Port;

public:
    Relay(QObject* parent = nullptr);
    ~Relay();

    bool ping(const QString& PortName = QString());
    bool isConnected() const;

    bool SetEnabledRelay(int relay);
    bool SetEnabledRelays(quint32 relay);
    //    bool GetEnabledRelays(quint32& relay);
    //    quint32 GetEnabledRelays();

signals:
    void Open(int mode);
    void Close();
    void Write(const QByteArray& data);

private:
    Port* m_port;
    QThread m_portThread;
    QMutex m_mutex;
    quint32 m_relay;
    int m_counter;
    mutable QSemaphore m_semaphore;
    mutable bool m_result;

    void RxPing(const QByteArray& data);
    void RxSetEnabledRelays(const QByteArray& data);
    void RxGetEnabledRelays(const QByteArray& data);

    void RxBufferOverflow(const QByteArray& data);
    void RxWrongCommand(const QByteArray& data);
    void RxTextualParcel(const QByteArray& data);
    void RxCrcError(const QByteArray& data);
    void RxNullFunction(const QByteArray& data);
};

class Port : public QSerialPort, private MyProtokol {
    Q_OBJECT
public:
    Port(Relay* manInterface);

    void Open(int mode);
    void Close();
    void Write(const QByteArray& data);

    Relay* m_r;
    typedef void (Relay::*func)(const QByteArray&);
    QVector<func> m_f;

private:
    void ReadyRead();
    QByteArray m_data;
    QByteArray m_tmpData;
    QMutex m_mutex;
    int m_couter;
};

#endif // MY_PROTOCOL_H
