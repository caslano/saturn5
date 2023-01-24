#ifndef ISO_FORMAT_HPP___
#define ISO_FORMAT_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/parse_format_base.hpp"

namespace boost {
namespace date_time {

//! Class to provide common iso formatting spec
template<class charT>
class iso_format_base {
public:
  //! Describe month format -- its an integer in iso format
  static month_format_spec month_format()
  {
    return month_as_integer;
  }

  //! String used printed is date is invalid
  static const charT* not_a_date()
  {     
    return "not-a-date-time";
  }
  //! String used to for positive infinity value
  static const charT* pos_infinity()
  {
    return "+infinity";
  }
  //! String used to for positive infinity value
  static const charT* neg_infinity()
  {
    return "-infinity";
  }

  //! ISO char for a year -- used in durations
  static charT year_sep_char()
  {
    return 'Y';
  }
  //! ISO char for a month
  static charT month_sep_char()
  {
    return '-';
  }
  //! ISO char for a day
  static charT day_sep_char()
  {
    return '-';
  }
  //! char for minute
  static charT hour_sep_char()
  {
    return ':';
  }
  //! char for minute
  static charT minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static charT second_sep_char()
  {
    return ':';
  }
  //! ISO char for a period
  static charT period_start_char()
  {
    return 'P';
  }
  //! Used in time in mixed strings to set start of time
  static charT time_start_char()
  {
    return 'T';
  }

  //! Used in mixed strings to identify start of a week number
  static charT week_start_char()
  {
    return 'W';
  }

  //! Separators for periods
  static charT period_sep_char()
  {
    return '/';
  }
  //! Separator for hh:mm:ss
  static charT time_sep_char()
  {
    return ':';
  }
  //! Preferred Separator for hh:mm:ss,decimal_fraction
  static charT fractional_time_sep_char()
  {
    return ',';
  }

  static bool is_component_sep(charT sep)
  {
    switch(sep) {
    case 'H':
    case 'M':
    case 'S':
    case 'W':
    case 'T':
    case 'Y':
    case 'D':return true;
    default:
      return false;
    }
  }

  static bool is_fractional_time_sep(charT sep)
  {
    switch(sep) {
    case ',':
    case '.': return true;
    default: return false;
    }
  }
  static bool is_timezone_sep(charT sep)
  {
    switch(sep) {
    case '+':
    case '-': return true;
    default: return false;
    }
  }
  static charT element_sep_char()
  {
    return '-';
  }

};

#ifndef BOOST_NO_STD_WSTRING

//! Class to provide common iso formatting spec
template<>
class iso_format_base<wchar_t> {
public:
  //! Describe month format -- its an integer in iso format
  static month_format_spec month_format()
  {
    return month_as_integer;
  }

  //! String used printed is date is invalid
  static const wchar_t* not_a_date()
  {      
    return L"not-a-date-time";
  }
  //! String used to for positive infinity value
  static const wchar_t* pos_infinity()
  {
    return L"+infinity";
  }
  //! String used to for positive infinity value
  static const wchar_t* neg_infinity()
  {
    return L"-infinity";
  }

  //! ISO char for a year -- used in durations
  static wchar_t year_sep_char()
  {
    return 'Y';
  }
  //! ISO char for a month
  static wchar_t month_sep_char()
  {
    return '-';
  }
  //! ISO char for a day
  static wchar_t day_sep_char()
  {
    return '-';
  }
  //! char for minute
  static wchar_t hour_sep_char()
  {
    return ':';
  }
  //! char for minute
  static wchar_t minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static wchar_t second_sep_char()
  {
    return ':';
  }
  //! ISO char for a period
  static wchar_t period_start_char()
  {
    return 'P';
  }
  //! Used in time in mixed strings to set start of time
  static wchar_t time_start_char()
  {
    return 'T';
  }

  //! Used in mixed strings to identify start of a week number
  static wchar_t week_start_char()
  {
    return 'W';
  }

  //! Separators for periods
  static wchar_t period_sep_char()
  {
    return '/';
  }
  //! Separator for hh:mm:ss
  static wchar_t time_sep_char()
  {
    return ':';
  }
  //! Preferred Separator for hh:mm:ss,decimal_fraction
  static wchar_t fractional_time_sep_char()
  {
    return ',';
  }

  static bool is_component_sep(wchar_t sep)
  {
    switch(sep) {
    case 'H':
    case 'M':
    case 'S':
    case 'W':
    case 'T':
    case 'Y':
    case 'D':return true;
    default:
      return false;
    }
  }

  static bool is_fractional_time_sep(wchar_t sep)
  {
    switch(sep) {
    case ',':
    case '.': return true;
    default: return false;
    }
  }
  static bool is_timezone_sep(wchar_t sep)
  {
    switch(sep) {
    case '+':
    case '-': return true;
    default: return false;
    }
  }
  static wchar_t element_sep_char()
  {
    return '-';
  }

};

#endif // BOOST_NO_STD_WSTRING

//! Format description for iso normal YYYYMMDD
template<class charT>
class iso_format : public iso_format_base<charT> {
public:
  //! The ios standard format doesn't use char separators
  static bool has_date_sep_chars()
  {
    return false;
  }
};

//! Extended format uses seperators YYYY-MM-DD
template<class charT>
class iso_extended_format : public iso_format_base<charT> {
public:
  //! Extended format needs char separators
  static bool has_date_sep_chars()
  {
    return true;
  }

};

} } //namespace date_time




#endif

/* iso_format.hpp
Hxc0Iiotah1RTqywFMpyHNLQGUNnVmV0FSFE+fgDIfYMwdStbZQ8WiBSZPhiyKDc7UjXN0+cL8G80vIiYU+3wZB+JBleiJMVZI0JdkSVUNKWQrnAkGFkOF5ImBUEw7Q5oj5R6lhj6CaE2sGQUkodS8y7caE8wrIywZBcytgSqNlkYhy2uFun0LDmNI9exwlzi7AqHSjm6bhQHBiSSaljg3k6ITQChlRS6lhhhseFKsGQQkodW8zwhNA+GNJAKYpFom0wGYRVDVlgxMaFyh1RE2DIR8o9/GiBib/ue3hv96J+IQrECis6X5QtYVGJjigYK6yRsCj7UqgRAqXHulR53oTsCKEjI2EKR8KCegkLwjuiKihjqwgLojpfUAW0FoEaq4It7ubv0jnoCTbBX/JX3Y8Pi+EGdz6h3v1DYUtCYYGYRXAnOXVZ6xUpreB6JGF+cdnnw6QIFpEtOq/Yfl7xN8WOhITFXEL2SMS3KujohNAaArUPjhr7fZoRIY2vw6D8/TfvsOZtQ7/QzgpN3b45GeWsj+7bVG+/rd+oV7KWliHZuo7G4VoAuPxv4WkZ5RfsXzhX97aptFNDvcOOZeuVhpdn2dLlr21d3/f1Cc3pw/xLylbPf5H0txRcz79M+ncqEWQS6P1DV8pat66b6h2ypWNxnQApZIZzle+UStt8FiDBzqgGbACktsfYYu3gDyCu86+1YMd/OER5h0kn
*/