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

#ifndef BOOST_INTRUSIVE_LINEAR_SLIST_ALGORITHMS_HPP
#define BOOST_INTRUSIVE_LINEAR_SLIST_ALGORITHMS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/detail/common_slist_algorithms.hpp>
#include <boost/intrusive/detail/algo_type.hpp>
#include <cstddef>
#include <boost/intrusive/detail/minimal_pair_header.hpp>   //std::pair

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//! linear_slist_algorithms provides basic algorithms to manipulate nodes
//! forming a linear singly linked list.
//!
//! linear_slist_algorithms is configured with a NodeTraits class, which encapsulates the
//! information about the node to be manipulated. NodeTraits must support the
//! following interface:
//!
//! <b>Typedefs</b>:
//!
//! <tt>node</tt>: The type of the node that forms the linear list
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
class linear_slist_algorithms
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
   static void init(const node_ptr & this_node);

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

   //! <b>Effects</b>: Returns true is "this_node" has the same state as if
   //!  it was inited using "init(node_ptr)"
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
   static void unlink_after(const node_ptr & prev_node);

   //! <b>Requires</b>: prev_node and last_node must be in a circular list
   //!  or be an empty circular list.
   //!
   //! <b>Effects</b>: Unlinks the range (prev_node, last_node) from the linear list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(const node_ptr & prev_node, const node_ptr & last_node);

   //! <b>Requires</b>: prev_node must be a node of a linear list.
   //!
   //! <b>Effects</b>: Links this_node after prev_node in the linear list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_after(const node_ptr & prev_node, const node_ptr & this_node);

   //! <b>Requires</b>: b and e must be nodes of the same linear list or an empty range.
   //!   and p must be a node of a different linear list.
   //!
   //! <b>Effects</b>: Removes the nodes from (b, e] range from their linear list and inserts
   //!   them after p in p's linear list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void transfer_after(const node_ptr & p, const node_ptr & b, const node_ptr & e);

   #endif   //#if defined(BOOST_INTRUSIVE_DOXYGEN_INVOKED)

   //! <b>Effects</b>: Constructs an empty list, making this_node the only
   //!   node of the circular list:
   //!  <tt>NodeTraits::get_next(this_node) == this_node</tt>.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static void init_header(const node_ptr & this_node)
   {  NodeTraits::set_next(this_node, node_ptr ());  }

   //! <b>Requires</b>: this_node and prev_init_node must be in the same linear list.
   //!
   //! <b>Effects</b>: Returns the previous node of this_node in the linear list starting.
   //!   the search from prev_init_node. The first node checked for equality
   //!   is NodeTraits::get_next(prev_init_node).
   //!
   //! <b>Complexity</b>: Linear to the number of elements between prev_init_node and this_node.
   //!
   //! <b>Throws</b>: Nothing.
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous_node(const node_ptr & prev_init_node, const node_ptr & this_node)
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   //! <b>Requires</b>: this_node must be in a linear list or be an empty linear list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in a linear list. If the linear list
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
      } while (p);
      return result;
   }

   //! <b>Requires</b>: this_node and other_node must be nodes inserted
   //!  in linear lists or be empty linear lists.
   //!
   //! <b>Effects</b>: Moves all the nodes previously chained after this_node after other_node
   //!   and vice-versa.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void swap_trailing_nodes(node_ptr this_node, node_ptr other_node)
   {
      node_ptr this_nxt    = NodeTraits::get_next(this_node);
      node_ptr other_nxt   = NodeTraits::get_next(other_node);
      NodeTraits::set_next(this_node, other_nxt);
      NodeTraits::set_next(other_node, this_nxt);
   }

   //! <b>Effects</b>: Reverses the order of elements in the list.
   //!
   //! <b>Returns</b>: The new first node of the list.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: This function is linear to the contained elements.
   static node_ptr reverse(node_ptr p)
   {
      if(!p) return node_ptr();
      node_ptr i = NodeTraits::get_next(p);
      node_ptr first(p);
      while(i){
         node_ptr nxti(NodeTraits::get_next(i));
         base_t::unlink_after(p);
         NodeTraits::set_next(i, first);
         first = i;
         i = nxti;
      }
      return first;
   }

   //! <b>Effects</b>: Moves the first n nodes starting at p to the end of the list.
   //!
   //! <b>Returns</b>: A pair containing the new first and last node of the list or
   //!   if there has been any movement, a null pair if n leads to no movement.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements plus the number moved positions.
   static std::pair<node_ptr, node_ptr> move_first_n_backwards(node_ptr p, std::size_t n)
   {
      std::pair<node_ptr, node_ptr> ret;
      //Null shift, or count() == 0 or 1, nothing to do
      if(!n || !p || !NodeTraits::get_next(p)){
         return ret;
      }

      node_ptr first = p;
      bool end_found = false;
      node_ptr new_last = node_ptr();
      node_ptr old_last = node_ptr();

      //Now find the new last node according to the shift count.
      //If we find 0 before finding the new last node
      //unlink p, shortcut the search now that we know the size of the list
      //and continue.
      for(std::size_t i = 1; i <= n; ++i){
         new_last = first;
         first = NodeTraits::get_next(first);
         if(first == node_ptr()){
            //Shortcut the shift with the modulo of the size of the list
            n %= i;
            if(!n)   return ret;
            old_last = new_last;
            i = 0;
            //Unlink p and continue the new first node search
            first = p;
            //unlink_after(new_last);
            end_found = true;
         }
      }

      //If the p has not been found in the previous loop, find it
      //starting in the new first node and unlink it
      if(!end_found){
         old_last = base_t::get_previous_node(first, node_ptr());
      }

      //Now link p after the new last node
      NodeTraits::set_next(old_last, p);
      NodeTraits::set_next(new_last, node_ptr());
      ret.first   = first;
      ret.second  = new_last;
      return ret;
   }

   //! <b>Effects</b>: Moves the first n nodes starting at p to the beginning of the list.
   //!
   //! <b>Returns</b>: A pair containing the new first and last node of the list or
   //!   if there has been any movement, a null pair if n leads to no movement.
   //!
   //! <b>Throws</b>: Nothing.
   //!
   //! <b>Complexity</b>: Linear to the number of elements plus the number moved positions.
   static std::pair<node_ptr, node_ptr> move_first_n_forward(node_ptr p, std::size_t n)
   {
      std::pair<node_ptr, node_ptr> ret;
      //Null shift, or count() == 0 or 1, nothing to do
      if(!n || !p || !NodeTraits::get_next(p))
         return ret;

      node_ptr first  = p;

      //Iterate until p is found to know where the current last node is.
      //If the shift count is less than the size of the list, we can also obtain
      //the position of the new last node after the shift.
      node_ptr old_last(first), next_to_it, new_last(p);
      std::size_t distance = 1;
      while(!!(next_to_it = node_traits::get_next(old_last))){
         if(distance++ > n)
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
         if(!new_before_last_pos)
            return ret;

         for( new_last = p
            ; --new_before_last_pos
            ; new_last = node_traits::get_next(new_last)){
            //empty
         }
      }

      //Get the first new node
      node_ptr new_first(node_traits::get_next(new_last));
      //Now put the old beginning after the old end
      NodeTraits::set_next(old_last, p);
      NodeTraits::set_next(new_last, node_ptr());
      ret.first   = new_first;
      ret.second  = new_last;
      return ret;
   }
};

/// @cond

template<class NodeTraits>
struct get_algo<LinearSListAlgorithms, NodeTraits>
{
   typedef linear_slist_algorithms<NodeTraits> type;
};

/// @endcond

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_LINEAR_SLIST_ALGORITHMS_HPP

/* linear_slist_algorithms.hpp
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
*/