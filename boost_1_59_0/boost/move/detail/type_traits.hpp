//////////////////////////////////////////////////////////////////////////////
// (C) Copyright John Maddock 2000.
// (C) Copyright Ion Gaztanaga 2005-2015.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
// The alignment and Type traits implementation comes from
// John Maddock's TypeTraits library.
//
// Some other tricks come from Howard Hinnant's papers and StackOverflow replies
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_DETAIL_TYPE_TRAITS_HPP
#define BOOST_MOVE_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>

// move/detail
#include <boost/move/detail/meta_utils.hpp>
// other
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
// std
#include <cstddef>

//Use of Boost.TypeTraits leads to long preprocessed source code due to
//MPL dependencies. We'll use intrinsics directly and make or own
//simplified version of TypeTraits.
//If someday Boost.TypeTraits dependencies are minimized, we should
//revisit this file redirecting code to Boost.TypeTraits traits.

//These traits don't care about volatile, reference or other checks
//made by Boost.TypeTraits because no volatile or reference types
//can be hold in Boost.Containers. This helps to avoid any Boost.TypeTraits
//dependency.

// Helper macros for builtin compiler support.
// If your compiler has builtin support for any of the following
// traits concepts, then redefine the appropriate macros to pick
// up on the compiler support:
//
// (these should largely ignore cv-qualifiers)
// BOOST_MOVE_IS_POD(T) should evaluate to true if T is a POD type
// BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) should evaluate to true if "T x;" has no effect
// BOOST_MOVE_HAS_TRIVIAL_COPY(T) should evaluate to true if T(t) <==> memcpy
// (Note: this trait does not guarantee T is copy constructible, the copy constructor could be deleted but still be trivial)
// BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) should evaluate to true if T(boost::move(t)) <==> memcpy
// BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) should evaluate to true if t = u <==> memcpy
// (Note: this trait does not guarantee T is assignable , the copy assignmen could be deleted but still be trivial)
// BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T) should evaluate to true if t = boost::move(u) <==> memcpy
// BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) should evaluate to true if ~T() has no effect
// BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) should evaluate to true if "T x;" can not throw
// BOOST_MOVE_HAS_NOTHROW_COPY(T) should evaluate to true if T(t) can not throw
// BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) should evaluate to true if t = u can not throw
// BOOST_MOVE_IS_ENUM(T) should evaluate to true it t is a union type.
// BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) should evaluate to true if T has a non-throwing move constructor.
// BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T) should evaluate to true if T has a non-throwing move assignment operator.
//
// The following can also be defined: when detected our implementation is greatly simplified.
//
// BOOST_ALIGNMENT_OF(T) should evaluate to the alignment requirements of type T.

#if defined(__MSL_CPP__) && (__MSL_CPP__ >= 0x8000)
    // Metrowerks compiler is acquiring intrinsic type traits support
    // post version 8.  We hook into the published interface to pick up
    // user defined specializations as well as compiler intrinsics as
    // and when they become available:
#   include <msl_utility>
#   define BOOST_MOVE_IS_UNION(T) BOOST_STD_EXTENSION_NAMESPACE::is_union<T>::value
#   define BOOST_MOVE_IS_POD(T) BOOST_STD_EXTENSION_NAMESPACE::is_POD<T>::value
#   define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) BOOST_STD_EXTENSION_NAMESPACE::has_trivial_default_ctor<T>::value
#   define BOOST_MOVE_HAS_TRIVIAL_COPY(T) BOOST_STD_EXTENSION_NAMESPACE::has_trivial_copy_ctor<T>::value
#   define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) BOOST_STD_EXTENSION_NAMESPACE::has_trivial_assignment<T>::value
#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) BOOST_STD_EXTENSION_NAMESPACE::has_trivial_dtor<T>::value
#endif

#if (defined(BOOST_MSVC) && defined(BOOST_MSVC_FULL_VER) && (BOOST_MSVC_FULL_VER >=140050215))\
         || (defined(BOOST_INTEL) && defined(_MSC_VER) && (_MSC_VER >= 1500))
#   define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   define BOOST_MOVE_IS_POD(T)                    (__is_pod(T) && __has_trivial_constructor(T))
#   define BOOST_MOVE_IS_EMPTY(T)                  __is_empty(T)
#   define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T)   __has_trivial_constructor(T)
#   define BOOST_MOVE_HAS_TRIVIAL_COPY(T)          (__has_trivial_copy(T)|| ::boost::move_detail::is_pod<T>::value)
#   define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T)        (__has_trivial_assign(T) || ::boost::move_detail::is_pod<T>::value)
#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T)    (__has_trivial_destructor(T) || ::boost::move_detail::is_pod<T>::value)
#   define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T)   (__has_nothrow_constructor(T) || ::boost::move_detail::is_trivially_default_constructible<T>::value)
#   define BOOST_MOVE_HAS_NOTHROW_COPY(T)          (__has_nothrow_copy(T) || ::boost::move_detail::is_trivially_copy_constructible<T>::value)
#   define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T)        (__has_nothrow_assign(T) || ::boost::move_detail::is_trivially_copy_assignable<T>::value)

#   define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
#   if defined(_MSC_VER) && (_MSC_VER >= 1700)
#       define BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T)   (__has_trivial_move_constructor(T) || ::boost::move_detail::is_pod<T>::value)
#       define BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T)        (__has_trivial_move_assign(T) || ::boost::move_detail::is_pod<T>::value)
#   endif
#  if _MSC_FULL_VER >= 180020827
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T) (__is_nothrow_assignable(T&, T&&))
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) (__is_nothrow_constructible(T, T&&))
#  endif
#endif

