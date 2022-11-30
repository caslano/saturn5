#ifndef _DATE_TIME_WRAPPING_INT_HPP__
#define _DATE_TIME_WRAPPING_INT_HPP__

/* Copyright (c) 2002,2003,2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/config.hpp"

namespace boost {
namespace date_time {

//! A wrapping integer used to support time durations (WARNING: only instantiate with a signed type)
/*! In composite date and time types this type is used to
 *  wrap at the day boundary.
 *  Ex:
 *  A wrapping_int<short, 10> will roll over after nine, and
 *  roll under below zero. This gives a range of [0,9]
 *
 * NOTE: it is strongly recommended that wrapping_int2 be used
 * instead of wrapping_int as wrapping_int is to be depricated
 * at some point soon.
 *
 * Also Note that warnings will occur if instantiated with an
 * unsigned type. Only a signed type should be used!
 */
template<typename int_type_, int_type_ wrap_val>
class wrapping_int {
public:
  typedef int_type_ int_type;
  //typedef overflow_type_ overflow_type;
  static BOOST_CONSTEXPR int_type wrap_value() {return wrap_val;}
  //!Add, return true if wrapped
  BOOST_CXX14_CONSTEXPR wrapping_int(int_type v) : value_(v) {}
  //! Explicit converion method
  BOOST_CONSTEXPR int_type as_int()   const   {return value_;}
  BOOST_CONSTEXPR operator int_type() const   {return value_;}
  //!Add, return number of wraps performed
  /*! The sign of the returned value will indicate which direction the
   * wraps went. Ex: add a negative number and wrapping under could occur,
   * this would be indicated by a negative return value. If wrapping over
   * took place, a positive value would be returned */
  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT add(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_val));
    IntT overflow = static_cast<IntT>(v / (wrap_val));
    value_ = static_cast<int_type>(value_ + remainder);
    return calculate_wrap(overflow);
  }
  //! Subtract will return '+d' if wrapping under took place ('d' is the number of wraps)
  /*! The sign of the returned value will indicate which direction the
   * wraps went (positive indicates wrap under, negative indicates wrap over).
   * Ex: subtract a negative number and wrapping over could
   * occur, this would be indicated by a negative return value. If
   * wrapping under took place, a positive value would be returned. */
  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT subtract(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_val));
    IntT underflow = static_cast<IntT>(-(v / (wrap_val)));
    value_ = static_cast<int_type>(value_ - remainder);
    return calculate_wrap(underflow) * -1;
  }
private:
  int_type value_;

  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT calculate_wrap(IntT wrap)
  {
    if ((value_) >= wrap_val)
    {
      ++wrap;
      value_ -= (wrap_val);
    }
    else if(value_ < 0)
    {
      --wrap;
      value_ += (wrap_val);
    }
    return wrap;
  }

};


//! A wrapping integer used to wrap around at the top (WARNING: only instantiate with a signed type)
/*! Bad name, quick impl to fix a bug -- fix later!!
 *  This allows the wrap to restart at a value other than 0.
 */
template<typename int_type_, int_type_ wrap_min, int_type_ wrap_max>
class wrapping_int2 {
public:
  typedef int_type_ int_type;
  static BOOST_CONSTEXPR int_type wrap_value() {return wrap_max;}
  static BOOST_CONSTEXPR int_type min_value()  {return wrap_min;}
  /*! If initializing value is out of range of [wrap_min, wrap_max],
   * value will be initialized to closest of min or max */
  BOOST_CXX14_CONSTEXPR wrapping_int2(int_type v) : value_(v) {
    if(value_ < wrap_min)
    {
      value_ = wrap_min;
    }
    if(value_ > wrap_max)
    {
      value_ = wrap_max;
    }
  }
  //! Explicit converion method
  BOOST_CONSTEXPR int_type as_int()   const   {return value_;}
  BOOST_CONSTEXPR operator int_type() const {return value_;}
  //!Add, return number of wraps performed
  /*! The sign of the returned value will indicate which direction the
   * wraps went. Ex: add a negative number and wrapping under could occur,
   * this would be indicated by a negative return value. If wrapping over
   * took place, a positive value would be returned */
  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT add(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_max - wrap_min + 1));
    IntT overflow = static_cast<IntT>(v / (wrap_max - wrap_min + 1));
    value_ = static_cast<int_type>(value_ + remainder);
    return calculate_wrap(overflow);
  }
  //! Subtract will return '-d' if wrapping under took place ('d' is the number of wraps)
  /*! The sign of the returned value will indicate which direction the
   * wraps went. Ex: subtract a negative number and wrapping over could
   * occur, this would be indicated by a positive return value. If
   * wrapping under took place, a negative value would be returned */
  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT subtract(IntT v)
  {
    int_type remainder = static_cast<int_type>(v % (wrap_max - wrap_min + 1));
    IntT underflow = static_cast<IntT>(-(v / (wrap_max - wrap_min + 1)));
    value_ = static_cast<int_type>(value_ - remainder);
    return calculate_wrap(underflow);
  }

private:
  int_type value_;

  template< typename IntT >
  BOOST_CXX14_CONSTEXPR IntT calculate_wrap(IntT wrap)
  {
    if ((value_) > wrap_max)
    {
      ++wrap;
      value_ -= (wrap_max - wrap_min + 1);
    }
    else if((value_) < wrap_min)
    {
      --wrap;
      value_ += (wrap_max - wrap_min + 1);
    }
    return wrap;
  }
};



} } //namespace date_time



#endif


/* wrapping_int.hpp
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
*/