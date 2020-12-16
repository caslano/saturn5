#ifndef POSIX_TIME_CONFIG_HPP___
#define POSIX_TIME_CONFIG_HPP___

/* Copyright (c) 2002,2003,2005,2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <cstdlib> //for MCW 7.2 std::abs(long long)
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/date_time/time_duration.hpp>
#include <boost/date_time/time_resolution_traits.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/wrapping_int.hpp>
#include <boost/date_time/compiler_config.hpp>

namespace boost {
namespace posix_time {


#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
  // set up conditional test compilations
#define BOOST_DATE_TIME_HAS_NANOSECONDS
  typedef date_time::time_resolution_traits<boost::date_time::time_resolution_traits_adapted64_impl, boost::date_time::nano,
    1000000000, 9 > time_res_traits;
#else
  // set up conditional test compilations
#undef  BOOST_DATE_TIME_HAS_NANOSECONDS
  typedef date_time::time_resolution_traits<
    boost::date_time::time_resolution_traits_adapted64_impl, boost::date_time::micro,
                                            1000000, 6 > time_res_traits;

#endif


  //! Base time duration type
  /*! \ingroup time_basics
   */
  class BOOST_SYMBOL_VISIBLE time_duration :
    public date_time::time_duration<time_duration, time_res_traits>
  {
  public:
    typedef time_res_traits rep_type;
    typedef time_res_traits::day_type day_type;
    typedef time_res_traits::hour_type hour_type;
    typedef time_res_traits::min_type min_type;
    typedef time_res_traits::sec_type sec_type;
    typedef time_res_traits::fractional_seconds_type fractional_seconds_type;
    typedef time_res_traits::tick_type tick_type;
    typedef time_res_traits::impl_type impl_type;
    BOOST_CXX14_CONSTEXPR time_duration(hour_type hour,
                                        min_type min,
                                        sec_type sec,
                                        fractional_seconds_type fs=0) :
      date_time::time_duration<time_duration, time_res_traits>(hour,min,sec,fs)
    {}
   BOOST_CXX14_CONSTEXPR time_duration() :
      date_time::time_duration<time_duration, time_res_traits>(0,0,0)
    {}
    //! Construct from special_values
    BOOST_CXX14_CONSTEXPR time_duration(boost::date_time::special_values sv) :
      date_time::time_duration<time_duration, time_res_traits>(sv)
    {}
    //Give duration access to ticks constructor -- hide from users
    friend class date_time::time_duration<time_duration, time_res_traits>;
  protected:
    BOOST_CXX14_CONSTEXPR explicit time_duration(impl_type tick_count) :
      date_time::time_duration<time_duration, time_res_traits>(tick_count)
    {}
  };

#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG

  //! Simple implementation for the time rep
  struct simple_time_rep
  {
    typedef gregorian::date      date_type;
    typedef time_duration        time_duration_type;
    BOOST_CXX14_CONSTEXPR simple_time_rep(date_type d, time_duration_type tod) :
      day(d),
      time_of_day(tod)
    {
      // make sure we have sane values for date & time
      if(!day.is_special() && !time_of_day.is_special()){
        if(time_of_day >= time_duration_type(24,0,0)) {
          while(time_of_day >= time_duration_type(24,0,0)) {
            day += date_type::duration_type(1);
            time_of_day -= time_duration_type(24,0,0);
          }
        }
        else if(time_of_day.is_negative()) {
          while(time_of_day.is_negative()) {
            day -= date_type::duration_type(1);
            time_of_day += time_duration_type(24,0,0);
          }
        }
      }
    }
    date_type day;
    time_duration_type time_of_day;
    BOOST_CXX14_CONSTEXPR bool is_special()const
    {
      return(is_pos_infinity() || is_neg_infinity() || is_not_a_date_time());
    }
    BOOST_CXX14_CONSTEXPR bool is_pos_infinity()const
    {
      return(day.is_pos_infinity() || time_of_day.is_pos_infinity());
    }
    BOOST_CXX14_CONSTEXPR bool is_neg_infinity()const
    {
      return(day.is_neg_infinity() || time_of_day.is_neg_infinity());
    }
    BOOST_CXX14_CONSTEXPR bool is_not_a_date_time()const
    {
      return(day.is_not_a_date() || time_of_day.is_not_a_date_time());
    }
  };

  class BOOST_SYMBOL_VISIBLE posix_time_system_config
  {
   public:
    typedef simple_time_rep time_rep_type;
    typedef gregorian::date date_type;
    typedef gregorian::date_duration date_duration_type;
    typedef time_duration time_duration_type;
    typedef time_res_traits::tick_type int_type;
    typedef time_res_traits resolution_traits;
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT)) //help bad compilers
#else
    BOOST_STATIC_CONSTANT(boost::int64_t, tick_per_second = 1000000000);
#endif
  };

