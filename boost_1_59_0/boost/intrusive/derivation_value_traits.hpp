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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value) BOOST_NOEXCEPT
   { return node_ptr(&value); }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value) BOOST_NOEXCEPT
   { return node_ptr(&value); }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(node_ptr n) BOOST_NOEXCEPT
   {
      return pointer_traits<pointer>::pointer_to(static_cast<reference>(*n));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const_node_ptr n) BOOST_NOEXCEPT
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