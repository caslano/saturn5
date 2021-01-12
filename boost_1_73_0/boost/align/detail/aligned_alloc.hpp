/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/align/align.hpp>
#include <boost/align/alignment_of.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    enum {
        N = alignment_of<void*>::value
    };
    if (alignment < N) {
        alignment = N;
    }
    std::size_t n = size + alignment - N;
    void* p = std::malloc(sizeof(void*) + n);
    if (p) {
        void* r = static_cast<char*>(p) + sizeof(void*);
        (void)boost::alignment::align(alignment, size, r, n);
        *(static_cast<void**>(r) - 1) = p;
        p = r;
    }
    return p;
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    if (ptr) {
        std::free(*(static_cast<void**>(ptr) - 1));
    }
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc.hpp
48FUM3VcYXrO26jU/s6Athuf1De0gCW7fxE7inobo9egrUp0obFMKGC/ru7syhBFs460JdXlb78H36LiKCN23AUx0OU+R+vZKz2x5V7H4gnmchtBmDNyM9R1oaHO6FyIX9n3QtEt56g1ILatBn5Z4am6brgQ+EFWuFTvrPIKnBYuEgWIoPC0Toh9kLs8s4/l0KLb8MJAPkf2ow0o/+CEUBivZuOvcaJt3adQNgk4O2NY/f9N
*/