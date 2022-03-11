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
#endif

#if defined(BOOST_CLANG) && defined(__has_feature)

#   if __has_feature(is_union)
#     define BOOST_MOVE_IS_UNION(T) __is_union(T)
#   endif
#   if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && __has_feature(is_pod)
#     define BOOST_MOVE_IS_POD(T) __is_pod(T)
#   endif
#   if (!defined(__GLIBCXX__) || (__GLIBCXX__ >= 20080306 && __GLIBCXX__ != 20080519)) && __has_feature(is_empty)
#     define BOOST_MOVE_IS_EMPTY(T) __is_empty(T)
#   endif
#   if __has_feature(has_trivial_constructor)
#     define BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T) __has_trivial_constructor(T)
#   endif
#   if __has_feature(has_trivial_copy)
#     define BOOST_MOVE_HAS_TRIVIAL_COPY(T) __has_trivial_copy(T)
#   endif
#   if __has_feature(has_trivial_assign)
#     define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) (__has_trivial_assign(T) )
#   endif
#   if __has_feature(has_trivial_destructor)
#     define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) __has_trivial_destructor(T)
#   endif
#   if __has_feature(has_nothrow_constructor)
#     define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) __has_nothrow_constructor(T)
#   endif
#   if __has_feature(has_nothrow_copy)
#     define BOOST_MOVE_HAS_NOTHROW_COPY(T) (__has_nothrow_copy(T))
#   endif
#   if __has_feature(is_nothrow_copy_assignable)
#     define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) (__has_nothrow_assign(T))
#   endif
#   if __has_feature(is_enum)
#     define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
#   endif
#   if __has_feature(has_trivial_move_constructor)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T) __has_trivial_move_constructor(T)
#   endif
#   if __has_feature(has_trivial_move_assign)
#     define BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T) __has_trivial_move_assign(T)
#   endif
#   define BOOST_MOVE_ALIGNMENT_OF(T) __alignof(T)
#endif

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
#   define BOOST_MOVE_HAS_TRIVIAL_COPY(T) ((__has_trivial_copy(T) BOOST_MOVE_INTEL_TT_OPTS))
#   define BOOST_MOVE_HAS_TRIVIAL_ASSIGN(T) ((__has_trivial_assign(T) BOOST_MOVE_INTEL_TT_OPTS) )
#   define BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T) (__has_trivial_destructor(T) BOOST_MOVE_INTEL_TT_OPTS)
#   define BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T) (__has_nothrow_constructor(T) BOOST_MOVE_INTEL_TT_OPTS)
#   define BOOST_MOVE_HAS_NOTHROW_COPY(T) ((__has_nothrow_copy(T) BOOST_MOVE_INTEL_TT_OPTS))
#   define BOOST_MOVE_HAS_NOTHROW_ASSIGN(T) ((__has_nothrow_assign(T) BOOST_MOVE_INTEL_TT_OPTS))

#   define BOOST_MOVE_IS_ENUM(T) __is_enum(T)
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

# if defined(__CODEGEARC__)
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
   #define BOOST_MOVE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T)  BOOST_MOVE_HAS_TRIVIAL_CONSTRUCTOR(T)
#else
   #define BOOST_MOVE_IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_TRIVIAL_MOVE_CONSTRUCTOR(T)
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
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)  BOOST_MOVE_HAS_TRIVIAL_MOVE_ASSIGN(T)
#else
   #define BOOST_MOVE_IS_TRIVIALLY_MOVE_ASSIGNABLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR
   #define BOOST_MOVE_IS_TRIVIALLY_DESTRUCTIBLE(T)   BOOST_MOVE_HAS_TRIVIAL_DESTRUCTOR(T)
#else
   #define BOOST_MOVE_IS_TRIVIALLY_DESTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR
   #define BOOST_MOVE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(T)  BOOST_MOVE_HAS_NOTHROW_CONSTRUCTOR(T)
#else
   #define BOOST_MOVE_IS_NOTHROW_DEFAULT_CONSTRUCTIBLE(T)  ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_COPY
   #define BOOST_MOVE_IS_NOTHROW_COPY_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_NOTHROW_COPY(T)
#else
   #define BOOST_MOVE_IS_NOTHROW_COPY_CONSTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_MOVE
   #define BOOST_MOVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T)   BOOST_MOVE_HAS_NOTHROW_MOVE(T)
#else
   #define BOOST_MOVE_IS_NOTHROW_MOVE_CONSTRUCTIBLE(T)   ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_ASSIGN
   #define BOOST_MOVE_IS_NOTHROW_COPY_ASSIGNABLE(T) BOOST_MOVE_HAS_NOTHROW_ASSIGN(T)
#else
   #define BOOST_MOVE_IS_NOTHROW_COPY_ASSIGNABLE(T) ::boost::move_detail::is_pod<T>::value
#endif

#ifdef BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN
   #define BOOST_MOVE_IS_NOTHROW_MOVE_ASSIGNABLE(T) BOOST_MOVE_HAS_NOTHROW_MOVE_ASSIGN(T)
#else
   #define BOOST_MOVE_IS_NOTHROW_MOVE_ASSIGNABLE(T) ::boost::move_detail::is_pod<T>::value
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
   //In several compilers BOOST_MOVE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE return true even with
   //deleted copy constructors so make sure the type is copy constructible.
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
   //In several compilers BOOST_MOVE_IS_TRIVIALLY_COPY_CONSTRUCTIBLE return true even with
   //deleted copy constructors so make sure the type is copy constructible.
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
   : is_pod<T>
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
typedef int (alignment_dummy::*member_function_ptr)();
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
   member_function_ptr member_function_ptr_;
   alignment_struct alignment_struct_;
};

typedef union max_align max_align_t;

/////////////////////////////
//    aligned_storage
/////////////////////////////

#if !defined(BOOST_NO_ALIGNMENT)

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
   aligned_struct<Len, Align> aligner;
   unsigned char data[sizeof(aligned_struct<Len, Align>)];
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
   unsigned char data[Len];
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