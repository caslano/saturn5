/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2014.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//
// The tree destruction algorithm is based on Julienne Walker and The EC Team code:
//
// This code is in the public domain. Anyone may use it or change it in any way that
// they see fit. The author assumes no responsibility for damages incurred through
// use of the original code or any variations thereof.
//
// It is requested, but not required, that due credit is given to the original author
// and anyone who has modified the code through a header comment, such as this one.

#ifndef BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <cstddef>

#include <boost/intrusive/detail/assert.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/intrusive/bstree_algorithms.hpp>
#include <boost/intrusive/detail/ebo_functor_holder.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

template<class NodeTraits, class F>
struct rbtree_node_cloner
   //Use public inheritance to avoid MSVC bugs with closures
   :  public detail::ebo_functor_holder<F>
{
   typedef typename NodeTraits::node_ptr  node_ptr;
   typedef detail::ebo_functor_holder<F>  base_t;

   explicit rbtree_node_cloner(F f)
      :  base_t(f)
   {}

   node_ptr operator()(node_ptr p)
   {
      node_ptr n = base_t::get()(p);
      NodeTraits::set_color(n, NodeTraits::get_color(p));
      return n;
   }
};

namespace detail {

template<class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct rbtree_node_checker
   : public bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker>
{
   typedef bstree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> base_checker_t;
   typedef ValueTraits                             value_traits;
   typedef typename value_traits::node_traits      node_traits;
   typedef typename node_traits::const_node_ptr    const_node_ptr;
   typedef typename node_traits::node_ptr          node_ptr;

   struct return_type
         : public base_checker_t::return_type
   {
      return_type() : black_count_(0) {}
      std::size_t black_count_;
   };

   rbtree_node_checker(const NodePtrCompare& comp, ExtraChecker extra_checker)
      : base_checker_t(comp, extra_checker)
   {}

   void operator () (const_node_ptr p,
                     const return_type& check_return_left, const return_type& check_return_right,
                     return_type& check_return)
   {

      if (node_traits::get_color(p) == node_traits::red()){
         //Red nodes have black children
         const node_ptr p_left(node_traits::get_left(p));   (void)p_left;
         const node_ptr p_right(node_traits::get_right(p)); (void)p_right;
         BOOST_INTRUSIVE_INVARIANT_ASSERT(!p_left  || node_traits::get_color(p_left)  == node_traits::black());
         BOOST_INTRUSIVE_INVARIANT_ASSERT(!p_right || node_traits::get_color(p_right) == node_traits::black());
         //Red node can't be root
         BOOST_INTRUSIVE_INVARIANT_ASSERT(node_traits::get_parent(node_traits::get_parent(p)) != p);
      }
      //Every path to p contains the same number of black nodes
      const std::size_t l_black_count = check_return_left.black_count_;
      BOOST_INTRUSIVE_INVARIANT_ASSERT(l_black_count == check_return_right.black_count_);
      check_return.black_count_ = l_black_count +
         static_cast<std::size_t>(node_traits::get_color(p) == node_traits::black());
      base_checker_t::operator()(p, check_return_left, check_return_right, check_return);
   }
};

} // namespace detail

#endif   //#ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED

