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
A0e//IT2F+KD685oWsqvPNI/NgjDb1R/YbjE9QmuerS3+hZ26ElW36htrcLG11tzH4ZPcLc0QZq/njFehuYWK7VlYz+QxbYU16mm9qBDJ69evaQjen78/LhLFywXPCNf83zFy+suvY3tyl8pu7tzFX/XJa6JZe4BYJAKRUomesNKTrjPRMRzxWNiimKuolKs8CBy0imnRGScBpPpYjh+36VNKqK0wdnKilQqqyymlN1yKnnExW0NU7BSk0yAAPxYKA3MSguZu3DPSfNyrRoYEwTLlCR2y0TGVnDHNKVaF+p1rxdVZYZMerGMVC/alcJN9fpBVgtEs2ZbkoUmLalSvEtmf5fWMhaJuaJEWCyqVSZU2t2HBYd53JMlKZ5lDRxMBVd1Cpz8plpds5MKRC+0uSiZK+Ntk8r1wUaUtQFKqjKHO5QF+2KJwnepymNe2v22EDsvTZVtyX/Rsn3sMckcUVGr79PQb9GKKaG69HkYXE3mAX3uz2b9cbCgySX1x4sG78NwfAFuCHgtid8VJVeIoiSxLjLB4wPnv3XSHTe4osF8NppMg/AqCKbT2eTLIpiPx96ITql18oL+rnLQ++SsRa1MrEz/6YV7+sI9xoJ5CjlT21BxbTqNH0ilgOtf0bj/0XN+Br48Il3lOcZF
*/