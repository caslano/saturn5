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
iO/4LErLisdMO/mRMZOYaHTyjQ8a5uKyz6QjfsvsIE3xFjthwX+zWP3augBJkSmO90KPQkk0rPMdpzAEIKx66yhcUELeXcrhCRN7Cs8idAZD1bveyKvhnmIWN63ucemqkwvOaT/OST/KzPWL3RhaDAkXcO9ZP0r9TQLa8Ip+GwYANUrqD9/hiFFo7hcU2AsFhpVYY6s1wzF3ndkboTzofOWLfvWndJO/Z7H800JgJLWcLocPxOaTtIHpGiKlAtfaiITOUQ+GK29Smnc9VHIJThz1S5LXGqXUWso4D0k5S7VMq/IleSWgkNgaPrVhLwy50H45VTFDUrYxGjm6KxS46tP93OzE1sIoCyzYveFzPuhHw7+VLKTSAfM+7AawAp6GLGX6NhOaxNvuA+5xlXLosm2g7fpDhizcf5HEIZenZwwVhDp4iDJ5iox06DtvYumPIDmaoCdwm2QDDPzUJdsq8K53yAbceIv9G4/54ltubBW1wxNEpFvTU5NIIxE+GPx3bjdeFRfLV72PjIBvV9mDv9NdgcJOUX1qJH/unixv3qUPhY4J6M9kCT5P81KOr0xa4l1vNXOwt1cAbEfNW/Jr9GXsLgDIKg29OjbURu/dSBsJfc7EdF49dQODIpPlZ5V3loFsUpIwiAZ/ZkXXzCbGsKRC6WPwtYhzxFGm6zXxhcCYmpzoGSooeD76jRs0Itccl7qwxs7i/LfTQZV8
*/