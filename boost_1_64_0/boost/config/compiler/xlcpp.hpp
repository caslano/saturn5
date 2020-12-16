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


/* xlcpp.hpp
z7teJ/k4ZhN9/bW0iKF7flrTBuJ5PHOkPAqlGUOkZS7SnHe+IL3b34H0U99v2cT1quPiqedbZqwGSE4nKW+d/Rc5DuV8ida6tyKtIe5dgHQ0j5t3si7BdGXopDzDnQZmZMHvrtoyWCbUqzISBzW0WjYSfao2vbXGtKc8NjV6SQM0e49q91jz1tB6rSzyDJ83D60byxtUO1jNM4lZjHv/5SmcJdD4gEf3+vllLPrLfBvST6ndlOeW8+ahdlO9nmR5zvttaE/9iD4levlbUt9L2THvhciY+1vL9ksqPVLZvRuG1TE4L2aHZ0S3Qt5fL3k4IfegkM4Tu1XfDb7KRvfeHWS/l/k+W1WRkv3eeZflrKs0BrPYXuYBzA9WiN+YRItNHk/kErvRXCoUzPMmolG0Ajli308J/X5YpmNhEYS3StVoTfb2ANNvIeY09eUzMq/6fAx9n8K3wLOAVbCvBE6WA0PbYuiOtUP4j7nQz6OGs4XwC+lqQ9x17ZDX+B3Li4V9EeFvt3Er4ipntJc2QPrQGFgQ+Aml83w8Z83ptb/hEjGOchrLfiqN3YFWwmt/YzkOiUxr/X7yfc02orPqAvVlzzSkmdo3Fn35JMtz/m8pdOI25newA3pqGrybzLsJnXX95Pu9AxFvSL77csrgAXc43BDLbCgfxreSXBjJTvMKvR5m+8p1XapCYp25jNENZUvggLXdMBgLAlsiML+JiXasFJiPhb6qiPROke5Er1fzHk3RSLd6Y+VEm25gbRrcV4KLyUNw63woj+LBn8x7YiGDZm8GNgERh7eNaFwYZfwn8SKT/HL3MD7KZSm6i+MSfNxwMgmPqIYNdSsL/DqGV3nBlYXchzhe26NOSws+EUGneuhRHTcbOEwgvCI7TDlssGJOs/zHWNteWEkX98XSRXZ5IpcE7hVcEkhnTu9kdKQ5Q3mhTtKds08xmhC4J4QyI0V4gWuHlhLYR62YU0sJ3trdDEtDnCc3n5IG+aIhLXz/upR5o7YHnnxX5eWMZ/UMI8p8PcNrnfBqFTGGt6k01so5c6nBQiYHspL4PsHa6Wcxc8Pp8XxxH94zqZTk+4tnDJp0eQjMPyM7fY8fCcxUbWeJVFtzCh6pajrShZsJK6cMT1ZTLrewNllnVC0r8DtFXhSxE64tYq+T8DcJPMyW9cgedS0r2n+sFu5lV3zGaR+L00j9KSuwVwmMtZkddWSFbJ4UmJf2KGGcKWbQwIcCnKIO83gbacHIDKtgSpP0+VeCl+oVikTU57LER6EhWXYTrvR9+g4fYGXggMd1XuL9YgNjl5X4Tagdct5vGTiMFZH0BAoDYJH3QcJ8+Ig0A+V9uwcIZ/e0iGeA1dc7kTF9YHcIefyT5fFir6/qgyL/AKPxpNHwM0ZTbVDkn3W3iVkYUPk7WX680kf5SW98DANBQqw3/sHEkE19yyHTMGwob5CacjvMaLDdXPckP9+And3vEhOk9YYXye8+1pa9yVKprPgfr6o75253c1f9tb3d5ne4n/EBJgYfj0g/ItLBQaIopR/i6ZiM9OLs9GgLjX14twuDVNB97I+zPJA6nt8DbS2JPMeUPHgfTBugs1gLNl4w+Z0Q/Iw6JOntcynPZF4vuC4UNkpByVN9Yo1baIL2hHH3Thak9fvQPeg5h7COL8EHUOhdvgN1v02ikFk9XloN0+5qsLlWV8qZLPizrs6uXb12dTflL8xk5U9KbK2QcpeeyY3Fq0cfQOJ781TrhTl5OTLf77C2xnePc870Bp1aX5VJ7cp20718xrOcz+b3potSXR1TrasRJYhqK/iePiT0vZCT9f1ekZ4DNZTSf3M3pY8XpPSfCvokMJL6wdgMU58QlfU=
*/