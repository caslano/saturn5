//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Pablo Halpern 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2011-2014. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_POINTER_TRAITS_HPP
#define BOOST_INTRUSIVE_POINTER_TRAITS_HPP

#include <boost/intrusive/detail/config_begin.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/intrusive/pointer_rebind.hpp>
#include <boost/move/detail/pointer_element.hpp>
#include <boost/intrusive/detail/mpl.hpp>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
namespace detail {

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1310)
BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_member_function_callable_with_pointer_to, pointer_to)
BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_member_function_callable_with_dynamic_cast_from, dynamic_cast_from)
BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_member_function_callable_with_static_cast_from, static_cast_from)
BOOST_INTRUSIVE_HAS_STATIC_MEMBER_FUNC_SIGNATURE(has_member_function_callable_with_const_cast_from, const_cast_from)
#else
BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED_IGNORE_SIGNATURE(has_member_function_callable_with_pointer_to, pointer_to)
BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED_IGNORE_SIGNATURE(has_member_function_callable_with_dynamic_cast_from, dynamic_cast_from)
BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED_IGNORE_SIGNATURE(has_member_function_callable_with_static_cast_from, static_cast_from)
BOOST_INTRUSIVE_HAS_MEMBER_FUNC_CALLED_IGNORE_SIGNATURE(has_member_function_callable_with_const_cast_from, const_cast_from)
#endif

