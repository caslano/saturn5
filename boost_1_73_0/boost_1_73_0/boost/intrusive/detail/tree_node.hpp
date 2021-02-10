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
ytNCr6rDR2FUKR/K5Sh881wSZmlR7qdJ+av2fpamZJReEMIbZ5K7JPtNKcj01tCak50YB4f0nia11ZykunA6pH5EvLEerpXsZDLpes4o6sN3+Iwiyp9ASkhObkHrqUMnG+vAHomIDtXoly1ey6xbk6VTh0I67qTCUklF3mBpnxeBiLTaNO6k9FbqjtxRm9dUi7K+YoeKIOYO/e8ZtGb7plsj9qKYq6PxqFLZ5PBZcJosHds1HdiU3zGHSmHejz5RqT1EdrRyQp9bVp1EZLPK8g5yF3nBaLhOTi3iy6PcveYkDCnfrPdafM88JrVjbeOT0owur6Jl3bKmaKly6V8JBdu+MIHMXCATjPwhRq7n4k7TDyADyHYHZLNmH0CWS5DB9nsarhWmzEMwDowD456McXU6iG9TwqWOzTQn1dG2z8pA3RLUqUJ5Oz2ybBTbzrf+HN909vTStOoLUXdKBHNSrBlfqPNVdlFZDLvKYzCmldD0lQC0OJs6Me50Jyi3uYfTXe3iVFeE+FJ2H0ZDdwtxuLnDUx04Wgvmm6TCWNUkGXt6FNJ5XZqeX7r71KE+kH/YZwLtEn5LtUyzdILa0B0A6A8Deh9A3xKg40klEA6EPw/C80Lt8XkDBAPBQHD2AHSBTQ0E5wLBYO7/6xx+
*/