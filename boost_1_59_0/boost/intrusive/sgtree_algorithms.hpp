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
   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const_node_ptr)
   static node_ptr get_header(const_node_ptr n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node) BOOST_NOEXCEPT;

   //Unlink is not possible since tree metadata is needed to update the tree
   //!static void unlink(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink_leftmost_without_rebalance
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const_node_ptr)
   static bool unique(const_node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const_node_ptr)
   static std::size_t size(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(node_ptr)
   static node_ptr next_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(node_ptr)
   static node_ptr prev_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   static void init_header(node_ptr header) BOOST_NOEXCEPT;
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::erase(node_ptr,node_ptr)
   template<class AlphaByMaxSize>
   static node_ptr erase(node_ptr header, node_ptr z, std::size_t tree_size, std::size_t &max_tree_size, AlphaByMaxSize alpha_by_maxsize)
   {
      bstree_algo::erase(header, z);
      --tree_size;
      if (tree_size > 0 &&
          tree_size < static_cast<std::size_t>(alpha_by_maxsize(max_tree_size))){
         bstree_algo::rebalance(header);
         max_tree_size = tree_size;
      }
      return z;
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const_node_ptr,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(node_ptr,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const_node_ptr, const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const_node_ptr,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const_node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const_node_ptr,const KeyType&,KeyNodePtrCompare)
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
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size) BOOST_NOEXCEPT
   {
      std::size_t depth;
      bstree_algo::push_back(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   template<class H_Alpha>
   static void push_front(node_ptr header, node_ptr new_node
         ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size) BOOST_NOEXCEPT
   {
      std::size_t depth;
      bstree_algo::push_front(header, new_node, &depth);
      rebalance_after_insertion(new_node, depth, tree_size+1, h_alpha, max_tree_size);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
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
   static bool is_header(const_node_ptr p) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static void rebalance(node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance_subtree
   static node_ptr rebalance_subtree(node_ptr old_root) BOOST_NOEXCEPT
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
      ,std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size) BOOST_NOEXCEPT
   {
      bstree_algo::insert_unique_commit(header, new_value, commit_data);
      rebalance_after_insertion(new_value, commit_data.depth, tree_size+1, h_alpha, max_tree_size);
   }

   template<class H_Alpha>
   static void rebalance_after_insertion
      (node_ptr x, std::size_t depth
      , std::size_t tree_size, H_Alpha h_alpha, std::size_t &max_tree_size) BOOST_NOEXCEPT
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