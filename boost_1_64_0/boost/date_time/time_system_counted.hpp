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
8dkzYfJOo2aZAVtGsEy8L040wx5ThMFIoFtlfussMD5hncFek7sw1DkAxcjKzPMpSPWSQqC6YW6pvpIlJ8yxnzDfP3mPWPNTDrPGbCbxu5sWSq9NkGYSN8mF0tY0YSbRW3qYLK2ZJb1EPwxnpqIbW8Vg8WCt+im2Vf+aq55qVH2crHp7WfWuVHXk7e2y4l9044rfDBUHmAmVCdX4LxQf8sRQ20boPfVwu0ofFkeV/nOlrPR4WekhqXb0vlNWuxtUO7pVSgwYRNh/drarekuu+gPjZdVvlFVflBJJ7ztkxW/s2rz0hvMUi8c14v+980E7T0GkWtDJIBUteFQPSEcbHpA0VRs1uZVUC0RqYP/OK7Ex42gl1mE8rsTWPia1Xbp04sNF22wGPZdBT5qIoLMV0PVapB9mVYk7j9O35PRvj8P0JWp6XjdHatmUnIvVcJnzQ5zzczdRzl8SEr8vFjn71Zz9lLOT7miitvftWYapG28tcPV/uJH1TZVY/d5cfbkWv5xh6hhmDsEcSjBmj/6mlXm+of5KMpbM1L3KeDgL3Cil3bGye/VLIlcPV4tmw3SugANeXIkkSMQRuKN7wScN8kS0X4GnYq7nYt4by4ZSajFwEI2K8chi1LPfagPIlxUYzRW4FbKjCKpA3cdcgXxRgXylAmO5AiV2FbiMK4Bn6BuX3KQKqMRwduFTq5lnFcl9QnJV8zLmZ+W8dYn+7qx/pAP92S692h3Gjbg6zL8JqL4rHdXKCOBNh0RahtC7Ye8Y7OfSeIgyVO+VBKmOaBMoxE+OYU2NPN8q82U3aZvhqv3aZnCzKuYvo6nD+cZih3tsYZO2GULmz0KHL6iwsuamQw3TISZ3xW7WrhfLDb/R0rg2Uum2hTdArhhFmK8bhZgveYQxJ0AG28pgpzHYMgKbzmAqeyQ/KdE2TpTAiR6jRP0pkXlEf1u3X6xQ4I5R4GSH4kRplMhFifrrs1bwk91hEFqEEyVuGrLR+dXNMvjqWZA98hCK4G91g0xOpROgkE+5ZmdxzcpGY83ufNgYrMtFLgHOCffF9OHDVRjT+qO5f7b9+cwOTenP2Up/zlb68z81a3/O5v6sLjcm6MdZK7nhRTaO2dzlvhxJpD23HEnb4yHJdFbPi44uOjdTWVXP38fZLORs4qnt7HlQ9txmp7916/2XDHP/Kw3++KF1w72lsL6x2c0ayvX/9Aaq/5kjsf55D0bsZl3BYKsYrAeBJRhgsisNY7h7GW4zUXXXgn3sZuXhvHkVq7Szb6DdLPPy+6g4lDlracupr6ux/azruNyOXO4EKnf4gkb2sw6tSZTUmnOIkT32tkZ3rQL2W0q86pEb+MqWkt3OTIADzVtKo4xtpHy1QF3KF7EBv9wAK+PubZ8dkmMSkyP1r0SOncSuPz8gz0f8B+8U299/lB55spsdB07K95ZnK2ach6VEmnFe1u3VcPqK+bmauPTRj3oTadhJx77vgWjLlR9Pbm8IczaZdGym3e8NqFZKpcbDIIPbH5DtZ6P4dmlrsmdtAt5H2JjhDtct4S4h/OftE/+Z8yLxf9+C/286/gkG/hkHjH+E/Wsbxf71/CR7+9d3fjsg+9cxZP/aWqrzyCkXawuN06mS3voRReHhIrxBiPv30ebfd/rmXx6eD3mFN/9e7k2bf9N625jD+tmkSB7I3J6oh5N48ew7PHj76eCZUh39s74KipMtoD21AJlVtk4uVnjyFhaCw/4hHSpNnfwu50ifNMZAFCq9dFe/AcVfsY8OiOrxLkt8GsZPN+LdFe0FDv7gyV+wiBSAUSp0pQ4RVzHAgNj8S4NxLrc8B/+xRWL3fVok+huxSNRMSt76sjgTzve6VCo=
*/