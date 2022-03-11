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