// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_CORE_HPP
#define BOOST_PFR_CORE_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/detail/core.hpp>

#include <boost/pfr/detail/sequence_tuple.hpp>
#include <boost/pfr/detail/stdtuple.hpp>
#include <boost/pfr/detail/for_each_field_impl.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>
#include <boost/pfr/detail/tie_from_structure_tuple.hpp>

#include <type_traits>
#include <utility>      // metaprogramming stuff

#include <boost/pfr/tuple_size.hpp>

/// \file boost/pfr/core.hpp
/// Contains all the basic tuple-like interfaces \forcedlink{get}, \forcedlink{tuple_size}, \forcedlink{tuple_element_t}, and others.
///
/// \b Synopsis:

namespace boost { namespace pfr {

/// \brief Returns reference or const reference to a field with index `I` in \aggregate `val`.
///
/// \b Example:
/// \code
///     struct my_struct { int i, short s; };
///     my_struct s {10, 11};
///     assert(boost::pfr::get<0>(s) == 10);
///     boost::pfr::get<1>(s) = 0;
/// \endcode
template <std::size_t I, class T>
constexpr decltype(auto) get(const T& val) noexcept {
    return detail::sequence_tuple::get<I>( detail::tie_as_tuple(val) );
}


/// \overload get
template <std::size_t I, class T>
constexpr decltype(auto) get(T& val
#if !BOOST_PFR_USE_CPP17
    , std::enable_if_t<std::is_assignable<T, T>::value>* = nullptr
#endif
) noexcept {
    return detail::sequence_tuple::get<I>( detail::tie_as_tuple(val) );
}

#if !BOOST_PFR_USE_CPP17
/// \overload get
template <std::size_t I, class T>
constexpr auto get(T&, std::enable_if_t<!std::is_assignable<T, T>::value>* = nullptr) noexcept {
    static_assert(sizeof(T) && false, "====================> Boost.PFR: Calling boost::pfr::get on non const non assignable type is allowed only in C++17");
    return 0;
}
#endif


/// \overload get
template <std::size_t I, class T>
constexpr auto get(T&& val, std::enable_if_t< std::is_rvalue_reference<T&&>::value>* = 0) noexcept {
    return std::move(detail::sequence_tuple::get<I>( detail::tie_as_tuple(val) ));
}


/// \brief `tuple_element` has a member typedef `type` that returns the type of a field with index I in \aggregate T.
///
/// \b Example:
/// \code
///     std::vector< boost::pfr::tuple_element<0, my_structure>::type > v;
/// \endcode
template <std::size_t I, class T>
using tuple_element = detail::sequence_tuple::tuple_element<I, decltype( ::boost::pfr::detail::tie_as_tuple(std::declval<T&>()) ) >;


/// \brief Type of a field with index `I` in \aggregate `T`.
///
/// \b Example:
/// \code
///     std::vector< boost::pfr::tuple_element_t<0, my_structure> > v;
/// \endcode
template <std::size_t I, class T>
using tuple_element_t = typename tuple_element<I, T>::type;


/// \brief Creates a `std::tuple` from fields of an \aggregate `val`.
///
/// \b Example:
/// \code
///     struct my_struct { int i, short s; };
///     my_struct s {10, 11};
///     std::tuple<int, short> t = make_tuple(s);
///     assert(get<0>(t) == 10);
/// \endcode
template <class T>
constexpr auto structure_to_tuple(const T& val) noexcept {
    return detail::make_stdtuple_from_tietuple(
        detail::tie_as_tuple(val),
        detail::make_index_sequence< tuple_size_v<T> >()
    );
}


/// \brief std::tie` like function that ties fields of a structure.
///
/// \returns a `std::tuple` with lvalue and const lvalue references to fields of an \aggregate `val`.
///
/// \b Example:
/// \code
///     void foo(const int&, const short&);
///     struct my_struct { int i, short s; };
///
///     const my_struct const_s{1, 2};
///     std::apply(foo, structure_tie(const_s));
///
///     my_struct s;
///     structure_tie(s) = std::tuple<int, short>{10, 11};
///     assert(s.s == 11);
/// \endcode
template <class T>
constexpr auto structure_tie(const T& val) noexcept {
    return detail::make_conststdtiedtuple_from_tietuple(
        detail::tie_as_tuple(const_cast<T&>(val)),
        detail::make_index_sequence< tuple_size_v<T> >()
    );
}


/// \overload structure_tie
template <class T>
constexpr auto structure_tie(T& val
#if !BOOST_PFR_USE_CPP17
    , std::enable_if_t<std::is_assignable<T, T>::value>* = nullptr
#endif
) noexcept {
    return detail::make_stdtiedtuple_from_tietuple(
        detail::tie_as_tuple(val),
        detail::make_index_sequence< tuple_size_v<T> >()
    );
}

#if !BOOST_PFR_USE_CPP17
/// \overload structure_tie
template <class T>
constexpr auto structure_tie(T&, std::enable_if_t<!std::is_assignable<T, T>::value>* = nullptr) noexcept {
    static_assert(sizeof(T) && false, "====================> Boost.PFR: Calling boost::pfr::structure_tie on non const non assignable type is allowed only in C++17");
    return 0;
}
#endif


/// \overload structure_tie
template <class T>
constexpr auto structure_tie(T&&, std::enable_if_t< std::is_rvalue_reference<T&&>::value>* = 0) noexcept {
    static_assert(sizeof(T) && false, "====================> Boost.PFR: Calling boost::pfr::structure_tie on rvalue references is forbidden");
    return 0;
}

/// Calls `func` for each field of a `value`.
///
/// \param func must have one of the following signatures:
///     * any_return_type func(U&& field)                // field of value is perfect forwarded to function
///     * any_return_type func(U&& field, std::size_t i)
///     * any_return_type func(U&& value, I i)           // Here I is an `std::integral_constant<size_t, field_index>`
///
/// \param value To each field of this variable will be the `func` applied.
///
/// \b Example:
/// \code
///     struct my_struct { int i, short s; };
///     int sum = 0;
///     for_each_field(my_struct{20, 22}, [&sum](const auto& field) { sum += field; });
///     assert(sum == 42);
/// \endcode
template <class T, class F>
void for_each_field(T&& value, F&& func) {
    constexpr std::size_t fields_count_val = boost::pfr::detail::fields_count<std::remove_reference_t<T>>();

    ::boost::pfr::detail::for_each_field_dispatcher(
        value,
        [f = std::forward<F>(func)](auto&& t) mutable {
            // MSVC related workaround. Its lambdas do not capture constexprs.
            constexpr std::size_t fields_count_val_in_lambda
                = boost::pfr::detail::fields_count<std::remove_reference_t<T>>();

            ::boost::pfr::detail::for_each_field_impl(
                t,
                std::forward<F>(f),
                detail::make_index_sequence<fields_count_val_in_lambda>{},
                std::is_rvalue_reference<T&&>{}
            );
        },
        detail::make_index_sequence<fields_count_val>{}
    );
}

/// \brief std::tie-like function that allows assigning to tied values from aggregates.
///
/// \returns an object with lvalue references to `args...`; on assignment of an \aggregate value to that
/// object each field of an aggregate is assigned to the corresponding `args...` reference.
///
/// \b Example:
/// \code
///     auto f() {
///       struct { struct { int x, y } p; short s; } res { { 4, 5 }, 6 };
///       return res;
///     }
///     auto [p, s] = f();
///     tie_from_structure(p, s) = f();
/// \endcode
template <typename... Elements>
constexpr detail::tie_from_structure_tuple<Elements...> tie_from_structure(Elements&... args) noexcept {
    return detail::tie_from_structure_tuple<Elements...>(args...);
}

}} // namespace boost::pfr

#endif // BOOST_PFR_CORE_HPP

/* core.hpp
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
*/