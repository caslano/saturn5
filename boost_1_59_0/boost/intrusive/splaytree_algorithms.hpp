/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2007-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
// The implementation of splay trees is based on the article and code published
// in C++ Users Journal "Implementing Splay Trees in C++" (September 1, 2005).
//
// The splay code has been modified and (supposedly) improved by Ion Gaztanaga.
//
// Here is the copyright notice of the original file containing the splay code:
//
//  splay_tree.h -- implementation of a STL compatible splay tree.
//
//  Copyright (c) 2004 Ralf Mattethat
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SPLAYTREE_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_SPLAYTREE_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/detail/uncast.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>

#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

/// @cond
namespace detail {

template<class NodeTraits>
struct splaydown_assemble_and_fix_header
{
   typedef typename NodeTraits::node_ptr node_ptr;

   splaydown_assemble_and_fix_header(node_ptr t, node_ptr header, node_ptr leftmost, node_ptr rightmost) BOOST_NOEXCEPT
      : t_(t)
      , null_node_(header)
      , l_(null_node_)
      , r_(null_node_)
      , leftmost_(leftmost)
      , rightmost_(rightmost)
   {}

   ~splaydown_assemble_and_fix_header()
   {
      this->assemble();

      //Now recover the original header except for the
      //splayed root node.
      //"t_" is the current root and "null_node_" is the header node
      NodeTraits::set_parent(null_node_, t_);
      NodeTraits::set_parent(t_, null_node_);
      //Recover leftmost/rightmost pointers
      NodeTraits::set_left (null_node_, leftmost_);
      NodeTraits::set_right(null_node_, rightmost_);
   }

   private:

   void assemble() BOOST_NOEXCEPT
   {
      //procedure assemble;
      //    left(r), right(l) := right(t), left(t);
      //    left(t), right(t) := right(null), left(null);
      //end assemble;
      {  //    left(r), right(l) := right(t), left(t);

         node_ptr const old_t_left  = NodeTraits::get_left(t_);
         node_ptr const old_t_right = NodeTraits::get_right(t_);
         NodeTraits::set_right(l_, old_t_left);
         NodeTraits::set_left (r_, old_t_right);
         if(old_t_left){
            NodeTraits::set_parent(old_t_left, l_);
         }
         if(old_t_right){
            NodeTraits::set_parent(old_t_right, r_);
         }
      }
      {  //    left(t), right(t) := right(null), left(null);
         node_ptr const null_right = NodeTraits::get_right(null_node_);
         node_ptr const null_left  = NodeTraits::get_left(null_node_);
         NodeTraits::set_left (t_, null_right);
         NodeTraits::set_right(t_, null_left);
         if(null_right){
            NodeTraits::set_parent(null_right, t_);
         }
         if(null_left){
            NodeTraits::set_parent(null_left, t_);
         }
      }
   }

   public:
   node_ptr t_, null_node_, l_, r_, leftmost_, rightmost_;
};

}  //namespace detail {
/// @endcond

