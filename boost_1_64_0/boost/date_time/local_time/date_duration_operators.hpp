#ifndef LOCAL_TIME_DATE_DURATION_OPERATORS_HPP___
#define LOCAL_TIME_DATE_DURATION_OPERATORS_HPP___
                                                                                
/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or 
 * http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/greg_duration_types.hpp"
#include "boost/date_time/local_time/local_date_time.hpp"

namespace boost {
namespace local_time {
  
  /*!@file date_duration_operators.hpp Operators for local_date_time and 
   * optional gregorian types. Operators use snap-to-end-of-month behavior. 
   * Further details on this behavior can be found in reference for 
   * date_time/date_duration_types.hpp and documentation for 
   * month and year iterators.
   */
 

  /*! Adds a months object and a local_date_time. Result will be same 
   * day-of-month as local_date_time unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline
  local_date_time 
  operator+(const local_date_time& t, const boost::gregorian::months& m)
  {
    return t + m.get_offset(t.utc_time().date());
  }
  
  /*! Adds a months object to a local_date_time. Result will be same 
   * day-of-month as local_date_time unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline
  local_date_time 
  operator+=(local_date_time& t, const boost::gregorian::months& m)
  {
    return t += m.get_offset(t.utc_time().date());
  }

  /*! Subtracts a months object and a local_date_time. Result will be same 
   * day-of-month as local_date_time unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline
  local_date_time 
  operator-(const local_date_time& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + m.get_neg_offset(t.utc_time().date());
  }
  
  /*! Subtracts a months object from a local_date_time. Result will be same 
   * day-of-month as local_date_time unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline
  local_date_time 
  operator-=(local_date_time& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += m.get_neg_offset(t.utc_time().date());
  }

  // local_date_time & years
  
  /*! Adds a years object and a local_date_time. Result will be same 
   * month and day-of-month as local_date_time unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline
  local_date_time 
  operator+(const local_date_time& t, const boost::gregorian::years& y)
  {
    return t + y.get_offset(t.utc_time().date());
  }

  /*! Adds a years object to a local_date_time. Result will be same 
   * month and day-of-month as local_date_time unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline
  local_date_time 
  operator+=(local_date_time& t, const boost::gregorian::years& y)
  {
    return t += y.get_offset(t.utc_time().date());
  }

  /*! Subtracts a years object and a local_date_time. Result will be same 
   * month and day-of-month as local_date_time unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline
  local_date_time 
  operator-(const local_date_time& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + y.get_neg_offset(t.utc_time().date());
  }

  /*! Subtracts a years object from a local_date_time. Result will be same 
   * month and day-of-month as local_date_time unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline
  local_date_time 
  operator-=(local_date_time& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += y.get_neg_offset(t.utc_time().date());
  }


}} // namespaces

#endif // LOCAL_TIME_DATE_DURATION_OPERATORS_HPP___

/* date_duration_operators.hpp
+LpKzCnXIH4sWsQ1WIyaM8EmXaS2eJsp/5phlb8e/+zBndB2txPaw3gLrEtmD3iXEeDC2uV4xqNUK9Xv6C5KVZXlqmpdllHkkAuwsrYzg0xzSYzJRRZzxj3rR9noBqEp1jB3ZGVdJlq1FKss3N1UBlpdZT45VRk29Rei+oOFoclDDIZJWZ9as6wdqu8OuabtVzRJ73Hij+1s2LoGeETFU4v6NOkbcnnrFiQ7/2z9vsZejnaJnnuesubn7s/WXCyODOpMoVQKTcobSmY2DvAvlmjb0UW7g8Ma9vn+kD+LNmmV9AyP7K59LJgkygaAlbXLSOGMgXF+PGk7OzLa9nIuwABTjX1CxYzrXm92Y7t460fcbmFBJWH22Q4HclaWKRLOuFHblYe1WZwNbw79086GAf9dycT9qXF2NpCl9TZkMOY8bfrvBvwCoIV209Acef6btvf7GY9ZfqXlezrz46IAyyxYJpzTDUuUVYKKZyY748G/fWAh5zLTMPwUhKe/MhmEw6tSPBWzA/JAi4mHri+cJCFqx5lLsYyAIHqtjhkbAq3vAkKToDdwSKEjKOjsffu2O7obe4F1eJxsR3dn7NgGD9kzuHcF3idh6NSHSBP2srFNiJ1Csa1RCB/UgDlVBCB+t7j8vnk++H1+ML+wy+/MMdhYYAqg7QvQa5CwnH8xGqQWNGJJJQMmrZOA08g4GeAcGqRlELIWBxlawE0RbhV65uUUcD5rHFPdiO0bBRy+hNjZAneSBFY8AfvDTy9K5NmIRDdvY77AMRnLqW28BTYwsLk4DhUCMAVdZ1/rvuxxfDPS9tAi0YCD8YSoKsXpJuuXdTz1vvDGjsL7pmykmc2UntwGbD9DS22SwoIuZpzDHtnmLiPV8PXI0nUD1WyQUsmk/GA7wpLstzz1TFIyrpGqJY8FmJo1hMm6+ug5Z0pcRz6U63VJ5bBmSbQuFloGwV3fo8WePH6rhFg2X7A31rhTRAGaujmygdZLH1R4BESffZQQ7c8L070s05gwzcxNRUvpDSQUYkIfRlGguJyYV01xa7EUOKa/9JwLfSBvo6XfFZEHxigZLtITdjSnTlVO2WAif89wNEyqL6TNRezDurDVQbNkbPjsYD7FtyBBhxMqTeGi6KcDekHdlV0YaOGWucwbpdSancIEKbVnK6zVsapnxvZmID5tAw9Sq03a2cgMCoPjoqAnvJqFF/YtQGgwkvdTnVbLa2GFNPQmdwtt13IqOOelMFr5/MRMdDBUMeTGXMkPrDFWENYeBtgMkmifxZsQaiZzJ2IRXHZTtBMcxpEX41m1MSsiNMdFk2XC4n5KTWU5Eki6DHugtVVdUyPw3aI3xqdkT+Ey3lMot94LsL8UGA2qx47rXGRogen+4OTveziEPofgKA/GX054ztXs5eDtzPJKNODA420svHXQ7izsBcpkAa1iTaLY0mdwJJlsodZXDIOlTqCvQAVRvYEWhHjnCyNBVkBlIyEA1QogyTUA6WUvotDRey0ZxHsZedYl9AVa54bPmCD3bHlvpgSOzl15nEJMhNISLNISIKQkQFjuR2rBLk0hiGipEwJKJQxs73TDpx9cGtNWKyr2mlYxgEHtyxV95wak0vp7WGmsuoCUEhchrZQIn2GGkaInTJWvBwN70GRZGQlkgaS0EKG+g015NkCdTFfETZ1G79LnRp3D4dyQy0TnAokNCdm/lXyZ6PgNSPO4aqCPi4XNz8z1CEEvM7JuHNkjbF9QxbFr01PgNPsMbHcOoOqkrDuDyqLoHfVZOI2u+hvv4HY++3M4tWUo0zAwwKvmF5K4h8amZxnefAOOeAm8XEEjsTchJSL49SbjHYFhZYdXs/Pqz5CGRyQ=
*/