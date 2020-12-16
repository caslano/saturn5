
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
dnurbFh8rP9d5tWfMdyOPLUoksP9aWCwPoxZtuuspcPzsn048dZcDpvMqcg6392SG12G7wl0dd5gdtYZLDTsq7oPfLcCh5Fn5iBPvsmL4+E+17BsgEJde9gqsz42fbvtLDmsMsayIwS9wXS2Q4x684FFbvd0Th2KbS0+ZKj2qX1wEOdUW26seh3Tx58lVw9iOustrrosQ4cxVvpdpLG+Rl7UuWtAJ2HBOv1Um9N4gAraJuCtSQvlYZvakqcr7gou08OtMjGC56CCg5+oC14HdGbO8p4V522NwV3AWZ2NtEdxuZgP67ZXnL7V3k8CnG4bcuVYjtQD0Rnf0y0+3YfxbCV/00Z4rkpT7T9cE78T/lzGmbNMAdq98j3GdXU/KHCjul+vJk3fhVNDYRb9VoX1REXoUtyLuUS+n3pG5b1nBELhVeoRcq6uRIivLCP+gyo+dv0krEaltJwzHIUYg4uQJ8jL9wWtfFW3Wgd/fhIEzCROK8OWxREqIe11/ULjLbn1uu81gmZD8spjiH4iRSJju2Vezn/p5WxUUjigElUkm2wNWBbke3w5z5U7Ck/i+mUPgh3qKfOkxOTl5btRRy1f2W36SZBEtYSZtHpRnx3Q+KCrwnq16lXKOp+UVSymQ3vgUUfts0q1GdYSry45gSFcRYYwz+uollfFDT2vHIUVbH8RZiQnDjiDDIM2Y6b2nxn1q3mNeinycl7YepQR/dgw3G/P7Oh7lLGfxFGMkiW3y6UnDluF8ztt5hemFb9czdhApcjc4C6FslHO9xp8kV+txlGjbDAGMTLmfX5O7/PIA5dq0qwxW4FsnVd5mm7cCEtpJUSeI6sQ/EzVumXeBxeM/q43oqjph6GLhwQjMTP6YCUmVeTl8X354xov7Od7SepDIaEXYbZvK0nkvFS/xeNaWcEOSH0/LbkQVQQ++QQmubwlncMl5FnS8gvduufDiKtVXHjCYHb44MakB7uBhw+KV2MOH8xeh6R875fLqJZGDfbyvUrT9zEJ8SIoJNQZ9+GnOLK+iym4ebm3jmvjNyw1oFUjD/lP9OAH3JovmSjPXS3PAPboq/UojXOmKTBhoeFZhJ1eXmY3r/cpjR9UjKh2FJfdjcnF41ln4+E7/UkvL+5B+dqLVe8zWhp1t97063HazJLoDXe2x5PRyX63N5lyCmq9P3j/S6jyGDaaDb8ZuN2eSEDP9WCe5zmjrRtxDXZm48SVUwf01HAEnP1hfwZPJoGfs4t55vL16+O6foijcr3me1VXlFfUF9yIRoFZNjf0cZcEaVCDhnMz7EF4aAPuioFe7k2wi7mtFjf0fCthGMKEEma8KGiSewpuM+6v3Ld2H42/6dZr1TSqNDzkF1KSsW9O+j1wTl4MLdHZpnScOqazrqZTBl0VwhH1OnSemc7DepBE3oGiRTdHmBi1x1M3dBkMy7VquV6t5GmNxr2hUSXiPb2hj/NaCZqjlMY577R/QvCiEBv6b0PXt2HcTOMAdLx4Jy/LlvtPGTNf2DBkJ6hUI9+ruMIWEa5IlB56Awplj+bnDX1+jstxsxFXyy40mniyDZqsMN+vv/rSqk0Ak20zbFRrTbc/FG+WgHaQz6NBzgOQ4lle3YOVfH7X+gwmvwjGCbhpFP5pBzpLRt9izx0fjI4fPrjdOdHncix1ddukGdeSsFkLOZ3sEX/g6822Rlh953gp13NdXVcGMYw+vxQzv10EFJlOXpetrl6XIAhqjVLgcxqTferC8vOKri57fimqlcDycYEz64dd6ENdieT1eKfGC9M0HFFrlsuezsvdwWnwnP/1rjHng5UMPiLf3Rk+bDh6BIiScNR3htiINN/8oqvr3TBpNMIgrAEfi90=
*/