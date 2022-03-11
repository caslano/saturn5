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