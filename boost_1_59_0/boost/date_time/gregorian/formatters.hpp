#ifndef GREGORIAN_FORMATTERS_HPP___
#define GREGORIAN_FORMATTERS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/compiler_config.hpp"
#include "boost/date_time/gregorian/gregorian_types.hpp"
#if defined(BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS)
#include "boost/date_time/date_formatting_limited.hpp"
#else
#include "boost/date_time/date_formatting.hpp"
#endif
#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_format_simple.hpp"

/* NOTE: "to_*_string" code for older compilers, ones that define 
 * BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS, is located in 
 * formatters_limited.hpp
 */

namespace boost {
namespace gregorian {

  // wrapper function for to_simple_(w)string(date)
  template<class charT>
  inline 
  std::basic_string<charT> to_simple_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return to_simple_string_type<char>(d);
  }


  // wrapper function for to_simple_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_simple_string_type(const date_period& d) {
    typedef std::basic_string<charT> string_type;
    charT b = '[', m = '/', e=']';

    string_type d1(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.begin()));
    string_type d2(date_time::date_formatter<date,date_time::simple_format<charT>,charT>::date_to_string(d.last()));
    return string_type(b + d1 + m + d2 + e);
  }
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    return to_simple_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date_period)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date_period& d) {
    charT sep = '/';
    std::basic_string<charT> s(date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.begin()));
    return s + sep + date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d.last());
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    return to_iso_string_type<char>(d);
  }


  // wrapper function for to_iso_extended_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_extended_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return to_iso_extended_string_type<char>(d);
  }

  // wrapper function for to_iso_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_iso_string_type(const date& d) {
    return date_time::date_formatter<date,date_time::iso_format<charT>,charT>::date_to_string(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return to_iso_string_type<char>(d);
  }

  
  

  // wrapper function for to_sql_(w)string(date)
  template<class charT>
  inline std::basic_string<charT> to_sql_string_type(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::basic_ostringstream<charT> ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill(ss.widen('0')) 
       << ymd.day;
    return ss.str();
  }
  inline std::string to_sql_string(const date& d) {
    return to_sql_string_type<char>(d);
  }


#if !defined(BOOST_NO_STD_WSTRING)
  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date_period& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::wstring to_simple_wstring(const date& d) {
    return to_simple_string_type<wchar_t>(d);
  }
  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date_period& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_extended_wstring(const date& d) {
    return to_iso_extended_string_type<wchar_t>(d);
  }
  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::wstring to_iso_wstring(const date& d) {
    return to_iso_string_type<wchar_t>(d);
  }
  inline std::wstring to_sql_wstring(const date& d) {
    return to_sql_string_type<wchar_t>(d);
  }
#endif // BOOST_NO_STD_WSTRING

} } //namespace gregorian


#endif


/* formatters.hpp
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
*/