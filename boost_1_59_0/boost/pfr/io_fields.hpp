// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PFR_IO_FIELDS_HPP
#define BOOST_PFR_IO_FIELDS_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/detail/core.hpp>

#include <type_traits>
#include <utility>      // metaprogramming stuff

#include <boost/pfr/detail/sequence_tuple.hpp>
#include <boost/pfr/detail/io.hpp>
#include <boost/pfr/detail/make_integer_sequence.hpp>
#include <boost/pfr/tuple_size.hpp>

/// \file boost/pfr/io_fields.hpp
/// Contains IO manupulator \forcedlink{io_fields} to read/write \aggregate `value` field-by-field.
///
/// \b Example:
/// \code
///     struct my_struct {
///         int i;
///         short s;
///     };
///
///     std::ostream& operator<<(std::ostream& os, const my_struct& x) {
///         return os << boost::pfr::io_fields(x);  // Equivalent to: os << "{ " << x.i << " ," <<  x.s << " }"
///     }
///
///     std::istream& operator>>(std::istream& is, my_struct& x) {
///         return is >> boost::pfr::io_fields(x);  // Equivalent to: is >> "{ " >> x.i >> " ," >>  x.s >> " }"
///     }
/// \endcode
///
/// \podops for other ways to define operators and more details.
///
/// \b Synopsis:

namespace boost { namespace pfr {

namespace detail {

template <class T>
struct io_fields_impl {
    T value;
};


template <class Char, class Traits, class T>
std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& out, io_fields_impl<const T&>&& x) {
    const T& value = x.value;
    constexpr std::size_t fields_count_val = boost::pfr::detail::fields_count<T>();
    out << '{';
#if BOOST_PFR_USE_CPP17 || BOOST_PFR_USE_LOOPHOLE
    detail::print_impl<0, fields_count_val>::print(out, detail::tie_as_tuple(value));
#else
    ::boost::pfr::detail::for_each_field_dispatcher(
        value,
        [&out](const auto& val) {
            // We can not reuse `fields_count_val` in lambda because compilers had issues with
            // passing constexpr variables into lambdas. Computing is again is the most portable solution.
            constexpr std::size_t fields_count_val_lambda = boost::pfr::detail::fields_count<T>();
            detail::print_impl<0, fields_count_val_lambda>::print(out, val);
        },
        detail::make_index_sequence<fields_count_val>{}
    );
#endif
    return out << '}';
}


template <class Char, class Traits, class T>
std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& out, io_fields_impl<T>&& x) {
    return out << io_fields_impl<const std::remove_reference_t<T>&>{x.value};
}

template <class Char, class Traits, class T>
std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& in, io_fields_impl<T&>&& x) {
    T& value = x.value;
    constexpr std::size_t fields_count_val = boost::pfr::detail::fields_count<T>();

    const auto prev_exceptions = in.exceptions();
    in.exceptions( typename std::basic_istream<Char, Traits>::iostate(0) );
    const auto prev_flags = in.flags( typename std::basic_istream<Char, Traits>::fmtflags(0) );

    char parenthis = {};
    in >> parenthis;
    if (parenthis != '{') in.setstate(std::basic_istream<Char, Traits>::failbit);

#if BOOST_PFR_USE_CPP17 || BOOST_PFR_USE_LOOPHOLE
    detail::read_impl<0, fields_count_val>::read(in, detail::tie_as_tuple(value));
#else
    ::boost::pfr::detail::for_each_field_dispatcher(
        value,
        [&in](const auto& val) {
            // We can not reuse `fields_count_val` in lambda because compilers had issues with
            // passing constexpr variables into lambdas. Computing is again is the most portable solution.
            constexpr std::size_t fields_count_val_lambda = boost::pfr::detail::fields_count<T>();
            detail::read_impl<0, fields_count_val_lambda>::read(in, val);
        },
        detail::make_index_sequence<fields_count_val>{}
    );
#endif

    in >> parenthis;
    if (parenthis != '}') in.setstate(std::basic_istream<Char, Traits>::failbit);

    in.flags(prev_flags);
    in.exceptions(prev_exceptions);

    return in;
}

template <class Char, class Traits, class T>
std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& in, io_fields_impl<const T&>&& ) {
    static_assert(sizeof(T) && false, "====================> Boost.PFR: Attempt to use istream operator on a boost::pfr::io_fields wrapped type T with const qualifier.");
    return in;
}

template <class Char, class Traits, class T>
std::basic_istream<Char, Traits>& operator>>(std::basic_istream<Char, Traits>& in, io_fields_impl<T>&& ) {
    static_assert(sizeof(T) && false, "====================> Boost.PFR: Attempt to use istream operator on a boost::pfr::io_fields wrapped temporary of type T.");
    return in;
}

} // namespace detail

/// IO manupulator to read/write \aggregate `value` field-by-field.
///
/// \b Example:
/// \code
///     struct my_struct {
///         int i;
///         short s;
///     };
///
///     std::ostream& operator<<(std::ostream& os, const my_struct& x) {
///         return os << boost::pfr::io_fields(x);  // Equivalent to: os << "{ " << x.i << " ," <<  x.s << " }"
///     }
///
///     std::istream& operator>>(std::istream& is, my_struct& x) {
///         return is >> boost::pfr::io_fields(x);  // Equivalent to: is >> "{ " >> x.i >> " ," >>  x.s >> " }"
///     }
/// \endcode
///
/// Input and output streaming operators for `boost::pfr::io_fields` are symmetric, meaning that you get the original value by streaming it and
/// reading back if each fields streaming operator is symmetric.
///
/// \customio
template <class T>
auto io_fields(T&& value) noexcept {
    return detail::io_fields_impl<T>{std::forward<T>(value)};
}

}} // namespace boost::pfr

#endif // BOOST_PFR_IO_FIELDS_HPP

/* io_fields.hpp
+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
*/