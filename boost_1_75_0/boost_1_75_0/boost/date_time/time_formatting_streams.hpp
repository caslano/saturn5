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
hzWuNibyMLEN5E32Vnqvjuzf2j8ytA+apw8LE6CfpT62th2Z2LYPnjf7OczmkcH8MSeBrmRytOGEd8TY0Dgw6J23a5SwuZbOMdBUOhVoTwtk0Dbk8mOjMHtfRQ/mo2jbGCXA/PCR8aGjlFx/oH9Mf9TA7U6fQmNkn5XUGrHuyNAwpXYfHu4fyB8YRWJzT0/Pzvyh/qERSvHPCegimHLHoA1jAmd04gCU+sPnqvz5+eHDwIDnE30yTjCSPjK2w/iCgUHyx4boUNi/M78fKsAY0yuZUc2r1gebxkaPHO7NQ1/1g23SRj2Qff0DGoEHzS3p3jsu3iQ6vWGof//IKPgzWWxiattMWzMKHsaODsFzRRTrDzGbXH8QkY3HjHrbVPdo7862MUNBe1DREQdPvnFtdA0PwzQ3Dh3bz2o4s42T/rH94+x+1WYC3b9+n7SZD5tx6O5x0j0ABZ3ltD731D7zqbsLHOYnxo0hDyubI/v2DQ0M4ZRKr8e2ffrNTi4ex+unGb8wf5w2YGSgf4Lo56oNQTb02GnotzPZtvdy8E5VtJu2f7g3T+9qsmF0gj2k6FSsLbQvHZo4YE7+2prLka0tcB3hTmxtmeoId2JrSzM7X1tvOfDpo8zOduCO7ts3Dofh/D7oPvoU1m5qePYODGGdjgp8GGPna2u0URikMPNA99EJNK/R47sH8AjdSGCZClMh6YWhM5bfOYrVsQl9
*/