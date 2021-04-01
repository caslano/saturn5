
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP
#define BOOST_MATH_HYPERGEOMETRIC_1F1_CF_HPP
//
// Evaluation of 1F1 by continued fraction
// by asymptotic approximation for large a, 
// see https://dlmf.nist.gov/13.8#E9
//
// This is not terribly useful, as it only gets a few digits correct even for very
// large a, also needs b and z small:
//


  namespace boost { namespace math { namespace detail {

     template <class T, class Policy>
     T hypergeometric_1F1_large_neg_a_asymtotic_dlmf_13_8_9(T a, T b, T z, const Policy& pol)
     {
        T result = boost::math::cyl_bessel_j(b - 1, sqrt(2 * z * (b - 2 * a)), pol);
        result *= boost::math::tgamma(b, pol) * exp(z / 2);
        T p = pow((b / 2 - a) * z, (1 - b) / 4);
        result *= p;
        result *= p;
        return result;
     }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_1F1_BESSEL_HPP

/* hypergeometric_1F1_large_a.hpp
kFKQJ3qsWyba8HZ4e0+RARJOD+wCJbirNKR371i+S77D/34TF6eClasnBW201X7oeukYnbJSrSN4n8STuR8qA5XON3zo9Fx7iss1FfPGXe0BzXuIs6iIMUz8fhb40AFHCo4YZuS5npjIBRoIvoWoW2qlrYhQ/zWjpD/EvdQBFzAaH/230M1TUWY8esqQ5buUi5iqEZUxe3vEaMpqh4WNqi6de1PmTOxdFaoeLe1Yam66KBlbeGfQnxh/N23MsiKiDbd/6O8SjRPLQvnlNXPNYB+5CuLPYGJ0nMQzHU6Tvz7NuDm4B2nXFrP1iSL9b0BUdFEEzY6jnn/o8ks5kt66fGy24rqARXc5T++9CmVOtnt/LU3ON8flUP+EUVs9hdOi50J2IJcmkHxAYZysloF3yQNbm+C3WxnEST9y6jOLJLuFp0Kb/+CWpzYGR2M1fuq4l1XWnmS2E/HMLBMIyRPV5tfKJwGhDJcYQRJWzHoV38EcJ4BpAFDK0FB/fN8CGDA3SHfqi42NaY9BIFRx5uPpPF9KyBEPWYikE/OB78j9WdxjK9V/4LIH5z6ipw==
*/