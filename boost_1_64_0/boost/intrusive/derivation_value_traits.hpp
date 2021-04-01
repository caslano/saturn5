/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>
#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type will
//!derive from node_traits::node

template<class T, class NodeTraits, link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct derivation_value_traits
{
   public:
   typedef NodeTraits                                                node_traits;
   typedef T                                                         value_type;
   typedef typename node_traits::node                                node;
   typedef typename node_traits::node_ptr                            node_ptr;
   typedef typename node_traits::const_node_ptr                      const_node_ptr;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<value_type>::type                      pointer;
   typedef typename pointer_traits<node_ptr>::
      template rebind_pointer<const value_type>::type                const_pointer;
   typedef typename boost::intrusive::
      pointer_traits<pointer>::reference                             reference;
   typedef typename boost::intrusive::
      pointer_traits<const_pointer>::reference                       const_reference;
   static const link_mode_type link_mode = LinkMode;

   static node_ptr to_node_ptr(reference value)
   { return node_ptr(&value); }

   static const_node_ptr to_node_ptr(const_reference value)
   { return node_ptr(&value); }

   static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer_traits<pointer>::pointer_to(static_cast<reference>(*n));
   }

   static const_pointer to_value_ptr(const const_node_ptr &n)
   {
      return pointer_traits<const_pointer>::pointer_to(static_cast<const_reference>(*n));
   }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_DERIVATION_VALUE_TRAITS_HPP

/* derivation_value_traits.hpp
CYOs+w6JXQBb/ojyoZ14/Mb2yKUMhKLbR8r0l5Oq/hNcOzsd9ykL7/1BWgZZeCxF+XizF6Jai5EO58YiKo8hUWBuTdMmf04PLfMnbabF+a7h9/CcJF13feb0Y9/wSjzZveM+RtwY+nVKbsYUvAsQfw3lHBwcb7E9UONjkQ0QdcGswxE24bvB7k8fzqLMAe63GK04orUZhWppKhBuCeBCyRbZGC0oxfhbVOw89l69u0QN5mRAuKpttEqqHlzvw9CBxuftKvmA/vGLLzI42KyFTPLqHNdv6VHHh0h8thumVgP+iiHHzWuV9ETwnbHDdYCropDhfvPwSeYy1JDuvQX+wIWwX38QgansQ2YZFD55dvCJhkT1HtUEH1msVU6LVKx/uV0SSInpAlaoX1zladgWKU4CKYDuine0NJ0Aahv3lj75VnhkovKiSeWT4VKwrHesUcqTK9eKN8hwNUUy/92tYL8sercfuDa66msVw7LM41FXAtFTRZ116E7vqUnh7yNR+Ya8rcPflWLjHKUXQom9vjWCgd5jYyQFKB8mE7I5AQOkcJhyTCZBSwOEFg==
*/