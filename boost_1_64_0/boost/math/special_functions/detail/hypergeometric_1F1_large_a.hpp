
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
EhthSzMoTCRtic0Oxm5v1OEGp7Y3olxUtM75wBMx2O+jGPiBsMSOzlGnhzrTjYg6rfeCHLVXzEmd1BynDu93wl79CcPhITSb7aC0wtxJgKHIdRPvzoRoO8C1qOkiTO5pDzBcOVFbW22U3RCftmZ1MKshJm2CFdPzmcTGs28ZHc9E0sxwNp4jwxwcz6jh8zaeU4aReOIsgDBkLKiyV9G/o+w1ZN38IROdArlBy03KfhifZi28BTiRNrUJTtcRGe8pHd9Dn9K6NA3q+4ddLtPprqyFxZX5o7wELfqo6+sN5/uy/z3PO0sa3O1Qpq8cz65U2IiUtncEWtx1tf5zs3Df9+7zSycri4snI70P8HmuVj3S6PDuIcmb/gtdhrctYY76Ra7OW5dEj17s6eyBtBfrabwzA+w+t06Pqqf3W2f9J5XETcwBjwq53RQU96INn6M5bbgHf4Mc3JOy+XqfI0bZ1IOQTmtdjTX1vmrNYxAetAFvCDG0/t4Bs2rcsfHvFTN0A2yEML3R4zBgwBmdumFSr7pi9wb1dDcq3Jgx/tD0gLprZGx0Kt2kS7vypoCeeaH82PSZxrQ+S9T3dU4zSdcto0tEJJxfdRle+4TN9DVPxxEOtJFf9xnaHkucXotZjS6vGH7tsLUjGyJkPKDTJb8/hSKNM0/lt3h6Oue2W1tr1/Q2ZrWX5NDlXZ7fqRSb/QJBPbP59Hp57wCuqtK8X8BRmmFfygXDTDd9DlfvQ9dcVgbdubr4GzotEH3OQqzn6DSjcsbrmInk8ZanS65gHnNq22NgHzZkPobDK4yblphzuGiY0+VuXzP5fbjcasCd2AkTh9nbU9D3mE6ejk1+4hnlznKds+o9zbGve3Wt1FA6pw0HZVv6jLuk4041KOf7WqSv9fX0wVClr/q6t6bf83Wvr+4bPbXRoY/v7OleXz72v/fWkEt39fUkc1/yNKSnS6KURtJffPSyYFboLM6RUytzPE0r46OXlCyj7guX9TNxy3I8Ay3s1MeKWZ6BFnZ8Hraj1h36obByvklfG2K8MWHv4yE/0/zLLD6ErZhrrT+Eqohqk6NPBFjc64+5/mD4Gh1nbBhivPWVqaB/6fERNw77nyziJA6od58Uf/Orgei5Ea53LekDAoy+q3cmpKdBV24MPqIYmgJlPx4m800fdnV9p8jI+5bdfpiU+VdCJ+sPqzLK/zjA6Dj0QzrHQcqZx9xrbuXuk5u+JB+DjHtH7kwfDFur6azBGVo8dOapR9+5rM9lh41yM0bdj2O5FINN+3lH583TSZcGYev6nOnQ53Zi2CjfdTS9wLYu/eRVnXjx6/VqrPRMR+cVe4xJBl666LsnRq7G2Yv6Hb3K1dNaSG0J7yBAmlbCHE/+q7R/hOW0hSTjzBDXXEs63ngmemSA2yUHPa4U4rD8jDpnORqp3GfxnnPHYLdInoHR5WI1qGNxUdrOMMfNuuovDGcXFWWtI8xyTwW7aVTAkQUGe8hLC1wNquxny+hsakhc/fLBo/68hQUXW/dUdmJdtudz9oAe2iCfxSKRMHteHdrudOLqbr5gJ+N+Lw6NjroT2KvjO2udjW01p9L3vuW3wXks6nzLZjLyKnqzq2OkEyHfvTimvVKovoxCHBIYa8RueEOzPaiDj/JYKSfpflzlt3VTlwG0ib57yC+cz/PyK817PS83Dui56azu7fL9aWVt2lnpW12dD3NDj17t6nyg+6yMX14rOi4F9N6oKl0hwBTYgr1CFrag1O+Q3559F70uwLB9J3sUrhhiqAah6UF7VsimGaz2gxdxMKOwphGKR56E61JegvGgGkaMtKFBP5NgPIZh1sQjulKY0/GQMc4Mxhiwo9CHR7M=
*/