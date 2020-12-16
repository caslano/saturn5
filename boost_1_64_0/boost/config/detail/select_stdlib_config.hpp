//  Boost compiler configuration selection header file

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

// locate which std lib we are using and define BOOST_STDLIB_CONFIG as needed:

// First, check if __has_include is available and <version> include can be located,
// otherwise include <cstddef> to determine if some version of STLport is in use as the std lib
// (do not rely on this header being included since users can short-circuit this header 
//  if they know whose std lib they are using.)
#if defined(__cplusplus) && defined(__has_include)
#  if __has_include(<version>)
// It should be safe to include `<version>` when it is present without checking
// the actual C++ language version as it consists solely of macro definitions.
// [version.syn] p1: The header <version> supplies implementation-dependent
// information about the C++ standard library (e.g., version number and release date).
#    include <version>
#  else
#    include <cstddef>
#  endif
#elif defined(__cplusplus)
#  include <cstddef>
#else
#  include <stddef.h>
#endif

#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
// STLPort library; this _must_ come first, otherwise since
// STLport typically sits on top of some other library, we
// can end up detecting that first rather than STLport:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/stlport.hpp"

#else

// If our std lib was not some version of STLport, and has not otherwise
// been detected, then include <utility> as it is about 
// the smallest of the std lib headers that includes real C++ stuff.
// Some std libs do not include their C++-related macros in <cstddef> 
// so this additional include makes sure we get those definitions.
// Note: do not rely on this header being included since users can short-circuit this 
// #include if they know whose std lib they are using.
#if !defined(__LIBCOMO__) && !defined(__STD_RWCOMPILER_H__) && !defined(_RWSTD_VER)\
   && !defined(_LIBCPP_VERSION) && !defined(__GLIBCPP__) && !defined(__GLIBCXX__)\
   && !defined(__STL_CONFIG_H) && !defined(__MSL_CPP__) && !defined(__IBMCPP__)\
   && !defined(MSIPL_COMPILE_H) && !defined(_YVALS) && !defined(_CPPLIB_VER)
#include <utility>
#endif

#if defined(__LIBCOMO__)
// Comeau STL:
#define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcomo.hpp"

#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
// Rogue Wave library:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/roguewave.hpp"

#elif defined(_LIBCPP_VERSION)
// libc++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libcpp.hpp"

#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
// GNU libstdc++ 3
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/libstdcpp3.hpp"

#elif defined(__STL_CONFIG_H)
// generic SGI STL
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/sgi.hpp"

#elif defined(__MSL_CPP__)
// MSL standard lib:
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/msl.hpp"

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__) && defined(__MVS__)
// IBM z/OS XL C/C++
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/xlcpp_zos.hpp"

#elif defined(__IBMCPP__)
// take the default VACPP std lib
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/vacpp.hpp"

#elif defined(MSIPL_COMPILE_H)
// Modena C++ standard library
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/modena.hpp"

#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
// Dinkumware Library (this has to appear after any possible replacement libraries):
#  define BOOST_STDLIB_CONFIG "boost/config/stdlib/dinkumware.hpp"

#elif defined (BOOST_ASSERT_CONFIG)
// this must come last - generate an error if we don't
// recognise the library:
#  error "Unknown standard library - please configure and report the results to boost.org"

#endif

#endif

#if 0
//
// This section allows dependency scanners to find all the files we *might* include:
//
#  include "boost/config/stdlib/stlport.hpp"
#  include "boost/config/stdlib/libcomo.hpp"
#  include "boost/config/stdlib/roguewave.hpp"
#  include "boost/config/stdlib/libcpp.hpp"
#  include "boost/config/stdlib/libstdcpp3.hpp"
#  include "boost/config/stdlib/sgi.hpp"
#  include "boost/config/stdlib/msl.hpp"
#  include "boost/config/stdlib/xlcpp_zos.hpp"
#  include "boost/config/stdlib/vacpp.hpp"
#  include "boost/config/stdlib/modena.hpp"
#  include "boost/config/stdlib/dinkumware.hpp"
#endif


