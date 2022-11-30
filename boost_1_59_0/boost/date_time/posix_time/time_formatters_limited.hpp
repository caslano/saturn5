#ifndef POSIXTIME_FORMATTERS_LIMITED_HPP___
#define POSIXTIME_FORMATTERS_LIMITED_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/iso_format.hpp>
#include <boost/date_time/date_format_simple.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/time_formatting_streams.hpp>
#include <boost/date_time/time_resolution_traits.hpp> // absolute_value

namespace boost {

namespace posix_time {

  //! Time duration to string -hh::mm::ss.fffffff. Example: 10:09:03.0123456
  /*!\ingroup time_format
   */
  inline std::string to_simple_string(time_duration td) {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special())
      {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes()) << ":";
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  //! Time duration in iso format -hhmmss,fffffff Example: 10:09:03,0123456
  /*!\ingroup time_format
   */
  inline
  std::string
  to_iso_string(time_duration td)
  {
    std::ostringstream ss;
    if(td.is_special()) {
      /* simply using 'ss << td.get_rep()' won't work on compilers
       * that don't support locales. This way does. */
      // switch copied from date_names_put.hpp
      switch(td.get_rep().as_special()) {
      case not_a_date_time:
        //ss << "not-a-number";
        ss << "not-a-date-time";
        break;
      case pos_infin:
        ss << "+infinity";
        break;
      case neg_infin:
        ss << "-infinity";
        break;
      default:
        ss << "";
      }
    }
    else {
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.hours());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.minutes());
      ss  << std::setw(2) << std::setfill('0')
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      char buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill('0')

          // JDG [7/6/02 VC++ compatibility]
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
            << buff;
#else
        << frac_sec;
#endif
      }
    }// else
    return ss.str();
  }

  //! Time to simple format CCYY-mmm-dd hh:mm:ss.fffffff
  /*!\ingroup time_format
   */
  inline
  std::string
  to_simple_string(ptime t)
  {
    std::string ts = gregorian::to_simple_string(t.date());// + " ";
    if(!t.time_of_day().is_special()) {
      return ts + " " + to_simple_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }

  //! Convert to string of form [YYYY-mmm-DD HH:MM::SS.ffffff/YYYY-mmm-DD HH:MM::SS.fffffff]
  /*!\ingroup time_format
   */
  inline
  std::string
  to_simple_string(time_period tp)
  {
    std::string d1(to_simple_string(tp.begin()));
    std::string d2(to_simple_string(tp.last()));
    return std::string("[" + d1 + "/" + d2 +"]");
  }

  //! Convert iso short form YYYYMMDDTHHMMSS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline
  std::string to_iso_string(ptime t)
  {
    std::string ts = gregorian::to_iso_string(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      return ts + "T" + to_iso_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }

  //! Convert to form YYYY-MM-DDTHH:MM:SS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline
  std::string
  to_iso_extended_string(ptime t)
  {
    std::string ts = gregorian::to_iso_extended_string(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      return ts + "T" + to_simple_string(t.time_of_day());
    }
    else {
      return ts;
    }
  }


} } //namespace posix_time


#endif


/* time_formatters_limited.hpp
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
*/