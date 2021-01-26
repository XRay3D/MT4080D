#include "transmodel.h"
#include "boost/pfr.hpp"

template <size_t I>
struct visit_impl {
    template <typename T>
    static decltype(auto) visit(T& tup, size_t idx)
    {
        if (idx == I - 1)
            return boost::pfr::get<I - 1>(tup);
        else
            return visit_impl<I - 1>::visit(tup, idx);
    }
};

template <>
struct visit_impl<0> {
    template <typename T, typename F>
    static decltype(auto) visit(T& /*tup*/, size_t /*idx*/, F /*fun*/)
    {
        assert(false);
        return 0;
    }
};

template <typename T>
decltype(auto) visit_at(T const& tup, size_t idx)
{
    return visit_impl<boost::pfr::tuple_size<T>::value>::visit(tup, idx);
}

//template <typename F, typename... Ts>
//decltype(auto) visit_at(std::tuple<Ts...>& tup, size_t idx, F fun)
//{
//    return visit_impl<sizeof...(Ts)>::visit(tup, idx, fun);
//}

TransModel::TransModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int TransModel::rowCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(m_data.size());
}

int TransModel::columnCount(const QModelIndex& /*parent*/) const
{
    return static_cast<int>(boost::pfr::tuple_size<Trans>::value);
}

QVariant TransModel::data(const QModelIndex& index, int role) const
{
    boost::pfr::get<1>(index);
    if (role == Qt::DisplayRole) {
        return visit_at(m_data[index.row()], index.column());
    }
    return {};
}
