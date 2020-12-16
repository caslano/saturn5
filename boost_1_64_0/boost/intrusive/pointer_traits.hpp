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
kTKOrWqkbxESLR8+9AowxkG9oUr3NbC+6I1Eb67qDewI+8Jo0buIPgj2g9fBAfAmOBCOh4PgVDgYzlD1Dq6GN8JN8Cao+rMk+AIcAw+pcodvw2T4LhwHP1LlBs/AdKje406BteFUWA/eE2j0S7PRr4Bz4FB4KxwB58GRcD7MgLfBu0R/CK6AO2Ae3ANXw5fgWlgE74PH4Db4KdwO/wEfg7/D52GwF8/DsBt8CcbAw7Af/ABeC4/DXPghXABPwCWiLxM9D34EH4bFKl/gSXgcfq6uD7+E5+ApdX34HazqzX1KlR88B6+EC2AfuBCmQZVPU+Av6JnQgb4YesF7oA/Mh77wflgVboJV4AOiPyz6o6LvgPXg67A+/Bo2hudgJPwNtoPhPtwfoKqDXWA32BX2hlfDwbAnTIAxMBv2ggtgf7gZDoBbYBx8Ag6Hr8DR8E2YCE/CMTDIl/oIm0BVjpHwe9gZ/gCHwLNwGHxZ1WN4ECbAEfjLgCPhTBgPl8A0mAenqfyBGfBBeDPcBTPhCzALvgaz4YdwJvwGzoO/wlzoqEL9gy2hKpdIuEDlA1wEs8R8JlwMb4dL4ErRV4m+U9zthnfAd0X/AN6p8gMuh6dEr1LVsPeHK9T1RW8PZ8HOoqt+JAMp6Wz0I7dK/x2ApEg/+U9fo5/0ZRzTCVaFXWAI7AoD4RBYHV4Pa8CbxD4J1oQzYG04R8xdz3N5XYzrXmbzPDdF+ucsWBNmwwZ6pbHhf43yI/5rSf8ehCwX/zvF/99gdbgbBoleV3R13T2wKXwdttBbFBjpfAb2gi/AXfAQ/Fns1XubI7Ca0/BXHR5W4Wtdnpf4HdHNiN+1Er/mSA8Zf/b1xp9yBxvBgVClPRa2F70jHAw7wyFQ5dlQeCWMg31U2HAQXAbjYDxU5XA9HA0TYDocDRfAm+AyOBaugOPgBpgCH4YT4FY4ET4F0+BeOBkehOnwNZgJi2AWLIbZ8HNVPvAbOAv+CHOhyp8RMMypdf1+Kwm2g4thV7gExsDbYX94BxziVOnS+akLs6i7kZ/RMp5vq64r+cm7KJ2fz8L2qrzkvv0a7AGPwD6qnGEsfAMOhYxRdX19C6bCozADvgdnwWNwjujzRc+DH8C/wY+gisvHTiMfPoP/gCfhGXhWxUu9b4M14TewNvwOhsMS2AB+6TTy4xTsDP8Fx0KnF+M0WAVuglXhCzAAvgWD4QewIfwUNoJfwAiIX0cz6AObQ1/YAgbAlrA6bAUJQ6c7ArZBbw4jYVt138I8SusyTiTsgh4y7pByaIo0c8p7VV9jfvBJX5k/gf6iVxc9GD4FQ0WvJ/plcB9srMoRqvr/ClTleBCqcvwZXgWfhwNU+4RT4UvwZrHPVOUNc1X5wgfgO/A5VX7wJDzhK+9f4Y1Ow99Nou9X5QFfU+UBT4n9V6r84C+q/KDKxx9gG3gGtoPKXUd4FnYT3TVuz+hp5NsVNuN2b1c/C0NgFRgmerjoLZUf2B36S7iFKiwJ9zEJtzayWcI97kM84SdQhVcM68OfYBP4Keyp6i28RswHwc/hUPglVO3jK5gKT8NJYq7y/RScLubz4DdwAfweroI/QpX/Z+DDEr6Kt5+qRzFGvN+TeDdEzku887yN/MiHem8qWFd/12DUj9WwOVwDO8D7YCd4P+wHN0i/uBGqdGyCEyBjHB3/F+Fk+BCcAhnz6PqzBebAR+EtcDtcovIWrlP1W/rLQqjS9STcAZ+Df1P1Ej6v6iV8Wa7ziqrf8A24G74Nn4ZH4V5X/6bC7GXkx42SH9WRbMkPNm/X7WozDFTxhA2VH9ga7oBXqfjAPip82Fe1L9gf7oJD1P0Pxov9dSqdMFH0H+S6Ub0=
*/