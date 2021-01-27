#pragma once

#include "boost/pfr.hpp"
#include <QDebug>
#include <QVariant>

//#define __AAA__
//#define __BBB__

#ifdef __AAA__

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
constexpr void visit_at(T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }
template <typename F, typename T>
constexpr void visit_at(const T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }

template <typename T>
constexpr auto get_at(T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }
template <typename T>
constexpr auto get_at(const T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }

#elif defined(__BBB__)

template <typename T>
inline constexpr size_t pod_size_v = boost::pfr::tuple_size<std::decay_t<T>>::value;

template <typename T, typename F, std::size_t... I>
void visit_impl(T& pod, const size_t idx, F fun, std::index_sequence<I...>)
{
    ((I == idx ? fun(boost::pfr::get<I>(pod)) : void()), ...);
}

template <typename T, std::size_t... I>
QVariant get_impl(T&& pod, const size_t idx, std::index_sequence<I...>)
{
    QVariant ret;
    return ((I == idx ? ret = boost::pfr::get<I>(pod) : ret), ..., ret);
}

template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(T& pod, const size_t idx, F fun) { visit_impl(pod, idx, fun, Indices {}); }
template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(const T& pod, const size_t idx, F fun) { visit_impl(pod, idx, fun, Indices {}); }

//template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
//constexpr auto get_at(T& pod, const size_t idx) { return get_impl(pod, idx, Indices {}); }
template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(const T& pod, const size_t idx) { return get_impl(pod, idx, Indices {}); }
#else

template <typename T>
inline constexpr size_t pod_size_v = boost::pfr::tuple_size<std::decay_t<T>>::value;

namespace detail {

template <std::size_t I>
class getter {
public:
    explicit getter() { }
    template <typename T>
    auto operator()(T&& pod) { return boost::pfr::get<I>(pod); }
};

template <typename T>
using function = std::function<QVariant(T)>;

template <typename T, size_t... Is>
struct array {
    static function<T> data[sizeof...(Is)];
};

template <typename T, size_t... Is>
function<T> array<T, Is...>::data[sizeof...(Is)] = { getter<Is>()... };

template <typename T, std::size_t... I>
QVariant get_impl(T&& pod, const size_t idx, std::index_sequence<I...>)
{
    return array<T, I...>::data[idx](pod);
}

template <typename T, typename F, std::size_t... I>
void visit_impl(T& pod, const size_t idx, F fun, std::index_sequence<I...>)
{
    ((I == idx ? fun(boost::pfr::get<I>(pod)) : void()), ...);
}
}

template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(T& pod, const size_t idx, F fun)
{
    detail::visit_impl(pod, idx, fun, Indices {});
}
template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(const T& pod, const size_t idx, F fun)
{
    detail::visit_impl(pod, idx, fun, Indices {});
}

template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(T&& pod, const size_t idx) { return detail::get_impl(pod, idx, Indices {}); }
template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(const T& pod, const size_t idx) { return detail::get_impl(pod, idx, Indices {}); }

#endif
