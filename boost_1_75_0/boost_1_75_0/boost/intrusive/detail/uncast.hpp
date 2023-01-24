/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_UNCAST_HPP
#define BOOST_INTRUSIVE_DETAIL_UNCAST_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class ConstNodePtr>
struct uncast_types
{
   typedef typename pointer_traits<ConstNodePtr>::element_type element_type;
   typedef typename remove_const<element_type>::type           non_const_type;
   typedef typename pointer_traits<ConstNodePtr>::
      template rebind_pointer<non_const_type>::type            non_const_pointer;
   typedef pointer_traits<non_const_pointer>                   non_const_traits;
};

template<class ConstNodePtr>
static typename uncast_types<ConstNodePtr>::non_const_pointer
   uncast(const ConstNodePtr & ptr)
{
   return uncast_types<ConstNodePtr>::non_const_traits::const_cast_from(ptr);
}

} //namespace detail {
} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DETAIL_UTILITIES_HPP

/* uncast.hpp
NouNneOyT1XHSlOAXTKJzX3E6sS7qRWebxolLSz5rOXmHmZp8f03KxBXKtbKZd0fBgZVQvaQS0447Z22w0VHQc1rmJlJeOEoLoZHuLLDK/1cQniRzEwMQ1ekp8H6Pe6iGVD73m2yuQHwPrMFFjJTayow+85/LSUyq7zS7s5e/tmh1JFleiLC8Yg9u20acZgZT17S8tnM/tPOgt3YmOeHpVa75BWgG1m8qbK3IPmA3TTF9pEcabbvyfoYjmggbLkXg0jYypWn3pvDl4TSkXdp2UUHwjXNWomVpb/YA61YWm3+pX2O5JnvYI07B9fpK0BvlbtyS1+nm53dfgBgmiXoamzWmki1+aPnrv1a18vyiCviALCqXl6Je9hqIHJBDnAVj74RKnIEZ8f+TpwVlfhhtppIgYC3Btd0dwmiUpfJ31+JWo8s1+dpH1Ap7HG5DNTvNjuqNhjKVgrYBe5x3Isudx8UuJbjJTMT+ouL+++QdR93qCxw99WAStF3LAoi1G4jPGVka6t8P2GpvFwmevLz6bQNMOtF0FF4vDVcDxBK2KNHdk4OfmQ0SpMfVMvMSqKe89rIVdb6VFg7A3T+ZST0HotVFalWe/R7vk14f6L52BRJjRfKqnM7m9HRHvqJ+qdnwtN2ya+x4dM1KFeExkw+ccl8LOPQKRVU653XAXWi4FYNY5TgZVfzjnhe5dE6/4LGVM4Pd5Cyz3CTW0SK
*/