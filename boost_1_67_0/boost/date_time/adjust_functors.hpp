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