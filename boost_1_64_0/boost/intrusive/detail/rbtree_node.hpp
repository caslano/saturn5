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

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const const_node_ptr & n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const node_ptr & n)
   {  return n->color_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(const node_ptr & n, color c)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const node_ptr & n)
   {  return ptr_bit::get_pointer(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  ptr_bit::set_pointer(n->parent_, p);  }

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

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const const_node_ptr & n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const node_ptr & n)
   {  return (color)ptr_bit::get_bits(n->parent_);  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(const node_ptr & n, color c)
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
DYda9giMjGEP+boJcQNsDTdCyTHWJvZ5Wym5VbAVXG3J5cXJ71LJrVV+63w5guQyHXIXS24ZND6vLbliyfVyyF0ouQWwJyyx5Koll+WQmyO5uTATzpNcIeGA5PIl15IwUnKDiGeeN2BbOBR2hcNgb1hg5X88jp3uU327X/X0s9b5rI2j9wzpPVN6z/LzUz8zyHXIjZXcONgFjrfPZxy58yU3UXKTLLnCOHJTJDdVckWW3ErJpTvkzpXcSNgJjrLPp+R6OOQWSW4x7A6XWHI1o2Kfh/6SO1v1dYAldziO3GU6f5fr/G2A/nmPI5em/Doov47QP++S6+CQ+7Pyewumwbet/Ori5LdQcouk52K73RgdW+5qyVVLbpcllx5H7nbJfVhyH7HvE3Hkessu+bJLH7vdkFwnh1yh8psMO8IpdnsvuYsd7f3HJLdfcp+AWfBemAPvhL3hJ2E/eEDt/F2wSPGmwU/BYngPLIGfhhfpuKfHcemxxKHHRdJjufS4RHqslR4rpMdK6bEKng9Xw8kmnnyc6X5TLn0uhYt1XHrwvTO2Pd6RHv+QHkQ0erSFOTCo9i0F9oMtYCFMhUWKNw22gsWwNSyBbeBFOv4GHOt9W4TdpYdZL1l6/EF6vAGz5QuuGzxllaNuTGx7TpP8TJVjluy5QPacLXteIHvOkT3nyp4LZM/5smex7Hmh7LnA0mPl2Nh6VEiPzdKjSnrslB5bpMdW6bFNerxHeuyUHu+VHldKjx3SY6ddv8bGPq/XSY8bpcdu6XGb9LhJetwsPd6ver4HFineNHiL8r9V9Xyv6vlt9vU2LrYenXV9Z8GOMFv1q6fqV47qVxfVr1zVr66wSPGmwe6qXz1Uv86CF5njVvs7LvZzxnmyxwSYAc+3fLjVjYvtw62EeOsafMA06vsF3xPN/l/+g/5fmn2//P/4fknW70uzz5dony8bduDrhXCI8BohbSf+WgjLCNcR7iEcJdQRsq5KDRQRKgn7CIcJrxHS3ocPGMISwk7CQcLzhNSrUwODCaWE7YR7CEcJdYTcamxOKCPsJtQQThBSd2FHQjFhO+EA4QjhJCH9mmZ/Mc1/p//3b5v/H3Jfb6b/n/78/9E5AX/dizLNY/+WnqWeJfwxPzRmw/S5TCspMfNn7CU1E1pPs14+qDUsTdw1MebS2HHVR1lVfoU1t3mSOf4E74ctTN9WXmr02o/aV2n3AS83cnfwHpNK2tZaL9YaGcUmzn2BK+iNGUo/Tzv2jckx640YjiUMyqhf62uc+vomZDespZfayFoGL+XYaxfEXtsxZKNs2aij1kGlTOyrDBvXsF9z+0v1DFlC+GvofHXx+gTN3MeppUvMebPn7Rkb/MKcC5aRiHXeukSO4VASsc6d4jes20i5rHM33hyfhf4N89IXYs9FMdY0tuw527Phqi7RNgyVI1vlCB8PIn0j+lKrU8PPUXvCO6RxIIbdNqxaW0WUhGxGGhHjsY24y17ETWzMi6OcEeOlTR7h83PUcTqXEJTv0r8jX+Mu48ayBMtXY5VvjdZGdF/Liqt5UtchPBadxudg905d/H7U17WOjBdnGXHOC8Vp2d6P87uwtaoarSv+9fZivLpirzejNfKifBq01jdms5+ECC36hMaYu2yoATsJ2rE+jaC1brjEXba04nf0xwitqagktndt5ZrjywPjZe+j2PFgK9qpDGyZNija3opzjDhjQ3Fadoiyd9PGGLXsXJKb2DU63zHuaLQ3FlIJV6j+biK0xPZ7o2xvev0jbc621l8y8dc7zoHSkr2KONcnCBNCda/NeN8Wp2QLL847hJrOxOnQzxoLEB4nr41ZW4M4uVFx8tkmSuAp0r0is94=
*/