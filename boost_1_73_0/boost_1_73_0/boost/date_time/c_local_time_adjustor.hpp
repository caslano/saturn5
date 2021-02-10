#ifndef DATE_TIME_C_LOCAL_TIME_ADJUSTOR_HPP__
#define DATE_TIME_C_LOCAL_TIME_ADJUSTOR_HPP__

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file c_local_time_adjustor.hpp
  Time adjustment calculations based on machine
*/

#include <stdexcept>
#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/c_time.hpp>
#include <boost/numeric/conversion/cast.hpp>

namespace boost {
namespace date_time {

  //! Adjust to / from utc using the C API
  /*! Warning!!! This class assumes that timezone settings of the
   *  machine are correct.  This can be a very dangerous assumption.
   */
  template<class time_type>
  class c_local_adjustor {
  public:
    typedef typename time_type::time_duration_type time_duration_type;
    typedef typename time_type::date_type date_type;
    typedef typename date_type::duration_type date_duration_type;
    //! Convert a utc time to local time
    static time_type utc_to_local(const time_type& t)
    {
      date_type time_t_start_day(1970,1,1);
      time_type time_t_start_time(time_t_start_day,time_duration_type(0,0,0));
      if (t < time_t_start_time) {
        boost::throw_exception(std::out_of_range("Cannot convert dates prior to Jan 1, 1970"));
        BOOST_DATE_TIME_UNREACHABLE_EXPRESSION(return time_t_start_time); // should never reach
      }
      date_duration_type dd = t.date() - time_t_start_day;
      time_duration_type td = t.time_of_day();
      uint64_t t2 = static_cast<uint64_t>(dd.days())*86400 +
                    static_cast<uint64_t>(td.hours())*3600 +
                    static_cast<uint64_t>(td.minutes())*60 +
                    td.seconds();
      // detect y2038 issue and throw instead of proceed with bad time
      std::time_t tv = boost::numeric_cast<std::time_t>(t2);
      std::tm tms, *tms_ptr;
      tms_ptr = c_time::localtime(&tv, &tms);
      date_type d(static_cast<unsigned short>(tms_ptr->tm_year + 1900),
                  static_cast<unsigned short>(tms_ptr->tm_mon + 1),
                  static_cast<unsigned short>(tms_ptr->tm_mday));
      time_duration_type td2(tms_ptr->tm_hour,
                             tms_ptr->tm_min,
                             tms_ptr->tm_sec,
                             t.time_of_day().fractional_seconds());
      
      return time_type(d,td2);
    }
  };



} } //namespace date_time



#endif

/* c_local_time_adjustor.hpp
rb+raHiO3OAYtQZ2v6yZwixq4NWy5CzbC/5d9zvxp5fQn00Go/E0uZiOk/4kDKZhch3FMZaenEeTGE6gc3wGfzTCkr0DnZIvDA/g1D859Y9wwPxLGFWbRDFtOo5fJJdC//ElDIPrkDwX5PYQ0ppRbH7FleLiDjGtFeSIAprYPsf4YB3G8+FoHEcx8UVOfuQiLZuMwVuThSNo8Y4QvVmyjOXARFPBPwRsmQ+iY9RkOBqG3lenvj6aTMLpZE4+gy0410uXMmb6htgKU4mJfIlG18zAywJrKJGyzyBhIj91lRJxcTEP3lgozsO4P4nG02g0JGOKrKFukcatY0DctgrJfptHzvQ2H1t+Y9o+RI7rK1o2dpfgqsd1G4vu8YH3n7s1L0uUBc0qt73b1lGxQdmppGYEneN5IOsNukf9wP2Zo5zY3dmp5Ip1UNC09Am5aDtcs78bpjTuFWtQMSpMNf2bc9z8VWUIYD34dmjBTHUm8+2ksSIpgnyHOrGW9ceWQy6LNlC8H+mZcox7V87OEfAciyEpFS+Q5gtNUZcpuN4aU6siFJVNH5YypTuNtT7xnwtmSjGuqFUX0iqOohUDYX5Qs9sWbVHcgVziPdugTqDoWJkoafoRRYtYIcTNY1QQNWTFBM5v4yICMdPaoLLP
*/