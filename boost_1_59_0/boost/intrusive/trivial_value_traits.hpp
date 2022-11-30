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

#ifndef BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type and
//!node_traits::node should be equal
template<class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct trivial_value_traits
{
   typedef NodeTraits                                          node_traits;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef typename node_traits::const_node_ptr                const_node_ptr;
   typedef typename node_traits::node                          value_type;
   typedef node_ptr                                            pointer;
   typedef const_node_ptr                                      const_pointer;
   static const link_mode_type link_mode = LinkMode;
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr       to_node_ptr (value_type &value) BOOST_NOEXCEPT
      {  return pointer_traits<node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr (const value_type &value) BOOST_NOEXCEPT
      {  return pointer_traits<const_node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static pointer  to_value_ptr(node_ptr n) BOOST_NOEXCEPT
      {  return n; }
   BOOST_INTRUSIVE_FORCEINLINE static const_pointer  to_value_ptr(const_node_ptr n) BOOST_NOEXCEPT
      {  return n; }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

/* trivial_value_traits.hpp
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
*/