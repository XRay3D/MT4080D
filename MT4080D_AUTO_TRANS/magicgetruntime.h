#pragma once

#include "boost/pfr.hpp"
#include <QDebug>
#include <QVariant>

#ifdef __ASD__

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

#else

template <typename T>
inline constexpr size_t pod_size_v = boost::pfr::tuple_size<std::decay_t<T>>::value;

template <size_t I>
struct get_visit_impl {
    template <typename T, typename F>
    constexpr static void visit(T& pod, const size_t idx, F fun)
    {
        (idx == I) ? fun(boost::pfr::get<I>(pod))
                   : get_visit_impl<I - 1>::visit(pod, idx, fun);
    }
    template <typename T>
    constexpr static auto get(T& pod, const size_t idx)
    {
        return (idx == I) ? boost::pfr::get<I>(pod)
                          : get_visit_impl<I - 1>::get(pod, idx);
    }
};

template <>
struct get_visit_impl<0> {
    template <typename T, typename F>
    constexpr static void visit(T& pod, const size_t idx, F fun)
    {
        assert(idx == 0);
        fun(boost::pfr::get<0>(pod));
    }
    template <typename T>
    constexpr static QVariant get(T& pod, const size_t idx)
    {
        assert(idx == 0);
        return boost::pfr::get<0>(pod);
    }
};

template <typename F, typename T>
constexpr void visit_at(T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T> - 1>::visit(pod, idx, fun); }
template <typename F, typename T>
constexpr void visit_at(const T& pod, const size_t idx, F fun) { get_visit_impl<pod_size_v<T> - 1>::visit(pod, idx, fun); }

template <typename T>
constexpr auto get_at(T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T> - 1>::get(pod, idx); }
template <typename T>
constexpr auto get_at(const T& pod, const size_t idx) { return get_visit_impl<pod_size_v<T> - 1>::get(pod, idx); }

#endif
