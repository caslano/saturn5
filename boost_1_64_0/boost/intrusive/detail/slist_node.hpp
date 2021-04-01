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
XBK+zDVQ2OQM6hjg7SqfFhbNuCwff8dDGsjaGbad/5pHSxHzxv0Yc8LldYGBf8NeEQDL9dPx+WDg5ASZQK36MZ2tG90zZcMiYtgkOK98X67nSzp+E6kxH5J+k60Z03TFeiud3BUit7t4p9ZLHNOCXqkWRCgvOdHpJy/g/mr2piROWvYacoBBij8DcLeZYuiA505Gr6UfZNowd+fagWtb2dyuBMrtaJXSnaQGLtgqL3kDutH+8kRndBdC7gf2UnJJ9WY7YKAxe8DJh8AZaLUfTVmbh15cNikvkA4XsS3cbxVgG9HAGndNZgcV9uL2BzMhP9uj+0/61Fp8AJiyjjZYEiBDS0A5jMOH35KEF/rd22+/LAwuz366C9Eql12/wavzbSUW53MDNQkrB7UG7IQXONVJVW+KTZOdmHou2gZbLzB733G1lk5vo9mm2hmnsy1JCgJ5g2PllV3ZA5pN6ahKJbLb3EHVD9TpP+iqmvrLRbAz6ivOBuobIqBFUvJNPiEKPxWxMqVRqIzd4HAVxnz2B2Y7cluRLGuFyO7DbkEPa3D3bXAo19V8mNrd2Q==
*/