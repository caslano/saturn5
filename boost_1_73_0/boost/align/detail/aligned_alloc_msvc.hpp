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
vfKxe2jJXGAcdAmUg010RK3s+52iN1CM/H3kgTZyfIUWsQQPfcWax5QjVLNr1Qjp3T0yYN69nVNe+mAZIhi3bzeHnYQOdNBq5rwE0iD9icezow77MFLwVTmMCK7eay4joFuI9OqWvdIeVIoXrhDCx9cOyliEL0keKD9+g/L7q/0ZKfLHHGqPLZDBu0vh+kS452J9haasjV+V5e9Qu1r+TpUJe72ys7sALTpXX8tGfFASF5Xi
*/