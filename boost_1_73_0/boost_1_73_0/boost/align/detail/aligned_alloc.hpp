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
MNdMjjU9s+4mLqnDKEZMGWRLHwAC+9YqUng0g3phl4hsDzLdgvLbD+iCApGhvlHMgqz4M4puZH8G1dGvnnJZzzTb1SNT5BxDYY4k0/0XVeaIcth1YWHEFs6jyavN2kR6o7wMJQoFAWz7lgwHnCjddhmc5qoaTjWaNk27ctVyJ9gN1UcmOLmVBTNdajxVRdwCZ4zPILwUpgxYh27ypWAn3BtXZixwmtWLlpRZUBkkt5wHUljSSxkGTIZsNqdLf2JisIkdGldvuZmW3o2FAdbm1YaC7QLp5vSBVxsjLxaDYAc2u7teSd+83l83u6oByg6qSKBvIDJJJAIXO0V+KELKw9juaocvrfBQ/8S/7J71gCO9qJxZCYtpE0oUuDC6pZH58/ra7hQZb008Wj8MDU92dmA4UdWMqdmYZtQE7qpvz6Hfx9Fp8lM9Nxc+AnNAGkEuJFZUZsGI7T7/knnpmJSZjaCpxdLjA8G83YSr+VQ/q4CN09mQTKHPzGLYcEZ/0W2+pvGdfyCaFqCD6XBEuqiAGx4Jj+7c5PbTK+Nshfh0VCtoJmXXMIqD1F6eEvgOZ2ormd7UMHq5SOBfmtiBJRpKM5PJJAY1wanJ1GGBmDTQUb/88HOlRREsesDTi1WNg9FQdHNmDBhBUi7ULJw+
*/