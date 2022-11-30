#ifndef DATE_TIME_TIME_SYSTEM_COUNTED_HPP
#define DATE_TIME_TIME_SYSTEM_COUNTED_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/time_defs.hpp>
#include <boost/date_time/special_defs.hpp>
#include <string>


namespace boost {
namespace date_time {

  //! Time representation that uses a single integer count
  template<class config>
  struct counted_time_rep
  {
    typedef typename config::int_type   int_type;
    typedef typename config::date_type  date_type;
    typedef typename config::impl_type  impl_type;
    typedef typename date_type::duration_type date_duration_type;
    typedef typename date_type::calendar_type calendar_type;
    typedef typename date_type::ymd_type ymd_type;
    typedef typename config::time_duration_type time_duration_type;
    typedef typename config::resolution_traits   resolution_traits;

    BOOST_CXX14_CONSTEXPR
    counted_time_rep(const date_type& d, const time_duration_type& time_of_day)
      : time_count_(1)
    {
      if(d.is_infinity() || d.is_not_a_date() || time_of_day.is_special()) {
        time_count_ = time_of_day.get_rep() + d.day_count();
        //std::cout << time_count_ << std::endl;
      }
      else {
        time_count_ = (d.day_number() * frac_sec_per_day()) + time_of_day.ticks();
      }
    }
    BOOST_CXX14_CONSTEXPR
    explicit counted_time_rep(int_type count) :
      time_count_(count)
    {}
    BOOST_CXX14_CONSTEXPR
    explicit counted_time_rep(impl_type count) :
      time_count_(count)
    {}
    BOOST_CXX14_CONSTEXPR
    date_type date() const
    {
      if(time_count_.is_special()) {
        return date_type(time_count_.as_special());
      }
      else {
        typename calendar_type::date_int_type dc = static_cast<typename calendar_type::date_int_type>(day_count());
        //std::cout << "time_rep here:" << dc << std::endl;
        ymd_type ymd = calendar_type::from_day_number(dc);
        return date_type(ymd);
      }
    }
    //int_type day_count() const
    BOOST_CXX14_CONSTEXPR
    unsigned long day_count() const
    {
      /* resolution_traits::as_number returns a boost::int64_t &
       * frac_sec_per_day is also a boost::int64_t so, naturally,
       * the division operation returns a boost::int64_t.
       * The static_cast to an unsigned long is ok (results in no data loss)
       * because frac_sec_per_day is either the number of
       * microseconds per day, or the number of nanoseconds per day.
       * Worst case scenario: resolution_traits::as_number returns the
       * maximum value an int64_t can hold and frac_sec_per_day
       * is microseconds per day (lowest possible value).
       * The division operation will then return a value of 106751991 -
       * easily fitting in an unsigned long.
       */
      return static_cast<unsigned long>(resolution_traits::as_number(time_count_) / frac_sec_per_day());
    }
    BOOST_CXX14_CONSTEXPR int_type time_count() const
    {
      return resolution_traits::as_number(time_count_);
    }
    BOOST_CXX14_CONSTEXPR int_type tod() const
    {
      return resolution_traits::as_number(time_count_) % frac_sec_per_day();
    }
    static BOOST_CXX14_CONSTEXPR int_type frac_sec_per_day()
    {
      int_type seconds_per_day = 60*60*24;
      int_type fractional_sec_per_sec(resolution_traits::res_adjust());
      return seconds_per_day*fractional_sec_per_sec;
    }
    BOOST_CXX14_CONSTEXPR bool is_pos_infinity()const
    {
      return impl_type::is_pos_inf(time_count_.as_number());
    }
    BOOST_CXX14_CONSTEXPR bool is_neg_infinity()const
    {
      return impl_type::is_neg_inf(time_count_.as_number());
    }
    BOOST_CXX14_CONSTEXPR bool is_not_a_date_time()const
    {
      return impl_type::is_not_a_number(time_count_.as_number());
    }
    BOOST_CXX14_CONSTEXPR bool is_special()const
    {
      return time_count_.is_special();
    }
    BOOST_CXX14_CONSTEXPR impl_type get_rep()const
    {
      return time_count_;
    }
  private:
    impl_type time_count_;
  };

