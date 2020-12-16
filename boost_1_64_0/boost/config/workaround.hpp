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
UnVvbilbHcrswZR66dCljr7Nl6d424j9MgmjMhUwgZ+AVllfqGBxuKMpOyp7Dz/1gjx3G0F4KcLy7QwLJxexk6VVVRZC19g57KSGnJhMmLi+nOnwRJqqDl1KT+swjkweubiyYPJ8Fn01MtkI5mhh5CoOysKO9VDYDs7PWH678JbTifwi4/I6BtN4EbvJQqUoNWXP9DiiLH3pBoHfqUefyho1Ok4bsA4s8DE7cf1C5mXaqQuaBiri40i8YPnScXMvLr241aNbIlYCyy7GArfB6cgkcotEwNDYvHBFDwNL6H9zgbejrPL8ICtjYydIzVGWa3M5jZ+ruiXZZfKBBd4GssyJnTDJjQ5ox7UOfauluQGjWri6NSmor4IFXq8i1/ddLwyNnoGOC4lDD/vnRd6WiyyJotxNh2TxRBq6fN6Wdy9a74TLyPFUJFo/Uj2zH1PHAd1JWfkhF3kdzcIqjmQeoh4QRmV1V4C9BLMLvMjzowzTJPdjT5xSKsCaRd2jsNrQD81Yy+IQCj8Icy9MczFcBnBzFTrLxywpYzWQJkHGvUuLvL/wVWNLZeFzPVqYZ0gPfeIwHT4Yfy4dCekYnFDNQatglXrZpGNrn6bDE0EYhFEcupZs41C4OYMwVZ2N3wf7fI5WOnFaFDLkengybP8fx5gOR7ixX1V+VYiFHtSIxYUejnzMR1a/b827ZJUklR83Lpqn2j6BDP+sHvSt/EuSOJOhA/JYjaw+5a6mHvTZG73Y8ZwwChtJtdBr2MR+9gf6lt8bzw0yR+YgoevtFJw+gDEHO54XLdnQS9IkTisiuwxvb9SLRZRFm8ZU9mAcR3EVBUEjCQsdzR9g/9231sV+EUZp4Qn+LBJGoSUV7OzcAGLAfFNtMGHvfDS1jRQlTpxlbmOMSo/iNf8Q+krLxrjvGZllflh6tQTv8/k4TcM5UJa59KsC0kh6NAyDcqXIwv9Qdp3BVT1VPCQBAorGjoqIioo9RMBY2dt7UVCxPlIeJJryzHvB2LHr2LBjx94VZ9RxRkex9xHr+MEPzFjGDzrD2LvuuW/33HP23YfA/MM/7O93tp7du+Xs2cAL3SBBcuXRi8xUdRu87GlcV8rUy8LEreSqD2o1CCp1V991racXmGwgwsLOyiAlsmwARd3R8pcM+bjMstRIe/BZtrperzB5SxSlk1tp1C8066fcH9bfqFwm0rQsoziopMxlqYVv26yz+nU9O7Qsuy+zvnQGZo/YKLR/TK0bb/kUTplZGfRF7L/wy9M2MJ8C/eoxWV+knmNL8UCgnHpqC4dCXj8fWjf9awV+kIaxwCZhkij3W0MuiSw/yopUQFMMTiuxrLu7fI6fpCHs0YSieomMfX1w/wDfRmeysUilcJzLVrnG9ExFgm9wlTSOQhRR4qdBmZAoiBjR45Ms7VCUeWblkZsTQdUDeMq41mXykfDyoHDDAvM+dNSVece9SCOOLHKKzE8z8X+nlXUcl1gcqfBKO0ucwGM+76D9wJm4Gnk2e/zb8zcjH4GbeV7kWrW/O/3p678UvmisJXf32Low8KzEtsqkFq+XVcs4j+oZ3+ygLH0rKdlbgdj61RdbP1POvtmdHv9mB04RBaWXs3jgK4byKvdkH+scy4sv4jiMy9JOWBx8Pob5ofOgSz3eFnGUW0mc8WhIPySPca37enxjcRTC9dMoLF1nIBKcn5J46FsaG3yeX5aZ61VtAueWrEe20Q/bBt8TSLPQtRwXZdjqgOy7TG3wMcsug6TMPVs0zLjMN+fKDb6nkKdh6so4zFxK6gb63acyhQjKMvTtwBLs1l9fCmU6XCaNA8eygkJQyzst8wjdxzf4GBGVtuOGaSwaTFfJd6CN/Zs=
*/