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
         (boost::intrusive::detail::, Ptr, reference, typename boost::intrusive::detail::unvoid_ref<element_type>::type)   reference;
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
   BOOST_INTRUSIVE_FORCEINLINE static pointer pointer_to(reference r)
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
   BOOST_INTRUSIVE_FORCEINLINE static pointer static_cast_from(const UPtr &uptr)
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
   BOOST_INTRUSIVE_FORCEINLINE static pointer const_cast_from(const UPtr &uptr)
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
   BOOST_INTRUSIVE_FORCEINLINE static pointer dynamic_cast_from(const UPtr &uptr)
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
   BOOST_INTRUSIVE_FORCEINLINE static T* to_raw_pointer(T* p)
   {  return p; }

   template <class Pointer>
   BOOST_INTRUSIVE_FORCEINLINE static typename pointer_traits<Pointer>::element_type*
      to_raw_pointer(const Pointer &p)
   {  return pointer_traits::to_raw_pointer(p.operator->());  }

   //priv_pointer_to
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_pointer_to(boost::intrusive::detail::true_, reference r)
   { return Ptr::pointer_to(r); }

   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_pointer_to(boost::intrusive::detail::false_, reference r)
   { return pointer(boost::intrusive::detail::addressof(r)); }

   //priv_static_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_static_cast_from(boost::intrusive::detail::true_, const UPtr &uptr)
   { return Ptr::static_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_static_cast_from(boost::intrusive::detail::false_, const UPtr &uptr)
   {  return uptr ? pointer_to(*static_cast<element_type*>(to_raw_pointer(uptr))) : pointer();  }

   //priv_const_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_const_cast_from(boost::intrusive::detail::true_, const UPtr &uptr)
   { return Ptr::const_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_const_cast_from(boost::intrusive::detail::false_, const UPtr &uptr)
   {  return uptr ? pointer_to(const_cast<element_type&>(*uptr)) : pointer();  }

   //priv_dynamic_cast_from
   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_dynamic_cast_from(boost::intrusive::detail::true_, const UPtr &uptr)
   { return Ptr::dynamic_cast_from(uptr); }

   template<class UPtr>
   BOOST_INTRUSIVE_FORCEINLINE static pointer priv_dynamic_cast_from(boost::intrusive::detail::false_, const UPtr &uptr)
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
   typedef T            element_type;
   typedef T*           pointer;
   typedef std::ptrdiff_t difference_type;

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
   BOOST_INTRUSIVE_FORCEINLINE static pointer pointer_to(reference r)
   { return boost::intrusive::detail::addressof(r); }

   //! <b>Returns</b>: static_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer static_cast_from(U *uptr)
   {  return static_cast<pointer>(uptr);  }

   //! <b>Returns</b>: const_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer const_cast_from(U *uptr)
   {  return const_cast<pointer>(uptr);  }

   //! <b>Returns</b>: dynamic_cast<pointer>(uptr)
   //!
   template<class U>
   BOOST_INTRUSIVE_FORCEINLINE static pointer dynamic_cast_from(U *uptr)
   {  return dynamic_cast<pointer>(uptr);  }
};

}  //namespace container {
}  //namespace boost {

#include <boost/intrusive/detail/config_end.hpp>

#endif // ! defined(BOOST_INTRUSIVE_POINTER_TRAITS_HPP)

/* pointer_traits.hpp
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
*/