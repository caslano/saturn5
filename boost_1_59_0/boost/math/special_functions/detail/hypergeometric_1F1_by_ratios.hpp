
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
     T hypergeometric_1F1_imp(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling);

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
     T hypergeometric_1F1_from_function_ratio_negative_b(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling, const T& ratio)
     {
        BOOST_MATH_STD_USING
        //
        // Let M2 = M(1+a-b, 2-b, z)
        // This is going to be a mighty big number:
        //
        long long local_scaling = 0;
        T M2 = boost::math::detail::hypergeometric_1F1_imp(T(1 + a - b), T(2 - b), z, pol, local_scaling);
        log_scaling -= local_scaling; // all the M2 terms are in the denominator
        //
        // Since a, b and z are all likely to be large we need the Wronksian
        // calculation below to not overflow, so scale everything right down:
        //
        if (fabs(M2) > 1)
        {
           long long s = lltrunc(log(fabs(M2)));
           log_scaling -= s;  // M2 will be in the denominator, so subtract the scaling!
           local_scaling += s;
           M2 *= exp(T(-s));
        }
        //
        // Let M3 = M(1+a-b + 1, 2-b + 1, z)
        // we can get to this from the ratio which is cheaper to calculate:
        //
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T> coef2(1 + a - b + 1, 2 - b + 1, z);
        T M3 = boost::math::tools::function_ratio_from_backwards_recurrence(coef2, boost::math::policies::get_epsilon<T, Policy>(), max_iter) * M2;
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        //
        // Get the RHS of the Wronksian:
        //
        long long fz = lltrunc(z);
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
     T hypergeometric_1F1_from_function_ratio_negative_b(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
        BOOST_MATH_ASSERT(a > data[index][0]);
        BOOST_MATH_ASSERT(-b < -data[index][1]);
        return z > data[index][2];
     }
     template <class T, class Policy>
     T hypergeometric_1F1_from_function_ratio_negative_b_forwards(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
        boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T> coef(a, b, z);
        T ratio = 1 / boost::math::tools::function_ratio_from_forwards_recurrence(coef, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
        boost::math::policies::check_series_iterations<T>("boost::math::hypergeometric_1F1_from_function_ratio_negative_b_positive_a<%1%>(%1%,%1%,%1%)", max_iter, pol);
        //
        // We can't normalise via the Wronksian as the subtraction in the Wronksian will suffer an exquisite amount of cancellation - 
        // potentially many hundreds of digits in this region.  However, if forwards iteration is stable at this point
        // it will also be stable for M(a, b+1, z) etc all the way up to the origin, and hopefully one step beyond.  So
        // use a reference value just over the origin to normalise:
        //
        long long scale = 0;
        int steps = itrunc(ceil(-b));
        T reference_value = hypergeometric_1F1_imp(T(a + steps), T(b + steps), z, pol, log_scaling);
        T found = boost::math::tools::apply_recurrence_relation_forward(boost::math::detail::hypergeometric_1F1_recurrence_a_and_b_coefficients<T>(a + 1, b + 1, z), steps - 1, T(1), ratio, &scale);
        log_scaling -= scale;
        if ((fabs(reference_value) < 1) && (fabs(reference_value) < tools::min_value<T>() * fabs(found)))
        {
           // Possible underflow, rescale
           long long s = lltrunc(tools::log_max_value<T>());
           log_scaling -= s;
           reference_value *= exp(T(s));
        }
        else if ((fabs(found) < 1) && (fabs(reference_value) > tools::max_value<T>() * fabs(found)))
        {
           // Overflow, rescale:
           long long s = lltrunc(tools::log_max_value<T>());
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
     T hypergeometric_1F1_from_function_ratio_negative_ab(const T& a, const T& b, const T& z, const Policy& pol, long long& log_scaling)
     {
        BOOST_MATH_STD_USING
        //
        // Get the function ratio, M(a+1, b+1, z)/M(a,b,z):
        //
        std::uintmax_t max_iter = boost::math::policies::get_max_series_iterations<Policy>();
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
        long long local_scaling = 0;
        T M2 = boost::math::detail::hypergeometric_1F1_imp(T(1 + a - b), T(2 - b), z, pol, local_scaling);
        log_scaling -= local_scaling; // all the M2 terms are in the denominator
        //
        // Let M3 = M(1+a-b + 1, 2-b + 1, z)
        // We don't use the ratio to get this as it's not clear that it's reliable:
        //
        long long local_scaling2 = 0;
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
        long long fz = lltrunc(z);
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