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
4V4VccKBUHbzOROJhsgoLSnvKUxbA7haqGxjlTB4Z0PsEalUTx1NAzX2bZNYdwKTAa2fZT4/cYX77UZifQ2yhnzkrFwgXazgj1oL4lm8yKvVnweDfe+OZVn72T/LN8bOBitvkECWqn9Uom1RMWQQCSiHgZyfGK1moPSPZvgrAsRW2eUOo9/P0uZblwRjFUyOLT3m60unHXLxk9E8LoA5O0vbhzK1ZfDAqXeFs0Fv5MCu4l31hFOFOceuUyAdSNLEXsN1Ug64sj+i8YjQj2c6uraaPeDAqFbfP4QDqkSlUahH/8ARFkdrl6ie5aEXNuc6NuxGhmglKj2CNCqvsQp/o+GgifVRhBHaUg5sBcwRfSyS7mjeVCeY3Ql7qA2Sd/uIw0UhYEmGb0wvW+Efi89cmkcg+Kz4nELNJc3vDgWNLPJ+N62mAZYnayaP+lc0MLxBiSxpNxmyRJV0HqzRcZANTQbBp4SNoEqVdjeBBDYPp21s+fWGcRPnfNxeAcZZnDvKpcdymoOomb1Me2sEj83U+iDpaGv/P2bRHEJm4AAXsfB6YZr8IVj3SVhU8Q==
*/