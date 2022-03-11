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