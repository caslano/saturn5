//
// detail/config.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_CONFIG_HPP
#define BOOST_ASIO_DETAIL_CONFIG_HPP

#if defined(BOOST_ASIO_STANDALONE)
# define BOOST_ASIO_DISABLE_BOOST_ARRAY 1
# define BOOST_ASIO_DISABLE_BOOST_ASSERT 1
# define BOOST_ASIO_DISABLE_BOOST_BIND 1
# define BOOST_ASIO_DISABLE_BOOST_CHRONO 1
# define BOOST_ASIO_DISABLE_BOOST_DATE_TIME 1
# define BOOST_ASIO_DISABLE_BOOST_LIMITS 1
# define BOOST_ASIO_DISABLE_BOOST_REGEX 1
# define BOOST_ASIO_DISABLE_BOOST_STATIC_CONSTANT 1
# define BOOST_ASIO_DISABLE_BOOST_THROW_EXCEPTION 1
# define BOOST_ASIO_DISABLE_BOOST_WORKAROUND 1
#else // defined(BOOST_ASIO_STANDALONE)
# include <boost/config.hpp>
# include <boost/version.hpp>
# define BOOST_ASIO_HAS_BOOST_CONFIG 1
#endif // defined(BOOST_ASIO_STANDALONE)

// Default to a header-only implementation. The user must specifically request
// separate compilation by defining either BOOST_ASIO_SEPARATE_COMPILATION or
// BOOST_ASIO_DYN_LINK (as a DLL/shared library implies separate compilation).
#if !defined(BOOST_ASIO_HEADER_ONLY)
# if !defined(BOOST_ASIO_SEPARATE_COMPILATION)
#  if !defined(BOOST_ASIO_DYN_LINK)
#   define BOOST_ASIO_HEADER_ONLY 1
#  endif // !defined(BOOST_ASIO_DYN_LINK)
# endif // !defined(BOOST_ASIO_SEPARATE_COMPILATION)
#endif // !defined(BOOST_ASIO_HEADER_ONLY)

#if defined(BOOST_ASIO_HEADER_ONLY)
# define BOOST_ASIO_DECL inline
#else // defined(BOOST_ASIO_HEADER_ONLY)
# if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
// We need to import/export our code only if the user has specifically asked
// for it by defining BOOST_ASIO_DYN_LINK.
#  if defined(BOOST_ASIO_DYN_LINK)
// Export if this is our own source, otherwise import.
#   if defined(BOOST_ASIO_SOURCE)
#    define BOOST_ASIO_DECL __declspec(dllexport)
#   else // defined(BOOST_ASIO_SOURCE)
#    define BOOST_ASIO_DECL __declspec(dllimport)
#   endif // defined(BOOST_ASIO_SOURCE)
#  endif // defined(BOOST_ASIO_DYN_LINK)
# endif // defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#endif // defined(BOOST_ASIO_HEADER_ONLY)

// If BOOST_ASIO_DECL isn't defined yet define it now.
#if !defined(BOOST_ASIO_DECL)
# define BOOST_ASIO_DECL
#endif // !defined(BOOST_ASIO_DECL)

// Microsoft Visual C++ detection.
#if !defined(BOOST_ASIO_MSVC)
# if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_MSVC)
#  define BOOST_ASIO_MSVC BOOST_MSVC
# elif defined(_MSC_VER) && (defined(__INTELLISENSE__) \
      || (!defined(__MWERKS__) && !defined(__EDG_VERSION__)))
#  define BOOST_ASIO_MSVC _MSC_VER
# endif // defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_MSVC)
#endif // !defined(BOOST_ASIO_MSVC)

// Clang / libc++ detection.
#if defined(__clang__)
# if (__cplusplus >= 201103)
#  if __has_include(<__config>)
#   include <__config>
#   if defined(_LIBCPP_VERSION)
#    define BOOST_ASIO_HAS_CLANG_LIBCXX 1
#   endif // defined(_LIBCPP_VERSION)
#  endif // __has_include(<__config>)
# endif // (__cplusplus >= 201103)
#endif // defined(__clang__)

// Android platform detection.
#if defined(__ANDROID__)
# include <android/api-level.h>
#endif // defined(__ANDROID__)

// Support move construction and assignment on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_MOVE)
# if !defined(BOOST_ASIO_DISABLE_MOVE)
#  if defined(__clang__)
#   if __has_feature(__cxx_rvalue_references__)
#    define BOOST_ASIO_HAS_MOVE 1
#   endif // __has_feature(__cxx_rvalue_references__)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_MOVE 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_MOVE 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
#  if defined(__INTEL_CXX11_MODE__)
#    if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500)
#      define BOOST_ASIO_HAS_MOVE 1
#    endif // defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500)
#    if defined(__ICL) && (__ICL >= 1500)
#      define BOOST_ASIO_HAS_MOVE 1
#    endif // defined(__ICL) && (__ICL >= 1500)
#  endif // defined(__INTEL_CXX11_MODE__)
# endif // !defined(BOOST_ASIO_DISABLE_MOVE)
#endif // !defined(BOOST_ASIO_HAS_MOVE)

// If BOOST_ASIO_MOVE_CAST isn't defined, and move support is available, define
// * BOOST_ASIO_MOVE_ARG,
// * BOOST_ASIO_NONDEDUCED_MOVE_ARG, and
// * BOOST_ASIO_MOVE_CAST
// to take advantage of rvalue references and perfect forwarding.
#if defined(BOOST_ASIO_HAS_MOVE) && !defined(BOOST_ASIO_MOVE_CAST)
# define BOOST_ASIO_MOVE_ARG(type) type&&
# define BOOST_ASIO_MOVE_ARG2(type1, type2) type1, type2&&
# define BOOST_ASIO_NONDEDUCED_MOVE_ARG(type) type&
# define BOOST_ASIO_MOVE_CAST(type) static_cast<type&&>
# define BOOST_ASIO_MOVE_CAST2(type1, type2) static_cast<type1, type2&&>
#endif // defined(BOOST_ASIO_HAS_MOVE) && !defined(BOOST_ASIO_MOVE_CAST)

// If BOOST_ASIO_MOVE_CAST still isn't defined, default to a C++03-compatible
// implementation. Note that older g++ and MSVC versions don't like it when you
// pass a non-member function through a const reference, so for most compilers
// we'll play it safe and stick with the old approach of passing the handler by
// value.
#if !defined(BOOST_ASIO_MOVE_CAST)
# if defined(__GNUC__)
#  if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1)) || (__GNUC__ > 4)
#   define BOOST_ASIO_MOVE_ARG(type) const type&
#  else // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1)) || (__GNUC__ > 4)
#   define BOOST_ASIO_MOVE_ARG(type) type
#  endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 1)) || (__GNUC__ > 4)
# elif defined(BOOST_ASIO_MSVC)
#  if (_MSC_VER >= 1400)
#   define BOOST_ASIO_MOVE_ARG(type) const type&
#  else // (_MSC_VER >= 1400)
#   define BOOST_ASIO_MOVE_ARG(type) type
#  endif // (_MSC_VER >= 1400)
# else
#  define BOOST_ASIO_MOVE_ARG(type) type
# endif
# define BOOST_ASIO_NONDEDUCED_MOVE_ARG(type) const type&
# define BOOST_ASIO_MOVE_CAST(type) static_cast<const type&>
# define BOOST_ASIO_MOVE_CAST2(type1, type2) static_cast<const type1, type2&>
#endif // !defined(BOOST_ASIO_MOVE_CAST)

