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
NNG661Hngo3awDGAVHwyPLLiRhzc9VPiV7l1GXFy0+OtWOSOuGCo2ix2+OLolnEsXRlX9jLZnILQl3qJw7ofDBekyttofOW7LKfeNyCyaVJ0WmmbGH2MQweWF7ZcwPSm6F9XgyFcEn2sKlu8zlajJWiMLUzZWsdKkmiTdmNaBZJWi0NKkvi6+Jrl2TSNs1Q/lF6W177DssixayfWRZQp0ytqDAmzOnYOyhHK8dpWrDcq8JTh
*/