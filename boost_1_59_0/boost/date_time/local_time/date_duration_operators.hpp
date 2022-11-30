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
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
*/