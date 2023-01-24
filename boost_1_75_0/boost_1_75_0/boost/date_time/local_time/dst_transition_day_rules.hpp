#ifndef LOCAL_TIME_DST_TRANSITION_DAY_RULES_HPP__
#define LOCAL_TIME_DST_TRANSITION_DAY_RULES_HPP__

/* Copyright (c) 2003-2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/dst_transition_generators.hpp"

namespace boost {
namespace local_time {
   
    //! Provides rule of the form starting Apr 30 ending Oct 21
    typedef date_time::dst_day_calc_rule<gregorian::date> dst_calc_rule;

    struct partial_date_rule_spec 
    {
      typedef gregorian::date date_type;
      typedef gregorian::partial_date start_rule;
      typedef gregorian::partial_date end_rule;
    };
    
    //! Provides rule of the form first Sunday in April, last Saturday in Oct
    typedef date_time::day_calc_dst_rule<partial_date_rule_spec> partial_date_dst_rule;

    struct first_last_rule_spec 
    {
      typedef gregorian::date date_type;
      typedef gregorian::first_kday_of_month start_rule;
      typedef gregorian::last_kday_of_month end_rule;
    };

    //! Provides rule of the form first Sunday in April, last Saturday in Oct
    typedef date_time::day_calc_dst_rule<first_last_rule_spec> first_last_dst_rule;

    struct last_last_rule_spec 
    {
      typedef gregorian::date date_type;
      typedef gregorian::last_kday_of_month start_rule;
      typedef gregorian::last_kday_of_month end_rule;
    };

    //! Provides rule of the form last Sunday in April, last Saturday in Oct
    typedef date_time::day_calc_dst_rule<last_last_rule_spec> last_last_dst_rule;

    struct nth_last_rule_spec
    {
      typedef gregorian::date date_type;
      typedef gregorian::nth_kday_of_month start_rule;
      typedef gregorian::last_kday_of_month end_rule;
    };

    //! Provides rule in form of [1st|2nd|3rd|4th] Sunday in April, last Sunday in Oct
    typedef date_time::day_calc_dst_rule<nth_last_rule_spec> nth_last_dst_rule;
    
    struct nth_kday_rule_spec
    {
      typedef gregorian::date date_type;
      typedef gregorian::nth_kday_of_month start_rule;
      typedef gregorian::nth_kday_of_month end_rule;
    };

    //! Provides rule in form of [1st|2nd|3rd|4th] Sunday in April/October
    typedef date_time::day_calc_dst_rule<nth_kday_rule_spec> nth_kday_dst_rule;
    //! Provides rule in form of [1st|2nd|3rd|4th] Sunday in April/October
    typedef date_time::day_calc_dst_rule<nth_kday_rule_spec> nth_day_of_the_week_in_month_dst_rule;


} }//namespace


#endif

/* dst_transition_day_rules.hpp
iR2DiEMu2RbCu1/UKxOj9eLgcQMXGtJso7B16Ik8yGmd1bBRwqmo5oN/MOK2NFK31WW/2aL47kSkuLnJZO0UspnxzqF05fkxO9OrXU1dc56cnJf8Ni/scT0j/CB8nJ/5M3fN3dd3e6T8u+cMEy/dXQW2N7m+5Bek24xUEhYKzeEH/5svsHLuh+yrX04Yki6jffRZIG1v8qSHQAe0BmIOSgv0BOQE7GSj5UCd8zz9H5SaRVAcABJFcQIEWCC4Le4Q3IcEd3eX4O7OQBLc3d3dh+Du7u7uNjjDrNaetmprD33oU1f17f335WcfI8H36RhxKHXSxTCEXkPWVu+aX+11Zc2vMo4/bm9+8hd8IK6SMBcJd7yGa+AD3rCZkkklGAsxZOdgvuF0eIpFFMbRs9owR+TZyfcDWRjMHrPO473x61TiD0Ezb54h67zeLSE1eofs1hjP99y9y6MPd0DMuhCSD0G9mtcMCD4857FR1QfZjlrNh6AnGaY4ZNhD6HKbC56YOQ0Wevit2Y4EmiIXtG4xlLtLT3mltjyeW/pwiAGNfV5G4PUmfzAEO96yOkK7HO1VVJkRgYCFPsrnFpzW44p+KN42O7S4J/yb80Z4haUx1BgWGBDgqrVjyd+y+3AFvZf5DSN6LUE9jWkJPZZ7Q9rh2InuyQzkhXek8Oap6nGlUUasoWzFc0DcQtJHr0KsoegChS/BOiLXIDvAOCAs
*/