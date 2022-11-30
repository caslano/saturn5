// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_IO_HPP
#define BOOST_PFR_DETAIL_IO_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <boost/pfr/detail/sequence_tuple.hpp>
#include <iosfwd>       // stream operators
#include <iomanip>

#if defined(__has_include)
#   if __has_include(<string_view>) && BOOST_PFR_USE_CPP17
#       include <string_view>
#   endif
#endif

namespace boost { namespace pfr { namespace detail {

inline auto quoted_helper(const std::string& s) noexcept {
    return std::quoted(s);
}

#if defined(__has_include)
#   if __has_include(<string_view>) && BOOST_PFR_USE_CPP17
template <class CharT, class Traits>
inline auto quoted_helper(std::basic_string_view<CharT, Traits> s) noexcept {
    return std::quoted(s);
}
#   endif
#endif

inline auto quoted_helper(std::string& s) noexcept {
    return std::quoted(s);
}

template <class T>
inline decltype(auto) quoted_helper(T&& v) noexcept {
    return std::forward<T>(v);
}

template <std::size_t I, std::size_t N>
struct print_impl {
    template <class Stream, class T>
    static void print (Stream& out, const T& value) {
        if (!!I) out << ", ";
        out << detail::quoted_helper(boost::pfr::detail::sequence_tuple::get<I>(value));
        print_impl<I + 1, N>::print(out, value);
    }
};

template <std::size_t I>
struct print_impl<I, I> {
    template <class Stream, class T> static void print (Stream&, const T&) noexcept {}
};


template <std::size_t I, std::size_t N>
struct read_impl {
    template <class Stream, class T>
    static void read (Stream& in, const T& value) {
        char ignore = {};
        if (!!I) {
            in >> ignore;
            if (ignore != ',') in.setstate(Stream::failbit);
            in >> ignore;
            if (ignore != ' ')  in.setstate(Stream::failbit);
        }
        in >> detail::quoted_helper( boost::pfr::detail::sequence_tuple::get<I>(value) );
        read_impl<I + 1, N>::read(in, value);
    }
};

template <std::size_t I>
struct read_impl<I, I> {
    template <class Stream, class T> static void read (Stream&, const T&) {}
};

}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_IO_HPP

/* io.hpp
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
*/