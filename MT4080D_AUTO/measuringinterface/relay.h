#ifndef MY_PROTOCOL_H
#define MY_PROTOCOL_H

#include "xrdevice.h"
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
#include <stdint.h>

enum Command_e {
    //    // Interface system
    //    PING,
    //    // User
    SET_CHANNEL = 1,
    SET_CUSTOM,
    //    // Interface system
    //    BUFFER_OVERFLOW = 0xF0,
    //    WRONG_COMMAND = 0xF1,
    //    TEXTUAL_PARCEL = 0xF2,
    //    CRC_ERROR = 0xF3
};

//class CallBack {
//public:
//    virtual ~CallBack() = default;
//    // Interface system
//    virtual void RxPing(const QByteArray& data) = 0;
//    // User
//    virtual void RxSetEnabledRelays(const QByteArray& data) = 0;
//    virtual void RxGetEnabledRelays(const QByteArray& data) = 0;
//    // Interface system
//    virtual void RxBufferOverflow(const QByteArray& data) = 0;
//    virtual void RxWrongCommand(const QByteArray& data) = 0;
//    virtual void RxTextualParcel(const QByteArray& data) = 0;
//    virtual void RxCrcError(const QByteArray& data) = 0;
//    virtual void RxNullFunction(const QByteArray& data) = 0;
//};

class Relay : public XrProtokol::Device {
    Q_OBJECT

public:
    Relay(QObject* parent = nullptr);
    ~Relay();

    // Device interface
    XrProtokol::Type type() const override { return XrProtokol::Type::Relay29_58; }

    bool setChannel(uint8_t relay);
    bool setEnabledRelay(uint8_t relay);

    //    bool Ping(const QString& PortName = QString());
    //    bool IsConnected() const;

    //    bool SetEnabledRelay(int relay);
    //    bool SetEnabledRelays(quint32 relay);
    //    //    bool GetEnabledRelays(quint32& relay);
    //    //    quint32 GetEnabledRelays();

    //signals:
    //    void Open(int mode);
    //    void Close();
    //    void Write(const QByteArray& data);

    //private:
    //    Port* m_port;
    //    QThread m_portThread;
    //    QMutex m_mutex;
    //    quint32 m_relay;
    //    int m_counter;
    //    mutable QSemaphore m_semaphore;
    //    mutable bool m_result;

    //    void RxPing(const QByteArray& data);
    //    void RxSetEnabledRelays(const QByteArray& data);
    //    void RxGetEnabledRelays(const QByteArray& data);

    //    void RxBufferOverflow(const QByteArray& data);
    //    void RxWrongCommand(const QByteArray& data);
    //    void RxTextualParcel(const QByteArray& data);
    //    void RxCrcError(const QByteArray& data);
    //    void RxNullFunction(const QByteArray& data);
};

#endif // MY_PROTOCOL_H
