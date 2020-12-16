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
TvAt/sAofmWep7rJ248dM7rO28/qMR/nanSgR0gY5dGw320QJhgmS6En6zEk+fGHa6negUe7sUDK2gnk9ofrUaf94Xpkd8yxxYgHy96Cs/jh+qwYTB4rQz7C+jD3cYQXyolX8/vwO9H3YVGu78P6t1r/Qaz3dKv2VsexUO6x/Bu0D5S/zPlaN3oxRsw3HgvyFWqkK1Qeo3hKYYrSZaIopfEIXZCLllYxmbAK7Mor1IgnaPHfgZlfoXIA/cUANVdb5vLJTrjCY0Q82E69IQIae7c8CoNeRjl7ufmt9OG1DaW4toVfxPcrVLfxkrHTl0bxyxJrLkDDbuUFSF8JR3gf1SIKxzY08uH7sX6uxxSq7grU50Oj+fFRH1Ro37FdgOhf2slOrhj1HVeM+o7tAjRVjGtH91ON7uNRH4qVvaRUhnxI+LEu1+FHG+WErvkl9CF0H8fQ/YNQH+r6440OQqG0me+R/z61Lj/NL9PrNUH7sxtdB+3HNR+Be2o/AiO9E6QYqSIKZ8xppGGpD44QphyvugL1OU6iH5bKNVQcdDuAkLJ2spODj8CM5vIEGz+72MZ+JkExGkat0paj1hnyL4c3yok+Zchn/dd6BAnpQinoan79fcOT4brhybA21Mfi31schUJ5HEofgYpL/EGn8hK/qXliHXcrn1iPUjnC+4zzLgr5PoFwJIw1fz/X85kpVN0Vu/ooPdVt2krpGqrmX/A/JV3zgO8TmsNTtGwV2hjfpxYjmlT3Fvi8+gmSS4c8b5+fRoa8DyHnqeIIOpQCuuYX6zfwvWnguzqU+PYWN4Sq5rvXNsjqls+X4/x8OebDnSY5x57OvCK40pKefoNcRSur6Kt+sPPny3KlLj9fLornSwXQX0yM52qrXD7ZCb5Wl9uJZxWcKDT2CnoUBr2McvZy88vrw7EGypuf/9/YPWC23l2Hncq760XN1Wdae/WZoVwT7jhPnxfWzOdMFxlo/Qe9p6ZQdVegvv3y8sxK6Rqq+HfIs3aykyvmhJcVc8JLu/qsLEa8BOAtOI/nhFGs7F0pkSHvQ8h6HA8vIygndc3vqm+g7iKk7p/E0hXIW90Qq3KE228f4TZ+CA5rPwRYpW+9oZ90K2/o866tIZW7EbRDYi7WofVfcj4xhaq7AvXtJ3fnVkrXUMU/QJ21k50cfAhOaS5PsPGzC23sQ3BmMeJdGd6Cb6ItDDRj9q6U5W4L+NIgswHlQ6Hc/Kb88I76TTzK+gehtvoMeKOjUNvaUdbgH4yydBM+yjfhI94BbXXpyHKqTQ/QkqQj/ZiulfIfd0JbVkcFuyeXuyp0T4aZ3ZM90nvC1qGBRC2xjTdYqHWnXbUuv41ehd7/KkX/N7/EvuGit712hvp5uz3fVD48SXGzFP5+u1V3v5i2P/bH/tgf+6N2vRq/hHr56Udcr+ajMQbpzevV81sa16t9Rj5esr7S2qp1H7a5lP/QSbh83a9bvu6XDwoooYNwFUFaW0Uo17GtdTfDXOdwEwQUNgzkUa5hDs3hk/+yqHjEYCkeMVofFNL5nNzSuo6HzJXjkuNeYBT+DKGvUzd5m94cGIVD/dRXV+FtAIwoGurDiFBAC6sRczg1BatL4UP9Mczlx4f6Ur0Dj0YBpKydQG4f6o/67UN92GiUA9/egpVzCMlaADkc6qOY2bPtX96HOBtx2QvoQqk9wI4EJf9lUTRiGTW8Sbw21Gt6VvYWR6FQzlCto5yOPgLxRKOz3byQrQW+eC37SmvL2UwkS/kPnYTr2v26de3i0sWKcqDNeD1vc9ZOruS/LXD/2boTXrquYGSuURgkAOU+Oh2LEv7LouiiN77mLd4LX+RuvJTsoCmN4l02NRemee0=
*/