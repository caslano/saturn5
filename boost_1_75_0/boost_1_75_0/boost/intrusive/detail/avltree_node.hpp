/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_AVLTREE_NODE_HPP
#define BOOST_INTRUSIVE_AVLTREE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>
#include <boost/intrusive/avltree_algorithms.hpp>
#include <boost/intrusive/pointer_plus_bits.hpp>
#include <boost/intrusive/detail/mpl.hpp>

namespace boost {
namespace intrusive {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                Generic node_traits for any pointer type                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//This is the compact representation: 3 pointers
template<class VoidPointer>
struct compact_avltree_node
{
   typedef typename pointer_rebind<VoidPointer, compact_avltree_node<VoidPointer> >::type       node_ptr;
   typedef typename pointer_rebind<VoidPointer, const compact_avltree_node<VoidPointer> >::type const_node_ptr;
   enum balance { negative_t, zero_t, positive_t };
   node_ptr parent_, left_, right_;
};

//This is the normal representation: 3 pointers + enum
template<class VoidPointer>
struct avltree_node
{
   typedef typename pointer_rebind<VoidPointer, avltree_node<VoidPointer> >::type         node_ptr;
   typedef typename pointer_rebind<VoidPointer, const avltree_node<VoidPointer> >::type   const_node_ptr;
   enum balance { negative_t, zero_t, positive_t };
   node_ptr parent_, left_, right_;
   balance balance_;
};

//This is the default node traits implementation
//using a node with 3 generic pointers plus an enum
template<class VoidPointer>
struct default_avltree_node_traits_impl
{
   typedef avltree_node<VoidPointer>      node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef typename node::balance balance;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const node_ptr & n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const const_node_ptr & n)
   {  return n->balance_;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const node_ptr & n)
   {  return n->balance_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(const node_ptr & n, balance b)
   {  n->balance_ = b;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance negative()
   {  return node::negative_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance zero()
   {  return node::zero_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance positive()
   {  return node::positive_t;  }
};

//This is the compact node traits implementation
//using a node with 3 generic pointers
template<class VoidPointer>
struct compact_avltree_node_traits_impl
{
   typedef compact_avltree_node<VoidPointer> node;
   typedef typename node::node_ptr           node_ptr;
   typedef typename node::const_node_ptr     const_node_ptr;
   typedef typename node::balance balance;

   typedef pointer_plus_bits<node_ptr, 2> ptr_bit;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const const_node_ptr & n)
   {  return (balance)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(const node_ptr & n, balance b)
   {  ptr_bit::set_bits(n->parent_, (std::size_t)b);  }

   BOOST_INTRUSIVE_FORCEINLINE static balance negative()
   {  return node::negative_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance zero()
   {  return node::zero_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance positive()
   {  return node::positive_t;  }
};

//Dispatches the implementation based on the boolean
template<class VoidPointer, bool Compact>
struct avltree_node_traits_dispatch
   :  public default_avltree_node_traits_impl<VoidPointer>
{};

template<class VoidPointer>
struct avltree_node_traits_dispatch<VoidPointer, true>
   :  public compact_avltree_node_traits_impl<VoidPointer>
{};

//Inherit from rbtree_node_traits_dispatch depending on the embedding capabilities
template<class VoidPointer, bool OptimizeSize = false>
struct avltree_node_traits
   :  public avltree_node_traits_dispatch
         < VoidPointer
         , OptimizeSize &&
            max_pointer_plus_bits
            < VoidPointer
            , detail::alignment_of<compact_avltree_node<VoidPointer> >::value
            >::value >= 2u
         >
{};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_AVLTREE_NODE_HPP

/* avltree_node.hpp
5OIY3i9lPMj0PuyQO/Cr72HkBGdJHQZLviq2lN0xosspJ/1OYjr2/4h8ZVaHS1wu66vslT023gOnkjjlYq1EUuy+RvHS3PvdquCh8Afu+MArHa9sMXFR456T+E5OqOU2Tnb4eW3EECfmgr3kY7RTrtZPIKhMK/qGu8AbzqGP6XPEWkNfN1k1BplycoAiXkmvf10k/RWqL7M1Sy8rqk/4uGmu2Hmx1wT2LepahMIvRtcLXF/U8DO2V8zmtYi9/kUBiNB5uSVvpCX6CuJHlhLsPxqNa0grSROpn+cRzSu4CgL+tD4JEdRSv8Gk/TzWuZtfavnZCgdVqdjbtpF1En3ZhenUb7lJvhZe25SJZECaEcs7ZaRC6nBhF3dn4rJcDoTbQqK9TSIY6ODD0vt8Vzmg7pO6h9fASI0ephMz7kyZuoPeYMZ1IYEfPEqgJDv6DVsOuG88PujKJkyxfubR8B3tQoa2uh/WQHK2pl/mmq0S0404xkwvrzh5LghzsjE9HsWZ4KSFoHmHeT3WfTnQ1omEuae4BYZnR2s9UrMF/5QtyX1PQktk5cF8MqI7POCs15IOf9aHKZ0xOv3xB3+S9xVyyld7rWlF/PzimhSLMG+fwFuspFvsJyoSLRgGOg2SEks019Am9O/Y3HtygmEydLdfSCk6SQaxkz1RYzIZz9U5ZJ4yMvxG53PJMM5LNmLQ7T6PlD4fYl0SJZKxFA6P
*/