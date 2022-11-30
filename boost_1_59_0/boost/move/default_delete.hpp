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

template< class T, class U
        , bool enable =  def_del_compatible_cond< U, T>::value &&
                        !move_upmu::is_array<T>::value &&
                        !move_upmu::is_same<typename move_upmu::remove_cv<T>::type, void>::value &&
                        !move_upmu::is_same<typename move_upmu::remove_cv<U>::type, typename move_upmu::remove_cv<T>::type>::value
        >
struct missing_virtual_destructor_default_delete
{  static const bool value = !move_upmu::has_virtual_destructor<T>::value;  };

template<class T, class U>
struct missing_virtual_destructor_default_delete<T, U, false>
{  static const bool value = false;  };

//////////////////////////////////////
//       missing_virtual_destructor
//////////////////////////////////////

template<class Deleter, class U>
struct missing_virtual_destructor
{  static const bool value = false;  };

template<class T, class U>
struct missing_virtual_destructor< ::boost::movelib::default_delete<T>, U >
   : missing_virtual_destructor_default_delete<T, U>
{};


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
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor<default_delete, U>::value ));
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
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor<default_delete, U>::value ));
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
      BOOST_STATIC_ASSERT(( !bmupd::missing_virtual_destructor<default_delete, U>::value ));
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