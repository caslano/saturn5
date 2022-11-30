#ifndef POSIXTIME_FORMATTERS_HPP___
#define POSIXTIME_FORMATTERS_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
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
#include <boost/date_time/time_parsing.hpp>

/* NOTE: The "to_*_string" code for older compilers, ones that define
 * BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS, is located in
 * formatters_limited.hpp
 */

namespace boost {

namespace posix_time {

  // template function called by wrapper functions:
  // to_*_string(time_duration) & to_*_wstring(time_duration)
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(time_duration td) {
    std::basic_ostringstream<charT> ss;
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
      charT fill_char = '0';
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.hours()) << ":";
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.minutes()) << ":";
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      charT buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill(fill_char)

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
  //! Time duration to string -hh::mm::ss.fffffff. Example: 10:09:03.0123456
  /*!\ingroup time_format
   */
  inline std::string to_simple_string(time_duration td) {
    return to_simple_string_type<char>(td);
  }


  // template function called by wrapper functions:
  // to_*_string(time_duration) & to_*_wstring(time_duration)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(time_duration td)
  {
    std::basic_ostringstream<charT> ss;
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
      charT fill_char = '0';
      if(td.is_negative()) {
        ss << '-';
      }
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.hours());
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.minutes());
      ss  << std::setw(2) << std::setfill(fill_char)
          << date_time::absolute_value(td.seconds());
      //TODO the following is totally non-generic, yelling FIXME
#if (defined(BOOST_MSVC) && (_MSC_VER < 1300))
      boost::int64_t frac_sec =
        date_time::absolute_value(td.fractional_seconds());
      // JDG [7/6/02 VC++ compatibility]
      charT buff[32];
      _i64toa(frac_sec, buff, 10);
#else
      time_duration::fractional_seconds_type frac_sec =
        date_time::absolute_value(td.fractional_seconds());
#endif
      if (frac_sec != 0) {
        ss  << "." << std::setw(time_duration::num_fractional_digits())
            << std::setfill(fill_char)

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
  inline std::string to_iso_string(time_duration td){
    return to_iso_string_type<char>(td);
  }

  //! Time to simple format CCYY-mmm-dd hh:mm:ss.fffffff
  /*!\ingroup time_format
   */
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(ptime t)
  {
    // can't use this w/gcc295, no to_simple_string_type<>(td) available
    std::basic_string<charT> ts = gregorian::to_simple_string_type<charT>(t.date());// + " ";
    if(!t.time_of_day().is_special()) {
      charT space = ' ';
      return ts + space + to_simple_string_type<charT>(t.time_of_day());
    }
    else {
      return ts;
    }
  }
  inline std::string to_simple_string(ptime t){
    return to_simple_string_type<char>(t);
  }

  // function called by wrapper functions to_*_string(time_period)
  // & to_*_wstring(time_period)
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(time_period tp)
  {
    charT beg = '[', mid = '/', end = ']';
    std::basic_string<charT> d1(to_simple_string_type<charT>(tp.begin()));
    std::basic_string<charT> d2(to_simple_string_type<charT>(tp.last()));
    return std::basic_string<charT>(beg + d1 + mid + d2 + end);
  }
  //! Convert to string of form [YYYY-mmm-DD HH:MM::SS.ffffff/YYYY-mmm-DD HH:MM::SS.fffffff]
  /*!\ingroup time_format
   */
  inline std::string to_simple_string(time_period tp){
    return to_simple_string_type<char>(tp);
  }

  // function called by wrapper functions to_*_string(time_period)
  // & to_*_wstring(time_period)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(ptime t)
  {
    std::basic_string<charT> ts = gregorian::to_iso_string_type<charT>(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      charT sep = 'T';
      return ts + sep + to_iso_string_type<charT>(t.time_of_day());
    }
    else {
      return ts;
    }
  }
  //! Convert iso short form YYYYMMDDTHHMMSS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline std::string to_iso_string(ptime t){
    return to_iso_string_type<char>(t);
  }


  // function called by wrapper functions to_*_string(time_period)
  // & to_*_wstring(time_period)
  template<class charT>
  inline std::basic_string<charT> to_iso_extended_string_type(ptime t)
  {
    std::basic_string<charT> ts = gregorian::to_iso_extended_string_type<charT>(t.date());// + "T";
    if(!t.time_of_day().is_special()) {
      charT sep = 'T';
      return ts + sep + to_simple_string_type<charT>(t.time_of_day());
    }
    else {
      return ts;
    }
  }
  //! Convert to form YYYY-MM-DDTHH:MM:SS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline std::string to_iso_extended_string(ptime t){
    return to_iso_extended_string_type<char>(t);
  }

#if !defined(BOOST_NO_STD_WSTRING)
  //! Time duration to wstring -hh::mm::ss.fffffff. Example: 10:09:03.0123456
  /*!\ingroup time_format
   */
  inline std::wstring to_simple_wstring(time_duration td) {
    return to_simple_string_type<wchar_t>(td);
  }
  //! Time duration in iso format -hhmmss,fffffff Example: 10:09:03,0123456
  /*!\ingroup time_format
   */
  inline std::wstring to_iso_wstring(time_duration td){
    return to_iso_string_type<wchar_t>(td);
  }
    inline std::wstring to_simple_wstring(ptime t){
    return to_simple_string_type<wchar_t>(t);
  }
  //! Convert to wstring of form [YYYY-mmm-DD HH:MM::SS.ffffff/YYYY-mmm-DD HH:MM::SS.fffffff]
  /*!\ingroup time_format
   */
  inline std::wstring to_simple_wstring(time_period tp){
    return to_simple_string_type<wchar_t>(tp);
  }
  //! Convert iso short form YYYYMMDDTHHMMSS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline std::wstring to_iso_wstring(ptime t){
    return to_iso_string_type<wchar_t>(t);
  }
  //! Convert to form YYYY-MM-DDTHH:MM:SS where T is the date-time separator
  /*!\ingroup time_format
   */
  inline std::wstring to_iso_extended_wstring(ptime t){
    return to_iso_extended_string_type<wchar_t>(t);
  }

#endif // BOOST_NO_STD_WSTRING


} } //namespace posix_time


#endif


/* time_formatters.hpp
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
*/