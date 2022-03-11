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

   splaydown_assemble_and_fix_header(node_ptr t, node_ptr header, node_ptr leftmost, node_ptr rightmost)
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

   void assemble()
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
   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const const_node_ptr&)
   static node_ptr get_header(const const_node_ptr & n);

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const const_node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const const_node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(const node_ptr & header1, const node_ptr & header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink(node_ptr)
   static void unlink(node_ptr node);

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
   //! Additional notes: the previous node of z is splayed to speed up range deletions.
   static void erase(node_ptr header, node_ptr z)
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
   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const const_node_ptr&,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(const node_ptr&,Disposer)
   template<class Disposer>
   static void clear_and_dispose(node_ptr header, Disposer disposer);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::count(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::lower_bound(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::upper_bound(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const const_node_ptr&, const KeyType&,KeyNodePtrCompare)
   //! Additional notes: the found node of the lower bound is splayed.
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {
      splay_down(detail::uncast(header), key, comp);
      return bstree_algo::find(header, key, comp);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const const_node_ptr&, const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::find(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::equal_range(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   //! Additional note: no splaying is performed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> lower_bound_range
      (const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp)
   {  return bstree_algo::lower_bound_range(header, key, comp);  }

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const const_node_ptr&,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const const_node_ptr&,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
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
      (node_ptr header, node_ptr pos, node_ptr new_node)
   {
      bstree_algo::insert_before(header, pos, new_node);
      splay_up(new_node, header);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   //! Additional note: the inserted node is splayed
   static void push_back(node_ptr header, node_ptr new_node)
   {
      bstree_algo::push_back(header, new_node);
      splay_up(new_node, header);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   //! Additional note: the inserted node is splayed
   static void push_front(node_ptr header, node_ptr new_node)
   {
      bstree_algo::push_front(header, new_node);
      splay_up(new_node, header);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   //! Additional note: nodes with the given key are splayed
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (node_ptr header, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data)
   {
      splay_down(header, key, comp);
      return bstree_algo::insert_unique_check(header, key, comp, commit_data);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
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
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p);

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance
   static void rebalance(node_ptr header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::rebalance_subtree
   static node_ptr rebalance_subtree(node_ptr old_root);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   // bottom-up splay, use data_ as parent for n    | complexity : logarithmic    | exception : nothrow
   static void splay_up(node_ptr node, node_ptr header)
   {  priv_splay_up<true>(node, header); }

   // top-down splay | complexity : logarithmic    | exception : strong, note A
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr splay_down(node_ptr header, const KeyType &key, KeyNodePtrCompare comp, bool *pfound = 0)
   {  return priv_splay_down<true>(header, key, comp, pfound);   }

   private:

   /// @cond

   // bottom-up splay, use data_ as parent for n    | complexity : logarithmic    | exception : nothrow
   template<bool SimpleSplay>
   static void priv_splay_up(node_ptr node, node_ptr header)
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
   static void link_left(node_ptr & t, node_ptr & l)
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
   static void link_right(node_ptr & t, node_ptr & r)
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
   static void rotate(node_ptr n)
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