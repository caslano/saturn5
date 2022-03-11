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