/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/detail/iterator.hpp>
#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>

namespace boost {
namespace intrusive {

template<class ValueTraits>
struct value_traits_pointers
{
   typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
      (boost::intrusive::detail::
      , ValueTraits, value_traits_ptr
      , typename boost::intrusive::pointer_traits<typename ValueTraits::node_traits::node_ptr>::template
         rebind_pointer<ValueTraits>::type)   value_traits_ptr;

   typedef typename boost::intrusive::pointer_traits<value_traits_ptr>::template
      rebind_pointer<ValueTraits const>::type const_value_traits_ptr;
};

template<class ValueTraits, bool IsConst, class Category>
struct iiterator
{
   typedef ValueTraits                                         value_traits;
   typedef typename value_traits::node_traits                  node_traits;
   typedef typename node_traits::node                          node;
   typedef typename node_traits::node_ptr                      node_ptr;
   typedef ::boost::intrusive::pointer_traits<node_ptr>        nodepointer_traits_t;
   typedef typename nodepointer_traits_t::template
      rebind_pointer<void>::type                               void_pointer;
   typedef typename ValueTraits::value_type                    value_type;
   typedef typename ValueTraits::pointer                       nonconst_pointer;
   typedef typename ValueTraits::const_pointer                 yesconst_pointer;
   typedef typename ::boost::intrusive::pointer_traits
      <nonconst_pointer>::reference                            nonconst_reference;
   typedef typename ::boost::intrusive::pointer_traits
      <yesconst_pointer>::reference                            yesconst_reference;
   typedef typename nodepointer_traits_t::difference_type      difference_type;
   typedef typename detail::if_c
      <IsConst, yesconst_pointer, nonconst_pointer>::type      pointer;
   typedef typename detail::if_c
      <IsConst, yesconst_reference, nonconst_reference>::type  reference;
   typedef iterator
         < Category
         , value_type
         , difference_type
         , pointer
         , reference
         > iterator_type;
   typedef typename value_traits_pointers
      <ValueTraits>::value_traits_ptr                          value_traits_ptr;
   typedef typename value_traits_pointers
      <ValueTraits>::const_value_traits_ptr                    const_value_traits_ptr;
   static const bool stateful_value_traits =
      detail::is_stateful_value_traits<value_traits>::value;
};

template<class NodePtr, class StoredPointer, bool StatefulValueTraits = true>
struct iiterator_members
{

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &data)
      :  nodeptr_(n_ptr), ptr_(data)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return ptr_;  }

   NodePtr nodeptr_;
   StoredPointer ptr_;
};

template<class NodePtr, class StoredPointer>
struct iiterator_members<NodePtr, StoredPointer, false>
{
   BOOST_INTRUSIVE_FORCEINLINE iiterator_members()
      : nodeptr_()//Value initialization to achieve "null iterators" (N3644)
   {}

   BOOST_INTRUSIVE_FORCEINLINE iiterator_members(const NodePtr &n_ptr, const StoredPointer &)
      : nodeptr_(n_ptr)
   {}

   BOOST_INTRUSIVE_FORCEINLINE StoredPointer get_ptr() const
   {  return StoredPointer();  }

   NodePtr nodeptr_;
};

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_IITERATOR_HPP

/* iiterator.hpp
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
*/