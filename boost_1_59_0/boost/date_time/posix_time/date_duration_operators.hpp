#ifndef DATE_DURATION_OPERATORS_HPP___
#define DATE_DURATION_OPERATORS_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Subject to the Boost Software License, Version 1.0. 
 * (See accompanying file LICENSE_1_0.txt or 
 * http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/greg_duration_types.hpp"
#include "boost/date_time/posix_time/ptime.hpp"

namespace boost {
namespace posix_time {
  
  /*!@file date_duration_operators.hpp Operators for ptime and 
   * optional gregorian types. Operators use snap-to-end-of-month behavior. 
   * Further details on this behavior can be found in reference for 
   * date_time/date_duration_types.hpp and documentation for 
   * month and year iterators.
   */
 

  /*! Adds a months object and a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+(const ptime& t, const boost::gregorian::months& m)
  {
    return t + m.get_offset(t.date());
  }
  
  /*! Adds a months object to a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+=(ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += m.get_offset(t.date());
  }

  /*! Subtracts a months object and a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-(const ptime& t, const boost::gregorian::months& m)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + m.get_neg_offset(t.date());
  }
  
  /*! Subtracts a months object from a ptime. Result will be same 
   * day-of-month as ptime unless original day was the last day of month.
   * see date_time::months_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-=(ptime& t, const boost::gregorian::months& m)
  {
    return t += m.get_neg_offset(t.date());
  }

  // ptime & years
  
  /*! Adds a years object and a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+(const ptime& t, const boost::gregorian::years& y)
  {
    return t + y.get_offset(t.date());
  }

  /*! Adds a years object to a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator+=(ptime& t, const boost::gregorian::years& y)
  {
    return t += y.get_offset(t.date());
  }

  /*! Subtracts a years object and a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-(const ptime& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t + y.get_neg_offset(t.date());
  }

  /*! Subtracts a years object from a ptime. Result will be same 
   * month and day-of-month as ptime unless original day was the 
   * last day of month. see date_time::years_duration for more details */
  inline BOOST_CXX14_CONSTEXPR
  ptime 
  operator-=(ptime& t, const boost::gregorian::years& y)
  {
    // get_neg_offset returns a negative duration, so we add
    return t += y.get_neg_offset(t.date());
  }

}} // namespaces

#endif // DATE_DURATION_OPERATORS_HPP___

/* date_duration_operators.hpp
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
*/