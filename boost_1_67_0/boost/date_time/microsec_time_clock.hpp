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