// Support variadic templates on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
# if !defined(BOOST_ASIO_DISABLE_VARIADIC_TEMPLATES)
#  if defined(__clang__)
#   if __has_feature(__cxx_variadic_templates__)
#    define BOOST_ASIO_HAS_VARIADIC_TEMPLATES 1
#   endif // __has_feature(__cxx_variadic_templates__)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_VARIADIC_TEMPLATES 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1900)
#    define BOOST_ASIO_HAS_VARIADIC_TEMPLATES 1
#   endif // (_MSC_VER >= 1900)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_VARIADIC_TEMPLATES)
#endif // !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

// Support deleted functions on compilers known to allow it.
#if !defined(BOOST_ASIO_DELETED)
# if defined(__GNUC__)
#  if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#   if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define BOOST_ASIO_DELETED = delete
#   endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#  endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
# endif // defined(__GNUC__)
# if defined(__clang__)
#  if __has_feature(__cxx_deleted_functions__)
#   define BOOST_ASIO_DELETED = delete
#  endif // __has_feature(__cxx_deleted_functions__)
# endif // defined(__clang__)
# if defined(BOOST_ASIO_MSVC)
#  if (_MSC_VER >= 1900)
#   define BOOST_ASIO_DELETED = delete
#  endif // (_MSC_VER >= 1900)
# endif // defined(BOOST_ASIO_MSVC)
# if !defined(BOOST_ASIO_DELETED)
#  define BOOST_ASIO_DELETED
# endif // !defined(BOOST_ASIO_DELETED)
#endif // !defined(BOOST_ASIO_DELETED)

// Support constexpr on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_CONSTEXPR)
# if !defined(BOOST_ASIO_DISABLE_CONSTEXPR)
#  if defined(__clang__)
#   if __has_feature(__cxx_constexpr__)
#    define BOOST_ASIO_HAS_CONSTEXPR 1
#   endif // __has_feature(__cxx_constexr__)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_CONSTEXPR 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1900)
#    define BOOST_ASIO_HAS_CONSTEXPR 1
#   endif // (_MSC_VER >= 1900)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_CONSTEXPR)
#endif // !defined(BOOST_ASIO_HAS_CONSTEXPR)
#if !defined(BOOST_ASIO_CONSTEXPR)
# if defined(BOOST_ASIO_HAS_CONSTEXPR)
#  define BOOST_ASIO_CONSTEXPR constexpr
# else // defined(BOOST_ASIO_HAS_CONSTEXPR)
#  define BOOST_ASIO_CONSTEXPR
# endif // defined(BOOST_ASIO_HAS_CONSTEXPR)
#endif // !defined(BOOST_ASIO_CONSTEXPR)

// Support noexcept on compilers known to allow it.
#if !defined(BOOST_ASIO_NOEXCEPT)
# if !defined(BOOST_ASIO_DISABLE_NOEXCEPT)
#  if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && (BOOST_VERSION >= 105300)
#   define BOOST_ASIO_NOEXCEPT BOOST_NOEXCEPT
#   define BOOST_ASIO_NOEXCEPT_OR_NOTHROW BOOST_NOEXCEPT_OR_NOTHROW
#  elif defined(__clang__)
#   if __has_feature(__cxx_noexcept__)
#    define BOOST_ASIO_NOEXCEPT noexcept(true)
#    define BOOST_ASIO_NOEXCEPT_OR_NOTHROW noexcept(true)
#   endif // __has_feature(__cxx_noexcept__)
#  elif defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#      define BOOST_ASIO_NOEXCEPT noexcept(true)
#      define BOOST_ASIO_NOEXCEPT_OR_NOTHROW noexcept(true)
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  elif defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1900)
#    define BOOST_ASIO_NOEXCEPT noexcept(true)
#    define BOOST_ASIO_NOEXCEPT_OR_NOTHROW noexcept(true)
#   endif // (_MSC_VER >= 1900)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_NOEXCEPT)
# if !defined(BOOST_ASIO_NOEXCEPT)
#  define BOOST_ASIO_NOEXCEPT
# endif // !defined(BOOST_ASIO_NOEXCEPT)
# if !defined(BOOST_ASIO_NOEXCEPT_OR_NOTHROW)
#  define BOOST_ASIO_NOEXCEPT_OR_NOTHROW throw()
# endif // !defined(BOOST_ASIO_NOEXCEPT_OR_NOTHROW)
#endif // !defined(BOOST_ASIO_NOEXCEPT)

// Support automatic type deduction on compilers known to support it.
#if !defined(BOOST_ASIO_HAS_DECLTYPE)
# if !defined(BOOST_ASIO_DISABLE_DECLTYPE)
#  if defined(__clang__)
#   if __has_feature(__cxx_decltype__)
#    define BOOST_ASIO_HAS_DECLTYPE 1
#   endif // __has_feature(__cxx_decltype__)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_DECLTYPE 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1800)
#    define BOOST_ASIO_HAS_DECLTYPE 1
#   endif // (_MSC_VER >= 1800)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_DECLTYPE)
#endif // !defined(BOOST_ASIO_HAS_DECLTYPE)

// Support alias templates on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
# if !defined(BOOST_ASIO_DISABLE_ALIAS_TEMPLATES)
#  if defined(__clang__)
#   if __has_feature(__cxx_alias_templates__)
#    define BOOST_ASIO_HAS_ALIAS_TEMPLATES 1
#   endif // __has_feature(__cxx_alias_templates__)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_ALIAS_TEMPLATES 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1900)
#    define BOOST_ASIO_HAS_ALIAS_TEMPLATES 1
#   endif // (_MSC_VER >= 1900)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_ALIAS_TEMPLATES)
#endif // !defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

// Support return type deduction on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION)
# if !defined(BOOST_ASIO_DISABLE_RETURN_TYPE_DEDUCTION)
#  if defined(__clang__)
#   if __has_feature(__cxx_return_type_deduction__)
#    define BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION 1
#   endif // __has_feature(__cxx_alias_templates__)
#  elif (__cplusplus >= 201402)
#   define BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION 1
#  elif defined(__cpp_return_type_deduction)
#   if (__cpp_return_type_deduction >= 201304)
#    define BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION 1
#   endif // (__cpp_return_type_deduction >= 201304)
#  endif // defined(__cpp_return_type_deduction)
# endif // !defined(BOOST_ASIO_DISABLE_RETURN_TYPE_DEDUCTION)
#endif // !defined(BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION)

// Support default function template arguments on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)
# if !defined(BOOST_ASIO_DISABLE_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)
#  if (__cplusplus >= 201103)
#   define BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS 1
#  endif // (__cplusplus >= 201103)
# endif // !defined(BOOST_ASIO_DISABLE_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)
#endif // !defined(BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)

// Support concepts on compilers known to allow them.
#if !defined(BOOST_ASIO_HAS_CONCEPTS)
# if !defined(BOOST_ASIO_DISABLE_CONCEPTS)
#  if defined(__cpp_concepts)
#   define BOOST_ASIO_HAS_CONCEPTS 1
#   if (__cpp_concepts >= 201707)
#    define BOOST_ASIO_CONCEPT concept
#   else // (__cpp_concepts >= 201707)
#    define BOOST_ASIO_CONCEPT concept bool
#   endif // (__cpp_concepts >= 201707)
#  endif // defined(__cpp_concepts)
# endif // !defined(BOOST_ASIO_DISABLE_CONCEPTS)
#endif // !defined(BOOST_ASIO_HAS_CONCEPTS)

