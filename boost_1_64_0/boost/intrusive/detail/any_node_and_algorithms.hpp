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
NqBwlcfdeD2Szo446ZTHT4eT+iaPy3Qi7+f3xkmnsp90NtRu2eY2rYhNFSnmtIKJ0tpEMbhMJ2LTwTjphPpLxzLKZVoRm0pSzWm1xkkr2FS/raql1spCV+kcB3f+G9/5+Wd/AzCg5pO+/eSeBdVbjl365pKjd57z2nmP/u++C/TverdnqObJ7GfFMr+VDh1O8A7JiJh3SMoNcqZ3ZEbEvCNTGVcOFLnTRO50TS6YQG6yyBWL3BRNLpRAbobInSlyM/V3QhLI+UUuW+RywEWp7p6hu537k+fixmfi5ufhfc/Al0Py3Ft/5i3Pu93NDz4OxjzL5jm2/vza+dx6FxT9vDr2WbXzOfUiqFLmE+V5tMwp2s+e7WfOvVDxhf0/Z94FmuYa9xK+DzrB8SHQ8OxYnhsbnhknmI88rs9Jmp8Jy/Pg2GfBCZ8DyzNg0/Nffb7S9Jx3YM94n1vqbj6zDNTnNPVntm2QZx26gtNB/Zms/jy25Kw0TwUUgvZBh6GM0uE50OHf8G/4N/z7b/mlQdf+S8b/c63h/6DH/pO1sX+ZjCu3Q17oeugm4i79Wd9Y78q1q9dcpB7h81dd1VKv3gIIfyt/RaFaj9KCvGmdi8TjVbzZfotXDX7Vt/HHc/0cdb3Jcw3/hrUvBvlgVUudYe2LxpsD71vCbyY0Nm7eGuTA/o7/csVzKe/JnkKchHF2twpLIeTq7HR4iolwCnQqNNU+do6h02LGtjmyNsbKk3GSJ5H1MehOmNhOmC8SJvbo4+9FqfZ7u+pXAV1ImXQ5yqRZH4UTT7OrMulKkE/5kk/dimeRJ5P/AlZknUrejEyQN+ku1g458uf/ZD6gRc0HpL31zj+f9aXb6j7Z9r0bn/r16J8Mzwf8J88H7Iz0J9I3Hta/lSjjci84HcyU8fNEGT9PBkvAebIm53ywFLxc1uRcId8Cqpc1Jg3gAvA6WWPyVnA+eL2Ey7dDpd3SL4g+PqghZhyeC+aAeWA+OA4skHmACWA+eAZYAC4AJ4CLZX5iFXgKeKXMH1SIXMnweH54PD88nu93PD+Psfv64fH78G/4N/wb/v3f/P5lz/+rrwsO1fP/07T3930p/GnfR50JVeHEtj4VvW9udV1t9eYNzVvrW2o3yvhf9k6vbmowjjUlDhm/r1O8wc1x9nuC17xnlj7GFx57/C/7m/Brrr9mywa1AcUYGcN+WvGO5fzq7BTOFxF4uot9QHKi9mTHNm0cv06FYYOE+RLsm9Uj+TpeIs+3ZCizrph8pVi1fYirTPkoMl6Nb6MpD+HT9/Tg52JcHr1XcJU6z7DPN0btg7JP5ibKpTxWi029MTZdV9VSzbRGv3b1urRL+PqdgxmILR7ZS/8A5IW+AP2WBCu/12fLqiWXX6QKSGx5KDtsSyF1rICwWsX7COMkZpWgz0AGOyVOrxbHRjXXkse1Xera7Z4iWnMIpQz22/Jj7PreVAva8zU3qOurKJOJnnlIFMrc1rtVeKtnAu1gNlpexdVIe/hbNmSoHz5Ifiv0PEVvPU85d+Zpnrw08m6p79uhkPWOz/dj8rSuqjlSP6bLPjljZE7wWsU7w5SPxKP3EZIP2vzel9X1QnQaqXjS1P6C19VE+pwXX3/9dbXuSOy/HXqP5EGBuV4ty1Z6Lsw+iew4Yo/kx3RtDxwrXtLinLRi9jdqkT36n4SKoEclTzxdhjzZ0NhQE5MvOVJPChX/A5yPNeUN8ZnzplDy9TR1/SPI+pk3GM+anVTVf765IJxHG9SUHHFK3Z6q+PeSk9kqzp3+6Lw8hs2nk5cZnJ8xLpyf08GjKDsDPBOaCZVIn5un17EB5q+VFulr+avt1Zkl+zB4iUewcTIHP7A=
*/