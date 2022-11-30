#ifndef DATE_TIME_HIGHRES_TIME_CLOCK_HPP___
#define DATE_TIME_HIGHRES_TIME_CLOCK_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


/*! @file microsec_time_clock.hpp
  This file contains a high resolution time clock implementation.
*/

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/date_time/time_clock.hpp>
#if defined(BOOST_HAS_FTIME)
#include <boost/winapi/time.hpp>
#endif

#ifdef BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK

namespace boost {
namespace date_time {

  //! A clock providing microsecond level resolution
  /*! A high precision clock that measures the local time
   *  at a resolution up to microseconds and adjusts to the
   *  resolution of the time system.  For example, for the
   *  a library configuration with nano second resolution,
   *  the last 3 places of the fractional seconds will always
   *  be 000 since there are 1000 nano-seconds in a micro second.
   */
  template<class time_type>
  class microsec_clock
  {
  private:
    //! Type for the function used to convert time_t to tm
    typedef std::tm* (*time_converter)(const std::time_t*, std::tm*);

  public:
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;
    typedef typename time_duration_type::rep_type resolution_traits_type;

    //! return a local time object for the given zone, based on computer clock
    //JKG -- looks like we could rewrite this against universal_time
    template<class time_zone_type>
    static time_type local_time(shared_ptr<time_zone_type> tz_ptr)
    {
      typedef typename time_type::utc_time_type utc_time_type;
      typedef second_clock<utc_time_type> second_clock;
      // we'll need to know the utc_offset this machine has
      // in order to get a utc_time_type set to utc
      utc_time_type utc_time = second_clock::universal_time();
      time_duration_type utc_offset = second_clock::local_time() - utc_time;
      // use micro clock to get a local time with sub seconds
      // and adjust it to get a true utc time reading with sub seconds
      utc_time = microsec_clock<utc_time_type>::local_time() - utc_offset;
      return time_type(utc_time, tz_ptr);
    }

    //! Returns the local time based on computer clock settings
    static time_type local_time()
    {
      return create_time(&c_time::localtime);
    }

    //! Returns the UTC time based on computer settings
    static time_type universal_time()
    {
      return create_time(&c_time::gmtime);
    }

  private:
    static time_type create_time(time_converter converter)
    {
#ifdef BOOST_HAS_GETTIMEOFDAY
      timeval tv;
      gettimeofday(&tv, 0); //gettimeofday does not support TZ adjust on Linux.
      std::time_t t = tv.tv_sec;
      boost::uint32_t sub_sec = tv.tv_usec;
#elif defined(BOOST_HAS_FTIME)
      boost::winapi::FILETIME_ ft;
      boost::winapi::GetSystemTimeAsFileTime(&ft);
#if BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3205))
      // Some runtime library implementations expect local times as the norm for ctime functions.
      {
        boost::winapi::FILETIME_ local_ft;
        boost::winapi::FileTimeToLocalFileTime(&ft, &local_ft);
        ft = local_ft;
      }
#endif

      boost::uint64_t micros = file_time_to_microseconds(ft); // it will not wrap, since ft is the current time
                                                              // and cannot be before 1970-Jan-01
      std::time_t t = static_cast<std::time_t>(micros / 1000000UL); // seconds since epoch
      // microseconds -- static casts suppress warnings
      boost::uint32_t sub_sec = static_cast<boost::uint32_t>(micros % 1000000UL);
#else
#error Internal Boost.DateTime error: BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK is defined, however neither gettimeofday nor FILETIME support is detected.
#endif

      std::tm curr;
      std::tm* curr_ptr = converter(&t, &curr);
      date_type d(static_cast< typename date_type::year_type::value_type >(curr_ptr->tm_year + 1900),
                  static_cast< typename date_type::month_type::value_type >(curr_ptr->tm_mon + 1),
                  static_cast< typename date_type::day_type::value_type >(curr_ptr->tm_mday));

      //The following line will adjust the fractional second tick in terms
      //of the current time system.  For example, if the time system
      //doesn't support fractional seconds then res_adjust returns 0
      //and all the fractional seconds return 0.
      int adjust = static_cast< int >(resolution_traits_type::res_adjust() / 1000000);

      time_duration_type td(static_cast< typename time_duration_type::hour_type >(curr_ptr->tm_hour),
                            static_cast< typename time_duration_type::min_type >(curr_ptr->tm_min),
                            static_cast< typename time_duration_type::sec_type >(curr_ptr->tm_sec),
                            sub_sec * adjust);

      return time_type(d,td);
    }

#if defined(BOOST_HAS_FTIME)
    /*!
     * The function converts file_time into number of microseconds elapsed since 1970-Jan-01
     *
     * \note Only dates after 1970-Jan-01 are supported. Dates before will be wrapped.
     */
    static boost::uint64_t file_time_to_microseconds(boost::winapi::FILETIME_ const& ft)
    {
      // shift is difference between 1970-Jan-01 & 1601-Jan-01
      // in 100-nanosecond units
      const boost::uint64_t shift = 116444736000000000ULL; // (27111902 << 32) + 3577643008

      // 100-nanos since 1601-Jan-01
      boost::uint64_t ft_as_integer = (static_cast< boost::uint64_t >(ft.dwHighDateTime) << 32) | static_cast< boost::uint64_t >(ft.dwLowDateTime);

      ft_as_integer -= shift; // filetime is now 100-nanos since 1970-Jan-01
      return (ft_as_integer / 10U); // truncate to microseconds
    }
#endif
  };


} } //namespace date_time

#endif //BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK


#endif


/* microsec_time_clock.hpp
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
*/