#if defined(BOOST_CLANG)
//    BOOST_MOVE_HAS_TRAIT
#   if defined __is_identifier
#       define BOOST_MOVE_HAS_TRAIT(T) (__has_extension(T) || !__is_identifier(__##T))
#   elif defined(__has_extension)
#     define BOOST_MOVE_HAS_TRAIT(T) __has_extension(T)
#   else
#     define BOOST_MOVE_HAS_TRAIT(T) 0
#   endif

//    BOOST_MOVE_IS_UNION
#   if BOOST_MOVE_HAS_TRAIT(is_union)
#     define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   endif

//    BOOST_MOVE_IS_ENUM
#   if BOOST_MOVE_HAS_TRAIT(is_enum)
#     define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
#   endif

//    BOOST_MOVE_IS_POD
#   if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && BOOST_MOVE_HAS_TRAIT(is_pod)
#     define BOOST_MOVE_IS_POD(T) __is_pod(T)
#   endif

//    BOOST_MOVE_IS_EMPTY
#   if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && BOOST_MOVE_HAS_TRAIT(is_empty)
#     define BOOST_MOVE_IS_EMPTY(T) __is_empty(T)
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR
#   if BOOST_MOVE_HAS_TRAIT(is_constructible) && BOOST_MOVE_HAS_TRAIT(is_trivially_constructible)
#     define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) __is_trivially_constructible(T)
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_constructor)
#     define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_COPY
#   if BOOST_MOVE_HAS_TRAIT(is_constructible) && BOOST_MOVE_HAS_TRAIT(is_trivially_constructible)
#     define BOOST_MOVE_HAS_TRIVIAL_COPY(T) (__is_constructible(T, const T &) && __is_trivially_constructible(T, const T &))
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_copy)
#     define BOOST_MOVE_HAS_TRIVIAL_COPY(T) __has_trivial_copy(T)
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_ASSIGN
#   if BOOST_MOVE_HAS_TRAIT(is_assignable) && BOOST_MOVE_HAS_TRAIT(is_trivially_assignable)
#     define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) (__is_assignable(T, const T &) && __is_trivially_assignable(T, const T &))
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_copy)
#     define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) __has_trivial_assign(T)
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR
#   if BOOST_MOVE_HAS_TRAIT(is_trivially_destructible)
#     define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) __is_trivially_destructible(T)
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_destructor)
#     define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#   endif

//    BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR
#   if BOOST_MOVE_HAS_TRAIT(is_nothrow_constructible)
#     define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) __is_nothrow_constructible(T)
#   elif BOOST_MOVE_HAS_TRAIT(has_nothrow_constructor)
#     define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#   endif

//    BOOST_MOVE_HAS_NOTHROW_COPY
#   if BOOST_MOVE_HAS_TRAIT(is_constructible) && BOOST_MOVE_HAS_TRAIT(is_nothrow_constructible)
#     define BOOST_MOVE_HAS_NOTHROW_COPY(T) (__is_constructible(T, const T &) && __is_nothrow_constructible(T, const T &))
#   elif BOOST_MOVE_HAS_TRAIT(has_nothrow_copy)
#     define BOOST_MOVE_HAS_NOTHROW_COPY(T) (__has_nothrow_copy(T))
#   endif

//    BOOST_MOVE_HAS_NOTHROW_ASSIGN
#   if BOOST_MOVE_HAS_TRAIT(is_assignable) && BOOST_MOVE_HAS_TRAIT(is_nothrow_assignable)
#     define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) (__is_assignable(T, const T &) && __is_nothrow_assignable(T, const T &))
#   elif BOOST_MOVE_HAS_TRAIT(has_nothrow_assign)
#     define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T))
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR
#   if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && BOOST_MOVE_HAS_TRAIT(is_constructible) && BOOST_MOVE_HAS_TRAIT(is_trivially_constructible)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) (__is_constructible(T, T&&) && __is_trivially_constructible(T, T&&))
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_move_constructor)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) __has_trivial_move_constructor(T)
#   endif

//    BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN
#   if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && BOOST_MOVE_HAS_TRAIT(is_assignable) && BOOST_MOVE_HAS_TRAIT(is_trivially_assignable)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T) (__is_assignable(T, T&&) && __is_trivially_assignable(T, T&&))
#   elif BOOST_MOVE_HAS_TRAIT(has_trivial_move_assign)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T) __has_trivial_move_assign(T)
#   endif

//    BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR
#   if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && BOOST_MOVE_HAS_TRAIT(is_constructible) && BOOST_MOVE_HAS_TRAIT(is_nothrow_constructible)
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) (__is_constructible(T, T&&) && __is_nothrow_constructible(T, T&&))
#   elif BOOST_MOVE_HAS_TRAIT(has_nothrow_move_constructor)
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) __has_nothrow_move_constructor(T)
#   endif

//    BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN
#   if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && BOOST_MOVE_HAS_TRAIT(is_assignable) && BOOST_MOVE_HAS_TRAIT(is_nothrow_assignable)
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T) (__is_assignable(T, T&&) && __is_nothrow_assignable(T, T&&))
#   elif BOOST_MOVE_HAS_TRAIT(has_nothrow_move_assign)
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T) __has_nothrow_move_assign(T)
#   endif

//    BOOST_MOVE_ALIGNMENT_OF
#   define BOOST_MOVE_ALIGNMENT_OF(T) __alignof(T)

#endif   //#if defined(BOOST_CLANG)

#if defined(__GNUC__) && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3) && !defined(__GCCXML__))) && !defined(BOOST_CLANG)

#ifdef BOOST_INTEL
#  define BOOST_MOVE_INTEL_TT_OPTS || ::boost::move_detail::is_pod<T>::value
#else
#  define BOOST_MOVE_INTEL_TT_OPTS
#endif

#   define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   define BOOST_MOVE_IS_POD(T) __is_pod(T)
#   define BOOST_MOVE_IS_EMPTY(T) __is_empty(T)
#   define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) ((__has_trivial_constructor(T) BOOST_MOVE_INTEL_TT_OPTS))

