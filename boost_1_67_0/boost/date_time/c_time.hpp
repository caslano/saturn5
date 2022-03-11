#ifndef DATE_TIME_C_TIME_HPP___
#define DATE_TIME_C_TIME_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


/*! @file c_time.hpp
  Provide workarounds related to the ctime header
*/

#include <ctime>
#include <string> // to be able to convert from string literals to exceptions
#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>

//Work around libraries that don't put time_t and time in namespace std
#ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::time_t; using ::time; using ::localtime;
                using ::tm;  using ::gmtime; }
#endif // BOOST_NO_STDC_NAMESPACE

//The following is used to support high precision time clocks
#ifdef BOOST_HAS_GETTIMEOFDAY
#include <sys/time.h>
#endif

#ifdef BOOST_HAS_FTIME
#include <time.h>
#endif

namespace boost {
namespace date_time {
  //! Provides a uniform interface to some 'ctime' functions
  /*! Provides a uniform interface to some ctime functions and
   * their '_r' counterparts. The '_r' functions require a pointer to a
   * user created std::tm struct whereas the regular functions use a
   * staticly created struct and return a pointer to that. These wrapper
   * functions require the user to create a std::tm struct and send in a
   * pointer to it. This struct may be used to store the resulting time.
   * The returned pointer may or may not point to this struct, however,
   * it will point to the result of the corresponding function.
   * All functions do proper checking of the C function results and throw
   * exceptions on error. Therefore the functions will never return NULL.
   */
  struct c_time {
    public:
#if defined(BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS)
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* localtime(const std::time_t* t, std::tm* result)
      {
        // localtime_r() not in namespace std???
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
        std::tm tmp;
        if(!localtime_r(t,&tmp))
            result = 0;
        else
            *result = tmp;
#else
        result = localtime_r(t, result);
#endif
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to local time"));
        return result;
      }
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* gmtime(const std::time_t* t, std::tm* result)
      {
        // gmtime_r() not in namespace std???
#if defined(__VMS) && __INITIAL_POINTER_SIZE == 64
        std::tm tmp;
        if(!gmtime_r(t,&tmp))
          result = 0;
        else
          *result = tmp;
#else
        result = gmtime_r(t, result);
#endif
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to UTC time"));
        return result;
      }
#else // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS

#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
#pragma warning(push) // preserve warning settings
#pragma warning(disable : 4996) // disable depricated localtime/gmtime warning on vc8
#endif // _MSC_VER >= 1400
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* localtime(const std::time_t* t, std::tm* result)
      {
        result = std::localtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to local time"));
        return result;
      }
      //! requires a pointer to a user created std::tm struct
      inline
      static std::tm* gmtime(const std::time_t* t, std::tm* result)
      {
        result = std::gmtime(t);
        if (!result)
          boost::throw_exception(std::runtime_error("could not convert calendar time to UTC time"));
        return result;
      }
#if (defined(_MSC_VER) && (_MSC_VER >= 1400))
#pragma warning(pop) // restore warnings to previous state
#endif // _MSC_VER >= 1400

#endif // BOOST_DATE_TIME_HAS_REENTRANT_STD_FUNCTIONS
  };
}} // namespaces

#endif // DATE_TIME_C_TIME_HPP___

/* c_time.hpp
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
*/