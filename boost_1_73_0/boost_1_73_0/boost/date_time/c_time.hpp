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
BMuMp7huO/8KO28IpR7QidRM2+ayvRbROwMIb8tpFspgLTRcXz1qoxVRZBxTS5ZyWpYbc0rkjcUFD7MXKK2ZNPlWhleKV02pqWCywaKkEAiMrdSGVNpEJBZAxeoV6qgjBdsgYKU7Ee3p56QJZcEcbZnXIi1sFebAylF2HFkJ6rmbo0Jaad6FxcyQZqaqBUONan0/mHfRG7fGVuzc1RtTkQlmOKp+aHfxRTAbTMkTEgXdowO7bjwZTUf90SAmjzQx/DO4Hg9CK4lOb2yjfn2gRlxw3UXd4HnXDB5YVXwkVmZgJ1J486CDSodnP7uneB4xH/vYE1IcWgJiNT3B1r6+1x30/azD/696T1ETo6ER0nCvSNwD2I/KVWhX7ObSEkWlWW7nPhM/5xa84EMQDYL30SCazkmQZe5169Q/PvJPfScaqlkuJb5E0QezP/knbm+7vdAya42M2q4iuOrMf+3bKJj1bDKED8FgFpIJ0/gmomx1YTK62u6Z1ol5v3ARLUex027hbHg1HN0Mk5GV/NaItMqwFXFAurqQnTgMIRjEIzyJ30/2mnARDcLrEN9KzqHTPcEd3tmbnsVhEo7jD9tJ8i9QSwMECgAAAAgALWdKUpxv2o4yBQAAVQsAADYACQBjdXJsLW1hc3Rlci9k
*/