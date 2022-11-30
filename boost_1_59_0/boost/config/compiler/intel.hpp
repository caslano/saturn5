//  (C) Copyright John Maddock 2001-8.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright Jens Maurer 2001.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002 - 2003.
//  (C) Copyright Guillaume Melquiond 2002 - 2003.
//  (C) Copyright Beman Dawes 2003.
//  (C) Copyright Martin Wille 2003.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Intel compiler setup:

#if defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500) && (defined(_MSC_VER) || defined(__GNUC__))

#ifdef _MSC_VER

#include <boost/config/compiler/visualc.hpp>

#undef BOOST_MSVC
#undef BOOST_MSVC_FULL_VER

#if (__INTEL_COMPILER >= 1500) && (_MSC_VER >= 1900)
//
// These appear to be supported, even though VC++ may not support them:
//
#define BOOST_HAS_EXPM1
#define BOOST_HAS_LOG1P
#undef BOOST_NO_CXX14_BINARY_LITERALS
// This one may be a little risky to enable??
#undef BOOST_NO_SFINAE_EXPR

#endif

#if (__INTEL_COMPILER <= 1600) && !defined(BOOST_NO_CXX14_VARIABLE_TEMPLATES)
#  define BOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

#else // defined(_MSC_VER)

#include <boost/config/compiler/gcc.hpp>

#undef BOOST_GCC_VERSION
#undef BOOST_GCC_CXX11
#undef BOOST_GCC
#undef BOOST_FALLTHROUGH

// Broken in all versions up to 17 (newer versions not tested)
#if (__INTEL_COMPILER <= 1700) && !defined(BOOST_NO_CXX14_CONSTEXPR)
#  define BOOST_NO_CXX14_CONSTEXPR
#endif

#if (__INTEL_COMPILER >= 1800) && (__cplusplus >= 201703)
#  define BOOST_FALLTHROUGH [[fallthrough]]
#endif

#endif // defined(_MSC_VER)

#undef BOOST_COMPILER

#if defined(__INTEL_COMPILER)
#if __INTEL_COMPILER == 9999
#  define BOOST_INTEL_CXX_VERSION 1200 // Intel bug in 12.1.
#else
#  define BOOST_INTEL_CXX_VERSION __INTEL_COMPILER
#endif
#elif defined(__ICL)
#  define BOOST_INTEL_CXX_VERSION __ICL
#elif defined(__ICC)
#  define BOOST_INTEL_CXX_VERSION __ICC
#elif defined(__ECC)
#  define BOOST_INTEL_CXX_VERSION __ECC
#endif

// Flags determined by comparing output of 'icpc -dM -E' with and without '-std=c++0x'
#if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && (__STDC_HOSTED__ && (BOOST_INTEL_CXX_VERSION <= 1200))) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define BOOST_INTEL_STDCXX0X
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#  define BOOST_INTEL_STDCXX0X
#endif

#ifdef __GNUC__
#  define BOOST_INTEL_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if !defined(BOOST_COMPILER)
#  if defined(BOOST_INTEL_STDCXX0X)
#    define BOOST_COMPILER "Intel C++ C++0x mode version " BOOST_STRINGIZE(BOOST_INTEL_CXX_VERSION)
#  else
#    define BOOST_COMPILER "Intel C++ version " BOOST_STRINGIZE(BOOST_INTEL_CXX_VERSION)
#  endif
#endif

#define BOOST_INTEL BOOST_INTEL_CXX_VERSION

#if defined(_WIN32) || defined(_WIN64)
#  define BOOST_INTEL_WIN BOOST_INTEL
#else
#  define BOOST_INTEL_LINUX BOOST_INTEL
#endif

#else // defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500) && (defined(_MSC_VER) || defined(__GNUC__))

#include <boost/config/compiler/common_edg.hpp>

#if defined(__INTEL_COMPILER)
#if __INTEL_COMPILER == 9999
#  define BOOST_INTEL_CXX_VERSION 1200 // Intel bug in 12.1.
#else
#  define BOOST_INTEL_CXX_VERSION __INTEL_COMPILER
#endif
#elif defined(__ICL)
#  define BOOST_INTEL_CXX_VERSION __ICL
#elif defined(__ICC)
#  define BOOST_INTEL_CXX_VERSION __ICC
#elif defined(__ECC)
#  define BOOST_INTEL_CXX_VERSION __ECC
#endif

