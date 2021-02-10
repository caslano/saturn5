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
Dde3ePSmu77mxjoJBA6np2fHOwUIYQD72fTiFGqzoQLY1lx6u0CFkpJTZMItmWW7GVftERLjrPyf1lY0DYp8vONl2GaPnKB+pdHjnqgbqFRfKIhptWr2sF91luwd5A6vVdp6sttgP4RKD1X5dFuB57lq6hMHlzvUuGnUdk+6rdI32JkUViqstbrhcicZKY32zKWdZ2vsVWXnxJqHGRZeJTTfokFfTxIlazn254L6I5FzhLaajv0xBb01K24CSLm1AhfIZODnOqPmZVfwXmEtzI1T5ZZpoTpqC9q6FlJg6UrrsTVpsb7HboiNvTdx1M0nW6+xT0sFvKroChUVJPEi82GaLDLiPk3wxNG6M+4y6I8Rw1AmBEOuvgmXs8ybgBG0wbPg7HmA19IWgU9gzauh1mRvniziLL6IZ6mHZeBmpn+F75PZ1Atk5fUF4/T//Uk5CSnsAdaGqA5o8hD+8eDzaqOJxyrDwYdRZVu8P/gdw57GAzyHseur9s6OEA9RxkeAKwzF2m8LX2oHcDT+dtzPq3syw1CAKHZvU3hzoDabfkeOy+NagZRk1+7W/vWCSjixwg9hNAtfRbMou/LCsuyv6LNg8jw4dQaLabZczOFDOFtOvQW3ePEYx22ax5d0vk/SivpH11I+8rK/1HrD
*/