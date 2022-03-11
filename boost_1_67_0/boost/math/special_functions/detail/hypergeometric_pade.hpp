
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
  inline T hypergeometric_2F1_pade(const T& bp, const T& cp, const T& zp, const Policy& pol)
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