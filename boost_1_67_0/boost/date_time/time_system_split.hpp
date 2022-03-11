#ifndef DATE_TIME_TIME_SYSTEM_SPLIT_HPP
#define DATE_TIME_TIME_SYSTEM_SPLIT_HPP

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <string>
#include <boost/cstdint.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/wrapping_int.hpp>

namespace boost {
namespace date_time {

  //! An unadjusted time system implementation.
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT))
  template<typename config, boost::int32_t ticks_per_second>
#else
  template<typename config>
#endif
  class split_timedate_system
  {
   public:
    typedef typename config::time_rep_type time_rep_type;
    typedef typename config::date_type     date_type;
    typedef typename config::time_duration_type time_duration_type;
    typedef typename config::date_duration_type date_duration_type;
    typedef typename config::int_type int_type;
    typedef typename config::resolution_traits   resolution_traits;

    //86400 is number of seconds in a day...
#if (defined(BOOST_DATE_TIME_NO_MEMBER_INIT))
    typedef date_time::wrapping_int<int_type, INT64_C(86400) * ticks_per_second > wrap_int_type;
#else
   private:
     BOOST_STATIC_CONSTANT(int_type, ticks_per_day = INT64_C(86400) * config::tick_per_second);
   public:
# if BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0X581) )
    typedef date_time::wrapping_int< split_timedate_system::int_type, split_timedate_system::ticks_per_day> wrap_int_type;
# else
    typedef date_time::wrapping_int<int_type, ticks_per_day> wrap_int_type;
#endif
#endif

    static
    BOOST_CXX14_CONSTEXPR
    time_rep_type get_time_rep(special_values sv)
    {
      switch (sv) {
      case not_a_date_time:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));
      case pos_infin:
        return time_rep_type(date_type(pos_infin),
                             time_duration_type(pos_infin));
      case neg_infin:
        return time_rep_type(date_type(neg_infin),
                             time_duration_type(neg_infin));
      case max_date_time: {
        time_duration_type td = time_duration_type(24,0,0,0) - time_duration_type(0,0,0,1);
        return time_rep_type(date_type(max_date_time), td);
      }
      case min_date_time:
        return time_rep_type(date_type(min_date_time), time_duration_type(0,0,0,0));

      default:
        return time_rep_type(date_type(not_a_date_time),
                             time_duration_type(not_a_date_time));

      }

    }

    static
    BOOST_CXX14_CONSTEXPR
    time_rep_type get_time_rep(const date_type& day,
                               const time_duration_type& tod,
                               date_time::dst_flags /* dst */ = not_dst)
    {
      if(day.is_special() || tod.is_special()) {
        if(day.is_not_a_date() || tod.is_not_a_date_time()) {
          return time_rep_type(date_type(not_a_date_time),
                               time_duration_type(not_a_date_time));
        }
        else if(day.is_pos_infinity()) {
          if(tod.is_neg_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(day, time_duration_type(pos_infin));
          }
        }
        else if(day.is_neg_infinity()) {
          if(tod.is_pos_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(day, time_duration_type(neg_infin));
          }
        }
        else if(tod.is_pos_infinity()) {
          if(day.is_neg_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(date_type(pos_infin), tod);
          }
        }
        else if(tod.is_neg_infinity()) {
          if(day.is_pos_infinity()) {
            return time_rep_type(date_type(not_a_date_time),
                                 time_duration_type(not_a_date_time));
          }
          else {
            return time_rep_type(date_type(neg_infin), tod);
          }
        }
      }
      return time_rep_type(day, tod);
    }
    static BOOST_CONSTEXPR date_type get_date(const time_rep_type& val)
    {
      return date_type(val.day);
    }
    static BOOST_CONSTEXPR time_duration_type get_time_of_day(const time_rep_type& val)
    {
      return time_duration_type(val.time_of_day);
    }
    static std::string zone_name(const time_rep_type&)
    {
      return std::string();
    }
    static BOOST_CONSTEXPR
    bool is_equal(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return ((lhs.day == rhs.day) && (lhs.time_of_day == rhs.time_of_day));
    }
    static BOOST_CXX14_CONSTEXPR
    bool is_less(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      if (lhs.day < rhs.day) return true;
      if (lhs.day > rhs.day) return false;
      return (lhs.time_of_day < rhs.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_days(const time_rep_type& base,
                           const date_duration_type& dd)
    {
      return time_rep_type(base.day+dd, base.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_days(const time_rep_type& base,
                                const date_duration_type& dd)
    {
      return split_timedate_system::get_time_rep(base.day-dd, base.time_of_day);
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_time_duration(const time_rep_type& base,
                                         const time_duration_type& td)
    {
      if(base.day.is_special() || td.is_special())
      {
        return split_timedate_system::get_time_rep(base.day, -td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return add_time_duration(base,td1);
      }

      wrap_int_type  day_offset(base.time_of_day.ticks());
      date_duration_type day_overflow(static_cast<typename date_duration_type::duration_rep_type>(day_offset.subtract(td.ticks())));

      return time_rep_type(base.day-day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_time_duration(const time_rep_type& base,
                                    time_duration_type td)
    {
      if(base.day.is_special() || td.is_special()) {
        return split_timedate_system::get_time_rep(base.day, td);
      }
      if (td.is_negative()) {
        time_duration_type td1 = td.invert_sign();
        return subtract_time_duration(base,td1);
      }

      wrap_int_type day_offset(base.time_of_day.ticks());
      date_duration_type day_overflow(static_cast< typename date_duration_type::duration_rep_type >(day_offset.add(td.ticks())));

      return time_rep_type(base.day+day_overflow,
                           time_duration_type(0,0,0,day_offset.as_int()));
    }
    static BOOST_CXX14_CONSTEXPR
    time_duration_type subtract_times(const time_rep_type& lhs,
                                      const time_rep_type& rhs)
    {
      date_duration_type dd = lhs.day - rhs.day;
      if (BOOST_LIKELY(!dd.is_special())) {
        time_duration_type td(dd.days()*24,0,0); // days * 24 hours
        time_duration_type td2 = lhs.time_of_day - rhs.time_of_day;
        return td+td2;
      } else {
        time_duration_type td(dd.as_special());
        time_duration_type td2 = lhs.time_of_day - rhs.time_of_day;
        return td+td2;
      }
    }

  };

} } //namespace date_time


#endif

/* time_system_split.hpp
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
*/