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
p88DL7nxg7+HzeErsAt8DY6Bu+FV8E1N/1vwfrhX0/83uA1+AnfAj+BTav+M2MefM9/SeDT3ec5sJ8+ZmGE+7ARlXUrA0Llp/PU58xRkiGvvli/1IhumU74zYSZcClvod69W8G7YBt4Hj4HbYXu4C3aAr8DO8CPYBR5Q8yE4FzoO9Q6mwG6wKewPC+BAeAwcBNvDwbALPB52hyfAXnAI7ANPhIPhSXAIHApPhkXwcTgcPglH
*/