#include "mt4080.h"
#include <QDebug>

const int id1 = qRegisterMetaType<MT4080::Display>("Display_t");

MT4080::MT4080(QObject* parent)
    : QObject(parent)
    , port(parent)
{
    port.setParity(QSerialPort::NoParity);
    port.setBaudRate(9600);
    connect(&port, &QSerialPort::readyRead, this, &MT4080::ReadyRead, Qt::DirectConnection);
}

MT4080::~MT4080() { port.close(); }

bool MT4080::open(const QString& portName)
{
    port.setPortName(portName);
    return port.open(QSerialPort::ReadOnly);
}

void MT4080::close() { port.close(); }

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
        switch (*reinterpret_cast<uint16_t*>(m_data.data() + i)) {
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
    m_display.primary.value = static_cast<double>(m->value1);

    Value2 = static_cast<double>(m->value2);
    m_display.secondary.value = static_cast<double>(m->value2);

    if (data.size() < 11) {
        m_display.secondary.function.clear();
        m_display.secondary.unit.clear();
        m_display.secondary.value = 0.0;
        m_display.frequency.clear();
        m_display.level.clear();
    }

    emit primary(Value1);
    emit second(Value2);
    emit display(m_display);
}

void MT4080::UpdateParameters(const QByteArray& data)
{
    auto rawDisplay = *reinterpret_cast<const RawDisplay*>(data.data());

    m_display.primary.function = slMode1[rawDisplay.function1].first;
    m_display.primary.unit = slMode1[rawDisplay.function1].second;

    if (rawDisplay.function1 == DCR) {
        m_display.secondary.function.clear();
        m_display.secondary.unit.clear();
    } else {
        m_display.secondary.function = slMode2[rawDisplay.function2].first;
        m_display.secondary.unit = slMode2[rawDisplay.function2].second;
    }
    m_display.frequency = slFrequency[rawDisplay.testFrequency];
    m_display.level = slLevel[rawDisplay.testLevel];

    m_display.speed = slSpeed[rawDisplay.measureSpeed];
    m_display.speed += slRelative[rawDisplay.relative];
}
