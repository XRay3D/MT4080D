#ifndef TRANSMODEL_H
#define TRANSMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/qglobal.h>

struct Trans {
    int no; // №
    QString nkgzh; // НКГЖ. ...
    QString marking; // Марки-ровка
    QString device; // Прибор
    QString housing; // Корпус
    int testVoltage; // according to KD // Испытательное напряжение по КД
    QString testVoltageType; // according to KD // Испытательное напряжение по КД
    QString controlWindingPiNnumbers; // Номера выводов контрольной обмотки
    QString controlWindingInductance; // μH // Индуктивность  контрольной обмотки, мкГн
    double rangeMin;
    double rangeMax; //, μH // ДИАПАЗОН, мкГн
    QString controlType; // Вид контроля
};

class TransModel : public QAbstractTableModel {
    Q_OBJECT

    std::vector<Trans> m_data;

public:
    explicit TransModel(QObject* parent = nullptr);
    ~TransModel();
signals:

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    static inline QString hd[] = {
        "no",
        "nkgzh",
        "marking",
        "device",
        "housing",
        "testVoltage",
        "testVoltageType",
        "controlWindingPiNnumbers",
        "controlWindingInductance",
        "rangeMin",
        "rangeMax",
        "controlType",
    };
};

#endif // TRANSMODEL_H
