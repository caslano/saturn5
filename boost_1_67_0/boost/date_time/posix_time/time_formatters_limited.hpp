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