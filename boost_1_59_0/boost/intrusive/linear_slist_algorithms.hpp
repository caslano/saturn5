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
#include <boost/intrusive/detail/twin.hpp>   //for node_pair

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
   //A simple struct containing:
   //
   // typedef node_ptr type;
   // node_ptr first;
   // node_ptr second;
   typedef twin<node_ptr>                  node_pair;

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

   //! <b>Effects</b>: Returns true is "this_node" has the same state as if
   //!  it was inited using "init(node_ptr)"
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
   //! <b>Effects</b>: Unlinks the range (prev_node, last_node) from the linear list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void unlink_after(node_ptr prev_node, node_ptr last_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: prev_node must be a node of a linear list.
   //!
   //! <b>Effects</b>: Links this_node after prev_node in the linear list.
   //!
   //! <b>Complexity</b>: Constant
   //!
   //! <b>Throws</b>: Nothing.
   static void link_after(node_ptr prev_node, node_ptr this_node) BOOST_NOEXCEPT;

   //! <b>Requires</b>: b and e must be nodes of the same linear list or an empty range.
   //!   and p must be a node of a different linear list.
   //!
   //! <b>Effects</b>: Removes the nodes from (b, e] range from their linear list and inserts
   //!   them after p in p's linear list.
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
   BOOST_INTRUSIVE_FORCEINLINE static node_ptr
      get_previous_node(node_ptr prev_init_node, node_ptr this_node) BOOST_NOEXCEPT
   {  return base_t::get_previous_node(prev_init_node, this_node);   }

   //! <b>Requires</b>: this_node must be in a linear list or be an empty linear list.
   //!
   //! <b>Effects</b>: Returns the number of nodes in a linear list. If the linear list
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
   BOOST_INTRUSIVE_FORCEINLINE static void swap_trailing_nodes(node_ptr this_node, node_ptr other_node) BOOST_NOEXCEPT
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
   static node_ptr reverse(node_ptr p) BOOST_NOEXCEPT
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
   static node_pair move_first_n_backwards(node_ptr p, std::size_t n) BOOST_NOEXCEPT
   {
      node_pair ret;
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
   static node_pair move_first_n_forward(node_ptr p, std::size_t n) BOOST_NOEXCEPT
   {
      node_pair ret;
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