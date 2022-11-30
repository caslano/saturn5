#ifndef DATE_TIME_SIMPLE_FORMAT_HPP___
#define DATE_TIME_SIMPLE_FORMAT_HPP___

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

//! Class to provide simple basic formatting rules
template<class charT>
class simple_format {
public:

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
  //! Describe month format
  static month_format_spec month_format()
  {
    return month_as_short_string;
  }
  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }
  //! This format uses '-' to separate date elements
  static bool has_date_sep_chars()
  {
    return true;
  }
  //! Char to sep?
  static charT year_sep_char()
  {
    return '-';
  }
  //! char between year-month
  static charT month_sep_char()
  {
    return '-';
  }
  //! Char to separate month-day
  static charT day_sep_char()
  {
    return '-';
  }
  //! char between date-hours
  static charT hour_sep_char()
  {
    return ' ';
  }
  //! char between hour and minute
  static charT minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static charT second_sep_char()
  {
    return ':';
  }

};

#ifndef BOOST_NO_STD_WSTRING

//! Specialization of formmating rules for wchar_t
template<>
class simple_format<wchar_t> {
public:

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
  //! Describe month format
  static month_format_spec month_format()
  {
    return month_as_short_string;
  }
  static ymd_order_spec date_order()
  {
    return ymd_order_iso; //YYYY-MM-DD
  }
  //! This format uses '-' to separate date elements
  static bool has_date_sep_chars()
  {
    return true;
  }
  //! Char to sep?
  static wchar_t year_sep_char()
  {
    return '-';
  }
  //! char between year-month
  static wchar_t month_sep_char()
  {
    return '-';
  }
  //! Char to separate month-day
  static wchar_t day_sep_char()
  {
    return '-';
  }
  //! char between date-hours
  static wchar_t hour_sep_char()
  {
    return ' ';
  }
  //! char between hour and minute
  static wchar_t minute_sep_char()
  {
    return ':';
  }
  //! char for second
  static wchar_t second_sep_char()
  {
    return ':';
  }

};

#endif // BOOST_NO_STD_WSTRING
} } //namespace date_time




#endif

/* date_format_simple.hpp
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
*/