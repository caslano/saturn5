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
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
*/