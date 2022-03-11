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