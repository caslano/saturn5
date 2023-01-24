
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
5hzNG7Iqnqt3NtLu15b29qGo+LxWcsLy5N7fOHDy2bllR06WZIDAoWML2fRAuOzlDxjWNe0tSCiHcMi5qXxVPKR1Nf5s+2Q0Pqs/huFqUbY5AetNsuH7aS5EdkuZY2QugXypUsPOoRC+RUKaK52ukeaRtuqpz3pZOXbfV/XXhLeBLNctTXa2wms+8vJC40JVdH4MhkiI+f1R4GZFfh2Ksmq3GkPOWpjUheyx4a31fRq9Ei0VzbW1EbB8O0bQygj0+HHMGHwjsQLoWpnw9KIVAuW0Hda1CaPtQD33XiGFbKGSSgD1hAWaE2jPbTOo61mTXUm0+TND5PKoyaD+wSFNl/4g/NZYhOdjtmO+8/Zw1dn+72Na4q8/b0UEoqaSvw7oA0P/IsroEswm2RkWI0Jf3DpwIBiW4+d7P32l5zn+0G1+fyK6Br61gTfl6GGO9bxDtQSny8dNJB43h45SSYgrqHYZZyJ/nfj/5fb+XAiD6XrDoORyLGDoln//YR/a3JkGdPEYO1E8286+n1nF2E1snobM3jSinMnEU/NGYn3SZzdbk5S/3YNXDiau/4T0pRy33sqXf3FaeD722hm1EM3nNWXtjUDUPpqGVVwYCkvU0XubUlbrTlxeXzIt3fkgqpj7u6MAy0TbhQrkqnISJJ9XuTWpw2QmZfuairEt2A6FOtXvKUzYh7X7u0KzZyTlK2yyElPK8XMkNN756UW1
*/