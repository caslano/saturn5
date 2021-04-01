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
edHa/pxPHc5gsULUvWPaEiMyXKrF5JPCIUNuHgYeOgkdoAnxheLpZ6CmXgAuPzjJ73o5QJqtJqyfh/2yCJQHIvtq3DLykvUPfCvUKIfoiCrf+eJLzGfGRmWSAs1rPZv+WSIUws/O0irFVxGQOy3YyXoNhXdInkc2fddJzxKoW1fec1ZpqedbIdYKmvULJxCiZ+5qNMw+t5ybh5azrr0OrJKp6bQWnFxNddQHNm0skdWoRHQ89J3aV/XO7vPKMw/oZG8Q0rSu0efaeK43PoxVV38Z3+3yTpAOlXa1hkljnf2jvhZ0J4sdWcz2iKEewoK4gNj70OfNzbg46FruwuS8k9PXnurJJHHHVXfu0OrNrKQqunQNKno9GiPh0LCWk5kMxFty+hNRUfEBjlVK4U2rZ4a/qvVZ0ud5nk4Z2w4YhAW7hvDbWmvjK7y/Vk/x6u2JCR+fL82vakp978IQxgiazgKU9HIes5rTIVphFXGcE9JnX5PfBZmFZ7Yfe59HMmGwgKBkV6d5yBj2S2sejh4XqGM8AfAsBCrV9yqLBFuyxJy9xCK0UrQrcywr6g==
*/