// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_OPS_HPP
#define BOOST_PFR_OPS_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/detail/detectors.hpp>
#include <boost/pfr/ops_fields.hpp>

/// \file boost/pfr/ops.hpp
/// Contains comparison and hashing functions.
/// If type is comparable using its own operator or its conversion operator, then the types operator is used. Otherwise
/// the operation is done via corresponding function from boost/pfr/ops.hpp header.
///
/// \b Example:
/// \code
///     #include <boost/pfr/ops.hpp>
///     struct comparable_struct {      // No operators defined for that structure
///         int i; short s; char data[7]; bool bl; int a,b,c,d,e,f;
///     };
///     // ...
///
///     comparable_struct s1 {0, 1, "Hello", false, 6,7,8,9,10,11};
///     comparable_struct s2 {0, 1, "Hello", false, 6,7,8,9,10,11111};
///     assert(boost::pfr::lt(s1, s2));
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Synopsis:
namespace boost { namespace pfr {

namespace detail {

///////////////////// Helper typedefs that are used by all the ops
    template <template <class, class> class Detector, class T, class U>
    using enable_not_comp_base_t = std::enable_if_t<
        not_appliable<Detector, T const&, U const&>::value,
        bool
    >;

    template <template <class, class> class Detector, class T, class U>
    using enable_comp_base_t = std::enable_if_t<
        !not_appliable<Detector, T const&, U const&>::value,
        bool
    >;
///////////////////// std::enable_if_t like functions that enable only if types do not support operation

    template <class T, class U> using enable_not_eq_comp_t = enable_not_comp_base_t<comp_eq_detector, T, U>;
    template <class T, class U> using enable_not_ne_comp_t = enable_not_comp_base_t<comp_ne_detector, T, U>;
    template <class T, class U> using enable_not_lt_comp_t = enable_not_comp_base_t<comp_lt_detector, T, U>;
    template <class T, class U> using enable_not_le_comp_t = enable_not_comp_base_t<comp_le_detector, T, U>;
    template <class T, class U> using enable_not_gt_comp_t = enable_not_comp_base_t<comp_gt_detector, T, U>;
    template <class T, class U> using enable_not_ge_comp_t = enable_not_comp_base_t<comp_ge_detector, T, U>;

    template <class T> using enable_not_hashable_t = std::enable_if_t<
        not_appliable<hash_detector, const T&, const T&>::value,
        std::size_t
    >;
///////////////////// std::enable_if_t like functions that enable only if types do support operation

    template <class T, class U> using enable_eq_comp_t = enable_comp_base_t<comp_eq_detector, T, U>;
    template <class T, class U> using enable_ne_comp_t = enable_comp_base_t<comp_ne_detector, T, U>;
    template <class T, class U> using enable_lt_comp_t = enable_comp_base_t<comp_lt_detector, T, U>;
    template <class T, class U> using enable_le_comp_t = enable_comp_base_t<comp_le_detector, T, U>;
    template <class T, class U> using enable_gt_comp_t = enable_comp_base_t<comp_gt_detector, T, U>;
    template <class T, class U> using enable_ge_comp_t = enable_comp_base_t<comp_ge_detector, T, U>;

    template <class T> using enable_hashable_t = std::enable_if_t<
        !not_appliable<hash_detector, const T&, const T&>::value,
        std::size_t
    >;
} // namespace detail


/// \brief Compares lhs and rhs for equality using their own comparison and conversion operators; if no operators avalable returns \forcedlink{eq_fields}(lhs, rhs).
///
/// \returns true if lhs is equal to rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_eq_comp_t<T, U> eq(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::eq_fields(lhs, rhs);
}

/// \overload eq
template <class T, class U>
constexpr detail::enable_eq_comp_t<T, U> eq(const T& lhs, const U& rhs) {
    return lhs == rhs;
}


/// \brief Compares lhs and rhs for inequality using their own comparison and conversion operators; if no operators avalable returns \forcedlink{ne_fields}(lhs, rhs).
///
/// \returns true if lhs is not equal to rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_ne_comp_t<T, U> ne(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::ne_fields(lhs, rhs);
}

/// \overload ne
template <class T, class U>
constexpr detail::enable_ne_comp_t<T, U> ne(const T& lhs, const U& rhs) {
    return lhs != rhs;
}


/// \brief Compares lhs and rhs for less-than using their own comparison and conversion operators; if no operators avalable returns \forcedlink{lt_fields}(lhs, rhs).
///
/// \returns true if lhs is less than rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_lt_comp_t<T, U> lt(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::lt_fields(lhs, rhs);
}

/// \overload lt
template <class T, class U>
constexpr detail::enable_lt_comp_t<T, U> lt(const T& lhs, const U& rhs) {
    return lhs < rhs;
}


/// \brief Compares lhs and rhs for greater-than using their own comparison and conversion operators; if no operators avalable returns \forcedlink{lt_fields}(lhs, rhs).
///
/// \returns true if lhs is greater than rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_gt_comp_t<T, U> gt(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::gt_fields(lhs, rhs);
}

/// \overload gt
template <class T, class U>
constexpr detail::enable_gt_comp_t<T, U> gt(const T& lhs, const U& rhs) {
    return lhs > rhs;
}


/// \brief Compares lhs and rhs for less-equal using their own comparison and conversion operators; if no operators avalable returns \forcedlink{le_fields}(lhs, rhs).
///
/// \returns true if lhs is less or equal to rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_le_comp_t<T, U> le(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::le_fields(lhs, rhs);
}

/// \overload le
template <class T, class U>
constexpr detail::enable_le_comp_t<T, U> le(const T& lhs, const U& rhs) {
    return lhs <= rhs;
}


/// \brief Compares lhs and rhs for greater-equal using their own comparison and conversion operators; if no operators avalable returns \forcedlink{ge_fields}(lhs, rhs).
///
/// \returns true if lhs is greater or equal to rhs; false otherwise
template <class T, class U>
constexpr detail::enable_not_ge_comp_t<T, U> ge(const T& lhs, const U& rhs) noexcept {
    return boost::pfr::ge_fields(lhs, rhs);
}

/// \overload ge
template <class T, class U>
constexpr detail::enable_ge_comp_t<T, U> ge(const T& lhs, const U& rhs) {
    return lhs >= rhs;
}


/// \brief Hashes value using its own std::hash specialization; if no std::hash specialization avalable returns \forcedlink{hash_fields}(value).
///
/// \returns std::size_t with hash of the value
template <class T>
constexpr detail::enable_not_hashable_t<T> hash_value(const T& value) noexcept {
    return boost::pfr::hash_fields(value);
}

/// \overload hash_value
template <class T>
constexpr detail::enable_hashable_t<T> hash_value(const T& value) {
    return std::hash<T>{}(value);
}

}} // namespace boost::pfr

#endif // BOOST_PFR_OPS_HPP

/* ops.hpp
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
*/