#ifndef MT4080_H
#define MT4080_H

#include <QMutex>
#include <QSemaphore>
#include <QSerialPort>
#include <QTimer>
#include <QWidget>

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <stdint.h>

class MT4080 : public QObject {
    Q_OBJECT
public:
    explicit MT4080(QObject* parent = 0);
    ~MT4080();

    bool Open(const QString& portName);
    void Close();

    typedef struct Display_t {
        struct {
            QString function;
            double value;
            QString unit;
        } firest;
        struct {
            QString function;
            double value;
            QString unit;
        } secopnd;
        QString speed;
        QString frequency;
        QString level;
    } Display_t;

#pragma pack(push, 1)
    typedef struct RawDisplay_t {
        uint8_t start;
        uint8_t type;
        unsigned testFrequency : 3;
        unsigned testLevel : 2;
        unsigned measureSpeed : 1;
        unsigned relative : 1;
        unsigned calibration : 1;
        unsigned function1 : 3;
        unsigned function2 : 2;
        unsigned rangeHoldAndUnit : 4;
        unsigned nShortCalOpenCal : 1;
        unsigned measurementModes : 4;
        unsigned remoteMode : 2;
        unsigned cs : 8;
    } RawDisplay_t;

    typedef struct Measure_t {
        uint8_t start;
        uint8_t type;
        float value1;
        float value2;
        uint8_t cs;
    } Measure_t;

#pragma pack(pop)

signals:
    void Primary(double val);
    void Second(double val);
    void Display(const Display_t& val);

private:
    enum ParcelType {
        MEASURE_PARAMETERS = 4, //  Параметры измерения
        MEASURE_DCR = 1, //        Измерение соапротивления DCR
        MEASURE_OTHER = 9, //      Другие измерерния
    };

    enum BeginParcel {
        START_DATA = 2, //          Начало посылки
        HEADER_PARAMETERS = START_DATA << 8 | MEASURE_PARAMETERS, //  Параметры измерения
        HEADER_DCR = START_DATA << 8 | MEASURE_DCR, //              Измерение соапротивления DCR
        HEADER_OTHER = START_DATA << 8 | MEASURE_OTHER, //          Другие измерерния
    };

    enum ParcelLength { // Длина посылки
        PARAMETER_LENGTH = 6,
        DCR_LENGTH = 7,
        OTHER_LENGTH = 11
    };

    bool CheckData(const QByteArray& data, int begin, int end);
    void ReadyRead();
    void UpdateParameters(const QByteArray& data);
    void UpdateValues(const QByteArray& data);

    //    QMutex mutex;
    //    QSemaphore semaphore;
    QByteArray m_data;

    double Value1;
    double Value2;

    QSerialPort port;

    const QStringList slFrequency;
    const QStringList slLevel;
    const QStringList slRelative;
    const QStringList slSpeed;

    using Pair = QPair<QString, QString>;

    const QList<Pair> slCombDispParallelMode;
    const QList<Pair> slCombDispSerialMode;
    const QList<Pair> slMode1;
    const QList<Pair> slMode2;

    Display_t display;
    RawDisplay_t rawDisplay;

    enum primaryParameterDisplay {
        Lp, // Parallel Inductance
        Ls, // Serial Inductance
        Cp, // Parallel Capacitance
        Cs, // Serial Capacitance
        Z, // AC Impedance
        DCR // DC Resistance
    };

    enum secondParameterDisplay {
        D, // Dissipation Factor
        Q, // Quality Factor
        O, // Phase Angle
        ESR // Equivalence Serial Resistance
    };

    enum frequency {
        f100Hz,
        f120Hz,
        f1KHz,
        f10KHz,
        f100KHz // (MT4080A only)
    };

    enum level {
        l1Vrms,
        l250mVrms,
        l50mVrms,
        l1VDC //(DCR only)
    };

    enum range {
        G,
        M,
        k,
        m /*= 3*/,
        u,
        n,
        p
    };

    //    Z 0.000Ω to 9999 MΩ
    //    L 0.000 μH to 9999 H
    //    C 0.000 pF to 9999 F
    //    DCR 0.000Ω  to 9999 MΩ
    //    ESR 0.000Ω  to 9999 Ω
    //    D 0.000 to 9999
    //    Q 0.000 to 9999
    //    θ -180.0°  to 180.0°

    //    ASCII string Numerical code
    //    1VDC 0
    //    1Vrms 1
    //    250mVrms 2
    //    50mVrms 3

    //    ASCII string Numerical code
    //    100Hz 0
    //    120Hz 1
    //    1KHz 2
    //    10KHz 3
    //    100KHz 4

    //    ASCII string Numerical code
    //    pF 0
    //    nF 1
    //    uF 2
    //    mF 3
    //    F 4
    //    nH 8
    //    uH 9
    //    mH 10
    //    H 11
    //    KH 12
    //    mOhm 17
    //    Ohm 18
    //    KOhm 19
    //    MOhm 20

    //    ASCII string Numerical code
    //    SLOW 0
    //    FAST 1

    //    Query the measurement mode. Six fields will be returned.
    //    1. Frequency
    //    2. Level
    //    3. Speed
    //    4. Measurement mode
    //    5. Unit of primary display
    //    6. Unit of secondary display
    //    The existence of field 6 depends on the measurement mode. For
    //    example, there’s no field 6 if the measurement mode is DCR. The
    //    separation between fields is space (ASCII 20H).
    //    Example:
    //    ASC ON
    //    CPD
    //    MODE?
    //    1KHz 1Vrms SLOW CpD uF (return value)
    //    ASC ON
    //    CPRP
    //    MODE?
    //    1KHz 1Vrms SLOW CpRp uF Ohm (return value)
};

#endif // MT4080_H
