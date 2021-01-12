/*
Copyright 2019-2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_DETAIL_BUFFER_FILL_HPP
#define BOOST_IO_DETAIL_BUFFER_FILL_HPP

#include <iosfwd>
#include <cstddef>

namespace boost {
namespace io {
namespace detail {

template<class charT, class traits>
inline bool
buffer_fill(std::basic_streambuf<charT, traits>& buf, charT ch,
    std::size_t size)
{
    charT fill[] = { ch, ch, ch, ch, ch, ch, ch, ch };
    enum {
        chunk = sizeof fill / sizeof(charT)
    };
    for (; size > chunk; size -= chunk) {
        if (static_cast<std::size_t>(buf.sputn(fill, chunk)) != chunk) {
            return false;
        }
    }
    return static_cast<std::size_t>(buf.sputn(fill, size)) == size;
}

} /* detail */
} /* io */
} /* boost */

#endif

/* buffer_fill.hpp
6uiUqmUZJiFGrT2dwWKidHGi6i9YJcArx1cPikqUt+B+IbHsLHP1q3q7ZkyAVU+huIdAKBObY1fGLgdZNtLD0NgFzJFP4EmUt2CVEMETeFtBhIuag9eSCDeMbCLOrQ6175yVVGSWlxPu6QNpJm52H0T9BDn2jMkQfXRtWWJzVoC4TlDQekvbyftzj4JxEE29D2tverwns581COutq4lqHB/BvbNPl7xz0n01p+3K5cZAH/tR
*/