// Standard library support for system errors.
# if !defined(BOOST_ASIO_DISABLE_STD_SYSTEM_ERROR)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_SYSTEM_ERROR 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<system_error>)
#     define BOOST_ASIO_HAS_STD_SYSTEM_ERROR 1
#    endif // __has_include(<system_error>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_SYSTEM_ERROR 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_SYSTEM_ERROR 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_SYSTEM_ERROR)

// Compliant C++11 compilers put noexcept specifiers on error_category members.
#if !defined(BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT)
# if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && (BOOST_VERSION >= 105300)
#  define BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT BOOST_NOEXCEPT
# elif defined(__clang__)
#  if __has_feature(__cxx_noexcept__)
#   define BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT noexcept(true)
#  endif // __has_feature(__cxx_noexcept__)
# elif defined(__GNUC__)
#  if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#   if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT noexcept(true)
#   endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#  endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
# elif defined(BOOST_ASIO_MSVC)
#  if (_MSC_VER >= 1900)
#   define BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT noexcept(true)
#  endif // (_MSC_VER >= 1900)
# endif // defined(BOOST_ASIO_MSVC)
# if !defined(BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT)
#  define BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT
# endif // !defined(BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT)
#endif // !defined(BOOST_ASIO_ERROR_CATEGORY_NOEXCEPT)

// Standard library support for arrays.
#if !defined(BOOST_ASIO_HAS_STD_ARRAY)
# if !defined(BOOST_ASIO_DISABLE_STD_ARRAY)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_ARRAY 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<array>)
#     define BOOST_ASIO_HAS_STD_ARRAY 1
#    endif // __has_include(<array>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_ARRAY 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1600)
#    define BOOST_ASIO_HAS_STD_ARRAY 1
#   endif // (_MSC_VER >= 1600)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_ARRAY)
#endif // !defined(BOOST_ASIO_HAS_STD_ARRAY)

// Standard library support for shared_ptr and weak_ptr.
#if !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)
# if !defined(BOOST_ASIO_DISABLE_STD_SHARED_PTR)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_SHARED_PTR 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_STD_SHARED_PTR 1
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_SHARED_PTR 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1600)
#    define BOOST_ASIO_HAS_STD_SHARED_PTR 1
#   endif // (_MSC_VER >= 1600)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_SHARED_PTR)
#endif // !defined(BOOST_ASIO_HAS_STD_SHARED_PTR)

// Standard library support for allocator_arg_t.
#if !defined(BOOST_ASIO_HAS_STD_ALLOCATOR_ARG)
# if !defined(BOOST_ASIO_DISABLE_STD_ALLOCATOR_ARG)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_ALLOCATOR_ARG 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_STD_ALLOCATOR_ARG 1
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_ALLOCATOR_ARG 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1600)
#    define BOOST_ASIO_HAS_STD_ALLOCATOR_ARG 1
#   endif // (_MSC_VER >= 1600)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_ALLOCATOR_ARG)
#endif // !defined(BOOST_ASIO_HAS_STD_ALLOCATOR_ARG)

// Standard library support for atomic operations.
#if !defined(BOOST_ASIO_HAS_STD_ATOMIC)
# if !defined(BOOST_ASIO_DISABLE_STD_ATOMIC)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_ATOMIC 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<atomic>)
#     define BOOST_ASIO_HAS_STD_ATOMIC 1
#    endif // __has_include(<atomic>)
#   elif defined(__apple_build_version__) && defined(_LIBCPP_VERSION)
#    if (__clang_major__ >= 10)
#     if __has_include(<atomic>)
#      define BOOST_ASIO_HAS_STD_ATOMIC 1
#     endif // __has_include(<atomic>)
#    endif // (__clang_major__ >= 10)
#   endif /// defined(__apple_build_version__) && defined(_LIBCPP_VERSION)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_ATOMIC 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_ATOMIC 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_ATOMIC)
#endif // !defined(BOOST_ASIO_HAS_STD_ATOMIC)

// Standard library support for chrono. Some standard libraries (such as the
// libstdc++ shipped with gcc 4.6) provide monotonic_clock as per early C++0x
// drafts, rather than the eventually standardised name of steady_clock.
#if !defined(BOOST_ASIO_HAS_STD_CHRONO)
# if !defined(BOOST_ASIO_DISABLE_STD_CHRONO)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_CHRONO 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<chrono>)
#     define BOOST_ASIO_HAS_STD_CHRONO 1
#    endif // __has_include(<chrono>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_CHRONO 1
#     if ((__GNUC__ == 4) && (__GNUC_MINOR__ == 6))
#      define BOOST_ASIO_HAS_STD_CHRONO_MONOTONIC_CLOCK 1
#     endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ == 6))
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_CHRONO 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_CHRONO)
#endif // !defined(BOOST_ASIO_HAS_STD_CHRONO)

// Boost support for chrono.
#if !defined(BOOST_ASIO_HAS_BOOST_CHRONO)
# if !defined(BOOST_ASIO_DISABLE_BOOST_CHRONO)
#  if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && (BOOST_VERSION >= 104700)
#   define BOOST_ASIO_HAS_BOOST_CHRONO 1
#  endif // defined(BOOST_ASIO_HAS_BOOST_CONFIG) && (BOOST_VERSION >= 104700)
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_CHRONO)
#endif // !defined(BOOST_ASIO_HAS_BOOST_CHRONO)

// Some form of chrono library is available.
#if !defined(BOOST_ASIO_HAS_CHRONO)
# if defined(BOOST_ASIO_HAS_STD_CHRONO) \
    || defined(BOOST_ASIO_HAS_BOOST_CHRONO)
#  define BOOST_ASIO_HAS_CHRONO 1
# endif // defined(BOOST_ASIO_HAS_STD_CHRONO)
        // || defined(BOOST_ASIO_HAS_BOOST_CHRONO)
#endif // !defined(BOOST_ASIO_HAS_CHRONO)

// Boost support for the DateTime library.
#if !defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
# if !defined(BOOST_ASIO_DISABLE_BOOST_DATE_TIME)
#  define BOOST_ASIO_HAS_BOOST_DATE_TIME 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_DATE_TIME)
#endif // !defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)

// Standard library support for addressof.
#if !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)
# if !defined(BOOST_ASIO_DISABLE_STD_ADDRESSOF)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_ADDRESSOF 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_STD_ADDRESSOF 1
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_ADDRESSOF 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_ADDRESSOF 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_ADDRESSOF)
#endif // !defined(BOOST_ASIO_HAS_STD_ADDRESSOF)

// Standard library support for the function class.
#if !defined(BOOST_ASIO_HAS_STD_FUNCTION)
# if !defined(BOOST_ASIO_DISABLE_STD_FUNCTION)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_FUNCTION 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_STD_FUNCTION 1
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_FUNCTION 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_FUNCTION 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_FUNCTION)
#endif // !defined(BOOST_ASIO_HAS_STD_FUNCTION)

