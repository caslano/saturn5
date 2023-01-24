//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_SET_HPP
#define BOOST_CONTAINER_PMR_SET_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/set.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
using set = boost::container::set<Key, Compare, polymorphic_allocator<Key>, Options>;

template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
using multiset = boost::container::multiset<Key, Compare, polymorphic_allocator<Key>, Options>;

#endif

//! A portable metafunction to obtain a set
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
struct set_of
{
   typedef boost::container::set<Key, Compare, polymorphic_allocator<Key>, Options> type;
};

//! A portable metafunction to obtain a multiset
//! that uses a polymorphic allocator
template <class Key
         ,class Compare = std::less<Key>
         ,class Options = void >
struct multiset_of
{
   typedef boost::container::multiset<Key, Compare, polymorphic_allocator<Key>, Options> type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_SET_HPP

/* set.hpp
1M9Lg94W3tW6dq2oZO55IcpGtPo1CWqtBhmyvCRoYxCpDhjP2gUoy4N9AuP6Nq9hRQQw4wB8K+TQdBtt1a6/mvWXlfH3r+I9u1PPJx6/xKd2P0V1+stk6RSccH1vn8qOSRJY7uQMdMIFXmDSf5Kj1rFuemztvsiOeZlBYtAAMUDOv1IySI4xmW5TTncZFLez5Sqen15Hb5+lGkzppEuspYbbez26nR7nvzXmptI8upWxW8KP3SF00yTsQR+NMQoXZwcaLWy7IWWm8VqRpgk+8aQebKVQicclABcs6NOBONOxycZoaultZIy2j/Op30/4wQ8LnbWn6dw4znjn3ZxYuczGB14mP36dtbveyPNf7HPu8W0OzyacuSgHQoXtUF8jWQukIDDfEETRniMokcTw4vFOUZWOKnIApXVUVqONx6BQEkRJ6ZpZj3tT1aXV825AA/fb8lwDhHjsrM9pUMAS39cghXZZeK0LW99tIaBwkD+Ij+eQQ70XpZ4ALM08QGsFLfsUaUndP7G9f9tJQLeA//AqqwDrFUjAmuzz87HGRpD9axfk7yT83wuX4MkrE/7ln7zAc8c/yeT2R3HTivHUUto9rC9RKDqdnL5KUN7jxbOadBEpGdkRCmFd90mdwYtmz2/zIt8g12u8c+1Btqvr7JS7DKsbXBx+m7uWHsLJMtuTkn6ywqCouGkyvn1J6LohXo9Ikg7eK0TXP7Im
*/