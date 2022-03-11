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