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
6kWJk/C+fWNKieWVcfX3QKBRpa5cyI/eCATUqsqzjuTdZSDlKLZLCy2VC/WQ/eXYRmmyj83UEpgihs2aNgnOBk/2alfBMwAa0RB4KuGZA085PDUQ3g7+D4T/D08h+S8JfniVRXyLpIPw8yWYvxM3/U/+1Pv/X6HxgdtlXnCLR57nsoefyPC0NOckD4gktvDFEfDHuyPg1VGrjAx+ORW0aGqA5GlZrtmP88tlVqVx/9kSXI3X74Z30Q3Gt5NGdeegpXgt39/VsnCI0QmonRfiW3HwjNm83L1meYNyVQMLdbcq80ee2ns0dbri0qBD+lRvzaaPwjSRkMYF236dBwNlak0wgegFtoEUpkireXia0Mk1F6zH3zuC1uPyu0MX+/X5iLUHYX1uWZ78usYqc79slrmXiE/e33uQP1nuhm925B95CWv5dVzVKkPGDCgL9paGKzh5q8YTIP6z7XhX8O/GasrbgHSUEU1g577bEJanz0ceIU54nwTBUm4/UPl8X+ffVxu0AtSfNFPmfgtlbougjHAc5NPdUSdQi+1Z6Cu/whzFLZlcI7fWd4khqwt80pteOP2DwlwtIj+itksQXmaFILg4boq7m6i/CMmuppaoIq/Q3X44aA3SMObnKlXW5da1ByLovlHv+xzpp+rKa1DYvXDHguqrObeZhwsuF7+NoxIegkKnBhx7PcTymDVDLytPZpdHYwcPO6IQX/CsOmxCIzh5nsz8+22kgBhgop3tgFIqbCH5vb3yrq69VasHR8U6izxQBV9rG4+HNrB23/cbhVbJRp7P6olEVqeMdMm5Zn/yN6+nldHub6vEatrj0pePfKwnvIHNLZJGd9KP9JT8lRwA1d1mnL3zyKWRR18aefhcz1IAwmeV+K8+ahw9++9jwqT/dO1L/8k6T9v0SF0fU9fLYKb5IruR8y8rD8L8YLtf//YKeZ546Rn79oN7RoQf3IWTzCdqUx6N8APcv7YhVj+49v5/V5jOF6h+fH/ou8/6v9I3ov6f/s1c//MWRvjxvfulmOtvrfrVLyr6gus99vqCi5p+Hljpf+aC3C9az8MWiiwnBX1C9L8s9ZaVmiG9vnEtS6/Jd5H0+sOdeo/kau10KRe9l8hjqQFcrulSWUAcS72BvoxjqSX2x1ID8lhqIPJY6nEULuSsbLWsxuQnotZKqPZGeN6D50x4xsLzMTyay+t2e537xXk2HfRfDPs1WvT9GrZ/qd5v+5fZB2z/Yj6PeCpXIVgwn+WNX59o6nnEQc83WZ+++FBlPDaG49XLLPaBlROy8W95D7IPPAGnMLISvJKsBEc0p5Wg3XnPE5bZnvd8uLdy3vO7WVHOe6rzzc4XDsJ8EzH+vaCMfxO+53ILl5MwmDttJ/xjLTAOhdPxk4fFmUWJpaBE7rYlODrYkdOAAV2pfijsZgas41zr4SiLncoSm4xv/OGsbxwitwtnJr+mD71t1wSv/RHSbKoJQlLOrHJ6w/6Yl0b9KV6ASp8X9knnL5f2SaXr8MwB/OmkwZ/OLvhzuIt9+uQEs34Q/n3A9Rq8Q2Qe/jlBY0t5jusavPDzjhCSJkMCwQJLSHHweAghAygp+Rd8y72U1cdotTRtTcOB+tOxvd9k2FJpaVYiRadiSyMwG6uUpk7tLK/JmVSNMFq5uLxkIicBtNDMBRoKpSTcNgQDn3XkZNhgcAOTmwq7gJJZrqc8THdMZRs3hGfLwFJpFQavoAIuxfxSp07VFZYQSmiwOZg65yXznEfmmwnkrYdrAi/GtQXWEmirljDh+qaII7d29fObK4X3XHzHgtDo9nTPxYgOaFh3Qy/cY22ccqWScvGfMuUkXBzGsnLm5p3/GVdlWdsX3s8=
*/