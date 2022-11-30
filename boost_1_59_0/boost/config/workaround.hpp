// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONFIG_WORKAROUND_HPP
#define BOOST_CONFIG_WORKAROUND_HPP

// Compiler/library version workaround macro
//
// Usage:
//
//   #if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
//      // workaround for eVC4 and VC6
//      ... // workaround code here
//   #endif
//
// When BOOST_STRICT_CONFIG is defined, expands to 0. Otherwise, the
// first argument must be undefined or expand to a numeric
// value. The above expands to:
//
//   (BOOST_MSVC) != 0 && (BOOST_MSVC) < 1300
//
// When used for workarounds that apply to the latest known version
// and all earlier versions of a compiler, the following convention
// should be observed:
//
//   #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1301))
//
// The version number in this case corresponds to the last version in
// which the workaround was known to have been required. When
// BOOST_DETECT_OUTDATED_WORKAROUNDS is not the defined, the macro
// BOOST_TESTED_AT(x) expands to "!= 0", which effectively activates
// the workaround for any version of the compiler. When
// BOOST_DETECT_OUTDATED_WORKAROUNDS is defined, a compiler warning or
// error will be issued if the compiler version exceeds the argument
// to BOOST_TESTED_AT().  This can be used to locate workarounds which
// may be obsoleted by newer versions.

#ifndef BOOST_STRICT_CONFIG

#include <boost/config.hpp>

#ifndef __BORLANDC__
#define __BORLANDC___WORKAROUND_GUARD 1
#else
#define __BORLANDC___WORKAROUND_GUARD 0
#endif
#ifndef __CODEGEARC__
#define __CODEGEARC___WORKAROUND_GUARD 1
#else
#define __CODEGEARC___WORKAROUND_GUARD 0
#endif
#ifndef BOOST_BORLANDC
#define BOOST_BORLANDC_WORKAROUND_GUARD 1
#else
#define BOOST_BORLANDC_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_CODEGEARC
#define BOOST_CODEGEARC_WORKAROUND_GUARD 1
#else
#define BOOST_CODEGEARC_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_EMBTC
#define BOOST_EMBTC_WORKAROUND_GUARD 1
#else
#define BOOST_EMBTC_WORKAROUND_GUARD 0
#endif
#ifndef _MSC_VER
#define _MSC_VER_WORKAROUND_GUARD 1
#else
#define _MSC_VER_WORKAROUND_GUARD 0
#endif
#ifndef _MSC_FULL_VER
#define _MSC_FULL_VER_WORKAROUND_GUARD 1
#else
#define _MSC_FULL_VER_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_MSVC
#define BOOST_MSVC_WORKAROUND_GUARD 1
#else
#define BOOST_MSVC_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_MSVC_FULL_VER
#define BOOST_MSVC_FULL_VER_WORKAROUND_GUARD 1
#else
#define BOOST_MSVC_FULL_VER_WORKAROUND_GUARD 0
#endif
#ifndef __GNUC__
#define __GNUC___WORKAROUND_GUARD 1
#else
#define __GNUC___WORKAROUND_GUARD 0
#endif
#ifndef __GNUC_MINOR__
#define __GNUC_MINOR___WORKAROUND_GUARD 1
#else
#define __GNUC_MINOR___WORKAROUND_GUARD 0
#endif
#ifndef __GNUC_PATCHLEVEL__
#define __GNUC_PATCHLEVEL___WORKAROUND_GUARD 1
#else
#define __GNUC_PATCHLEVEL___WORKAROUND_GUARD 0
#endif
#ifndef BOOST_GCC
#define BOOST_GCC_WORKAROUND_GUARD 1
#define BOOST_GCC_VERSION_WORKAROUND_GUARD 1
#else
#define BOOST_GCC_WORKAROUND_GUARD 0
#define BOOST_GCC_VERSION_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_XLCPP_ZOS
#define BOOST_XLCPP_ZOS_WORKAROUND_GUARD 1
#else
#define BOOST_XLCPP_ZOS_WORKAROUND_GUARD 0
#endif
#ifndef __IBMCPP__
#define __IBMCPP___WORKAROUND_GUARD 1
#else
#define __IBMCPP___WORKAROUND_GUARD 0
#endif
#ifndef __SUNPRO_CC
#define __SUNPRO_CC_WORKAROUND_GUARD 1
#else
#define __SUNPRO_CC_WORKAROUND_GUARD 0
#endif
#ifndef __DECCXX_VER
#define __DECCXX_VER_WORKAROUND_GUARD 1
#else
#define __DECCXX_VER_WORKAROUND_GUARD 0
#endif
#ifndef __MWERKS__
#define __MWERKS___WORKAROUND_GUARD 1
#else
#define __MWERKS___WORKAROUND_GUARD 0
#endif
#ifndef __EDG__
#define __EDG___WORKAROUND_GUARD 1
#else
#define __EDG___WORKAROUND_GUARD 0
#endif
#ifndef __EDG_VERSION__
#define __EDG_VERSION___WORKAROUND_GUARD 1
#else
#define __EDG_VERSION___WORKAROUND_GUARD 0
#endif
#ifndef __HP_aCC
#define __HP_aCC_WORKAROUND_GUARD 1
#else
#define __HP_aCC_WORKAROUND_GUARD 0
#endif
#ifndef __hpxstd98
#define __hpxstd98_WORKAROUND_GUARD 1
#else
#define __hpxstd98_WORKAROUND_GUARD 0
#endif
#ifndef _CRAYC
#define _CRAYC_WORKAROUND_GUARD 1
#else
#define _CRAYC_WORKAROUND_GUARD 0
#endif
#ifndef __DMC__
#define __DMC___WORKAROUND_GUARD 1
#else
#define __DMC___WORKAROUND_GUARD 0
#endif
#ifndef MPW_CPLUS
#define MPW_CPLUS_WORKAROUND_GUARD 1
#else
#define MPW_CPLUS_WORKAROUND_GUARD 0
#endif
#ifndef __COMO__
#define __COMO___WORKAROUND_GUARD 1
#else
#define __COMO___WORKAROUND_GUARD 0
#endif
#ifndef __COMO_VERSION__
#define __COMO_VERSION___WORKAROUND_GUARD 1
#else
#define __COMO_VERSION___WORKAROUND_GUARD 0
#endif
#ifndef __INTEL_COMPILER
#define __INTEL_COMPILER_WORKAROUND_GUARD 1
#else
#define __INTEL_COMPILER_WORKAROUND_GUARD 0
#endif
#ifndef __ICL
#define __ICL_WORKAROUND_GUARD 1
#else
#define __ICL_WORKAROUND_GUARD 0
#endif
#ifndef _COMPILER_VERSION
#define _COMPILER_VERSION_WORKAROUND_GUARD 1
#else
#define _COMPILER_VERSION_WORKAROUND_GUARD 0
#endif
#ifndef __clang_major__
#define __clang_major___WORKAROUND_GUARD 1
#else
#define __clang_major___WORKAROUND_GUARD 0
#endif

