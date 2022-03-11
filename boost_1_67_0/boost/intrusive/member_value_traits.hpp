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

#ifndef BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP
#define BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/intrusive_fwd.hpp>

#include <boost/intrusive/link_mode.hpp>
#include <boost/intrusive/detail/parent_from_member.hpp>
#include <boost/move/detail/to_raw_pointer.hpp> 
#include <boost/intrusive/pointer_traits.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

//!This value traits template is used to create value traits
//!from user defined node traits where value_traits::value_type will
//!store a node_traits::node
template< class T, class NodeTraits
        , typename NodeTraits::node T::* PtrToMember
        , link_mode_type LinkMode
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
   = safe_link
   #endif
>
struct member_value_traits
{
   public:
   typedef NodeTraits                                                   node_traits;
   typedef T                                                            value_type;
   typedef typename node_traits::node                                   node;
   typedef typename node_traits::node_ptr                               node_ptr;
   typedef typename node_traits::const_node_ptr                         const_node_ptr;
   typedef pointer_traits<node_ptr>                                     node_ptr_traits;
   typedef typename pointer_traits<node_ptr>::template
      rebind_pointer<T>::type                                           pointer;
   typedef typename pointer_traits<node_ptr>::template
      rebind_pointer<const T>::type                                     const_pointer;
   //typedef typename pointer_traits<pointer>::reference                  reference;
   //typedef typename pointer_traits<const_pointer>::reference            const_reference;
   typedef value_type &                                                 reference;
   typedef const value_type &                                           const_reference;
   static const link_mode_type link_mode = LinkMode;

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value)
   {  return pointer_traits<node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value)
   {  return pointer_traits<const_node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(const node_ptr &n)
   {
      return pointer_traits<pointer>::pointer_to(*detail::parent_from_member<value_type, node>
         (boost::movelib::to_raw_pointer(n), PtrToMember));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const const_node_ptr &n)
   {
      return pointer_traits<const_pointer>::pointer_to(*detail::parent_from_member<value_type, node>
         (boost::movelib::to_raw_pointer(n), PtrToMember));

   }
};

} //namespace intrusive
} //namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif //BOOST_INTRUSIVE_MEMBER_VALUE_TRAITS_HPP

/* member_value_traits.hpp
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
*/