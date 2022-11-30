#ifndef DATE_TIME_DST_RULES_HPP__
#define DATE_TIME_DST_RULES_HPP__

/* Copyright (c) 2002,2003, 2007 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file dst_rules.hpp
  Contains template class to provide static dst rule calculations
*/

#include "boost/date_time/date_generators.hpp"
#include "boost/date_time/period.hpp"
#include "boost/date_time/date_defs.hpp"
#include <stdexcept>

namespace boost {
  namespace date_time {

    enum time_is_dst_result {is_not_in_dst, is_in_dst,
                             ambiguous, invalid_time_label};


    //! Dynamic class used to caluclate dst transition information
    template<class date_type_,
             class time_duration_type_>
    class dst_calculator
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;

      //! Check the local time offset when on dst start day
      /*! On this dst transition, the time label between
       *  the transition boundary and the boudary + the offset
       *  are invalid times.  If before the boundary then still
       *  not in dst.
       *@param time_of_day Time offset in the day for the local time
       *@param dst_start_offset_minutes Local day offset for start of dst
       *@param dst_length_minutes Number of minutes to adjust clock forward
       *@retval status of time label w.r.t. dst
       */
      static time_is_dst_result
      process_local_dst_start_day(const time_duration_type& time_of_day,
                                  unsigned int dst_start_offset_minutes,
                                  long dst_length_minutes)
      {
        //std::cout << "here" << std::endl;
        if (time_of_day < time_duration_type(0,dst_start_offset_minutes,0)) {
          return is_not_in_dst;
        }
        long offset = dst_start_offset_minutes + dst_length_minutes;
        if (time_of_day >= time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        return invalid_time_label;
      }

      //! Check the local time offset when on the last day of dst
      /*! This is the calculation for the DST end day.  On that day times
       *  prior to the conversion time - dst_length (1 am in US) are still
       *  in dst.  Times between the above and the switch time are
       *  ambiguous.  Times after the start_offset are not in dst.
       *@param time_of_day Time offset in the day for the local time
       *@param dst_end_offset_minutes Local time of day for end of dst
       *@retval status of time label w.r.t. dst
       */
      static time_is_dst_result
      process_local_dst_end_day(const time_duration_type& time_of_day,
                                unsigned int dst_end_offset_minutes,
                                long dst_length_minutes)
      {
        //in US this will be 60 so offset in day is 1,0,0
        int offset = dst_end_offset_minutes-dst_length_minutes;
        if (time_of_day < time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        if (time_of_day >= time_duration_type(0,dst_end_offset_minutes,0)) {
          return is_not_in_dst;
        }
        return ambiguous;
      }

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for
       *  invalid and ambiguous.
       *  @param current_day The day to check for dst
       *  @param time_of_day Time offset within the day to check
       *  @param dst_start_day  Starting day of dst for the given locality
       *  @param dst_start_offset Time offset within day for dst boundary
       *  @param dst_end_day    Ending day of dst for the given locality
       *  @param dst_end_offset Time offset within day given in dst for dst boundary
       *  @param dst_length_minutes length of dst adjusment
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result
      local_is_dst(const date_type& current_day,
                   const time_duration_type& time_of_day,
                   const date_type& dst_start_day,
                   const time_duration_type& dst_start_offset,
                   const date_type& dst_end_day,
                   const time_duration_type& dst_end_offset,
                   const time_duration_type& dst_length)
      {
        unsigned int start_minutes = static_cast<unsigned>(
          dst_start_offset.hours() * 60 + dst_start_offset.minutes());
        unsigned int end_minutes = static_cast<unsigned>(
          dst_end_offset.hours() * 60 + dst_end_offset.minutes());
        long length_minutes = static_cast<long>(
          dst_length.hours() * 60 + dst_length.minutes());

        return local_is_dst(current_day, time_of_day,
                            dst_start_day, start_minutes,
                            dst_end_day, end_minutes,
                            length_minutes);
      }

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for
       *  invalid and ambiguous.
       *  @param current_day The day to check for dst
       *  @param time_of_day Time offset within the day to check
       *  @param dst_start_day  Starting day of dst for the given locality
       *  @param dst_start_offset_minutes Offset within day for dst
       *         boundary (eg 120 for US which is 02:00:00)
       *  @param dst_end_day    Ending day of dst for the given locality
       *  @param dst_end_offset_minutes Offset within day given in dst for dst
       *         boundary (eg 120 for US which is 02:00:00)
       *  @param dst_length_minutes Length of dst adjusment (eg: 60 for US)
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result
      local_is_dst(const date_type& current_day,
                   const time_duration_type& time_of_day,
                   const date_type& dst_start_day,
                   unsigned int dst_start_offset_minutes,
                   const date_type& dst_end_day,
                   unsigned int dst_end_offset_minutes,
                   long dst_length_minutes)
      {
        //in northern hemisphere dst is in the middle of the year
        if (dst_start_day < dst_end_day) {
          if ((current_day > dst_start_day) && (current_day < dst_end_day)) {
            return is_in_dst;
          }
          if ((current_day < dst_start_day) || (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
        }
        else {//southern hemisphere dst is at begining /end of year
          if ((current_day < dst_start_day) && (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
          if ((current_day > dst_start_day) || (current_day < dst_end_day)) {
            return is_in_dst;
          }
        }

        if (current_day == dst_start_day) {
          return process_local_dst_start_day(time_of_day,
                                             dst_start_offset_minutes,
                                             dst_length_minutes);
        }

        if (current_day == dst_end_day) {
          return process_local_dst_end_day(time_of_day,
                                           dst_end_offset_minutes,
                                           dst_length_minutes);
        }
        //you should never reach this statement
        return invalid_time_label;
      }

    };


    //! Compile-time configurable daylight savings time calculation engine
    /* This template provides the ability to configure a daylight savings
     * calculation at compile time covering all the cases.  Unfortunately
     * because of the number of dimensions related to daylight savings
     * calculation the number of parameters is high.  In addition, the
     * start and end transition rules are complex types that specify
     * an algorithm for calculation of the starting day and ending
     * day of daylight savings time including the month and day
     * specifications (eg: last sunday in October).
     *
     * @param date_type A type that represents dates, typically gregorian::date
     * @param time_duration_type Used for the offset in the day calculations
     * @param dst_traits A set of traits that define the rules of dst
     *        calculation.  The dst_trait must include the following:
     * start_rule_functor - Rule to calculate the starting date of a
     *                      dst transition (eg: last_kday_of_month).
     * start_day - static function that returns month of dst start for
     *             start_rule_functor
     * start_month -static function that returns day or day of week for
     *              dst start of dst
     * end_rule_functor - Rule to calculate the end of dst day.
     * end_day - static fucntion that returns end day for end_rule_functor
     * end_month - static function that returns end month for end_rule_functor
     * dst_start_offset_minutes - number of minutes from start of day to transition to dst -- 120 (or 2:00 am) is typical for the U.S. and E.U.
     * dst_start_offset_minutes - number of minutes from start of day to transition off of dst -- 180 (or 3:00 am) is typical for E.U.
     * dst_length_minutes - number of minutes that dst shifts clock
     */
    template<class date_type,
             class time_duration_type,
             class dst_traits>
    class dst_calc_engine
    {
    public:
      typedef typename date_type::year_type year_type;
      typedef typename date_type::calendar_type calendar_type;
      typedef dst_calculator<date_type, time_duration_type> dstcalc;

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for
       *  invalid and ambiguous.
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result local_is_dst(const date_type& d,
                                             const time_duration_type& td)
      {

        year_type y = d.year();
        date_type dst_start = local_dst_start_day(y);
        date_type dst_end   = local_dst_end_day(y);
        return dstcalc::local_is_dst(d,td,
                                     dst_start,
                                     dst_traits::dst_start_offset_minutes(),
                                     dst_end,
                                     dst_traits::dst_end_offset_minutes(),
                                     dst_traits::dst_shift_length_minutes());

      }

      static bool is_dst_boundary_day(date_type d)
      {
        year_type y = d.year();
        return ((d == local_dst_start_day(y)) ||
                (d == local_dst_end_day(y)));
      }

      //! The time of day for the dst transition (eg: typically 01:00:00 or 02:00:00)
      static time_duration_type dst_offset()
      {
        return time_duration_type(0,dst_traits::dst_shift_length_minutes(),0);
      }

      static date_type local_dst_start_day(year_type year)
      {
        return dst_traits::local_dst_start_day(year);
      }

      static date_type local_dst_end_day(year_type year)
      {
        return dst_traits::local_dst_end_day(year);
      }


    };

    //! Depricated: Class to calculate dst boundaries for US time zones
    /* Use dst_calc_engine instead.
     * In 2007 US/Canada DST rules changed
     * (http://en.wikipedia.org/wiki/Energy_Policy_Act_of_2005#Change_to_daylight_saving_time).
     */
    template<class date_type_,
             class time_duration_type_,
             unsigned int dst_start_offset_minutes=120, //from start of day
             short dst_length_minutes=60>  //1 hour == 60 min in US
    class us_dst_rules
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;
      typedef typename date_type::year_type year_type;
      typedef typename date_type::calendar_type calendar_type;
      typedef date_time::last_kday_of_month<date_type> lkday;
      typedef date_time::first_kday_of_month<date_type> fkday;
      typedef date_time::nth_kday_of_month<date_type> nkday;
      typedef dst_calculator<date_type, time_duration_type> dstcalc;

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for
       *  invalid and ambiguous.
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result local_is_dst(const date_type& d,
                                             const time_duration_type& td)
      {

        year_type y = d.year();
        date_type dst_start = local_dst_start_day(y);
        date_type dst_end   = local_dst_end_day(y);
        return dstcalc::local_is_dst(d,td,
                                     dst_start,dst_start_offset_minutes,
                                     dst_end, dst_start_offset_minutes,
                                     dst_length_minutes);

      }


      static bool is_dst_boundary_day(date_type d)
      {
        year_type y = d.year();
        return ((d == local_dst_start_day(y)) ||
                (d == local_dst_end_day(y)));
      }

      static date_type local_dst_start_day(year_type year)
      {
        if (year >= year_type(2007)) {
          //second sunday in march
          nkday ssim(nkday::second, Sunday, date_time::Mar);
          return ssim.get_date(year);
        } else {
          //first sunday in april
          fkday fsia(Sunday, date_time::Apr);
          return fsia.get_date(year);
        }
      }

      static date_type local_dst_end_day(year_type year)
      {
        if (year >= year_type(2007)) {
          //first sunday in november
          fkday fsin(Sunday, date_time::Nov);
          return fsin.get_date(year);
        } else {
          //last sunday in october
          lkday lsio(Sunday, date_time::Oct);
          return lsio.get_date(year);
        }
      }

      static time_duration_type dst_offset()
      {
        return time_duration_type(0,dst_length_minutes,0);
      }

     private:


    };

    //! Used for local time adjustments in places that don't use dst
    template<class date_type_, class time_duration_type_>
    class null_dst_rules
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;


      //! Calculates if the given local time is dst or not
      /*! @retval Always is_not_in_dst since this is for zones without dst
       */
      static time_is_dst_result local_is_dst(const date_type&,
                                             const time_duration_type&)
      {
        return is_not_in_dst;
      }

      //! Calculates if the given utc time is in dst
      static time_is_dst_result utc_is_dst(const date_type&,
                                           const time_duration_type&)
      {
        return is_not_in_dst;
      }

      static bool is_dst_boundary_day(date_type /*d*/)
      {
        return false;
      }

      static time_duration_type dst_offset()
      {
        return time_duration_type(0,0,0);
      }

    };


  } } //namespace date_time



#endif

/* dst_rules.hpp
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
*/