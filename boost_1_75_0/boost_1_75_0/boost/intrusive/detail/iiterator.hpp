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
yKIkm7wvkePwnvXdV6ay7yo6pGGaTrC3P1OcETGR2oCXWGhTXGps2bu+JtSGQ+iHB0QHl3tOVjv4v9N51Id23CJvTE95S7LZT7ViPN0ld6FtHAGRQgZjgp0qpv4Cu7BEMkOh7HOXKkTH5ze+7PaqOd/9rYVS7tTLp9ZU20KoNdx7uqLs3myM80NiXKh8gs8tQ7LDdKnAmgPHlpKOX6+HV5z4R0IjBZ0cH593Tn7VltvpMmUpCHa9FxKREae9flE3mthhEwZI3lIqzPFOfpbmGgIR1R1jiMmozr9YBfrn+CMdDh0eId0i+iEz7MfNDjupPRJ2Bd1AqGYsnQK8Yro/A5QACsZ9sOaoJ4kr5WcivyxYNiyoW3qrDDTQdk91lOf06ZlroxheDC/NmyO/5XHyYILjaT7GDNItLiW/dbr208q2Zhgo187VBlFP/V3k0yrTrv73+jxiTZAbwPgFC2hyr4tJ4PRm4OL4SzZQEYkDAG07EVAE31SEnD11nUbRXlgY03sRv1jrYZvFP7TDZa7tHyjpLzyeOsLh7eE8XsMvokkPnRw8XqAXCvoLT3joqM/mckbnFlSH/iIEMPEDLvB6jdN8Q3AiDHpVNTYPOfbZqM9ejEkWsmSh2YRL0V4AnqDnv+wtF5sSHRuYNrQK9entpm4qPw9qO38SKpqsaPCn24gCN/iy6cVticX9kR9vmmSSi0j/OpQMVLNvA+Z7
*/