//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SF_BINOMIAL_HPP
#define BOOST_MATH_SF_BINOMIAL_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/beta.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{ namespace math{

template <class T, class Policy>
T binomial_coefficient(unsigned n, unsigned k, const Policy& pol)
{
   BOOST_STATIC_ASSERT(!boost::is_integral<T>::value);
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::binomial_coefficient<%1%>(unsigned, unsigned)";
   if(k > n)
      return policies::raise_domain_error<T>(
         function, 
         "The binomial coefficient is undefined for k > n, but got k = %1%.",
         static_cast<T>(k), pol);
   T result;
   if((k == 0) || (k == n))
      return static_cast<T>(1);
   if((k == 1) || (k == n-1))
      return static_cast<T>(n);

   if(n <= max_factorial<T>::value)
   {
      // Use fast table lookup:
      result = unchecked_factorial<T>(n);
      result /= unchecked_factorial<T>(n-k);
      result /= unchecked_factorial<T>(k);
   }
   else
   {
      // Use the beta function:
      if(k < n - k)
         result = k * beta(static_cast<T>(k), static_cast<T>(n-k+1), pol);
      else
         result = (n - k) * beta(static_cast<T>(k+1), static_cast<T>(n-k), pol);
      if(result == 0)
         return policies::raise_overflow_error<T>(function, 0, pol);
      result = 1 / result;
   }
   // convert to nearest integer:
   return ceil(result - 0.5f);
}
//
// Type float can only store the first 35 factorials, in order to
// increase the chance that we can use a table driven implementation
// we'll promote to double:
//
template <>
inline float binomial_coefficient<float, policies::policy<> >(unsigned n, unsigned k, const policies::policy<>& pol)
{
   return policies::checked_narrowing_cast<float, policies::policy<> >(binomial_coefficient<double>(n, k, pol), "boost::math::binomial_coefficient<%1%>(unsigned,unsigned)");
}

template <class T>
inline T binomial_coefficient(unsigned n, unsigned k)
{
   return binomial_coefficient<T>(n, k, policies::policy<>());
}

} // namespace math
} // namespace boost


#endif // BOOST_MATH_SF_BINOMIAL_HPP




/* binomial.hpp
gfQCnbcFx8+rqMWP+jlfRF4FORqoxV8LMlPL9B9T+R1i+j0l/cPXpARf33O8LvnFdmBdiB0fdLy2Z34Un50dJ+Sj8K9zrdfbhY9xjRI+TrtV8gIv8ToHPMgFP+D9u88RD3Kcf+V5+lHvp67w+STrR/x7puC0LS3fy+qPXvYk67aD5Bc/C5Bxq/BBZzN0OOfxvv7PesY+tOibPBr67+J1RzXvF2v5+SLPq4ssF+tQ/Ix9GXZi3w2fXTzPdPH+jDwN/Gx1/zu9/mrpeZN8Dn7xSjJ+J3l+/GG7548jBef9NRrPOL6D+PP38CH7kXdAnlnwR/5I/ZHjU8GJE/iHzir7PfkK+vPb1chRyec5B6vFD/h+4Qfky7Gr85/NH7Ccne3XY70e4HyOZ76b8POB6IHnaccx+Rn01oqW+dzzbR3LR14fPf9k+93t/HKB/Zn9D3jO934nT3zTf4LooYcjnd/8Qu+Rm/0x/nSM6NN/Ra7klTwHKh+APdg/0v9anyN7/dGG7zdxX+h9+l69xx7kH6HXX3DsWJSdqoQ9VvgcX/FZAb99zfPLLPWHD/JWxNl066G8WvRQS/zC907RRc7Wns9bEI+yF+cy8L9DcPgkP8XzR/bfoxmvfs3pL7oVnUdgH8H7xUm/hh2IT8WF1+eHfis8tPVsx3s9PyzSM3bAzvDP+TB8XuWW+gD8mfN/6N6nFjuWqCUuHvK+cpHHky8inljnojfy5vj9r+oHfws1DvuTJ8avjrV/8p7+2AV5znQ+75ik7c45I3ieMh+cp9KfdQV6HOZ14zrhQe+jPU9pnYA+94zyfMl5IX7B9wM8y+BXejrR6032TdingVrsXSo4/PE9hB75L+St7fx9f9Pv5HFjvJ+903E7i5Y8l1ri5UTec57t86NBWieCZ43331V8jmg/OY18GXipD4A+8xl89fK8wb4KeTnPwY7oH73NTtqFDzovWOR5fJD8F71wPgi+HNGjP+dI+P/7wsfznqQdzP4a+7Nfx6/OEf/oeULSVitM4M1eyEwdjJ6VX6mAfOd5veLxGQW2117n6anLgS/yR9Dt5u/wTZmp0czXyA39aeoPnXXpc0TW89S1CI5f7PA+jPMh9My6CT4/El6eoQcfFwAnDyA66KUZ6xHpl/N3+H5DcPSaUou86Bk7Yz/sMkv94Iu6Gvz8KtFlnOOmlfplQoe6EeSgbgT5Xkrve9UfvNU0nmfOc7DDCsGJ70vVwt8Ur4OIO57vd3xW8jlwZT1jnxe9r95s/7hE+ODvSrX0o94JvIucv7jPecL2tOSTNB7+PvU6j3UH/vmq550874POYn2luGU/i52uFp/onzwHdp6R9G98QwL//HGNo5+eD8Z+nHdiv0zH05uig74GON5GwI/sgLzwybko8r5mvL+KP/gg34X+mEfhl+80eJADOfFv+GFdgT/coxZ57hYcuTm/Ag/rMt4fm5Wcl14mPMR/F9kPv8Eu4Gd9hn6aahz6eEj0kYN1KHr+3OumFz2e9S7vj/X6+zTB8Q/z+8LVWaks9JGhfuiP7yd2q2T/vsv+YD+uc7LXm1W8/ybvgV7Yh0DvHe9z2e/DJ+c1zKvvOn+6XO8Zh/z4K/7JfLPd51fLBId+/YTfQ/lNYZ5rer0LHP9/0utp4gT65IPwz8utJ+yIHtr6+1ve8dxb/dDvdYKDp5H4hN+m9o+zWJ/J3vg/frFULfzxPeS5nujCV/pcnvUjcXiL/Xk4LedZwoc/p/PX5C3ht9jfA+yKPFMERw/sh/Ar1lPIUy9pW/awf1ZxvNt+R12ulnEfCI7eH7U/TXO++btEX+tXqkV/7Bt5rmi79/Y8NN/jqnrdQJ0cfsLvgaPP98UH/Xc=
*/