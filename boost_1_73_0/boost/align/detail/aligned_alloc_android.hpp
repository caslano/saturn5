/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_ANDROID_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::memalign(alignment, size);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_android.hpp
r2VK3hh7Jzx7pOppZuPv/aqTC2+uLLwBTe1OnGdcRqz96MkJtsaYQXIgPDohbUC+A8AuD1Ck0SrTH8qgM+7HKBj8bNXVkXOGMo1Adjko1KAmYykoaaIN+Qt4i1x3tmiFa5IPdourz6pFt9eyeG8EkWpcnFwgn+k+1pUR+A/lc8OFiRkZwdBumSGP7lTLDVtCRu9Gab4iV7pN/YH17PyFVBZT/YAz7GvbIpvtFk1Q7ge0cGWM
*/