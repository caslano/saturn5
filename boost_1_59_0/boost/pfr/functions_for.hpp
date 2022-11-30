// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_FUNCTIONS_FOR_HPP
#define BOOST_PFR_FUNCTIONS_FOR_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/ops_fields.hpp>
#include <boost/pfr/io_fields.hpp>

/// \file boost/pfr/functions_for.hpp
/// Contains BOOST_PFR_FUNCTIONS_FOR macro that defined comparison and stream operators for T along with hash_value function.
/// \b Example:
/// \code
///     #include <boost/pfr/functions_for.hpp>
///
///     namespace my_namespace {
///         struct my_struct {      // No operators defined for that structure
///             int i; short s; char data[7]; bool bl; int a,b,c,d,e,f;
///         };
///         BOOST_PFR_FUNCTIONS_FOR(my_struct)
///     }
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Synopsis:

/// \def BOOST_PFR_FUNCTIONS_FOR(T)
/// Defines comparison and stream operators for T along with hash_value function.
///
/// \b Example:
/// \code
///     #include <boost/pfr/functions_for.hpp>
///     struct comparable_struct {      // No operators defined for that structure
///         int i; short s; char data[7]; bool bl; int a,b,c,d,e,f;
///     };
///     BOOST_PFR_FUNCTIONS_FOR(comparable_struct)
///     // ...
///
///     comparable_struct s1 {0, 1, "Hello", false, 6,7,8,9,10,11};
///     comparable_struct s2 {0, 1, "Hello", false, 6,7,8,9,10,11111};
///     assert(s1 < s2);
///     std::cout << s1 << std::endl; // Outputs: {0, 1, H, e, l, l, o, , , 0, 6, 7, 8, 9, 10, 11}
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Defines \b following \b for \b T:
/// \code
/// bool operator==(const T& lhs, const T& rhs);
/// bool operator!=(const T& lhs, const T& rhs);
/// bool operator< (const T& lhs, const T& rhs);
/// bool operator> (const T& lhs, const T& rhs);
/// bool operator<=(const T& lhs, const T& rhs);
/// bool operator>=(const T& lhs, const T& rhs);
///
/// template <class Char, class Traits>
/// std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& out, const T& value);
///
/// template <class Char, class Traits>
/// std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& in, T& value);
///
/// // helper function for Boost unordered containers and boost::hash<>.
/// std::size_t hash_value(const T& value);
/// \endcode

#define BOOST_PFR_FUNCTIONS_FOR(T)                                                                                                          \
    BOOST_PFR_MAYBE_UNUSED inline bool operator==(const T& lhs, const T& rhs) { return ::boost::pfr::eq_fields(lhs, rhs); }                 \
    BOOST_PFR_MAYBE_UNUSED inline bool operator!=(const T& lhs, const T& rhs) { return ::boost::pfr::ne_fields(lhs, rhs); }                 \
    BOOST_PFR_MAYBE_UNUSED inline bool operator< (const T& lhs, const T& rhs) { return ::boost::pfr::lt_fields(lhs, rhs); }                 \
    BOOST_PFR_MAYBE_UNUSED inline bool operator> (const T& lhs, const T& rhs) { return ::boost::pfr::gt_fields(lhs, rhs); }                 \
    BOOST_PFR_MAYBE_UNUSED inline bool operator<=(const T& lhs, const T& rhs) { return ::boost::pfr::le_fields(lhs, rhs); }                 \
    BOOST_PFR_MAYBE_UNUSED inline bool operator>=(const T& lhs, const T& rhs) { return ::boost::pfr::ge_fields(lhs, rhs); }                 \
    template <class Char, class Traits>                                                                                                     \
    BOOST_PFR_MAYBE_UNUSED inline ::std::basic_ostream<Char, Traits>& operator<<(::std::basic_ostream<Char, Traits>& out, const T& value) { \
        return out << ::boost::pfr::io_fields(value);                                                                                       \
    }                                                                                                                                       \
    template <class Char, class Traits>                                                                                                     \
    BOOST_PFR_MAYBE_UNUSED inline ::std::basic_istream<Char, Traits>& operator>>(::std::basic_istream<Char, Traits>& in, T& value) {        \
        return in >> ::boost::pfr::io_fields(value);                                                                                        \
    }                                                                                                                                       \
    BOOST_PFR_MAYBE_UNUSED inline std::size_t hash_value(const T& v) {                                                                      \
        return ::boost::pfr::hash_fields(v);                                                                                                \
    }                                                                                                                                       \
/**/

#endif // BOOST_PFR_FUNCTIONS_FOR_HPP


/* functions_for.hpp
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
*/