// Standard library support for type traits.
#if !defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)
# if !defined(BOOST_ASIO_DISABLE_STD_TYPE_TRAITS)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_TYPE_TRAITS 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<type_traits>)
#     define BOOST_ASIO_HAS_STD_TYPE_TRAITS 1
#    endif // __has_include(<type_traits>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_TYPE_TRAITS 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_TYPE_TRAITS 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_TYPE_TRAITS)
#endif // !defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS)

// Standard library support for the nullptr_t type.
#if !defined(BOOST_ASIO_HAS_NULLPTR)
# if !defined(BOOST_ASIO_DISABLE_NULLPTR)
#  if defined(__clang__)
#   if __has_feature(__cxx_nullptr__)
#    define BOOST_ASIO_HAS_NULLPTR 1
#   endif // __has_feature(__cxx_rvalue_references__)
#  elif defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_NULLPTR 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 6)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_NULLPTR 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_NULLPTR)
#endif // !defined(BOOST_ASIO_HAS_NULLPTR)

// Standard library support for the C++11 allocator additions.
#if !defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)
# if !defined(BOOST_ASIO_DISABLE_CXX11_ALLOCATORS)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_CXX11_ALLOCATORS 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_CXX11_ALLOCATORS 1
#   endif // (__cplusplus >= 201103)
#  elif defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_CXX11_ALLOCATORS 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1800)
#    define BOOST_ASIO_HAS_CXX11_ALLOCATORS 1
#   endif // (_MSC_VER >= 1800)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_CXX11_ALLOCATORS)
#endif // !defined(BOOST_ASIO_HAS_CXX11_ALLOCATORS)

// Standard library support for the cstdint header.
#if !defined(BOOST_ASIO_HAS_CSTDINT)
# if !defined(BOOST_ASIO_DISABLE_CSTDINT)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_CSTDINT 1
#   elif (__cplusplus >= 201103)
#    define BOOST_ASIO_HAS_CSTDINT 1
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_CSTDINT 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_CSTDINT 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_CSTDINT)
#endif // !defined(BOOST_ASIO_HAS_CSTDINT)

// Standard library support for the thread class.
#if !defined(BOOST_ASIO_HAS_STD_THREAD)
# if !defined(BOOST_ASIO_DISABLE_STD_THREAD)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_THREAD 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<thread>)
#     define BOOST_ASIO_HAS_STD_THREAD 1
#    endif // __has_include(<thread>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_THREAD 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_THREAD 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_THREAD)
#endif // !defined(BOOST_ASIO_HAS_STD_THREAD)

// Standard library support for the mutex and condition variable classes.
#if !defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)
# if !defined(BOOST_ASIO_DISABLE_STD_MUTEX_AND_CONDVAR)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<mutex>)
#     define BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR 1
#    endif // __has_include(<mutex>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_MUTEX_AND_CONDVAR)
#endif // !defined(BOOST_ASIO_HAS_STD_MUTEX_AND_CONDVAR)

// Standard library support for the call_once function.
#if !defined(BOOST_ASIO_HAS_STD_CALL_ONCE)
# if !defined(BOOST_ASIO_DISABLE_STD_CALL_ONCE)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_CALL_ONCE 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<mutex>)
#     define BOOST_ASIO_HAS_STD_CALL_ONCE 1
#    endif // __has_include(<mutex>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_CALL_ONCE 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_CALL_ONCE 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_CALL_ONCE)
#endif // !defined(BOOST_ASIO_HAS_STD_CALL_ONCE)

// Standard library support for futures.
#if !defined(BOOST_ASIO_HAS_STD_FUTURE)
# if !defined(BOOST_ASIO_DISABLE_STD_FUTURE)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    define BOOST_ASIO_HAS_STD_FUTURE 1
#   elif (__cplusplus >= 201103)
#    if __has_include(<future>)
#     define BOOST_ASIO_HAS_STD_FUTURE 1
#    endif // __has_include(<mutex>)
#   endif // (__cplusplus >= 201103)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_FUTURE 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 7)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_FUTURE 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_FUTURE)
#endif // !defined(BOOST_ASIO_HAS_STD_FUTURE)

// Standard library support for std::string_view.
#if !defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
# if !defined(BOOST_ASIO_DISABLE_STD_STRING_VIEW)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201402)
#     if __has_include(<string_view>)
#      define BOOST_ASIO_HAS_STD_STRING_VIEW 1
#     endif // __has_include(<string_view>)
#    endif // (__cplusplus >= 201402)
#   else // defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201703)
#     if __has_include(<string_view>)
#      define BOOST_ASIO_HAS_STD_STRING_VIEW 1
#     endif // __has_include(<string_view>)
#    endif // (__cplusplus >= 201703)
#   endif // defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  elif defined(__GNUC__)
#   if (__GNUC__ >= 7)
#    if (__cplusplus >= 201703)
#     define BOOST_ASIO_HAS_STD_STRING_VIEW 1
#    endif // (__cplusplus >= 201703)
#   endif // (__GNUC__ >= 7)
#  elif defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1910 && _MSVC_LANG >= 201703)
#    define BOOST_ASIO_HAS_STD_STRING_VIEW 1
#   endif // (_MSC_VER >= 1910 && _MSVC_LANG >= 201703)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_STRING_VIEW)
#endif // !defined(BOOST_ASIO_HAS_STD_STRING_VIEW)

// Standard library support for std::experimental::string_view.
#if !defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# if !defined(BOOST_ASIO_DISABLE_STD_EXPERIMENTAL_STRING_VIEW)
#  if defined(__clang__)
#   if defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    if (_LIBCPP_VERSION < 7000)
#     if (__cplusplus >= 201402)
#      if __has_include(<experimental/string_view>)
#       define BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#      endif // __has_include(<experimental/string_view>)
#     endif // (__cplusplus >= 201402)
#    endif // (_LIBCPP_VERSION < 7000)
#   else // defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#    if (__cplusplus >= 201402)
#     if __has_include(<experimental/string_view>)
#      define BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#     endif // __has_include(<experimental/string_view>)
#    endif // (__cplusplus >= 201402)
#   endif // // defined(BOOST_ASIO_HAS_CLANG_LIBCXX)
#  endif // defined(__clang__)
#  if defined(__GNUC__)
#   if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)) || (__GNUC__ > 4)
#    if (__cplusplus >= 201402)
#     define BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW 1
#    endif // (__cplusplus >= 201402)
#   endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 9)) || (__GNUC__ > 4)
#  endif // defined(__GNUC__)
# endif // !defined(BOOST_ASIO_DISABLE_STD_EXPERIMENTAL_STRING_VIEW)
#endif // !defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)

// Standard library has a string_view that we can use.
#if !defined(BOOST_ASIO_HAS_STRING_VIEW)
# if !defined(BOOST_ASIO_DISABLE_STRING_VIEW)
#  if defined(BOOST_ASIO_HAS_STD_STRING_VIEW)
#   define BOOST_ASIO_HAS_STRING_VIEW 1
#  elif defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
#   define BOOST_ASIO_HAS_STRING_VIEW 1
#  endif // defined(BOOST_ASIO_HAS_STD_EXPERIMENTAL_STRING_VIEW)
# endif // !defined(BOOST_ASIO_DISABLE_STRING_VIEW)
#endif // !defined(BOOST_ASIO_HAS_STRING_VIEW)