  //! An unadjusted time system implementation.
  template<class time_rep>
  class counted_time_system
  {
   public:
    typedef time_rep time_rep_type;
    typedef typename time_rep_type::impl_type impl_type;
    typedef typename time_rep_type::time_duration_type time_duration_type;
    typedef typename time_duration_type::fractional_seconds_type fractional_seconds_type;
    typedef typename time_rep_type::date_type date_type;
    typedef typename time_rep_type::date_duration_type date_duration_type;


    template<class T> static BOOST_CXX14_CONSTEXPR void unused_var(const T&) {}

    static BOOST_CXX14_CONSTEXPR
    time_rep_type get_time_rep(const date_type& day,
                               const time_duration_type& tod,
                               date_time::dst_flags dst=not_dst)
    {
      unused_var(dst);
      return time_rep_type(day, tod);
    }

    static BOOST_CXX14_CONSTEXPR time_rep_type get_time_rep(special_values sv)
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

    static BOOST_CXX14_CONSTEXPR date_type
    get_date(const time_rep_type& val)
    {
      return val.date();
    }
    static BOOST_CXX14_CONSTEXPR
    time_duration_type get_time_of_day(const time_rep_type& val)
    {
      if(val.is_special()) {
        return time_duration_type(val.get_rep().as_special());
      }
      else{
        return time_duration_type(0,0,0,val.tod());
      }
    }
    static std::string zone_name(const time_rep_type&)
    {
      return "";
    }
    static BOOST_CXX14_CONSTEXPR bool is_equal(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return (lhs.time_count() == rhs.time_count());
    }
    static BOOST_CXX14_CONSTEXPR
    bool is_less(const time_rep_type& lhs, const time_rep_type& rhs)
    {
      return (lhs.time_count() < rhs.time_count());
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_days(const time_rep_type& base,
                           const date_duration_type& dd)
    {
      if(base.is_special() || dd.is_special()) {
        return(time_rep_type(base.get_rep() + dd.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() + (dd.days() * time_rep_type::frac_sec_per_day()));
      }
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_days(const time_rep_type& base,
                                const date_duration_type& dd)
    {
      if(base.is_special() || dd.is_special()) {
        return(time_rep_type(base.get_rep() - dd.get_rep()));
      }
      else{
        return time_rep_type(base.time_count() - (dd.days() * time_rep_type::frac_sec_per_day()));
      }
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type subtract_time_duration(const time_rep_type& base,
                                         const time_duration_type& td)
    {
      if(base.is_special() || td.is_special()) {
        return(time_rep_type(base.get_rep() - td.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() - td.ticks());
      }
    }
    static BOOST_CXX14_CONSTEXPR
    time_rep_type add_time_duration(const time_rep_type& base,
                                    time_duration_type td)
    {
      if(base.is_special() || td.is_special()) {
        return(time_rep_type(base.get_rep() + td.get_rep()));
      }
      else {
        return time_rep_type(base.time_count() + td.ticks());
      }
    }
    static BOOST_CXX14_CONSTEXPR
    time_duration_type subtract_times(const time_rep_type& lhs,
                                      const time_rep_type& rhs)
    {
      if(lhs.is_special() || rhs.is_special()) {
        return(time_duration_type(
          impl_type::to_special((lhs.get_rep() - rhs.get_rep()).as_number())));
      }
      else {
        fractional_seconds_type fs = lhs.time_count() - rhs.time_count();
        return time_duration_type(0,0,0,fs);
      }
    }

  };


} } //namespace date_time



#endif


/* time_system_counted.hpp
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
*/