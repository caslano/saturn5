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
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
*/