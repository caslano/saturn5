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
gC90Pw8Trq8qZDH3jfo3tR4gqOvyC9DeN5ehG2eFlGadDi52ikD5YC4HWPvvuwK7phPGOeqHyKaM1ZHzAOjg7llSJcEeAyhvMqguVeRhBpTk3D+zUNT0StjLh8MF7BVELkXEAap2ZMAT4R7CaHToEiSuhmfGiLmm5qmTgcA6U2XCHciBc4FXEr/CwCSq7F2o/vjVLYDUW+yU5Bzy3YKE3cQPl88MWhdrQbi0I30bKv5rDNYM+kWntAkr4pJYqezMn5j6jIqYXX8VGphz9vPdTbQ70DCSuLScgRR5TMqPNEuakMZ2Z/TcHUN63sCHGCx8p/b40ka2zNsXj7nQi+wiRPmJEGkRDG0yJgD+JPnKmofcuHf+VjWux+mdrAbbpMHsCZj2EIg326TavZFjY4xYGlywH0waGzoswHEa8jUJW4XsOFOPC0A1GV8EPN/ikIxJQU2WrrD61DRBvOhfUl7CGbntIjQTMBbSkYsNZFadbYPOsXvaBtqYv8DVqL3jLJoiBKFBjXiP/P8aBNjnX+HUkBU34huKA+GzcLLM9/GonScDckrE3mVHllVALw==
*/