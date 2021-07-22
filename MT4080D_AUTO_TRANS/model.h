#ifndef MODEL_H
#define MODEL_H

#include <QAbstractTableModel>

class Model : public QAbstractTableModel {
    Q_OBJECT
    std::vector<double> m_data;
    const double& m_max;
    const double& m_min;

    void save();
    void load();

public:
    explicit Model(const double& min, const double& max, QObject* parent = nullptr);
    ~Model() override;
    void addData(double data);
    void setLastData(double data);
    void clear();
    void copy();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex& = {}) const override;
    int columnCount(const QModelIndex& = {}) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool insertRows(int row, int count, const QModelIndex& parent) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // MODEL_H
