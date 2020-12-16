///////////////////////////////////////////////////////////////////////////////
//  Copyright 2014 Anton Bikineev
//  Copyright 2014 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2014 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP
#define BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

#include <boost/math/special_functions/bessel.hpp>
#include <boost/math/special_functions/gamma.hpp>

  namespace boost { namespace math { namespace detail {

  template <class T, class Policy>
  inline T hypergeometric_0F1_bessel(const T& b, const T& z, const Policy& pol)
  {
    BOOST_MATH_STD_USING

    const bool is_z_nonpositive = z <= 0;

    const T sqrt_z = is_z_nonpositive ? T(sqrt(-z)) : T(sqrt(z));
    const T bessel_mult = is_z_nonpositive ?
      boost::math::cyl_bessel_j(b - 1, 2 * sqrt_z, pol) :
      boost::math::cyl_bessel_i(b - 1, 2 * sqrt_z, pol) ;

    if (b > boost::math::max_factorial<T>::value)
    {
       const T lsqrt_z = log(sqrt_z);
       const T lsqrt_z_pow_b = (b - 1) * lsqrt_z;
       T lg = (boost::math::lgamma(b, pol) - lsqrt_z_pow_b);
       lg = exp(lg);
       return lg * bessel_mult;
    }
    else
    {
       const T sqrt_z_pow_b = pow(sqrt_z, b - 1);
       return (boost::math::tgamma(b, pol) / sqrt_z_pow_b) * bessel_mult;
    }
  }

  } } } // namespaces

#endif // BOOST_MATH_HYPERGEOMETRIC_0F1_BESSEL_HPP

/* hypergeometric_0F1_bessel.hpp
HGTTVKTQt9X95cg7aTwns7xif1/QMlkvlrdG6N8DHCcX5gFvbJlQWzR1FXBJfbdGeZwNP6QduKrVedyAtUbLOGPn+Gqi82MmZyVM/h3upQsplhb7mvU8RTl6u9IuXBoc1fZqcmaDLuPLvO2Irf2+vB5U5haWl0/Smv1SlUKHuaLK+41OGVKLsKf4IlqfX5iXsTfu5AkwFAjcmWF1Pkq/u9nYSq/vSiulGp9f3wnTybuz+UTSpoy/LNNaU3uKoxsEdeqPt5DvPsPP4kj/4Oscc+nnfZ2vqH/YLq2mqjQcGK5BuU5Nqjqn2buhz1AKqjo2vI7RW7W8NCe63k5NFXNpodbj716Y7SZrW/wF3hwZnpdNXUcelm9k+O5OdjGVervKMO06rW7Xz6g03jNM4qSx1L/rehxHQNrw6wV1p573rV+d9vZasq33fv31UppZSzamu7uNKJF8vIDjBjVtZxsdtW4XfdTR6eGbabpej/zRd/fcSzP58mOi7qyMLmj1bgx9/ya6vnE1U3uyRzd19FpD2UTDTzpub+10Gjt1ff/apwI69f4P0eP3TwcY8mZzE8zATQdKAzqv0p6mcS6Y6OM+Q+k0TUkWqfMhH9aMezfO6oWMVs12wrVUWG92EYdJqGKeoR1pzljykZf1mU53y+0v9902Tj/yzoe6E5ShTzjhotmuzN5rStr84DJaT05T+1eP3btixz/0GLSRuDP9R2GmGnfa2p4fWq4b6z3LP/b11DjB+GkvqKe7NdU7Zz7Da2cSH19HG9kW5ieGSfw3WUo/9RlqR5UbvZDO5yikzzQMtV1IL1rD9PW4FZMu9kJI575D0sMy3WQb6TU0OhW6SL01+POAno4bsmdLEday5bYbm2ovndUpQVU9NXp3N3cBfox8hjdQ4wy5rz+83m6ptHDrA1Xy5sZaB/rUJ61OVQH1yei7ZFGpe8wupnU8SNeKVZ7+zWnXqU2fprZd3XVr9W5n8w5os//u6qRNEyR6pX+5TF+hZz1kw76+x9zTubhgr8jLPL2h9or431KR1rbF/lbeNtH9xRS2dOiSNFoqfUrbIT0t9EifmeEhYtJ7gqcrs0uz9+LwyR7yVV/Xe3E8jcO3K3H//ETXTsPtgejidH2iDT1N713fm/hLj4jqUEu6GN1dEx5oHc6jXD4wy3N6MjR/IjctVrrfiB9jdbbBJF37nhsPa5ONpOZwZx4U0FNHlBuD5wqj7yFpyL6S5zm6s4+172qTvaoNGU/eW/Tsqc90cpgj2pV+ZqmA4XDiLS/LIUKq/VwXbj19b1C5tS55WxOmVqdD82Tbr69tnMa+yLrST2fTLmjzNqG1JgtX+gzYtuhk0NMZJXmPJw0x0r13WjgaGG9M7sSZk71ITdGzFJMy+6wL4/f8jWLYPE91vqHrjORepgWZfzniMcuzlfxSpvRdRqTj6lHDVSunjtDRJ9V3W4Y9xL6ogcfMHa3cs4Jrm7oSLsshWDpcx3xuEqzo3C0n4fKY8IZQrG0PHJ7f3qW8kH6wZ/U7kC77AEJ6tbI0f58qBSzLeNgHnl8c+CXpb7w8VKlwT9nbOecyS24ezktZDHDZxVopRpz00z6HvD4n7d3zXCathPTzPaW9er7Vq7On7kfSObHB5gIMbTLRzNTxAEOLoCkjbZLUDdRuGd88+8K+ltYRzIk/zXyr68m8rIkcN5xfVzBfGGRRX6SMhzn2XK0XnDCcX28iCWeYRTB1OIMs6s/0JJyWK6pDJyTf7m6+kXok7UXPMFKXZB3IMqH6hHkA66/UKek7nm4ZpCXqVf8ZltP1T+Y+rJ+mDso6oWVNPZR6PW9ZXRdlDvZ5luP6iLg83zK6Tkr/a/2Ueqm5nuU=
*/