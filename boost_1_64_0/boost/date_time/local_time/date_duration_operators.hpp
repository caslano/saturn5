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
uI48fpN5iiu+zx+Ar89hKNCFyf0jq1YaJmLXL8otOgx13DjESF03kyKXokdI/4PQDwwBIT5X8EqXVtO69iZkGcYkkhWbVQ/JURe4XnpNjhBvuBvlORYDtAjACbvkgDnRRE9aw3+lBqZ5pbTleVRxDtqB60vlpQ4wkTmNrDCpTbyTQGPafxGc1E74FIu6IbXY/nCdMeUMaTI2BH77ms6vP1QvtwukpBsxzpCmWRVbhaU4hDXJhrrQ9/JuakFuApLjV7Sxj1fE9wuaQZwDot5taJYoW7JK/zNuh5T9dWBPR4+7DyKTIx2m3QG+SxtcdCgU00ILQ8phk5nK1lKDMBuoypahim2nckxSmdCLkZUUTfkpE9r4VDxGAqRp3ZxduS3DeE77FpZufseI3aKuWJCaIyn5b1ZBy25toaQawBtu9Vx4MLXLQ4J7AP3UgX9RL5iwQM3LmLefQ12Z0cywfRcpQdSlP0S8ib3MZm/i44vplWQZ8TjY0MBFKW+osmvMVKPl6IK8tosWUHW7BCjE5z5Kyy1evXKmn7MtmzlXG7L1Qg2c7W7H10hJ4zBYEA==
*/