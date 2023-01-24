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
4hlzwQb5KmdAR5G4qzbyPQr+tROuBob3jCwT167cgjwwAzTohUasBAT39xQmV/7AlDIcUAsIaDBUAYEiQ4jhTkunj0BT78OD6kiiEQVPLvbAanPbSyKPqQbm5AHPRgqyb+2Rt7//Lpm92XVXIUZ6yqpmkggV/evSWXb658Yliu8mW2xJ12jNQBvYkpfX2tY2YnbIwWorkBmN/uuvpJ1VTBxcFoDRooWfosWlRQpFihV3KEUGKW7F3V0HKe7uVqDA4lrctcDg7u5MgRkGBoZZy+6+7Gaz2eQkN/flvt2TfDnnO2f1OUhHEO8vqcOqvKRYqjDrvhBXRfv8UCnTcJMZ47/z2X8MC2q1scQ8JNZfy2cskZTGp5R/qY71of6vyi0v71/vam7O1m6W7u7/bL8FBhjoeErA9NwcRhXzhlRSm23TSj1TBLzeDLvmCUs4KC5ZUJY7kcxJrwlxLcUiYjiyy8s/OuGMlbCxV1nN8ePr8vcvcVMs0off2DtmvmxtaHh5V8L9wgFzIAjV3PHBwTwtBtwN67bWS9ea2E9MJ4QFgPxho+2wp7bjTf+r9J778PTpHvAc3FlNT1jSE6LRkHymdJYVztjyB6vFQ5lZg40OObDAWOt0VBLztnUtR0FwKwCUiUIVHN/HvKPxldfltUu7nEGBvjpwUdRRAoCUmCf6jKZ8oybx9reAzZ8C2CpylpLWH47aTTaW5zjOuCaO
*/