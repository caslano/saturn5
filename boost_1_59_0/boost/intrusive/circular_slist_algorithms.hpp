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
   static void init(node_ptr this_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns true is "this_node" is the only node of a circular list:
   //!  or it's a not inserted node:
   //!  <tt>return node_ptr() == NodeTraits::get_next(this_node) || NodeTraits::get_next(this_node) == this_node</tt>
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static bool unique(const_node_ptr this_node) BOOST_NOEXCEPT;

   //! <b>Effects</b>: Returns true is "this_node" has the same state as
   //!  if it was inited using "init(node_ptr)"
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static bool inited(const_node_ptr this_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: prev_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the next node of prev_node from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(node_ptr prev_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: prev_node and last_node must be in a circular list
   //!  or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the range (prev_node, last_node) from the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(node_ptr prev_node, node_ptr last_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: prev_node must be a node of a circular list.
   //!
   //! <b>Effects</b>: Links this_node after prev_node in the circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_after(node_ptr prev_node, node_ptr this_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: b and e must be nodes of the same circular list or an empty range.
   //!   and p must be a node of a different circular list.
   //!
   //! <b>Effects</b>: Removes the nodes from (b, e] range from their circular list and inserts
   //!   them after p in p's circular list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void transfer_after(node_ptr p, node_ptr b, node_ptr e) BOOST_NOEXCEPT;

   #endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Constructs an empty list, making this_node the only
   //!   node of the circular list:
   //!  <tt>NodeTraits::get_next(this_node) == this_node</tt>.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void init_header(node_ptr this_node) BOOST_NOEXCEPT
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
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_node(node_ptr prev_init_node, node_ptr this_node) BOOST_NOEXCEPT
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of this_node in the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_node(node_ptr this_node) BOOST_NOEXCEPT
   {  return base_t::get_previous_node(this_node, this_node); }

   //! <b>Requires</b>: this_node must be in a circular list or be an empty circular list.
   //!
   //! <b>Effects</b>: Returns the previous node of the previous node of this_node in the circular list.
   //!
   //! <b>Complexity</b>: Linear to the number of elements in the circular list.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_previous_node(node_ptr this_node) BOOST_NOEXCEPT
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
   static node_ptr get_previous_previous_node(node_ptr p, node_ptr this_node) BOOST_NOEXCEPT
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
   static std::size_t count(const_node_ptr this_node) BOOST_NOEXCEPT
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
   static void unlink(node_ptr this_node) BOOST_NOEXCEPT
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
   BOOST_INTRUSIVE_FORCEINLINE static void link_before (node_ptr nxt_node, node_ptr this_node) BOOST_NOEXCEPT
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
   static void swap_nodes(node_ptr this_node, node_ptr other_node) BOOST_NOEXCEPT
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
   static void reverse(node_ptr p) BOOST_NOEXCEPT
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
   static node_ptr move_backwards(node_ptr p, std::size_t n) BOOST_NOEXCEPT
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
   static node_ptr move_forward(node_ptr p, std::size_t n) BOOST_NOEXCEPT
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