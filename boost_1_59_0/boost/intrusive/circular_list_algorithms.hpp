/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_CIRCULAR_LIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_CIRCULAR_LIST_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! circular_list_algorithms provides basic algorithms to manipulate nodes
//! forming a circular doubly linked list. An empty circular list is formed by a node
//! whose pointers point to itself.
//!
//! circular_list_algorithms is configured with a NodeTraits class, which encapsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the circular list
//!
//! <tt>node_ptr</tt>: A pointer to a node
//!
//! <tt>const_node_ptr</tt>: A pointer to a const node
//!
//! <b>Static functions</b>:
//!
//! <tt>static node_ptr get_previous(const_node_ptr n);</tt>
//!
//! <tt>static void set_previous(node_ptr n, node_ptr prev);</tt>
//!
//! <tt>static node_ptr get_next(const_node_ptr n);</tt>
//!
//! <tt>static void set_next(node_ptr n, node_ptr next);</tt>
template<class NodeTraits>
class circular_list_algorithms
{
   public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;

   //! <b>Effects</b>: Constructs an non-used list element, so that
   //! inited(this_node) == true
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void init(node_ptr this_node) BOOST_NOEXCEPT
   {
      const node_ptr null_node = node_ptr();
      NodeTraits::set_next(this_node, null_node);
      NodeTraits::set_previous(this_node, null_node);
   }

   //! <b>Effects</b>: Returns true is "this_node" is in a non-used state
   //! as if it was initialized by the "init" function.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const_node_ptr this_node) BOOST_NOEXCEPT
   {  return !NodeTraits::get_next(this_node); }

