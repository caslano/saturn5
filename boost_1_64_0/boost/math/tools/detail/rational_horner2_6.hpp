//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_6.hpp
CUsxAvMi3wiHojA/B0eGypk7Xe0lPtT2EtuoJRV3/8R/0NX2H1aw+tMVdk5fhK0Onvp4LQfkNDX+jdr4t9OpGG0J9lJr9+T1JUUHi4vY7sOqj9fiR6epOMJHYvx9P9jnWvzVqRGjHQH/sZZ5HogOhsvZdlTq47V7wCf5KRvj3yTGX3RSdYFs/YIGdsFYU/C+dA/uvz/j2N31y07w01iM+2Mx7rLpyWfJ1i+pIVW3f4uY/+7F4dz2b5wVpHUhOouRx/ude3ub7ToBFxceKVu/oiHxuqiwAVFmHYh3k7O0uCbEnetynN+ps/6J/c7Zw9sWwkvc7X3pVm69GGp/8ZJQIlznLsP8tCf8xRbBYeqcXXWy9RvaFMA5ZbI8h8rKMsKBd3ooGbrfPFTpwxZNH77dTR9Gc3MYYn/x6oMS4VonByh9+FTTh++oAecs+dCH6WY48OqDLkPZyn39FIU+fGbXN+yTiHdSd9Do+FtOHlnDroW3hl15SWGspP07W069JkLXh95+ygOHrYLDvvOuQM7T92L/BPuQJNeMZt41I95JcUpUWMMWi9el6HW5uvupP1h8Llj02fe6B+Vof6CenXAWlSpzGJoPZT2jLiseW1BTHssRmYts+RxuGerOaneVu7BNy134kUpcNWGbeG2E6KP9xZm3oInQa1AF/bQZtnK74PDhzkHYU+ykAHzqtSlSHxoPY9eHkrJiVl2If76aDwl+GgM9aLVznEKnzpAj/ImG4K3YvmnIh3yfNe+N82Q2/tnKV/jLR1Mw7i/EuEc9fSsyMnbRjnhNJbw34ekyiFP/S4sjhQWlrM8saCJ03/EPH22E/n8pONz9ehCtP1NjvLYB4X0BIxxY3x9xy1BnEb/7aD704SvB4dubtzyGijC0IwG+Ajj072qCA+NzE7oE5Sf84qPOiDN+LRiMO/p9nD78stsbLB4jDFjfYHHLULbhCx9twpsb39h3rd4ctKu9UZzS1HdW+So2hxFG5gTjkxu6BGUXtvjoJcyHbwWDttNu/FCO8jfa6dw/xHvRvVh9xpKKwrD9jQ2BEuCKt27y0Sgw+E4wGHjr4e/L1t+pLv72SipywnnXRnSR9x11TYh7nfjI5+SF7xAsLrwgdYFs/YMyUxF3SpJ+0twjWf0kdJP3fT9NiPuu9js+p67a93aNk8TBeLvsT5o+ABGogNxPtfDOjUitnXdayEVBfbw2/mU++hLrxA9i/MndJ6GG7V80M1O9DdzJtpO8tY0jE6IFMfE7XykkJUH3mxf56AvMhx/t+ml1ibfHETWdgN+6i3Y71rKN9W6Z3cP2KcuZCa8JcduGBT6nHtROwWL+hdHL0Gr1D+h7qJJ8VtuguslX08MtQ51XP+Bz8jh+Ehx6T2n9Uo40werfDf6TT3Ko35N9Xsg+jjXAQcpQc2OOj46DfdwlOFy0pAduniZarYmoh4V6aSN576q39zE0IVJdync12S1D+ZGzfXQJOPxs16pN/uhFJH1aI5JwXwYcmpca4MBZ6UZJ0Bnc53Ny/tsEg/FT7zweC4S1Phl+A+qajDHCIFLIdqtOSdDtwr2KwS8agxRrZxL2lmDQ+qIBBpxp4EqCnrsxzefEG38VDFo/XviKHGWqdX0O1oguiDNtYPWl7R6y3sNWAly58FN9NBIMfhMMrmt4A36jxypWtavb9SBqQg8YX7xVAlx3jgWDM8Hgd8Gg27HHzpOtXqvAxaDtBQMMivmyeJQAl790rY+ORW78H4JBjzWzNslWn1WSHq9LgHruBhgMbS/ymcuKATL087lJPqeu6p9aXVW/1ZqC89okqQseYxwMYHDnt1zho8PA4S+7bvlXe90sWwPWUj/uxUEfpj/PzoE=
*/