//! rbtree_algorithms provides basic algorithms to manipulate
//! nodes forming a red-black tree. The insertion and deletion algorithms are
//! based on those in Cormen, Leiserson, and Rivest, Introduction to Algorithms
//! (MIT Press, 1990), except that
//!
//! (1) the header node is maintained with links not only to the root
//! but also to the leftmost node of the tree, to enable constant time
//! begin(), and to the rightmost node of the tree, to enable linear time
//! performance when used with the generic set algorithms (set_union,
//! etc.);
//!
//! (2) when a node being deleted has two children its successor node is
//! relinked into its place, rather than copied, so that the only
//! pointers invalidated are those referring to the deleted node.
//!
//! rbtree_algorithms is configured with a NodeTraits class, which encapsulates the
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
//! <tt>color</tt>: The type that can store the color of a node
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
//!
//! <tt>static color get_color(const_node_ptr n);</tt>
//!
//! <tt>static void set_color(node_ptr n, color c);</tt>
//!
//! <tt>static color black();</tt>
//!
//! <tt>static color red();</tt>
template<class NodeTraits>
class rbtree_algorithms
   #ifndef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   : public bstree_algorithms<NodeTraits>
   #endif
{
   public:
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef typename NodeTraits::color           color;

   /// @cond
   private:

   typedef bstree_algorithms<NodeTraits>  bstree_algo;

   /// @endcond

   public:

   //! This type is the information that will be
   //! filled by insert_unique_check
   typedef typename bstree_algo::insert_commit_data insert_commit_data;

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const_node_ptr)
   static node_ptr get_header(const_node_ptr n) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2) BOOST_NOEXCEPT;

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2) BOOST_NOEXCEPT
   {
      if(node1 == node2)
         return;

      node_ptr header1(bstree_algo::get_header(node1)), header2(bstree_algo::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2) BOOST_NOEXCEPT
   {
      if(node1 == node2)   return;

      bstree_algo::swap_nodes(node1, header1, node2, header2);
      //Swap color
      color c = NodeTraits::get_color(node1);
      NodeTraits::set_color(node1, NodeTraits::get_color(node2));
      NodeTraits::set_color(node2, c);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node) BOOST_NOEXCEPT
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, bstree_algo::get_header(node_to_be_replaced), new_node);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::replace_node(node_to_be_replaced, header, new_node);
      NodeTraits::set_color(new_node, NodeTraits::get_color(node_to_be_replaced));
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink(node_ptr)
   static void unlink(node_ptr node) BOOST_NOEXCEPT
   {
      node_ptr x = NodeTraits::get_parent(node);
      if(x){
         while(!is_header(x))
            x = NodeTraits::get_parent(x);
         erase(x, node);
      }
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink_leftmost_without_rebalance
   static node_ptr unlink_leftmost_without_rebalance(node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const_node_ptr)
   static bool unique(const_node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const_node_ptr)
   static std::size_t size(const_node_ptr header) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(const_node_ptr)
   static node_ptr next_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(const_node_ptr)
   static node_ptr prev_node(node_ptr node) BOOST_NOEXCEPT;

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(node_ptr node) BOOST_NOEXCEPT;
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   static void init_header(node_ptr header) BOOST_NOEXCEPT
   {
      bstree_algo::init_header(header);
      NodeTraits::set_color(header, NodeTraits::red());
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::erase(node_ptr,node_ptr)
   static node_ptr erase(node_ptr header, node_ptr z) BOOST_NOEXCEPT
   {
      typename bstree_algo::data_for_rebalance info;
      bstree_algo::erase(header, z, info);
      rebalance_after_erasure(header, z, info);
      return z;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_unique
   template<class NodePtrCompare>
   static bool transfer_unique
      (node_ptr header1, NodePtrCompare comp, node_ptr header2, node_ptr z)
   {
      typename bstree_algo::data_for_rebalance info;
      bool const transferred = bstree_algo::transfer_unique(header1, comp, header2, z, info);
      if(transferred){
         rebalance_after_erasure(header2, z, info);
         rebalance_after_insertion(header1, z);
      }
      return transferred;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::transfer_equal
   template<class NodePtrCompare>
   static void transfer_equal
      (node_ptr header1, NodePtrCompare comp, node_ptr header2, node_ptr z)
   {
      typename bstree_algo::data_for_rebalance info;
      bstree_algo::transfer_equal(header1, comp, header2, z, info);
      rebalance_after_erasure(header2, z, info);
      rebalance_after_insertion(header1, z);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const_node_ptr,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer)
   {
      rbtree_node_cloner<NodeTraits, Cloner> new_cloner(cloner);
      bstree_algo::clone(source_header, target_header, new_cloner, disposer);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(const_node_ptr,Disposer)
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
      (const_node_ptr eader, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const_node_ptr,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count(const_node_ptr header, const KeyType &key, KeyNodePtrCompare comp);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_upper_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare>
   static node_ptr insert_equal_upper_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp)
   {
      bstree_algo::insert_equal_upper_bound(h, new_node, comp);
      rebalance_after_insertion(h, new_node);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal_lower_bound(node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare>
   static node_ptr insert_equal_lower_bound
      (node_ptr h, node_ptr new_node, NodePtrCompare comp)
   {
      bstree_algo::insert_equal_lower_bound(h, new_node, comp);
      rebalance_after_insertion(h, new_node);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_equal(node_ptr,node_ptr,node_ptr,NodePtrCompare)
   template<class NodePtrCompare>
   static node_ptr insert_equal
      (node_ptr header, node_ptr hint, node_ptr new_node, NodePtrCompare comp)
   {
      bstree_algo::insert_equal(header, hint, new_node, comp);
      rebalance_after_insertion(header, new_node);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_before(node_ptr,node_ptr,node_ptr)
   static node_ptr insert_before
      (node_ptr header, node_ptr pos, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::insert_before(header, pos, new_node);
      rebalance_after_insertion(header, new_node);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   static void push_back(node_ptr header, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::push_back(header, new_node);
      rebalance_after_insertion(header, new_node);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   static void push_front(node_ptr header, node_ptr new_node) BOOST_NOEXCEPT
   {
      bstree_algo::push_front(header, new_node);
      rebalance_after_insertion(header, new_node);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const_node_ptr,const_node_ptr,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header, node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_commit(node_ptr,node_ptr,const insert_commit_data&)
   static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data) BOOST_NOEXCEPT
   {
      bstree_algo::insert_unique_commit(header, new_value, commit_data);
      rebalance_after_insertion(header, new_value);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const_node_ptr p) BOOST_NOEXCEPT
   {
      return NodeTraits::get_color(p) == NodeTraits::red() &&
            bstree_algo::is_header(p);
   }

   /// @cond
   private:

   static void rebalance_after_erasure
      ( node_ptr header, node_ptr z, const typename bstree_algo::data_for_rebalance &info) BOOST_NOEXCEPT
   {
      color new_z_color;
      if(info.y != z){
         new_z_color = NodeTraits::get_color(info.y);
         NodeTraits::set_color(info.y, NodeTraits::get_color(z));
      }
      else{
         new_z_color = NodeTraits::get_color(z);
      }
      //Rebalance rbtree if needed
      if(new_z_color != NodeTraits::red()){
         rebalance_after_erasure_restore_invariants(header, info.x, info.x_parent);
      }
   }

   static void rebalance_after_erasure_restore_invariants(node_ptr header, node_ptr x, node_ptr x_parent) BOOST_NOEXCEPT
   {
      while(1){
         if(x_parent == header || (x && NodeTraits::get_color(x) != NodeTraits::black())){
            break;
         }
         //Don't cache x_is_leftchild or similar because x can be null and
         //equal to both x_parent_left and x_parent_right
         const node_ptr x_parent_left(NodeTraits::get_left(x_parent));
         if(x == x_parent_left){ //x is left child
            node_ptr w = NodeTraits::get_right(x_parent);
            BOOST_INTRUSIVE_INVARIANT_ASSERT(w);
            if(NodeTraits::get_color(w) == NodeTraits::red()){
               NodeTraits::set_color(w, NodeTraits::black());
               NodeTraits::set_color(x_parent, NodeTraits::red());
               bstree_algo::rotate_left(x_parent, w, NodeTraits::get_parent(x_parent), header);
               w = NodeTraits::get_right(x_parent);
               BOOST_INTRUSIVE_INVARIANT_ASSERT(w);
            }
            node_ptr const w_left (NodeTraits::get_left(w));
            node_ptr const w_right(NodeTraits::get_right(w));
            if((!w_left  || NodeTraits::get_color(w_left)  == NodeTraits::black()) &&
               (!w_right || NodeTraits::get_color(w_right) == NodeTraits::black())){
               NodeTraits::set_color(w, NodeTraits::red());
               x = x_parent;
               x_parent = NodeTraits::get_parent(x_parent);
            }
            else {
               if(!w_right || NodeTraits::get_color(w_right) == NodeTraits::black()){
                  NodeTraits::set_color(w_left, NodeTraits::black());
                  NodeTraits::set_color(w, NodeTraits::red());
                  bstree_algo::rotate_right(w, w_left, NodeTraits::get_parent(w), header);
                  w = NodeTraits::get_right(x_parent);
                  BOOST_INTRUSIVE_INVARIANT_ASSERT(w);
               }
               NodeTraits::set_color(w, NodeTraits::get_color(x_parent));
               NodeTraits::set_color(x_parent, NodeTraits::black());
               const node_ptr new_wright(NodeTraits::get_right(w));
               if(new_wright)
                  NodeTraits::set_color(new_wright, NodeTraits::black());
               bstree_algo::rotate_left(x_parent, NodeTraits::get_right(x_parent), NodeTraits::get_parent(x_parent), header);
               break;
            }
         }
         else {
            // same as above, with right_ <-> left_.
            node_ptr w = x_parent_left;
            if(NodeTraits::get_color(w) == NodeTraits::red()){
               NodeTraits::set_color(w, NodeTraits::black());
               NodeTraits::set_color(x_parent, NodeTraits::red());
               bstree_algo::rotate_right(x_parent, w, NodeTraits::get_parent(x_parent), header);
               w = NodeTraits::get_left(x_parent);
               BOOST_INTRUSIVE_INVARIANT_ASSERT(w);
            }
            node_ptr const w_left (NodeTraits::get_left(w));
            node_ptr const w_right(NodeTraits::get_right(w));
            if((!w_right || NodeTraits::get_color(w_right) == NodeTraits::black()) &&
               (!w_left  || NodeTraits::get_color(w_left)  == NodeTraits::black())){
               NodeTraits::set_color(w, NodeTraits::red());
               x = x_parent;
               x_parent = NodeTraits::get_parent(x_parent);
            }
            else {
               if(!w_left || NodeTraits::get_color(w_left) == NodeTraits::black()){
                  NodeTraits::set_color(w_right, NodeTraits::black());
                  NodeTraits::set_color(w, NodeTraits::red());
                  bstree_algo::rotate_left(w, w_right, NodeTraits::get_parent(w), header);
                  w = NodeTraits::get_left(x_parent);
                  BOOST_INTRUSIVE_INVARIANT_ASSERT(w);
               }
               NodeTraits::set_color(w, NodeTraits::get_color(x_parent));
               NodeTraits::set_color(x_parent, NodeTraits::black());
               const node_ptr new_wleft(NodeTraits::get_left(w));
               if(new_wleft)
                  NodeTraits::set_color(new_wleft, NodeTraits::black());
               bstree_algo::rotate_right(x_parent, NodeTraits::get_left(x_parent), NodeTraits::get_parent(x_parent), header);
               break;
            }
         }
      }
      if(x)
         NodeTraits::set_color(x, NodeTraits::black());
   }

   static void rebalance_after_insertion(node_ptr header, node_ptr p) BOOST_NOEXCEPT
   {
      NodeTraits::set_color(p, NodeTraits::red());
      while(1){
         node_ptr p_parent(NodeTraits::get_parent(p));
         const node_ptr p_grandparent(NodeTraits::get_parent(p_parent));
         if(p_parent == header || NodeTraits::get_color(p_parent) == NodeTraits::black() || p_grandparent == header){
            break;
         }

         NodeTraits::set_color(p_grandparent, NodeTraits::red());
         node_ptr const p_grandparent_left (NodeTraits::get_left (p_grandparent));
         bool const p_parent_is_left_child = p_parent == p_grandparent_left;
         node_ptr const x(p_parent_is_left_child ? NodeTraits::get_right(p_grandparent) : p_grandparent_left);

         if(x && NodeTraits::get_color(x) == NodeTraits::red()){
            NodeTraits::set_color(x, NodeTraits::black());
            NodeTraits::set_color(p_parent, NodeTraits::black());
            p = p_grandparent;
         }
         else{ //Final step
            const bool p_is_left_child(NodeTraits::get_left(p_parent) == p);
            if(p_parent_is_left_child){ //p_parent is left child
               if(!p_is_left_child){ //p is right child
                  bstree_algo::rotate_left_no_parent_fix(p_parent, p);
                  //No need to link p and p_grandparent:
                  //    [NodeTraits::set_parent(p, p_grandparent) + NodeTraits::set_left(p_grandparent, p)]
                  //as p_grandparent is not the header, another rotation is coming and p_parent
                  //will be the left child of p_grandparent
                  p_parent = p;
               }
               bstree_algo::rotate_right(p_grandparent, p_parent, NodeTraits::get_parent(p_grandparent), header);
            }
            else{  //p_parent is right child
               if(p_is_left_child){ //p is left child
                  bstree_algo::rotate_right_no_parent_fix(p_parent, p);
                  //No need to link p and p_grandparent:
                  //    [NodeTraits::set_parent(p, p_grandparent) + NodeTraits::set_right(p_grandparent, p)]
                  //as p_grandparent is not the header, another rotation is coming and p_parent
                  //will be the right child of p_grandparent
                  p_parent = p;
               }
               bstree_algo::rotate_left(p_grandparent, p_parent, NodeTraits::get_parent(p_grandparent), header);
            }
            NodeTraits::set_color(p_parent, NodeTraits::black());
            break;
         }
      }
      NodeTraits::set_color(NodeTraits::get_parent(header), NodeTraits::black());
   }
   /// @endcond
};

/// @cond

template<class NodeTraits>
struct get_algo<RbTreeAlgorithms, NodeTraits>
{
   typedef rbtree_algorithms<NodeTraits> type;
};

template <class ValueTraits, class NodePtrCompare, class ExtraChecker>
struct get_node_checker<RbTreeAlgorithms, ValueTraits, NodePtrCompare, ExtraChecker>
{
    typedef detail::rbtree_node_checker<ValueTraits, NodePtrCompare, ExtraChecker> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_RBTREE_ALGORITHMS_HPP

/* rbtree_algorithms.hpp
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
*/