#   if defined(BOOST_GCC) && (BOOST_GCC > 50000)
#     define BOOST_MOVE_HAS_TRIVIAL_COPY(T) (__is_trivially_constructible(T, const T &))
#     define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) (__is_trivially_assignable(T, const T &))
#   else
#     define BOOST_MOVE_HAS_TRIVIAL_COPY(T) ((__has_trivial_copy(T) BOOST_MOVE_INTEL_TT_OPTS))
#     define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) ((__has_trivial_assign(T) BOOST_MOVE_INTEL_TT_OPTS) )
#   endif

#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) BOOST_MOVE_INTEL_TT_OPTS)
#   define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) BOOST_MOVE_INTEL_TT_OPTS)
#   define BOOST_MOVE_HAS_NOTHROW_COPY(T) ((__has_nothrow_copy(T) BOOST_MOVE_INTEL_TT_OPTS))
#   define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) ((__has_nothrow_assign(T) BOOST_MOVE_INTEL_TT_OPTS))

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_SFINAE_EXPR)

   template <typename T>
   T && boost_move_tt_declval() BOOST_NOEXCEPT;

#  if defined(BOOST_GCC) && (BOOST_GCC >= 80000)
// __is_assignable / __is_constructible implemented
#     define BOOST_MOVE_IS_ASSIGNABLE(T, U)     __is_assignable(T, U)
#     define BOOST_MOVE_IS_CONSTRUCTIBLE(T, U)  __is_constructible(T, U)
#  else

   template<typename Tt, typename Ut>
   class boost_move_tt_is_assignable
   {
      struct twochar {  char dummy[2]; };
      template < class T
               , class U
               , class = decltype(boost_move_tt_declval<T>() = boost_move_tt_declval<U>())
               > static char test(int);

      template<class, class> static twochar test(...);

      public:
      static const bool value = sizeof(test<Tt, Ut>(0)) == sizeof(char);
   };

   template<typename Tt, typename Ut>
   class boost_move_tt_is_constructible
   {
      struct twochar {  char dummy[2]; };
      template < class T
               , class U
               , class = decltype(T(boost_move_tt_declval<U>()))
               > static char test(int);

      template<class, class> static twochar test(...);

      public:
      static const bool value = sizeof(test<Tt, Ut>(0)) == sizeof(char);
   };

#     define BOOST_MOVE_IS_ASSIGNABLE(T, U)     boost_move_tt_is_assignable<T,U>::value
#     define BOOST_MOVE_IS_CONSTRUCTIBLE(T, U)  boost_move_tt_is_constructible<T, U>::value

#  endif

   template <typename T, typename U, bool = BOOST_MOVE_IS_ASSIGNABLE(T, U)>
   struct boost_move_tt_is_nothrow_assignable
   {
      static const bool value = false;
   };

   template <typename T, typename U>
   struct boost_move_tt_is_nothrow_assignable<T, U, true>
   {
      #if !defined(BOOST_NO_CXX11_NOEXCEPT)
      static const bool value = noexcept(boost_move_tt_declval<T>() = boost_move_tt_declval<U>());
      #else
      static const bool value = false;
      #endif
   };

   template <typename T, typename U, bool = BOOST_MOVE_IS_CONSTRUCTIBLE(T, U)>
   struct boost_move_tt_is_nothrow_constructible
   {
      static const bool value = false;
   };

   template <typename T, typename U>
   struct boost_move_tt_is_nothrow_constructible<T, U, true>
   {
      #if !defined(BOOST_NO_CXX11_NOEXCEPT)
      static const bool value = noexcept(T(boost_move_tt_declval<U>()));
      #else
      static const bool value = false;
      #endif
   };

#     define BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T)       boost_move_tt_is_nothrow_assignable<T, T&&>::value
#     define BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T)  boost_move_tt_is_nothrow_constructible<T, T&&>::value

#  endif

#   define BOOST_MOVE_IS_ENUM(T) __is_enum(T)

// BOOST_MOVE_ALIGNMENT_OF
#   if (!defined(unix) && !defined(__unix__)) || defined(__LP64__)
      // GCC sometimes lies about alignment requirements
      // of type double on 32-bit unix platforms, use the
      // old implementation instead in that case:
#     define BOOST_MOVE_ALIGNMENT_OF(T) __alignof__(T)
#   endif
#endif

#if defined(__ghs__) && (__GHS_VERSION_NUMBER >= 600)

#   define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   define BOOST_MOVE_IS_POD(T) __is_pod(T)
#   define BOOST_MOVE_IS_EMPTY(T) __is_empty(T)
#   define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#   define BOOST_MOVE_HAS_TRIVIAL_COPY(T) (__has_trivial_copy(T))
#   define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T))
#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#   define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#   define BOOST_MOVE_HAS_NOTHROW_COPY(T) (__has_nothrow_copy(T))
#   define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T))

#   define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
#   define BOOST_MOVE_ALIGNMENT_OF(T) __alignof__(T)
#endif

# if defined(BOOST_CODEGEARC)
#   define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   define BOOST_MOVE_IS_POD(T) __is_pod(T)
#   define BOOST_MOVE_IS_EMPTY(T) __is_empty(T)
#   define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) (__has_trivial_default_constructor(T))
#   define BOOST_MOVE_HAS_TRIVIAL_COPY(T) (__has_trivial_copy_constructor(T))
#   define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T))
#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T))
#   define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_default_constructor(T))
#   define BOOST_MOVE_HAS_NOTHROW_COPY(T) (__has_nothrow_copy_constructor(T))
#   define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T))

#   define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
#   define BOOST_MOVE_ALIGNMENT_OF(T) alignof(T)

#endif

//Fallback definitions

