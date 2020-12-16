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
iCiHAhyhWZIsU4RqMjgiEcjYGIXEmtY7LLc2VNMhrGiBTmuPwyhaW0ZZDUol0rTU0F8lqSaWQCzTDbEi6RVJk4wHEqELrNKu36G40Tx8apqdzx/EEQCg5Vv06a5Ks7qFGTATvUeA8qh+BJ5CEk5wjMLGYacrdLo8FzzO7dN0L9rnXXv73EqznWniaWIDdGt1YJ1pGF4nG0Toihm90phCrxTolUMGLpV2sZMJihjYN2Alh7D9x8Tf4Slvm/83KaGjcqsWOvygVJ0cT2rV0PbYnphtYsaKaLp4l6upc52iYQ6+R6+mZuqG8TwgGmZMPGS2g1uJQWEKwQeZfRbz3TGfU5kQOyG94EDUviF3eTL72lM26vE9oIxGa9GLgaocsu9ptp98xpDd7JASunXIBp8YnBJcIj8q5X24fOqGqlWxkriM6otKY068e5WYE4vRJ9RhG3TWonPQWXvwrn2pk8PmI2yvPuYPa9/bHUIjffvdvA2z7XK7habIVoZsWww70tz5TkFQJXVdGiMGIMhB268Ikj2+UpS0Te/7yCOnlWzAMfWLwUbSQz1ljY8wXlnAC6WKaekvEMrwJbIrU0t8QBRg6itaYrFGgaAlQ+ePAJ/Ofpwno/vu4tPZRRtuMM8/0iQpYXlNWHouCkTevBacuQ+MkPfhE69PevwpLWr7LAtYtEKXCsyoSuKneEHafkaCoilhPkwq5PyUS1KmI1uIuNq+oSdKxdRG7+n61A/Y1W6yiDEbwT5B9tCBYoxYvKAngDoU0Jb76Q0JCNhtMlAcjPGB7Rd0U4lbLqc/Ojx0CcL1aVGekxLOR9cIfRTmJAQAJeucVCDnpAIxJxXwoF+oB/1CQPeuo5flhBJe8uhAmrrHMP6wUbRnQM1oAWUAysJEsJfkVrs8yCLUZPz45fluwI33c1Au4ipQGTHLi/hIOZWjoaYRIDGbQVoD1H0zNu6LJ+n66J9/UFPNB03m+taypj3lk3bWtBgucdQXpNgRGbc3Zq5qz322s6va8uVJ5sNcwf+MJJq9GM3uKjD9W5rNk6cDC3UgvSIQb+rE/jauIbsiOtbuNw0fxI9o5uIxzeGsAmw0yuLyKJUqBiyYVUBM4iog/RsliK5JTefWoTyQtJF++riov5L8VH9gJyGUB6uD8ji/VhvXSPp3rry7UN57GxRT7HiSmcI0Wi1V/ZxGJn2uIBbK0S7RxxKfUPImjt2BVKGuW5eJt3TCWxrJYgrCiTsjGy4gN1MIvhziq8DBX076Cnrx5sLbSS25FBFm2HweVRx8Ppplz4W/gYizFCLOxXqmGXKnOvj8vFvnfXE3RomW3YYFWpqCVsHQRglol9mhvX6HgrbEhNa82ynA3W3ZPg+spBfBLQTqiy4GgaKKqqMWmlZ3dzUMZZFu1Ivip3DxD9yK4i+3F1+li3dQ8dFxEgEx5InM0zjzPJF5rT1zP515M21YqasdFs0lIHjDwr7+bAA5h4GMFEDW2IG8Rt7kYev7hkjjHk9pNuRpb+G9idgQnmpxDxZFrXciT8mLquCJXPBOXTDeUPAiUfD5XPDv16LgG+0FnyEL3skFb15rK/hXd5gFP7FWFdy0QxX8UhpSMg+qVqnPgnYFzJjYLj0yIeRxg4QYqwECq4V2rLbepkqopRLEggytzAWZPlGKeipPaTrKqaIOQNQyM8r0d1LUG7PfHB3uUuE5CJ8sw4cYHiGQ9kTMAIOxQMeJjtYpHGaK/jKFCymyEZIlQ4xs6+mjLpDYWm5yWp35F5MsShKBTwcpabqs8Tp5H8ctVlFyDXTH+CJ5lpBUsq2hX7EKh0XkqYDqwFdk0S12WX6UZfF/M0EntYa9Ccp/o5rgE4eJrJJNhac=
*/