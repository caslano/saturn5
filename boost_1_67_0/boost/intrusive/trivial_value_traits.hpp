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
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr       to_node_ptr (value_type &value)
      {  return pointer_traits<node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr (const value_type &value)
      {  return pointer_traits<const_node_ptr>::pointer_to(value);  }
   BOOST_INTRUSIVE_FORCEINLINE static const pointer  &      to_value_ptr(const node_ptr &n)        {  return n; }
   BOOST_INTRUSIVE_FORCEINLINE static const const_pointer  &to_value_ptr(const const_node_ptr &n)  {  return n; }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TRIVIAL_VALUE_TRAITS_HPP

/* trivial_value_traits.hpp
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
*/