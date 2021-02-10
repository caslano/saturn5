
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
xBa2og2bkVtEcHFOLlCCzkgvIr6I/MJgM/KLCDDOCUb0KbsYrvwH0EVEERlFhBSRUkRMETmFjflhge4cVRCCgR1xhZFXGIGFkVgYkYWRWdgMLYzUwogtjNzCPMJtoCO6MLIL89kSHeyIL4z8wjxivw26v/3R/4ri9Uj/Iv4DO4/4D+iIMowsw3y2RPIMI9AwBzsCDSPRMCINI9Mwny2RXMMINoxkw5yWSLJhRBtGtmE+WyL5hhFwGAmHEXGYAx0Rh5FxmM+WSM5hBB1G0mFEHUbWYQ50ZB3msyWSdxiBh5F4GJGHkXkYoYc50Plsiefcg6dwQ4JhRBhGhmGEGEaKYcQY5rOnOT2NJMOIMowswwgzjDTDiDPMZ08j0jCnpxFpGJmGEWoYqYYRa1iePY1ow8g2LIMX2YYRbhjphhFvWJ49LcfpEfAi5LBMTyPkMFIOI+awPHsaUYeRdRhhh5F2WAYu0g4j7rA8exqRh5F5WI6APRL2GbGjHSH7Jyl7xOyRs0fQTk8j/jDyD8vAlWdPIwIxMhAjBDFSEMvAlYGLOMTy7GlEIkYmYoQiRipixCJGLmIZuGYusjVs1MErg1emp2XgysCVgSvPnpbBK4NXBq9MT8v0tExPy/S0PHtapqdlelqmp2V6WobNDJsZ
*/