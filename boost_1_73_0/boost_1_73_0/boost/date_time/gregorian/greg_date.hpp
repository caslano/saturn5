#ifndef GREG_DATE_HPP___
#define GREG_DATE_HPP___

/* Copyright (c) 2002,2003, 2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date$
 */

#include <boost/throw_exception.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/date.hpp>
#include <boost/date_time/special_defs.hpp>
#include <boost/date_time/gregorian/greg_calendar.hpp>
#include <boost/date_time/gregorian/greg_duration.hpp>

namespace boost {
namespace gregorian {

  //bring special enum values into the namespace
  using date_time::special_values;
  using date_time::not_special;
  using date_time::neg_infin;
  using date_time::pos_infin;
  using date_time::not_a_date_time;
  using date_time::max_date_time;
  using date_time::min_date_time;

  //! A date type based on gregorian_calendar
  /*! This class is the primary interface for programming with
      greogorian dates.  The is a lightweight type that can be
      freely passed by value.  All comparison operators are
      supported.
      \ingroup date_basics
  */
  class BOOST_SYMBOL_VISIBLE date : public date_time::date<date, gregorian_calendar, date_duration>
  {
   public:
    typedef gregorian_calendar::year_type year_type;
    typedef gregorian_calendar::month_type month_type;
    typedef gregorian_calendar::day_type day_type;
    typedef gregorian_calendar::day_of_year_type day_of_year_type;
    typedef gregorian_calendar::ymd_type ymd_type;
    typedef gregorian_calendar::date_rep_type date_rep_type;
    typedef gregorian_calendar::date_int_type date_int_type;
    typedef date_duration  duration_type;
#if !defined(DATE_TIME_NO_DEFAULT_CONSTRUCTOR)
    //! Default constructor constructs with not_a_date_time
    BOOST_CXX14_CONSTEXPR date():
      date_time::date<date, gregorian_calendar, date_duration>(date_rep_type::from_special(not_a_date_time))
    {}
#endif // DATE_TIME_NO_DEFAULT_CONSTRUCTOR
    //! Main constructor with year, month, day
    BOOST_CXX14_CONSTEXPR date(year_type y, month_type m, day_type d)
      : date_time::date<date, gregorian_calendar, date_duration>(y, m, d)
    {
      if (gregorian_calendar::end_of_month_day(y, m) < d) {
        boost::throw_exception(bad_day_of_month(std::string("Day of month is not valid for year")));
      }
    }
    //! Constructor from a ymd_type structure
    BOOST_CXX14_CONSTEXPR explicit date(const ymd_type& ymd)
      : date_time::date<date, gregorian_calendar, date_duration>(ymd)
    {}
    //! Needed copy constructor
    BOOST_CXX14_CONSTEXPR explicit date(const date_int_type& rhs):
      date_time::date<date,gregorian_calendar, date_duration>(rhs)
    {}
    //! Needed copy constructor
    BOOST_CXX14_CONSTEXPR explicit date(date_rep_type rhs):
      date_time::date<date,gregorian_calendar, date_duration>(rhs)
    {}
    //! Constructor for infinities, not a date, max and min date
    BOOST_CXX14_CONSTEXPR explicit date(special_values sv):
      date_time::date<date, gregorian_calendar, date_duration>(date_rep_type::from_special(sv))
    {
      if (sv == min_date_time)
      {
        *this = date(1400, 1, 1);
      }
      if (sv == max_date_time)
      {
        *this = date(9999, 12, 31);
      }

    }
    //!Return the Julian Day number for the date.
    BOOST_CXX14_CONSTEXPR date_int_type julian_day() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::julian_day_number(ymd);
    }
    //!Return the day of year 1..365 or 1..366 (for leap year)
    BOOST_CXX14_CONSTEXPR day_of_year_type day_of_year() const
    {
      date start_of_year(year(), 1, 1);
      unsigned short doy = static_cast<unsigned short>((*this-start_of_year).days() + 1);
      return day_of_year_type(doy);
    }
    //!Return the Modified Julian Day number for the date.
    BOOST_CXX14_CONSTEXPR date_int_type modjulian_day() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::modjulian_day_number(ymd);
    }
    //!Return the iso 8601 week number 1..53
    BOOST_CXX14_CONSTEXPR int week_number() const
    {
      ymd_type ymd = year_month_day();
      return gregorian_calendar::week_number(ymd);
    }
    //! Return the day number from the calendar
    BOOST_CXX14_CONSTEXPR date_int_type day_number() const
    {
      return days_;
    }
    //! Return the last day of the current month
    BOOST_CXX14_CONSTEXPR date end_of_month() const
    {
      ymd_type ymd = year_month_day();
      unsigned short eom_day =  gregorian_calendar::end_of_month_day(ymd.year, ymd.month);
      return date(ymd.year, ymd.month, eom_day);
    }

    friend BOOST_CXX14_CONSTEXPR
    bool operator==(const date& lhs, const date& rhs);

   private:

  };

  inline BOOST_CXX14_CONSTEXPR
  bool operator==(const date& lhs, const date& rhs)
  {
    return lhs.days_ == rhs.days_;
  }


} } //namespace gregorian



#endif

/* greg_date.hpp
5sYtGEzjVlaQUUni1eGoVsaFoCj02WqyJOXwXpf8YrLUsLXlPFvsCCKtXtGsKlKYQ1ogF2dIfJOqNFaFlbeJqK34LNuUf6dkG99jylJ4RY12SN2wQVNptGnSdXf8cXA1puv2aNTuj29o8IHa/Ruv71O3fwFsaFgtSD3mhTLwoiC9yBOt4h3jf2uni2D8kc6vRr3BcDz5OB4P21d48JIaL6hd3TGsXzWokegp153eBC/fBs/xgN9NlDSriVElVxj/ACYDfeFH6rc/d8SB0tsT1LMkfo9figdEKisEnJY6knwagCjnWWwLWBYrqyq86Q+GYTcUQToT/9BplFSxol/YvoPi/FdhTUUZnu+7dcSf0LM5QJIAK/suNSnJ0jua6nIhzf3xe2vxohOej7rDcXfQF0OJMkgn5ZpIwkdV+L7jwnNI8FfWWprWe+CW6qS5Fn0y1CNzbLt2KdOSdN0nZHIl7zVssqo5N/IiQ1O4pAVCcMdumhOGjW1adBHDb6qSbBlQd4ZGw9MS0QOSVs473Nz4ptFgM12Ykn6vVLGy5oyGMZg2Svk4/6ROUGiqPM8KdgB9yEIi19G9VTNV0MqGOUKZwKlNiAF94PbOFqpW1nTUxA6B6eIqYhIQ6rEsJKWqXGbFPRUZGvUEfZYHFHLe
*/