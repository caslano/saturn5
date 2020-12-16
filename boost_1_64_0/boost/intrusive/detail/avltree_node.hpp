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
wWr4K3gHRFT4nRAp+lS2j8E18B+yLePIpJ+Oa0vyp48j+zt67SBxVf19Bs+B38LB8HNp747DbNkeA7+A4yR8GvwSFsCv4F0Svh7+Ez5qpyf5yXH6cbAfuW5jkNGSn+/RqwVd1G8HGCXn0w0/lPB/wurwBKwBf4AeSBjb3uNkOv0IPLtJuashGXKcmmJPsTAa1oYxsBZMkm1nbRtJJ9pwv5kj940CWAPO1dckqiDeaIk3RuJdqOLJtVVBvhMk34mS72TJd5LkO1nL95EKjn+ZHH+mHD9fy3dZBfHyJN5UiTfNybd8pwXtDflOkvtgKkTUeL802FjuA2mSThGSKel8IOnUQgolnWZyPzlD4jeX+0kr2FbGP/aAZ8s4x7Zwtp0nub46yHWUAR+Q8Y4vwG7wAOyuz4/0TujnjEyph97ynNFHi1ck8eIrWQupDtTXQiquIN5EiZcj8XK1eKUV5LO/xBsg+RyoxTvyzsmtYWW9GzreYol3pcRbIvEOIekSb7PEq48ckHg9XF77yIRNYW+5/vvADNgP9rDLIffjwXA0HALHw3HwYjgUTofD4GwJnwNHSDs+Fl4h4YthNlwKL5D2fRS8R/SKRe9+eCF8WLbXw77wMdm2y5fuvO9j9zKe3KWtW8z5cvTiw9RLr0RvdBXXioqsExVZJ+pU1onK2RZZKyqyVtRPt1bUIcYyn0Dqd2SdDmQ0UojchZQiR5DoTh4rHclGCpFVyDPIEcTqzDpRSBZSiBQje5CPkPgMj5WBTECWI+uQUuRwRmT8dOQX+UV+kV/kF/lFfj//3082/j+3sPB0jf/PSLYcP67lrmBf0zWkXbS73B+k9+jRIwf1GTOawdBzFsz2+qC/p/wsyNQ8q9yvmDghfE4lPZcaO7XN++5vncPOuNgYvf/b8ZsOUd1+/cV2HpIlD7qPyyoZp56DuJCJSHE6Yi7TvDyGN9k+9sMH9VNlW9jYKZupLKQT2B+Om4O5PxzdAF8S0p1XeEVBnmWex1BPu168rT8lt5AzGzRe05iP/LzZkm6SppsUoPuOYUzcJ2p/XbU/Q+3H2LTxBRvV/lHMfeZyfEbmJXrHQZ3LQX4fhp+n77xRv3LeAvr5pR7FX0TCnPpyxhnWiydc6oUwyiq6Un7dFg6LI8T9Kpx6QB7AFtL3VGwLI/oMDrQFZzxQCxX3TqszKS61PEYbIX2nvkeoa4X6NNsIulWzkfQ94dtI+p7wbQRdzUaC/V3bqP2rrHb8ezVij+O5i2utFXV8Hom4z48dGNuSwatxMeID7LWLAQHj6F6u67WbLsR5qW7ldmP7qj66x/FVrdCOqGvCqOvTbEe+TKlziMxA1mNHZZXYUeGiwrDalLJyGyBzYgPijO67Br9UOmOtniHG5pUFnWtVYKMN6bqf1FV+k1cU5s032lBZFWxIdI3tSH1o7fWWoZMVpdnZbFUxtaWcw2wdcpmKvdiX7+sJXntZHV5b0ydUW5Oiz8eq169uJ1JnPhuhbghTdWO0Ed0HNLqmNwMXyHfjbGRDOnnfa7IRNepFGZ/UQ/D9VMVLMNkLaYbvk1W0t2rti56221Nx+6LrZnlnvCicVVBus3eq/V0Zbe2R84vvoQpzq/bDQwaLYriXJ3FsjxVbjWGAFFaNze1O+BKkKwejTYlz17aCxljZ4mtruiWbx+V6QtyHqPMQ9yHqMoz2g7qR9sO/rSit6T+uMBZ5zG4rQtvBHO/oPiukLRxXcWuYbIF0Kx2L0sdcbn/7PSRzaTSQSPWRL5rwzwsh861qJFSePS+EtF/SDN9+0XWeHfdQtytixSbqxJTbQxWfHSs793q9LJKx8pkcyA7oCR+ynyGM9cK8zB2N17Xjs9s=
*/