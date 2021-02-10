/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Olaf Krzikalla 2004-2006.
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_LIST_NODE_HPP
#define BOOST_INTRUSIVE_LIST_NODE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>

namespace boost {
namespace intrusive {

// list_node_traits can be used with circular_list_algorithms and supplies
// a list_node holding the pointers needed for a double-linked list
// it is used by list_derived_node and list_member_node

template<class VoidPointer>
struct list_node
{
   typedef typename pointer_rebind<VoidPointer, list_node>::type  node_ptr;
   node_ptr next_;
   node_ptr prev_;
};

template<class VoidPointer>
struct list_node_traits
{
   typedef list_node<VoidPointer>      node;
   typedef typename node::node_ptr     node_ptr;
   typedef typename pointer_rebind<VoidPointer, const node>::type   const_node_ptr;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const const_node_ptr & n)
   {  return n->prev_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_previous(const node_ptr & n)
   {  return n->prev_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_previous(node_ptr n, node_ptr prev)
   {  n->prev_ = prev;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const const_node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr get_next(const node_ptr & n)
   {  return n->next_;  }

   BOOST_INTRUSIVE_FORCEINLINE static void set_next(node_ptr n, node_ptr next)
   {  n->next_ = next;  }
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_LIST_NODE_HPP

/* list_node.hpp
okgTwL/7V/S6z4fdrXuil2xt3aWePFWJmsRao1Zw761SZSFMDLcIFi+b5P76GxAVFHQGGhEyVUmVINPT3QP9a6BnfA93mmKZtvnoQJv8ILo5JxZIjqtqJgwt82+iOHCt6QT+C315Ri7qimvpdbo1lJXv8pTA4Nkg1sX/Pv+/9n6XrBtCD5MdosKVq+mqL/MnuDatmezAb8SyNdOALyfNJhXz6RO0B9AfjKDT7o7oZo3uHF3e34z+HHag/rtmnJ3Ch5dfvnyElmnYJtXucj7XNUV2qJQ6NF+aPzfParXW9c2Fpy7VdtGm172imk3cae3dXUeSLm86MHrSbKB/humADD9kXVNhJn8nj1S/ExiZMPHVdbzD5oE/XFszptC/u/za+WktybUJPYxA52VuWg7cBUJAMWcz2VDB+7dcY91g/ckXBY1H8L17Qvuvn8Qd96fpgiIbYM+Joj2+UoUV03jUpq7lWw7PT8Tw+jBW+q3bTl5BpQr5X3lqzmQ6VkBdBLSht2Opp64Z1HI6MkBe5NlcJ+eMKnvCFufHtsPrcTKGpm1rE89FT6amEBseaadRi2QrvvtoN+1eL+gGPkxkm55ktOne8+TjXnH+p8GcGJLUy1G0/7mnTSTp9jSPbug+1Xy2QZKG3bzlL3d02328
*/