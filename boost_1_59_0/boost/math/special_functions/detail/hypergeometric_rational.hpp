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

  #include <array>

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

    std::array<T, 9u> d = {{
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