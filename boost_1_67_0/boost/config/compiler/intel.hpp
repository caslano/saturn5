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
#if (BOOST_INTEL_CXX_VERSION >= 1400) && (!defined(BOOST_INTEL_GCC_VERSION) || (BOOST_INTEL_GCC_VERSION >= 40700)) && (!defined(_MSC_VER) || (_MSC_VER >= 1700))
#  undef BOOST_NO_CXX11_FINAL
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