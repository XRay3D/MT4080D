#include "model.h"

#include <QApplication>
#include <QClipboard>
#include <QColor>

Model::Model(const double& min, const double& max, QObject* parent)
    : QAbstractTableModel(parent)
    , m_max(max)
    , m_min(min)
{
}

void Model::addData(double data, bool _new)
{
    if (_new)
        insertRow(m_data.size());
    else
        m_data.last() = data;
    dataChanged(createIndex(m_data.size() - 1, 0), createIndex(m_data.size() - 1, 0));
}

void Model::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_data.size() - 1);
    m_data.clear();
    endRemoveRows();
}

void Model::copy()
{
    if (m_data.count()) {
        QString str;
        for (int row = 0; row < m_data.count(); ++row) {
            str.append(data(createIndex(row, 0), Qt::DisplayRole).toString().replace('.', ','));
            str.append("\r\n");
        }
        QApplication::clipboard()->setText(str);
    }
}

int Model::rowCount(const QModelIndex& /*parent*/) const
{
    return m_data.size();
}

int Model::columnCount(const QModelIndex& /*parent*/) const
{
    return 1;
}

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

bool Model::insertRows(int position, int rows, const QModelIndex& /*int row, int count, const QModelIndex& parent*/)
{
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        m_data.append(0.0);
    endInsertRows();
    return true;
}
