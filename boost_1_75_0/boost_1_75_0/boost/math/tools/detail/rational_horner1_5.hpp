//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_5_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_5_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_5.hpp
MIQy4fu3Dy7ncXBF5A+GOJexVHjoAPoikn/Y0FkIa3yVGB8wJspTmGwDq+JiXZnvW6rstCQDa7AHDpMHMiUGI1pRhpflVRlhfFVGGF6VEex+HpdSfL/bTFGpsToYmEwaBh+bL9qTI2AQ0lPyyHjQRqeRcZN4iU6/3AEjWaM6kQJcqP07T96QnPAGvRMFkTDm24myGk9Km35P8gbF5QOxmWyLEkkf2mxbnATRG2De7rLQ/BKLHoVDIYA38jH5U0EaNdRckF3/TwlErF5Hh5k1ApvT9gOH1yVKN46OetyRXWKz2GPeqhur8qQS5PoCRRkfOVfirUtxgXK4wEPM7xYuBukzr2pcHifmvOwCtFL+5gr2TZqrFUqu4uS3vezFluJQX5E400FAKoSCF2Cx8Qq515FoFnsTuCxhbcz/0zs65hIkqN7EAvMJCmRPurbTr+aCh3Vv53Y6cx5cjMXNi46Kr1BGxSXDMyRdoS/L1dgo6xgNHjUPQALlMeWXyDf1kuH2HF8NqhoczFWdzoxS9CUFT9s5wL26SFGJIS9DXoa1iU0uUzOKQHvG30xl2pnKVEboab9IWf9634eifIOsLFd707VGK9jPUvmq1ZvHfyHPI12qNIU1rCkY1vOmAEKi7cABAWZT0Lq9hNlKA6BRiRMixVumMAtRrHsp5DMZ5G2lIC+UgnxzGhokhYZ+kBFvtDe+A4i37m6hLB8zytDK
*/