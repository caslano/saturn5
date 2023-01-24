//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP
#define BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

// move
#include <boost/move/adl_move_swap.hpp>
#include <boost/move/utility_core.hpp>

namespace boost {
namespace container {
namespace dtl {

template<class AllocatorType>
inline void swap_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void swap_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  boost::adl_move_swap(l, r);   }

template<class AllocatorType>
inline void assign_alloc(AllocatorType &, const AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void assign_alloc(AllocatorType &l, const AllocatorType &r, dtl::true_type)
{  l = r;   }

template<class AllocatorType>
inline void move_alloc(AllocatorType &, AllocatorType &, dtl::false_type)
   BOOST_NOEXCEPT_OR_NOTHROW
{}

template<class AllocatorType>
inline void move_alloc(AllocatorType &l, AllocatorType &r, dtl::true_type)
{  l = ::boost::move(r);   }

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ALLOC_TRAITS_HPP

/* alloc_helpers.hpp
YJWKHsjsvQijNh+X+MeCvhLWeRWAXGw9zAyug9G+n2DQERMQcKkC5PARkF0ZoKclIHbq3v+YDvsDSkAhuRF2vW2ENTENMPGsGUwPqoWxfp9B1KsGkG0ZCGl5EPl/S4dnRhe/+N18f3F/YAmczm6E41lNsC+lEWZfvAkykfUwG/fH+JefAT17DwN1fUBoz1UQU3/0zTo4mGhAS2UxxPq5QAzDEaKe20KkmzW8cn4EIfaWEGR3B/yfmMP+oDLQfdcEOkXNcDq3GaSv3ITNCY2wLLoefgurx+PwARDdHwbu14fBWi4w/PyTb8ICOJldpfyYcHywcfyosN/nAqs4G5iF6dBckAJNeUmwP/g9mJc3w+0PTKAXM2G1rjmoZDTBDjweq95g+c4VlHx06DoM1HEHkSvO3yTf9ZYOx6fK5wrIPSEJqarzIfrw7xCwfw647JwJjzbNgFtrp8L+0AowLW3ujltMHlD9cTG3EY5lNFCRJ3+QgTcl//jWxXBsyyJQ27wIVDdJw9GNC+HIhgV4PKVAZb0Upd/zOwYcv0vExw35bTzxSUf5YiuhfLqw3ucDqzQHTkTXQGFze3c0fuoAKXgxJTGkqg1eVrYBMonoJZ8av2f3INDmNvg/vQUvntwE30em4GNljOUvoOQzLK9z/bLV/2n7rx2Qo3TwqGeDO47WNSw4cN8WNAqaQSm9CTbEN8CC8HqOfLofJb8pK47C
*/