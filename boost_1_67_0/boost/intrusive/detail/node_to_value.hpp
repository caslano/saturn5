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

#ifndef BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP
#define BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/pointer_traits.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <boost/intrusive/detail/is_stateful_value_traits.hpp>

namespace boost {
namespace intrusive {
namespace detail {

template<class VoidPointer>
struct dummy_constptr
{
   typedef typename boost::intrusive::pointer_traits<VoidPointer>::
      template rebind_pointer<const void>::type ConstVoidPtr;

   explicit dummy_constptr(ConstVoidPtr)
   {}

   dummy_constptr()
   {}

   ConstVoidPtr get_ptr() const
   {  return ConstVoidPtr();  }
};

template<class VoidPointer>
struct constptr
{
   typedef typename boost::intrusive::pointer_traits<VoidPointer>::
      template rebind_pointer<const void>::type ConstVoidPtr;

   constptr()
   {}

   explicit constptr(const ConstVoidPtr &ptr)
      :  const_void_ptr_(ptr)
   {}

   const void *get_ptr() const
   {  return boost::movelib::to_raw_pointer(const_void_ptr_);  }

   ConstVoidPtr const_void_ptr_;
};

template <class VoidPointer, bool store_ptr>
struct select_constptr
{
   typedef typename if_c
      < store_ptr
      , constptr<VoidPointer>
      , dummy_constptr<VoidPointer>
      >::type type;
};


template<class ValueTraits, bool IsConst>
struct node_to_value
   :  public select_constptr
      < typename pointer_traits
            <typename ValueTraits::pointer>::template rebind_pointer<void>::type
      , is_stateful_value_traits<ValueTraits>::value
      >::type
{
   static const bool stateful_value_traits = is_stateful_value_traits<ValueTraits>::value;
   typedef typename select_constptr
      < typename pointer_traits
            <typename ValueTraits::pointer>::
               template rebind_pointer<void>::type
      , stateful_value_traits >::type                 Base;

   typedef ValueTraits                                 value_traits;
   typedef typename value_traits::value_type           value_type;
   typedef typename value_traits::node_traits::node    node;
   typedef typename add_const_if_c
         <value_type, IsConst>::type                   vtype;
   typedef typename add_const_if_c
         <node, IsConst>::type                         ntype;
   typedef typename pointer_traits
      <typename ValueTraits::pointer>::
         template rebind_pointer<ntype>::type          npointer;
   typedef typename pointer_traits<npointer>::
      template rebind_pointer<const ValueTraits>::type const_value_traits_ptr;

   node_to_value(const const_value_traits_ptr &ptr)
      :  Base(ptr)
   {}

   typedef vtype &                                 result_type;
   typedef ntype &                                 first_argument_type;

   const_value_traits_ptr get_value_traits() const
   {  return pointer_traits<const_value_traits_ptr>::static_cast_from(Base::get_ptr());  }

   result_type to_value(first_argument_type arg, false_) const
   {  return *(value_traits::to_value_ptr(pointer_traits<npointer>::pointer_to(arg)));  }

   result_type to_value(first_argument_type arg, true_) const
   {  return *(this->get_value_traits()->to_value_ptr(pointer_traits<npointer>::pointer_to(arg))); }

   result_type operator()(first_argument_type arg) const
   {  return this->to_value(arg, bool_<stateful_value_traits>()); }
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_NODE_TO_VALUE_HPP

/* node_to_value.hpp
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
*/