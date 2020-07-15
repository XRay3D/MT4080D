#include "mt4080.h"
#include <QDebug>

const int id1 = qRegisterMetaType<MT4080::Display_t>("Display_t");

MT4080::MT4080(QObject* parent)
    : QObject(parent)
    , port(parent)
    , slFrequency{ "100Hz", "120Hz", "1kHz", "10kHz", "100kHz" }
    , slLevel{ "50mVrms", "250mVrms", "1Vrms", "1VDC" }
    , slRelative{ "REL", "" }
    , slSpeed{ "SLOW ", "FAST" }
    , slCombDispParallelMode{ qMakePair(QStringLiteral("Cp"), QStringLiteral("D")), qMakePair(QStringLiteral("Cp"), QStringLiteral("Q")), qMakePair(QStringLiteral("Lp"), QStringLiteral("D")), qMakePair(QStringLiteral("Lp"), QStringLiteral("Q")) } //    Parallel Mode
    , slCombDispSerialMode{ qMakePair(QStringLiteral("Z"), QString("θ")), qMakePair(QStringLiteral("Cs"), QStringLiteral("D")), qMakePair(QStringLiteral("Cs"), QStringLiteral("Q")), qMakePair(QStringLiteral("Cs"), QStringLiteral("ESR")), qMakePair(QStringLiteral("Ls"), QStringLiteral("D")), qMakePair(QStringLiteral("Ls"), QStringLiteral("Q")), qMakePair(QStringLiteral("Ls"), QStringLiteral("ESR")) } //    Serial Mode
    , slMode1{ qMakePair(QStringLiteral("Lp"), QStringLiteral("H")), qMakePair(QStringLiteral("Ls"), QStringLiteral("H")), qMakePair(QStringLiteral("Cp"), QString("µF")), qMakePair(QStringLiteral("Cs"), QString("µF")), qMakePair(QStringLiteral("Z"), QString("Ω")), qMakePair(QStringLiteral("DCR"), QString("Ω")) }
    , slMode2{ qMakePair(QStringLiteral("D"), QStringLiteral("")), qMakePair(QStringLiteral("Q"), QStringLiteral("")), qMakePair(QString("θ"), QStringLiteral("Deg")), qMakePair(QStringLiteral("ESR"), QString("Ω")), qMakePair(QStringLiteral(""), QStringLiteral("")) }

{
    port.setParity(QSerialPort::NoParity);
    port.setBaudRate(9600);
    connect(&port, &QSerialPort::readyRead, this, &MT4080::ReadyRead, Qt::DirectConnection);
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
    //    qDebug(Q_FUNC_INFO);
    //    qDebug() << begin << end;
    quint8 c = 0;
    for (int i = begin; i < end; ++i)
        c += data[i];
    return !c;
}

void MT4080::ReadyRead()
{
    m_data.append(port.readAll());
    if (m_data.size() < PARAMETER_LENGTH)
        return;
    for (int i = 0, size = m_data.size() - 1; i < size; ++i) {
        const uint16_t header = m_data[i + 0] << 8 | m_data[i + 1];
        switch (header) {
        case HEADER_PARAMETERS: {
            const int end = i + PARAMETER_LENGTH;
            if (m_data.size() >= end && CheckData(m_data, i, end)) {
                UpdateParameters(m_data.mid(i, PARAMETER_LENGTH));
                m_data.remove(0, end);
                return;
            }
        } break;
        case HEADER_DCR: {
            const int end = i + DCR_LENGTH;
            if (m_data.size() >= end && CheckData(m_data, i, end)) {
                UpdateValues(m_data.mid(i, DCR_LENGTH));
                m_data.remove(0, end);
                return;
            }
        } break;
        case HEADER_OTHER: {
            const int end = i + OTHER_LENGTH;
            if (m_data.size() >= end && CheckData(m_data, i, end)) {
                UpdateValues(m_data.mid(i, OTHER_LENGTH));
                m_data.remove(0, end);
                return;
            }
        } break;
        default:
            continue;
        }
    }
}

void MT4080::UpdateValues(const QByteArray& data)
{
    const Measure_t* const m = reinterpret_cast<const Measure_t*>(data.data());

    Value1 = static_cast<double>(m->value1);
    display.firest.value = static_cast<double>(m->value1);

    Value2 = static_cast<double>(m->value2);
    display.secopnd.value = static_cast<double>(m->value2);

    if (data.size() < 11) {
        display.secopnd.function.clear();
        display.secopnd.unit.clear();
        display.secopnd.value = 0.0;
        display.frequency.clear();
        display.level.clear();
    }

    emit Primary(Value1);
    emit Second(Value2);
    emit Display(display);
}

void MT4080::UpdateParameters(const QByteArray& data)
{
    rawDisplay = *reinterpret_cast<const RawDisplay_t*>(data.data());

    display.firest.function = slMode1.at(rawDisplay.function1).first;
    display.firest.unit = slMode1.at(rawDisplay.function1).second;

    if (rawDisplay.function1 == DCR) {
        display.secopnd.function.clear();
        display.secopnd.unit.clear();
    } else {
        display.secopnd.function = slMode2.at(rawDisplay.function2).first;
        display.secopnd.unit = slMode2.at(rawDisplay.function2).second;
    }
    display.frequency = slFrequency.at(rawDisplay.testFrequency);
    display.level = slLevel.at(rawDisplay.testLevel);
    display.speed = slSpeed.at(rawDisplay.measureSpeed) + slRelative.at(rawDisplay.relative);
}
