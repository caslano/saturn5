#ifndef DATE_TIME_DATE_FORMATTING_LIMITED_HPP___
#define DATE_TIME_DATE_FORMATTING_LIMITED_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/compiler_config.hpp"
#include <string>
#include <sstream>
#include <iomanip>


namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class month_type, class format_type>
  class month_formatter
  {
  public:
    //! Formats a month as as string into an ostream
    /*! This function demands that month_type provide
     *  functions for converting to short and long strings
     *  if that capability is used.
     */
    static std::ostream& format_month(const month_type& month,
                                      std::ostream& os)
    {
      switch (format_type::month_format()) 
      {
        case month_as_short_string: 
        { 
          os << month.as_short_string(); 
          break;
        }
        case month_as_long_string: 
        { 
          os << month.as_long_string(); 
          break;
        }
        case month_as_integer: 
        { 
          os << std::setw(2) << std::setfill('0') << month.as_number();
          break;
        }
     
      }
      return os;
    } // format_month
  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type, class format_type>
  class ymd_formatter
  {
  public:
    //! Convert ymd to a standard string formatting policies
    /*! This is standard code for handling date formatting with
     *  year-month-day based date information.  This function 
     *  uses the format_type to control whether the string will
     *  contain separator characters, and if so what the character
     *  will be.  In addtion, it can format the month as either
     *  an integer or a string as controled by the formatting 
     *  policy
     */ 
    static std::string ymd_to_string(ymd_type ymd)
    {
      typedef typename ymd_type::month_type month_type;
      std::ostringstream ss;
      ss << ymd.year;
      if (format_type::has_date_sep_chars()) {
        ss << format_type::month_sep_char();
      }
      //this name is a bit ugly, oh well....
      month_formatter<month_type,format_type>::format_month(ymd.month, ss);
      if (format_type::has_date_sep_chars()) {
        ss << format_type::day_sep_char();
      }
      ss  << std::setw(2) << std::setfill('0') 
          << ymd.day;
      return ss.str();
    }
  };


  //! Convert a date to string using format policies
  template<class date_type, class format_type>
  class date_formatter
  {
  public:
    //! Convert to a date to standard string using format policies
    static std::string date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return format_type::not_a_date();
      }
      if (d.is_neg_infinity()) {
        return format_type::neg_infinity();
      }
      if (d.is_pos_infinity()) {
        return format_type::pos_infinity();
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type>::ymd_to_string(ymd);
    }    
  };


} } //namespace date_time


#endif


/* date_formatting_limited.hpp
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
*/