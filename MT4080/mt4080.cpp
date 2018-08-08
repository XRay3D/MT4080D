#include "mt4080.h"
#include <QDebug>

int id1 = qRegisterMetaType<MT4080::Display_t>("Display_t");

MT4080::MT4080(QObject* parent)
    : QObject(parent)
    , port(parent)
    , slFrequency(QString("100Hz|120Hz|1kHz|10kHz|100kHz").split('|'))
    , slLevel(QString("50mVrms|250mVrms|1Vrms|1VDC").split('|'))
    , slRelative(QString("REL|").split('|'))
    , slSpeed(QString("SLOW |FAST").split('|'))
    , slCombDispParallelMode(QList<Pair>()
          << qMakePair(QString("Cp"), QString("D"))
          << qMakePair(QString("Cp"), QString("Q"))
          << qMakePair(QString("Lp"), QString("D"))
          << qMakePair(QString("Lp"), QString("Q"))) //    Parallel Mode

    , slCombDispSerialMode(QList<Pair>()
          << qMakePair(QString("Z"), QString("θ"))
          << qMakePair(QString("Cs"), QString("D"))
          << qMakePair(QString("Cs"), QString("Q"))
          << qMakePair(QString("Cs"), QString("ESR"))
          << qMakePair(QString("Ls"), QString("D"))
          << qMakePair(QString("Ls"), QString("Q"))
          << qMakePair(QString("Ls"), QString("ESR"))) //    Serial Mode

    , slMode1(QList<Pair>()
          << qMakePair(QString("Lp"), QString("H"))
          << qMakePair(QString("Ls"), QString("H"))
          << qMakePair(QString("Cp"), QString("µF"))
          << qMakePair(QString("Cs"), QString("µF"))
          << qMakePair(QString("Z"), QString("Ω"))
          << qMakePair(QString("DCR"), QString("Ω")))

    , slMode2(QList<Pair>()
          << qMakePair(QString("D"), QString(""))
          << qMakePair(QString("Q"), QString(""))
          << qMakePair(QString("θ"), QString("Deg"))
          << qMakePair(QString("ESR"), QString("Ω"))
          << qMakePair(QString(""), QString("")))

{
    port.setParity(QSerialPort::NoParity);
    port.setBaudRate(9600);
    connect(&port, &QSerialPort::readyRead, this, &MT4080::ReadyRead);
}

MT4080::~MT4080()
{
    port.close();
}

bool MT4080::Open(const QString& portName)
{
    port.setPortName(portName);
    return port.open(QSerialPort::ReadOnly);
}

void MT4080::Close()
{
    port.close();
}

bool MT4080::CheckData(const QByteArray& data, int begin, int end)
{
    unsigned char c = 0;
    for (int i = begin; i < end; ++i) {
        c += data[i];
    }
    return !c;
}

void MT4080::ReadyRead()
{
    QMutexLocker locker(&mutex);

    enum ParcelType {
        START_DATA = 2, //Начало посылки
        MEASURE_PARAMETERS = 4, //  Параметры измерения
        MEASURED_DCR = 1, //  Измерение соапротивления DCR
        MEASURED_OTHER = 9, //  Другие измерерния
    };

    enum ParcelLength {
        PARAMETER_LENGTH = 6, // Длина посылки 1
        DCR_LENGTH = 7, // Длина посылки 2
        OTHER_LENGTH = 11 // Длина посылки 3
    };

    m_data.append(port.readAll());

    for (int i = 0; i < m_data.size() - 1 && m_data.size() >= PARAMETER_LENGTH; ++i) {
        const Measure_t* const m = reinterpret_cast<Measure_t*>(m_data.data() + i);
        if (m->start == START_DATA) {
            int end;
            switch (m->type) {
            case MEASURE_PARAMETERS:
                end = i + PARAMETER_LENGTH;
                if (m_data.size() >= end && CheckData(m_data, i, end)) {
                    UpdateOtherDisp(m_data.mid(i, PARAMETER_LENGTH));
                    m_data.remove(0, end);
                    return;
                }
                break;
            case MEASURED_DCR:
                end = i + DCR_LENGTH;
                if (m_data.size() >= end && CheckData(m_data, i, end)) {
                    UpdateValues(m_data.mid(i, DCR_LENGTH));
                    m_data.remove(0, end);
                    return;
                }
                break;
            case MEASURED_OTHER:
                end = i + OTHER_LENGTH;
                if (m_data.size() >= end && CheckData(m_data, i, end)) {
                    UpdateValues(m_data.mid(i, OTHER_LENGTH));
                    m_data.remove(0, end);
                    return;
                }
                break;
            default:
                continue;
            }
        }
    }
}

void MT4080::UpdateValues(const QByteArray& data)
{
    const Measure_t* const m = reinterpret_cast<const Measure_t*>(data.data());

    Value1 = m->value1;
    display.firest.value = m->value1;

    Value2 = m->value2;
    display.secopnd.value = m->value2;

    if (data.size() < 11) {
        display.secopnd.function.clear();
        display.secopnd.unit.clear();
        display.secopnd.value = 0.0f;
        display.frequency.clear();
        display.level.clear();
    }

    emit Primary(Value1);
    emit Second(Value2);
    emit Display(display);
}

void MT4080::UpdateOtherDisp(const QByteArray& data)
{
    rawDisplay = *reinterpret_cast<const RawDisplay_t*>(data.data());

    display.firest.function = slMode1.at(rawDisplay.function1).first;
    display.firest.unit = slMode1.at(rawDisplay.function1).second;

    if (rawDisplay.function1 == DCR) {
        display.secopnd.function.clear();
        display.secopnd.unit.clear();
    }
    else {
        display.secopnd.function = slMode2.at(rawDisplay.function2).first;
        display.secopnd.unit = slMode2.at(rawDisplay.function2).second;
    }
    display.frequency = slFrequency.at(rawDisplay.testFrequency);
    display.level = slLevel.at(rawDisplay.testLevel);
    display.speed = slSpeed.at(rawDisplay.measureSpeed) + slRelative.at(rawDisplay.relative);
}
