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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(node_ptr n)
   {  return n->parent_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->parent_ = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(node_ptr n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(node_ptr n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const_node_ptr n)
   {  return n->balance_;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(node_ptr n)
   {  return n->balance_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(node_ptr n, balance b)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const_node_ptr n)
   {  return n->left_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->left_ = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const_node_ptr n)
   {  return n->right_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->right_ = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const_node_ptr n)
   {  return (balance)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(node_ptr n, balance b)
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