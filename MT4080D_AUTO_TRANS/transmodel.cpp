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
            for (size_t i = 0; i < pod_size_v<Trans>; ++i) {
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
            for (size_t k = 0; k < pod_size_v<Trans>; ++k) {
                visit_at(trans, k, [jObject, k](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;
                    arg = jObject[toColumKeyName(k)].toVariant().value<T>();
                });
                if (0 && k == Marking) {
                    visit_at(trans, k, [](auto&& arg) {
                        using T = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<T, QString>) {
                            arg = arg.replace("T", "Т");
                            //                            QRegExp rx("(\\d),.*(\\d)");
                            //                            if (rx.exactMatch(arg)) {
                            //                                bool ok;
                            //                                if (int a = rx.cap(1).toInt(&ok); ok)
                            //                                    if (int b = rx.cap(2).toInt(&ok); ok && abs(a - b) == 1) {
                            //                                        qDebug() << rx.capturedTexts();
                            //                                        arg = std::min(rx.cap(1), rx.cap(2)) + " – " + std::max(rx.cap(1), rx.cap(2));
                            //                                        qDebug() << arg;
                            //                                    }
                            //                            }
                        }
                    });
                }
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

TransModel::~TransModel() { save(); }

int TransModel::rowCount(const QModelIndex&) const { return static_cast<int>(m_data.size()); }

int TransModel::columnCount(const QModelIndex&) const { return static_cast<int>(boost::pfr::tuple_size<Trans>::value); }

QVariant TransModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return get_at(m_data[index.row()], index.column());
    else if (role == Qt::TextAlignmentRole && index.column() != 1)
        return Qt::AlignCenter;
    else if (role == Qt::BackgroundColorRole
        && (index.column() == 5 || index.column() == 9 || index.column() == 10)
        && get_at(m_data[index.row()], index.column()) == 0)
        return QColor(255, 127, 127);
    else if (role == Qt::UserRole + 0)
        return get_at(m_data[index.row()], 9);
    else if (role == Qt::UserRole + 1)
        return get_at(m_data[index.row()], 10);
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
