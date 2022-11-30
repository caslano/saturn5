// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// Provides std::char_traits for libraries without templated streams. Should not
// be confused with <boost/iostreams/char_traits.hpp>, which defines the
// template boost::iostreams::char_traits.

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_CHAR_TRAITS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHAR_TRAITS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <iosfwd>
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifdef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <boost/config.hpp> // Make sure size_t is in std.
# include <cstddef>
# include <cstring>
# include <cstdio>
#endif

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //--------------------------------//
# define BOOST_IOSTREAMS_CHAR_TRAITS(ch) std::char_traits< ch >
#else
# define BOOST_IOSTREAMS_CHAR_TRAITS(ch) boost::iostreams::detail::char_traits

namespace boost { namespace iostreams { namespace detail {

struct char_traits  {
    typedef char            char_type;
    typedef int             int_type;
    typedef std::streampos  pos_type;
    typedef std::streamoff  off_type;

    // Note: this may not be not conforming, since it treats chars as unsigned,
    // but is only used to test for equality.
    static int compare(const char* lhs, const char* rhs, std::size_t n)
    { return std::strncmp(lhs, rhs, n); }
    static char* copy(char *dest, const char *src, std::size_t n)
    { return static_cast<char*>(std::memcpy(dest, src, n)); }
    static char* move(char *dest, const char *src, std::size_t n)
    { return static_cast<char*>(std::memmove(dest, src, n)); }
    static const char* find(const char* s, std::size_t n, const char& c)
    { return (const char*) (const void*) std::memchr(s, c, n); }
    static char to_char_type(const int& c) { return c; }
    static int to_int_type(const char& c) { return c; }
    static bool eq_int_type(const int& lhs, const int& rhs)
    { return lhs == rhs; }
    static int eof() { return EOF; }
    static int not_eof(const int& c) { return c != EOF ? c : '\n'; }
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES //-----------------------//

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHAR_TRAITS_HPP_INCLUDED

/* char_traits.hpp
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
*/