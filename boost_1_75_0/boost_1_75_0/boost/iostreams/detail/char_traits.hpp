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
Tjx6lc1YERveBMY7OrKNprLW4IJTXFoWDsY17D3mm2nKX4Et/ZHBwY1ewtdF9bKkFfwlW5n2rrPc0UYZMA05k4fLODWxEZNHbarLZOpHe6EQGgm4tUjrZRSfdV6yF3Da0Pg52RCixtwnJGb0i93hQmwPbqnBDF09EB0+lFdCm0hvSYF+8PGFBCHulaoRj340mWxxlL1zp8ML4+STHqfjOecXOHFFWlrgkmIfXNvhbNLbpfEQ7VaUbLFes+3SBU8+zfdLzRq1ZXzndnqWWLTyfq0r5a9Gg4kMy6torHlIj1tGNQ6UU6nOCO95RrrQPoRZCeMrFHAvMcG+PDin88RfKc+Cpd2k8okoWdRIK54TDYvesQhN7y0tUlI998xTZgzgW7oBn2vKbSTU/wwKwEn6rLQXZPozIMmyG7/zhc7whYKolrbRJ7LUEd4tAsAtoWOQQZ5h8PuPBITR6Eonh6E/biZ1kz+3nZpTjYQ4ivudE1oCbBg0xgHfmzt2vKpBp/QDj2F80eFVN0Dm2MaJsl0oKay1qj4l1gp8sgDCPg8zFL5VoWn/gjdhwSnCop75z5JrFLFtWPLTtLqzfMuuWXj8m85EGWSIV1AwPM5y+muRpdSuoD89ITaMs7LI63aJYjICKOkCLUAJzX2RzLBn75DzDxa6Qa/DWb4II5DqX1dIr6KTAP9nOgFDSqDjxAAFfmV9tIp3ioi0A4mJPJoB
*/