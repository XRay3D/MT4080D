#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

class Model : public QAbstractTableModel {
    Q_OBJECT
    QVector<double> m_data;
    const double& m_max;
    const double& m_min;

public:
    explicit Model(const double& min, const double& max, QObject* parent = nullptr);
    void addData(double data, bool _new = false);
    void clear();
    void copy();

signals:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool insertRows(int row, int count, const QModelIndex& parent) override;
};

#endif // MODEL_H
