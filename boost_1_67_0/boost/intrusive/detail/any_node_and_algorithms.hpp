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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->node_ptr_1 = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const const_node_ptr & n)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->node_ptr_1;   }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->node_ptr_1 = next;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_prev_in_group(const const_node_ptr & n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_prev_in_group(node_ptr n, node_ptr prev)
   {  n->node_ptr_2 = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static std::size_t get_hash(const const_node_ptr & n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_hash(const node_ptr & n, std::size_t h)
   {  n->size_t_1 = h;  }
};


template<class VoidPointer>
struct any_rbtree_node_traits
{
   typedef any_node<VoidPointer>          node;
   typedef typename node::node_ptr        node_ptr;
   typedef typename node::const_node_ptr  const_node_ptr;

   typedef std::size_t color;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->node_ptr_3;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->node_ptr_3 = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static color get_color(const const_node_ptr & n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_color(const node_ptr & n, color c)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
   {  return n->node_ptr_3;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_right(node_ptr n, node_ptr r)
   {  n->node_ptr_3 = r;  }

   BOOST_INTRUSIVE_FORCEINLINE static balance get_balance(const const_node_ptr & n)
   {  return n->size_t_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_balance(const node_ptr & n, balance b)
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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_parent(const const_node_ptr & n)
   {  return n->node_ptr_1;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_parent(node_ptr n, node_ptr p)
   {  n->node_ptr_1 = p;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_left(const const_node_ptr & n)
   {  return n->node_ptr_2;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_left(node_ptr n, node_ptr l)
   {  n->node_ptr_2 = l;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_right(const const_node_ptr & n)
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
   BOOST_INTRUSIVE_FORCEINLINE static void init(const node_ptr & node)
   {  node->node_ptr_1 = node_ptr();   };

   //! <b>Effects</b>: Returns true if node is in the same state as if called init(node)
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const const_node_ptr & node)
   {  return !node->node_ptr_1;  };

   BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr & node)
   {  return !node->node_ptr_1; }

   static void unlink(const node_ptr &)
   {
      //Auto-unlink hooks and unlink() are not available for any hooks
      any_algorithms<VoidPointer>::template function_not_available_for_any_hooks<node_ptr>();
   }

   static void swap_nodes(const node_ptr &, const node_ptr &)
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