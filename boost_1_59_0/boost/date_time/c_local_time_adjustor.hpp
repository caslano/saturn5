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
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
*/