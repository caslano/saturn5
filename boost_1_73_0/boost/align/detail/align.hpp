/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline void*
align(std::size_t alignment, std::size_t size, void*& ptr,
    std::size_t& space)
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size <= space) {
        char* p = reinterpret_cast<char*>(~(alignment - 1) &
            (reinterpret_cast<std::size_t>(ptr) + alignment - 1));
        std::size_t n = space - (p - static_cast<char*>(ptr));
        if (size <= n) {
            ptr = p;
            space = n;
            return p;
        }
    }
    return 0;
}

} /* alignment */
} /* boost */

#endif

/* align.hpp
0DWSQXULwY7D+i5wmgdDJVKFff1WgeVipynO1IyTmDawXnxJaaYgHV1OOX2yHWGRCp8iYiY+UxfhwB6a910HqMGzE5EC6Ju/T0oaDrC94A38atQnuDVJRQ+JJGDEISX8FkWSWc/qG50QxFAn5NilM52oz5hYX050qignw2/4Q3BgD47ET2yZzx3J2Lq6BfsGMojSItMvN8uRAtqFhUH6vh/hA/9wo6m+tZmXMIK0fgkIkgB8
*/