#ifndef _RWSTD_VER
#define _RWSTD_VER_WORKAROUND_GUARD 1
#else
#define _RWSTD_VER_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_RWSTD_VER
#define BOOST_RWSTD_VER_WORKAROUND_GUARD 1
#else
#define BOOST_RWSTD_VER_WORKAROUND_GUARD 0
#endif
#ifndef __GLIBCPP__
#define __GLIBCPP___WORKAROUND_GUARD 1
#else
#define __GLIBCPP___WORKAROUND_GUARD 0
#endif
#ifndef _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC
#define _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC_WORKAROUND_GUARD 1
#else
#define _GLIBCXX_USE_C99_FP_MACROS_DYNAMIC_WORKAROUND_GUARD 0
#endif
#ifndef __SGI_STL_PORT
#define __SGI_STL_PORT_WORKAROUND_GUARD 1
#else
#define __SGI_STL_PORT_WORKAROUND_GUARD 0
#endif
#ifndef _STLPORT_VERSION
#define _STLPORT_VERSION_WORKAROUND_GUARD 1
#else
#define _STLPORT_VERSION_WORKAROUND_GUARD 0
#endif
#ifndef __LIBCOMO_VERSION__
#define __LIBCOMO_VERSION___WORKAROUND_GUARD 1
#else
#define __LIBCOMO_VERSION___WORKAROUND_GUARD 0
#endif
#ifndef _CPPLIB_VER
#define _CPPLIB_VER_WORKAROUND_GUARD 1
#else
#define _CPPLIB_VER_WORKAROUND_GUARD 0
#endif

#ifndef BOOST_INTEL_CXX_VERSION
#define BOOST_INTEL_CXX_VERSION_WORKAROUND_GUARD 1
#else
#define BOOST_INTEL_CXX_VERSION_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_INTEL_WIN
#define BOOST_INTEL_WIN_WORKAROUND_GUARD 1
#else
#define BOOST_INTEL_WIN_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_DINKUMWARE_STDLIB
#define BOOST_DINKUMWARE_STDLIB_WORKAROUND_GUARD 1
#else
#define BOOST_DINKUMWARE_STDLIB_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_INTEL
#define BOOST_INTEL_WORKAROUND_GUARD 1
#else
#define BOOST_INTEL_WORKAROUND_GUARD 0
#endif
#ifndef BOOST_CLANG_VERSION
#define BOOST_CLANG_VERSION_WORKAROUND_GUARD 1
#else
#define BOOST_CLANG_VERSION_WORKAROUND_GUARD 0
#endif

// Always define to zero, if it's used it'll be defined my MPL:
#define BOOST_MPL_CFG_GCC_WORKAROUND_GUARD 0

#define BOOST_WORKAROUND(symbol, test)                \
       ((symbol ## _WORKAROUND_GUARD + 0 == 0) &&     \
       (symbol != 0) && (1 % (( (symbol test) ) + 1)))
//                              ^ ^           ^ ^
// The extra level of parenthesis nesting above, along with the
// BOOST_OPEN_PAREN indirection below, is required to satisfy the
// broken preprocessor in MWCW 8.3 and earlier.
//
// The basic mechanism works as follows:
//   (symbol test) + 1        =>   if (symbol test) then 2 else 1
//   1 % ((symbol test) + 1)  =>   if (symbol test) then 1 else 0
//
// The complication with % is for cooperation with BOOST_TESTED_AT().
// When "test" is BOOST_TESTED_AT(x) and
// BOOST_DETECT_OUTDATED_WORKAROUNDS is #defined,
//
//   symbol test              =>   if (symbol <= x) then 1 else -1
//   (symbol test) + 1        =>   if (symbol <= x) then 2 else 0
//   1 % ((symbol test) + 1)  =>   if (symbol <= x) then 1 else divide-by-zero
//

#ifdef BOOST_DETECT_OUTDATED_WORKAROUNDS
#  define BOOST_OPEN_PAREN (
#  define BOOST_TESTED_AT(value)  > value) ?(-1): BOOST_OPEN_PAREN 1
#else
#  define BOOST_TESTED_AT(value) != ((value)-(value))
#endif

#else

#define BOOST_WORKAROUND(symbol, test) 0

#endif

#endif // BOOST_CONFIG_WORKAROUND_HPP

/* workaround.hpp
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
*/