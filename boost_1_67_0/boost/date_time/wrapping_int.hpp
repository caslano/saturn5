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