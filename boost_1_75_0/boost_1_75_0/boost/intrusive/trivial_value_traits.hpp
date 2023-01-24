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
ydEvXlYnWhkp3h39089AuYH8JTNBUzqjbk+LoijqmT8lRBDf8u8SvKBHTlX389FlCyTfDzGM8KmWLkEVtdW3rfML2eKdFFdsMIXlGrmV9TzCZAemA+5XRvfaJmbt+x7lfxjAq3pnPraZFIFNlvu/uo7TSY/VNqgXqHP22S7L4CIvENW5Gd55soS6U/xuV8FcDyrz40+tRji+tHBpTttI9x58olZp9I7fdi+5Fil0DsZr69TqdC2d9Lu7/a1du3aqyrbRX4RkbeLzzV+6o/bLSDP3Ps1P+bY5q5e1SR3/ZsOFuUOPoJBmhFl6u4Lh48si7ZDO9Jhq5LRbnXTV4yaHH1WNgwxcQ3eRy/NM/nNdZe9O21ZrLOZbTgoqk3jwywzG4KHCkcvFaV8rCw9rkTuIv/6aI4PAXDGZkr7C5f0X7H/didyVBqN1Qv32t2oI7/RDCHXDW+Srs/GcVD7Vqjx54ILsJMfkdZvlbMVOWJabiRvh81azw426LCMP8Hpup6o1fsZmT0Sdk1LTaDOwVZxNd7F2rIrtnI+9NCnuiHmFWFv/TLZ2SND16sYqjKXR+/WqZedhY79ywW0RtSKb3eLL+Bmvx7D2ya96uQsA9uHLbGM971qOTwNOVi0ad3rMxief8IXca8x512iogJGnQfvZvayQd967q50u6bGJzla5k0ZSq6uHNTeAtvDVJxNp16zrTu8vnfxGGsqOp0oT
*/