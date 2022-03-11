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