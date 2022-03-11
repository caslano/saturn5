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
   static node_ptr next_node(const node_ptr & node)
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
   static node_ptr prev_node(const node_ptr & node)
   {
      if(is_header(node)){
         //return NodeTraits::get_right(node);
         return maximum(NodeTraits::get_parent(node));
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
   static bool is_header(const const_node_ptr & p)
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
   static node_ptr get_header(const const_node_ptr & node)
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