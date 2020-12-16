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
02NJMyZ2vgq/NZoEB2K1owR9P0HfbAZdRtAY3JU1uR6bHGmDy85Y2tlLhW+5mT5hmapPwIfwXaBPYDQjVcJ6Krw1K3yevvBdqZoqYeFvQZVgqh9gFsn2dlzeIXWOkHC8diHhYM8od3/QXlUoAtx2EXDo5hb4hqvYgt2kxEMBtemREEqJPZPUCroikX1jd2hDvVnW3AcyyTKbxnqLoVuZQPF+ERcoZG3RuChr1hyCLbDjfjgTBxYqp8VidheZh558EnbqQ9ipVbJTm6XA4jMukyoTsHPhLWsjYagGaFFUCawluDR47Kox/3xGj1AvN4yl62PQ+CQaUqL5uOm3tAIns3FEHhdx9h7YDXcnxDyFvAtSQYpywm6cw4hSzuEqE80ELk4kkKygIPDHfR6NchfP5XzpXkfUi/poPuqo1+AA6vXIQBkJUTGSDyLyq7r+8ZADUT1FqJ5gqGr0qKYiqvebM5FnBdtbg1gQ4OTpWpSCa68RcybH/AJhPp9hnq/H3BUx39Bc6xvjYSYkrLBZ7JE5X0K5tzY3zpjdtsPe/eJKXLTUE87BIsXt1KAX+09W4FaWuy4Fs6LQwrUSF6cTCkxEIS1r1i1crvGqLVqyq1Hz9zxlMm8XnrH1h7dTRyF7HQWniB7RHRh2nxYRtP2WeE7/EfclpCyWKbVMJvyqMSpq+zR2nITp0hUdcRmqNPSLRrrsoVl3T+trMgBPs0HfrnYZpwcunjFsjaocydZWDn4TDxqGKTHtzlrwKMLrWjhhv2yhnmGQ5ScabcmuxIiGkgCtYAaLeRWFnqkCGrA5Ns0R+aOeVou+bBRxE4k7Iw2+Ihpc28eEBn8Ac7TwPWnAgLoA1phWVA5TJk1nA50XA/lpJr2YRiX9yP3AsJJu1pf07i9Qkg8yir5EIzyJ61zYRCcYoKkxA7ShmdpzFOWRBKDeacY+FQwNzyYUfn/MyzSh3Egrmmb40TFIZSoGtKno16aiz5xbAofEU1mp7BzLRZ75kBl51G6FXZL40pquJm3vbdJTyw8A/fancm1nudR2ntpMXUiLxMoJQ3bm7hTotxPU+45EkXQyRJCHmVR7GIbj7ZF0VFSOrYbf2PdYfzGVOlHlerPK3aavXGMjVG5Eqp5jVBqn5sZPtanZlfB9eqJJYx9BfBmpSTOtJ+DFoc/eqZNZco2tm83Jxv5I6Dn9ZE5xkR1qAxds8BsvqawUN2xlzopvcdqTjlxNxOfQxyFo53joxkOvdNaCF+GBbJH0dS1Lo7ouVM9EgVgP85uF+Cwzb/qGqvsOzRKPnfKOZ3ViQ5sU+wCHaXSx7+YP2FZiMioyx4r+HUz96+xFR6C6/t32E7Q7j5WP6PgElrI2ocYnZXCO1Vcg/CaCaTSINjCWlQY5x8EcEYJ2DTsQhncxMhq8qeaLKGYzcF5sf2gpzC1tirYVOAVzZQEhIjk0HdsLUkrolC+gkQNhj2C1keFWkJnTMDhQR+Ge70flxJlEhH3oBNpn6Ah75Y9Q5htc5T8eIHqLTiRxdjLBXsZgb9XD9kPYJRhbLFs/0rQRaBhzj9vMx9zfU3DMaefwa/iY62fXdJQ1XOtUiJTDFxJ6wD4chHTEpCbic2jtZ43RSH+BRF3oZlPjFh2PjbtG37jz90Pj6rDT8GRCWx3UTtEkqnotg1vW6rw23HR5qMaVuiVeqRyRHPNlCkVNDGDIa38b1f7Nnlj7sfrar/ihUbGl6adwCS9fXhBO2hqVQP+AKmsbvGIsMvQNSkrHyt0IgGEcAUx2YPJbXblLZtzgbV74TKHTtuokp+2xfk7babBrGgTfa/vguyM6oCOfI59fw8dUP8N06KPTZHznVTK+8zR+oFDL+C4es+M=
*/