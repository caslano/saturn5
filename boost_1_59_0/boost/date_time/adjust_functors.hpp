#ifndef _DATE_TIME_ADJUST_FUNCTORS_HPP___
#define _DATE_TIME_ADJUST_FUNCTORS_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/date.hpp"
#include "boost/date_time/wrapping_int.hpp"

namespace boost {
namespace date_time {


  //! Functor to iterate a fixed number of days
  template<class date_type>
  class day_functor
  {
  public:
    typedef typename date_type::duration_type duration_type;
    day_functor(int f) : f_(f) {}
    duration_type get_offset(const date_type&) const
    {
      return duration_type(f_);
    }
    duration_type get_neg_offset(const date_type&) const
    {
      return duration_type(-f_);
    }
  private:
    int f_;
  };


  //! Provides calculation to find next nth month given a date
  /*! This adjustment function provides the logic for 'month-based'
   *  advancement on a ymd based calendar.  The policy it uses
   *  to handle the non existant end of month days is to back
   *  up to the last day of the month.  Also, if the starting
   *  date is the last day of a month, this functor will attempt
   *  to adjust to the end of the month.

   */
  template<class date_type>
  class month_functor
  {
  public:
    typedef typename date_type::duration_type duration_type;
    typedef typename date_type::calendar_type cal_type;
    typedef typename cal_type::ymd_type ymd_type;
    typedef typename cal_type::day_type day_type;

    month_functor(int f) : f_(f), origDayOfMonth_(0) {}
    duration_type get_offset(const date_type& d) const
    {
      ymd_type ymd(d.year_month_day());
      if (origDayOfMonth_ == 0) {
        origDayOfMonth_ = ymd.day;
        day_type endOfMonthDay(cal_type::end_of_month_day(ymd.year,ymd.month));
        if (endOfMonthDay == ymd.day) {
          origDayOfMonth_ = -1; //force the value to the end of month
        }
      }
      typedef date_time::wrapping_int2<short,1,12> wrap_int2;
      wrap_int2 wi(ymd.month);
      //calc the year wrap around, add() returns 0 or 1 if wrapped
      const typename ymd_type::year_type year(static_cast<typename ymd_type::year_type::value_type>(ymd.year + wi.add(f_)));
//       std::cout << "trace wi: " << wi.as_int() << std::endl;
//       std::cout << "trace year: " << year << std::endl;
      //find the last day for the new month
      day_type resultingEndOfMonthDay(cal_type::end_of_month_day(year, wi.as_int()));
      //original was the end of month -- force to last day of month
      if (origDayOfMonth_ == -1) {
        return date_type(year, wi.as_int(), resultingEndOfMonthDay) - d;
      }
      day_type dayOfMonth = origDayOfMonth_;
      if (dayOfMonth > resultingEndOfMonthDay) {
        dayOfMonth = resultingEndOfMonthDay;
      }
      return date_type(year, wi.as_int(), dayOfMonth) - d;
    }
    //! Returns a negative duration_type
    duration_type get_neg_offset(const date_type& d) const
    {
      ymd_type ymd(d.year_month_day());
      if (origDayOfMonth_ == 0) {
        origDayOfMonth_ = ymd.day;
        day_type endOfMonthDay(cal_type::end_of_month_day(ymd.year,ymd.month));
        if (endOfMonthDay == ymd.day) {
          origDayOfMonth_ = -1; //force the value to the end of month
        }
      }
      typedef date_time::wrapping_int2<short,1,12> wrap_int2;
      wrap_int2 wi(ymd.month);
      //calc the year wrap around, add() returns 0 or 1 if wrapped
      const typename ymd_type::year_type year(static_cast<typename ymd_type::year_type::value_type>(ymd.year + wi.subtract(f_)));
      //find the last day for the new month
      day_type resultingEndOfMonthDay(cal_type::end_of_month_day(year, wi.as_int()));
      //original was the end of month -- force to last day of month
      if (origDayOfMonth_ == -1) {
        return date_type(year, wi.as_int(), resultingEndOfMonthDay) - d;
      }
      day_type dayOfMonth = origDayOfMonth_;
      if (dayOfMonth > resultingEndOfMonthDay) {
        dayOfMonth = resultingEndOfMonthDay;
      }
      return date_type(year, wi.as_int(), dayOfMonth) - d;
    }
  private:
    int f_;
    mutable short origDayOfMonth_;
  };


  //! Functor to iterate a over weeks
  template<class date_type>
  class week_functor
  {
  public:
    typedef typename date_type::duration_type duration_type;
    typedef typename date_type::calendar_type calendar_type;
    week_functor(int f) : f_(f) {}
    duration_type get_offset(const date_type&) const
    {
      return duration_type(f_*static_cast<int>(calendar_type::days_in_week()));
    }
    duration_type get_neg_offset(const date_type&) const
    {
      return duration_type(-f_*static_cast<int>(calendar_type::days_in_week()));
    }
  private:
    int f_;
  };

  //! Functor to iterate by a year adjusting for leap years
  template<class date_type>
  class year_functor
  {
  public:
    //typedef typename date_type::year_type year_type;
    typedef typename date_type::duration_type duration_type;
    year_functor(int f) : _mf(f * 12) {}
    duration_type get_offset(const date_type& d) const
    {
      return _mf.get_offset(d);
    }
    duration_type get_neg_offset(const date_type& d) const
    {
      return _mf.get_neg_offset(d);
    }
  private:
    month_functor<date_type> _mf;
  };


} }//namespace date_time


#endif


/* adjust_functors.hpp
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
*/