// Standard library support for iostream move construction and assignment.
#if !defined(BOOST_ASIO_HAS_STD_IOSTREAM_MOVE)
# if !defined(BOOST_ASIO_DISABLE_STD_IOSTREAM_MOVE)
#  if defined(__GNUC__)
#   if (__GNUC__ > 4)
#    if (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#     define BOOST_ASIO_HAS_STD_IOSTREAM_MOVE 1
#    endif // (__cplusplus >= 201103) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#   endif // (__GNUC__ > 4)
#  endif // defined(__GNUC__)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1700)
#    define BOOST_ASIO_HAS_STD_IOSTREAM_MOVE 1
#   endif // (_MSC_VER >= 1700)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_IOSTREAM_MOVE)
#endif // !defined(BOOST_ASIO_HAS_STD_IOSTREAM_MOVE)

// Standard library has invoke_result (which supersedes result_of).
#if !defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)
# if !defined(BOOST_ASIO_DISABLE_STD_INVOKE_RESULT)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_VER >= 1911 && _MSVC_LANG >= 201703)
#    define BOOST_ASIO_HAS_STD_INVOKE_RESULT 1
#   endif // (_MSC_VER >= 1911 && _MSVC_LANG >= 201703)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_STD_INVOKE_RESULT)
#endif // !defined(BOOST_ASIO_HAS_STD_INVOKE_RESULT)

// Windows App target. Windows but with a limited API.
#if !defined(BOOST_ASIO_WINDOWS_APP)
# if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0603)
#  include <winapifamily.h>
#  if (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) \
       || WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_TV_TITLE)) \
   && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#   define BOOST_ASIO_WINDOWS_APP 1
#  endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
         // && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
# endif // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0603)
#endif // !defined(BOOST_ASIO_WINDOWS_APP)

// Legacy WinRT target. Windows App is preferred.
#if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
# if !defined(BOOST_ASIO_WINDOWS_APP)
#  if defined(__cplusplus_winrt)
#   include <winapifamily.h>
#   if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) \
    && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#    define BOOST_ASIO_WINDOWS_RUNTIME 1
#   endif // WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
          // && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#  endif // defined(__cplusplus_winrt)
# endif // !defined(BOOST_ASIO_WINDOWS_APP)
#endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)

// Windows target. Excludes WinRT but includes Windows App targets.
#if !defined(BOOST_ASIO_WINDOWS)
# if !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#  if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_WINDOWS)
#   define BOOST_ASIO_WINDOWS 1
#  elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#   define BOOST_ASIO_WINDOWS 1
#  elif defined(BOOST_ASIO_WINDOWS_APP)
#   define BOOST_ASIO_WINDOWS 1
#  endif // defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_WINDOWS)
# endif // !defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(BOOST_ASIO_WINDOWS)

// Windows: target OS version.
#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(_WIN32_WINNT) && !defined(_WIN32_WINDOWS)
#  if defined(_MSC_VER) || defined(__BORLANDC__)
#   pragma message( \
  "Please define _WIN32_WINNT or _WIN32_WINDOWS appropriately. For example:\n"\
  "- add -D_WIN32_WINNT=0x0601 to the compiler command line; or\n"\
  "- add _WIN32_WINNT=0x0601 to your project's Preprocessor Definitions.\n"\
  "Assuming _WIN32_WINNT=0x0601 (i.e. Windows 7 target).")
#  else // defined(_MSC_VER) || defined(__BORLANDC__)
#   warning Please define _WIN32_WINNT or _WIN32_WINDOWS appropriately.
#   warning For example, add -D_WIN32_WINNT=0x0601 to the compiler command line.
#   warning Assuming _WIN32_WINNT=0x0601 (i.e. Windows 7 target).
#  endif // defined(_MSC_VER) || defined(__BORLANDC__)
#  define _WIN32_WINNT 0x0601
# endif // !defined(_WIN32_WINNT) && !defined(_WIN32_WINDOWS)
# if defined(_MSC_VER)
#  if defined(_WIN32) && !defined(WIN32)
#   if !defined(_WINSOCK2API_)
#    define WIN32 // Needed for correct types in winsock2.h
#   else // !defined(_WINSOCK2API_)
#    error Please define the macro WIN32 in your compiler options
#   endif // !defined(_WINSOCK2API_)
#  endif // defined(_WIN32) && !defined(WIN32)
# endif // defined(_MSC_VER)
# if defined(__BORLANDC__)
#  if defined(__WIN32__) && !defined(WIN32)
#   if !defined(_WINSOCK2API_)
#    define WIN32 // Needed for correct types in winsock2.h
#   else // !defined(_WINSOCK2API_)
#    error Please define the macro WIN32 in your compiler options
#   endif // !defined(_WINSOCK2API_)
#  endif // defined(__WIN32__) && !defined(WIN32)
# endif // defined(__BORLANDC__)
# if defined(__CYGWIN__)
#  if !defined(__USE_W32_SOCKETS)
#   error You must add -D__USE_W32_SOCKETS to your compiler options.
#  endif // !defined(__USE_W32_SOCKETS)
# endif // defined(__CYGWIN__)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: minimise header inclusion.
#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN)
#  if !defined(WIN32_LEAN_AND_MEAN)
#   define WIN32_LEAN_AND_MEAN
#  endif // !defined(WIN32_LEAN_AND_MEAN)
# endif // !defined(BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: suppress definition of "min" and "max" macros.
#if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# if !defined(BOOST_ASIO_NO_NOMINMAX)
#  if !defined(NOMINMAX)
#   define NOMINMAX 1
#  endif // !defined(NOMINMAX)
# endif // !defined(BOOST_ASIO_NO_NOMINMAX)
#endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)

// Windows: IO Completion Ports.
#if !defined(BOOST_ASIO_HAS_IOCP)
# if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#  if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)
#   if !defined(UNDER_CE) && !defined(BOOST_ASIO_WINDOWS_APP)
#    if !defined(BOOST_ASIO_DISABLE_IOCP)
#     define BOOST_ASIO_HAS_IOCP 1
#    endif // !defined(BOOST_ASIO_DISABLE_IOCP)
#   endif // !defined(UNDER_CE) && !defined(BOOST_ASIO_WINDOWS_APP)
#  endif // defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0400)
# endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#endif // !defined(BOOST_ASIO_HAS_IOCP)

// On POSIX (and POSIX-like) platforms we need to include unistd.h in order to
// get access to the various platform feature macros, e.g. to be able to test
// for threads support.
#if !defined(BOOST_ASIO_HAS_UNISTD_H)
# if !defined(BOOST_ASIO_HAS_BOOST_CONFIG)
#  if defined(unix) \
   || defined(__unix) \
   || defined(_XOPEN_SOURCE) \
   || defined(_POSIX_SOURCE) \
   || (defined(__MACH__) && defined(__APPLE__)) \
   || defined(__FreeBSD__) \
   || defined(__NetBSD__) \
   || defined(__OpenBSD__) \
   || defined(__linux__) \
   || defined(__HAIKU__)
#   define BOOST_ASIO_HAS_UNISTD_H 1
#  endif
# endif // !defined(BOOST_ASIO_HAS_BOOST_CONFIG)
#endif // !defined(BOOST_ASIO_HAS_UNISTD_H)
#if defined(BOOST_ASIO_HAS_UNISTD_H)
# include <unistd.h>
#endif // defined(BOOST_ASIO_HAS_UNISTD_H)

