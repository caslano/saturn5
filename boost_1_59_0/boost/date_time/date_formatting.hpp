#ifndef DATE_TIME_DATE_FORMATTING_HPP___
#define DATE_TIME_DATE_FORMATTING_HPP___

/* Copyright (c) 2002-2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/iso_format.hpp"
#include "boost/date_time/compiler_config.hpp"
#include <boost/io/ios_state.hpp>
#include <string>
#include <sstream>
#include <iomanip>

/* NOTE: "formatter" code for older compilers, ones that define 
 * BOOST_DATE_TIME_INCLUDE_LIMITED_HEADERS, is located in  
 * date_formatting_limited.hpp
 */

namespace boost {
namespace date_time {

  //! Formats a month as as string into an ostream
  template<class month_type, class format_type, class charT=char>
  class month_formatter
  {
    typedef std::basic_ostream<charT> ostream_type;
  public:
    //! Formats a month as as string into an ostream
    /*! This function demands that month_type provide
     *  functions for converting to short and long strings
     *  if that capability is used.
     */
    static ostream_type& format_month(const month_type& month,
                                      ostream_type &os)
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
          boost::io::basic_ios_fill_saver<charT> ifs(os);
          os << std::setw(2) << std::setfill(os.widen('0')) << month.as_number();
          break;
        }
        default:
          break;
          
      }
      return os;
    } // format_month
  };


  //! Convert ymd to a standard string formatting policies
  template<class ymd_type, class format_type, class charT=char>
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
    static std::basic_string<charT> ymd_to_string(ymd_type ymd)
    {
      typedef typename ymd_type::month_type month_type;
      std::basic_ostringstream<charT> ss;

      // Temporarily switch to classic locale to prevent possible formatting
      // of year with comma or other character (for example 2,008).
      ss.imbue(std::locale::classic());
      ss << ymd.year;
      ss.imbue(std::locale());

      if (format_type::has_date_sep_chars()) {
        ss << format_type::month_sep_char();
      }
      //this name is a bit ugly, oh well....
      month_formatter<month_type,format_type,charT>::format_month(ymd.month, ss);
      if (format_type::has_date_sep_chars()) {
        ss << format_type::day_sep_char();
      }
      ss  << std::setw(2) << std::setfill(ss.widen('0')) 
          << ymd.day;
      return ss.str();
    }
  };


  //! Convert a date to string using format policies
  template<class date_type, class format_type, class charT=char>
  class date_formatter
  {
  public:
    typedef std::basic_string<charT> string_type;
    //! Convert to a date to standard string using format policies
    static string_type date_to_string(date_type d)
    {
      typedef typename date_type::ymd_type ymd_type;
      if (d.is_not_a_date()) {
        return string_type(format_type::not_a_date());
      }
      if (d.is_neg_infinity()) {
        return string_type(format_type::neg_infinity());
      }
      if (d.is_pos_infinity()) {
        return string_type(format_type::pos_infinity());
      }
      ymd_type ymd = d.year_month_day();
      return ymd_formatter<ymd_type, format_type, charT>::ymd_to_string(ymd);
    }    
  };


} } //namespace date_time


#endif


/* date_formatting.hpp
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
*/