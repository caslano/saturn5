/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_BSTREE_ALGORITHMS_BASE_HPP
#define BOOST_INTRUSIVE_BSTREE_ALGORITHMS_BASE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/uncast.hpp>

namespace boost {
namespace intrusive {

template<class NodeTraits>
class bstree_algorithms_base
{
   public:
   typedef typename NodeTraits::node            node;
   typedef NodeTraits                           node_traits;
   typedef typename NodeTraits::node_ptr        node_ptr;
   typedef typename NodeTraits::const_node_ptr  const_node_ptr;

   //! <b>Requires</b>: 'node' is a node from the tree except the header.
   //!
   //! <b>Effects</b>: Returns the next node of the tree.
   //!
   //! <b>Complexity</b>: Average constant time.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr next_node(node_ptr node) BOOST_NOEXCEPT
   {
      node_ptr const n_right(NodeTraits::get_right(node));
      if(n_right){
         return minimum(n_right);
      }
      else {
         node_ptr n(node);
         node_ptr p(NodeTraits::get_parent(n));
         while(n == NodeTraits::get_right(p)){
            n = p;
            p = NodeTraits::get_parent(p);
         }
         return NodeTraits::get_right(n) != p ? p : n;
      }
   }

   //! <b>Requires</b>: 'node' is a node from the tree except the leftmost node.
   //!
   //! <b>Effects</b>: Returns the previous node of the tree.
   //!
   //! <b>Complexity</b>: Average constant time.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr prev_node(node_ptr node) BOOST_NOEXCEPT
   {
      if(is_header(node)){
         return NodeTraits::get_right(node);
      }
      else if(NodeTraits::get_left(node)){
         return maximum(NodeTraits::get_left(node));
      }
      else {
         node_ptr p(node);
         node_ptr x = NodeTraits::get_parent(p);
         while(p == NodeTraits::get_left(x)){
            p = x;
            x = NodeTraits::get_parent(x);
         }
         return x;
      }
   }

   //! <b>Requires</b>: 'node' is a node of a tree but not the header.
   //!
   //! <b>Effects</b>: Returns the minimum node of the subtree starting at p.
   //!
   //! <b>Complexity</b>: Logarithmic to the size of the subtree.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr minimum(node_ptr node)
   {
      for(node_ptr p_left = NodeTraits::get_left(node)
         ;p_left
         ;p_left = NodeTraits::get_left(node)){
         node = p_left;
      }
      return node;
   }

   //! <b>Requires</b>: 'node' is a node of a tree but not the header.
   //!
   //! <b>Effects</b>: Returns the maximum node of the subtree starting at p.
   //!
   //! <b>Complexity</b>: Logarithmic to the size of the subtree.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr maximum(node_ptr node)
   {
      for(node_ptr p_right = NodeTraits::get_right(node)
         ;p_right
         ;p_right = NodeTraits::get_right(node)){
         node = p_right;
      }
      return node;
   }

   //! <b>Requires</b>: p is a node of a tree.
   //!
   //! <b>Effects</b>: Returns true if p is the header of the tree.
   //!
   //! <b>Complexity</b>: Constant.
   //!
   //! <b>Throws</b>: Nothing.
   static bool is_header(const_node_ptr p) BOOST_NOEXCEPT
   {
      node_ptr p_left (NodeTraits::get_left(p));
      node_ptr p_right(NodeTraits::get_right(p));
      if(!NodeTraits::get_parent(p) || //Header condition when empty tree
         (p_left && p_right &&         //Header always has leftmost and rightmost
            (p_left == p_right ||      //Header condition when only node
               (NodeTraits::get_parent(p_left)  != p ||
                NodeTraits::get_parent(p_right) != p ))
               //When tree size > 1 headers can't be leftmost's
               //and rightmost's parent
          )){
         return true;
      }
      return false;
   }

   //! <b>Requires</b>: 'node' is a node of the tree or a header node.
   //!
   //! <b>Effects</b>: Returns the header of the tree.
   //!
   //! <b>Complexity</b>: Logarithmic.
   //!
   //! <b>Throws</b>: Nothing.
   static node_ptr get_header(const_node_ptr node)
   {
      node_ptr n(detail::uncast(node));
      node_ptr p(NodeTraits::get_parent(node));
      //If p is null, then n is the header of an empty tree
      if(p){
         //Non-empty tree, check if n is neither root nor header
         node_ptr pp(NodeTraits::get_parent(p));
         //If granparent is not equal to n, then n is neither root nor header,
         //the try the fast path
         if(n != pp){
            do{
               n = p;
               p = pp;
               pp = NodeTraits::get_parent(pp);
            }while(n != pp);
            n = p;
         }
         //Check if n is root or header when size() > 0
         else if(!bstree_algorithms_base::is_header(n)){
            n = p;
         }
      }
      return n;
   }
};

}  //namespace intrusive
}  //namespace boost

#endif //BOOST_INTRUSIVE_BSTREE_ALGORITHMS_BASE_HPP

/* bstree_algorithms_base.hpp
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
*/