//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_5_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_5_HPP

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
      V t[4];
      t[0] = a[4] * x2 + a[2];
      t[1] = a[3] * x2 + a[1];
      t[2] = b[4] * x2 + b[2];
      t[3] = b[3] * x2 + b[1];
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[4]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_5.hpp
hIeHB+ny2EBzHrcU9Xqq6QnUE1iHZFt1ye5XiLR+CvULEyzi6x03KF6eQb47Cdbs4guyxcyNbIvEfHdOFP26/EY21yDYX8+2bKSYKGxkSyS2snacuIPP1cg6SOzrOO9tlEcljaw0F+ybvSUYtX+ljbY4Q7b0P190oueAlZLYsBHRIm91WAYwN4lNv1u9OfkArIDEDveZLO5HATYD246bwNK3dzhHdlY2sqX43A1rX+rDR+JbFMC6SqzX+hdnSZd3jWwSF6xV6YqiL1zNyA4xwSqPHPs7sepG9tBJsAZdu1EdwuoYaS79urVdWTN9EcUEsPYSa9ykai+KJbORTZNYh/mpjDQDVpsLtvHRHPI9ua6RDWGCbau70Jls8TWy3hI70HCZ+C4NsI8k9skLRex1qGdkBRXB1t1cF0bp1Tcy5iRY2bmHLpCdTY2sBxNsSqwbjZ3MzdTpXajjtpjyCNg8Lpjh0xfinvyWRraQCTZ6Vr5+9BywgQbB5nYeJO76eE/9XHrlsmRLDrA6imApVXIGkS7t1c/drO68nN7ZwcgsEgtvV3I++d5BnX9Tjy2jfLd0NLJPpfT+OD5xIOnZ2ciSmGDP/JZ/LM6TGGl+4hqwCqluND7yA1aSCzZpQQPyIaub0dbXQFZrb4Nv6Dl/I3MRTLXG569m6n0QwPIJphpbWIC5S2zy9mJFqC4AVl1iK8zbxfd9gRUSTLUengVskMTq1P6oIdnS3cicJeZfd34w2QIsEXX5zVrvrt3RicptgJHWV64CG1iv5UtxLkT4flXjeyaw+hLr1fh4HOVRL6g/JXa1W76FpLWGKe1TSpEPvVAXZB4DjKI/CCxUEWzw9c8biXMhRtuYGdmKVb8dJt+BlZBY96uuFGdpwKZIrNmh1QHiXAjULxKbcaO92OcIrJPEno8oR+llAesrsZvPKzQmO/sZ2VdM8qFsz0wqR/2NbD4XrOn3i26TDwON7BwTbDh/9IBsed+I/XnUbJ+ZxgjmQUYWJrHjbh51qN4dhHGG7FDmn60o34F5Syw4dhTFIAsy2ubBkI3fvO8a5TuwBhI76n4rP/kArLDEpo8bmEQ+aN7ZfMtf4jtNQViOkD1bmSL26QAzS+w/5SLEPsBgdXpjA39vR3YCi1UEu6ZcovnBnMFGFsUEW7q3jZnsHGK07dlD5j6q8WOyBVisxOqeLVmP4jpEHS/r9p/tR1qHqN95xafjfvIhVJ1/r4zj61PsAhshsTpOFxpQvg9V523LQU9JMz9glSR27MQDMYYFNlliQZV/XUCahRmZn8QGzLgVRc8BGyWxy06fDSYfwo22OQhk9c/NX0O2AGspsYC57UtTvgNzFkw9lx6ujrODSd+4UHxGqOuCeod/+5V8AJYmsW/jtog72IF9LNd1fh2vUXrDjKydxIZ8FCS+HRsJ7aZsy4BpXuKskLoc/ZL57BrlX6Q6Jqo/2R5DMQishCKV2yLFfqZ3Rhtt83zIev6+uARpBuwdiZUpPeMmxRkwf7msPD06jOIlRvSXrljXNJIyFpDvwNpIbF2Dbn7keyz265CVH9tvMaUXi20VMpfjJX+gfLdgLCH75T8dLpEuwDIktsHt9joqf8ONbLjECt19T5wHijMyH4n1LrSuJWkWl7t/mcAaSexeWuYTipd4I+smsRn/5euu46s4tjiAz01yDQLc4AS7eAkW3CFocIJbIAGCNxAguAV3CMVboClaPFBcgxSXUKA8PHiwEh5FipR33uu83zl3P5/s39/P7M45M7M7a7NVvz2NepJFaEsiy7r7+Aj+vspH1RaW7WT7mhgrZEHCIud324ickXUUdqCdpQTaaIiPWm5hK1/ifHfkc5huB23ez6c=
*/