// Flags determined by comparing output of 'icpc -dM -E' with and without '-std=c++0x'
#if (!(defined(_WIN32) || defined(_WIN64)) && defined(__STDC_HOSTED__) && (__STDC_HOSTED__ && (BOOST_INTEL_CXX_VERSION <= 1200))) || defined(__GXX_EXPERIMENTAL_CPP0X__) || defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define BOOST_INTEL_STDCXX0X
#endif
#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#  define BOOST_INTEL_STDCXX0X
#endif

#ifdef __GNUC__
#  define BOOST_INTEL_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if !defined(BOOST_COMPILER)
#  if defined(BOOST_INTEL_STDCXX0X)
#    define BOOST_COMPILER "Intel C++ C++0x mode version " BOOST_STRINGIZE(BOOST_INTEL_CXX_VERSION)
#  else
#    define BOOST_COMPILER "Intel C++ version " BOOST_STRINGIZE(BOOST_INTEL_CXX_VERSION)
#  endif
#endif

#define BOOST_INTEL BOOST_INTEL_CXX_VERSION

#if defined(_WIN32) || defined(_WIN64)
#  define BOOST_INTEL_WIN BOOST_INTEL
#else
#  define BOOST_INTEL_LINUX BOOST_INTEL
#endif

#if (BOOST_INTEL_CXX_VERSION <= 600)

#  if defined(_MSC_VER) && (_MSC_VER <= 1300) // added check for <= VC 7 (Peter Dimov)

// Boost libraries assume strong standard conformance unless otherwise
// indicated by a config macro. As configured by Intel, the EDG front-end
// requires certain compiler options be set to achieve that strong conformance.
// Particularly /Qoption,c,--arg_dep_lookup (reported by Kirk Klobe & Thomas Witt)
// and /Zc:wchar_t,forScope. See boost-root/tools/build/intel-win32-tools.jam for
// details as they apply to particular versions of the compiler. When the
// compiler does not predefine a macro indicating if an option has been set,
// this config file simply assumes the option has been set.
// Thus BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP will not be defined, even if
// the compiler option is not enabled.

#     define BOOST_NO_SWPRINTF
#  endif

// Void returns, 64 bit integrals don't work when emulating VC 6 (Peter Dimov)

#  if defined(_MSC_VER) && (_MSC_VER <= 1200)
#     define BOOST_NO_VOID_RETURNS
#     define BOOST_NO_INTEGRAL_INT64_T
#  endif

#endif

#if (BOOST_INTEL_CXX_VERSION <= 710) && defined(_WIN32)
#  define BOOST_NO_POINTER_TO_MEMBER_TEMPLATE_PARAMETERS
#endif

// See http://aspn.activestate.com/ASPN/Mail/Message/boost/1614864
#if BOOST_INTEL_CXX_VERSION < 600
#  define BOOST_NO_INTRINSIC_WCHAR_T
#else
// We should test the macro _WCHAR_T_DEFINED to check if the compiler
// supports wchar_t natively. *BUT* there is a problem here: the standard
// headers define this macro if they typedef wchar_t. Anyway, we're lucky
// because they define it without a value, while Intel C++ defines it
// to 1. So we can check its value to see if the macro was defined natively
// or not.
// Under UNIX, the situation is exactly the same, but the macro _WCHAR_T
// is used instead.
#  if ((_WCHAR_T_DEFINED + 0) == 0) && ((_WCHAR_T + 0) == 0)
#    define BOOST_NO_INTRINSIC_WCHAR_T
#  endif
#endif

