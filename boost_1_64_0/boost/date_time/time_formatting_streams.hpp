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
8nTo2JUaxAxA/MIKYg6AiObsHGwrrEX12gFsB1hBvFgH2J4E0cmtkGNNeSemHI4pksvzVqHlC/etrU9bsp2H2bYbabNttGYbhdk2QjZM0sJJHrUm6YNJbrUmudea5LPTgEBNWvwd1vgtGD9Fi7/JGv8Axh+mxV9rjV+O8Xth/EqOD1vjGyDerHfAoxnLhfbisVdpZ+04XjfN+z8RbNUB6+10rv6t9hLIuYXSwvlK+JIuQxts7Bjx7Hl8PBw+N+35hsM4Gv6+hL873nQYL8Cf4y2HcSj8TYG/W+GvCf6egL934c+woXFQ3o/3wEVYPXbffPW9H03/sPyCXaB/YIFmKBfV4uEL9Q285+FP+xvhfFvkj9jxQWE7CO+1gTBw+rPfue1x+BryBn0NgK/M5XCeCq3qjrvOVwuDGhZzPkJw6rIat9AZoIFeEOwJ6BQ7K31//SwqfS/GJfhCpfSdfjJgRL7v7tSUIi7dTmK0NFaQkk8Vyj10QT0fPqZjlSDJqZ2YedmkcT5B4qI8lXDSGlK5COilwvuuLwX0KxKh7+jJysweRWooxrMN7D3xdZx3H9jJpXew09zUwXrNcx41C4uVSqA9bRzI41t4929zg7K6DZRjEBqGoj0o9oTM5V3qBLefm9gJPu+wE/hFJ6jhTrDq96oTnKU6wem1shPcnbYTyANj3Ey41995JzhZdQLcjq9K6An+VD0huYhd0xO09gzMIAqD3Sw48FIaOn9kP9QbrOQ26yy/YclfoPL/45K0+amFW8+xuirDFyX10/jx8QaUD7sTfSMVfXC+D1cKIsYVOfo0qzbDGTU4mtc0PjyqxNblWogHQjxmCBhDs424+h7UHBykf8PpG6/+7WsGoQvVIlj5fFF5X+TDi2k7K5/3BBbDV6yRMV3YigeEEcuNdbwFtz6fFFGj9BwnYI6x3Fsa+3GBvCWJ/+gIyAAUQ7xM60dQJ60SRV/EE0Fkf5zPO/SrF+KmxA/diTLhLzxnvVPPbWzqmc5FYgyN8ya0Q22phCr4FSVqmLPYM1oRpg3nFyN3gnkuh5LEhsU8pCp1FDeKENlwgXK9H9wxsjWTGa/D/umtT+RA+9oUB2oN0lCtDo+rRz7uR8cI5LbungZW8ELybeqGl1yaEKMfqHto4M68Iwy+b67Vi9Nr6DoveB6DvEmOhZRi35VimhKDzyZZB6WN17gSOdQFJuMcrDHOAPh6Up/MrQKygtBJ2a0fd9MtxwM1hK6+PvLPSs1K1A9VYG19DJSqO9cVjG7/Ot3c3wLSKDM5X5C6Db17OVT0jACP0c8b2QzL1mSHw4NP0kI+vX4CZ4tNncd70sT7k+MTNEn3TdM1Sa04jZRjr3opKNRGHcMPB1J19UTV3DGqAJ1YRCpyjcVc6MpK4kn2WLFiLr6UYwwJ+Czr93hGDgr2WAzmGRm4O9vcWX2KN3UeP2hTen0kn3+dqo3k0MDUQoRPCBF9WYg45XElRNQrIWJQjRQi3u1IiKhIJUnW4Qxfu8GZWojoQTZ/SyVENE9nN0R7MSpbHkNUZltRufpYgUpskqyEtqnGY9mXRgaVeF2+KySP1E8qVeddZ1BzUa+a65IuhLGSePasSV5wFtTd8ZF6ijtlCJcmS8Z7he7zzxezpxScfHJiz3dx16KqI32s/QzN6yX7fvIqPSmX/O5MSIIlZdTfhfZkUyfxYWNTJ/NVw+liv6c3s+UbN8B+TwPG3F+qXw8qOleh8N+0QZnJnKs6V9l4Ol7ht5mH+VAikwf0BtnMfZegetfmDD/PGfZpxEac0Rfp8rJjAAu+i7SyXurK641GulJib8bm7+tTYLMabaVSl3AIIBq7yNz6DrETFjENlkPhxyI=
*/