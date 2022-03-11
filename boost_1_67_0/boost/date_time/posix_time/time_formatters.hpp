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