#ifdef BOOST_MOVE_IS_UNION
   #define BOOST_MOVE_IS_UNION_IMPL(T) BOOST_MOVE_IS_UNION(T)
#else
   #define BOOST_MOVE_IS_UNION_IMPL(T) false
#endif

#ifdef BOOST_MOVE_IS_POD
   //in some compilers the intrinsic is limited to class types so add scalar and void
   #define BOOST_MOVE_IS_POD_IMPL(T) (::boost::move_detail::is_scalar<T>::value ||\
                                      ::boost::move_detail::is_void<T>::value   ||\
                                       BOOST_MOVE_IS_POD(T))
#else
   #define BOOST_MOVE_IS_POD_IMPL(T) \
      (::boost::move_detail::is_scalar<T>::value || ::boost::move_detail::is_void<T>::value)
#endif

#ifdef BOOST_MOVE_IS_EMPTY
   #define BOOST_MOVE_IS_EMPTY_IMPL(T) BOOST_MOVE_IS_EMPTY(T)
#else
   #define BOOST_MOVE_IS_EMPTY_IMPL(T)    ::boost::move_detail::is_empty_nonintrinsic<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_COPY
   #define BOOST_MOVE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value ||\
                                                          (::boost::move_detail::is_copy_constructible<T>::value &&\
                                                           BOOST_MOVE_HAS_TRIVIAL_COPY(T))
#else
   #define BOOST_MOVE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR
   #define BOOST_MOVE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T)  BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_ASSIGN
   #define BOOST_MOVE_IS_TRIVIALLY_COPY_ASSIGNABLE(T) ::boost::move_detail::is_pod<T>::value ||\
                                                      ( ::boost::move_detail::is_copy_assignable<T>::value &&\
                                                         BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T))
#else
   #define BOOST_MOVE_IS_TRIVIALLY_COPY_ASSIGNABLE(T) ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)  BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR
   #define BOOST_MOVE_IS_TRIVIALLY_DESTRUCTIBLE(T)   BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_TRIVIALLY_DESTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR
   #define BOOST_MOVE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(T)  BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_COPY
   #define BOOST_MOVE_IS_NOTHROW_COPY_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_NOTHROW_COPY(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_NOTHROW_COPY_CONSTRUCTIBLE(T)   BOOST_MOVE_IS_TRIVIALLY_COPY_ASSIGNABLE(T)
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_ASSIGN
   #define BOOST_MOVE_IS_NOTHROW_COPY_ASSIGNABLE(T) BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_NOTHROW_COPY_ASSIGNABLE(T) BOOST_MOVE_IS_TRIVIALLY_COPY_ASSIGNABLE(T)
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR
   #define BOOST_MOVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_NOTHROW_MOVE_CONSTRUCTOR(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T)   BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN
   #define BOOST_MOVE_IS_NOTHROW_MOVE_ASSIGNABLE(T) BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T) || ::boost::move_detail::is_pod<T>::value
#else
   #define BOOST_MOVE_IS_NOTHROW_MOVE_ASSIGNABLE(T) BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)
#endif

#ifdef BOOST_MOVE_IS_ENUM
   #define BOOST_MOVE_IS_ENUM_IMPL(T)   BOOST_MOVE_IS_ENUM(T)
#else
   #define BOOST_MOVE_IS_ENUM_IMPL(T)   ::boost::move_detail::is_enum_nonintrinsic<T>::value
#endif

