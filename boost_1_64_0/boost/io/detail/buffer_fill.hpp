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
YqT7P12gAalGEUY1lytSE5XFEVhgK5WvbP6op0E9IhRvd8Kn1Piwnje2eOQwNb1o7plFQR3SGxO9VL9KniLL1JBHT/G1UmhSZSzLflX+NIdxGRuJKxWM8UCSlldwS444AzkJvUTq0/psnsjDjQPa5p7/HIRM7Om3TRW3KJOPO0yqt4jBySRfdpAcEm4KIpadj64unhsvL2CTmlcFEz1v5SYVp93BXx6gUmaBDBwNOSso+i75xgOgRT/YUtSAjdyVEMwdEZ2X0O02k+z23i9cnlZuVWxPt0PWQNjyYoPP3Rb1n6Q1G6ehtG+doPJ5S6VkYzRWEJP+Jnvz4KKgn6sVrZzz+ZXGp3a1Q2ifYAsnl2le0fUifoBA4pYfhLQwiWor26QatlglUo7aFpDrgKipZOCOfh5/6reCo2/00RTRaaLuwfQylq9zoWhWAlZ/I22/QhoKJMNv5Jfi2pP41WDf9LuYlZtzLfwevMoPDJRxqSkQCHr9s4SQBIUMm1zfW8lW9iQouiXd/SvXbZ3yi/Guxbyr4U70Xvy4e/Ir1JBcopITsSLX/PkYeHGY4A==
*/