// Linux: epoll, eventfd and timerfd.
#if defined(__linux__)
# include <linux/version.h>
# if !defined(BOOST_ASIO_HAS_EPOLL)
#  if !defined(BOOST_ASIO_DISABLE_EPOLL)
#   if LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,45)
#    define BOOST_ASIO_HAS_EPOLL 1
#   endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,5,45)
#  endif // !defined(BOOST_ASIO_DISABLE_EPOLL)
# endif // !defined(BOOST_ASIO_HAS_EPOLL)
# if !defined(BOOST_ASIO_HAS_EVENTFD)
#  if !defined(BOOST_ASIO_DISABLE_EVENTFD)
#   if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
#    define BOOST_ASIO_HAS_EVENTFD 1
#   endif // LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,22)
#  endif // !defined(BOOST_ASIO_DISABLE_EVENTFD)
# endif // !defined(BOOST_ASIO_HAS_EVENTFD)
# if !defined(BOOST_ASIO_HAS_TIMERFD)
#  if defined(BOOST_ASIO_HAS_EPOLL)
#   if (__GLIBC__ > 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 8)
#    define BOOST_ASIO_HAS_TIMERFD 1
#   endif // (__GLIBC__ > 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ >= 8)
#  endif // defined(BOOST_ASIO_HAS_EPOLL)
# endif // !defined(BOOST_ASIO_HAS_TIMERFD)
#endif // defined(__linux__)

// Mac OS X, FreeBSD, NetBSD, OpenBSD: kqueue.
#if (defined(__MACH__) && defined(__APPLE__)) \
  || defined(__FreeBSD__) \
  || defined(__NetBSD__) \
  || defined(__OpenBSD__)
# if !defined(BOOST_ASIO_HAS_KQUEUE)
#  if !defined(BOOST_ASIO_DISABLE_KQUEUE)
#   define BOOST_ASIO_HAS_KQUEUE 1
#  endif // !defined(BOOST_ASIO_DISABLE_KQUEUE)
# endif // !defined(BOOST_ASIO_HAS_KQUEUE)
#endif // (defined(__MACH__) && defined(__APPLE__))
       //   || defined(__FreeBSD__)
       //   || defined(__NetBSD__)
       //   || defined(__OpenBSD__)

// Solaris: /dev/poll.
#if defined(__sun)
# if !defined(BOOST_ASIO_HAS_DEV_POLL)
#  if !defined(BOOST_ASIO_DISABLE_DEV_POLL)
#   define BOOST_ASIO_HAS_DEV_POLL 1
#  endif // !defined(BOOST_ASIO_DISABLE_DEV_POLL)
# endif // !defined(BOOST_ASIO_HAS_DEV_POLL)
#endif // defined(__sun)

// Serial ports.
#if !defined(BOOST_ASIO_HAS_SERIAL_PORT)
# if defined(BOOST_ASIO_HAS_IOCP) \
  || !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#  if !defined(__SYMBIAN32__)
#   if !defined(BOOST_ASIO_DISABLE_SERIAL_PORT)
#    define BOOST_ASIO_HAS_SERIAL_PORT 1
#   endif // !defined(BOOST_ASIO_DISABLE_SERIAL_PORT)
#  endif // !defined(__SYMBIAN32__)
# endif // defined(BOOST_ASIO_HAS_IOCP)
        //   || !defined(BOOST_ASIO_WINDOWS)
        //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
        //   && !defined(__CYGWIN__)
#endif // !defined(BOOST_ASIO_HAS_SERIAL_PORT)

// Windows: stream handles.
#if !defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)
# if !defined(BOOST_ASIO_DISABLE_WINDOWS_STREAM_HANDLE)
#  if defined(BOOST_ASIO_HAS_IOCP)
#   define BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE 1
#  endif // defined(BOOST_ASIO_HAS_IOCP)
# endif // !defined(BOOST_ASIO_DISABLE_WINDOWS_STREAM_HANDLE)
#endif // !defined(BOOST_ASIO_HAS_WINDOWS_STREAM_HANDLE)

// Windows: random access handles.
#if !defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)
# if !defined(BOOST_ASIO_DISABLE_WINDOWS_RANDOM_ACCESS_HANDLE)
#  if defined(BOOST_ASIO_HAS_IOCP)
#   define BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE 1
#  endif // defined(BOOST_ASIO_HAS_IOCP)
# endif // !defined(BOOST_ASIO_DISABLE_WINDOWS_RANDOM_ACCESS_HANDLE)
#endif // !defined(BOOST_ASIO_HAS_WINDOWS_RANDOM_ACCESS_HANDLE)

// Windows: object handles.
#if !defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)
# if !defined(BOOST_ASIO_DISABLE_WINDOWS_OBJECT_HANDLE)
#  if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#   if !defined(UNDER_CE) && !defined(BOOST_ASIO_WINDOWS_APP)
#    define BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE 1
#   endif // !defined(UNDER_CE) && !defined(BOOST_ASIO_WINDOWS_APP)
#  endif // defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
# endif // !defined(BOOST_ASIO_DISABLE_WINDOWS_OBJECT_HANDLE)
#endif // !defined(BOOST_ASIO_HAS_WINDOWS_OBJECT_HANDLE)

// Windows: OVERLAPPED wrapper.
#if !defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR)
# if !defined(BOOST_ASIO_DISABLE_WINDOWS_OVERLAPPED_PTR)
#  if defined(BOOST_ASIO_HAS_IOCP)
#   define BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR 1
#  endif // defined(BOOST_ASIO_HAS_IOCP)
# endif // !defined(BOOST_ASIO_DISABLE_WINDOWS_OVERLAPPED_PTR)
#endif // !defined(BOOST_ASIO_HAS_WINDOWS_OVERLAPPED_PTR)

// POSIX: stream-oriented file descriptors.
#if !defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
# if !defined(BOOST_ASIO_DISABLE_POSIX_STREAM_DESCRIPTOR)
#  if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#   define BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR 1
#  endif // !defined(BOOST_ASIO_WINDOWS)
         //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
         //   && !defined(__CYGWIN__)
# endif // !defined(BOOST_ASIO_DISABLE_POSIX_STREAM_DESCRIPTOR)
#endif // !defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)

// UNIX domain sockets.
#if !defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)
# if !defined(BOOST_ASIO_DISABLE_LOCAL_SOCKETS)
#  if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#   define BOOST_ASIO_HAS_LOCAL_SOCKETS 1
#  endif // !defined(BOOST_ASIO_WINDOWS)
         //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
         //   && !defined(__CYGWIN__)
# endif // !defined(BOOST_ASIO_DISABLE_LOCAL_SOCKETS)
#endif // !defined(BOOST_ASIO_HAS_LOCAL_SOCKETS)

// Can use sigaction() instead of signal().
#if !defined(BOOST_ASIO_HAS_SIGACTION)
# if !defined(BOOST_ASIO_DISABLE_SIGACTION)
#  if !defined(BOOST_ASIO_WINDOWS) \
  && !defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  && !defined(__CYGWIN__)
#   define BOOST_ASIO_HAS_SIGACTION 1
#  endif // !defined(BOOST_ASIO_WINDOWS)
         //   && !defined(BOOST_ASIO_WINDOWS_RUNTIME)
         //   && !defined(__CYGWIN__)
