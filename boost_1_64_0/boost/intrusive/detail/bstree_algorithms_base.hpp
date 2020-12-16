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
TsU7gW9WX/roFprqh7SDr1kxQGfuoP5KJ4V5QqpxV65pqjvSMT8rJEpeJqr9k3lqH2FqC4hvavsNbUGwLr9cleFUGetyntrf0mWP1J2IbJB7wHmqluerdiPVNze40m3liqadyEEeojQBbYwz/r2z0j3LFUPN5SIPWzHKVg5jJ9tq4e9Sl7LEF33vs5WjYivnsh0nc4NVk7H951OYsxMJgweI1wO+Is8r90h4heM65Xml44vO84rB5gJ8pZ1zK/ciw7NJfAXPJstk7oAMed/pjKzDPkvIg9k+Q7Y3Trv9pIrbzmpt9pEn7fCfb0U34Jnw1Npp/TlPHzs5NkHWJEfcyDLkpSb8s8+pi1wWsJsypeNElWBN8v9iE5lrSeyphtK9gmcUt6nskpYrqO5MZdd1L09kO2Dcdiz77WO3pxSJ5c9DeQtV9srH88covSvJk7cdXM45XxVPW8SB4mLK56s5Lrbt09nGdi9bp+ZER+dogM5htqfVRadaH0fnmOjIfFnYv/dZPTM5nDkbqiXM2ufYv9pu6Wx3csZ8UO/OnDLRFdyXukvH++/kHe5V5BXilpjPqe9VXj+3pvNI/PDf40v2hf9sXbIv/Gfrkn3hP1uXBNmSvMOLLV38kve5uRPndQI1t55j9yZybFRsO97KGnqqV3en83wV06J6tbgGteMaNnSfY2/yiBX0Ts81qiTgOd5pn59VedlpteDf8ci93EFacNxVxF9X1/uc7s6wjxpbvXZcg7PcDTlSg6jq8XExnUO8BxreO+XbhDrWbdbZnP0rEfu5MQ79YuQ84lb3uKd73zurG987A58TX06q9L1T7Nhgp/q3itP47rAtRebhERu/DXmN45a+ZLRx+URRuY0TP7id1tqfz9X+XHyTapnsnvjh233pS+HbfelL4ds9uhXafZf9yu6V/WUSoXkK9qfs3md/TdPdZ5y8/b2kjr9czWqzWOxvBXHSU+S7R9vYrFD2d7ptz7nvnUbb2yJj5HvK80MP5E2OW7TfaHvyWaNy2yN+4DcNooecFwf98G2taH/4tla0P3xbQ7dCW3tc7Y/VbEXu02Ira9T+MygP5ZZ7Z5/kkz/vAd8spP5O/dz7vv83kvH07eTct0UOc+yDfud+Cp0TfM9SReW8S91w3p125E2l38pqHuJ58WDwOZgzWRsH+YHan2iyC+KG/nZtb36p9lfz9i1wEjbyAttXPfOkOc8zdRPlG6TovIHOh0noVOe7Qk2r0j6IUHPNUg+GewNlC7jGpsv4533yPeBFZGs69vmyXs/ONyFp3811nariXMTX+ChTXZNm+M/mokuYc15y5xcWzJlvlT97JiudXdYO/jVci6RhvG6N16Lo+l0/+vPwLLW/LSWLcr4XvazCovQ5KJzrrZXat4mxCtVU+5+eyvNiI/ri7HZ5MfNK1Y3tZ98F6vDIE9W4es04PtoEfC8K+e1qjUq7O9+uqgflxbajFQ25dzRS3644lpq/SoV/Q3gG4V2VDV4d544zfLcSSZE8L0G/v53nqaQT61G2nEnYIsTbT3ZZkI3akirxP0TvTTsf3XnIS7YLW1ulUUT4M8gAlZcLgvLh0zmCqOshJtN4HF+dvZ1kSzjvAH7XRxjf53W7ox3zb9v856FOC26z/kKbFX8g4FqSBsu2mw+a+F9DyQcqbK9Iq+L26owDodsriavqP78x9pjmq/+0oPpPEZ0paSfdHvnNofJBk/DaI0+6rBmszcfwMRvZwXWov1LpdWmqN+KH/06Fbqi2x9jO6GmPCOhbsDfH2fspSZz2rYH3Gew1/HkIpP7C6JeUvAbUa7qMER+P+NZr+pQ0i8z1Ks08x1f1Gjz34PUq3mj1PDHMbKs=
*/