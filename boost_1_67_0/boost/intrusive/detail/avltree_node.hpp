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
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
*/