/* select_stdlib_config.hpp
GACH/rk0vS7Ugjj57lvR5/8HzEQfZzWTDV8NUU7W0grimWAgMnjYvNxlcu7H5fPzsiUDdO/vEEIJa2WW1Ea5eJAaMt31eQvCjn141WXqRqrnYYMeGKp7f4N4CPcFzvkQqSYLMTUATg5WuUweomTB8Dcv/xE93bDeixzw5BDQQ4zG6NIxpRH2U+/8FRZAKhJERgGwcUBnqzV/P9P+sMYldmM8WLX8/F2r8/EO1y8QD2BcPuf5GC2tISZAAdh56ta5jA9nuOXD+RmizD4cNURSD44BcOjb77vEFJQRVJK+XRf5wrp3D2xvr3/a3ohHbtRDrKULATIANgf5e11inUdzMEL5cj7e973u/QkWon+7hHMtyCHShX0YBFu3FG5Tm1QVsR3X/LpO+i1/hO0oJ7XxM3IwJEIsJUkA5zxo6DZ1xkeqzwO3dtS9P8CgAowPPZCTg+L2xAKzQTC+/Y5uEUIORqm1v+lSlBN3QwmuhYU89UaSI1TXTWN06SHqYBi94WS3mICxPyr4aUSzbR/rN/0eJmUjI5wy0tCqSmIWDII5H091m/qs1yj/1Hn77tRvuQuW4W3GaHNGDig9+wbAcT5e4RbnIAej5fO8xT9/pHt3Qr9GGAPGuR7KK4n3RQngvM8bcYvrkQNVxPX8q3I/xUwxRof2cepM5ZWEIbI2grGlVLjFHcjBdWo/yHEtUn1ScoY92fjCPPl8cYRxstu8BsBpS5EXSJbgnqj8tx80WV6pe7+Ft7CmSrccTg6G0zlmDIAjzud2t7nXPda61/0NlKA/YkWQkYOKUmozikEwtqTH3OJK5EAVKP5q7qwS1BSg22GoO3JyEK8irKBiQdhz4aX0vqieaxbs7KZ7t0E/3BcHccrMtHcHMiHsfWGNW7RBHm5Q94nOuWuc7v0a1iIP3byMPFSFqU2sBsGsifVuU+9cxQHOP+C3rvott0LfIMqLnDpkVSxCrEgbBGNX/MQtxqMtQcUA9n7tWowF3QLCjxZGTg4SJaXFxOvBQGTalb5wi2XIw3h1g2bT1ra69yvw+erBnpAYRmxXkgDOHGrb3GKkV3Nws7Iqbrj0TN37JUz3oD2BU26WQ6SeChJhP23MX0BuVspzz+Ov1yOsIt4SJIDTB/mDW3hxLajYhcrRU3YnO1UW45QflnMejKisIj4bDII5G35xi80oNysHbOKP3CH6LT+HbqH0fQk/Fwe1XQraEc8EA5Hpd/rLbeztkyx7+yYoY7a3y9tesSr1IDW610Ux+6PkIpUrbLLKYn7WT1NVn5SeIBXn1o0pvgtHqR4MVMiH8z6RyyNaIxcq1qtxn4PRH/kp7DkM5Qa5Plz0XERkldmystKw+YGKjzpATk7aesSpyMmt8tmy6Jn3dO8nkKqrNYYnV0F6qOVlZfIeFFnehjpAzrhxyckZyIlaLO81v2++7v0Y1qNMsbJeOCkms0s6gerYJ0/0iO7IyW3y+fLBjbDO7UeQyuUwoF44qSbbS+oAOWOpJSdHISfTVJa1Y5ceiZZa2JeqN1UfnBDmfakD5NxPJCep+J/b1drxh3rq3g9BuFAG4ckFZA+1vDTBtKEYJGO3yPeITsiJyhs1sE0f9Hl+ADfU59qp5NpPJJDT1p/vMTmj7rByRm2AFThParNY8j1HwonqgRHapFGZGPbcKPCYnFF3Wjmj1sPirJS1k5MH0s3DIFgcdPCYnFF3WTmj3oeeQbTz8uT+1iOkTBrlQDA6Sw+PyRl1t5Uzah3U4lt3Zl0PpEmj6mCYfaGXRwxrqnmYoSokTCpvovpUof1qH/LAOhcok0ZZEHYcbcwjFuN8UEVE7p120UEYGQK1yMMY4NFVSsLyCx+kS8MJ5IybKfM=
*/