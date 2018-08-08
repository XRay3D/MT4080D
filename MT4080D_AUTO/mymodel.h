#ifndef MODEL_COEFFICIENTS_H
#define MODEL_COEFFICIENTS_H

#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MyModel(QObject* parent = nullptr);
    ~MyModel();
    void stateChanged(const QMap<int, bool>& enabled, int orientation);
    void setChData(double value, int row, int column);
    double getChData(int row, int column);
    inline bool enabled(int row, int column) const { return m_rowsEnabled[row] && m_columnsEnabled[column]; }
    inline bool enabled(const QModelIndex& index) const { return m_rowsEnabled[index.row()] && m_columnsEnabled[index.column()]; }
    QMap<int, bool> rowsEnabled() const;

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
        Columns = 4,
        Rows = 58,
    };

    double m_data[Columns][Rows];

    QMap<int, bool> m_rowsEnabled;
    QMap<int, bool> m_columnsEnabled;

    inline bool checkRow(int value) const { return -1 < value && value < Rows; }
    inline bool checkCol(int value) const { return -1 < value && value < Columns; }
};

#endif // MODEL_COEFFICIENTS_H
