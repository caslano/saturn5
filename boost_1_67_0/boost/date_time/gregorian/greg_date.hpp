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