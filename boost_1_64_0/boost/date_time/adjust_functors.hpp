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
t95K9oHaWnYOB/V1tbdOZud56qDUT/GxhEwmk0nDsk5HyMgEGpDJZAsm1ENjQev5ac/xR8rb1jSNLyq3+AM/zWb7jY+zkrCS5pGV2za8D2F4NXHIWR3eTUdYjg+aQQbULAx+hhatH/3Nk7Y8ctKOiDZpx+onbV4ng7UfC8cq0wmgARQH0uaos4nDtYHdMXiA081Wmp81wQFfdOoT/aTOKptyE5s8ddI2qi+RohU7UddtG1Vl0pabJ23m4RxVIFtPWieqW7daTtpGqrwy32bSLmKLt/O1SVtpOWmr2WwqmtGfHUphpD93a7KBMydbtWGyVZtmNEo0Ca78rNPRMzJpjM5EmxvIazP65UGykuhJvlDWYkYvUoT6a2Z0tWFGN+pntG9QtBlNGTijY9CCzRmmMMitSpeCXMYzF5wvwlxB20l4fb4PHhmb1/n79gN6qO//L8Y87dZL9ncld/Ul++i/3/BinMSfyIhlj1tEGXDHJ/rPMKxu6ej8Zxii8ys08Duhc37fp3fhZx+KrI7Ov3Dpj86Two81jnXz4RvG6a2P4AMLoxsZfnOD5tORSOFeHD6lHgHHQCRvuAIobkdlBQ/DpYJ0/1A24dbGNxw3L0KPJFxJ4JO3xlJmITHR5VNagTWeW2FLvLfo8zaFryk85I1eSJE70D3AcbdejYd+kHFv70F7mDTLZNAyb8Qqg5B1X82q+Ni5TVti61w+5mua42fHo00/3iKmcOgFsRdSmE+bqSPsib2kcueAi8/AcnsY6Lye1uV2Quu6chrxwx5DoTsrFbW96Dq+ERdzsIeqtGRyGhx6ZnRDT8vx/iFG0qoo4n5FaUvn9yuKLJ7fuleGYwyhGQkOwQIrK8ENaKU8yUq5SOVKPpEvP+9FbXO158CkO7yXO5V79wWemuYNFLe8rtBDr4NlmYNlPVILWhZ35j8DAPFUF+6HT7YPP42MhkMTuNfTtYvrkx9v8eJJXGAtllH4VNWd7ZxzsFH4HlI/tp8ut69s4VlaITJzXsPH7GQa4qF1HSFIyy1WJ1o/5/jGG/sbCjQRYH7gS4dXYJ+zJHhvjldWFS1QU+d363rWOTlLsqW0zl3ye8JkvLfPCz7WnOaeiNu3RKnJc9x4gGw6BwKHqYaumFo7qnVhBm0LJXv9V27zRvqv5HB7OySHY6zGpVIaaOcNychmT+VYv+NUnyLsKdsSZqjaJbj/Rg4oOrESJXStFU4l1oNZtPNARMPMcH7gA+eQSMO6LMBYsIKLZfyNEtOvybSETOnWmo/mhX20ZqFbyuKRKj5QoqsazRnAb7xth09g5jpTbruLAzAU+cKGUfIJShyeVmM4NmY+NcDxSfjFPIl9IdkvVvrQi+lU5OIPHjXA6yA+x56TfA6X3E9XBd5nGz+cIMaLBxdQ/x6fkWcZPYc47F+gHP9D37YE2htbsaImetW5CxuukyUcupoS0nqcOjen8XqDOUpBL5ZyCwpcsdoTnorVi3lpgwa0Opkyw9Ztx3LC1cgTLhb4WLCgwZvqfNt/DawhY6XosAa6KxOlVPCDFR3/8UcWIqOcE//oULbiEtlBE2JgMG71AfqgDxV4o/+2vZ1KKb3Njf0iTcvGM0ZodaIJNmn0gXMpPW/cjQXKSlCirQSVMW0xbUssKxlgyTse2yUrV0it0/Ahl//J3rWAR1Vc4bub3WQJgQ0YIAhCIAGDPFwh2ESCbDS2q0RJFSUqahDQICgp7GJUwsOggiuKSpVqa7E+qvWtFQNWTQABlSq+3y3aWjeuWtRaqUK2558zM/fe3U2yUUrtVy8f2XvncebMmTMzZ86cOeNU4Q6EL9fhLsxjCHdiHpvPgR4VmIbAMzkwWwW6EHgsB+Y=
*/