BOOST_INTRUSIVE_INSTANTIATE_EVAL_DEFAULT_TYPE_TMPLT(element_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(difference_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(size_type)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(reference)
BOOST_INTRUSIVE_INSTANTIATE_DEFAULT_TYPE_TMPLT(value_traits_ptr)

}  //namespace detail {


//! pointer_traits is the implementation of C++11 std::pointer_traits class with some
//! extensions like castings.
//!
//! pointer_traits supplies a uniform interface to certain attributes of pointer-like types.
//!
//! <b>Note</b>: When defining a custom family of pointers or references to be used with BI
//! library, make sure the public static conversion functions accessed through
//! the `pointer_traits` interface (`*_cast_from` and `pointer_to`) can
//! properly convert between const and nonconst referred member types
//! <b>without the use of implicit constructor calls</b>. It is suggested these
//! conversions be implemented as function templates, where the template
//! argument is the type of the object being converted from.
template <typename Ptr>
struct pointer_traits
{
   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
      //!The pointer type
      //!queried by this pointer_traits instantiation
      typedef Ptr             pointer;

      //!Ptr::element_type if such a type exists; otherwise, T if Ptr is a class
      //!template instantiation of the form SomePointer<T, Args>, where Args is zero or
      //!more type arguments ; otherwise , the specialization is ill-formed.
      typedef unspecified_type element_type;

      //!Ptr::difference_type if such a type exists; otherwise,
      //!std::ptrdiff_t.
      typedef unspecified_type difference_type;

      //!Ptr::rebind<U> if such a type exists; otherwise, SomePointer<U, Args> if Ptr is
      //!a class template instantiation of the form SomePointer<T, Args>, where Args is zero or
      //!more type arguments ; otherwise, the instantiation of rebind is ill-formed.
      //!
      //!For portable code for C++03 and C++11, <pre>typename rebind_pointer<U>::type</pre>
      //!shall be used instead of rebind<U> to obtain a pointer to U.
      template <class U> using rebind = unspecified;

      //!Ptr::reference if such a type exists (non-standard extension); otherwise, element_type &
      //!
      typedef unspecified_type reference;
   #else
      typedef Ptr                                                             pointer;
      //
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_EVAL_DEFAULT
         ( boost::intrusive::detail::, Ptr, element_type
         , boost::movelib::detail::first_param<Ptr>)                          element_type;
      //
      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
         (boost::intrusive::detail::, Ptr, difference_type, std::ptrdiff_t)   difference_type;

      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
         ( boost::intrusive::detail::, Ptr, size_type
         , typename boost::move_detail::
               make_unsigned<difference_type>::type)                          size_type;

      typedef BOOST_INTRUSIVE_OBTAIN_TYPE_WITH_DEFAULT
         ( boost::intrusive::detail::, Ptr, reference
         , typename boost::intrusive::detail::unvoid_ref<element_type>::type) reference;
      //
      template <class U> struct rebind_pointer
      {
         typedef typename boost::intrusive::pointer_rebind<Ptr, U>::type  type;
      };

      #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         template <class U> using rebind = typename boost::intrusive::pointer_rebind<Ptr, U>::type;
      #endif
   #endif   //#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

   //! <b>Remark</b>: If element_type is (possibly cv-qualified) void, r type is unspecified; otherwise,
   //!   it is element_type &.
   //!
   //! <b>Returns</b>: A dereferenceable pointer to r obtained by calling Ptr::pointer_to(reference).
   //!   Non-standard extension: If such function does not exist, returns pointer(addressof(r));
   //!
   //! <b>Note</b>: For non-conforming compilers only the existence of a member function called
   //!   <code>pointer_to</code> is checked.
   BOOST_INTRUSIVE_FORCEINLINE static pointer pointer_to(reference r) BOOST_NOEXCEPT
   {
      //Non-standard extension, it does not require Ptr::pointer_to. If not present
      //tries to converts &r to pointer.
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_pointer_to
            <Ptr, Ptr (*)(reference)>::value;
      boost::intrusive::detail::bool_<value> flag;
      return pointer_traits::priv_pointer_to(flag, r);
   }

   //! <b>Remark</b>: Non-standard extension.
   //!
   //! <b>Returns</b>: A dereferenceable pointer to r obtained by calling the static template function
   //!   Ptr::static_cast_from(UPpr/const UPpr &).
   //!   If such function does not exist, returns pointer_to(static_cast<element_type&>(*uptr))
   //!
   //! <b>Note</b>: For non-conforming compilers only the existence of a member function called
   //!   <code>static_cast_from</code> is checked.
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer static_cast_from(const UPtr &uptr) BOOST_NOEXCEPT
   {
      typedef const UPtr &RefArg;
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_static_cast_from
            <pointer, pointer(*)(RefArg)>::value
         || boost::intrusive::detail::
               has_member_function_callable_with_static_cast_from
                  <pointer, pointer(*)(UPtr)>::value;
      return pointer_traits::priv_static_cast_from(boost::intrusive::detail::bool_<value>(), uptr);
   }

   //! <b>Remark</b>: Non-standard extension.
   //!
   //! <b>Returns</b>: A dereferenceable pointer to r obtained by calling the static template function
   //!   Ptr::const_cast_from<UPtr>(UPpr/const UPpr &).
   //!   If such function does not exist, returns pointer_to(const_cast<element_type&>(*uptr))
   //!
   //! <b>Note</b>: For non-conforming compilers only the existence of a member function called
   //!   <code>const_cast_from</code> is checked.
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer const_cast_from(const UPtr &uptr) BOOST_NOEXCEPT
   {
      typedef const UPtr &RefArg;
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_const_cast_from
            <pointer, pointer(*)(RefArg)>::value
         || boost::intrusive::detail::
               has_member_function_callable_with_const_cast_from
                  <pointer, pointer(*)(UPtr)>::value;
      return pointer_traits::priv_const_cast_from(boost::intrusive::detail::bool_<value>(), uptr);
   }

   //! <b>Remark</b>: Non-standard extension.
   //!
   //! <b>Returns</b>: A dereferenceable pointer to r obtained by calling the static template function
   //!   Ptr::dynamic_cast_from<UPtr>(UPpr/const UPpr &).
   //!   If such function does not exist, returns pointer_to(*dynamic_cast<element_type*>(&*uptr))
   //!
   //! <b>Note</b>: For non-conforming compilers only the existence of a member function called
   //!   <code>dynamic_cast_from</code> is checked.
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer dynamic_cast_from(const UPtr &uptr) BOOST_NOEXCEPT
   {
      typedef const UPtr &RefArg;
      const bool value = boost::intrusive::detail::
         has_member_function_callable_with_dynamic_cast_from
            <pointer, pointer(*)(RefArg)>::value
         || boost::intrusive::detail::
               has_member_function_callable_with_dynamic_cast_from
                  <pointer, pointer(*)(UPtr)>::value;
      return pointer_traits::priv_dynamic_cast_from(boost::intrusive::detail::bool_<value>(), uptr);
   }

   ///@cond
   private:
   //priv_to_raw_pointer
   template <class T>
   BOOST_INTRUSIVE_FORCEINLINE static T* to_raw_pointer(T* p) BOOST_NOEXCEPT
   {  return p; }

   template <class Pointer>
   BOOST_INTRUSIVE_FORCEINLINE static typename pointer_traits<Pointer>::element_type*
      to_raw_pointer(const Pointer &p) BOOST_NOEXCEPT
   {  return pointer_traits::to_raw_pointer(p.operator->());  }

   //priv_pointer_to
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_pointer_to(boost::intrusive::detail::true_, reference r) BOOST_NOEXCEPT
   { return Ptr::pointer_to(r); }

   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_pointer_to(boost::intrusive::detail::false_, reference r) BOOST_NOEXCEPT
   { return pointer(boost::intrusive::detail::addressof(r)); }

   //priv_static_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_static_cast_from(boost::intrusive::detail::true_, const UPtr &uptr) BOOST_NOEXCEPT
   { return Ptr::static_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_static_cast_from(boost::intrusive::detail::false_, const UPtr &uptr) BOOST_NOEXCEPT
   {  return uptr ? pointer_to(*static_cast<element_type*>(to_raw_pointer(uptr))) : pointer();  }

   //priv_const_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_const_cast_from(boost::intrusive::detail::true_, const UPtr &uptr) BOOST_NOEXCEPT
   { return Ptr::const_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_const_cast_from(boost::intrusive::detail::false_, const UPtr &uptr) BOOST_NOEXCEPT
   {  return uptr ? pointer_to(const_cast<element_type&>(*uptr)) : pointer();  }

   //priv_dynamic_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_dynamic_cast_from(boost::intrusive::detail::true_, const UPtr &uptr) BOOST_NOEXCEPT
   { return Ptr::dynamic_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_dynamic_cast_from(boost::intrusive::detail::false_, const UPtr &uptr) BOOST_NOEXCEPT
   {  return uptr ? pointer_to(dynamic_cast<element_type&>(*uptr)) : pointer();  }
   ///@endcond
};

///@cond

// Remove cv qualification from Ptr parameter to pointer_traits:
template <typename Ptr>
struct pointer_traits<const Ptr> : pointer_traits<Ptr> {};
template <typename Ptr>
struct pointer_traits<volatile Ptr> : pointer_traits<Ptr> { };
template <typename Ptr>
struct pointer_traits<const volatile Ptr> : pointer_traits<Ptr> { };
// Remove reference from Ptr parameter to pointer_traits:
template <typename Ptr>
struct pointer_traits<Ptr&> : pointer_traits<Ptr> { };

///@endcond

//! Specialization of pointer_traits for raw pointers
//!
template <typename T>
struct pointer_traits<T*>
{
   typedef T               element_type;
   typedef T*              pointer;
   typedef std::ptrdiff_t  difference_type;
   typedef std::size_t     size_type;

   #ifdef BOOST_INTRUSIVE_DOXYGEN_INVOKED
      typedef T &          reference;
      //!typedef for <pre>U *</pre>
      //!
      //!For portable code for C++03 and C++11, <pre>typename rebind_pointer<U>::type</pre>
      //!shall be used instead of rebind<U> to obtain a pointer to U.
      template <class U> using rebind = U*;
   #else
      typedef typename boost::intrusive::detail::unvoid_ref<element_type>::type reference;
      #if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
         template <class U> using rebind = U*;
      #endif
   #endif

   template <class U> struct rebind_pointer
   {  typedef U* type;  };

   //! <b>Returns</b>: addressof(r)
   //!
   BOOST_INTRUSIVE_FORCEINLINE static pointer pointer_to(reference r) BOOST_NOEXCEPT
   { return boost::intrusive::detail::addressof(r); }

   //! <b>Returns</b>: static_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer static_cast_from(U *uptr) BOOST_NOEXCEPT
   {  return static_cast<pointer>(uptr);  }

   //! <b>Returns</b>: const_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer const_cast_from(U *uptr) BOOST_NOEXCEPT
   {  return const_cast<pointer>(uptr);  }

   //! <b>Returns</b>: dynamic_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer dynamic_cast_from(U *uptr) BOOST_NOEXCEPT
   {  return dynamic_cast<pointer>(uptr);  }
};

}  //namespace container {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif // ! defined(BOOST_INTRUSIVE_POINTER_TRAITS_HPP)

/* pointer_traits.hpp
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
*/