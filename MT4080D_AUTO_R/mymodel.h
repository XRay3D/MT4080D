#ifndef MODEL_COEFFICIENTS_H
#define MODEL_COEFFICIENTS_H

#include <QAbstractTableModel>

using UsedMap = std::map<int, bool>;

class MyModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MyModel(QObject* parent = nullptr);
    ~MyModel();
    void stateChanged(const UsedMap& enabled, int orientation);
    void setChData(double value, int row, int column);
    double getChData(int row, int column);
    inline bool enabled(int row, int column) const {
        if(m_rowsEnabled.contains(row) && m_columnsEnabled.contains(column))
            return m_rowsEnabled.at(row) && m_columnsEnabled.at(column);
        return false;
    }
    inline bool enabled(const QModelIndex& index) const {
        if(m_rowsEnabled.contains(index.row()) && m_columnsEnabled.contains(index.column()))
            return m_rowsEnabled.at(index.row()) && m_columnsEnabled.at(index.column());
        return false;
    }
    UsedMap rowsEnabled() const;

signals:

public slots:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    enum {
        Columns = 6,
        Rows = 58,
    };

    double m_data[Columns][Rows] {};

    UsedMap m_rowsEnabled;
    UsedMap m_columnsEnabled;

    inline bool checkRow(int value) const { return -1 < value && value < Rows; }
    inline bool checkCol(int value) const { return -1 < value && value < Columns; }
};

#endif // MODEL_COEFFICIENTS_H
