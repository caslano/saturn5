/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type will
//!derive from node_traits::node

template<class T, class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct derivation_value_traits
{
   public:
   typedef NodeTraits                                                node_traits;
   typedef T                                                         value_type;
   typedef typename node_traits::node                                node;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef typename boost::intrusive::
      pointer_traits<pointer>::reference                             reference;
   typedef typename boost::intrusive::
      pointer_traits<const_pointer>::reference                       const_reference;
   static const link_mode_type link_mode = LinkMode;

   static node_ptr to_node_ptr(reference value)
   { return node_ptr(&value); }

   static const_node_ptr to_node_ptr(const_reference value)
   { return node_ptr(&value); }

   static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer_traits<pointer>::pointer_to(static_cast<reference>(*n));
   }

   static const_pointer to_value_ptr(const const_node_ptr &n)
   {
      return pointer_traits<const_pointer>::pointer_to(static_cast<const_reference>(*n));
   }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

/* derivation_value_traits.hpp
qoQPuLgayNcHFG3OttBfW6+0kMoIVD5T0ju+798c3fQ69FckTiIPJJL5HziScOYVmAdB1BBTGUUJolA1oSyCP9bmfuAScMm2cUm8057NS1YpqVVFsgHBgGDEE0xCmFDSZKWCdIMpDxgJjFQKRorOtK5QgF1OJL2I+Q4C6BID6FV3fZZLozMFUsrECkotuxU9LQFxgDgKn0BIcGPKRDjKMAvYBGySxCZKuCPyQyRl4hZMZkA/oB/eZV5Wa8BH0I/yhV7KvZdPcJjaogL30sbo5Z/25AerPba8vDq+QHQa0Wn2tM6B/Tp2w1zO6BRP+i/RXoMD+gLMD8qS8Bm+uahaqnBJGRWqlkZ+b6mMhr3M2zNg1mHWYdZh1rObdVR1q9AeyRz+tTK7JMvtX5c4xinSqCftluRqyRHaVHqH5HbaXNTPUcF7jTadKC8AswmzCbMJs6mc2axOyQEZAdrIr7GXMU5bbgex8tsS/eyU3kX38vf+vadr/ol+5/To4uIY4VmEZzkX01k0hcpaNnWdu20J0yq0UrpoiOenet0LWGVYZXlWmf76ae+equFCmbqjixvvzP3V9eXN5c2/r477sNuw29zttumBYeh/wYjDiJfQiCPnCTYbnjQscoUscsWN8LYYTEXDz8teL6wnrCc8
*/