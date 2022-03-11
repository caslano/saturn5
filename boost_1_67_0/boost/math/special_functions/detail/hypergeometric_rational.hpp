///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_RATIONAL_HPP
#define BOOST_MATH_HYPERGEOMETRIC_RATIONAL_HPP

  #include <boost/array.hpp>

  namespace boost{ namespace math{ namespace detail{

  // Luke: C ------- SUBROUTINE R1F1P(AP, CP, Z, A, B, N) ---------
  // Luke: C --- RATIONAL APPROXIMATION OF 1F1( AP ; CP ; -Z ) ----
  template <class T, class Policy>
  inline T hypergeometric_1F1_rational(const T& ap, const T& cp, const T& zp, const Policy& )
  {
    BOOST_MATH_STD_USING

    static const T zero = T(0), one = T(1), two = T(2), three = T(3);

    // Luke: C ------------- INITIALIZATION -------------
    const T z = -zp;
    const T z2 = z / two;

    T ct1 = ap * (z / cp);
    T ct2 = z2 / (one + cp);
    T xn3 = zero;
    T xn2 = one;
    T xn1 = two;
    T xn0 = three;

    T b1 = one;
    T a1 = one;
    T b2 = one + ((one + ap) * (z2 / cp));
    T a2 = b2 - ct1;
    T b3 = one + ((two + b2) * (((two + ap) / three) * ct2));
    T a3 = b3 - ((one + ct2) * ct1);
    ct1 = three;

    const unsigned max_iterations = boost::math::policies::get_max_series_iterations<Policy>();

    T a4 = T(0), b4 = T(0);
    T result = T(0), prev_result = a3 / b3;

    for (unsigned k = 2; k < max_iterations; ++k)
    {
      // Luke: C ----- CALCULATION OF THE MULTIPLIERS -----
      // Luke: C ----------- FOR THE RECURSION ------------
      ct2 = (z2 / ct1) / (cp + xn1);
      const T g1 = one + (ct2 * (xn2 - ap));
      ct2 *= ((ap + xn1) / (cp + xn2));
      const T g2 = ct2 * ((cp - xn1) + (((ap + xn0) / (ct1 + two)) * z2));
      const T g3 = ((ct2 * z2) * (((z2 / ct1) / (ct1 - two)) * ((ap + xn2)) / (cp + xn3))) * (ap - xn2);

      // Luke: C ------- THE RECURRENCE RELATIONS ---------
      // Luke: C ------------ ARE AS FOLLOWS --------------
      b4 = (g1 * b3) + (g2 * b2) + (g3 * b1);
      a4 = (g1 * a3) + (g2 * a2) + (g3 * a1);

      prev_result = result;
      result = a4 / b4;

      // condition for interruption
      if ((fabs(result) * boost::math::tools::epsilon<T>()) > fabs(result - prev_result) / fabs(result))
        break;

      b1 = b2; b2 = b3; b3 = b4;
      a1 = a2; a2 = a3; a3 = a4;

      xn3 = xn2; 
      xn2 = xn1; 
      xn1 = xn0; 
      xn0 += 1;
      ct1 += two;
    }

    return result;
  }

  // Luke: C ----- SUBROUTINE R2F1P(AB, BP, CP, Z, A, B, N) -------
  // Luke: C -- RATIONAL APPROXIMATION OF 2F1( AB , BP; CP ; -Z ) -
  template <class T, class Policy>
  inline T hypergeometric_2F1_rational(const T& ap, const T& bp, const T& cp, const T& zp, const unsigned n, const Policy& )
  {
    BOOST_MATH_STD_USING

    static const T one = T(1), two = T(2), three = T(3), four = T(4),
                   six = T(6), half_7 = T(3.5), half_3 = T(1.5), forth_3 = T(0.75);

    // Luke: C ------------- INITIALIZATION -------------
    const T z = -zp;
    const T z2 = z / two;

    T sabz = (ap + bp) * z;
    const T ab = ap * bp;
    const T abz = ab * z;
    const T abz1 = z + (abz + sabz);
    const T abz2 = abz1 + (sabz + (three * z));
    const T cp1 = cp + one;
    const T ct1 = cp1 + cp1;

    T b1 = one;
    T a1 = one;
    T b2 = one + (abz1 / (cp + cp));
    T a2 = b2 - (abz / cp);
    T b3 = one + ((abz2 / ct1) * (one + (abz1 / ((-six) + (three * ct1)))));
    T a3 = b3 - ((abz / cp) * (one + ((abz2 - abz1) / ct1)));
    sabz /= four;

    const T abz1_div_4 = abz1 / four;
    const T cp1_inc = cp1 + one;
    const T cp1_mul_cp1_inc = cp1 * cp1_inc;

    boost::array<T, 9u> d = {{
      ((half_7 - ab) * z2) - sabz,
      abz1_div_4,
      abz1_div_4 - (two * sabz),
      cp1_inc,
      cp1_mul_cp1_inc,
      cp * cp1_mul_cp1_inc,
      half_3,
      forth_3,
      forth_3 * z
    }};

    T xi = three;
    T a4 = T(0), b4 = T(0);
    for (unsigned k = 2; k < n; ++k)
    {
      // Luke: C ----- CALCULATION OF THE MULTIPLIERS -----
      // Luke: C ----------- FOR THE RECURSION ------------
      T g3 = (d[2] / d[7]) * (d[1] / d[5]);
      d[1] += d[8] + sabz;
      d[2] += d[8] - sabz;
      g3 *= d[1] / d[6];
      T g1 = one + (((d[1] + d[0]) / d[6]) / d[3]);
      T g2 = (d[1] / d[4]) / d[6];
      d[7] += two * d[6];
      ++d[6];
      g2 *= cp1 - (xi + ((d[2] + d[0]) / d[6]));

      // Luke: C ------- THE RECURRENCE RELATIONS ---------
      // Luke: C ------------ ARE AS FOLLOWS --------------
      b4 = (g1 * b3) + (g2 * b2) + (g3 * b1);
      a4 = (g1 * a3) + (g2 * a2) + (g3 * a1);
      b1 = b2; b2 = b3; b3 = b4;
      a1 = a2; a2 = a3; a3 = a4;

      d[8] += z2;
      d[0] += two * d[8];
      d[5] += three * d[4];
      d[4] += two * d[3];
      ++d[3];
      ++xi;
    }

    return a4 / b4;
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_RATIONAL_HPP

/* hypergeometric_rational.hpp
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
*/