#ifndef DATE_TIME_TIME_CLOCK_HPP___
#define DATE_TIME_TIME_CLOCK_HPP___

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file time_clock.hpp
  This file contains the interface for clock devices.
*/

#include "boost/date_time/c_time.hpp"
#include "boost/shared_ptr.hpp"

namespace boost {
namespace date_time {


  //! A clock providing time level services based on C time_t capabilities
  /*! This clock provides resolution to the 1 second level
   */
  template<class time_type>
  class second_clock
  {
  public:
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;

    static time_type local_time()
    {
      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::localtime(&t);
      curr_ptr = c_time::localtime(&t, &curr);
      return create_time(curr_ptr);
    }


    //! Get the current day in universal date as a ymd_type
    static time_type universal_time()
    {

      ::std::time_t t;
      ::std::time(&t);
      ::std::tm curr, *curr_ptr;
      //curr_ptr = ::std::gmtime(&t);
      curr_ptr = c_time::gmtime(&t, &curr);
      return create_time(curr_ptr);
    }

    template<class time_zone_type>
    static time_type local_time(boost::shared_ptr<time_zone_type> tz_ptr)
    {
      typedef typename time_type::utc_time_type utc_time_type;
      utc_time_type utc_time = second_clock<utc_time_type>::universal_time();
      return time_type(utc_time, tz_ptr);
    }


  private:
    static time_type create_time(::std::tm* current)
    {
      date_type d(static_cast<unsigned short>(current->tm_year + 1900),
                  static_cast<unsigned short>(current->tm_mon + 1),
                  static_cast<unsigned short>(current->tm_mday));
      time_duration_type td(current->tm_hour,
                            current->tm_min,
                            current->tm_sec);
      return time_type(d,td);
    }

  };


} } //namespace date_time


#endif

/* time_clock.hpp
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
*/