/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)

*/
#ifndef BOOST_ALIGN_IS_ALIGNED_HPP
#define BOOST_ALIGN_IS_ALIGNED_HPP

#include <boost/align/detail/is_aligned.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, bool>::type
is_aligned(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return (value & (T(alignment) - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
VBJe8lXKa10Te9qSpPXL23j3IdgNLiRcFhPRCBevjqEogTKxvK56IiRw35UOyr1A0p6Vo56sZ6V12V/P6nSO3pOJbj2r0vrlnaxnBUnSnkVF49ZTtkmMn5Z1UCTsfZFIi78d1x0NYfw4DF80eBTXA/7+ZX4SVMaJgsdDXRFcJeVVFHejUHtxrTFA74KMk+9DxrvDMkoDS34pdS5Ezivtg5AmhZIPO4XoKWM7RSqC3zzBpzj5tXnHhEMtrdzuQXU=
*/