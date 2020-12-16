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
Xtd49GqIgDNwtnqle/uYfEN0zWgWfW1WX2gl9xwa+jDNx54JTH+GhmnPr0ew2QGED790Cl8jDx/PgRhgvVQvWBF2PQt987h8U69Te7Bw2pOO2+2jsjP218qNuWMsSR8Z9//kAzFevrn5uOT6mT8NT00/czrnF/oX08WzEa+n4WE0/TC0SrBEiqyF7G3JFOGuH6VVMHx5LqY/xdRYR3R+LW9Zjz947P5dj9eg0HFcKADXYXktNvuOc6lzGWzGiVetYVHSO8wAu9Lg048SJ7PrhCSc7l35D6INXt2h07VDJJ8cjoND44OGBw+IDxoZGmwCtd3cvNXA03IdlWDPhEEiAU7JInfL3LSEpML9fIHN4Lm0hH4pdVlayoB7U9LZBCdTu/3yqXGmTfDvOwFeMF+34w+nA/KupRRTsLCXCqwyAyn5I5Scq8/HtkAU5YfC7b0CPI2Mfsp47td7Y+FlSws9TjrS1xzbiVl+dH23MAHiKac86sEH3gQlqTLl5BQ2egxCadKExhn7OmNVbAFt/EQPtnx5on0tX65oV/PL0/IVHa5KaOyQ16SCEPcT275PQtt7L7uJUiYEm9ZZptkYQRcygHIaY6M5HHSNI9ITHWc7mF/Tk/Crx7syLXVuGuTokJtShPS60S77KIY4uCgJl4w2AwnSSvN685GiB4a6z6KY7O7yhs9cBGaEeqC0Uqs/fEvjREiK5PUkSFfsfYCoqnWxtZGHTjP11IqdRYNUcINo40T6lUNizaY73E7jBfr/Z/r/Cf3/hv53SXca2394OvWY+g5z4rjwaDGGs9NKjN8z0+X8Yb13TplrhgpVAF0EsMJlO+RtuoTMIRA6404KGY8ltfeyX9BfFORU1ov/IusTm7c9oXAf0oQsKJB0inuR7kVKZxY8sHlnenzZZuyEcJa4yjs+Bc2DADk/s3EPQC4ikEDYCYSnuy0I70LpOwXC70iE0xTCgQ4QDg3Q8ng71XHaquNt3pnVTnWosrJG36rOhses85UurnMa6jzXZanzbqC4S9R5oJxzXarOk10d1LlU17ldiqS1Q5FdaVaKZDTv7NkuRbI6psh3JZvh0GQ7KY3J5gLZitMsZNuDeuwWZDtbiSqKbAeldUC209olW6kmW7tEdbVD1JudVqKm0Un4dunVs2N67R/K52nKv+lgyrtB+ScdFsq3orJ7BOV/LSmfrih/m6MDytdpyrfbLmnttour3XZxt9MuaQ5ruziadw5ol5q5HVPze9R4hmt+hmi86EC0nBCUWLXEWnofZV4BAdKVyorjh+f79Ng9hUBS9PBZh2zRzD0oINtYLHvhuWniyFiumHQHcOJglr7HNne5h09QT5DpxERVBRBaPCigKJlxbJiKbo6k0+zfTennPcsdNv5DEuJOXAMko/lM9btOWQLG9ItRgp7PNzp1CVO4hCyakLvtbKcEIMGFpIiDmG1P1TjkGd6GX1IQ8NBz7BEmHhdxIT1pGuy2q108smRB+wxTMcE94FCYGi5vw0aJqZ7WVjkUpt5lOLjGBRGktG6728W2Z4fY7vP6iGnjz7IGenp43jBr8ISuwQAaibvtabcGuR3i91+oY/r/g2IvwZ4u4fzb4doSyR/vxdMXo0ffF8PX7E/jrbW3h2Br7Wj62PC03loLDlbX7F+bZvosIv1WWsivvoT9bQap1wS0cxjaSgHtHTu0oRra0Wn0+c0wQtS89ClkvarueJG/zJ7/b4Noo+9rp76nxRN5l+w8K1bKe1WKyIBuWYXpaXgeg3IKUFvtoG4GqAcIFBVdRILT/RRoXnpUl01bwPqTnTVvo1eJYx0DvrsgCeCjABgHkG3ZoYO2OnVeYnrfqSD1tzojpnyp+GM=
*/