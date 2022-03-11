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