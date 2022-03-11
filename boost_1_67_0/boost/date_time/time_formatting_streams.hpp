#ifndef DATE_TIME_TIME_FORMATTING_STREAMS_HPP___
#define DATE_TIME_TIME_FORMATTING_STREAMS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/compiler_config.hpp>

#ifndef BOOST_DATE_TIME_NO_LOCALE

#include <locale>
#include <iomanip>
#include <iostream>
#include <boost/date_time/date_formatting_locales.hpp>
#include <boost/date_time/time_resolution_traits.hpp>

namespace boost {
namespace date_time {


  //! Put a time type into a stream using appropriate facets
  template<class time_duration_type,
           class charT = char>
  class ostream_time_duration_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_duration_type::fractional_seconds_type fractional_seconds_type;

    //! Put time into an ostream 
    static void duration_put(const time_duration_type& td, 
                             ostream_type& os)
    {
      if(td.is_special()) {
        os << td.get_rep(); 
      }
      else {
        charT fill_char = '0';
        if(td.is_negative()) {
          os << '-';
        }
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.hours()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.minutes()) << ":";
        os  << std::setw(2) << std::setfill(fill_char) 
            << absolute_value(td.seconds());
        fractional_seconds_type frac_sec = 
          absolute_value(td.fractional_seconds());
        if (frac_sec != 0) {
          os  << "." 
              << std::setw(time_duration_type::num_fractional_digits())
              << std::setfill(fill_char)
              << frac_sec;
        }
      } // else
    } // duration_put
  }; //class ostream_time_duration_formatter

  //! Put a time type into a stream using appropriate facets
  template<class time_type,
           class charT = char>
  class ostream_time_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_type::date_type date_type;
    typedef typename time_type::time_duration_type time_duration_type;
    typedef ostream_time_duration_formatter<time_duration_type, charT> duration_formatter;

    //! Put time into an ostream 
    static void time_put(const time_type& t, 
                         ostream_type& os)
    {
      date_type d = t.date();
      os << d;
      if(!d.is_infinity() && !d.is_not_a_date())
      {
        os << " "; //TODO: fix the separator here.
        duration_formatter::duration_put(t.time_of_day(), os);
      }
      
    } // time_to_ostream    
  }; //class ostream_time_formatter


  //! Put a time period into a stream using appropriate facets
  template<class time_period_type,
           class charT = char>
  class ostream_time_period_formatter
  {
  public:
    typedef std::basic_ostream<charT> ostream_type;
    typedef typename time_period_type::point_type time_type;
    typedef ostream_time_formatter<time_type, charT> time_formatter;

    //! Put time into an ostream 
    static void period_put(const time_period_type& tp, 
                           ostream_type& os)
    {
      os << '['; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.begin(), os);
      os << '/'; //TODO: facet or manipulator for periods?
      time_formatter::time_put(tp.last(), os);
      os << ']'; 

    } // period_put

  }; //class ostream_time_period_formatter


  
} } //namespace date_time

#endif //BOOST_DATE_TIME_NO_LOCALE

#endif

/* time_formatting_streams.hpp
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
*/