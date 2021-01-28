#include "transmodel.h"
#include "magicgetruntime.h"

#include <QColor>
#include <QDebug>
#include <QFile>
#include <QFontMetrics>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaEnum>
#include <QRegExp>
#include <QTextCodec>
#include <variant>

void TransModel::save()
{
    QFile file("трансформаторы.json");
    if (file.open(QFile::WriteOnly)) {
        QJsonArray jArray;
        for (auto& trans : m_data) {
            QVariantMap varMap;
            for (index_t i = 0; i < pod_size_v<Trans>; ++i) {
                varMap[toColumKeyName(i)] = get_at(trans, i);
            }
            jArray << QJsonObject::fromVariantMap(varMap);
        }
        file.write(QJsonDocument(jArray).toJson());
    } else
        qDebug() << file.errorString();
}

void TransModel::load()
{
    QFile file("трансформаторы.json");
    if (file.open(QFile::ReadOnly)) {
        auto jArray(QJsonDocument::fromJson(file.readAll()).array());
        m_data.resize(jArray.size());
        for (auto& trans : m_data) {
            auto jObject(jArray.takeAt(0));
            for (index_t k = 0; k < pod_size_v<Trans>; ++k) {
                visit_at(trans, k, [jObject, k](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;
                    arg = jObject[toColumKeyName(k)].toVariant().value<T>();
                });
            }
        }
    } else
        qDebug() << file.errorString();
}

TransModel::TransModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    load();
}

TransModel::~TransModel()
{
    save();
}

int TransModel::rowCount(const QModelIndex&) const { return static_cast<int>(m_data.size()); }

int TransModel::columnCount(const QModelIndex&) const { return static_cast<int>(boost::pfr::tuple_size<Trans>::value); }

QVariant TransModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if /*  */ constexpr (1) { // 126.191 ms 99
            return get_at(m_data[index.row()], index.column());
        } else if constexpr (0) { // 133.285 ms 99
            if /*  */ (index.column() == No) {
                return m_data[index.row()].no;
            } else if (index.column() == Nkgzh) {
                return m_data[index.row()].nkgzh;
            } else if (index.column() == Marking) {
                return m_data[index.row()].marking;
            } else if (index.column() == Device) {
                return m_data[index.row()].device;
            } else if (index.column() == Housing) {
                return m_data[index.row()].housing;
            } else if (index.column() == TestVoltage) {
                return m_data[index.row()].testVoltage;
            } else if (index.column() == TestVoltageType) {
                return m_data[index.row()].testVoltageType;
            } else if (index.column() == ControlWindingPiNnumbers) {
                return m_data[index.row()].controlWindingPiNnumbers;
            } else if (index.column() == ControlWindingInductance) {
                return m_data[index.row()].controlWindingInductance;
            } else if (index.column() == RangeMin) {
                return m_data[index.row()].rangeMin;
            } else if (index.column() == RangeMax) {
                return m_data[index.row()].rangeMax;
            } else if (index.column() == ControlType) {
                return m_data[index.row()].controlType;
            }
        } else if constexpr (0) { // 170.744 ms 99
            switch (index.column()) {
            case No:
                return m_data[index.row()].no;
            case Nkgzh:
                return m_data[index.row()].nkgzh;
            case Marking:
                return m_data[index.row()].marking;
            case Device:
                return m_data[index.row()].device;
            case Housing:
                return m_data[index.row()].housing;
            case TestVoltage:
                return m_data[index.row()].testVoltage;
            case TestVoltageType:
                return m_data[index.row()].testVoltageType;
            case ControlWindingPiNnumbers:
                return m_data[index.row()].controlWindingPiNnumbers;
            case ControlWindingInductance:
                return m_data[index.row()].controlWindingInductance;
            case RangeMin:
                return m_data[index.row()].rangeMin;
            case RangeMax:
                return m_data[index.row()].rangeMax;
            case ControlType:
                return m_data[index.row()].controlType;
            }
        }
    } else if (role == Qt::TextAlignmentRole && index.column() != 1)
        return Qt::AlignCenter;
    else if (role == Qt::BackgroundColorRole
        && (index.column() == 5 || index.column() == 9 || index.column() == 10)
        && get_at(m_data[index.row()], index.column()) == 0)
        return QColor(255, 127, 127);
    else if (role == Trans::RangeMin)
        return m_data[index.row()].rangeMin;
    else if (role == Trans::RangeMax)
        return m_data[index.row()].rangeMax;
    return {};
}

bool TransModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole) {
        visit_at(m_data[index.row()], index.column(), [value](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            arg = value.value<T>();
        });
        return true;
    }
    return {};
}

Qt::ItemFlags TransModel::flags(const QModelIndex&) const { return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable; }

QVariant TransModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return headers[section];
    return QAbstractTableModel::headerData(section, orientation, role);
}

QString TransModel::toColumKeyName(int c) { return staticMetaObject.enumerator(2).valueToKey(c); }
