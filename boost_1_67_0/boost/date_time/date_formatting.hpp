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