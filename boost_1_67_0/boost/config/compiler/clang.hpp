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


/* clang.hpp
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
*/