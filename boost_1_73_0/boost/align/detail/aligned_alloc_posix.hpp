/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_POSIX_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <stdlib.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
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

/* aligned_alloc_posix.hpp
wCVLLP6fzWL5t/jJcYbe9+3KN1s9KwOVu5f6cJq8/cdsH/1QcvMyid0pm10TkLbNZSTLIGHodyQ+5XpOUow974jjAw1K5pXKvqUrmCXVyasiVO5a6WldU/n84tVCnNXXyoagNgf06pqZwKlWcmGdClcxezXO0HFrWXTCS/+PR3gruy4XrtCshFT/nZiq/mip/g3wr78iVMCQlxkSUA0zByEYXzIgMqBuSraHNRwQ937ZHhA/
*/