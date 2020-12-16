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
xtXUymbcr1VS+OYQvqI6ZI2xKM8QKK3ft65iyxch1blSXmZirt5fmKuDV7Oe4uZ+SdNG6QXhnxwSI8kPlS35I9qo24PZOkNgznNekkDyBlh+jDlvAZv5pNLwiq0hOh0B098ypYTGygExkKVcDDUCsgTVZD3SUmSg7OgrC77za+Av2oC/gDT5YL9+Kbdfzwcp5pP7mBST/2cpxcjiFcc/UirCJ7isjUETWewKkrqUsIrhuap5s7TFn+mTGzU8s1ObHCzmOcCzmvbeYxMsHQ9zRY5KXQ6BsVjkyNpIdmwL8B/WV8SlDu+zqafzWar751GRdM3hN5p5aCRwhZbjqejf4wOXE3C5AC5XgXf8E4Bx52wcDdSIGVUenBuVJ/Ph4WZa7ODxWmEdWUqsOXcBWUXX/oLby9N14U/8hMqGPaShyaGAlu1ZgEnuAM4vlQW5XXJYfGxmYb3w8hFO2ykjnbZU+Lse/s6D59+NwN/iD9P/v/g47U/MNo1372H8SPXxO4rmeSH56VoAv1CIwQ1jt5+jQuordAdb4lerYBp+HWDRpQfYhCZzADeNL4iyRb+WP/1S6Sb5UhPe6BTBxWM3l3Pr+YnwNQACU+DqLy59lRfj0BAsuCz0Hex3tTqKXSjV9LqfSDYAO3zK/OzuxiiZHxfE7k6pqKMRezn6MWXile1byJ+CBR7KvtXqpziufw77V3JTXw5WgeulH2Y0EpyNKmncYcTIS8JV0ld1yhbn+nRsDbPIZmQoqh1EjnR6ZJGztF2P6i4rCfXPaMaa2Nw0KQrVTX4q7XoojerG7zVheZEuZkDIaQjoDAA6/K4VTM8Pypn/x0ij4f6YX/HsJ68jAbFXCZ1XaEVzeL/fMdWt3MwOz5DJU9HgcxnsFbPh3rKdEfWNFkTUORuIqAEl/O86hxrEZQYB3M0BzuEAZTQTKjuBt3LKcT3kIE9t/7DRZWjlDlblRDPfTVS9D8G4lAnpeLbF353UnJ8wcFau9hAtD7TLXYCz6f6nYDI8WEsrkQzfhCNCF22IDZ5Itlo83UrLZilU8FBRmTFaZdam88oQAL9UFL9mOOaoZhlQMzbceLQGnwwkE64ECN5+F3YPKLdSXUjwbM0TdSDaZvmVPbmpU43tIJs0zcWb1J9Sx/iFWszHGZI/NL1Djk2mxnq8idxFNeAN533qqDwn+bp8ncbr0o6lom2KRmdsf+QFcNNCA+r4DDGgloO5aFHtg/S6LX9dFroBXrNe/42Fm0n6Q/zX1P/JF8QvhKGnvFEpjgrba3ZqjB3KoyXh3SYbXcJyo6yosIbvjxopxKkd42NuYSIQiPSTEMfyM17lqF/L5hZXCAT3whxSq0K/qbYuqi1PF8+4ahc6xKpdaOfZ+dFmOaTE3o+iZ0UfeZmTYOhA81hyNClepaBKCV/JMobxRd+HLcM8KDJWtsbBihwAvrGYkZEcyDuS8gIMq2ipPCgtdZMEUcxF9wGS8Q1gU2MAxd/4LIVNhgFTr64ZJt4Vpdq0axmr6JxFOHoq0TgNN5eoCj34WKOMP6NobcoAb7EQ8Sc6oL0Uuq+Ya22Kw5dDinBQi+JLYeiRCENVAqhK5HbiBIQVdCDfzD6AKGEQ1xKEP4JraQn+Qpl4mVT3+End4w+H7SqWrvBT3pX3FSMs6o2k+uQZ2ITCy5EiSylmKdZlWQZZTCnkhfzDxIEYggXkzWQk7w37UfCCMVXZTeLy/w2LE5VrId978T3WPk+rPQ47DImVuHeEWs0FYgt2OYpxNCLfh9eCjgMYHU+Ecy099a5g1AtONFBqgI4Mi8BSJUFVRPtlha6GFZxIoDX15J3U1MgfNJ9jgQwaKmiXTwUMFf7SqTpmyNsD8l8=
*/