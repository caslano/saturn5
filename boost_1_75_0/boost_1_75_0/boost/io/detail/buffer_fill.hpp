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
Md7PhfJJWD6z6ZC1aArnbTt+JgBT3OPTImiqW7xzm3oKY0zeZB2n1Yj1+6t3kELzC23VEjJbD5FkTJrRzSMOUq7LYOD+sDUjrt8jRDbkmbAgdFR6uBsPIuUZ/LJoV0ARkzz1KDTgYFtw4y1wXnfQzaG9VjeFaESEGycHKj4/vBVWPB0Qsnv56yqC7P55RfPLRPDP0CVJIimgPEN576OW7gshM8I+1w8U6Kqx7Su4ZFJ2Jv7wxPvpAccXboTeSlFLWRtcVAF4a49mj7SOtKwwi96MVI60hiQsd0nBK2cX9cw3ww42CNoIEg0SAhuCxb6IgjEhSKRv4oLowQFfuPNRnd448ecTOE3vBhKf4H4hy6fYRkd5I/HGUwpkTdFknUDdNTRKJbv6XsAkVRBKE8hcY99Hsn3JEdJCHdL+8w1pPtUfUPvfCBm/+SzXneMPDeOrfLCGv+/iJhijhxrrKxah+Q7KQL8wJ1KooN0p8VBQce6WmfumiCOXmbNOchuczEfm8g1eivvSU3JH9Pr4OQ1b88e6dYrbHWdSwn/PFNjJ8FXJqhSb+QjlkkOHknV9KrUUzXv8vT6lzifLFImKZlDIyPxB8NiMk4EstuSuNFEhQfpyYaidx+ydwefZsrBz235maZUvxtqqsdoWJXkeXakR7EFAr+H7nTf1vz27VKoZHD+5dRjIiuRwnkuqUU3Xvy8hnk76JmqCNXfiVKyl
*/