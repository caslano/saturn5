
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
dbp5nm9vb65/pqlfrFPX3TX1iZr6XFF/vX3tsaFl4thQZguxrIllzwndSZoyQLQl6Ir9sTs+gR64Au/GVTgFV6MO1+BMXIvRuA5N+AzOwQ24ADfiffgspuNz+DC+gI/jJszGzbgOt+Bz+CLmYh6+jK/gDnwV38StWIjbcB/uxP2YjyX4Gh7F1/EEvoEVuBu/w7fxYqZ9D16Je9EZC7EzvoPdcR/2w3dxIBbhMHwfI/EDXIbF
*/