#if defined(__GNUC__) && !defined(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL)
//
// Figure out when Intel is emulating this gcc bug
// (All Intel versions prior to 9.0.26, and versions
// later than that if they are set up to emulate gcc 3.2
// or earlier):
//
#  if ((__GNUC__ == 3) && (__GNUC_MINOR__ <= 2)) || (BOOST_INTEL < 900) || (__INTEL_COMPILER_BUILD_DATE < 20050912)
#     define BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  endif
#endif
#if (defined(__GNUC__) && (__GNUC__ < 4)) || (defined(_WIN32) && (BOOST_INTEL_CXX_VERSION <= 1200)) || (BOOST_INTEL_CXX_VERSION <= 1200)
// GCC or VC emulation:
#define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif
//
// Verify that we have actually got BOOST_NO_INTRINSIC_WCHAR_T
// set correctly, if we don't do this now, we will get errors later
// in type_traits code among other things, getting this correct
// for the Intel compiler is actually remarkably fragile and tricky:
//
#ifdef __cplusplus
#if defined(BOOST_NO_INTRINSIC_WCHAR_T)
#include <cwchar>
template< typename T > struct assert_no_intrinsic_wchar_t;
template<> struct assert_no_intrinsic_wchar_t<wchar_t> { typedef void type; };
// if you see an error here then you need to unset BOOST_NO_INTRINSIC_WCHAR_T
// where it is defined above:
typedef assert_no_intrinsic_wchar_t<unsigned short>::type assert_no_intrinsic_wchar_t_;
#else
template< typename T > struct assert_intrinsic_wchar_t;
template<> struct assert_intrinsic_wchar_t<wchar_t> {};
// if you see an error here then define BOOST_NO_INTRINSIC_WCHAR_T on the command line:
template<> struct assert_intrinsic_wchar_t<unsigned short> {};
#endif
#endif

#if defined(_MSC_VER) && (_MSC_VER+0 >= 1000)
#  if _MSC_VER >= 1200
#     define BOOST_HAS_MS_INT64
#  endif
#  define BOOST_NO_SWPRINTF
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#elif defined(_WIN32)
#  define BOOST_DISABLE_WIN32
#endif

// I checked version 6.0 build 020312Z, it implements the NRVO.
// Correct this as you find out which version of the compiler
// implemented the NRVO first.  (Daniel Frey)
#if (BOOST_INTEL_CXX_VERSION >= 600)
#  define BOOST_HAS_NRVO
#endif

// Branch prediction hints
// I'm not sure 8.0 was the first version to support these builtins,
// update the condition if the version is not accurate. (Andrey Semashev)
#if defined(__GNUC__) && BOOST_INTEL_CXX_VERSION >= 800
#define BOOST_LIKELY(x) __builtin_expect(x, 1)
#define BOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif

// RTTI
// __RTTI is the EDG macro
// __INTEL_RTTI__ is the Intel macro
// __GXX_RTTI is the g++ macro
// _CPPRTTI is the MSVC++ macro
#if !defined(__RTTI) && !defined(__INTEL_RTTI__) && !defined(__GXX_RTTI) && !defined(_CPPRTTI)

#if !defined(BOOST_NO_RTTI)
# define BOOST_NO_RTTI
#endif

// in MS mode, static typeid works even when RTTI is off
#if !defined(_MSC_VER) && !defined(BOOST_NO_TYPEID)
# define BOOST_NO_TYPEID
#endif

#endif

//
// versions check:
// we don't support Intel prior to version 6.0:
#if BOOST_INTEL_CXX_VERSION < 600
#  error "Compiler not supported or configured - please reconfigure"
#endif

// Intel on MacOS requires
#if defined(__APPLE__) && defined(__INTEL_COMPILER)
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif

// Intel on Altix Itanium
#if defined(__itanium__) && defined(__INTEL_COMPILER)
#  define BOOST_NO_TWO_PHASE_NAME_LOOKUP
#endif

//
// An attempt to value-initialize a pointer-to-member may trigger an
// internal error on Intel <= 11.1 (last checked version), as was
// reported by John Maddock, Intel support issue 589832, May 2010.
// Moreover, according to test results from Huang-Vista-x86_32_intel,
// intel-vc9-win-11.1 may leave a non-POD array uninitialized, in some
// cases when it should be value-initialized.
// (Niels Dekker, LKEB, May 2010)
// Apparently Intel 12.1 (compiler version number 9999 !!) has the same issue (compiler regression).
#if defined(__INTEL_COMPILER)
#  if (__INTEL_COMPILER <= 1110) || (__INTEL_COMPILER == 9999) || (defined(_WIN32) && (__INTEL_COMPILER < 1600))
#    define BOOST_NO_COMPLETE_VALUE_INITIALIZATION
#  endif
#endif

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if defined(__GNUC__) && (__GNUC__ >= 4)
#  define BOOST_SYMBOL_EXPORT __attribute__((visibility("default")))
#  define BOOST_SYMBOL_IMPORT
#  define BOOST_SYMBOL_VISIBLE __attribute__((visibility("default")))
#endif