namespace boost {
namespace move_detail {

//////////////////////////
//    is_reference
//////////////////////////
template<class T>
struct is_reference
{  static const bool value = false; };

template<class T>
struct is_reference<T&>
{  static const bool value = true; };

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
template<class T>
struct is_reference<T&&>
{  static const bool value = true; };
#endif

//////////////////////////
//    is_pointer
//////////////////////////
template<class T>
struct is_pointer
{  static const bool value = false; };

template<class T>
struct is_pointer<T*>
{  static const bool value = true; };

//////////////////////////
//       is_const
//////////////////////////
template<class T>
struct is_const
{  static const bool value = false; };

template<class T>
struct is_const<const T>
{  static const bool value = true; };

//////////////////////////
//       unvoid_ref
//////////////////////////
template <typename T> struct unvoid_ref : add_lvalue_reference<T>{};
template <> struct unvoid_ref<void>                { typedef unvoid_ref & type; };
template <> struct unvoid_ref<const void>          { typedef unvoid_ref & type; };
template <> struct unvoid_ref<volatile void>       { typedef unvoid_ref & type; };
template <> struct unvoid_ref<const volatile void> { typedef unvoid_ref & type; };

template <typename T>
struct add_reference : add_lvalue_reference<T>
{};

//////////////////////////
//    add_const_reference
//////////////////////////
template <class T>
struct add_const_reference
{  typedef const T &type;   };

template <class T>
struct add_const_reference<T&>
{  typedef T& type;   };

//////////////////////////
//    add_const_if_c
//////////////////////////
template<class T, bool Add>
struct add_const_if_c
   : if_c<Add, typename add_const<T>::type, T>
{};

//////////////////////////
//    remove_const
//////////////////////////
template<class T>
struct remove_const
{  typedef T type;   };

template<class T>
struct remove_const< const T>
{  typedef T type;   };

//////////////////////////
//    remove_cv
//////////////////////////
template<typename T> struct remove_cv                    {  typedef T type;   };
template<typename T> struct remove_cv<const T>           {  typedef T type;   };
template<typename T> struct remove_cv<const volatile T>  {  typedef T type;   };
template<typename T> struct remove_cv<volatile T>        {  typedef T type;   };

//////////////////////////
//    remove_cvref
//////////////////////////
template<class T>
struct remove_cvref
   : remove_cv<typename remove_reference<T>::type>
{
};

//////////////////////////
//    make_unsigned
//////////////////////////
template <class T>
struct make_unsigned_impl                                         {  typedef T type;   };
template <> struct make_unsigned_impl<signed char>                {  typedef unsigned char  type; };
template <> struct make_unsigned_impl<signed short>               {  typedef unsigned short type; };
template <> struct make_unsigned_impl<signed int>                 {  typedef unsigned int   type; };
template <> struct make_unsigned_impl<signed long>                {  typedef unsigned long  type; };
#ifdef BOOST_HAS_LONG_LONG
template <> struct make_unsigned_impl< ::boost::long_long_type >  {  typedef ::boost::ulong_long_type type; };
#endif

template <class T>
struct make_unsigned
   : make_unsigned_impl<typename remove_cv<T>::type>
{};

//////////////////////////
//    is_floating_point
//////////////////////////
template<class T> struct is_floating_point_cv               {  static const bool value = false; };
template<>        struct is_floating_point_cv<float>        {  static const bool value = true; };
template<>        struct is_floating_point_cv<double>       {  static const bool value = true; };
template<>        struct is_floating_point_cv<long double>  {  static const bool value = true; };

template<class T>
struct is_floating_point
   : is_floating_point_cv<typename remove_cv<T>::type>
{};

//////////////////////////
//    is_integral
//////////////////////////
template<class T> struct is_integral_cv                    {  static const bool value = false; };
template<> struct is_integral_cv<                     bool>{  static const bool value = true; };
template<> struct is_integral_cv<                     char>{  static const bool value = true; };
template<> struct is_integral_cv<            unsigned char>{  static const bool value = true; };
template<> struct is_integral_cv<              signed char>{  static const bool value = true; };
#ifndef BOOST_NO_CXX11_CHAR16_T
template<> struct is_integral_cv<                 char16_t>{  static const bool value = true; };
#endif
#ifndef BOOST_NO_CXX11_CHAR32_T
template<> struct is_integral_cv<                 char32_t>{  static const bool value = true; };
#endif
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template<> struct is_integral_cv<                  wchar_t>{  static const bool value = true; };
#endif
template<> struct is_integral_cv<                    short>{  static const bool value = true; };
template<> struct is_integral_cv<           unsigned short>{  static const bool value = true; };
template<> struct is_integral_cv<                      int>{  static const bool value = true; };
template<> struct is_integral_cv<             unsigned int>{  static const bool value = true; };
template<> struct is_integral_cv<                     long>{  static const bool value = true; };
template<> struct is_integral_cv<            unsigned long>{  static const bool value = true; };
#ifdef BOOST_HAS_LONG_LONG
template<> struct is_integral_cv< ::boost:: long_long_type>{  static const bool value = true; };
template<> struct is_integral_cv< ::boost::ulong_long_type>{  static const bool value = true; };
#endif

template<class T>
struct is_integral
   : public is_integral_cv<typename remove_cv<T>::type>
{};

//////////////////////////////////////
//          remove_all_extents
//////////////////////////////////////
template <class T>
struct remove_all_extents
{  typedef T type;};

template <class T>
struct remove_all_extents<T[]>
{  typedef typename remove_all_extents<T>::type type; };

template <class T, std::size_t N>
struct remove_all_extents<T[N]>
{  typedef typename remove_all_extents<T>::type type;};

//////////////////////////
//    is_scalar
//////////////////////////
template<class T>
struct is_scalar
{  static const bool value = is_integral<T>::value || is_floating_point<T>::value; };

//////////////////////////
//       is_void
//////////////////////////
template<class T>
struct is_void_cv
{  static const bool value = false; };

template<>
struct is_void_cv<void>
{  static const bool value = true; };

template<class T>
struct is_void
   : is_void_cv<typename remove_cv<T>::type>
{};

//////////////////////////////////////
//          is_array
//////////////////////////////////////
template<class T>
struct is_array
{  static const bool value = false; };

template<class T>
struct is_array<T[]>
{  static const bool value = true;  };

template<class T, std::size_t N>
struct is_array<T[N]>
{  static const bool value = true;  };

//////////////////////////////////////
//           is_member_pointer
//////////////////////////////////////
template <class T>         struct is_member_pointer_cv         {  static const bool value = false; };
template <class T, class U>struct is_member_pointer_cv<T U::*> {  static const bool value = true; };

template <class T>
struct is_member_pointer
    : is_member_pointer_cv<typename remove_cv<T>::type>
{};

//////////////////////////////////////
//          is_nullptr_t
//////////////////////////////////////
template <class T>
struct is_nullptr_t_cv
{  static const bool value = false; };

#if !defined(BOOST_NO_CXX11_NULLPTR)
template <>
struct is_nullptr_t_cv
   #if !defined(BOOST_NO_CXX11_DECLTYPE)
   <decltype(nullptr)>
   #else
   <std::nullptr_t>
   #endif
{  static const bool value = true; };
#endif

template <class T>
struct is_nullptr_t
   : is_nullptr_t_cv<typename remove_cv<T>::type>
{};

//////////////////////////////////////
//          is_function
//////////////////////////////////////
//Inspired by libc++, thanks to Howard Hinnant
//For a function to pointer an lvalue of function type T can be implicitly converted to a prvalue
//pointer to that function. This does not apply to non-static member functions because lvalues
//that refer to non-static member functions do not exist.
template <class T>
struct is_reference_convertible_to_pointer
{
   struct twochar { char dummy[2]; };
   template <class U> static char    test(U*);
   template <class U> static twochar test(...);
   static T& source();
   static const bool value = sizeof(char) == sizeof(test<T>(source()));
};
//Filter out:
// - class types that might have implicit conversions
// - void (to avoid forming a reference to void later)
// - references (e.g.: filtering reference to functions)
// - nullptr_t (convertible to pointer)
template < class T
         , bool Filter = is_class_or_union<T>::value  ||
                         is_void<T>::value            ||
                         is_reference<T>::value       ||
                         is_nullptr_t<T>::value       >
struct is_function_impl
{  static const bool value = is_reference_convertible_to_pointer<T>::value; };

template <class T>
struct is_function_impl<T, true>
{  static const bool value = false; };

template <class T>
struct is_function
   : is_function_impl<T>
{};

//////////////////////////////////////
//       is_union
//////////////////////////////////////
template<class T>
struct is_union_noextents_cv
{  static const bool value = BOOST_MOVE_IS_UNION_IMPL(T); };

template<class T>
struct is_union
   : is_union_noextents_cv<typename remove_cv<typename remove_all_extents<T>::type>::type>
{};

//////////////////////////////////////
//             is_class
//////////////////////////////////////
template <class T>
struct is_class
{
   static const bool value = is_class_or_union<T>::value && ! is_union<T>::value;
};


//////////////////////////////////////
//             is_arithmetic
//////////////////////////////////////
template <class T>
struct is_arithmetic
{
   static const bool value = is_floating_point<T>::value ||
                             is_integral<T>::value;
};

//////////////////////////////////////
//    is_member_function_pointer
//////////////////////////////////////
template <class T>
struct is_member_function_pointer_cv
{
   static const bool value = false;
};

template <class T, class C>
struct is_member_function_pointer_cv<T C::*>
   : is_function<T>
{};

template <class T>
struct is_member_function_pointer
    : is_member_function_pointer_cv<typename remove_cv<T>::type>
{};

//////////////////////////////////////
//             is_enum
//////////////////////////////////////
#if !defined(BOOST_MOVE_IS_ENUM)
//Based on (http://howardhinnant.github.io/TypeHiearchy.pdf)
template <class T>
struct is_enum_nonintrinsic
{
   static const bool value =  !is_arithmetic<T>::value     &&
                              !is_reference<T>::value      &&
                              !is_class_or_union<T>::value &&
                              !is_array<T>::value          &&
                              !is_void<T>::value           &&
                              !is_nullptr_t<T>::value      &&
                              !is_member_pointer<T>::value &&
                              !is_pointer<T>::value        &&
                              !is_function<T>::value;
};
#endif

template <class T>
struct is_enum
{  static const bool value = BOOST_MOVE_IS_ENUM_IMPL(T);  };

//////////////////////////////////////
//       is_pod
//////////////////////////////////////
template<class T>
struct is_pod_noextents_cv  //for non-c++11 compilers, a safe fallback
{  static const bool value = BOOST_MOVE_IS_POD_IMPL(T); };

template<class T>
struct is_pod
   : is_pod_noextents_cv<typename remove_cv<typename remove_all_extents<T>::type>::type>
{};

//////////////////////////////////////
//             is_empty
//////////////////////////////////////
#if !defined(BOOST_MOVE_IS_EMPTY)

template <typename T>
struct empty_helper_t1 : public T
{
   empty_helper_t1();  // hh compiler bug workaround
   int i[256];
   private:

