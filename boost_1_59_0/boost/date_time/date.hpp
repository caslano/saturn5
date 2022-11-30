#ifndef DATE_TIME_DATE_HPP___
#define DATE_TIME_DATE_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include <boost/operators.hpp>
#include <boost/date_time/compiler_config.hpp>
#include <boost/date_time/year_month_day.hpp>
#include <boost/date_time/special_defs.hpp>

namespace boost {
namespace date_time {

  //!Representation of timepoint at the one day level resolution.
  /*!
    The date template represents an interface shell for a date class
    that is based on a year-month-day system such as the gregorian
    or iso systems.  It provides basic operations to enable calculation
    and comparisons.

    <b>Theory</b>

    This date representation fundamentally departs from the C tm struct
    approach.  The goal for this type is to provide efficient date
    operations (add, subtract) and storage (minimize space to represent)
    in a concrete class.  Thus, the date uses a count internally to
    represent a particular date.  The calendar parameter defines
    the policies for converting the the year-month-day and internal
    counted form here.  Applications that need to perform heavy
    formatting of the same date repeatedly will perform better
    by using the year-month-day representation.

    Internally the date uses a day number to represent the date.
    This is a monotonic time representation. This representation
    allows for fast comparison as well as simplifying
    the creation of writing numeric operations.  Essentially, the
    internal day number is like adjusted julian day.  The adjustment
    is determined by the Epoch date which is represented as day 1 of
    the calendar.  Day 0 is reserved for negative infinity so that
    any actual date is automatically greater than negative infinity.
    When a date is constructed from a date or formatted for output,
    the appropriate conversions are applied to create the year, month,
    day representations.
  */


  template<class T, class calendar, class duration_type_>
  class BOOST_SYMBOL_VISIBLE date : private
       boost::less_than_comparable<T
     , boost::equality_comparable<T
    > >
  {
  public:
    typedef T date_type;
    typedef calendar calendar_type;
    typedef typename calendar::date_traits_type traits_type;
    typedef duration_type_ duration_type;
    typedef typename calendar::year_type year_type;
    typedef typename calendar::month_type month_type;
    typedef typename calendar::day_type day_type;
    typedef typename calendar::ymd_type ymd_type;
    typedef typename calendar::date_rep_type date_rep_type;
    typedef typename calendar::date_int_type date_int_type;
    typedef typename calendar::day_of_week_type day_of_week_type;
    BOOST_CXX14_CONSTEXPR date(year_type y, month_type m, day_type d)
      : days_(calendar::day_number(ymd_type(y, m, d)))
    {}
    BOOST_CXX14_CONSTEXPR date(const ymd_type& ymd)
      : days_(calendar::day_number(ymd))
    {}
    //let the compiler write copy, assignment, and destructor
    BOOST_CXX14_CONSTEXPR year_type        year() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.year;
    }
    BOOST_CXX14_CONSTEXPR month_type       month() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.month;
    }
    BOOST_CXX14_CONSTEXPR day_type         day() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return ymd.day;
    }
    BOOST_CXX14_CONSTEXPR day_of_week_type day_of_week() const
    {
      ymd_type ymd = calendar::from_day_number(days_);
      return calendar::day_of_week(ymd);
    }
    BOOST_CXX14_CONSTEXPR ymd_type         year_month_day() const
    {
      return calendar::from_day_number(days_);
    }
    BOOST_CONSTEXPR bool operator<(const date_type& rhs)  const
    {
      return days_ < rhs.days_;
    }
    BOOST_CONSTEXPR bool operator==(const date_type& rhs) const
    {
      return days_ == rhs.days_;
    }
    //! check to see if date is a special value
    BOOST_CONSTEXPR bool is_special()const
    {
      return(is_not_a_date() || is_infinity());
    }
    //! check to see if date is not a value
    BOOST_CONSTEXPR bool is_not_a_date()  const
    {
      return traits_type::is_not_a_number(days_);
    }
    //! check to see if date is one of the infinity values
    BOOST_CONSTEXPR bool is_infinity()  const
    {
      return traits_type::is_inf(days_);
    }
    //! check to see if date is greater than all possible dates
    BOOST_CONSTEXPR bool is_pos_infinity()  const
    {
      return traits_type::is_pos_inf(days_);
    }
    //! check to see if date is greater than all possible dates
    BOOST_CONSTEXPR bool is_neg_infinity()  const
    {
      return traits_type::is_neg_inf(days_);
    }
    //! return as a special value or a not_special if a normal date
    BOOST_CXX14_CONSTEXPR special_values as_special()  const
    {
      return traits_type::to_special(days_);
    }
    BOOST_CXX14_CONSTEXPR duration_type operator-(const date_type& d) const
    {
      if (!this->is_special() && !d.is_special())
      {
        // The duration underlying type may be wider than the date underlying type.
        // Thus we calculate the difference in terms of two durations from some common fixed base date.
        typedef typename duration_type::duration_rep_type duration_rep_type;
        return duration_type(static_cast< duration_rep_type >(days_) - static_cast< duration_rep_type >(d.days_));
      }
      else
      {
        // In this case the difference will be a special value, too
        date_rep_type val = date_rep_type(days_) - date_rep_type(d.days_);
        return duration_type(val.as_special());
      }
    }

    BOOST_CXX14_CONSTEXPR date_type operator-(const duration_type& dd) const
    {
      if(dd.is_special())
      {
        return date_type(date_rep_type(days_) - dd.get_rep());
      }
      return date_type(date_rep_type(days_) - static_cast<date_int_type>(dd.days()));
    }
    BOOST_CXX14_CONSTEXPR date_type operator-=(const duration_type& dd)
    {
      *this = *this - dd;
      return date_type(days_);
    }
    BOOST_CONSTEXPR date_rep_type day_count() const
    {
      return days_;
    }
    //allow internal access from operators
    BOOST_CXX14_CONSTEXPR date_type operator+(const duration_type& dd) const
    {
      if(dd.is_special())
      {
        return date_type(date_rep_type(days_) + dd.get_rep());
      }
      return date_type(date_rep_type(days_) + static_cast<date_int_type>(dd.days()));
    }
    BOOST_CXX14_CONSTEXPR date_type operator+=(const duration_type& dd)
    {
      *this = *this + dd;
      return date_type(days_);
    }

    //see reference
  protected:
    /*! This is a private constructor which allows for the creation of new
      dates.  It is not exposed to users since that would require class
      users to understand the inner workings of the date class.
    */
    BOOST_CONSTEXPR explicit date(date_int_type days) : days_(days) {}
    BOOST_CXX14_CONSTEXPR explicit date(date_rep_type days) : days_(days.as_number()) {}
    date_int_type days_;

  };




} } // namespace date_time




#endif

/* date.hpp
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
*/