# endif // !defined(BOOST_ASIO_DISABLE_SIGACTION)
#endif // !defined(BOOST_ASIO_HAS_SIGACTION)

// Can use signal().
#if !defined(BOOST_ASIO_HAS_SIGNAL)
# if !defined(BOOST_ASIO_DISABLE_SIGNAL)
#  if !defined(UNDER_CE)
#   define BOOST_ASIO_HAS_SIGNAL 1
#  endif // !defined(UNDER_CE)
# endif // !defined(BOOST_ASIO_DISABLE_SIGNAL)
#endif // !defined(BOOST_ASIO_HAS_SIGNAL)

// Can use getaddrinfo() and getnameinfo().
#if !defined(BOOST_ASIO_HAS_GETADDRINFO)
# if !defined(BOOST_ASIO_DISABLE_GETADDRINFO)
#  if defined(BOOST_ASIO_WINDOWS) || defined(__CYGWIN__)
#   if defined(_WIN32_WINNT) && (_WIN32_WINNT >= 0x0501)
#    define BOOST_ASIO_HAS_GETADDRINFO 1
#   elif defined(UNDER_CE)
#    define BOOST_ASIO_HAS_GETADDRINFO 1
#   endif // defined(UNDER_CE)
#  elif defined(__MACH__) && defined(__APPLE__)
#   if defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#    if (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1050)
#     define BOOST_ASIO_HAS_GETADDRINFO 1
#    endif // (__MAC_OS_X_VERSION_MIN_REQUIRED >= 1050)
#   else // defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#    define BOOST_ASIO_HAS_GETADDRINFO 1
#   endif // defined(__MAC_OS_X_VERSION_MIN_REQUIRED)
#  else // defined(__MACH__) && defined(__APPLE__)
#   define BOOST_ASIO_HAS_GETADDRINFO 1
#  endif // defined(__MACH__) && defined(__APPLE__)
# endif // !defined(BOOST_ASIO_DISABLE_GETADDRINFO)
#endif // !defined(BOOST_ASIO_HAS_GETADDRINFO)

// Whether standard iostreams are disabled.
#if !defined(BOOST_ASIO_NO_IOSTREAM)
# if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_NO_IOSTREAM)
#  define BOOST_ASIO_NO_IOSTREAM 1
# endif // !defined(BOOST_NO_IOSTREAM)
#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

// Whether exception handling is disabled.
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
# if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_ASIO_NO_EXCEPTIONS 1
# endif // !defined(BOOST_NO_EXCEPTIONS)
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)

// Whether the typeid operator is supported.
#if !defined(BOOST_ASIO_NO_TYPEID)
# if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_NO_TYPEID)
#  define BOOST_ASIO_NO_TYPEID 1
# endif // !defined(BOOST_NO_TYPEID)
#endif // !defined(BOOST_ASIO_NO_TYPEID)

// Threads.
#if !defined(BOOST_ASIO_HAS_THREADS)
# if !defined(BOOST_ASIO_DISABLE_THREADS)
#  if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_HAS_THREADS)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(__GNUC__) && !defined(__MINGW32__) \
     && !defined(linux) && !defined(__linux) && !defined(__linux__)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(_MT) || defined(__MT__)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(_REENTRANT)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(__APPLE__)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(__HAIKU__)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(_POSIX_THREADS) && (_POSIX_THREADS + 0 >= 0)
#   define BOOST_ASIO_HAS_THREADS 1
#  elif defined(_PTHREADS)
#   define BOOST_ASIO_HAS_THREADS 1
#  endif // defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_HAS_THREADS)
# endif // !defined(BOOST_ASIO_DISABLE_THREADS)
#endif // !defined(BOOST_ASIO_HAS_THREADS)

// POSIX threads.
#if !defined(BOOST_ASIO_HAS_PTHREADS)
# if defined(BOOST_ASIO_HAS_THREADS)
#  if defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_HAS_PTHREADS)
#   define BOOST_ASIO_HAS_PTHREADS 1
#  elif defined(_POSIX_THREADS) && (_POSIX_THREADS + 0 >= 0)
#   define BOOST_ASIO_HAS_PTHREADS 1
#  elif defined(__HAIKU__)
#   define BOOST_ASIO_HAS_PTHREADS 1
#  endif // defined(BOOST_ASIO_HAS_BOOST_CONFIG) && defined(BOOST_HAS_PTHREADS)
# endif // defined(BOOST_ASIO_HAS_THREADS)
#endif // !defined(BOOST_ASIO_HAS_PTHREADS)

// Helper to prevent macro expansion.
#define BOOST_ASIO_PREVENT_MACRO_SUBSTITUTION

// Helper to define in-class constants.
#if !defined(BOOST_ASIO_STATIC_CONSTANT)
# if !defined(BOOST_ASIO_DISABLE_BOOST_STATIC_CONSTANT)
#  define BOOST_ASIO_STATIC_CONSTANT(type, assignment) \
    BOOST_STATIC_CONSTANT(type, assignment)
# else // !defined(BOOST_ASIO_DISABLE_BOOST_STATIC_CONSTANT)
#  define BOOST_ASIO_STATIC_CONSTANT(type, assignment) \
    static const type assignment
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_STATIC_CONSTANT)
#endif // !defined(BOOST_ASIO_STATIC_CONSTANT)

// Boost array library.
#if !defined(BOOST_ASIO_HAS_BOOST_ARRAY)
# if !defined(BOOST_ASIO_DISABLE_BOOST_ARRAY)
#  define BOOST_ASIO_HAS_BOOST_ARRAY 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_ARRAY)
#endif // !defined(BOOST_ASIO_HAS_BOOST_ARRAY)

// Boost assert macro.
#if !defined(BOOST_ASIO_HAS_BOOST_ASSERT)
# if !defined(BOOST_ASIO_DISABLE_BOOST_ASSERT)
#  define BOOST_ASIO_HAS_BOOST_ASSERT 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_ASSERT)
#endif // !defined(BOOST_ASIO_HAS_BOOST_ASSERT)

// Boost limits header.
#if !defined(BOOST_ASIO_HAS_BOOST_LIMITS)
# if !defined(BOOST_ASIO_DISABLE_BOOST_LIMITS)
#  define BOOST_ASIO_HAS_BOOST_LIMITS 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_LIMITS)
#endif // !defined(BOOST_ASIO_HAS_BOOST_LIMITS)

// Boost throw_exception function.
#if !defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)
# if !defined(BOOST_ASIO_DISABLE_BOOST_THROW_EXCEPTION)
#  define BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_THROW_EXCEPTION)
#endif // !defined(BOOST_ASIO_HAS_BOOST_THROW_EXCEPTION)

// Boost regex library.
#if !defined(BOOST_ASIO_HAS_BOOST_REGEX)
# if !defined(BOOST_ASIO_DISABLE_BOOST_REGEX)
#  define BOOST_ASIO_HAS_BOOST_REGEX 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_REGEX)
#endif // !defined(BOOST_ASIO_HAS_BOOST_REGEX)

// Boost bind function.
#if !defined(BOOST_ASIO_HAS_BOOST_BIND)
# if !defined(BOOST_ASIO_DISABLE_BOOST_BIND)
#  define BOOST_ASIO_HAS_BOOST_BIND 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_BIND)
#endif // !defined(BOOST_ASIO_HAS_BOOST_BIND)

