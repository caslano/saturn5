/*
Copyright 2020 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MINGW_HPP
#define BOOST_ALIGN_DETAIL_ALIGNED_ALLOC_MINGW_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>
#include <malloc.h>

namespace boost {
namespace alignment {

inline void*
aligned_alloc(std::size_t alignment, std::size_t size) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return ::__mingw_aligned_malloc(size, alignment);
}

inline void
aligned_free(void* ptr) BOOST_NOEXCEPT
{
    ::__mingw_aligned_free(ptr);
}

} /* alignment */
} /* boost */

#endif

/* aligned_alloc_mingw.hpp
gzPOgrEJEfs1F2UFSiVr55kIMLMbNjIHxXETOTbSCnFolgCMTccmTsJn8lq3j4Ct5RTGN3RINnojLinm13Widgrn9tFGYK3X8iacKwG1wz1Jb4Q7BZ+6tjR1BsSE5Yrg1hrn9+McBOoohpmgrbvuzRQE5CByTXHrAJHk6AAxISyvEgfDEbmNhmr2NBOq3+Bo6Q5ucoBi1xZN8O58q1puqY6aJf64rEgW2W0iZ+DaaOq4myCqdHcxtNU2YW0cTe0=
*/