/*
Copyright 2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_ALIGN_DOWN_HPP
#define BOOST_ALIGN_ALIGN_DOWN_HPP

#include <boost/align/detail/align_down.hpp>
#include <boost/align/detail/not_pointer.hpp>

namespace boost {
namespace alignment {

template<class T>
BOOST_CONSTEXPR inline typename detail::not_pointer<T, T>::type
align_down(T value, std::size_t alignment) BOOST_NOEXCEPT
{
    return T(value & ~T(alignment - 1));
}

} /* alignment */
} /* boost */

#endif

/* align_down.hpp
7HfxykY6hwA2secfC+We9qFCSqUaqN5FxgRqA8m+wsz3vxpMpo/ssINx
*/