#else

  class millisec_posix_time_system_config
  {
   public:
    typedef boost::int64_t time_rep_type;
    //typedef time_res_traits::tick_type time_rep_type;
    typedef gregorian::date date_type;
    typedef gregorian::date_duration date_duration_type;
    typedef time_duration time_duration_type;
    typedef time_res_traits::tick_type int_type;
    typedef time_res_traits::impl_type impl_type;
    typedef time_res_traits resolution_traits;
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT)) //help bad compilers
#else
    BOOST_STATIC_CONSTANT(boost::int64_t, tick_per_second = 1000000);
#endif
  };

#endif

} }//namespace posix_time


#endif



/* posix_time_config.hpp
E9tw1TiRlyRlF55wID7pAziVdXD+xl+njt+UXXVvnaUjHhwOf7Cm+sNxpcuO1DVDfHTHr6rCUIW6J+i6YV03rOuGqW54ddmO47FumOsGdN0A1B2u60Z03YiuG6G6kdVlT+q6Ea5bqetWQt0f31Nn7donUqp+Sd9/PUdvCqJmU3BbQD3RxWSnmXtypc6HVxisbAnQ0t5hPS9XK7u0lLDb04/S9PIum7eDEXj212EyablqqUwABA49V6rnSnquZvNz2BilVwdy76SIEe+V4L0v3lkxE6FoDQE+bwEV+Rkq8TNUgGGlNnRq97riZS9+Z6ghUAMVUtXQM8kRlTxIZUEJP/fzli8fJezbaqLU94NicZBYxtEfB0nX7BLdJOxYrjJYtGYnrq3a03rIdyAFngSZG3joyL6M00sQc1xcD85gXUCtcTHglCClsH/oLJWXqss9Xw7j10/jlxwkoLuUeuTzQ3breLyz7I6nxllPOvpzMWUwVng88juNR/EOQ0u+83gMaC0VpdasePntET3qhMkIQERivfSG5KgS+84ASYQnS/RPu3aW8E/7+eF2/zTcQSb7F7NbfjJbY3dYe1w6rB2V77BmzjLF0xctHGvlZw6Zu9pgPNTyTue9o+5qNF86MX1UBJkOyNnbAxZJH4DFkLyexOgXlk4m1tVJ1kFQoRT5LJ6TfQ6BtCEQx4h6bQaIzwCJMhD8tvbNPhcDooQ0efWoEqVJ8Z+j/+WwI5kV0f5eeSUHFJapEQe/JBAR/OwqIi5DpVba6yqQJEZIKRlbwGALELYACKSh8ogS+rS+w+3n56ABbSfnaVc7SYRSK7kQ7bdWpAOYS28ROG0BAalIYQsCzGjrKvFRS5LSVzq2np1+OG94IkrJsQxPOc7BYyfdR5stAHL/qIbKZcNx+s6Otxfo2IxF0tHJRY/d2T6yb86UOoRKcAtruyg3sOH4q92qkcz5OB7k6uM4JqDgIogRfpoKKUxUQASmr8TnQX05tqP5r9cj/eaA9nJ97F2x0mqbtgk+ba2KOe57oIq5DFQxrUYV88RE1Bre6VWpXnmMf83BqD5BAD4PAvAjgAvzASzVABYAgIAEcJIGMIPPMwN7GrqG60sNHn5Cn1mffZQ5yAf/oawN59co1zWuoxpnvL3NXoPUTkjqCE3qWU+Q2kmS+sL+SGoXADQ33Vvi1GDVyltEnjGuRsG4CgIGnoU5lYiI8FsErGZOxtXIALuoJy+5URhARXKTMICK5Gab4ZbtogI2JTfKZK9JbpLJPpPcLIyrxAG2r8ZUy2LavhrT9tVYAftqGCPzudtXZRl3+6q9DE7I74mz5EL2hcP47eKXQ4cSpsBnAz6m37b0/R+PwsAnJ/WXVG52bEPXvTrvMpn3ynFFJZ/Af8aZahlbETlQ1V8Ci8qtqMv9650f/ciTReTlksMGyMtlJMVwObF3TnY+MIF1Y0YBVup+JoTrH40qYTtm8dYsc+32frSxUUSIY5zZWImsKIL/pkMd8T841eA/lJZAkHwxJi/Z107N35UkzJaVfuQe6XEMOunR9MT5dLS81NTEwXzjWEPdVXHIQ0PnQTos5nci+SGYodSHoFSIZ3FMT1WyNR+uY0Qo+AwIwzEO2Z7UCC99X+5mn1B6xqTt/bsXEtK9PzyHYPtFV/yuLn8oxLmvmPl9xxQdCo6obp5uR9Val9/rUZ18ypHU6zbE1eFSe929v0cxEXC8GvZNqXGio6+aRDpOOmEA1w+o6edNc/NROIQdM1MXP0C9wZ0qeeFNluKs+W29QhjXBbPmJTBrXmFmzc+PgVkTjQDQ7xhjJABPBkbqUBgRYTEiXn9zG7PqYsgC+yGhbcpOEgXrJhueHgs=
*/