/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MSVC_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::_aligned_malloc(size, alignment);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::_aligned_free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_msvc.hpp
PC0u6t/058V3326gF77HoI8mqS4cDjl5B8CCZ/9ZtJDVJiV9dKeceZCP5ZjE65u/3bW80Od9rCfepgP6+g1K3Ht78B+V1Yq7++JPuG6bnUkke3k+aYn3ndLCG1XBz9F+ybP2850aD30jrBSC7ejcvhHFUFFN/65pD1gJ32Oy9aVexSi7Qy0fb+XVGJkWwNxply3wwXift7o8ntNMt6QNFNQg12YpEyAcrO7R5P1WF/j814UutUzSmW4g6GQYtMNEaDGr2/+vXiy1UlvE5uvxle7zp99l50Tjhb4g+ODR0Vem1/5GFPUD9celN055YFc138dFyf2b4vbPXB3HlU9/sDH0f7/fKvk+NmVXJrvm5tKVn3T44wVOuc5NNP7rSGrlfH4YWtzMfZko0FScgFqmG0xT51Lj3sCsZYbPQktdyl9JV0ig3F8mhW04bT9EXPqOqnkSf2TzMCPH6G7WPBX+vvrN371dWbxGalF7W9/tySY6s89zF7FEfZQfLPr1esBEJkrSGHBX8EIXRzanb7zTfOqvmkNjqxq9X9WeG4wp6BL17wZfFiGKUcaI0GviXs9x+9450/ixqc3X22z9xA4P5FKDvG/c3Z/u7Gte8i9rFi3AQNiQ4Zd3U2YoqIa3cd9MtNBCenGtK4tt62eiZ+6f9bMIlttoxHxPotId6UdvX44i78PYGmg6n/Rewhwz/s6fWp+EG4ReFUfx1S7q
*/