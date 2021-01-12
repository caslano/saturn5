/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MACOS_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    if (size == 0) {
        return 0;
    }
    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }
    void* p;
    if (::posix_memalign(&p, alignment, size) != 0) {
        p = 0;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_macos.hpp
38HIpC69MIPcrqJgj3r2qGUvXDg3pWNvj+Q7jfkGBi9Ki5H8laQyNN6CVLzXJd4Ixsu1y9u+HNiKub2AGxclMrcYiAXiw1Qh+ae1zlQvXYYYOvWuVNBEQnhsi4O6pT76FoUELWk0alcd0WT8OeWd6eSUR5JKk9iWT1hTZyKhnU1Gdwr6FUHNg3Kk+EHKc6dGTTOd7VlKW7jx8jo7DAw08PCgsGYmR6XKTcyEKpt+7ZCBOUtm
*/