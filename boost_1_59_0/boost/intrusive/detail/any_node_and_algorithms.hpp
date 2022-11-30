/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_ANY_NODE_HPP
#define BOOST_INTRUSIVE_ANY_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <cstddef>

namespace boost {
namespace intrusive {

template<class VoidPointer>
struct any_node
{
   typedef any_node                                               node;
   typedef typename pointer_rebind<VoidPointer, node>::type       node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type const_node_ptr;
   node_ptr    node_ptr_1;
   node_ptr    node_ptr_2;
   node_ptr    node_ptr_3;
   std::size_t size_t_1;
};

template<class VoidPointer>
struct any_list_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const_node_ptr n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->node_ptr_1 = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const_node_ptr n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_previous(node_ptr n, node_ptr prev)
   {  n->node_ptr_2 = prev;  }
};


template<class VoidPointer>
struct any_slist_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const_node_ptr n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->node_ptr_1 = next;  }
};


template<class VoidPointer>
struct any_unordered_node_traits
   :  public any_slist_node_traits<VoidPointer>
{
   typedef any_slist_node_traits<VoidPointer>                  reduced_slist_node_traits;
   typedef typename reduced_slist_node_traits::node            node;
   typedef typename reduced_slist_node_traits::node_ptr        node_ptr;
   typedef typename reduced_slist_node_traits::const_node_ptr  const_node_ptr;

   static const bool store_hash        = true;
   static const bool optimize_multikey = true;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const_node_ptr n)
   {  return n->node_ptr_1;   }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->node_ptr_1 = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_prev_in_group(const_node_ptr n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_prev_in_group(node_ptr n, node_ptr prev)
   {  n->node_ptr_2 = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_hash(const_node_ptr n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_hash(node_ptr n, std::size_t h)
   {  n->size_t_1 = h;  }
};


template<class VoidPointer>
struct any_rbtree_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef std::size_t color;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const_node_ptr n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const_node_ptr n)
   {  return n->node_ptr_3;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->node_ptr_3 = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const_node_ptr n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(node_ptr n, color c)
   {  n->size_t_1 = c;  }

   BOOST_INTRUSIVE_FORCEINLINE static color black()
   {  return 0u;  }

   BOOST_INTRUSIVE_FORCEINLINE static color red()
   {  return 1u;  }
};


template<class VoidPointer>
struct any_avltree_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef std::size_t balance;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const_node_ptr n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const_node_ptr n)
   {  return n->node_ptr_3;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->node_ptr_3 = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const_node_ptr n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(node_ptr n, balance b)
   {  n->size_t_1 = b;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance negative()
   {  return 0u;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance zero()
   {  return 1u;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance positive()
   {  return 2u;  }
};


template<class VoidPointer>
struct any_tree_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const_node_ptr n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const_node_ptr n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const_node_ptr n)
   {  return n->node_ptr_3;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->node_ptr_3 = r;  }
};

template<class VoidPointer>
class any_node_traits
{
   public:
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;
};

template<class VoidPointer>
class any_algorithms
{
   template <class T>
   static void function_not_available_for_any_hooks(typename detail::enable_if<detail::is_same<T, bool> >::type)
   {}

   public:
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;
   typedef any_node_traits<VoidPointer>   node_traits;

   //! <b>Requires</b>: node must not be part of any tree.
   //!
   //! <b>Effects</b>: After the function unique(node) == true.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Nodes</b>: If node is inserted in a tree, this function corrupts the tree.
   BOOST_INTRUSIVE_FORCEINLINE static void init(node_ptr node) BOOST_NOEXCEPT
   {  node->node_ptr_1 = node_ptr();   };

   //! <b>Effects</b>: Returns true if node is in the same state as if called init(node)
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const_node_ptr node)
   {  return !node->node_ptr_1;  };

   BOOST_INTRUSIVE_FORCEINLINE static bool unique(const_node_ptr node) BOOST_NOEXCEPT
   {  return !node->node_ptr_1; }

   static void unlink(node_ptr)
   {
      //Auto-unlink hooks and unlink() are not available for any hooks
      any_algorithms<VoidPointer>::template function_not_available_for_any_hooks<node_ptr>();
   }

   static void swap_nodes(node_ptr, node_ptr)
   {
      //Any nodes have no swap_nodes capability because they don't know
      //what algorithm they must use to unlink the node from the container
      any_algorithms<VoidPointer>::template function_not_available_for_any_hooks<node_ptr>();
   }
};

///@cond

template<class NodeTraits>
struct get_algo<AnyAlgorithm, NodeTraits>
{
   typedef typename pointer_rebind<typename NodeTraits::node_ptr, void>::type void_pointer;
   typedef any_algorithms<void_pointer> type;
};

///@endcond

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_ANY_NODE_HPP

/* any_node_and_algorithms.hpp
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
*/