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

   BOOST_INTRUSIVE_FORCEINLINE static node_ptr to_node_ptr(reference value) BOOST_NOEXCEPT
   {  return pointer_traits<node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static const_node_ptr to_node_ptr(const_reference value) BOOST_NOEXCEPT
   {  return pointer_traits<const_node_ptr>::pointer_to(value.*PtrToMember);   }

   BOOST_INTRUSIVE_FORCEINLINE static pointer to_value_ptr(node_ptr n) BOOST_NOEXCEPT
   {
      return pointer_traits<pointer>::pointer_to(*detail::parent_from_member<value_type, node>
         (boost::movelib::to_raw_pointer(n), PtrToMember));
   }

   BOOST_INTRUSIVE_FORCEINLINE static const_pointer to_value_ptr(const_node_ptr n) BOOST_NOEXCEPT
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