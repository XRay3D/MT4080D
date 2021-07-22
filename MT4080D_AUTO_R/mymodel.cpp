#include "mymodel.h"
#include <QColor>
#include <QDebug>
#include <QFile>

template <typename T, size_t N>
int s(T (&)[N]) { return N; }

MyModel::MyModel(QObject* parent)
    : QAbstractTableModel(parent) {
    setObjectName("ModelCoefficients");
    //    memset(m_data, 0, sizeof(m_data));
    //        memset(m_enabled, 0, sizeof(m_enabled));
    QFile file("data.bin");
    if(!file.open(QIODevice::ReadOnly))
        return;
    QByteArray d(file.readAll());
    if(d.size())
        memcpy(m_data, d.constData(), d.size());
}

MyModel::~MyModel() {
    QFile file("data.bin");
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(reinterpret_cast<const char*>(m_data), sizeof(m_data));
}

void MyModel::stateChanged(const UsedMap& enabled, int orientation) {
    if(orientation == Qt::Vertical)
        m_rowsEnabled = enabled;
    else
        m_columnsEnabled = enabled;
    dataChanged(createIndex(0, 0), createIndex(Rows - 1, Columns - 1), {Qt::DisplayRole});
}

//void MyModel::setChData(float* value, int channel)
//{
//    //qDebug() << s(value);
//    if (checkCol(channel)) {
//        for (int resistor = 0; resistor < 5; ++resistor) {
//            if (enabled(channel, resistor))
//                m_data[channel][resistor] = value[resistor];
//        }
//        dataChanged(createIndex(0, channel), createIndex(5, channel), { Qt::DisplayRole });
//    }
//}

void MyModel::setChData(double value, int row, int column) {
    const QModelIndex& index = createIndex(row, column);
    if(checkCol(column) && checkRow(row) && enabled(row, column)) {
        m_data[column][row] = value;
        dataChanged(index, index, {Qt::DisplayRole});
    }
}

double MyModel::getChData(int row, int column) {
    //const QModelIndex& index = createIndex(row, column);
    if(checkCol(column) && checkRow(row))
        return m_data[column][row];
    return 0.0;
}

int MyModel::rowCount(const QModelIndex& /*parent*/) const {
    return Rows;
}

int MyModel::columnCount(const QModelIndex& /*parent*/) const {
    return Columns;
}

QVariant MyModel::data(const QModelIndex& index, int role) const {
    switch(role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        return m_data[index.column()][index.row()];
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    case Qt::BackgroundColorRole:
        return enabled(index) ? QVariant() : QColor(240, 240, 240);
    default:
        return QVariant();
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    switch(role) {
    case Qt::DisplayRole:
    case Qt::EditRole:
        if(checkRow(index.row()) && checkCol(index.column()) && enabled(index)) {
            m_data[index.column()][index.row()] = value.toDouble();
            return true;
        }
        return false;
    default:
        return false;
    }
    return false;
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const {
    switch(orientation) {
    case Qt::Horizontal:
        switch(role) {
        case Qt::TextAlignmentRole:
            return Qt::AlignCenter;
        case Qt::DisplayRole:
            return "Измерение " + QString::number(section + 1);
        default:
            break;
        }
        break;
    case Qt::Vertical:
        switch(role) {
        case Qt::TextAlignmentRole:
            return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
        case Qt::DisplayRole:
            return "      " + QString::number(section + 1);
        default:
            break;
        }
    default:
        break;
    }
    return QVariant();
    //    switch (role) {
    //    case Qt::TextAlignmentRole:
    //        if (orientation == Qt::Horizontal)
    //            return Qt::AlignCenter;
    //        else
    //            return static_cast<int>(Qt::AlignRight | Qt::AlignVCenter);
    //    case Qt::DisplayRole:
    //        if (orientation == Qt::Horizontal)
    //            return "Измерение\r\n" + QString::number(section + 1);
    //        else
    //            return "      " + QString::number(section + 1);
    //    default:
    //        return QVariant();
    //    }
}

Qt::ItemFlags MyModel::flags(const QModelIndex& index) const {
    return enabled(index) ? Qt::ItemIsEnabled : Qt::NoItemFlags;
}

UsedMap MyModel::rowsEnabled() const {
    return m_rowsEnabled;
}
