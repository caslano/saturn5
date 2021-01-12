/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_TREE_NODE_HPP
#define BOOST_INTRUSIVE_TREE_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
namespace intrusive {

template<class VoidPointer>
struct tree_node
{
   typedef typename pointer_rebind<VoidPointer, tree_node>::type  node_ptr;

   node_ptr parent_, left_, right_;
};

template<class VoidPointer>
struct tree_node_traits
{
   typedef tree_node<VoidPointer> node;

   typedef typename node::node_ptr   node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type const_node_ptr;

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
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_TREE_NODE_HPP

/* tree_node.hpp
eafncVXort8eyKropqGQ5CqcPEDNnl2bRP/88FFn6JO26wBJL6gXzR5Kp7q8Bn95IN5Fi/cujowb44ysEEbGvAFG9ryRysg0MBIVeN5yinCw8K7jm/p+MpjgrvsmteL2zenT3jZ7ln1hq+87kcdrn9qYTg/BnIROTLPHNRbwwHvSztdJmKMWRY5b/O2uYC6hRNOojQV5t8UDDmldJf2xiasp6O2HlXLR84AgnW9zruAKTeCU
*/