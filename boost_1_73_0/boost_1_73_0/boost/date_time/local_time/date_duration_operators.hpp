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
+cyzLTzao2Ou7u4x1q6LGvkyHJFWFABfik9y20z2sRVK1tQlNy37XmDPqy5CBaGiXfB1OwFwDrD4dnaZDCaRFbc3cu7J8tmmbR6MgmeF0GZtmgfLzNhxsDiN+Uzg8TakgZZVyiAGj9keT2dsx1mUeeEmjxp6/gRz5WsU2fosPz+igk2GR4Gx7VHgR54fhf+jEt2u+IDu6jA1TlzJO6j63yP4byAxiL2SMpU/pNQOwlML5a39Ro1upqzGxx/G09n43XQ2jc6c8XZc2YmDykDwyipwctuWTMuh++tv7n7XSgsvWi58+jCeLT1nIQ1+oWibzouD98zSg1jdr57OYOm/94OPfhzYs4iN0e9d2EHoeTSehQEO5XeL2zOQG/546s0mIQ3Q+Kj23qMvFjdDonvQxbq7O7cOt4tZI+X9VZ4dsaqgAV4eOP8BUEsDBAoAAAAIAC1nSlJaCzWtKQUAAFQLAAA3AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9IVFRQUFJPWFlUVU5ORUwuM1VUBQABtkgkYK1VXW/aSBR996+4Yl+gIiZpIvVzqyXEadhSQNi0RUKyBnscT2M8Xs84BG33v++ZsSkhadU8FAS2x3PP/Tr3jLts0bPf9nFc
*/