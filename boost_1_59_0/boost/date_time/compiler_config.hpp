#ifndef DATE_TIME_COMPILER_CONFIG_HPP___
#define DATE_TIME_COMPILER_CONFIG_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstdlib>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


// This file performs some local compiler configurations

#include <boost/date_time/locale_config.hpp> //set up locale configurations

//Set up a configuration parameter for platforms that have 
//GetTimeOfDay
#if defined(BOOST_HAS_GETTIMEOFDAY) || defined(BOOST_HAS_FTIME)
#define BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK
#endif

// To Force no default constructors for date & ptime, un-comment following
//#define DATE_TIME_NO_DEFAULT_CONSTRUCTOR

// Include extensions to date_duration - comment out to remove this feature
#define BOOST_DATE_TIME_OPTIONAL_GREGORIAN_TYPES

#if (defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) || BOOST_WORKAROUND( BOOST_BORLANDC,  BOOST_TESTED_AT(0x581) ) )
#define BOOST_DATE_TIME_NO_MEMBER_INIT
#endif

// include these types before we try to re-define them
#include <boost/cstdint.hpp>

//Define INT64_C for compilers that don't have it
#if (!defined(INT64_C))
#define INT64_C(value)  int64_t(value)
#endif


/* Workaround for Borland iterator error. Error was "Cannot convert 'istream *' to 'wistream *' in function istream_iterator<>::istream_iterator() */
#if defined(BOOST_BORLANDC) && defined(BOOST_BCB_WITH_RW_LIB)
#define BOOST_DATE_TIME_NO_WISTREAM_ITERATOR
#endif


// Borland v5.64 does not have the following in std namespace; v5.5.1 does
#if defined(BOOST_BORLANDC) && defined(BOOST_BCB_WITH_STLPORT)
#include <locale>
namespace std {
  using stlport::tolower;
  using stlport::ctype;
  using stlport::use_facet;
}
#endif

// workaround for errors associated with output for date classes 
// modifications and input streaming for time classes. 
// Compilers affected are:
// gcc295, msvc (neither with STLPort), any borland
// 
#if (((defined(__GNUC__) && (__GNUC__ < 3)) || \
      (defined(_MSC_VER) && (_MSC_VER < 1300)) ) && \
      !defined(_STLP_OWN_IOSTREAMS) ) || \
      BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0x581) )
#define BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS
#endif

// The macro marks up places where compiler complains for missing return statement or
// uninitialized variables after calling to boost::throw_exception.
// BOOST_UNREACHABLE_RETURN doesn't work since even compilers that support
// unreachable statements detection emit such warnings.
#if defined(_MSC_VER)
// Use special MSVC extension to markup unreachable code
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) __assume(false)
#elif !defined(BOOST_NO_UNREACHABLE_RETURN_DETECTION)
// Call to a non-returning function should suppress the warning
#  if defined(BOOST_NO_STDC_NAMESPACE)
namespace std {
    using ::abort;
}
#  endif // defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) std::abort()
#else
// For other poor compilers the specified expression is compiled. Usually, this would be a return statement.
#  define BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(x) x
#endif

/* The following handles the definition of the necessary macros
 * for dll building on Win32 platforms.
 * 
 * For code that will be placed in the date_time .dll, 
 * it must be properly prefixed with BOOST_DATE_TIME_DECL.
 * The corresponding .cpp file must have BOOST_DATE_TIME_SOURCE
 * defined before including its header. For examples see:
 * greg_month.hpp & greg_month.cpp
 * 
 */

// we need to import/export our code only if the user has specifically
// asked for it by defining either BOOST_ALL_DYN_LINK if they want all boost
// libraries to be dynamically linked, or BOOST_DATE_TIME_DYN_LINK
// if they want just this one to be dynamically liked:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_DATE_TIME_DYN_LINK)
    // export if this is our own source, otherwise import:
#   ifdef BOOST_DATE_TIME_SOURCE
#     define BOOST_DATE_TIME_DECL BOOST_SYMBOL_EXPORT
#   else
#     define BOOST_DATE_TIME_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_DATE_TIME_SOURCE
#endif  // DYN_LINK
//
// if BOOST_WHATEVER_DECL isn't defined yet define it now:
#ifndef BOOST_DATE_TIME_DECL
#  define BOOST_DATE_TIME_DECL
#endif


#if defined(BOOST_HAS_THREADS) 
#  if defined(_MSC_VER) || defined(__MWERKS__) || defined(__MINGW32__) ||  defined(__BORLANDC__)
     //no reentrant posix functions (eg: localtime_r)
#  elif (!defined(__hpux) || (defined(__hpux) && defined(_REENTRANT)))
#   define BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS
#  endif
#endif

#if defined(BOOST_NO_CXX11_NULLPTR)
#  define BOOST_DATE_TIME_NULLPTR 0
#else
#  define BOOST_DATE_TIME_NULLPTR nullptr
#endif

#endif

/* compiler_config.hpp
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
*/