// Boost's BOOST_WORKAROUND macro.
#if !defined(BOOST_ASIO_HAS_BOOST_WORKAROUND)
# if !defined(BOOST_ASIO_DISABLE_BOOST_WORKAROUND)
#  define BOOST_ASIO_HAS_BOOST_WORKAROUND 1
# endif // !defined(BOOST_ASIO_DISABLE_BOOST_WORKAROUND)
#endif // !defined(BOOST_ASIO_HAS_BOOST_WORKAROUND)

// Microsoft Visual C++'s secure C runtime library.
#if !defined(BOOST_ASIO_HAS_SECURE_RTL)
# if !defined(BOOST_ASIO_DISABLE_SECURE_RTL)
#  if defined(BOOST_ASIO_MSVC) \
    && (BOOST_ASIO_MSVC >= 1400) \
    && !defined(UNDER_CE)
#   define BOOST_ASIO_HAS_SECURE_RTL 1
#  endif // defined(BOOST_ASIO_MSVC)
         // && (BOOST_ASIO_MSVC >= 1400)
         // && !defined(UNDER_CE)
# endif // !defined(BOOST_ASIO_DISABLE_SECURE_RTL)
#endif // !defined(BOOST_ASIO_HAS_SECURE_RTL)

// Handler hooking. Disabled for ancient Borland C++ and gcc compilers.
#if !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)
# if !defined(BOOST_ASIO_DISABLE_HANDLER_HOOKS)
#  if defined(__GNUC__)
#   if (__GNUC__ >= 3)
#    define BOOST_ASIO_HAS_HANDLER_HOOKS 1
#   endif // (__GNUC__ >= 3)
#  elif !defined(__BORLANDC__)
#   define BOOST_ASIO_HAS_HANDLER_HOOKS 1
#  endif // !defined(__BORLANDC__)
# endif // !defined(BOOST_ASIO_DISABLE_HANDLER_HOOKS)
#endif // !defined(BOOST_ASIO_HAS_HANDLER_HOOKS)

// Support for the __thread keyword extension.
#if !defined(BOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION)
# if defined(__linux__)
#  if defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#   if ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 3)
#    if !defined(__INTEL_COMPILER) && !defined(__ICL) \
       && !(defined(__clang__) && defined(__ANDROID__))
#     define BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#     define BOOST_ASIO_THREAD_KEYWORD __thread
#    elif defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
#     define BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#    endif // defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1100)
           // && !(defined(__clang__) && defined(__ANDROID__))
#   endif // ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 3)) || (__GNUC__ > 3)
#  endif // defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
# endif // defined(__linux__)
# if defined(BOOST_ASIO_MSVC) && defined(BOOST_ASIO_WINDOWS_RUNTIME)
#  if (_MSC_VER >= 1700)
#   define BOOST_ASIO_HAS_THREAD_KEYWORD_EXTENSION 1
#   define BOOST_ASIO_THREAD_KEYWORD __declspec(thread)
#  endif // (_MSC_VER >= 1700)
# endif // defined(BOOST_ASIO_MSVC) && defined(BOOST_ASIO_WINDOWS_RUNTIME)
#endif // !defined(BOOST_ASIO_DISABLE_THREAD_KEYWORD_EXTENSION)
#if !defined(BOOST_ASIO_THREAD_KEYWORD)
# define BOOST_ASIO_THREAD_KEYWORD __thread
#endif // !defined(BOOST_ASIO_THREAD_KEYWORD)

// Support for POSIX ssize_t typedef.
#if !defined(BOOST_ASIO_DISABLE_SSIZE_T)
# if defined(__linux__) \
   || (defined(__MACH__) && defined(__APPLE__))
#  define BOOST_ASIO_HAS_SSIZE_T 1
# endif // defined(__linux__)
        //   || (defined(__MACH__) && defined(__APPLE__))
#endif // !defined(BOOST_ASIO_DISABLE_SSIZE_T)

// Helper macros to manage transition away from error_code return values.
#if defined(BOOST_ASIO_NO_DEPRECATED)
# define BOOST_ASIO_SYNC_OP_VOID void
# define BOOST_ASIO_SYNC_OP_VOID_RETURN(e) return
#else // defined(BOOST_ASIO_NO_DEPRECATED)
# define BOOST_ASIO_SYNC_OP_VOID boost::system::error_code
# define BOOST_ASIO_SYNC_OP_VOID_RETURN(e) return e
#endif // defined(BOOST_ASIO_NO_DEPRECATED)

// Newer gcc, clang need special treatment to suppress unused typedef warnings.
#if defined(__clang__)
# if defined(__apple_build_version__)
#  if (__clang_major__ >= 7)
#   define BOOST_ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
#  endif // (__clang_major__ >= 7)
# elif ((__clang_major__ == 3) && (__clang_minor__ >= 6)) \
    || (__clang_major__ > 3)
#  define BOOST_ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
# endif // ((__clang_major__ == 3) && (__clang_minor__ >= 6))
        //   || (__clang_major__ > 3)
#elif defined(__GNUC__)
# if ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#  define BOOST_ASIO_UNUSED_TYPEDEF __attribute__((__unused__))
# endif // ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 8)) || (__GNUC__ > 4)
#endif // defined(__GNUC__)
#if !defined(BOOST_ASIO_UNUSED_TYPEDEF)
# define BOOST_ASIO_UNUSED_TYPEDEF
#endif // !defined(BOOST_ASIO_UNUSED_TYPEDEF)

// Some versions of gcc generate spurious warnings about unused variables.
#if defined(__GNUC__)
# if (__GNUC__ >= 4)
#  define BOOST_ASIO_UNUSED_VARIABLE __attribute__((__unused__))
# endif // (__GNUC__ >= 4)
#endif // defined(__GNUC__)
#if !defined(BOOST_ASIO_UNUSED_VARIABLE)
# define BOOST_ASIO_UNUSED_VARIABLE
#endif // !defined(BOOST_ASIO_UNUSED_VARIABLE)

// Support co_await on compilers known to allow it.
#if !defined(BOOST_ASIO_HAS_CO_AWAIT)
# if !defined(BOOST_ASIO_DISABLE_CO_AWAIT)
#  if defined(BOOST_ASIO_MSVC)
#   if (_MSC_FULL_VER >= 190023506)
#    if defined(_RESUMABLE_FUNCTIONS_SUPPORTED)
#     define BOOST_ASIO_HAS_CO_AWAIT 1
#    endif // defined(_RESUMABLE_FUNCTIONS_SUPPORTED)
#   endif // (_MSC_FULL_VER >= 190023506)
#  endif // defined(BOOST_ASIO_MSVC)
# endif // !defined(BOOST_ASIO_DISABLE_CO_AWAIT)
# if defined(__clang__)
#  if (__cplusplus >= 201703) && (__cpp_coroutines >= 201703)
#   if __has_include(<experimental/coroutine>)
#    define BOOST_ASIO_HAS_CO_AWAIT 1
#   endif // __has_include(<experimental/coroutine>)
#  endif // (__cplusplus >= 201703) && (__cpp_coroutines >= 201703)
# endif // defined(__clang__)
#endif // !defined(BOOST_ASIO_HAS_CO_AWAIT)

#endif // BOOST_ASIO_DETAIL_CONFIG_HPP

/* config.hpp
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
*/