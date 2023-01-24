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
+b8yt3y99AfcxV2bklh1+OrZyLq70iTqa9nslurZIIqrP7VDjerMkZvgI3YnuobaF8zPX94NmaduNxYxDuLPFd1ZOicSoDeg3Do58P9Bkhooj1HE9snGGjlqjp6JKRimKO9lH2hl6dGkq9ir/iz7CBp/msxp47Y67Dx0vjwHvcwWLSXk/HpCOyhqSpGlKo4u/VihYp1SlvKlYFNcCah+cjpPNTvE7P+GZ7uFaTXhaXjlKBzsDKYx5nQSqUURQBL4NndYXG9yivhTQOCcJsZbGnM6ftQ//SwV9mQh5lQufBn/dSToYmUTVRkow8tvOfcKwzQCnVZBWHp7OTR+GIjxfksRemM44itatIwZJVlPLymWgkwLMZIbzBc9Ujf3QLYiK9e/eoK2N0cA4wlyFTW91ZippWoHO1XYUxGah6o2r2eaXXuVrjkuCZmI0rsWpDMuWI3e0sF9h6Phc4bdCbG9Ggbce4oYCyH4Mjy1033a+Rxdd03V9Jpdjjn3cuX5g4/dff1M4ED3MmMOwn3U+02eEwt2+zrsuwu8MZJNEdSae7ESBnjkeG4dUlJ4/q7nPO7mixHP2xIheGQ9cvcue0ZYfJJ68wslW+n0ZRuel37Hs30APgGTgDPBOkWHInk4rolTyLrBt8EHYFQwS5DWW5ag1H67rFIMLwInXCdOp/e1pK342oVDDbRGaJWo7OjVb6pRFpFqFnmy3MTwhaYP
*/