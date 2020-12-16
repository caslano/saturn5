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
20Y8YvdFJO6TRr+Zrt9dKl4fOkw6NL/LPOdHB+iUnRZ5nrVUZc6zTDvfXc7vCKWTnUpt+MWoOqihrrlN89/bN9pbmsazrWxJY3fVv7kiLkBPkU7epdYT3nD/K/RvxkUsM+so0iZ6qbU1eqXo6LVWRs392OGKtMbEss8jdrJVL66ZlRlHHUlZf6jqKM3yksJT+dfpX89Xfch74hNwO+gZgY5FYUeDukZH9nj9PCvRGXTkz/AQnIqO5KEjX0EL3ViIjiyFtXi+3Y60jIiwtqLPfSOjrVeQZVF3hafSv58j7XIzVU5jI2ZyvTx09CuLeNDRK9HRVTCa6yZx/Zvh3bAJ123LdR+C22EPrjuI6z8HX0FnR3H9dK7/ATwMZ4cvtr4O5+6M8LrfuL5E1W2y71NrGHubo+jbeVU9FWv1NJw+sNNvyVf3+IkIpw+dpcKn1Cmtx4luvd8qOlxbwjrxdfMUBOhaR9Gl7SF0qYOcL9LO2++5syph51Hec+VdU3/XzQ16z1Xviu4ak5SfsMYk1BqQnWrtybZ3f5z17sUPeN4L2/vwut57inhn3ahssbWOvX1o57QH/16/fcRr5978x1/ORph5rcovu/ZkrTPmKOOh6VC3l3OW7IPtBWvA3rAm7AtrwbNhbdgf1oUDYCs4EHaDg+EQOAJOhSPhpXA0XAXHwNvgRbCVB32GneAE1z6CjO/BHvJb3zedJPumubZKRzJE1JqY0+Cp8EzYUN9nfI1r/4r8Bu4X7sZ1bXaXfJ0JHTs56RLuTQmn28n5TtLxPQyHloT3wVNhJGwEo2BTWAM2gzGwJYyFHWEc7Arj4ZmwNhwIG8ELYCc4EXaGk2AdmAcT4CJ4mpRnc7getoAbYEu4EbaCm2BruAW2gX+C7eBjsAPcI9d5Q11H7OSEyfiKjBsNgpuRDTKmeLrsA+8I+8AecDjsDW+EfeC7sB8c4UFP4BR4DnwUDoKvw8GwMffJENgNDoXL4XnwdjgcHoMj4Q/wfDjZhz7BK+EFcA8cCw/DcXCkH/2Cq+AlcBdMh/VJ+0Q4A06Gl8IM+DqcAj+BU2E3KnQ6PA/OgGPhLHgZzII3w2y4GebAvTAXfgFnQx4b1hzYBM6FvWEevAjOgwvgfHgjXAAfgvlwD7wU/hX+BvpoVy6Dp8HLYQ94BRwLr4Rz4SL+vw7+FhbBxXAnvAoegEvgj3AprB+FDSrYFS6Ho2ABzIFXw0K4At4LV8Jn4Sr4AbwWfg+vg3Wp+ELYEV4PR8MbYC68ES6Hq+E9cA18Ct4E98Ob4TdwLawTjd062A7eCgfB2+AsuA5eBW+Hd8I74eNwPXwb3gW/gnfDOB4K98BUuAEOhL+Dk+Hv4ZXwXngbvA8+Au+Hr8M/wC/hAzCZhm4j7Aj/CEfA7XAVfAJugk/Cz+BTMCYWu1iwCXwa9obPwIvgs3ABfA7eCJ+HD8EX4EtwJ/wr3AV9cdjLgqfBF2EP+BIcC1+B+XAPvA7uhQ/AYrgTvgoPwNegPx67eLA+fAN2hW/CUfAtmAPfhoXwHXgvfBe+AN+DH8A/w+/hPliXBv992BF+AIfD/XAm/BAuhx/B38MD8Cl4EP4Zfgy/gZ/AOjSMf4Xt4CE4BH4Kp8K/wavgZ/BOeBg+Dj+Hb8Mv4VfwCIyrQz8btoZH4UD4FZwGj8Er4dfwNngcPgK/ga/DE/BL+C2MTqD9hmfA7+FQeBLmwB/gSvgPeC+0PKQHeuBe6IWHoA9+A/0wOpHuI2wKw2FHGAGHwkh4EYyCObAGXA6j4e0wBm6GNeFOGAtfg3HwOKwNGyXR7sPuMAH2g4lwEkyCufAUmP8rrQFt0TnMGoRMQ1YhGztXrwn9Xz78yIx/4fw=
*/