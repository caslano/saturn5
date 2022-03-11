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
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
*/