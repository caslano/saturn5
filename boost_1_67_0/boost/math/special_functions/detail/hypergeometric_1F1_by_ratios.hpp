
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HYPERGEOMETRIC_1F1_BY_RATIOS_HPP_
#define BOOST_HYPERGEOMETRIC_1F1_BY_RATIOS_HPP_

#include <boost/math/tools/recurrence.hpp>
#include <boost/math/policies/error_handling.hpp>

  namespace boost { namespace math { namespace detail {

     template <class T, class Policy>
     T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling);

     /*
      Evaluation by method of ratios for domain b < 0 < a,z

      We first convert the recurrence relation into a ratio
      of M(a+1, b+1, z) / M(a, b, z) using Shintan's equivalence
      between solving a recurrence relation using Miller's method
      and continued fractions.  The continued fraction is VERY rapid
      to converge (typically < 10 terms), but may converge to entirely
      the wrong value if we're in a bad part of the domain.  Strangely
      it seems to matter not whether we use recurrence on a, b or a and b
      they all work or not work about the same, so we might as well make
      life easy for ourselves and use the a and b recurrence to avoid
      having to apply one extra recurrence to convert from an a or b
      recurrence to an a+b one.

      See: H. Shintan, Note on Miller's recurrence algorithm, J. Sci. Hiroshima Univ. Ser. A-I Math., 29 (1965), pp. 121-133.
      Also: Computational Aspects of Three Term Recurrence Relations, SIAM Review, January 1967.

      The following table lists by experiment, how large z can be in order to
      ensure the continued fraction converges to the correct value:

          a         b    max  z
         13,      -130,      22
         13,     -1300,     335
         13,    -13000,    3585
        130,      -130,       8
        130,     -1300,     263
        130,   - 13000,    3420
       1300,      -130,       1
       1300,     -1300,      90
       1300,    -13000,    2650
      13000,       -13,       -
      13000,      -130,       -
      13000,     -1300,      13
      13000,    -13000,     750

      So try z_limit = -b / (4 - 5 * sqrt(log(a)) * a / b);
      or     z_limit = -b / (4 - 5 * (log(a)) * a / b)  for a < 100
      
      This still isn't quite right for both a and b small, but we'll be using a Bessel approximation
      in that region anyway.

      Normalization using wronksian {1,2} from A&S 13.1.20 (also 13.1.12, 13.1.13):

      W{ M(a,b,z), z^(1-b)M(1+a-b, 2-b, z) } = (1-b)z^-b e^z

       = M(a,b,z) M2'(a,b,z) - M'(a,b,z) M2(a,b,z)
       = M(a,b,z) [(a-b+1)z^(1-b)/(2-b) M2(a+1,b+1,z) + (1-b)z^-b M2(a,b,z)] - a/b M(a+1,b+1,z) z^(1-b)M2(a,b,z)
       = M(a,b,z) [(a-b+1)z^(1-b)/(2-b) M2(a+1,b+1,z) + (1-b)z^-b M2(a,b,z)] - a/b R(a,b,z) M(a,b,z) z^(1-b)M2(a,b,z)
       = M(a,b,z) [(a-b+1)z^(1-b)/(2-b) M2(a+1,b+1,z) + (1-b)z^-b M2(a,b,z) - a/b R(a,b,z) z^(1-b)M2(a,b,z) ]
       so:
       (1-b)e^z = M(a,b,z) [(a-b+1)z/(2-b) M2(a+1,b+1,z) + (1-b) M2(a,b,z) - a/b z R(a,b,z) M2(a,b,z) ]

      */

     template <class T>
     inline bool is_in_hypergeometric_1F1_from_function_ratio_negative_b_region(const T& a, const T& b, const T& z)
     {
        BOOST_MATH_STD_USING
        if (a < 100)
           return z < -b / (4 - 5 * (log(a)) * a / b);
        else
           return z < -b / (4 - 5 * sqrt(log(a)) * a / b);
     }

     template <class T, class Policy>
     T hypergeometric_1F1_from_function_ratio_negative_b(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling, const T& ratio)
     {
        BOOST_MATH_STD_USING
        //
        // Let M2 = M(1+a-b, 2-b, z)
        // This is going to be a mighty big number:
        //
        int local_scaling = 0;
        T M2 = boost::math::detail::hypergeometric_1F1_imp(T(1 + a - b), T(2 - b), z, pol, local_scaling);
        log_scaling -= local_scaling; // all the M2 terms are in the denominator
        //
        // Since a, b and z are all likely to be large we need the Wronksian
        // calculation below to not overflow, so scale everything right down:
        //
        if (fabs(M2) > 1)
        {
           int s = itrunc(log(fabs(M2)));
           log_scaling -= s;  // M2 will be in the denominator, so subtract the scaling!
           local_scaling += s;
           M2 *= exp(T(-s));
        }
        //
        // Let M3 = M(1+a-b + 1, 2-b + 1, z)
        // we can get to this from the ratio which is cheaper to calculate:
        //
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T> coef2(1 + a - b + 1, 2 - b + 1, z);
        T M3 = boost::math::tools::function_ratio_from_backwards_recurrence(coef2, boost::math::policies::get_epsilon<T, Policy>(), max_iter) * M2;
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        //
        // Get the RHS of the Wronksian:
        //
        int fz = itrunc(z);
        log_scaling += fz;
        T rhs = (1 - b) * exp(z - fz);
        //
        // We need to divide that by:
        // [(a-b+1)z/(2-b) M2(a+1,b+1,z) + (1-b) M2(a,b,z) - a/b z^b R(a,b,z) M2(a,b,z) ]
        // Note that at this stage, both M3 and M2 are scaled by exp(local_scaling).
        //
        T lhs = (a - b + 1) * z * M3 / (2 - b) + (1 - b) * M2 - a * z * ratio * M2 / b;

        return rhs / lhs;
     }

     template <class T, class Policy>
     T hypergeometric_1F1_from_function_ratio_negative_b(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T> coef(a + 1, b + 1, z);
        T ratio = boost::math::tools::function_ratio_from_backwards_recurrence(coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        return hypergeometric_1F1_from_function_ratio_negative_b(a, b, z, pol, log_scaling, ratio);
     }
     //
     // And over again, this time via forwards recurrence when z is large enough:
     //
     template <class T>
     bool hypergeometric_1F1_is_in_forwards_recurence_for_negative_b_region(const T& a, const T& b, const T& z)
     {
        //
        // There's no easy relation between a, b and z that tells us whether we're in the region
        // where forwards recursion is stable, so use a lookup table, note that the minimum
        // permissible z-value is decreasing with a, and increasing with |b|:
        //
        static const float data[][3] = {
           {7.500e+00f, -7.500e+00f, 8.409e+00f },
           {7.500e+00f, -1.125e+01f, 8.409e+00f },
           {7.500e+00f, -1.688e+01f, 9.250e+00f },
           {7.500e+00f, -2.531e+01f, 1.119e+01f },
           {7.500e+00f, -3.797e+01f, 1.354e+01f },
           {7.500e+00f, -5.695e+01f, 1.983e+01f },
           {7.500e+00f, -8.543e+01f, 2.639e+01f },
           {7.500e+00f, -1.281e+02f, 3.864e+01f },
           {7.500e+00f, -1.922e+02f, 5.657e+01f },
           {7.500e+00f, -2.883e+02f, 8.283e+01f },
           {7.500e+00f, -4.325e+02f, 1.213e+02f },
           {7.500e+00f, -6.487e+02f, 1.953e+02f },
           {7.500e+00f, -9.731e+02f, 2.860e+02f },
           {7.500e+00f, -1.460e+03f, 4.187e+02f },
           {7.500e+00f, -2.189e+03f, 6.130e+02f },
           {7.500e+00f, -3.284e+03f, 9.872e+02f },
           {7.500e+00f, -4.926e+03f, 1.445e+03f },
           {7.500e+00f, -7.389e+03f, 2.116e+03f },
           {7.500e+00f, -1.108e+04f, 3.098e+03f },
           {7.500e+00f, -1.663e+04f, 4.990e+03f },
           {1.125e+01f, -7.500e+00f, 6.318e+00f },
           {1.125e+01f, -1.125e+01f, 6.950e+00f },
           {1.125e+01f, -1.688e+01f, 7.645e+00f },
           {1.125e+01f, -2.531e+01f, 9.250e+00f },
           {1.125e+01f, -3.797e+01f, 1.231e+01f },
           {1.125e+01f, -5.695e+01f, 1.639e+01f },
           {1.125e+01f, -8.543e+01f, 2.399e+01f },
           {1.125e+01f, -1.281e+02f, 3.513e+01f },
           {1.125e+01f, -1.922e+02f, 5.657e+01f },
           {1.125e+01f, -2.883e+02f, 8.283e+01f },
           {1.125e+01f, -4.325e+02f, 1.213e+02f },
           {1.125e+01f, -6.487e+02f, 1.776e+02f },
           {1.125e+01f, -9.731e+02f, 2.860e+02f },
           {1.125e+01f, -1.460e+03f, 4.187e+02f },
           {1.125e+01f, -2.189e+03f, 6.130e+02f },
           {1.125e+01f, -3.284e+03f, 9.872e+02f },
           {1.125e+01f, -4.926e+03f, 1.445e+03f },
           {1.125e+01f, -7.389e+03f, 2.116e+03f },
           {1.125e+01f, -1.108e+04f, 3.098e+03f },
           {1.125e+01f, -1.663e+04f, 4.990e+03f },
           {1.688e+01f, -7.500e+00f, 4.747e+00f },
           {1.688e+01f, -1.125e+01f, 5.222e+00f },
           {1.688e+01f, -1.688e+01f, 5.744e+00f },
           {1.688e+01f, -2.531e+01f, 7.645e+00f },
           {1.688e+01f, -3.797e+01f, 1.018e+01f },
           {1.688e+01f, -5.695e+01f, 1.490e+01f },
           {1.688e+01f, -8.543e+01f, 2.181e+01f },
           {1.688e+01f, -1.281e+02f, 3.193e+01f },
           {1.688e+01f, -1.922e+02f, 5.143e+01f },
           {1.688e+01f, -2.883e+02f, 7.530e+01f },
           {1.688e+01f, -4.325e+02f, 1.213e+02f },
           {1.688e+01f, -6.487e+02f, 1.776e+02f },
           {1.688e+01f, -9.731e+02f, 2.600e+02f },
           {1.688e+01f, -1.460e+03f, 4.187e+02f },
           {1.688e+01f, -2.189e+03f, 6.130e+02f },
           {1.688e+01f, -3.284e+03f, 9.872e+02f },
           {1.688e+01f, -4.926e+03f, 1.445e+03f },
           {1.688e+01f, -7.389e+03f, 2.116e+03f },
           {1.688e+01f, -1.108e+04f, 3.098e+03f },
           {1.688e+01f, -1.663e+04f, 4.990e+03f },
           {2.531e+01f, -7.500e+00f, 3.242e+00f },
           {2.531e+01f, -1.125e+01f, 3.566e+00f },
           {2.531e+01f, -1.688e+01f, 4.315e+00f },
           {2.531e+01f, -2.531e+01f, 5.744e+00f },
           {2.531e+01f, -3.797e+01f, 7.645e+00f },
           {2.531e+01f, -5.695e+01f, 1.231e+01f },
           {2.531e+01f, -8.543e+01f, 1.803e+01f },
           {2.531e+01f, -1.281e+02f, 2.903e+01f },
           {2.531e+01f, -1.922e+02f, 4.676e+01f },
           {2.531e+01f, -2.883e+02f, 6.845e+01f },
           {2.531e+01f, -4.325e+02f, 1.102e+02f },
           {2.531e+01f, -6.487e+02f, 1.776e+02f },
           {2.531e+01f, -9.731e+02f, 2.600e+02f },
           {2.531e+01f, -1.460e+03f, 4.187e+02f },
           {2.531e+01f, -2.189e+03f, 6.130e+02f },
           {2.531e+01f, -3.284e+03f, 8.974e+02f },
           {2.531e+01f, -4.926e+03f, 1.445e+03f },
           {2.531e+01f, -7.389e+03f, 2.116e+03f },
           {2.531e+01f, -1.108e+04f, 3.098e+03f },
           {2.531e+01f, -1.663e+04f, 4.990e+03f },
           {3.797e+01f, -7.500e+00f, 2.214e+00f },
           {3.797e+01f, -1.125e+01f, 2.679e+00f },
           {3.797e+01f, -1.688e+01f, 3.242e+00f },
           {3.797e+01f, -2.531e+01f, 4.315e+00f },
           {3.797e+01f, -3.797e+01f, 6.318e+00f },
           {3.797e+01f, -5.695e+01f, 9.250e+00f },
           {3.797e+01f, -8.543e+01f, 1.490e+01f },
           {3.797e+01f, -1.281e+02f, 2.399e+01f },
           {3.797e+01f, -1.922e+02f, 3.864e+01f },
           {3.797e+01f, -2.883e+02f, 6.223e+01f },
           {3.797e+01f, -4.325e+02f, 1.002e+02f },
           {3.797e+01f, -6.487e+02f, 1.614e+02f },
           {3.797e+01f, -9.731e+02f, 2.600e+02f },
           {3.797e+01f, -1.460e+03f, 3.806e+02f },
           {3.797e+01f, -2.189e+03f, 6.130e+02f },
           {3.797e+01f, -3.284e+03f, 8.974e+02f },
           {3.797e+01f, -4.926e+03f, 1.445e+03f },
           {3.797e+01f, -7.389e+03f, 2.116e+03f },
           {3.797e+01f, -1.108e+04f, 3.098e+03f },
           {3.797e+01f, -1.663e+04f, 4.990e+03f },
           {5.695e+01f, -7.500e+00f, 1.513e+00f },
           {5.695e+01f, -1.125e+01f, 1.830e+00f },
           {5.695e+01f, -1.688e+01f, 2.214e+00f },
           {5.695e+01f, -2.531e+01f, 3.242e+00f },
           {5.695e+01f, -3.797e+01f, 4.315e+00f },
           {5.695e+01f, -5.695e+01f, 7.645e+00f },
           {5.695e+01f, -8.543e+01f, 1.231e+01f },
           {5.695e+01f, -1.281e+02f, 1.983e+01f },
           {5.695e+01f, -1.922e+02f, 3.513e+01f },
           {5.695e+01f, -2.883e+02f, 5.657e+01f },
           {5.695e+01f, -4.325e+02f, 9.111e+01f },
           {5.695e+01f, -6.487e+02f, 1.467e+02f },
           {5.695e+01f, -9.731e+02f, 2.363e+02f },
           {5.695e+01f, -1.460e+03f, 3.806e+02f },
           {5.695e+01f, -2.189e+03f, 5.572e+02f },
           {5.695e+01f, -3.284e+03f, 8.974e+02f },
           {5.695e+01f, -4.926e+03f, 1.314e+03f },
           {5.695e+01f, -7.389e+03f, 2.116e+03f },
           {5.695e+01f, -1.108e+04f, 3.098e+03f },
           {5.695e+01f, -1.663e+04f, 4.990e+03f },
           {8.543e+01f, -7.500e+00f, 1.250e+00f },
           {8.543e+01f, -1.125e+01f, 1.250e+00f },
           {8.543e+01f, -1.688e+01f, 1.513e+00f },
           {8.543e+01f, -2.531e+01f, 2.214e+00f },
           {8.543e+01f, -3.797e+01f, 3.242e+00f },
           {8.543e+01f, -5.695e+01f, 5.222e+00f },
           {8.543e+01f, -8.543e+01f, 9.250e+00f },
           {8.543e+01f, -1.281e+02f, 1.639e+01f },
           {8.543e+01f, -1.922e+02f, 2.903e+01f },
           {8.543e+01f, -2.883e+02f, 5.143e+01f },
           {8.543e+01f, -4.325e+02f, 8.283e+01f },
           {8.543e+01f, -6.487e+02f, 1.334e+02f },
           {8.543e+01f, -9.731e+02f, 2.148e+02f },
           {8.543e+01f, -1.460e+03f, 3.460e+02f },
           {8.543e+01f, -2.189e+03f, 5.572e+02f },
           {8.543e+01f, -3.284e+03f, 8.974e+02f },
           {8.543e+01f, -4.926e+03f, 1.314e+03f },
           {8.543e+01f, -7.389e+03f, 2.116e+03f },
           {8.543e+01f, -1.108e+04f, 3.098e+03f },
           {8.543e+01f, -1.663e+04f, 4.536e+03f },
           {1.281e+02f, -7.500e+00f, 1.250e+00f },
           {1.281e+02f, -1.125e+01f, 1.250e+00f },
           {1.281e+02f, -1.688e+01f, 1.250e+00f },
           {1.281e+02f, -2.531e+01f, 1.513e+00f },
           {1.281e+02f, -3.797e+01f, 2.214e+00f },
           {1.281e+02f, -5.695e+01f, 3.923e+00f },
           {1.281e+02f, -8.543e+01f, 6.950e+00f },
           {1.281e+02f, -1.281e+02f, 1.231e+01f },
           {1.281e+02f, -1.922e+02f, 2.181e+01f },
           {1.281e+02f, -2.883e+02f, 4.250e+01f },
           {1.281e+02f, -4.325e+02f, 6.845e+01f },
           {1.281e+02f, -6.487e+02f, 1.213e+02f },
           {1.281e+02f, -9.731e+02f, 1.953e+02f },
           {1.281e+02f, -1.460e+03f, 3.460e+02f },
           {1.281e+02f, -2.189e+03f, 5.572e+02f },
           {1.281e+02f, -3.284e+03f, 8.159e+02f },
           {1.281e+02f, -4.926e+03f, 1.314e+03f },
           {1.281e+02f, -7.389e+03f, 1.924e+03f },
           {1.281e+02f, -1.108e+04f, 3.098e+03f },
           {1.281e+02f, -1.663e+04f, 4.536e+03f },
           {1.922e+02f, -7.500e+00f, 1.250e+00f },
           {1.922e+02f, -1.125e+01f, 1.250e+00f },
           {1.922e+02f, -1.688e+01f, 1.250e+00f },
           {1.922e+02f, -2.531e+01f, 1.250e+00f },
           {1.922e+02f, -3.797e+01f, 1.664e+00f },
           {1.922e+02f, -5.695e+01f, 2.679e+00f },
           {1.922e+02f, -8.543e+01f, 5.222e+00f },
           {1.922e+02f, -1.281e+02f, 9.250e+00f },
           {1.922e+02f, -1.922e+02f, 1.803e+01f },
           {1.922e+02f, -2.883e+02f, 3.193e+01f },
           {1.922e+02f, -4.325e+02f, 5.657e+01f },
           {1.922e+02f, -6.487e+02f, 1.002e+02f },
           {1.922e+02f, -9.731e+02f, 1.776e+02f },
           {1.922e+02f, -1.460e+03f, 3.145e+02f },
           {1.922e+02f, -2.189e+03f, 5.066e+02f },
           {1.922e+02f, -3.284e+03f, 8.159e+02f },
           {1.922e+02f, -4.926e+03f, 1.194e+03f },
           {1.922e+02f, -7.389e+03f, 1.924e+03f },
           {1.922e+02f, -1.108e+04f, 3.098e+03f },
           {1.922e+02f, -1.663e+04f, 4.536e+03f },
           {2.883e+02f, -7.500e+00f, 1.250e+00f },
           {2.883e+02f, -1.125e+01f, 1.250e+00f },
           {2.883e+02f, -1.688e+01f, 1.250e+00f },
           {2.883e+02f, -2.531e+01f, 1.250e+00f },
           {2.883e+02f, -3.797e+01f, 1.250e+00f },
           {2.883e+02f, -5.695e+01f, 2.013e+00f },
           {2.883e+02f, -8.543e+01f, 3.566e+00f },
           {2.883e+02f, -1.281e+02f, 6.950e+00f },
           {2.883e+02f, -1.922e+02f, 1.354e+01f },
           {2.883e+02f, -2.883e+02f, 2.399e+01f },
           {2.883e+02f, -4.325e+02f, 4.676e+01f },
           {2.883e+02f, -6.487e+02f, 8.283e+01f },
           {2.883e+02f, -9.731e+02f, 1.614e+02f },
           {2.883e+02f, -1.460e+03f, 2.600e+02f },
           {2.883e+02f, -2.189e+03f, 4.605e+02f },
           {2.883e+02f, -3.284e+03f, 7.417e+02f },
           {2.883e+02f, -4.926e+03f, 1.194e+03f },
           {2.883e+02f, -7.389e+03f, 1.924e+03f },
           {2.883e+02f, -1.108e+04f, 2.817e+03f },
           {2.883e+02f, -1.663e+04f, 4.536e+03f },
           {4.325e+02f, -7.500e+00f, 1.250e+00f },
           {4.325e+02f, -1.125e+01f, 1.250e+00f },
           {4.325e+02f, -1.688e+01f, 1.250e+00f },
           {4.325e+02f, -2.531e+01f, 1.250e+00f },
           {4.325e+02f, -3.797e+01f, 1.250e+00f },
           {4.325e+02f, -5.695e+01f, 1.375e+00f },
           {4.325e+02f, -8.543e+01f, 2.436e+00f },
           {4.325e+02f, -1.281e+02f, 4.747e+00f },
           {4.325e+02f, -1.922e+02f, 9.250e+00f },
           {4.325e+02f, -2.883e+02f, 1.803e+01f },
           {4.325e+02f, -4.325e+02f, 3.513e+01f },
           {4.325e+02f, -6.487e+02f, 6.845e+01f },
           {4.325e+02f, -9.731e+02f, 1.334e+02f },
           {4.325e+02f, -1.460e+03f, 2.363e+02f },
           {4.325e+02f, -2.189e+03f, 3.806e+02f },
           {4.325e+02f, -3.284e+03f, 6.743e+02f },
           {4.325e+02f, -4.926e+03f, 1.086e+03f },
           {4.325e+02f, -7.389e+03f, 1.749e+03f },
           {4.325e+02f, -1.108e+04f, 2.817e+03f },
           {4.325e+02f, -1.663e+04f, 4.536e+03f },
           {6.487e+02f, -7.500e+00f, 1.250e+00f },
           {6.487e+02f, -1.125e+01f, 1.250e+00f },
           {6.487e+02f, -1.688e+01f, 1.250e+00f },
           {6.487e+02f, -2.531e+01f, 1.250e+00f },
           {6.487e+02f, -3.797e+01f, 1.250e+00f },
           {6.487e+02f, -5.695e+01f, 1.250e+00f },
           {6.487e+02f, -8.543e+01f, 1.664e+00f },
           {6.487e+02f, -1.281e+02f, 3.242e+00f },
           {6.487e+02f, -1.922e+02f, 6.950e+00f },
           {6.487e+02f, -2.883e+02f, 1.354e+01f },
           {6.487e+02f, -4.325e+02f, 2.639e+01f },
           {6.487e+02f, -6.487e+02f, 5.143e+01f },
           {6.487e+02f, -9.731e+02f, 1.002e+02f },
           {6.487e+02f, -1.460e+03f, 1.953e+02f },
           {6.487e+02f, -2.189e+03f, 3.460e+02f },
           {6.487e+02f, -3.284e+03f, 6.130e+02f },
           {6.487e+02f, -4.926e+03f, 9.872e+02f },
           {6.487e+02f, -7.389e+03f, 1.590e+03f },
           {6.487e+02f, -1.108e+04f, 2.561e+03f },
           {6.487e+02f, -1.663e+04f, 4.124e+03f },
           {9.731e+02f, -7.500e+00f, 1.250e+00f },
           {9.731e+02f, -1.125e+01f, 1.250e+00f },
           {9.731e+02f, -1.688e+01f, 1.250e+00f },
           {9.731e+02f, -2.531e+01f, 1.250e+00f },
           {9.731e+02f, -3.797e+01f, 1.250e+00f },
           {9.731e+02f, -5.695e+01f, 1.250e+00f },
           {9.731e+02f, -8.543e+01f, 1.250e+00f },
           {9.731e+02f, -1.281e+02f, 2.214e+00f },
           {9.731e+02f, -1.922e+02f, 4.747e+00f },
           {9.731e+02f, -2.883e+02f, 9.250e+00f },
           {9.731e+02f, -4.325e+02f, 1.983e+01f },
           {9.731e+02f, -6.487e+02f, 3.864e+01f },
           {9.731e+02f, -9.731e+02f, 7.530e+01f },
           {9.731e+02f, -1.460e+03f, 1.467e+02f },
           {9.731e+02f, -2.189e+03f, 2.860e+02f },
           {9.731e+02f, -3.284e+03f, 5.066e+02f },
           {9.731e+02f, -4.926e+03f, 8.974e+02f },
           {9.731e+02f, -7.389e+03f, 1.445e+03f },
           {9.731e+02f, -1.108e+04f, 2.561e+03f },
           {9.731e+02f, -1.663e+04f, 4.124e+03f },
           {1.460e+03f, -7.500e+00f, 1.250e+00f },
           {1.460e+03f, -1.125e+01f, 1.250e+00f },
           {1.460e+03f, -1.688e+01f, 1.250e+00f },
           {1.460e+03f, -2.531e+01f, 1.250e+00f },
           {1.460e+03f, -3.797e+01f, 1.250e+00f },
           {1.460e+03f, -5.695e+01f, 1.250e+00f },
           {1.460e+03f, -8.543e+01f, 1.250e+00f },
           {1.460e+03f, -1.281e+02f, 1.513e+00f },
           {1.460e+03f, -1.922e+02f, 3.242e+00f },
           {1.460e+03f, -2.883e+02f, 6.950e+00f },
           {1.460e+03f, -4.325e+02f, 1.354e+01f },
           {1.460e+03f, -6.487e+02f, 2.903e+01f },
           {1.460e+03f, -9.731e+02f, 5.657e+01f },
           {1.460e+03f, -1.460e+03f, 1.213e+02f },
           {1.460e+03f, -2.189e+03f, 2.148e+02f },
           {1.460e+03f, -3.284e+03f, 4.187e+02f },
           {1.460e+03f, -4.926e+03f, 7.417e+02f },
           {1.460e+03f, -7.389e+03f, 1.314e+03f },
           {1.460e+03f, -1.108e+04f, 2.328e+03f },
           {1.460e+03f, -1.663e+04f, 3.749e+03f },
           {2.189e+03f, -7.500e+00f, 1.250e+00f },
           {2.189e+03f, -1.125e+01f, 1.250e+00f },
           {2.189e+03f, -1.688e+01f, 1.250e+00f },
           {2.189e+03f, -2.531e+01f, 1.250e+00f },
           {2.189e+03f, -3.797e+01f, 1.250e+00f },
           {2.189e+03f, -5.695e+01f, 1.250e+00f },
           {2.189e+03f, -8.543e+01f, 1.250e+00f },
           {2.189e+03f, -1.281e+02f, 1.250e+00f },
           {2.189e+03f, -1.922e+02f, 2.214e+00f },
           {2.189e+03f, -2.883e+02f, 4.747e+00f },
           {2.189e+03f, -4.325e+02f, 9.250e+00f },
           {2.189e+03f, -6.487e+02f, 1.983e+01f },
           {2.189e+03f, -9.731e+02f, 4.250e+01f },
           {2.189e+03f, -1.460e+03f, 8.283e+01f },
           {2.189e+03f, -2.189e+03f, 1.776e+02f },
           {2.189e+03f, -3.284e+03f, 3.460e+02f },
           {2.189e+03f, -4.926e+03f, 6.130e+02f },
           {2.189e+03f, -7.389e+03f, 1.086e+03f },
           {2.189e+03f, -1.108e+04f, 1.924e+03f },
           {2.189e+03f, -1.663e+04f, 3.408e+03f },
           {3.284e+03f, -7.500e+00f, 1.250e+00f },
           {3.284e+03f, -1.125e+01f, 1.250e+00f },
           {3.284e+03f, -1.688e+01f, 1.250e+00f },
           {3.284e+03f, -2.531e+01f, 1.250e+00f },
           {3.284e+03f, -3.797e+01f, 1.250e+00f },
           {3.284e+03f, -5.695e+01f, 1.250e+00f },
           {3.284e+03f, -8.543e+01f, 1.250e+00f },
           {3.284e+03f, -1.281e+02f, 1.250e+00f },
           {3.284e+03f, -1.922e+02f, 1.513e+00f },
           {3.284e+03f, -2.883e+02f, 3.242e+00f },
           {3.284e+03f, -4.325e+02f, 6.318e+00f },
           {3.284e+03f, -6.487e+02f, 1.354e+01f },
           {3.284e+03f, -9.731e+02f, 2.903e+01f },
           {3.284e+03f, -1.460e+03f, 6.223e+01f },
           {3.284e+03f, -2.189e+03f, 1.334e+02f },
           {3.284e+03f, -3.284e+03f, 2.600e+02f },
           {3.284e+03f, -4.926e+03f, 5.066e+02f },
           {3.284e+03f, -7.389e+03f, 9.872e+02f },
           {3.284e+03f, -1.108e+04f, 1.749e+03f },
           {3.284e+03f, -1.663e+04f, 3.098e+03f },
           {4.926e+03f, -7.500e+00f, 1.250e+00f },
           {4.926e+03f, -1.125e+01f, 1.250e+00f },
           {4.926e+03f, -1.688e+01f, 1.250e+00f },
           {4.926e+03f, -2.531e+01f, 1.250e+00f },
           {4.926e+03f, -3.797e+01f, 1.250e+00f },
           {4.926e+03f, -5.695e+01f, 1.250e+00f },
           {4.926e+03f, -8.543e+01f, 1.250e+00f },
           {4.926e+03f, -1.281e+02f, 1.250e+00f },
           {4.926e+03f, -1.922e+02f, 1.250e+00f },
           {4.926e+03f, -2.883e+02f, 2.013e+00f },
           {4.926e+03f, -4.325e+02f, 4.315e+00f },
           {4.926e+03f, -6.487e+02f, 9.250e+00f },
           {4.926e+03f, -9.731e+02f, 2.181e+01f },
           {4.926e+03f, -1.460e+03f, 4.250e+01f },
           {4.926e+03f, -2.189e+03f, 9.111e+01f },
           {4.926e+03f, -3.284e+03f, 1.953e+02f },
           {4.926e+03f, -4.926e+03f, 3.806e+02f },
           {4.926e+03f, -7.389e+03f, 7.417e+02f },
           {4.926e+03f, -1.108e+04f, 1.445e+03f },
           {4.926e+03f, -1.663e+04f, 2.561e+03f },
           {7.389e+03f, -7.500e+00f, 1.250e+00f },
           {7.389e+03f, -1.125e+01f, 1.250e+00f },
           {7.389e+03f, -1.688e+01f, 1.250e+00f },
           {7.389e+03f, -2.531e+01f, 1.250e+00f },
           {7.389e+03f, -3.797e+01f, 1.250e+00f },
           {7.389e+03f, -5.695e+01f, 1.250e+00f },
           {7.389e+03f, -8.543e+01f, 1.250e+00f },
           {7.389e+03f, -1.281e+02f, 1.250e+00f },
           {7.389e+03f, -1.922e+02f, 1.250e+00f },
           {7.389e+03f, -2.883e+02f, 1.375e+00f },
           {7.389e+03f, -4.325e+02f, 2.947e+00f },
           {7.389e+03f, -6.487e+02f, 6.318e+00f },
           {7.389e+03f, -9.731e+02f, 1.490e+01f },
           {7.389e+03f, -1.460e+03f, 3.193e+01f },
           {7.389e+03f, -2.189e+03f, 6.845e+01f },
           {7.389e+03f, -3.284e+03f, 1.334e+02f },
           {7.389e+03f, -4.926e+03f, 2.860e+02f },
           {7.389e+03f, -7.389e+03f, 5.572e+02f },
           {7.389e+03f, -1.108e+04f, 1.086e+03f },
           {7.389e+03f, -1.663e+04f, 2.116e+03f },
           {1.108e+04f, -7.500e+00f, 1.250e+00f },
           {1.108e+04f, -1.125e+01f, 1.250e+00f },
           {1.108e+04f, -1.688e+01f, 1.250e+00f },
           {1.108e+04f, -2.531e+01f, 1.250e+00f },
           {1.108e+04f, -3.797e+01f, 1.250e+00f },
           {1.108e+04f, -5.695e+01f, 1.250e+00f },
           {1.108e+04f, -8.543e+01f, 1.250e+00f },
           {1.108e+04f, -1.281e+02f, 1.250e+00f },
           {1.108e+04f, -1.922e+02f, 1.250e+00f },
           {1.108e+04f, -2.883e+02f, 1.250e+00f },
           {1.108e+04f, -4.325e+02f, 2.013e+00f },
           {1.108e+04f, -6.487e+02f, 4.315e+00f },
           {1.108e+04f, -9.731e+02f, 1.018e+01f },
           {1.108e+04f, -1.460e+03f, 2.181e+01f },
           {1.108e+04f, -2.189e+03f, 4.676e+01f },
           {1.108e+04f, -3.284e+03f, 1.002e+02f },
           {1.108e+04f, -4.926e+03f, 2.148e+02f },
           {1.108e+04f, -7.389e+03f, 4.187e+02f },
           {1.108e+04f, -1.108e+04f, 8.974e+02f },
           {1.108e+04f, -1.663e+04f, 1.749e+03f },
           {1.663e+04f, -7.500e+00f, 1.250e+00f },
           {1.663e+04f, -1.125e+01f, 1.250e+00f },
           {1.663e+04f, -1.688e+01f, 1.250e+00f },
           {1.663e+04f, -2.531e+01f, 1.250e+00f },
           {1.663e+04f, -3.797e+01f, 1.250e+00f },
           {1.663e+04f, -5.695e+01f, 1.250e+00f },
           {1.663e+04f, -8.543e+01f, 1.250e+00f },
           {1.663e+04f, -1.281e+02f, 1.250e+00f },
           {1.663e+04f, -1.922e+02f, 1.250e+00f },
           {1.663e+04f, -2.883e+02f, 1.250e+00f },
           {1.663e+04f, -4.325e+02f, 1.375e+00f },
           {1.663e+04f, -6.487e+02f, 2.947e+00f },
           {1.663e+04f, -9.731e+02f, 6.318e+00f },
           {1.663e+04f, -1.460e+03f, 1.490e+01f },
           {1.663e+04f, -2.189e+03f, 3.193e+01f },
           {1.663e+04f, -3.284e+03f, 6.845e+01f },
           {1.663e+04f, -4.926e+03f, 1.467e+02f },
           {1.663e+04f, -7.389e+03f, 3.145e+02f },
           {1.663e+04f, -1.108e+04f, 6.743e+02f },
           {1.663e+04f, -1.663e+04f, 1.314e+03f },
        };
        if ((a > 1.663e+04) || (-b > 1.663e+04))
           return z > -b;  // Way overly conservative?
        if (a < data[0][0])
           return false;
        int index = 0;
        while (data[index][0] < a)
           ++index;
        if(a != data[index][0])
           --index;
        while ((data[index][1] < b) && (data[index][2] > 1.25))
           --index;
        ++index;
        BOOST_ASSERT(a > data[index][0]);
        BOOST_ASSERT(-b < -data[index][1]);
        return z > data[index][2];
     }
     template <class T, class Policy>
     T hypergeometric_1F1_from_function_ratio_negative_b_forwards(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T> coef(a, b, z);
        T ratio = 1 / boost::math::tools::function_ratio_from_forwards_recurrence(coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        //
        // We can't normalise via the Wronksian as the subtraction in the Wronksian will suffer an exquisite amount of cancellation - 
        // potentially many hundreds of digits in this region.  However, if forwards iteration is stable at this point
        // it will also be stable for M(a, b+1, z) etc all the way up to the origin, and hopefully one step beyond.  So
        // use a reference value just over the origin to normalise:
        //
        int scale = 0;
        int steps = itrunc(ceil(-b));
        T reference_value = hypergeometric_1F1_imp(T(a + steps), T(b + steps), z, pol, log_scaling);
        T found = boost::math::tools::apply_recurrence_relation_forward(boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T>(a + 1, b + 1, z), steps - 1, T(1), ratio, &scale);
        log_scaling -= scale;
        if ((fabs(reference_value) < 1) && (fabs(reference_value) < tools::min_value<T>() * fabs(found)))
        {
           // Possible underflow, rescale
           int s = itrunc(tools::log_max_value<T>());
           log_scaling -= s;
           reference_value *= exp(T(s));
        }
        else if ((fabs(found) < 1) && (fabs(reference_value) > tools::max_value<T>() * fabs(found)))
        {
           // Overflow, rescale:
           int s = itrunc(tools::log_max_value<T>());
           log_scaling += s;
           reference_value /= exp(T(s));
        }
        return reference_value / found;
     }



     //
     // This next version is largely the same as above, but calculates the ratio for the b recurrence relation
     // which has a larger area of stability than the ab recurrence when a,b < 0.  We can then use a single
     // recurrence step to convert this to the ratio for the ab recursion and proceed largely as before.
     // The routine is quite insensitive to the size of z, but requires |a| < |5b| for accuracy.
     // Fortunately the accuracy outside this domain falls off steadily rather than suddenly switching
     // to a different behaviour.
     //
     template <class T, class Policy>
     T hypergeometric_1F1_from_function_ratio_negative_ab(const T& a, const T& b, const T& z, const Policy& pol, int& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        boost::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_b_coefficients<T> coef(a, b + 1, z);
        T ratio = boost::math::tools::function_ratio_from_backwards_recurrence(coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        //
        // We need to use A&S 13.4.3 to convert a ratio for M(a, b + 1, z) / M(a, b, z)
        // to M(a+1, b+1, z) / M(a, b, z)
        //
        // We have:        (a-b)M(a, b+1, z) - aM(a+1, b+1, z) + bM(a, b, z) = 0
        // and therefore:  M(a + 1, b + 1, z) / M(a, b, z) = ((a - b)M(a, b + 1, z) / M(a, b, z) + b) / a
        //
        ratio = ((a - b) * ratio + b) / a;
        //
        // Let M2 = M(1+a-b, 2-b, z)
        // This is going to be a mighty big number:
        //
        int local_scaling = 0;
        T M2 = boost::math::detail::hypergeometric_1F1_imp(T(1 + a - b), T(2 - b), z, pol, local_scaling);
        log_scaling -= local_scaling; // all the M2 terms are in the denominator
        //
        // Let M3 = M(1+a-b + 1, 2-b + 1, z)
        // We don't use the ratio to get this as it's not clear that it's reliable:
        //
        int local_scaling2 = 0;
        T M3 = boost::math::detail::hypergeometric_1F1_imp(T(2 + a - b), T(3 - b), z, pol, local_scaling2);
        //
        // M2 and M3 must be identically scaled:
        //
        if (local_scaling != local_scaling2)
        {
           M3 *= exp(T(local_scaling2 - local_scaling));
        }
        //
        // Get the RHS of the Wronksian:
        //
        int fz = itrunc(z);
        log_scaling += fz;
        T rhs = (1 - b) * exp(z - fz);
        //
        // We need to divide that by:
        // [(a-b+1)z/(2-b) M2(a+1,b+1,z) + (1-b) M2(a,b,z) - a/b z^b R(a,b,z) M2(a,b,z) ]
        // Note that at this stage, both M3 and M2 are scaled by exp(local_scaling).
        //
        T lhs = (a - b + 1) * z * M3 / (2 - b) + (1 - b) * M2 - a * z * ratio * M2 / b;

        return rhs / lhs;
     }

  } } } // namespaces

#endif // BOOST_HYPERGEOMETRIC_1F1_BY_RATIOS_HPP_

/* hypergeometric_1F1_by_ratios.hpp
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
*/