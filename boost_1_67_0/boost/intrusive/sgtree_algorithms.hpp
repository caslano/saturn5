/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//
// Scapegoat tree algorithms are taken from the paper titled:
// "Scapegoat Trees" by Igal Galperin Ronald L. Rivest.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <cstddef>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! sgtree_algorithms is configured with a NodeTraits class, which encapsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the binary search tree
//!
//! <tt>node_ptr</tt>: A pointer to a node
//!
//! <tt>const_node_ptr</tt>: A pointer to a const node
//!
//! <b>Static functions</b>:
//!
//! <tt>static node_ptr get_parent(const_node_ptr n);</tt>
//!
//! <tt>static void set_parent(node_ptr n, node_ptr parent);</tt>
//!
//! <tt>static node_ptr get_left(const_node_ptr n);</tt>
//!
//! <tt>static void set_left(node_ptr n, node_ptr left);</tt>
//!
//! <tt>static node_ptr get_right(const_node_ptr n);</tt>
//!
//! <tt>static void set_right(node_ptr n, node_ptr right);</tt>
template<class NodeTraits>
class sgtree_algorithms
   #ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_algorithms<NodeTraits>
   #endif
{
   public:
   typedef typename NodeTraits::node            node;
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node_ptr       node_ptr;
   typedef typename NodeTraits::const_node_ptr const_node_ptr;

   /// @cond
   private:

   typedef bstree_algorithms<NodeTraits>  bstree_algo;

   /// @endcond

   public:
   //! This type is the information that will be
   //! filled by insert_unique_check
   struct insert_commit_data
      : bstree_algo::insert_commit_data
   {
      std::size_t depth;
   };

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const const_node_ptr&)
   static node_ptr get_header(const_node_ptr n);

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node);

   //Unlink is not possible since tree metadata is needed to update the tree
   //!static void unlink(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink_leftmost_without_rebalance
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const const_node_ptr&)
   static bool unique(const_node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const const_node_ptr&)
   static std::size_t size(const_node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(const node_ptr&)
   static node_ptr next_node(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(const node_ptr&)
   static node_ptr prev_node(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(node_ptr node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   static void init_header(node_ptr header);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::erase(node_ptr,node_ptr)
   template<class AlphaByMaxSize>
   static node_ptr erase(node_ptr header, node_ptr z, std::size_t tree_size, std::size_t &max_tree_size, AlphaByMaxSize alpha_by_maxsize)
   {
      bstree_algo::erase(header, z);
      --tree_size;
      if (tree_size > 0 &&
          tree_size < alpha_by_maxsize(max_tree_size)){
         bstree_algo::rebalance(header);
         max_tree_size = tree_size;
      }
      return z;
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const const_node_ptr&,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(const node_ptr&,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const const_node_ptr&, const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const const_node_ptr&,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const_node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count(const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_upper_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal_upper_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal_upper_bound(h, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_lower_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal_lower_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal_lower_bound(h, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal(node_ptr,node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare, class H_Alpha>
   static node_ptr insert_equal
      (node_ptr header, node_ptr hint, node_ptr new_node, NodePtrCompare comp
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_equal(header, hint, new_node, comp, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_before(node_ptr,node_ptr,node_ptr)
   template<class H_Alpha>
   static node_ptr insert_before
      (node_ptr header, node_ptr pos, node_ptr new_node
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::insert_before(header, pos, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   template<class H_Alpha>
   static void push_back(node_ptr header, node_ptr new_node
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::push_back(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   template<class H_Alpha>
   static void push_front(node_ptr header, node_ptr new_node
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      std::size_t depth;
      bstree_algo::push_front(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check(header, key, comp, commit_data, &depth);
      commit_data.depth = depth;
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header, node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      std::pair<node_ptr, bool> ret =
         bstree_algo::insert_unique_check
            (header, hint, key, comp, commit_data, &depth);
      commit_data.depth = depth;
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_commit(node_ptr,node_ptr,const insert_commit_data&)
   template<class H_Alpha>
   BOOST_INTRUSIVE_FORCEINLINE static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {  return insert_commit(header, new_value, commit_data, tree_size, h_alpha, max_tree_size);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_unique
   template<class NodePtrCompare, class H_Alpha, class AlphaByMaxSize>
   static bool transfer_unique
      ( node_ptr header1, NodePtrCompare comp, std::size_t tree1_size, std::size_t &max_tree1_size
      , node_ptr header2, node_ptr z,   std::size_t tree2_size, std::size_t &max_tree2_size
      ,H_Alpha h_alpha, AlphaByMaxSize alpha_by_maxsize)
   {
      insert_commit_data commit_data;
      bool const transferable = insert_unique_check(header1, z, comp, commit_data).second;
      if(transferable){
         erase(header2, z, tree2_size, max_tree2_size, alpha_by_maxsize);
         insert_commit(header1, z, commit_data, tree1_size, h_alpha, max_tree1_size);
      }
      return transferable;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_equal
   template<class NodePtrCompare, class H_Alpha, class AlphaByMaxSize>
   static void transfer_equal
      ( node_ptr header1, NodePtrCompare comp, std::size_t tree1_size, std::size_t &max_tree1_size
      , node_ptr header2, node_ptr z,   std::size_t tree2_size, std::size_t &max_tree2_size
      ,H_Alpha h_alpha, AlphaByMaxSize alpha_by_maxsize)
   {
      insert_commit_data commit_data;
      insert_equal_upper_bound_check(header1, z, comp, commit_data);
      erase(header2, z, tree2_size, max_tree2_size, alpha_by_maxsize);
      insert_commit(header1, z, commit_data, tree1_size, h_alpha, max_tree1_size);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p);

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static void rebalance(node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance_subtree
   static node_ptr rebalance_subtree(node_ptr old_root)
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   /// @cond
   private:

   template<class KeyType, class KeyNodePtrCompare>
   static void insert_equal_upper_bound_check
      (node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      std::size_t depth;
      bstree_algo::insert_equal_upper_bound_check(header, key, comp, commit_data, &depth);
      commit_data.depth = depth;
   }

   template<class H_Alpha>
   static void insert_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      bstree_algo::insert_unique_commit(header, new_value, commit_data);
      rebalance_after_insertion(new_value, commit_data.depth, tree_size+1, h_alpha, max_tree_size);
   }

   template<class H_Alpha>
   static void rebalance_after_insertion
      (node_ptr x, std::size_t depth
      , std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size)
   {
      if(tree_size > max_tree_size)
         max_tree_size = tree_size;

      if(tree_size > 2 && //Nothing to do with only the root
         //Check if the root node is unbalanced
         //Scapegoat paper depth counts root depth as zero and "depth" counts root as 1,
         //but since "depth" is the depth of the ancestor of x, i == depth
         depth > h_alpha(tree_size)){

         //Find the first non height-balanced node
         //as described in the section 4.2 of the paper.
         //This method is the alternative method described
         //in the paper. Authors claim that this method
         //may tend to yield more balanced trees on the average
         //than the weight balanced method.
         node_ptr s = x;
         std::size_t size = 1;
         for(std::size_t ancestor = 1; ancestor != depth; ++ancestor){
            const node_ptr s_parent = NodeTraits::get_parent(s);
            const node_ptr s_parent_left = NodeTraits::get_left(s_parent);
            //Obtain parent's size (previous size + parent + sibling tree)
            const node_ptr s_sibling = s_parent_left == s ? NodeTraits::get_right(s_parent) : s_parent_left;
            size += 1 + bstree_algo::subtree_size(s_sibling);
            s = s_parent;
            if(ancestor > h_alpha(size)){ //is 's' scapegoat?
               bstree_algo::rebalance_subtree(s);
               return;
            }
         }
         //The whole tree must be rebuilt
         max_tree_size = tree_size;
         bstree_algo::rebalance_subtree(NodeTraits::get_parent(s));
      }
   }
   /// @endcond
};

/// @cond

template<class NodeTraits>
struct get_algo<SgTreeAlgorithms, NodeTraits>
{
   typedef sgtree_algorithms<NodeTraits> type;
};

template <class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker<SgTreeAlgorithms, ValueTraits, NodePtrCompare, ExtraChecker>
{
   typedef detail::bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SGTREE_ALGORITHMS_HPP

/* sgtree_algorithms.hpp
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
*/