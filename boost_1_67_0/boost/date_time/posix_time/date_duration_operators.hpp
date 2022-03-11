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