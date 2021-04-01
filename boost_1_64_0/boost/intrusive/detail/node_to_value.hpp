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
gDCvnN0va6c9/vOPBTBq+EmZbNwXpiD/+qBdQ4X073WVIkntPgwuguiTp/TJ6LwR8mcXVi4VBAtM0Ei98rDf8ZmVVZkKEb19dDirtu0SDdzHdkOzVzofz6ajI/5fVV4DNsvsZAHIZFRzC/SXQoojWFiK4s9SfrWafjk/YugTGBlggadE2wPTjALOs3ce8Gakm9I4uWZnyvUswA9GQ2YHipZvIXTeBWauTIovYZaYb0J1I9GAJ9rqR79Fn5SB3ve4lw8FJkW2y6i2i0a/yzzJpWmHyA89obEE54b05FT3NUHfjsODH5ovDxFXzPQpi3kk8IztlI7mukVgIYuG51VT8eGcgebbf1BZcXX2+a+TxQxHlMB8gtRANQchbTYqqyBXn5LBfiRlXjopMbNEfyqjMwUg10sdt+JgNNB3SCP9ED208j9OUCghR+Xif5lV6Mz3+Pfj4d0HWJ2kZVBE2/J4Q6Mql49AoJPdlOi9ENfKJuCTQ5Ku3aVGeO/C6qM2OGCOszfMbfNm6xjHJvzFAA3jsnhQZzXxIy5z/s0snZ6AF1+8InFgBuELnZZUFA==
*/