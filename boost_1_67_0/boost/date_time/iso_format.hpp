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