   empty_helper_t1(const empty_helper_t1&);
   empty_helper_t1& operator=(const empty_helper_t1&);
};

struct empty_helper_t2 { int i[256]; };

template <typename T, bool IsClass = is_class<T>::value >
struct is_empty_nonintrinsic
{
   static const bool value = false;
};

template <typename T>
struct is_empty_nonintrinsic<T, true>
{
   static const bool value = sizeof(empty_helper_t1<T>) == sizeof(empty_helper_t2);
};
#endif

template <class T>
struct is_empty
{  static const bool value = BOOST_MOVE_IS_EMPTY_IMPL(T);  };


template<class T>
struct has_boost_move_no_copy_constructor_or_assign_type
{
   template <class U>
   static yes_type test(typename U::boost_move_no_copy_constructor_or_assign*);

   template <class U>
   static no_type test(...);

   static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);
};

//////////////////////////////////////
//       is_copy_constructible
//////////////////////////////////////
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) && !defined(BOOST_NO_CXX11_DECLTYPE) \
   && !defined(BOOST_INTEL_CXX_VERSION) && \
      !(defined(BOOST_MSVC) && _MSC_VER == 1800)
#define BOOST_MOVE_TT_CXX11_IS_COPY_CONSTRUCTIBLE
#endif

template<class T>
struct is_copy_constructible
{
   // Intel compiler has problems with SFINAE for copy constructors and deleted functions:
   //
   // error: function *function_name* cannot be referenced -- it is a deleted function
   // static yes_type test(U&, decltype(U(boost::declval<U&>()))* = 0);
   //                                                        ^ 
   // MSVC 12.0 (Visual 2013) has problems when the copy constructor has been deleted. See:
   // https://connect.microsoft.com/VisualStudio/feedback/details/800328/std-is-copy-constructible-is-broken
   #if defined(BOOST_MOVE_TT_CXX11_IS_COPY_CONSTRUCTIBLE)
      template<class U> static typename add_reference<U>::type source();
      static no_type test(...);
      #ifdef BOOST_NO_CXX11_DECLTYPE
         template <class U>
         static yes_type test(U&, bool_<sizeof(U(source<U>()))>* = 0);
      #else
         template <class U>
         static yes_type test(U&, decltype(U(source<U>()))* = 0);
      #endif
      static const bool value = sizeof(test(source<T>())) == sizeof(yes_type);
   #else
   static const bool value = !has_boost_move_no_copy_constructor_or_assign_type<T>::value;
   #endif
};


//////////////////////////////////////
//       is_copy_assignable
//////////////////////////////////////
#if !defined(BOOST_NO_CXX11_DELETED_FUNCTIONS) && !defined(BOOST_NO_CXX11_DECLTYPE) \
   && !defined(BOOST_INTEL_CXX_VERSION) && \
      !(defined(BOOST_MSVC) && _MSC_VER == 1800)
