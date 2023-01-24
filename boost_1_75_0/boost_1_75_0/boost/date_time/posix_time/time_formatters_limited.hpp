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
lgV+GOG5vlAeNWVTvow0eQASHKckOdZeRHkSog/W7xRG5G70rcZVa1jWU/Yf7F9Et7zxc+ZYJe843U719ZDcdFa3Um6DsC9T2zg3+f9ObEa0CU/mXpirIj9vGY5b/9LLmUA3o3xFrzj4C3XMe9QATpFx28ZYTgdnHXUSNIsN+l1tWsh15qM6ESyOoq0+rckB8Hy3yIupNm6uimdjTGOSXa47rMpgMXvCDm3B600KNIJxayRbQiz7xXYbAMe+BTno+SVxExcYydqRSVDZHrviKyNa84msUI5VuhsarXNjAqvRd27C1XbRd/3p+Q9artvuE6wSfi95Qmpy6PlRoLudcHuQvTEAFG9vmrkafUG7NAGqOz8OZJvb/tKbWgPHZivXUqymRlxSd10iXIUasryyLNMnYoDIuf3xhOiVPuTRQGo6ZZgHddvtNngOQoPu92Ea0C+2kzqh7cDs/MWY7Twt2HcF0EMW9M6fCuGyakB6XBsD1eMt0UoeUm19/oP3sLzX+dOeCtlD3iBouwoBQLnlDnc+t8Vwre4rkBKAxS+bK+8J6+UP85Wd+ys3O812aaC9GiJYN1zDkt/JvI0UMGpClSf74sZfhV3GUIXNtwxoy25uWLRjccLv+iKyPvnYqOjxlzWynzH6egon/mhuDkFDyxOwUxGnwbFWsYadqKlGCrWG1pUDMa7iFzSekaRiVzjbeNuDF+wWteMNYNWg
*/