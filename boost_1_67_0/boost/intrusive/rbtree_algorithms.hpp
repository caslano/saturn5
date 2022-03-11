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

   BOOST_INTRUSIVE_FORCEINLINE node_ptr operator()(node_ptr p)
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

   void operator () (const const_node_ptr& p,
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::get_header(const const_node_ptr&)
   static node_ptr get_header(const const_node_ptr & n);

   //! @copydoc ::boost::intrusive::bstree_algorithms::begin_node
   static node_ptr begin_node(const const_node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::end_node
   static node_ptr end_node(const const_node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_tree
   static void swap_tree(node_ptr header1, node_ptr header2);

   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr node2)
   {
      if(node1 == node2)
         return;

      node_ptr header1(bstree_algo::get_header(node1)), header2(bstree_algo::get_header(node2));
      swap_nodes(node1, header1, node2, header2);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::swap_nodes(node_ptr,node_ptr,node_ptr,node_ptr)
   static void swap_nodes(node_ptr node1, node_ptr header1, node_ptr node2, node_ptr header2)
   {
      if(node1 == node2)   return;

      bstree_algo::swap_nodes(node1, header1, node2, header2);
      //Swap color
      color c = NodeTraits::get_color(node1);
      NodeTraits::set_color(node1, NodeTraits::get_color(node2));
      NodeTraits::set_color(node2, c);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr new_node)
   {
      if(node_to_be_replaced == new_node)
         return;
      replace_node(node_to_be_replaced, bstree_algo::get_header(node_to_be_replaced), new_node);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::replace_node(node_ptr,node_ptr,node_ptr)
   static void replace_node(node_ptr node_to_be_replaced, node_ptr header, node_ptr new_node)
   {
      bstree_algo::replace_node(node_to_be_replaced, header, new_node);
      NodeTraits::set_color(new_node, NodeTraits::get_color(node_to_be_replaced));
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::unlink(node_ptr)
   static void unlink(const node_ptr& node)
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
   static node_ptr unlink_leftmost_without_rebalance(const node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::unique(const const_node_ptr&)
   static bool unique(const const_node_ptr & node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::size(const const_node_ptr&)
   static std::size_t size(const const_node_ptr & header);

   //! @copydoc ::boost::intrusive::bstree_algorithms::next_node(const node_ptr&)
   static node_ptr next_node(const node_ptr & node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::prev_node(const node_ptr&)
   static node_ptr prev_node(const node_ptr & node);

   //! @copydoc ::boost::intrusive::bstree_algorithms::init(node_ptr)
   static void init(const node_ptr & node);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::init_header(node_ptr)
   BOOST_INTRUSIVE_FORCEINLINE static void init_header(node_ptr header)
   {
      bstree_algo::init_header(header);
      NodeTraits::set_color(header, NodeTraits::red());
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::erase(node_ptr,node_ptr)
   static node_ptr erase(node_ptr header, node_ptr z)
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

   //! @copydoc ::boost::intrusive::bstree_algorithms::clone(const const_node_ptr&,node_ptr,Cloner,Disposer)
   template <class Cloner, class Disposer>
   static void clone
      (const_node_ptr source_header, node_ptr target_header, Cloner cloner, Disposer disposer)
   {
      rbtree_node_cloner<NodeTraits, Cloner> new_cloner(cloner);
      bstree_algo::clone(source_header, target_header, new_cloner, disposer);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::clear_and_dispose(const node_ptr&,Disposer)
   template<class Disposer>
   static void clear_and_dispose(const node_ptr & header, Disposer disposer);

   //! @copydoc ::boost::intrusive::bstree_algorithms::lower_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr lower_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::upper_bound(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr upper_bound
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::find(const const_node_ptr&, const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static node_ptr find
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::equal_range(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> equal_range
      (const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp);

   //! @copydoc ::boost::intrusive::bstree_algorithms::bounded_range(const const_node_ptr&,const KeyType&,const KeyType&,KeyNodePtrCompare,bool,bool)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, node_ptr> bounded_range
      (const const_node_ptr & header, const KeyType &lower_key, const KeyType &upper_key, KeyNodePtrCompare comp
      , bool left_closed, bool right_closed);

   //! @copydoc ::boost::intrusive::bstree_algorithms::count(const const_node_ptr&,const KeyType&,KeyNodePtrCompare)
   template<class KeyType, class KeyNodePtrCompare>
   static std::size_t count(const const_node_ptr & header, const KeyType &key, KeyNodePtrCompare comp);

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
      (node_ptr header, node_ptr pos, node_ptr new_node)
   {
      bstree_algo::insert_before(header, pos, new_node);
      rebalance_after_insertion(header, new_node);
      return new_node;
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_back(node_ptr,node_ptr)
   static void push_back(node_ptr header, node_ptr new_node)
   {
      bstree_algo::push_back(header, new_node);
      rebalance_after_insertion(header, new_node);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::push_front(node_ptr,node_ptr)
   static void push_front(node_ptr header, node_ptr new_node)
   {
      bstree_algo::push_front(header, new_node);
      rebalance_after_insertion(header, new_node);
   }

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header,  const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data);

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_check(const const_node_ptr&,const node_ptr&,const KeyType&,KeyNodePtrCompare,insert_commit_data&)
   template<class KeyType, class KeyNodePtrCompare>
   static std::pair<node_ptr, bool> insert_unique_check
      (const_node_ptr header, node_ptr hint, const KeyType &key
      ,KeyNodePtrCompare comp, insert_commit_data &commit_data);
   #endif   //#ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED

   //! @copydoc ::boost::intrusive::bstree_algorithms::insert_unique_commit(node_ptr,node_ptr,const insert_commit_data&)
   static void insert_unique_commit
      (node_ptr header, node_ptr new_value, const insert_commit_data &commit_data)
   {
      bstree_algo::insert_unique_commit(header, new_value, commit_data);
      rebalance_after_insertion(header, new_value);
   }

   //! @copydoc ::boost::intrusive::bstree_algorithms::is_header
   static bool is_header(const const_node_ptr & p)
   {
      return NodeTraits::get_color(p) == NodeTraits::red() &&
            bstree_algo::is_header(p);
   }

   /// @cond
   private:

   static void rebalance_after_erasure
      ( node_ptr header, node_ptr z, const typename bstree_algo::data_for_rebalance &info)
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

   static void rebalance_after_erasure_restore_invariants(node_ptr header, node_ptr x, node_ptr x_parent)
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

   static void rebalance_after_insertion(node_ptr header, node_ptr p)
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