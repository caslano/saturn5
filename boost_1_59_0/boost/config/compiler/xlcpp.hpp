// (C) Copyright Douglas Gregor 2010
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  compiler setup for IBM XL C/C++ for Linux (Little Endian) based on clang.

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

#if defined(__int64) && !defined(__GNUC__)
#  define BOOST_HAS_MS_INT64
#endif

#define BOOST_HAS_NRVO

// Branch prediction hints
#if defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

// Clang supports "long long" in all compilation modes.
#define BOOST_HAS_LONG_LONG

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  define BOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define BOOST_SYMBOL_IMPORT
#  define BOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
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
#if defined(_MSC_VER) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#  define BOOST_NO_CXX11_CHAR16_T
#  define BOOST_NO_CXX11_CHAR32_T
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

#if !__has_feature(cxx_thread_local)
#  define BOOST_NO_CXX11_THREAD_LOCAL
#endif

#if __cplusplus < 201400
// All versions with __cplusplus above this value seem to support this:
#  define BOOST_NO_CXX14_DIGIT_SEPARATORS
#endif


// Unused attribute:
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_ATTRIBUTE_UNUSED __attribute__((unused))
#endif

// Type aliasing hint.
#if __has_attribute(__may_alias__)
#  define BOOST_MAY_ALIAS __attribute__((__may_alias__))
#endif

#ifndef BOOST_COMPILER
#  define BOOST_COMPILER "Clang version " __clang_version__
#endif

// Macro used to identify the Clang compiler.
#define BOOST_CLANG 1

#define BOOST_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

/* xlcpp.hpp
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
*/