#ifndef DATE_TIME_LOCAL_TIMEZONE_DEFS_HPP__
#define DATE_TIME_LOCAL_TIMEZONE_DEFS_HPP__

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland 
 * $Date$
 */

#include "boost/date_time/dst_rules.hpp"

namespace boost {
  namespace date_time {

    // Configurations for common dst rules cases:
    // See http://www.wharton.co.uk/Support/sup_dst.htm for more
    // information on how various locales use dst rules

    //! Specification for daylight savings start rules in US
    /*! This class is used to configure dst_calc_engine template typically
        as follows:
        @code
          using namespace boost::gregorian;
          using namespace boost::posix_time;
          typedef us_dst_trait<date> us_dst_traits;
          typedef boost::date_time::dst_calc_engine<date, time_duration, 
                                                    us_dst_traits>  
                                                    us_dst_calc;
          //calculate the 2002 transition day of USA April 7 2002
          date dst_start = us_dst_calc::local_dst_start_day(2002); 

          //calculate the 2002 transition day of USA Oct 27 2002
          date dst_end = us_dst_calc::local_dst_end_day(2002); 
                                                    
          //check if a local time is in dst or not -- posible answers
          //are yes, no, invalid time label, ambiguous
          ptime t(...some time...);  
          if (us_dst::local_is_dst(t.date(), t.time_of_day()) 
              == boost::date_time::is_not_in_dst) 
          {

          }

        @endcode
        This generates a type suitable for the calculation of dst 
        transitions for the United States.  Of course other templates
        can be used for other locales.

    */

     template<class date_type>
     struct us_dst_trait
     {
       typedef typename date_type::day_of_week_type day_of_week_type;
       typedef typename date_type::month_type month_type;
       typedef typename date_type::year_type year_type;
       typedef date_time::nth_kday_of_month<date_type> start_rule_functor;
       typedef date_time::first_kday_of_month<date_type> end_rule_functor;
       typedef date_time::first_kday_of_month<date_type> start_rule_functor_pre2007;
       typedef date_time::last_kday_of_month<date_type> end_rule_functor_pre2007;
       static day_of_week_type start_day(year_type) {return Sunday;}
       static month_type start_month(year_type y) 
       {
         if (y < 2007) return Apr;
         return Mar;
       }
       static day_of_week_type end_day(year_type) {return Sunday;}
       static month_type end_month(year_type y) 
       {
         if (y < 2007) return Oct;
         return Nov;
       }
       static date_type local_dst_start_day(year_type year)
       {
         if (year < 2007) {
           start_rule_functor_pre2007 start1(start_day(year), 
                                             start_month(year));
           return start1.get_date(year);
         }
         start_rule_functor start(start_rule_functor::second,
                                  start_day(year), 
                                  start_month(year));
         return start.get_date(year);
          
       }
       static date_type local_dst_end_day(year_type year)
       {
         if (year < 2007) {
           end_rule_functor_pre2007 end_rule(end_day(year), 
                                             end_month(year));
           return end_rule.get_date(year);
         }
         end_rule_functor end(end_day(year), 
                              end_month(year));
         return end.get_date(year);      
       }
       static int dst_start_offset_minutes() { return 120;}
       static int dst_end_offset_minutes() { return 120; }
       static int dst_shift_length_minutes() { return 60; }
     };

    //!Rules for daylight savings start in the EU (Last Sun in Mar)
    /*!These amount to the following:
      - Start of dst day is last Sunday in March
      - End day of dst is last Sunday in Oct
      - Going forward switch time is 2:00 am (offset 120 minutes)
      - Going back switch time is 3:00 am (off set 180 minutes)
      - Shift duration is one hour (60 minutes)
    */
    template<class date_type>
    struct eu_dst_trait
    {
      typedef typename date_type::day_of_week_type day_of_week_type;
      typedef typename date_type::month_type month_type;
      typedef typename date_type::year_type year_type;
      typedef date_time::last_kday_of_month<date_type> start_rule_functor;
      typedef date_time::last_kday_of_month<date_type> end_rule_functor;
      static day_of_week_type start_day(year_type) {return Sunday;}
      static month_type start_month(year_type) {return Mar;}
      static day_of_week_type end_day(year_type) {return Sunday;}
      static month_type end_month(year_type) {return Oct;}
      static int dst_start_offset_minutes() { return 120;}
      static int dst_end_offset_minutes() { return 180; }
      static int dst_shift_length_minutes() { return 60; }
      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }
      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }
    };

    //! Alternative dst traits for some parts of the United Kingdom
    /* Several places in the UK use EU start and end rules for the 
       day, but different local conversion times (eg: forward change at 1:00 
       am local and  backward change at 2:00 am dst instead of 2:00am 
       forward and 3:00am back for the EU).
    */
    template<class date_type>
    struct uk_dst_trait : public eu_dst_trait<date_type>
    {
      static int dst_start_offset_minutes() { return 60;}
      static int dst_end_offset_minutes() { return 120; }
      static int dst_shift_length_minutes() { return 60; }
    };

    //Rules for Adelaide Australia
    template<class date_type>
    struct acst_dst_trait
    {
      typedef typename date_type::day_of_week_type day_of_week_type;
      typedef typename date_type::month_type month_type;
      typedef typename date_type::year_type year_type;
      typedef date_time::last_kday_of_month<date_type> start_rule_functor;
      typedef date_time::last_kday_of_month<date_type> end_rule_functor;
      static day_of_week_type start_day(year_type) {return Sunday;}
      static month_type start_month(year_type) {return Oct;}
      static day_of_week_type end_day(year_type) {return Sunday;}
      static month_type end_month(year_type) {return Mar;}
      static int dst_start_offset_minutes() { return 120;}
      static int dst_end_offset_minutes() { return 180; }
      static int dst_shift_length_minutes() { return 60; }
      static date_type local_dst_start_day(year_type year)
      {
        start_rule_functor start(start_day(year), 
                                 start_month(year));
        return start.get_date(year);      
      }
      static date_type local_dst_end_day(year_type year)
      {
        end_rule_functor end(end_day(year), 
                             end_month(year));
        return end.get_date(year);      
      }
    };
    
    




} } //namespace boost::date_time


#endif

/* local_timezone_defs.hpp
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
*/