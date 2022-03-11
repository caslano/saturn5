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
   BOOST_INTRUSIVE_FORCEINLINE static void init(node_ptr this_node)
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
   BOOST_INTRUSIVE_FORCEINLINE static bool inited(const const_node_ptr &this_node)
   {  return !NodeTraits::get_next(this_node); }

   //! <b>Effects</b>: Constructs an empty list, making this_node the only
   //!   node of the circular list:
   //!  <tt>NodeTraits::get_next(this_node) == NodeTraits::get_previous(this_node)
   //!  == this_node</tt>.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void init_header(node_ptr this_node)
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
   BOOST_INTRUSIVE_FORCEINLINE static bool unique(const const_node_ptr &this_node)
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
   static std::size_t count(const const_node_ptr &this_node)
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
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr unlink(node_ptr this_node)
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
   BOOST_INTRUSIVE_FORCEINLINE static void unlink(node_ptr b, node_ptr e)
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
   BOOST_INTRUSIVE_FORCEINLINE static void link_before(node_ptr nxt_node, node_ptr this_node)
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
   BOOST_INTRUSIVE_FORCEINLINE static void link_after(node_ptr prev_node, node_ptr this_node)
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
   static void swap_nodes(node_ptr this_node, node_ptr other_node)
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
   static void transfer(node_ptr p, node_ptr b, node_ptr e)
   {
      if (b != e) {
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
   static void transfer(node_ptr p, node_ptr i)
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
   static void reverse(node_ptr p)
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
   static void move_backwards(node_ptr p, std::size_t n)
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
   static void move_forward(node_ptr p, std::size_t n)
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
   static std::size_t distance(const const_node_ptr &f, const const_node_ptr &l)
   {
      const_node_ptr i(f);
      std::size_t result = 0;
      while(i != l){
         i = NodeTraits::get_next(i);
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
   BOOST_INTRUSIVE_FORCEINLINE static void swap_prev(node_ptr this_node, node_ptr other_node)
   {
      node_ptr temp(NodeTraits::get_previous(this_node));
      NodeTraits::set_previous(this_node, NodeTraits::get_previous(other_node));
      NodeTraits::set_previous(other_node, temp);
   }

   BOOST_INTRUSIVE_FORCEINLINE static void swap_next(node_ptr this_node, node_ptr other_node)
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