   //! <b>Effects</b>: Constructs an empty list, making this_node the only
   //!   node of the circular list:
   //!  <tt>NodeTraits::get_next(this_node) == NodeTraits::get_previous(this_node)
   //!  == this_node</tt>.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void init_header(node_ptr this_node) BOOST_NOEXCEPT
   {
      NodeTraits::set_next(this_node, this_node);
      NodeTraits::set_previous(this_node, this_node);
   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns true is "this_node" is the only node of a circular list:
   //!  <tt>return NodeTraits::get_next(this_node) == this_node</tt>
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static bool unique(const_node_ptr this_node) BOOST_NOEXCEPT
   {
      node_ptr next = NodeTraits::get_next(this_node);
      return !next || next == this_node;
   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in a circular list. If the circular list
   //!  is empty, returns 1.
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t count(const_node_ptr this_node) BOOST_NOEXCEPT
   {
      std::size_t result = 0;
      const_node_ptr p = this_node;
      do{
         p = NodeTraits::get_next(p);
         ++result;
      }while (p != this_node);
      return result;
   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the node from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr unlink(node_ptr this_node) BOOST_NOEXCEPT
   {
      node_ptr next(NodeTraits::get_next(this_node));
      node_ptr prev(NodeTraits::get_previous(this_node));
      NodeTraits::set_next(prev, next);
      NodeTraits::set_previous(next, prev);
      return next;
   }

   //! <b>Requires</b>: b and e must be nodes of the same circular list or an empty range.
   //!
   //! <b>Effects</b>: Unlinks the node [b, e) from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink(node_ptr b, node_ptr e) BOOST_NOEXCEPT
   {
      if (b != e) {
         node_ptr prevb(NodeTraits::get_previous(b));
         NodeTraits::set_previous(e, prevb);
         NodeTraits::set_next(prevb, e);
      }
   }

   //! <b>Requires</b>: nxt_node must be a node of a circular list.
   //!
   //! <b>Effects</b>: Links this_node before nxt_node in the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_before(node_ptr nxt_node, node_ptr this_node) BOOST_NOEXCEPT
   {
      node_ptr prev(NodeTraits::get_previous(nxt_node));
      NodeTraits::set_previous(this_node, prev);
      NodeTraits::set_next(this_node, nxt_node);
      //nxt_node might be an alias for prev->next_
      //so use it before NodeTraits::set_next(prev, ...)
      //is called and the reference changes its value
      NodeTraits::set_previous(nxt_node, this_node);
      NodeTraits::set_next(prev, this_node);
   }

   //! <b>Requires</b>: prev_node must be a node of a circular list.
   //!
   //! <b>Effects</b>: Links this_node after prev_node in the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_after(node_ptr prev_node, node_ptr this_node) BOOST_NOEXCEPT
   {
      node_ptr next(NodeTraits::get_next(prev_node));
      NodeTraits::set_previous(this_node, prev_node);
      NodeTraits::set_next(this_node, next);
      //prev_node might be an alias for next->next_
      //so use it before update it before NodeTraits::set_previous(next, ...)
      //is called and the reference changes it's value
      NodeTraits::set_next(prev_node, this_node);
      NodeTraits::set_previous(next, this_node);
   }

   //! <b>Requires</b>: this_node and other_node must be nodes inserted
   //!  in circular lists or be empty circular lists.
   //!
   //! <b>Effects</b>: Swaps the position of the nodes: this_node is inserted in
   //!   other_nodes position in the second circular list and the other_node is inserted
   //!   in this_node's position in the first circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void swap_nodes(node_ptr this_node, node_ptr other_node) BOOST_NOEXCEPT
   {
      if (other_node == this_node)
         return;
      bool this_inited  = inited(this_node);
      bool other_inited = inited(other_node);
      if(this_inited){
         init_header(this_node);
      }
      if(other_inited){
         init_header(other_node);
      }

      node_ptr next_this(NodeTraits::get_next(this_node));
      node_ptr prev_this(NodeTraits::get_previous(this_node));
      node_ptr next_other(NodeTraits::get_next(other_node));
      node_ptr prev_other(NodeTraits::get_previous(other_node));
      //these first two swaps must happen before the other two
      swap_prev(next_this, next_other);
      swap_next(prev_this, prev_other);
      swap_next(this_node, other_node);
      swap_prev(this_node, other_node);

      if(this_inited){
         init(other_node);
      }
      if(other_inited){
         init(this_node);
      }
   }

   //! <b>Requires</b>: b and e must be nodes of the same circular list or an empty range.
   //!   and p must be a node of a different circular list or may not be an iterator in
   //    [b, e).
   //!
   //! <b>Effects</b>: Removes the nodes from [b, e) range from their circular list and inserts
   //!   them before p in p's circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void transfer(node_ptr p, node_ptr b, node_ptr e) BOOST_NOEXCEPT
   {
      if (b != e && p != b && p != e) {
         node_ptr prev_p(NodeTraits::get_previous(p));
         node_ptr prev_b(NodeTraits::get_previous(b));
         node_ptr prev_e(NodeTraits::get_previous(e));
         NodeTraits::set_next(prev_e, p);
         NodeTraits::set_previous(p, prev_e);
         NodeTraits::set_next(prev_b, e);
         NodeTraits::set_previous(e, prev_b);
         NodeTraits::set_next(prev_p, b);
         NodeTraits::set_previous(b, prev_p);
      }
   }

   //! <b>Requires</b>: i must a node of a circular list
   //!   and p must be a node of a different circular list.
   //!
   //! <b>Effects</b>: Removes the node i from its circular list and inserts
   //!   it before p in p's circular list.
   //!   If p == i or p == NodeTraits::get_next(i), this function is a null operation.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void transfer(node_ptr p, node_ptr i) BOOST_NOEXCEPT
   {
      node_ptr n(NodeTraits::get_next(i));
      if(n != p && i != p){
         node_ptr prev_p(NodeTraits::get_previous(p));
         node_ptr prev_i(NodeTraits::get_previous(i));
         NodeTraits::set_next(prev_p, i);
         NodeTraits::set_previous(i, prev_p);
         NodeTraits::set_next(i, p);
         NodeTraits::set_previous(p, i);
         NodeTraits::set_previous(n, prev_i);
         NodeTraits::set_next(prev_i, n);

      }
   }

   //! <b>Effects</b>: Reverses the order of elements in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: This function is linear time.
   static void reverse(node_ptr p) BOOST_NOEXCEPT
   {
      node_ptr f(NodeTraits::get_next(p));
      node_ptr i(NodeTraits::get_next(f)), e(p);

      while(i != e) {
         node_ptr n = i;
         i = NodeTraits::get_next(i);
         transfer(f, n, i);
         f = n;
      }
   }

   //! <b>Effects</b>: Moves the node p n positions towards the end of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of moved positions.
   static void move_backwards(node_ptr p, std::size_t n) BOOST_NOEXCEPT
   {
      //Null shift, nothing to do
      if(!n) return;
      node_ptr first  = NodeTraits::get_next(p);
      //size() == 0 or 1, nothing to do
      if(first == NodeTraits::get_previous(p)) return;
      unlink(p);
      //Now get the new first node
      while(n--){
         first = NodeTraits::get_next(first);
      }
      link_before(first, p);
   }

   //! <b>Effects</b>: Moves the node p n positions towards the beginning of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of moved positions.
   static void move_forward(node_ptr p, std::size_t n) BOOST_NOEXCEPT
   {
      //Null shift, nothing to do
      if(!n)   return;
      node_ptr last  = NodeTraits::get_previous(p);
      //size() == 0 or 1, nothing to do
      if(last == NodeTraits::get_next(p))   return;

      unlink(p);
      //Now get the new last node
      while(n--){
         last = NodeTraits::get_previous(last);
      }
      link_after(last, p);
   }

   //! <b>Requires</b>: f and l must be in a circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in the range [f, l).
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t distance(const_node_ptr f, const_node_ptr l) BOOST_NOEXCEPT
   {
      std::size_t result = 0;
      while(f != l){
         f = NodeTraits::get_next(f);
         ++result;
      }
      return result;
   }

   struct stable_partition_info
   {
      std::size_t num_1st_partition;
      std::size_t num_2nd_partition;
      node_ptr    beg_2st_partition;
   };

   template<class Pred>
   static void stable_partition(node_ptr beg, node_ptr end, Pred pred, stable_partition_info &info)
   {
      node_ptr bcur = node_traits::get_previous(beg);
      node_ptr cur  = beg;
      node_ptr new_f = end;

      std::size_t num1 = 0, num2 = 0;
      while(cur != end){
         if(pred(cur)){
            ++num1;
            bcur = cur;
            cur  = node_traits::get_next(cur);
         }
         else{
            ++num2;
            node_ptr last_to_remove = bcur;
            new_f = cur;
            bcur = cur;
            cur  = node_traits::get_next(cur);
            BOOST_TRY{
               //Main loop
               while(cur != end){
                  if(pred(cur)){ //Might throw
                     ++num1;
                     //Process current node
                     node_traits::set_next    (last_to_remove, cur);
                     node_traits::set_previous(cur, last_to_remove);
                     last_to_remove = cur;
                     node_ptr nxt = node_traits::get_next(cur);
                     node_traits::set_next    (bcur, nxt);
                     node_traits::set_previous(nxt, bcur);
                     cur = nxt;
                  }
                  else{
                     ++num2;
                     bcur = cur;
                     cur  = node_traits::get_next(cur);
                  }
               }
            }
            BOOST_CATCH(...){
               node_traits::set_next    (last_to_remove, new_f);
               node_traits::set_previous(new_f, last_to_remove);
               BOOST_RETHROW;
            }
            BOOST_CATCH_END
            node_traits::set_next(last_to_remove, new_f);
            node_traits::set_previous(new_f, last_to_remove);
            break;
         }
      }
      info.num_1st_partition = num1;
      info.num_2nd_partition = num2;
      info.beg_2st_partition = new_f;
   }

   private:
   static void swap_prev(node_ptr this_node, node_ptr other_node) BOOST_NOEXCEPT
   {
      node_ptr temp(NodeTraits::get_previous(this_node));
      NodeTraits::set_previous(this_node, NodeTraits::get_previous(other_node));
      NodeTraits::set_previous(other_node, temp);
   }

   static void swap_next(node_ptr this_node, node_ptr other_node) BOOST_NOEXCEPT
   {
      node_ptr temp(NodeTraits::get_next(this_node));
      NodeTraits::set_next(this_node, NodeTraits::get_next(other_node));
      NodeTraits::set_next(other_node, temp);
   }
};

/// @cond

template<class NodeTraits>
struct get_algo<CircularListAlgorithms, NodeTraits>
{
   typedef circular_list_algorithms<NodeTraits> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_CIRCULAR_LIST_ALGORITHMS_HPP

/* circular_list_algorithms.hpp
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
*/