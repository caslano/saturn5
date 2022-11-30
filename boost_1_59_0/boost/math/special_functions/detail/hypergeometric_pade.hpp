
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_PADE_HPP
#define BOOST_MATH_HYPERGEOMETRIC_PADE_HPP

  namespace boost{ namespace math{ namespace detail{

  // Luke: C ---------- SUBROUTINE R1F1P(CP, Z, A, B, N) ----------
  // Luke: C ----- PADE APPROXIMATION OF 1F1( 1 ; CP ; -Z ) -------
  template <class T, class Policy>
  inline T hypergeometric_1F1_pade(const T& cp, const T& zp, const Policy& )
  {
    BOOST_MATH_STD_USING

    static const T one = T(1);

    // Luke: C ------------- INITIALIZATION -------------
    const T z = -zp;
    const T zz = z * z;
    T b0 = one;
    T a0 = one;
    T xi1 = one;
    T ct1 = cp + one;
    T cp1 = cp - one;

    T b1 = one + (z / ct1);
    T a1 = b1 - (z / cp);

    const unsigned max_iterations = boost::math::policies::get_max_series_iterations<Policy>();

    T b2 = T(0), a2 = T(0);
    T result = T(0), prev_result;

    for (unsigned k = 1; k < max_iterations; ++k)
    {
      // Luke: C ----- CALCULATION OF THE MULTIPLIERS -----
      // Luke: C ----------- FOR THE RECURSION ------------
      const T ct2 = ct1 * ct1;
      const T g1 = one + ((cp1 / (ct2 + ct1 + ct1)) * z);
      const T g2 = ((xi1 / (ct2 - one)) * ((xi1 + cp1) / ct2)) * zz;

      // Luke: C ------- THE RECURRENCE RELATIONS ---------
      // Luke: C ------------ ARE AS FOLLOWS --------------
      b2 = (g1 * b1) + (g2 * b0);
      a2 = (g1 * a1) + (g2 * a0);

      prev_result = result;
      result = a2 / b2;

      // condition for interruption
      if ((fabs(result) * boost::math::tools::epsilon<T>()) > fabs(result - prev_result))
        break;

      b0 = b1; b1 = b2;
      a0 = a1; a1 = a2;

      ct1 += 2;
      xi1 += 1;
    }

    return a2 / b2;
  }

  // Luke: C -------- SUBROUTINE R2F1P(BP, CP, Z, A, B, N) --------
  // Luke: C ---- PADE APPROXIMATION OF 2F1( 1 , BP; CP ; -Z ) ----
  template <class T, class Policy>
  inline T hypergeometric_2F1_pade(const T& bp, const T& cp, const T& zp, const Policy&)
  {
    BOOST_MATH_STD_USING

    static const T one = T(1);

    // Luke: C ---------- INITIALIZATION -----------
    const T z = -zp;
    const T zz = z * z;
    T b0 = one;
    T a0 = one;
    T xi1 = one;
    T ct1 = cp;
    const T b1c1 = (cp - one) * (bp - one);

    T b1 = one + ((z / (cp + one)) * (bp + one));
    T a1 = b1 - ((bp / cp) * z);

    const unsigned max_iterations = boost::math::policies::get_max_series_iterations<Policy>();

    T b2 = T(0), a2 = T(0);
    T result = T(0), prev_result = a1 / b1;

    for (unsigned k = 1; k < max_iterations; ++k)
    {
      // Luke: C ----- CALCULATION OF THE MULTIPLIERS -----
      // Luke: C ----------- FOR THE RECURSION ------------
      const T ct2 = ct1 + xi1;
      const T ct3 = ct2 * ct2;
      const T g2 = (((((ct1 / ct3) * (bp - ct1)) / (ct3 - one)) * xi1) * (bp + xi1)) * zz;
      ++xi1;
      const T g1 = one + (((((xi1 + xi1) * ct1) + b1c1) / (ct3 + ct2 + ct2)) * z);

      // Luke: C ------- THE RECURRENCE RELATIONS ---------
      // Luke: C ------------ ARE AS FOLLOWS --------------
      b2 = (g1 * b1) + (g2 * b0);
      a2 = (g1 * a1) + (g2 * a0);

      prev_result = result;
      result = a2 / b2;

      // condition for interruption
      if ((fabs(result) * boost::math::tools::epsilon<T>()) > fabs(result - prev_result))
        break;

      b0 = b1; b1 = b2;
      a0 = a1; a1 = a2;

      ++ct1;
    }

    return a2 / b2;
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_PADE_HPP

/* hypergeometric_pade.hpp
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
*/