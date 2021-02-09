#ifndef TRANSMODEL_H
#define TRANSMODEL_H

#include <QtCore/QAbstractTableModel>
#include <QtCore/qglobal.h>

struct Trans {
    int no; // №
    QString nkgzh; // НКГЖ. ...
    QString marking; // Маркировка
    QString device; // Прибор
    QString housing; // Корпус
    int testVoltage; // according to KD // Испытательное напряжение по КД
    QString testVoltageType; // according to KD // Испытательное напряжение по КД
    QString controlWindingPinNumbers; // Номера выводов контрольной обмотки
    QString controlWindingInductance; // μH // Индуктивность  контрольной обмотки, мкГн
    double rangeMin;
    double rangeMax; //, μH // ДИАПАЗОН, мкГн
    QString controlType; // Вид контроля
    enum MyRole {
        RangeMin = Qt::UserRole + 0,
        RangeMax = Qt::UserRole + 1,
        Pins = Qt::UserRole + 2,
    };
};

class TransModel : public QAbstractTableModel {
    Q_OBJECT

    std::vector<Trans> m_data;
    void save();
    void load();

public:
    explicit TransModel(QObject* parent = nullptr);
    ~TransModel();

public:
    // QAbstractItemModel interface
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    enum ColumKey {
        No,
        Nkgzh,
        Marking,
        Device,
        Housing,
        TestVoltage,
        TestVoltageType,
        ControlWindingPiNnumbers,
        ControlWindingInductance,
        RangeMin,
        RangeMax,
        ControlType,
    };
    Q_ENUM(ColumKey)
    static QString toColumKeyName(int c);

    static const inline QString headers[] = {
        "№",
        "НКГЖ",
        "Марки-\nровка",
        "Входит в\nсостав\nприбора",
        "Корпус",
        "Испытательное\nнапряжение по\nКД",
        "Род\nнапряжения",
        "Номера\nвыводов\nконтрольной\nобмотки",
        "Индуктивность\nконтрольной\nобмотки,\nмкГн",
        "Диапазон\nмин.,\nмкГн",
        "Диапазон\nмакс.,\nмкГн",
        "Вид\nконтроля",
    };
};

#endif // TRANSMODEL_H
