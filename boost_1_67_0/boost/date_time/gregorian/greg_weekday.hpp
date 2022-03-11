#ifndef GREG_WEEKDAY_HPP___
#define GREG_WEEKDAY_HPP___

/* Copyright (c) 2002,2003,2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/date_time/constrained_value.hpp>
#include <boost/date_time/date_defs.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <stdexcept>
#include <string>

namespace boost {
namespace gregorian {

  //bring enum values into the namespace
  using date_time::Sunday;
  using date_time::Monday;
  using date_time::Tuesday;
  using date_time::Wednesday;
  using date_time::Thursday;
  using date_time::Friday;
  using date_time::Saturday;


  //! Exception that flags that a weekday number is incorrect
  struct BOOST_SYMBOL_VISIBLE bad_weekday : public std::out_of_range
  {
    bad_weekday() : std::out_of_range(std::string("Weekday is out of range 0..6")) {}
  };
  typedef CV::simple_exception_policy<unsigned short, 0, 6, bad_weekday> greg_weekday_policies;
  typedef CV::constrained_value<greg_weekday_policies> greg_weekday_rep;


  //! Represent a day within a week (range 0==Sun to 6==Sat)
  class BOOST_SYMBOL_VISIBLE greg_weekday : public greg_weekday_rep {
  public:
    typedef boost::date_time::weekdays weekday_enum;
    BOOST_CXX14_CONSTEXPR greg_weekday(value_type day_of_week_num) :
      greg_weekday_rep(day_of_week_num)
    {}

    BOOST_CXX14_CONSTEXPR value_type as_number() const {return value_;}
    BOOST_CXX14_CONSTEXPR weekday_enum as_enum() const {return static_cast<weekday_enum>(value_);}

    //! Return a 3 digit english string of the day of week (eg: Sun)
    const char* as_short_string() const
    {
      static const char* const short_weekday_names[]
        = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

      return short_weekday_names[value_];
    }

    //! Return a point to a long english string representing day of week
    const char* as_long_string() const
    {
      static const char* const long_weekday_names[]
        = {"Sunday","Monday","Tuesday","Wednesday", "Thursday", "Friday", "Saturday"};

      return long_weekday_names[value_];
    }


#ifndef BOOST_NO_STD_WSTRING

    //! Return a 3 digit english wchar_t string of the day of week (eg: Sun)
    const wchar_t* as_short_wstring() const
    {
      static const wchar_t* const w_short_weekday_names[]={L"Sun", L"Mon", L"Tue",
                                                           L"Wed", L"Thu", L"Fri", L"Sat"};
      return w_short_weekday_names[value_];
    }

    //! Return a point to a long english wchar_t string representing day of week
    const wchar_t* as_long_wstring()  const
    {
      static const wchar_t* const w_long_weekday_names[]= {L"Sunday",L"Monday",L"Tuesday",
                                                           L"Wednesday", L"Thursday",
                                                           L"Friday", L"Saturday"};
      return w_long_weekday_names[value_];
    }

#endif // BOOST_NO_STD_WSTRING


  };



} } //namespace gregorian



#endif

/* greg_weekday.hpp
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
*/