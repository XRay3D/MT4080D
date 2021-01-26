#include "transmodel.h"
#include "boost/pfr.hpp"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextCodec>
#include <variant>

//template <size_t I>
//struct visit_impl {
// template <typename T>
// static decltype(auto) visit(T&& pod, size_t idx)
// {
// (idx == I - 1) ? boost::pfr::get<I - 1>(pod)
// : visit_impl<I - 1>::visit(pod, idx);
// }
//};

//template <>
//struct visit_impl<0> {
// template <typename T>
// static decltype(auto) visit(T& /*pod*/, size_t /*idx*/) { assert(false); }
// template <typename T, typename F>
// static decltype(auto) visit(T& /*pod*/, size_t /*idx*/, F /*fun*/) { assert(false); }
//};

//template <typename T>
//decltype(auto) visit_at(const T& pod, size_t idx) { return visit_impl<pod_size_v<T>>::visit(pod, idx); }
//template <typename T>
//decltype(auto) visit_at(T&& pod, size_t idx) { return visit_impl<pod_size_v<T>>::visit(std::move(pod), idx); }

template <typename T>
inline constexpr size_t pod_size_v = boost::pfr::tuple_size<std::decay_t<T>>::value;

template <size_t I>
struct get_visit_impl {
    template <typename T, typename F>
    constexpr static void visit(T& pod, const size_t idx, F fun)
    {
        (idx == I - 1) ? fun(boost::pfr::get<I - 1>(pod))
                       : get_visit_impl<I - 1>::visit(pod, idx, fun);
    }
    template <typename T>
    constexpr static auto get(T& pod, const size_t idx)
    {
        return (idx == I - 1) ? boost::pfr::get<I - 1>(pod)
                              : get_visit_impl<I - 1>::get(pod, idx);
    }
};

template <>
struct get_visit_impl<0> {
    // clang-format off
    template <typename T, typename F>
    static void visit(T&, size_t, F) { assert(false); }
    template <typename T>
    static QVariant get(T&, size_t) { assert(false); return {}; }
    // clang-format on
};

template <typename F, typename T>
void visit_at(T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }
template <typename F, typename T>
void visit_at(const T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }

template <typename T>
auto get_at(T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }
template <typename T>
auto get_at(const T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }

TransModel::TransModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    QFile file("data.txt");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString line;
        QStringList list;
        QTextStream ts(&file);
        ts.setCodec(QTextCodec::codecForName("UTF-8"));
        while (ts.readLineInto(&line))
            list << line;
        m_data.resize(list.size());
        for (size_t i = 0; i < m_data.size(); ++i) {
            auto& trans = m_data[i];
            int ctr = 0;
            for (auto&& str : list[i].split('\t')) {
                visit_at(trans, ctr++, [str, &line](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;
                    bool ok = true;
                    if constexpr /**/ (std::is_same_v<T, int>) {
                        arg = str.toInt(&ok);
                        arg = ok ? (line.clear(), arg) : (line = str, -999);
                    } else if constexpr (std::is_same_v<T, double>) {
                        arg = str.toDouble(&ok);
                        arg = ok ? (line.clear(), arg) : (line = str, -999);
                    } else if constexpr (std::is_same_v<T, QString>)
                        arg = str.isEmpty() ? line : str;
                    if (!ok)
                        qDebug() << str;
                });
            }
        }
    } else
        qDebug() << file.errorString();
}

TransModel::~TransModel()
{
    QFile file("data2.txt");
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QJsonObject jObject;
        QJsonArray jArray;
        for (auto& trans : m_data) {
            for (size_t i = 0; i < pod_size_v<Trans>; ++i) {
                visit_at(trans, i, [&jObject, &i](auto&& arg) { jObject[hd[i]] = arg; });
            }
            jArray << jObject;
        }
        file.write(QJsonDocument(jArray).toJson());
        //        QString line;
        //        QStringList list;
        //        QTextStream ts(&file);
        //        ts.setCodec(QTextCodec::codecForName("UTF-8"));
        //        for (auto& trans : m_data) {
        //            for (size_t i = 0; i < pod_size_v<Trans>; ++i) {
        //                if (i)
        //                    ts << '\t';
        //                visit_at(trans, i, [&ts](auto&& arg) { ts << arg; });
        //            }
        //            ts << '\n';
        //        }
    } else
        qDebug() << file.errorString();
}

int TransModel::rowCount(const QModelIndex&) const { return static_cast<int>(m_data.size()); }

int TransModel::columnCount(const QModelIndex&) const { return static_cast<int>(boost::pfr::tuple_size<Trans>::value); }

QVariant TransModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return get_at(m_data[index.row()], index.column());
    else if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    return {};
}

bool TransModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::EditRole) {
        visit_at(m_data[index.row()], index.column(), [value](auto&& arg) { arg = value.value<std::decay_t<decltype(arg)>>(); });
        return true;
    }
    return {};
}

Qt::ItemFlags TransModel::flags(const QModelIndex&) const { return Qt::ItemIsEditable | Qt::ItemIsEnabled; }
