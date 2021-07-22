#include "model.h"

#include <QApplication>
#include <QClipboard>
#include <QColor>
#include <QDataStream>
#include <QFile>

void Model::save()
{
    QFile file("data.bin");
    if (file.open(QFile::WriteOnly)) {
        QDataStream stream(&file);
        stream << m_data.size();
        for (auto val : m_data)
            stream << val;
    }
}

void Model::load()
{
    QFile file("data.bin");
    if (file.open(QFile::ReadOnly)) {
        QDataStream stream(&file);
        size_t size {};
        stream >> size;
        m_data.resize(size);
        for (auto& val : m_data)
            stream >> val;
    }
}

Model::Model(const double& min, const double& max, QObject* parent)
    : QAbstractTableModel(parent)
    , m_max(max)
    , m_min(min) //
{
    load();
}

Model::~Model()
{
    save();
}

void Model::addData(double data)
{
    insertRow(m_data.size());
    setLastData(data);
}

void Model::setLastData(double data)
{
    m_data.back() = data;
    save();
    emit dataChanged(createIndex(m_data.size() - 1, 0), createIndex(m_data.size() - 1, 0), { Qt::DisplayRole });
}

void Model::clear()
{
    if (!m_data.size())
        return;
    beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
    m_data.clear();
    endRemoveRows();
}

void Model::copy()
{
    if (!m_data.size())
        return;
    QString str;
    for (auto&& val : m_data)
        str.append(QVariant(val).toString().replace('.', ',').append("\r\n"));
    QApplication::clipboard()->setText(str);
}

int Model::rowCount(const QModelIndex& /*parent*/) const { return m_data.size(); }

int Model::columnCount(const QModelIndex& /*parent*/) const { return 1; }

QVariant Model::data(const QModelIndex& index, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return m_data[index.row()];
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    case Qt::BackgroundColorRole:
        if (auto val = m_data[index.row()]; m_max > val && val > m_min)
            return QColor(128, 255, 128);
        else
            return QColor(255, 128, 128);
    }
    return {};
}

bool Model::insertRows(int position, int rows, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_data.push_back(0.0);

    endInsertRows();

    return true;
}

QVariant Model::headerData(int section, Qt::Orientation /*orientation*/, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        return ++section;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
    }
    return {};
}
