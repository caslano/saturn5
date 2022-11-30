// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_SEQUENCE_TUPLE_HPP
#define BOOST_PFR_DETAIL_SEQUENCE_TUPLE_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>

#include <utility>      // metaprogramming stuff
#include <cstddef>      // std::size_t

///////////////////// Tuple that holds its values in the supplied order
namespace boost { namespace pfr { namespace detail { namespace sequence_tuple {

template <std::size_t N, class T>
struct base_from_member {
    T value;
};

template <class I, class ...Tail>
struct tuple_base;



template <std::size_t... I, class ...Tail>
struct tuple_base< std::index_sequence<I...>, Tail... >
    : base_from_member<I , Tail>...
{
    static constexpr std::size_t size_v = sizeof...(I);

    // We do not use `noexcept` in the following functions, because if user forget to put one then clang will issue an error:
    // "error: exception specification of explicitly defaulted default constructor does not match the calculated one".
    constexpr tuple_base() = default;
    constexpr tuple_base(tuple_base&&) = default;
    constexpr tuple_base(const tuple_base&) = default;

    constexpr tuple_base(Tail... v) noexcept
        : base_from_member<I, Tail>{ v }...
    {}
};

template <>
struct tuple_base<std::index_sequence<> > {
    static constexpr std::size_t size_v = 0;
};

template <std::size_t N, class T>
constexpr T& get_impl(base_from_member<N, T>& t) noexcept {
    return t.value;
}

template <std::size_t N, class T>
constexpr const T& get_impl(const base_from_member<N, T>& t) noexcept {
    return t.value;
}

template <std::size_t N, class T>
constexpr volatile T& get_impl(volatile base_from_member<N, T>& t) noexcept {
    return t.value;
}

template <std::size_t N, class T>
constexpr const volatile T& get_impl(const volatile base_from_member<N, T>& t) noexcept {
    return t.value;
}

template <std::size_t N, class T>
constexpr T&& get_impl(base_from_member<N, T>&& t) noexcept {
    return std::forward<T>(t.value);
}


template <class ...Values>
struct tuple: tuple_base<
    detail::index_sequence_for<Values...>,
    Values...>
{
    using tuple_base<
        detail::index_sequence_for<Values...>,
        Values...
    >::tuple_base;
};


template <std::size_t N, class ...T>
constexpr decltype(auto) get(tuple<T...>& t) noexcept {
    static_assert(N < tuple<T...>::size_v, "====================> Boost.PFR: Tuple index out of bounds");
    return sequence_tuple::get_impl<N>(t);
}

template <std::size_t N, class ...T>
constexpr decltype(auto) get(const tuple<T...>& t) noexcept {
    static_assert(N < tuple<T...>::size_v, "====================> Boost.PFR: Tuple index out of bounds");
    return sequence_tuple::get_impl<N>(t);
}

template <std::size_t N, class ...T>
constexpr decltype(auto) get(const volatile tuple<T...>& t) noexcept {
    static_assert(N < tuple<T...>::size_v, "====================> Boost.PFR: Tuple index out of bounds");
    return sequence_tuple::get_impl<N>(t);
}

template <std::size_t N, class ...T>
constexpr decltype(auto) get(volatile tuple<T...>& t) noexcept {
    static_assert(N < tuple<T...>::size_v, "====================> Boost.PFR: Tuple index out of bounds");
    return sequence_tuple::get_impl<N>(t);
}

template <std::size_t N, class ...T>
constexpr decltype(auto) get(tuple<T...>&& t) noexcept {
    static_assert(N < tuple<T...>::size_v, "====================> Boost.PFR: Tuple index out of bounds");
    return sequence_tuple::get_impl<N>(std::move(t));
}

template <std::size_t I, class T>
using tuple_element = std::remove_reference< decltype(
        ::boost::pfr::detail::sequence_tuple::get<I>( std::declval<T>() )
    ) >;


}}}} // namespace boost::pfr::detail::sequence_tuple

#endif // BOOST_PFR_CORE_HPP

/* sequence_tuple.hpp
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
*/