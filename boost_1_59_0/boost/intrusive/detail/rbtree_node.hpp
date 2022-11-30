/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_RBTREE_NODE_HPP
#define BOOST_INTRUSIVE_RBTREE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>
#include <boost/intrusive/rbtree_algorithms.hpp>
#include <boost/intrusive/pointer_plus_bits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/tree_node.hpp>

namespace boost {
namespace intrusive {

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//                Generic node_traits for any pointer type                 //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//This is the compact representation: 3 pointers
template<class VoidPointer>
struct compact_rbtree_node
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename pointer_rebind<VoidPointer, node >::type         node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node >::type   const_node_ptr;
   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
};

//This is the normal representation: 3 pointers + enum
template<class VoidPointer>
struct rbtree_node
{
   typedef rbtree_node<VoidPointer> node;
   typedef typename pointer_rebind<VoidPointer, node >::type         node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node >::type   const_node_ptr;

   enum color { red_t, black_t };
   node_ptr parent_, left_, right_;
   color color_;
};

//This is the default node traits implementation
//using a node with 3 generic pointers plus an enum
template<class VoidPointer>
struct default_rbtree_node_traits_impl
{
   typedef rbtree_node<VoidPointer> node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef typename node::color color;

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

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const_node_ptr n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(node_ptr n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(node_ptr n, color c)
   {  n->color_ = c;  }

   BOOST_INTRUSIVE_FORCEINLINE static color black()
   {  return node::black_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static color red()
   {  return node::red_t;  }
};

//This is the compact node traits implementation
//using a node with 3 generic pointers
template<class VoidPointer>
struct compact_rbtree_node_traits_impl
{
   typedef compact_rbtree_node<VoidPointer> node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef pointer_plus_bits<node_ptr, 1> ptr_bit;

   typedef typename node::color color;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(node_ptr n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

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

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const_node_ptr n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(node_ptr n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(node_ptr n, color c)
   {  ptr_bit::set_bits(n->parent_, c != 0);  }

   BOOST_INTRUSIVE_FORCEINLINE static color black()
   {  return node::black_t;  }

   BOOST_INTRUSIVE_FORCEINLINE static color red()
   {  return node::red_t;  }
};

//Dispatches the implementation based on the boolean
template<class VoidPointer, bool Compact>
struct rbtree_node_traits_dispatch
   :  public default_rbtree_node_traits_impl<VoidPointer>
{};

template<class VoidPointer>
struct rbtree_node_traits_dispatch<VoidPointer, true>
   :  public compact_rbtree_node_traits_impl<VoidPointer>
{};

//Inherit from rbtree_node_traits_dispatch depending on the embedding capabilities
template<class VoidPointer, bool OptimizeSize = false>
struct rbtree_node_traits
   :  public rbtree_node_traits_dispatch
         < VoidPointer
         ,  OptimizeSize &&
           (max_pointer_plus_bits
            < VoidPointer
            , detail::alignment_of<compact_rbtree_node<VoidPointer> >::value
            >::value >= 1)
         >
{};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_NODE_HPP

/* rbtree_node.hpp
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
*/