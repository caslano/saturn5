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
Xe3g4VTlz/NrK8+c9SefH9SsBFTyiqVOE9wCFkJR6WVZGseZMbaJtgHt4yxlAnkFYsZDcEK0321AyRHrepiQsNDB46eKXRPFsimxL8gIw+GGqTEN0D819Pb2suxu7EjpVikpRWcpZcyW8PxOG8ZUPpRgtxU61mk5bfJ+CXivKOyjDU53sD3eBJBM1BkiC8/vBN9JuctylXT80S/+cufs3npyrI1CJOjqDRLadz1Y1DcoymKK9bSXZnzHA3ImHHlTimKW7Q1ZDHCUm1mhJXigjd4fbRy49QrhG605Uf4TlTUcWdP0YSddDYDpOVaZqcn2sVAorcacdYDiXIAa+dlKeTtb2o6uzKvfBgwYurNufJspI2DIKeY+yMRvIAiW4QoSU09nDpSaYWIrymOrOQnnDg+H4+IVb088DEDCp6RwvccrKt+7T2V51vuDHmWJPulWVpiHfmq96tyMyY6sQDTmgvS6sqgB23yCv5MSUTag4HPyn6rwaAm+EMES7QlKZB75X/Ke5azqRdpTnaUhj74yippsMXvGfywVoHJ0XiB9nDbqd8iR11+0AjilCM4Pb0QnLy8V5peChlCgcTfU7uTE1TWSANl6joI/nbT51v6BB4+H5cD2QVfvrTN1TuQGn/CozndQvQ8iY8FiKmqLWfPYu0w07Dwyt3einFRQXLDJQAINoCyIwVsMi9aRizTaiYRE3LQPB/A/BsofNGe5
*/