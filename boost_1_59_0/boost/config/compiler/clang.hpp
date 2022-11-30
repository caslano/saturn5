// (C) Copyright Douglas Gregor 2010
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// Clang compiler setup.

#define BOOST_HAS_PRAGMA_ONCE

// Detecting `-fms-extension` compiler flag assuming that _MSC_VER defined when that flag is used.
#if defined (_MSC_VER) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))
#   define BOOST_HAS_PRAGMA_DETECT_MISMATCH
#endif

// When compiling with clang before __has_extension was defined,
// even if one writes 'defined(__has_extension) && __has_extension(xxx)',
// clang reports a compiler error. So the only workaround found is:

#ifndef __has_extension
#define __has_extension __has_feature
#endif

#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#ifndef __has_cpp_attribute
#define __has_cpp_attribute(x) 0
#endif

#if !__has_feature(cxx_exceptions) && !defined(BOOST_NO_EXCEPTIONS)
#  define BOOST_NO_EXCEPTIONS
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_RTTI)
#  define BOOST_NO_RTTI
#endif

#if !__has_feature(cxx_rtti) && !defined(BOOST_NO_TYPEID)
#  define BOOST_NO_TYPEID
#endif

#if !__has_feature(cxx_thread_local)
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#ifdef __is_identifier
#if !__is_identifier(__int64) && !defined(__GNUC__)
#  define BOOST_HAS_MS_INT64
#endif
#endif

#if __has_include(<stdint.h>)
#  define BOOST_HAS_STDINT_H
#endif

#if (defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)) && !defined(_CRAYC)
#if (__clang_major__ >= 4) && defined(__has_include)
#if __has_include(<quadmath.h>)
#  define BOOST_HAS_FLOAT128
#endif
#endif
#endif


#define BOOST_HAS_NRVO

// Branch prediction hints
#if !defined (__c2__) && defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

// Clang supports "long long" in all compilation modes.
#define BOOST_HAS_LONG_LONG

//
// We disable this if the compiler is really nvcc with C++03 as it
// doesn't actually support __int128 as of CUDA_VERSION=7500
// even though it defines __SIZEOF_INT128__.
// See https://svn.boost.org/trac/boost/ticket/10418
//     https://svn.boost.org/trac/boost/ticket/11852
// Only re-enable this for nvcc if you're absolutely sure
// of the circumstances under which it's supported.
// Similarly __SIZEOF_INT128__ is defined when targetting msvc
// compatibility even though the required support functions are absent.
//
#if defined(__CUDACC__)
#  if defined(BOOST_GCC_CXX11)
#    define BOOST_NVCC_CXX11
#  else
#    define BOOST_NVCC_CXX03
#  endif
#endif

#if defined(__SIZEOF_INT128__) && !defined(BOOST_NVCC_CXX03) && !defined(_MSC_VER)
#  define BOOST_HAS_INT128
#endif


//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__)
#  define BOOST_HAS_DECLSPEC
#  define BOOST_SYMBOL_EXPORT __attribute__((__dllexport__))
#  define BOOST_SYMBOL_IMPORT __attribute__((__dllimport__))
#else
#  define BOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#  define BOOST_SYMBOL_IMPORT
#endif

//
// The BOOST_FALLTHROUGH macro can be used to annotate implicit fall-through
// between switch labels.
//
#if __cplusplus >= 201103L && defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define BOOST_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif

#if !__has_feature(cxx_auto_type)
#  define BOOST_NO_CXX11_AUTO_DECLARATIONS
#  define BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

//
// Currently clang on Windows using VC++ RTL does not support C++11's char16_t or char32_t
//
#if (defined(_MSC_VER) && (_MSC_VER < 1900)) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1800) && !defined(__GNUC__)
#define BOOST_HAS_EXPM1
#define BOOST_HAS_LOG1P
#endif

#if !__has_feature(cxx_constexpr)
#  define BOOST_NO_CXX11_CONSTEXPR
#endif

#if !__has_feature(cxx_decltype)
#  define BOOST_NO_CXX11_DECLTYPE
#endif

#if !__has_feature(cxx_decltype_incomplete_return_types)
#  define BOOST_NO_CXX11_DECLTYPE_N3276
#endif

#if !__has_feature(cxx_defaulted_functions)
#  define BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
#  define BOOST_NO_CXX11_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_explicit_conversions)
#  define BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if !__has_feature(cxx_default_function_template_args)
#  define BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

#if !__has_feature(cxx_lambdas)
#  define BOOST_NO_CXX11_LAMBDAS
#endif

#if !__has_feature(cxx_local_type_template_args)
#  define BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if !__has_feature(cxx_noexcept)
#  define BOOST_NO_CXX11_NOEXCEPT
#endif

#if !__has_feature(cxx_nullptr)
#  define BOOST_NO_CXX11_NULLPTR
#endif

#if !__has_feature(cxx_range_for)
#  define BOOST_NO_CXX11_RANGE_BASED_FOR
#endif

