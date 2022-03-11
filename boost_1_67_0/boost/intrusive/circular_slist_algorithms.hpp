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

#ifndef BOOST_INTRUSIVE_CIRCULAR_SLIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_CIRCULAR_SLIST_ALGORITHMS_HPP

#include <cstddef>
#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/common_slist_algorithms.hpp>
#include <boost/intrusive/detail/algo_type.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! circular_slist_algorithms provides basic algorithms to manipulate nodes
//! forming a circular singly linked list. An empty circular list is formed by a node
//! whose pointer to the next node points to itself.
//!
//! circular_slist_algorithms is configured with a NodeTraits class, which encapsulates the
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
//! <tt>static node_ptr get_next(const_node_ptr n);</tt>
//!
//! <tt>static void set_next(node_ptr n, node_ptr next);</tt>
template<class NodeTraits>
class circular_slist_algorithms
   /// @cond
   : public detail::common_slist_algorithms<NodeTraits>
   /// @endcond
{
   /// @cond
   typedef detail::common_slist_algorithms<NodeTraits> base_t;
   /// @endcond
   public:
   typedef typename NodeTraits::node            node;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;
   typedef NodeTraits                           node_traits;

   #if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Constructs an non-used list element, putting the next
   //!   pointer to null:
   //!  <tt>NodeTraits::get_next(this_node) == node_ptr()</tt>
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void init(node_ptr this_node);

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns true is "this_node" is the only node of a circular list:
   //!  or it's a not inserted node:
   //!  <tt>return node_ptr() == NodeTraits::get_next(this_node) || NodeTraits::get_next(this_node) == this_node</tt>
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static bool unique(const_node_ptr this_node);

   //! <b>Effects</b>: Returns true is "this_node" has the same state as
   //!  if it was inited using "init(node_ptr)"
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static bool inited(const_node_ptr this_node);

   //! <b>Requires</b>: prev_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the next node of prev_node from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(node_ptr prev_node);

   //! <b>Requires</b>: prev_node and last_node must be in a circular list
   //!  or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the range (prev_node, last_node) from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(node_ptr prev_node, node_ptr last_node);

   //! <b>Requires</b>: prev_node must be a node of a circular list.
   //!
   //! <b>Effects</b>: Links this_node after prev_node in the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_after(node_ptr prev_node, node_ptr this_node);

   //! <b>Requires</b>: b and e must be nodes of the same circular list or an empty range.
   //!   and p must be a node of a different circular list.
   //!
   //! <b>Effects</b>: Removes the nodes from (b, e] range from their circular list and inserts
   //!   them after p in p's circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void transfer_after(node_ptr p, node_ptr b, node_ptr e);

   #endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Constructs an empty list, making this_node the only
   //!   node of the circular list:
   //!  <tt>NodeTraits::get_next(this_node) == this_node</tt>.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void init_header(node_ptr this_node)
   {  NodeTraits::set_next(this_node, this_node);  }

   //! <b>Requires</b>: this_node and prev_init_node must be in the same circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of this_node in the circular list starting.
   //!   the search from prev_init_node. The first node checked for equality
   //!   is NodeTraits::get_next(prev_init_node).
   //!
   //! <b>Complexity</b>: Linear to the number of elements between prev_init_node and this_node.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_node(const node_ptr &prev_init_node, const node_ptr &this_node)
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of this_node in the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_node(const node_ptr & this_node)
   {  return base_t::get_previous_node(this_node, this_node); }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of the previous node of this_node in the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_previous_node(const node_ptr & this_node)
   {  return get_previous_previous_node(this_node, this_node); }

   //! <b>Requires</b>: this_node and p must be in the same circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of the previous node of this_node in the
   //!   circular list starting. the search from p. The first node checked
   //!   for equality is NodeTraits::get_next((NodeTraits::get_next(p)).
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr get_previous_previous_node(node_ptr p, const node_ptr & this_node)
   {
      node_ptr p_next = NodeTraits::get_next(p);
      node_ptr p_next_next = NodeTraits::get_next(p_next);
      while (this_node != p_next_next){
         p = p_next;
         p_next = p_next_next;
         p_next_next = NodeTraits::get_next(p_next);
      }
      return p;
   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in a circular list. If the circular list
   //!  is empty, returns 1.
   //!
   //! <b>Complexity</b>: Linear
   //!
   //! <b>Throws</b>: Nothing.
   static std::size_t count(const const_node_ptr & this_node)
   {
      std::size_t result = 0;
      const_node_ptr p = this_node;
      do{
         p = NodeTraits::get_next(p);
         ++result;
      } while (p != this_node);
      return result;
   }

   //! <b>Requires</b>: this_node must be in a circular list, be an empty circular list or be inited.
   //!
   //! <b>Effects</b>: Unlinks the node from the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void unlink(node_ptr this_node)
   {
      if(NodeTraits::get_next(this_node))
         base_t::unlink_after(get_previous_node(this_node));
   }

   //! <b>Requires</b>: nxt_node must be a node of a circular list.
   //!
   //! <b>Effects</b>: Links this_node before nxt_node in the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void link_before (node_ptr nxt_node, node_ptr this_node)
   {  base_t::link_after(get_previous_node(nxt_node), this_node);   }

   //! <b>Requires</b>: this_node and other_node must be nodes inserted
   //!  in circular lists or be empty circular lists.
   //!
   //! <b>Effects</b>: Swaps the position of the nodes: this_node is inserted in
   //!   other_nodes position in the second circular list and the other_node is inserted
   //!   in this_node's position in the first circular list.
   //!
   //! <b>Complexity</b>: Linear to number of elements of both lists
   //!
   //! <b>Throws</b>: Nothing.
   static void swap_nodes(node_ptr this_node, node_ptr other_node)
   {
      if (other_node == this_node)
         return;
      const node_ptr this_next = NodeTraits::get_next(this_node);
      const node_ptr other_next = NodeTraits::get_next(other_node);
      const bool this_null   = !this_next;
      const bool other_null  = !other_next;
      const bool this_empty  = this_next == this_node;
      const bool other_empty = other_next == other_node;

      if(!(other_null || other_empty)){
         NodeTraits::set_next(this_next == other_node ? other_node : get_previous_node(other_node), this_node );
      }
      if(!(this_null | this_empty)){
         NodeTraits::set_next(other_next == this_node ? this_node  : get_previous_node(this_node), other_node );
      }
      NodeTraits::set_next(this_node,  other_empty ? this_node  : (other_next == this_node ? other_node : other_next) );
      NodeTraits::set_next(other_node, this_empty  ? other_node : (this_next == other_node ? this_node :  this_next ) );
   }

   //! <b>Effects</b>: Reverses the order of elements in the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: This function is linear to the contained elements.
   static void reverse(node_ptr p)
   {
      node_ptr i = NodeTraits::get_next(p), e(p);
      for (;;) {
         node_ptr nxt(NodeTraits::get_next(i));
         if (nxt == e)
            break;
         base_t::transfer_after(e, i, nxt);
      }
   }

   //! <b>Effects</b>: Moves the node p n positions towards the end of the list.
   //!
   //! <b>Returns</b>: The previous node of p after the function if there has been any movement,
   //!   Null if n leads to no movement.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements plus the number moved positions.
   static node_ptr move_backwards(node_ptr p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n) return node_ptr();
      node_ptr first  = NodeTraits::get_next(p);

      //count() == 1 or 2, nothing to do
      if(NodeTraits::get_next(first) == p)
         return node_ptr();

      bool end_found = false;
      node_ptr new_last = node_ptr();

      //Now find the new last node according to the shift count.
      //If we find p before finding the new last node
      //unlink p, shortcut the search now that we know the size of the list
      //and continue.
      for(std::size_t i = 1; i <= n; ++i){
         new_last = first;
         first = NodeTraits::get_next(first);
         if(first == p){
            //Shortcut the shift with the modulo of the size of the list
            n %= i;
            if(!n)
               return node_ptr();
            i = 0;
            //Unlink p and continue the new first node search
            first = NodeTraits::get_next(p);
            base_t::unlink_after(new_last);
            end_found = true;
         }
      }

      //If the p has not been found in the previous loop, find it
      //starting in the new first node and unlink it
      if(!end_found){
         base_t::unlink_after(base_t::get_previous_node(first, p));
      }

      //Now link p after the new last node
      base_t::link_after(new_last, p);
      return new_last;
   }

   //! <b>Effects</b>: Moves the node p n positions towards the beginning of the list.
   //!
   //! <b>Returns</b>: The previous node of p after the function if there has been any movement,
   //!   Null if n leads equals to no movement.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements plus the number moved positions.
   static node_ptr move_forward(node_ptr p, std::size_t n)
   {
      //Null shift, nothing to do
      if(!n) return node_ptr();
      node_ptr first  = node_traits::get_next(p);

      //count() == 1 or 2, nothing to do
      if(node_traits::get_next(first) == p) return node_ptr();

      //Iterate until p is found to know where the current last node is.
      //If the shift count is less than the size of the list, we can also obtain
      //the position of the new last node after the shift.
      node_ptr old_last(first), next_to_it, new_last(p);
      std::size_t distance = 1;
      while(p != (next_to_it = node_traits::get_next(old_last))){
         if(++distance > n)
            new_last = node_traits::get_next(new_last);
         old_last = next_to_it;
      }
      //If the shift was bigger or equal than the size, obtain the equivalent
      //forward shifts and find the new last node.
      if(distance <= n){
         //Now find the equivalent forward shifts.
         //Shortcut the shift with the modulo of the size of the list
         std::size_t new_before_last_pos = (distance - (n % distance))% distance;
         //If the shift is a multiple of the size there is nothing to do
         if(!new_before_last_pos)   return node_ptr();

         for( new_last = p
            ; new_before_last_pos--
            ; new_last = node_traits::get_next(new_last)){
            //empty
         }
      }

      //Now unlink p and link it after the new last node
      base_t::unlink_after(old_last);
      base_t::link_after(new_last, p);
      return new_last;
   }
};

/// @cond

template<class NodeTraits>
struct get_algo<CircularSListAlgorithms, NodeTraits>
{
   typedef circular_slist_algorithms<NodeTraits> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_CIRCULAR_SLIST_ALGORITHMS_HPP

/* circular_slist_algorithms.hpp
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
*/