// Type aliasing hint
#if defined(__GNUC__) && (BOOST_INTEL_CXX_VERSION >= 1300)
#  define BOOST_MAY_ALIAS __attribute__((__may_alias__))
#endif

//
// C++0x features
// For each feature we need to check both the Intel compiler version, 
// and the version of MSVC or GCC that we are emulating.
// See http://software.intel.com/en-us/articles/c0x-features-supported-by-intel-c-compiler/
// for a list of which features were implemented in which Intel releases.
//
#if defined(BOOST_INTEL_STDCXX0X)
// BOOST_NO_CXX11_CONSTEXPR:
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40600)) && !defined(_MSC_VER)
// Available in earlier Intel versions, but fail our tests:
#  undef BOOST_NO_CXX11_CONSTEXPR
#endif
// BOOST_NO_CXX11_NULLPTR:
#if (BOOST_INTEL_CXX_VERSION >= 1210) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_NULLPTR
#endif
// BOOST_NO_CXX11_TEMPLATE_ALIASES
#if (BOOST_INTEL_CXX_VERSION >= 1210) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_TEMPLATE_ALIASES
#endif

// BOOST_NO_CXX11_DECLTYPE
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_DECLTYPE
#endif

// BOOST_NO_CXX11_DECLTYPE_N3276
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_DECLTYPE_N3276
#endif

// BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

// BOOST_NO_CXX11_RVALUE_REFERENCES
#if (BOOST_INTEL_CXX_VERSION >= 1300) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
// This is available from earlier Intel versions, but breaks Filesystem and other libraries:
#  undef BOOST_NO_CXX11_RVALUE_REFERENCES
#endif

// BOOST_NO_CXX11_STATIC_ASSERT
#if (BOOST_INTEL_CXX_VERSION >= 1110) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40300)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_STATIC_ASSERT
#endif

// BOOST_NO_CXX11_VARIADIC_TEMPLATES
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

// BOOST_NO_CXX11_VARIADIC_MACROS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40200)) && (!defined(_MSC_VER) || (_MSC_VER >= 1400))
#  undef BOOST_NO_CXX11_VARIADIC_MACROS
#endif

// BOOST_NO_CXX11_AUTO_DECLARATIONS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_AUTO_DECLARATIONS
#endif

// BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

// BOOST_NO_CXX11_CHAR16_T
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#  undef BOOST_NO_CXX11_CHAR16_T
#endif

// BOOST_NO_CXX11_CHAR32_T
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#  undef BOOST_NO_CXX11_CHAR32_T
#endif

// BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

// BOOST_NO_CXX11_DELETED_FUNCTIONS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_DELETED_FUNCTIONS
#endif

// BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#  undef BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

// BOOST_NO_CXX11_SCOPED_ENUMS
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40501)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
// This is available but broken in earlier Intel releases.
#  undef BOOST_NO_CXX11_SCOPED_ENUMS
#endif

// BOOST_NO_SFINAE_EXPR
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#  undef BOOST_NO_SFINAE_EXPR
#endif

// BOOST_NO_CXX11_SFINAE_EXPR
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40800)) && !defined(_MSC_VER)
#  undef BOOST_NO_CXX11_SFINAE_EXPR
#endif

// BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
// This is available in earlier Intel releases, but breaks Multiprecision:
#  undef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

// BOOST_NO_CXX11_LAMBDAS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 1600))
#  undef BOOST_NO_CXX11_LAMBDAS
#endif

// BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500))
#  undef BOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

// BOOST_NO_CXX11_RANGE_BASED_FOR
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#  undef BOOST_NO_CXX11_RANGE_BASED_FOR
#endif

// BOOST_NO_CXX11_RAW_LITERALS
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_RAW_LITERALS
#endif

