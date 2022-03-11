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