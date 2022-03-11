//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DEFAULT_DELETE_HPP_INCLUDED
#define BOOST_MOVE_DEFAULT_DELETE_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>
#include <boost/move/detail/unique_ptr_meta_utils.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/static_assert.hpp>

#include <cstddef>   //For std::size_t,std::nullptr_t

//!\file
//! Describes the default deleter (destruction policy) of <tt>unique_ptr</tt>: <tt>default_delete</tt>.

namespace boost{
// @cond
namespace move_upd {

namespace bmupmu = ::boost::move_upmu;

////////////////////////////////////////
////        enable_def_del
////////////////////////////////////////

//compatible with a pointer type T*:
//When either Y* is convertible to T*
//Y is U[N] and T is U cv []
template<class U, class T>
struct def_del_compatible_cond
   : bmupmu::is_convertible<U*, T*>
{};

template<class U, class T, std::size_t N>
struct def_del_compatible_cond<U[N], T[]>
   : def_del_compatible_cond<U[], T[]>
{};

template<class U, class T, class Type = bmupmu::nat>
struct enable_def_del
   : bmupmu::enable_if_c<def_del_compatible_cond<U, T>::value, Type>
{};

////////////////////////////////////////
////        enable_defdel_call
////////////////////////////////////////

//When 2nd is T[N], 1st(*)[N] shall be convertible to T(*)[N]; 
//When 2nd is T[],  1st(*)[] shall be convertible to T(*)[]; 
//Otherwise, 1st* shall be convertible to 2nd*.

template<class U, class T, class Type = bmupmu::nat>
struct enable_defdel_call
   : public enable_def_del<U, T, Type>
{};

template<class U, class T, class Type>
struct enable_defdel_call<U, T[], Type>
   : public enable_def_del<U[], T[], Type>
{};

template<class U, class T, class Type, std::size_t N>
struct enable_defdel_call<U, T[N], Type>
   : public enable_def_del<U[N], T[N], Type>
{};

////////////////////////////////////////
////     Some bool literal zero conversion utilities
////////////////////////////////////////

struct bool_conversion {int for_bool; int for_arg(); };
typedef int bool_conversion::* explicit_bool_arg;

#if !defined(BOOST_NO_CXX11_NULLPTR) && !defined(BOOST_NO_CXX11_DECLTYPE)
   typedef decltype(nullptr) nullptr_type;
#elif !defined(BOOST_NO_CXX11_NULLPTR)
   typedef std::nullptr_t nullptr_type;
#else
   typedef int (bool_conversion::*nullptr_type)();
#endif

template<bool B>
struct is_array_del
{};

template<class T>
void call_delete(T *p, is_array_del<true>)
{
   delete [] p;
}

template<class T>
void call_delete(T *p, is_array_del<false>)
{
   delete p;
}

}  //namespace move_upd {
// @endcond

namespace movelib {

namespace bmupd = boost::move_upd;
namespace bmupmu = ::boost::move_upmu;

//!The class template <tt>default_delete</tt> serves as the default deleter
//!(destruction policy) for the class template <tt>unique_ptr</tt>.
//!
//! \tparam T The type to be deleted. It may be an incomplete type
template <class T>
struct default_delete
{
   //! Default constructor.
   //!
   BOOST_CONSTEXPR default_delete()
   //Avoid "defaulted on its first declaration must not have an exception-specification" error for GCC 4.6
   #if !defined(BOOST_GCC) || (BOOST_GCC < 40600 && BOOST_GCC >= 40700) || defined(BOOST_MOVE_DOXYGEN_INVOKED)
   BOOST_NOEXCEPT
   #endif
   #if !defined(BOOST_NO_CXX11_DEFAULTED_FUNCTIONS) || defined(BOOST_MOVE_DOXYGEN_INVOKED)
   = default;
   #else
   {};
   #endif

   #if defined(BOOST_MOVE_DOXYGEN_INVOKED)
   //! Trivial copy constructor
   //!
   default_delete(const default_delete&) BOOST_NOEXCEPT = default;
   //! Trivial assignment
   //!
   default_delete &operator=(const default_delete&) BOOST_NOEXCEPT = default;
   #else
   typedef typename bmupmu::remove_extent<T>::type element_type;
   #endif

   //! <b>Effects</b>: Constructs a default_delete object from another <tt>default_delete<U></tt> object.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!   - If T is not an array type and U* is implicitly convertible to T*.
   //!   - If T is an array type and U* is a more CV qualified pointer to remove_extent<T>::type.
   template <class U>
   default_delete(const default_delete<U>&
      BOOST_MOVE_DOCIGN(BOOST_MOVE_I typename bmupd::enable_def_del<U BOOST_MOVE_I T>::type* =0)
      ) BOOST_NOEXCEPT
   {
      //If T is not an array type, U derives from T
      //and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor<default_delete, U>::value ));
   }

   //! <b>Effects</b>: Constructs a default_delete object from another <tt>default_delete<U></tt> object.
   //!
   //! <b>Remarks</b>: This constructor shall not participate in overload resolution unless:
   //!   - If T is not an array type and U* is implicitly convertible to T*.
   //!   - If T is an array type and U* is a more CV qualified pointer to remove_extent<T>::type.
   template <class U>
   BOOST_MOVE_DOC1ST(default_delete&, 
      typename bmupd::enable_def_del<U BOOST_MOVE_I T BOOST_MOVE_I default_delete &>::type)
      operator=(const default_delete<U>&) BOOST_NOEXCEPT
   {
      //If T is not an array type, U derives from T
      //and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor<default_delete, U>::value ));
      return *this;
   }

   //! <b>Effects</b>: if T is not an array type, calls <tt>delete</tt> on static_cast<T*>(ptr),
   //!   otherwise calls <tt>delete[]</tt> on static_cast<remove_extent<T>::type*>(ptr).
   //!
   //! <b>Remarks</b>: If U is an incomplete type, the program is ill-formed.
   //!   This operator shall not participate in overload resolution unless:
   //!      - T is not an array type and U* is convertible to T*, OR
   //!      - T is an array type, and remove_cv<U>::type is the same type as
   //!         remove_cv<remove_extent<T>::type>::type and U* is convertible to remove_extent<T>::type*.
   template <class U>
   BOOST_MOVE_DOC1ST(void, typename bmupd::enable_defdel_call<U BOOST_MOVE_I T BOOST_MOVE_I void>::type)
      operator()(U* ptr) const BOOST_NOEXCEPT
   {
      //U must be a complete type
      BOOST_STATIC_ASSERT(sizeof(U) > 0);
      //If T is not an array type, U derives from T
      //and T has no virtual destructor, then you have a problem
      BOOST_STATIC_ASSERT(( !::boost::move_upmu::missing_virtual_destructor<default_delete, U>::value ));
      element_type * const p = static_cast<element_type*>(ptr);
      move_upd::call_delete(p, move_upd::is_array_del<bmupmu::is_array<T>::value>());
   }

   //! <b>Effects</b>: Same as <tt>(*this)(static_cast<element_type*>(nullptr))</tt>.
   //!
   void operator()(BOOST_MOVE_DOC0PTR(bmupd::nullptr_type)) const BOOST_NOEXCEPT
   {  BOOST_STATIC_ASSERT(sizeof(element_type) > 0);  }
};

}  //namespace movelib {
}  //namespace boost{

#include <boost/move/detail/config_end.hpp>

#endif   //#ifndef BOOST_MOVE_DEFAULT_DELETE_HPP_INCLUDED

/* default_delete.hpp
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
*/