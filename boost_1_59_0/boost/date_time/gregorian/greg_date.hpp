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
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
*/