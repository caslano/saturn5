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
n3zoLlT3Tuq87/GKJTdqFyA1GbtPo3QbXFfIL0v9kZCEEsl4TMCQ4VX8C6yPN/Ej1BzxiVXF/DgUk1171690NCy5ZOje070eHZlKpYhi8KU7wwbbPUtwGcxL1jbnKkS04VwqagPf1iiL5CO1osUPGyN8Z7nh/Er+dT/ZB+9m1Mf9u9zjdGEpBdi7xGyShTPbk3n+8tUYpgpWppKqJdJLqsvlHt5D2PxYjnybU2wuChaFa9u2bdu2TttT2z21bd/atm3bunX/v7btdmYyyWQeJrORnfW+s5LvYf0NitJF61vbuNEC+AU5JDb9Ku6mRtTvzQGVX4lDy9Vd9qHKepUkLosg6Sk1WX0mOdgW1PG8a4MMTZG1PsSptjNfEjSjLN515YJJ0hNVvKw9CiQBsGif+mEuGUj2hdzgbSSSasUyWAdYpWPwS2bIv+rIELo0yCIEFpuS3Poc0fsnb94TH3A/CQftBKIMIJOg6AUio/AOOU44JyHz0H27bHznF74Mt9CXHpBHv/B8EXjSUNmWl+mhMbFWYvfhkWubU72uZy/7NC4QFgg3R7IWYIoXYShS+tXTAGGMCKX+eN7odWNEi95CEnP6c7bE1CUnvK2GtCLi21wL7ryhZIV5rcS2QFHNxk8QdjrU5E2PClIuVZxtbWhfb/UYE6euMcBeZ5qnnxjTw2gtrw7kiu4BW/tdoJ26WuuQBdY7WXG0v/NIr8e0
*/