// BOOST_NO_CXX11_UNICODE_LITERALS
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40500)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#  undef BOOST_NO_CXX11_UNICODE_LITERALS
#endif

// BOOST_NO_CXX11_NOEXCEPT
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
// Available in earlier Intel release, but generates errors when used with 
// conditional exception specifications, for example in multiprecision:
#  undef BOOST_NO_CXX11_NOEXCEPT
#endif

// BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40600)) && (!defined(_MSC_VER) || (_MSC_VER >= 9999))
#  undef BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

// BOOST_NO_CXX11_USER_DEFINED_LITERALS
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#  undef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif

// BOOST_NO_CXX11_ALIGNAS
#if (BOOST_INTEL_CXX_VERSION >= 1500) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#  undef BOOST_NO_CXX11_ALIGNAS
#endif

// BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#if (BOOST_INTEL_CXX_VERSION >= 1200) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 180020827))
#  undef BOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif

// BOOST_NO_CXX11_INLINE_NAMESPACES
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40400)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#  undef BOOST_NO_CXX11_INLINE_NAMESPACES
#endif

// BOOST_NO_CXX11_REF_QUALIFIERS
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40800)) && (!defined(_MSC_VER) || (_MSC_FULL_VER >= 190021730))
#  undef BOOST_NO_CXX11_REF_QUALIFIERS
#endif

// BOOST_NO_CXX11_FINAL
// BOOST_NO_CXX11_OVERRIDE
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#  undef BOOST_NO_CXX11_FINAL
#  undef BOOST_NO_CXX11_OVERRIDE
#endif

// BOOST_NO_CXX11_UNRESTRICTED_UNION
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 50100)) && (!defined(_MSC_VER))
#  undef BOOST_NO_CXX11_UNRESTRICTED_UNION
#endif

#endif // defined(BOOST_INTEL_STDCXX0X)

//
// Broken in all versions up to 15:
#define BOOST_NO_CXX11_FIXED_LENGTH_VARIADIC_TEMPLATE_EXPANSION_PACKS

#if defined(BOOST_INTEL_STDCXX0X) && (BOOST_INTEL_CXX_VERSION <= 1310)
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

#if defined(BOOST_INTEL_STDCXX0X) && (BOOST_INTEL_CXX_VERSION == 1400)
// A regression in Intel's compiler means that <tuple> seems to be broken in this release as well as <future> :
#  define BOOST_NO_CXX11_HDR_FUTURE
#  define BOOST_NO_CXX11_HDR_TUPLE
#endif

#if (BOOST_INTEL_CXX_VERSION < 1200)
//
// fenv.h appears not to work with Intel prior to 12.0:
//
#  define BOOST_NO_FENV_H
#endif

// Intel 13.10 fails to access defaulted functions of a base class declared in private or protected sections,
// producing the following errors:
// error #453: protected function "..." (declared at ...") is not accessible through a "..." pointer or object
#if (BOOST_INTEL_CXX_VERSION <= 1310)
#  define BOOST_NO_CXX11_NON_PUBLIC_DEFAULTED_FUNCTIONS
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
#  define BOOST_HAS_STDINT_H
#endif

#if defined(__CUDACC__)
#  if defined(BOOST_GCC_CXX11)
#    define BOOST_NVCC_CXX11
#  else
#    define BOOST_NVCC_CXX03
#  endif
#endif

#if defined(__LP64__) && defined(__GNUC__) && (BOOST_INTEL_CXX_VERSION >= 1310) && !defined(BOOST_NVCC_CXX03)
#  define BOOST_HAS_INT128
#endif

#endif // defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 1500) && (defined(_MSC_VER) || defined(__GNUC__))
//
// last known and checked version:
#if (BOOST_INTEL_CXX_VERSION > 1700)
#  if defined(BOOST_ASSERT_CONFIG)
#     error "Boost.Config is older than your compiler - please check for an updated Boost release."
#  elif defined(_MSC_VER)
//
//      We don't emit this warning any more, since we have so few
//      defect macros set anyway (just the one).
//
//#     pragma message("boost: Unknown compiler version - please run the configure tests and report the results")
#  endif
#endif


/* intel.hpp
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
*/