#define BOOST_MOVE_TT_CXX11_IS_COPY_ASSIGNABLE
#endif

template <class T>
struct is_copy_assignable
{
// Intel compiler has problems with SFINAE for copy constructors and deleted functions:
//
// error: function *function_name* cannot be referenced -- it is a deleted function
// static boost::type_traits::yes_type test(T1&, decltype(T1(boost::declval<T1&>()))* = 0);
//                                                        ^ 
//
// MSVC 12.0 (Visual 2013) has problems when the copy constructor has been deleted. See:
// https://connect.microsoft.com/VisualStudio/feedback/details/800328/std-is-copy-constructible-is-broken
#if defined(BOOST_MOVE_TT_CXX11_IS_COPY_ASSIGNABLE)
   typedef char yes_type;
   struct no_type { char dummy[2]; };
   
   template <class U>   static typename add_reference<U>::type source();
   template <class U>   static decltype(source<U&>() = source<const U&>(), yes_type() ) test(int);
   template <class>     static no_type test(...);

   static const bool value = sizeof(test<T>(0)) == sizeof(yes_type);
#else
   static const bool value = !has_boost_move_no_copy_constructor_or_assign_type<T>::value;
#endif
};

//////////////////////////////////////
//       is_trivially_destructible
//////////////////////////////////////
template<class T>
struct is_trivially_destructible
{  static const bool value = BOOST_MOVE_IS_TRIVIALLY_DESTRUCTIBLE(T); };

//////////////////////////////////////
//       is_trivially_default_constructible
//////////////////////////////////////
template<class T>
struct is_trivially_default_constructible
{  static const bool value = BOOST_MOVE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T); };

//////////////////////////////////////
//       is_trivially_copy_constructible
//////////////////////////////////////
template<class T>
struct is_trivially_copy_constructible
{
   static const bool value = BOOST_MOVE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE(T);
};

//////////////////////////////////////
//       is_trivially_move_constructible
//////////////////////////////////////
template<class T>
struct is_trivially_move_constructible
{ static const bool value = BOOST_MOVE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T); };

//////////////////////////////////////
//       is_trivially_copy_assignable
//////////////////////////////////////
template<class T>
struct is_trivially_copy_assignable
{
   static const bool value = BOOST_MOVE_IS_TRIVIALLY_COPY_ASSIGNABLE(T);
};                             

//////////////////////////////////////
//       is_trivially_move_assignable
//////////////////////////////////////
template<class T>
struct is_trivially_move_assignable
{  static const bool value = BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T);  };

//////////////////////////////////////
//       is_nothrow_default_constructible
//////////////////////////////////////
template<class T>
struct is_nothrow_default_constructible
{  static const bool value = BOOST_MOVE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(T);  };

//////////////////////////////////////
//    is_nothrow_copy_constructible
//////////////////////////////////////
template<class T>
struct is_nothrow_copy_constructible
{  static const bool value = BOOST_MOVE_IS_NOTHROW_COPY_CONSTRUCTIBLE(T);  };

//////////////////////////////////////
//    is_nothrow_move_constructible
//////////////////////////////////////
template<class T>
struct is_nothrow_move_constructible
{  static const bool value = BOOST_MOVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T);  };

//////////////////////////////////////
//       is_nothrow_copy_assignable
//////////////////////////////////////
template<class T>
struct is_nothrow_copy_assignable
{  static const bool value = BOOST_MOVE_IS_NOTHROW_COPY_ASSIGNABLE(T);  };

//////////////////////////////////////
//    is_nothrow_move_assignable
//////////////////////////////////////
template<class T>
struct is_nothrow_move_assignable
{  static const bool value = BOOST_MOVE_IS_NOTHROW_MOVE_ASSIGNABLE(T);  };

//////////////////////////////////////
//    is_nothrow_swappable
//////////////////////////////////////
template<class T>
struct is_nothrow_swappable
{
   static const bool value = is_empty<T>::value || is_pod<T>::value;
};

//////////////////////////////////////
//       alignment_of
//////////////////////////////////////
template <typename T>
struct alignment_of_hack
{
   T t1;
   char c;
   T t2;
   alignment_of_hack();
   ~alignment_of_hack();
};

template <unsigned A, unsigned S>
struct alignment_logic
{  static const std::size_t value = A < S ? A : S; };

template< typename T >
struct alignment_of_impl
#if defined(BOOST_MSVC) && (BOOST_MSVC >= 1400)
    // With MSVC both the native __alignof operator
    // and our own logic gets things wrong from time to time :-(
    // Using a combination of the two seems to make the most of a bad job:
   : alignment_logic< sizeof(alignment_of_hack<T>) - 2*sizeof(T), __alignof(T)>
{};
#elif !defined(BOOST_MOVE_ALIGNMENT_OF)
   : alignment_logic< sizeof(alignment_of_hack<T>) - 2*sizeof(T), sizeof(T)>
{};
#else
{  static const std::size_t value = BOOST_MOVE_ALIGNMENT_OF(T);  };
#endif

template< typename T >
struct alignment_of
   : alignment_of_impl<T>
{};

class alignment_dummy;
typedef void (*function_ptr)();
typedef int (alignment_dummy::*member_ptr);

struct alignment_struct
{  long double dummy[4];  };

/////////////////////////////
//    max_align_t
/////////////////////////////
//This is not standard, but should work with all compilers
union max_align
{
   char        char_;
   short       short_;
   int         int_;
   long        long_;
   #ifdef BOOST_HAS_LONG_LONG
   ::boost::long_long_type   long_long_;
   #endif
   float       float_;
   double      double_;
   void *      void_ptr_;
   long double long_double_[4];
   alignment_dummy *unknown_class_ptr_;
   function_ptr function_ptr_;
   alignment_struct alignment_struct_;
};

