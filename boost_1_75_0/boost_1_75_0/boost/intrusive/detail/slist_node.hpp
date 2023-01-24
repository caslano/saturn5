/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SLIST_NODE_HPP
#define BOOST_INTRUSIVE_SLIST_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
namespace intrusive {

template<class VoidPointer>
struct slist_node
{
   typedef typename pointer_rebind<VoidPointer, slist_node>::type   node_ptr;
   node_ptr next_;
};

// slist_node_traits can be used with circular_slist_algorithms and supplies
// a slist_node holding the pointers needed for a singly-linked list
// it is used by slist_base_hook and slist_member_hook
template<class VoidPointer>
struct slist_node_traits
{
   typedef slist_node<VoidPointer>  node;
   typedef typename node::node_ptr  node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type    const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SLIST_NODE_HPP

/* slist_node.hpp
eFFk4eiKJWwGCD/h9duGzF7lC+4i0lKk2uHC1PlssZVjg1gk1tU9wctKnUoL4RrqbBXNOUsm2dxtYWljThaI7Hgsf4UMlArO16CqaCPg3KgVnLWTpWY2P2g4Dt5jtcW60Qp/5ElbmE+9LLVDT9UaPQsxYjQX2hucz6LfVquQrd3Ct/aj+zuYB9Pf/x3MNnRU2t5i2ieNZfr/ArPgbqyn7Y9ZtE+brTLJH8mlRg3Q3uNPbQKqpMyl77NpDiJCdj/1PH0vb1VjDWDOGsDnMv4HmPc+34Iyl/a4H3KCbQmiBj9t63FdY2VYjn7juLHNOBzxzZ1wcZua0/kwMfRlfPDb3tvPba0/9nitKHvb62J15Yz6GnnP/9oU2I3GjZ6InI5MquvUCa925kAbfw/QqnFd+smfw0Am09X6mbX/6C0tM8IEPjMom7pNLla5Eyzmwnm3jqmDteD3qiZUrfs86gBWf+D5F5i7/g5mezq3MEfyv4MZ9cuG3GvQQs5fwWoeeNVSG2KeIe2AFfqFrv5FqQ3NU6I//rsWBUdUeH/EIb/VPMiGQ9qXH1PV6gEbdnxuuK+X1Oq6Rr+92saoTjHPolb4UWnQkBEt0he6ULZyzi7lvncHVIuQndyE2dq7ML4jO3i3VLpuZuBxESB0pPnou1VQKdS+BolK5yfd368jpNzKsL16CJVOmNn8PfkeAzdEa6EUrNftOEDMSdONZg29
*/