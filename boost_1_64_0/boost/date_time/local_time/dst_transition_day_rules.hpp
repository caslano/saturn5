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
Rz28zR35FKts3HsextDLbNVNBke26o58/ss+3XHy//dvw9ypu1p63q5xk0/ZP5CrDDpzt7qLpxONH6DKxJnNZne8sq3fhB7+IoWueYXbhK8tLg1l90cfTDLYlWa1jj8OW/F4EpRwJ0GzzsUk6P3AO9tOgl57liZBp/CIvN1JYsUG5p+OTrirA1n63baHi9F3/za9b66ZfYsAPcigjLsFoVXtj7Nb/2m6EHhJlpd/b0Xe+DLtUkm6oec2Uwb2tYlSzk9elEQ3wpzUrKMSJNCoPXgX28Umym7sHetaZHY9J+vM94JZNIkG1Ywryo4g+xlOoNMwxHzCL4n5W8kvgQQZJEi5vLZEOcHU4hXkpHFLai9GgQGcBEn10rWU7ntNAWG12s+0/V/2Kb9/6bevkD65u0tO+jEKoWrJ1XLSyQxlg20n0U/aingi6xty/G13P1yD3t6MrgSTBtdNbfcckEZZt09LA3SI+xx4VY5+kndEJYZMwX6Yzl5OceAQiPGHX9d9ULssz270cxf+jcuzYlH//oHMtE00EgmSijYGXFWdF+R9GE2IsD6OXqT/0AukhzPp7mqeyscRKCAg+zQfD9IwHUlo7NDDw/Q8SFSaWuzbF5NTxnQu2gSirj+m3t2WeUgHTMPnwP9Uaxp+9wyZht+MUgLtt51KsME064ZA25GW5rsMTQxQkK8gbbC1Apw8zqx+7cVtleM+buIwr8WUpm8hMygAstbsZbaBc3pgTnjII5En9bD5sTFNJsbukzf4lRjrYZyzjBwcE9kYjRfdBCwCHBimX1QQLooXLhtd0k3Fw5wNr7rcmkCkCQmuqXBLu8CljfyTsjvzX2Vnxtd4VouKoJayjyBCZsQ6i8g+zz/WyoSKLHBFAlNVpJEVZVbFJi5uqEsysInoCU+xWhhLjEwInCNeoTqaqOrmIbNXTaqsrzcidLU47LNhUixL5SbO6eUmzWKjC1eYmeJCHEFoHwUhPoa45wMc11qBuMOgM0dTRDaCiEmI2JsiTgnLwQV0RBhIn4JRMVpzp0mfM388uW/HdAWb4IJV54eDSmBRABQcN4/ZrhloauAyMhCoBs+RsQd0B2fjsTAxbenvWQv+pgHPr7q9x8TMf7QA27XLHuUcq4gP3Qtl4SkMTx54W/byTayUvG07Je4YHPRIeMksar9yE8t8PxX9+0XmSWFTZ6eaCY3YEPOdYY9bAy1JTTcxzYjJsE65/qYkJBcX7ePsol3HjoRFcPLgtmtYfhzIFsOccg4aI56Uq/RZKkXFaNYUHN/baCuD+8Q3ZToje+yyEA+S8hJaJMf2Xi4eS2ULL6RjPoNlWJKsa4tZHo47Y4yCl+htr4tw/AYutOeClKPp1qAlHiXIR4xKzQu0vUvZVqkIcFO9/8ZtTOq7Bg0732ETWkDWFLhb7MVv4zfrDc21pCLKFEELFcGJiDM8psPRZbzOoeIsHYO8sNBnP0IteSq6N0wcAXb1NUP6ShPJjp4g/0yQP7gL2MQy6Wb2aF7W8a6Qg4cuijv+wkVxCYjcCaYP7yC14oQNA8rMSmzTnm3S8qiLxJJcstpmpHPEN5WyKY6KvvrX+ktrGBTFnD0mRKNi1Kxlbxvr2ugPm63Qtr2u2UijsUbyFkDiafc7q4PbcYa0e2Ri+n/78RrPzenO0/mHF9wBXdcpsEoV1/4Fo7p7M51LF0Ff07Xuntp0DX8nAhRdzUEezHZ1g9Rudw4Mw74UcveTn2WHYfPtMOz4J2kYtpRGSUuRFGY8HTV01gCe+6MZkqUjHQsigbYPCPEr1pGF2NuIJMOxLuo+ngyb0dh4Go1J1JbwdkOgNpeu7YuNomjK6rvGYnXxLneRaJxh3UMdWbo=
*/