//!   A splay tree is an implementation of a binary search tree. The tree is
//!   self balancing using the splay algorithm as described in
//!
//!      "Self-Adjusting Binary Search Trees
//!      by Daniel Dominic Sleator and Robert Endre Tarjan
//!      AT&T Bell Laboratories, Murray Hill, NJ
//!      Journal of the ACM, Vol 32, no 3, July 1985, pp 652-686
//!
//! splaytree_algorithms is configured with a NodeTraits class, which encapsulates the
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
class splaytree_algorithms
   #ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_algorithms<NodeTraits>
   #endif
{
   /// @cond
   private:
   typedef bstree_algorithms<NodeTraits> bstree_algo;
   /// @endcond

   public:
   typedef typename NodeTraits::node            node;
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;

   //! This type is the information that will be
   //! filled by insert_unique_check
   typedef typename bstree_algo::insert_commit_data insert_commit_data;

   public:
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const_node_ptr)
   static node_ptr get_header(const_node_ptr n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink(node_ptr)
   static void unlink(node_ptr node) BOOST_NOEXCEPT;

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
   //! Additional notes: the previous node of z is splayed to speed up range deletions.
   static void erase(node_ptr header, node_ptr z) BOOST_NOEXCEPT
   {
      //posibility 1
      if(NodeTraits::get_left(z)){
         splay_up(bstree_algo::prev_node(z), header);
      }

      //possibility 2
      //if(NodeTraits::get_left(z)){
      //   node_ptr l = NodeTraits::get_left(z);
      //   splay_up(l, header);
      //}

      //if(NodeTraits::get_left(z)){
      //   node_ptr l = bstree_algo::prev_node(z);
      //   splay_up_impl(l, z);
      //}

      //possibility 4
      //splay_up(z, header);

      bstree_algo::erase(header, z);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_unique
   template<class NodePtrCompare>
   static bool transfer_unique
      (node_ptr header1, NodePtrCompare comp, node_ptr header2, node_ptr z)
   {
      typename bstree_algo::insert_commit_data commit_data;
      bool const transferable = bstree_algo::insert_unique_check(header1, z, comp, commit_data).second;
      if(transferable){
         erase(header2, z);
         bstree_algo::insert_commit(header1, z, commit_data);
         splay_up(z, header1);
      }
      return transferable;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_equal
   template<class NodePtrCompare>
   static void transfer_equal
      (node_ptr header1, NodePtrCompare comp, node_ptr header2, node_ptr z)
   {
      insert_commit_data commit_data;
      splay_down(header1, z, comp);
      bstree_algo::insert_equal_upper_bound_check(header1, z, comp, commit_data);
      erase(header2, z);
      bstree_algo::insert_commit(header1, z, commit_data);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const_node_ptr,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(node_ptr,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer) BOOST_NOEXCEPT;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional notes: an element with key `key` is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      std::pair<node_ptr, node_ptr> ret = equal_range(header, key, comp);
      std::size_t n = 0;
      while(ret.first != ret.second){
         ++n;
         ret.first = next_node(ret.first);
      }
      return n;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::count(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the first node of the range is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      node_ptr y = bstree_algo::lower_bound(header, key, comp);
      //splay_up(y, detail::uncast(header));
      return y;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::lower_bound(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the first node of the range is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      node_ptr y = bstree_algo::upper_bound(header, key, comp);
      //splay_up(y, detail::uncast(header));
      return y;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::upper_bound(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const_node_ptr, const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the found node of the lower bound is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      return bstree_algo::find(header, key, comp);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const_node_ptr, const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::find(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the first node of the range is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      std::pair<node_ptr, node_ptr> ret = bstree_algo::equal_range(header, key, comp);
      //splay_up(ret.first, detail::uncast(header));
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::equal_range(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the first node of the range is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> lower_bound_range
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      std::pair<node_ptr, node_ptr> ret = bstree_algo::lower_bound_range(header, key, comp);
      //splay_up(ret.first, detail::uncast(header));
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound_range(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> lower_bound_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::lower_bound_range(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const_node_ptr,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   //! Additional notes: the first node of the range is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed)
   {
      splay_down(detail::uncast(header), lower_key, comp);
      std::pair<node_ptr, node_ptr> ret =
         bstree_algo::bounded_range(header, lower_key, upper_key, comp, left_closed, right_closed);
      //splay_up(ret.first, detail::uncast(header));
      return ret;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const_node_ptr,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const_node_ptr header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed)
   {  return bstree_algo::bounded_range(header, lower_key, upper_key, comp, left_closed, right_closed);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_upper_bound(node_ptr,node_ptr,NodePtrCompare)
   //! Additional note: the inserted node is splayed
   template<class NodePtrCompare>
   static node_ptr insert_equal_upper_bound
      (node_ptr header, node_ptr new_node, NodePtrCompare comp)
   {
      splay_down(header, new_node, comp);
      return bstree_algo::insert_equal_upper_bound(header, new_node, comp);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_lower_bound(node_ptr,node_ptr,NodePtrCompare)
   //! Additional note: the inserted node is splayed
   template<class NodePtrCompare>
   static node_ptr insert_equal_lower_bound
      (node_ptr header, node_ptr new_node, NodePtrCompare comp)
   {
      splay_down(header, new_node, comp);
      return bstree_algo::insert_equal_lower_bound(header, new_node, comp);
   }  

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal(node_ptr,node_ptr,node_ptr,NodePtrCompare)
   //! Additional note: the inserted node is splayed
   template<class NodePtrCompare>
   static node_ptr insert_equal
      (node_ptr header, node_ptr hint, node_ptr new_node, NodePtrCompare comp)
   {
      splay_down(header, new_node, comp);
      return bstree_algo::insert_equal(header, hint, new_node, comp);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_before(node_ptr,node_ptr,node_ptr)
   //! Additional note: the inserted node is splayed
   static node_ptr insert_before
      (node_ptr header, node_ptr pos, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::insert_before(header, pos, new_node);
      splay_up(new_node, header);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   //! Additional note: the inserted node is splayed
   static void push_back(node_ptr header, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::push_back(header, new_node);
      splay_up(new_node, header);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   //! Additional note: the inserted node is splayed
   static void push_front(node_ptr header, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::push_front(header, new_node);
      splay_up(new_node, header);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   //! Additional note: nodes with the given key are splayed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (node_ptr header, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      splay_down(header, key, comp);
      return bstree_algo::insert_unique_check(header, key, comp, commit_data);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   //! Additional note: nodes with the given key are splayed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (node_ptr header, node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      splay_down(header, key, comp);
      return bstree_algo::insert_unique_check(header, hint, key, comp, commit_data);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_commit(node_ptr,node_ptr,const insert_commit_data&)
   static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance
   static void rebalance(node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance_subtree
   static node_ptr rebalance_subtree(node_ptr old_root) BOOST_NOEXCEPT;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   // bottom-up splay, use data_ as parent for n    | complexity : logarithmic    | exception : nothrow
   static void splay_up(node_ptr node, node_ptr header) BOOST_NOEXCEPT
   {  priv_splay_up<true>(node, header); }

   // top-down splay | complexity : logarithmic    | exception : strong, note A
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr splay_down(node_ptr header, const KeyType &key, KeyNodePtrCompare comp, bool *pfound = 0)
   {  return priv_splay_down<true>(header, key, comp, pfound);   }

   private:

   /// @cond

   // bottom-up splay, use data_ as parent for n    | complexity : logarithmic    | exception : nothrow
   template<bool SimpleSplay>
   static void priv_splay_up(node_ptr node, node_ptr header) BOOST_NOEXCEPT
   {
      // If (node == header) do a splay for the right most node instead
      // this is to boost performance of equal_range/count on equivalent containers in the case
      // where there are many equal elements at the end
      node_ptr n((node == header) ? NodeTraits::get_right(header) : node);
      node_ptr t(header);

      if( n == t ) return;

      for( ;; ){
         node_ptr p(NodeTraits::get_parent(n));
         node_ptr g(NodeTraits::get_parent(p));

         if( p == t )   break;

         if( g == t ){
            // zig
            rotate(n);
         }
         else if ((NodeTraits::get_left(p) == n && NodeTraits::get_left(g) == p)    ||
                  (NodeTraits::get_right(p) == n && NodeTraits::get_right(g) == p)  ){
            // zig-zig
            rotate(p);
            rotate(n);
         }
         else {
            // zig-zag
            rotate(n);
            if(!SimpleSplay){
               rotate(n);
            }
         }
      }
   }

   template<bool SimpleSplay, class KeyType, class KeyNodePtrCompare>
   static node_ptr priv_splay_down(node_ptr header, const KeyType &key, KeyNodePtrCompare comp, bool *pfound = 0)
   {
      //Most splay tree implementations use a dummy/null node to implement.
      //this function. This has some problems for a generic library like Intrusive:
      //
      // * The node might not have a default constructor.
      // * The default constructor could throw.
      //
      //We already have a header node. Leftmost and rightmost nodes of the tree
      //are not changed when splaying (because the invariants of the tree don't
      //change) We can back up them, use the header as the null node and
      //reassign old values after the function has been completed.
      node_ptr const old_root  = NodeTraits::get_parent(header);
      node_ptr const leftmost  = NodeTraits::get_left(header);
      node_ptr const rightmost = NodeTraits::get_right(header);
      if(leftmost == rightmost){ //Empty or unique node
         if(pfound){
            *pfound = old_root && !comp(key, old_root) && !comp(old_root, key);
         }
         return old_root ? old_root : header;
      }
      else{
         //Initialize "null node" (the header in our case)
         NodeTraits::set_left (header, node_ptr());
         NodeTraits::set_right(header, node_ptr());
         //Class that will backup leftmost/rightmost from header, commit the assemble(),
         //and will restore leftmost/rightmost to header even if "comp" throws
         detail::splaydown_assemble_and_fix_header<NodeTraits> commit(old_root, header, leftmost, rightmost);
         bool found = false;

         for( ;; ){
            if(comp(key, commit.t_)){
               node_ptr const t_left = NodeTraits::get_left(commit.t_);
               if(!t_left)
                  break;
               if(comp(key, t_left)){
                  bstree_algo::rotate_right_no_parent_fix(commit.t_, t_left);
                  commit.t_ = t_left;
                  if( !NodeTraits::get_left(commit.t_) )
                     break;
                  link_right(commit.t_, commit.r_);
               }
               else{
                  link_right(commit.t_, commit.r_);
                  if(!SimpleSplay && comp(t_left, key)){
                     if( !NodeTraits::get_right(commit.t_) )
                        break;
                     link_left(commit.t_, commit.l_);
                  }
               }
            }
            else if(comp(commit.t_, key)){
               node_ptr const t_right = NodeTraits::get_right(commit.t_);
               if(!t_right)
                  break;

               if(comp(t_right, key)){
                     bstree_algo::rotate_left_no_parent_fix(commit.t_, t_right);
                     commit.t_ = t_right;
                     if( !NodeTraits::get_right(commit.t_) )
                        break;
                     link_left(commit.t_, commit.l_);
               }
               else{
                  link_left(commit.t_, commit.l_);
                  if(!SimpleSplay && comp(key, t_right)){
                     if( !NodeTraits::get_left(commit.t_) )
                        break;
                     link_right(commit.t_, commit.r_);
                  }
               }
            }
            else{
               found = true;
               break;
            }
         }

         //commit.~splaydown_assemble_and_fix_header<NodeTraits>() will first
         //"assemble()" + link the new root & recover header's leftmost & rightmost
         if(pfound){
            *pfound = found;
         }
         return commit.t_;
      }
   }

   // break link to left child node and attach it to left tree pointed to by l   | complexity : constant | exception : nothrow
   static void link_left(node_ptr & t, node_ptr & l) BOOST_NOEXCEPT
   {
      //procedure link_left;
      //    t, l, right(l) := right(t), t, t
      //end link_left
      NodeTraits::set_right(l, t);
      NodeTraits::set_parent(t, l);
      l = t;
      t = NodeTraits::get_right(t);
   }

   // break link to right child node and attach it to right tree pointed to by r | complexity : constant | exception : nothrow
   static void link_right(node_ptr & t, node_ptr & r) BOOST_NOEXCEPT
   {
      //procedure link_right;
      //    t, r, left(r) := left(t), t, t
      //end link_right;
      NodeTraits::set_left(r, t);
      NodeTraits::set_parent(t, r);
      r = t;
      t = NodeTraits::get_left(t);
   }

   // rotate n with its parent                     | complexity : constant    | exception : nothrow
   static void rotate(node_ptr n) BOOST_NOEXCEPT
   {
      //procedure rotate_left;
      //    t, right(t), left(right(t)) := right(t), left(right(t)), t
      //end rotate_left;
      node_ptr p = NodeTraits::get_parent(n);
      node_ptr g = NodeTraits::get_parent(p);
      //Test if g is header before breaking tree
      //invariants that would make is_header invalid
      bool g_is_header = bstree_algo::is_header(g);

      if(NodeTraits::get_left(p) == n){
         NodeTraits::set_left(p, NodeTraits::get_right(n));
         if(NodeTraits::get_left(p))
            NodeTraits::set_parent(NodeTraits::get_left(p), p);
         NodeTraits::set_right(n, p);
      }
      else{ // must be ( p->right == n )
         NodeTraits::set_right(p, NodeTraits::get_left(n));
         if(NodeTraits::get_right(p))
            NodeTraits::set_parent(NodeTraits::get_right(p), p);
         NodeTraits::set_left(n, p);
      }

      NodeTraits::set_parent(p, n);
      NodeTraits::set_parent(n, g);

      if(g_is_header){
         if(NodeTraits::get_parent(g) == p)
            NodeTraits::set_parent(g, n);
         else{//must be ( g->right == p )
            BOOST_INTRUSIVE_INVARIANT_ASSERT(false);
            NodeTraits::set_right(g, n);
         }
      }
      else{
         if(NodeTraits::get_left(g) == p)
            NodeTraits::set_left(g, n);
         else  //must be ( g->right == p )
            NodeTraits::set_right(g, n);
      }
   }

   /// @endcond
};

/// @cond

template<class NodeTraits>
struct get_algo<SplayTreeAlgorithms, NodeTraits>
{
   typedef splaytree_algorithms<NodeTraits> type;
};

template <class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker<SplayTreeAlgorithms, ValueTraits, NodePtrCompare, ExtraChecker>
{
   typedef detail::bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_SPLAYTREE_ALGORITHMS_HPP

/* splaytree_algorithms.hpp
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
*/