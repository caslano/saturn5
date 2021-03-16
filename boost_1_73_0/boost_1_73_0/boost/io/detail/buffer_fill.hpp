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
5hVpm6lVJoxNsLPqYKGJupYDA6HM/NBRVanBoa3pIXpy9HzZl2w7A9ut3K5sS2DznPLQOdo+yp9atEX18AmsZxaoI8UxnQNqvHTq85VM7IJHk35HqMuVTOaC2qz0zxPnqPtB/UqoJ0G9KRSGqpzUBeXg/6+FKsT/46TkEY5+PiumRoP6vFD8he3jhWJIf4JQxaBOFGo8qJOE8u2cpc2KuMbjHW2IxGsDOw+/f7Nm2RK+Sblm5QpEic01fA6isXE=
*/