#if !__has_feature(cxx_raw_string_literals)
#  define BOOST_NO_CXX11_RAW_LITERALS
#endif

#if !__has_feature(cxx_reference_qualified_functions)
#  define BOOST_NO_CXX11_REF_QUALIFIERS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

#if !__has_feature(cxx_rvalue_references)
#  define BOOST_NO_CXX11_RVALUE_REFERENCES
#endif

#if !__has_feature(cxx_strong_enums)
#  define BOOST_NO_CXX11_SCOPED_ENUMS
#endif

#if !__has_feature(cxx_static_assert)
#  define BOOST_NO_CXX11_STATIC_ASSERT
#endif

#if !__has_feature(cxx_alias_templates)
#  define BOOST_NO_CXX11_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_unicode_literals)
#  define BOOST_NO_CXX11_UNICODE_LITERALS
#endif

#if !__has_feature(cxx_variadic_templates)
#  define BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if !__has_feature(cxx_user_literals)
#  define BOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif

#if !__has_feature(cxx_alignas)
#  define BOOST_NO_CXX11_ALIGNAS
#endif

#if !__has_feature(cxx_trailing_return)
#  define BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif

#if !__has_feature(cxx_inline_namespaces)
#  define BOOST_NO_CXX11_INLINE_NAMESPACES
#endif

#if !__has_feature(cxx_override_control)
#  define BOOST_NO_CXX11_FINAL
#  define BOOST_NO_CXX11_OVERRIDE
#endif

#if !__has_feature(cxx_unrestricted_unions)
#  define BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif

#if !(__has_feature(__cxx_binary_literals__) || __has_extension(__cxx_binary_literals__))
#  define BOOST_NO_CXX14_BINARY_LITERALS
#endif

#if !__has_feature(__cxx_decltype_auto__)
#  define BOOST_NO_CXX14_DECLTYPE_AUTO
#endif

#if !__has_feature(__cxx_aggregate_nsdmi__)
#  define BOOST_NO_CXX14_AGGREGATE_NSDMI
#endif

#if !__has_feature(__cxx_init_captures__)
#  define BOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif

#if !__has_feature(__cxx_generic_lambdas__)
#  define BOOST_NO_CXX14_GENERIC_LAMBDAS
#endif

// clang < 3.5 has a defect with dependent type, like following.
//
//  template <class T>
//  constexpr typename enable_if<pred<T> >::type foo(T &)
//  { } // error: no return statement in constexpr function
//
// This issue also affects C++11 mode, but C++11 constexpr requires return stmt.
// Therefore we don't care such case.
//
// Note that we can't check Clang version directly as the numbering system changes depending who's
// creating the Clang release (see https://github.com/boostorg/config/pull/39#issuecomment-59927873)
// so instead verify that we have a feature that was introduced at the same time as working C++14
// constexpr (generic lambda's in this case):
//
#if !__has_feature(__cxx_generic_lambdas__) || !__has_feature(__cxx_relaxed_constexpr__)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif

#if !__has_feature(__cxx_return_type_deduction__)
#  define BOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif

#if !__has_feature(__cxx_variable_templates__)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

#if !defined(__cpp_structured_bindings) || (__cpp_structured_bindings < 201606)
#  define BOOST_NO_CXX17_STRUCTURED_BINDINGS
#endif

#if !defined(__cpp_if_constexpr) || (__cpp_if_constexpr < 201606)
#  define BOOST_NO_CXX17_IF_CONSTEXPR
#endif

// Clang 3.9+ in c++1z
#if !__has_cpp_attribute(fallthrough) || __cplusplus < 201406L
#  define BOOST_NO_CXX17_INLINE_VARIABLES
#  define BOOST_NO_CXX17_FOLD_EXPRESSIONS
#endif

#if __cplusplus < 201103L
#define BOOST_NO_CXX11_SFINAE_EXPR
#endif

#if __cplusplus < 201400
// All versions with __cplusplus above this value seem to support this:
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif
//
// __builtin_unreachable:
#if defined(__has_builtin) && __has_builtin(__builtin_unreachable)
#define BOOST_UNREACHABLE_RETURN(x) __builtin_unreachable();
#endif

#if (__clang_major__ == 3) && (__clang_minor__ == 0)
// Apparently a clang bug:
#  define BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS
#endif

// Clang has supported the 'unused' attribute since the first release.
#define BOOST_ATTRIBUTE_UNUSED __attribute__((__unused__))

// Type aliasing hint.
#if __has_attribute(__may_alias__)
#  define BOOST_MAY_ALIAS __attribute__((__may_alias__))
#endif

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "Clang version " __clang_version__
#endif

// Macro used to identify the Clang compiler.
#define BOOST_CLANG 1

// BOOST_CLANG_VERSION
#include <boost/config/compiler/clang_version.hpp>

/* clang.hpp
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
*/