typedef union max_align max_align_t;

/////////////////////////////
//    aligned_storage
/////////////////////////////

#if defined(_MSC_VER) && defined(_M_IX86)

// Special version for usual alignments on x86 MSVC because it might crash
// when passsing aligned types by value even for 8 byte alignment.
template<std::size_t Align>
struct aligned_struct;

template <> struct aligned_struct<1> { char data; };
template <> struct aligned_struct<2> { short data; };
template <> struct aligned_struct<4> { int data; };
template <> struct aligned_struct<8> { double data; };

#define BOOST_MOVE_ALIGNED_STRUCT(x) \
  template <> struct aligned_struct<x> { \
    __declspec(align(x)) char data; \
  }
BOOST_MOVE_ALIGNED_STRUCT(16);
BOOST_MOVE_ALIGNED_STRUCT(32);
BOOST_MOVE_ALIGNED_STRUCT(64);
BOOST_MOVE_ALIGNED_STRUCT(128);
BOOST_MOVE_ALIGNED_STRUCT(512);
BOOST_MOVE_ALIGNED_STRUCT(1024);
BOOST_MOVE_ALIGNED_STRUCT(2048);
BOOST_MOVE_ALIGNED_STRUCT(4096);

template<std::size_t Len, std::size_t Align>
union aligned_union
{
   typedef aligned_struct<Align> aligner_t;
   aligner_t aligner;
   unsigned char data[Len > sizeof(aligner_t) ? Len : sizeof(aligner_t)];
};

template<std::size_t Len, std::size_t Align>
struct aligned_storage_impl
{
   typedef aligned_union<Len, Align> type;
};

#elif !defined(BOOST_NO_ALIGNMENT)

template<std::size_t Len, std::size_t Align>
struct aligned_struct;

#define BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(A)\
template<std::size_t Len>\
struct BOOST_ALIGNMENT(A) aligned_struct<Len, A>\
{\
   unsigned char data[Len];\
};\
//

//Up to 4K alignment (typical page size)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x1)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x2)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x4)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x8)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x10)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x20)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x40)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x80)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x100)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x200)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x400)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x800)
BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT(0x1000)

#undef BOOST_MOVE_ALIGNED_STORAGE_WITH_BOOST_ALIGNMENT

// Workaround for bogus [-Wignored-attributes] warning on GCC 6.x/7.x: don't use a type that "directly" carries the alignment attribute.
// See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=82270
template<std::size_t Len, std::size_t Align>
union aligned_struct_wrapper
{
   typedef aligned_struct<Len, Align> aligner_t;
   aligned_struct<Len, Align> aligner;
   unsigned char data[Len > sizeof(aligner_t) ? Len : sizeof(aligner_t)];
};

template<std::size_t Len, std::size_t Align>
struct aligned_storage_impl
{
   typedef aligned_struct_wrapper<Len, Align> type;
};

#else //BOOST_NO_ALIGNMENT

template<class T, std::size_t Len>
union aligned_union
{   
   T aligner;
   unsigned char data[Len > sizeof(T) ? Len : sizeof(T)];
};

template<std::size_t Len, std::size_t Align, class T, bool Ok>
struct aligned_next;

template<std::size_t Len, std::size_t Align, class T>
struct aligned_next<Len, Align, T, true>
{
   BOOST_STATIC_ASSERT((alignment_of<T>::value == Align));
   typedef aligned_union<T, Len> type;
};

//End of search defaults to max_align_t
template<std::size_t Len, std::size_t Align>
struct aligned_next<Len, Align, max_align_t, false>
{   typedef aligned_union<max_align_t, Len> type;   };

//Now define a search list through types
#define BOOST_MOVE_ALIGNED_NEXT_STEP(TYPE, NEXT_TYPE)\
   template<std::size_t Len, std::size_t Align>\
   struct aligned_next<Len, Align, TYPE, false>\
      : aligned_next<Len, Align, NEXT_TYPE, Align == alignment_of<NEXT_TYPE>::value>\
   {};\
   //
   BOOST_MOVE_ALIGNED_NEXT_STEP(long double, max_align_t)
   BOOST_MOVE_ALIGNED_NEXT_STEP(double, long double)
   #ifdef BOOST_HAS_LONG_LONG
      BOOST_MOVE_ALIGNED_NEXT_STEP(::boost::long_long_type, double)
      BOOST_MOVE_ALIGNED_NEXT_STEP(long, ::boost::long_long_type)
   #else
      BOOST_MOVE_ALIGNED_NEXT_STEP(long, double)
   #endif
   BOOST_MOVE_ALIGNED_NEXT_STEP(int, long)
   BOOST_MOVE_ALIGNED_NEXT_STEP(short, int)
   BOOST_MOVE_ALIGNED_NEXT_STEP(char, short)
#undef BOOST_MOVE_ALIGNED_NEXT_STEP

template<std::size_t Len, std::size_t Align>
struct aligned_storage_impl
   : aligned_next<Len, Align, char, Align == alignment_of<char>::value>
{};

#endif

template<std::size_t Len, std::size_t Align = alignment_of<max_align_t>::value>
struct aligned_storage
{
   //Sanity checks for input parameters
   BOOST_STATIC_ASSERT(Align > 0);

   //Sanity checks for output type
   typedef typename aligned_storage_impl<Len ? Len : 1, Align>::type type;
   static const std::size_t value = alignment_of<type>::value;
   BOOST_STATIC_ASSERT(value >= Align);
   BOOST_STATIC_ASSERT((value % Align) == 0);

   //Just in case someone instantiates aligned_storage
   //instead of aligned_storage::type (typical error).
   private:
   aligned_storage();
};

}  //namespace move_detail {
}  //namespace boost {

#include <boost/move/detail/config_end.hpp>

#endif   //#ifndef BOOST_MOVE_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
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
*/