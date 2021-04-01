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
Dh+aCOieoPrjE6J54iw6U/XQ+kWtAwphqtLB2teO0MSM5AaaRmhkqdMQ9+/aVvS2SqXlYBb4pLt+ap0JTEQMtF73+O0VX7lMURzrI/mRpBekqkxrFi566W7iBRQSISb1dOui30aATfr5oefInPSwRWRpG2CqXviFL8nXD92wVCAmq4dXXpDfWeiqGuQzQwhBklYWQh4D0+BICiPtS7Z7Fn7Rl0Nm444K0n7uB/ur//Ik60xeIKGFHSL9x6rDGDhQnrwxwKzqD1iYg4S2HpKuAp4RNZl4BDpJfITadMU+ZewQ6TsnqjByWj4tWnyUmIoBBxTV3uaG7WBaKy8d+K0RxIKnQHrn/AYBuRGkpMfRsawIbBAa0RfODusLMCIOK2g6ZiV1EXbZ7+OodWJw8mcLSX+xuQvB4seNc5LmX8dCOawSe625yC225N9883F/DPvnHr/LnPFZVSqX28WdDi8i3FtP2RT/uZ/FiDY/s2bbelLGn18usHO8m6AZgsxzZGdV3KpZLzgM5tHKt03dCBh7v6FmeNUgVxepv+jOztlGjE5bK+iR5wqah2edvw==
*/