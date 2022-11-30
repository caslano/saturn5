#ifndef GREGORIAN_FORMATTERS_LIMITED_HPP___
#define GREGORIAN_FORMATTERS_LIMITED_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/date_formatting_limited.hpp"
#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/date_format_simple.hpp"
#include "boost/date_time/compiler_config.hpp"

namespace boost {
namespace gregorian {

  //! To YYYY-mmm-DD string where mmm 3 char month name. Example:  2002-Jan-01
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date& d) {
    return date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d);
  }

  //! Convert date period to simple string. Example: [2002-Jan-01/2002-Jan-02]
  /*!\ingroup date_format
   */
  inline std::string to_simple_string(const date_period& d) {
    std::string s("[");
    std::string d1(date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d.begin()));
    std::string d2(date_time::date_formatter<date,date_time::simple_format<char> >::date_to_string(d.last()));
    return std::string("[" + d1 + "/" + d2 + "]");
  }

  //! Date period to iso standard format CCYYMMDD/CCYYMMDD. Example: 20021225/20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date_period& d) {
    std::string s(date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.begin()));
    return s + "/" + date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d.last());
  }


  //! Convert to iso extended format string CCYY-MM-DD. Example 2002-12-31
  /*!\ingroup date_format
   */
  inline std::string to_iso_extended_string(const date& d) {
    return date_time::date_formatter<date,date_time::iso_extended_format<char> >::date_to_string(d);
  }

  //! Convert to iso standard string YYYYMMDD. Example: 20021231
  /*!\ingroup date_format
   */
  inline std::string to_iso_string(const date& d) {
    return date_time::date_formatter<date,date_time::iso_format<char> >::date_to_string(d);
  }
  
  

  inline std::string to_sql_string(const date& d) 
  {
    date::ymd_type ymd = d.year_month_day();
    std::ostringstream ss;
    ss << ymd.year << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.month.as_number() //solves problem with gcc 3.1 hanging
       << "-"
       << std::setw(2) << std::setfill('0') 
       << ymd.day;
    return ss.str();
  }


} } //namespace gregorian


#endif


/* formatters_limited.hpp
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
*/