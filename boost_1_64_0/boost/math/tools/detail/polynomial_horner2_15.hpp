//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_15_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_15_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_15.hpp
31WOOeM23v8+3J024ftwkoj+4vGO4u1PUXcUlwbTuMk2be2x0Zu/v+Tfc6Mga6u0vmV/Ikbf+HVLX+qJOvSktg0+58pKO3xcVC8d1e+nBeiJzd67rS/KRJI3nl8E0f+81yanWrCGNecd9/zKzmcjwjIJiyzZIGGnlzd2PG69A8l0psKvvDbK8nADnd0zlGABMTIw+i4wfbmIcy/M8zK4VX32Hao98E3YXfzadWkTcvgi1z7zt4VzyGMhcVZHuxw8h2vOAvVx4A0JaMSWrh9t5Tzbc/rDTN62OZzuApv8lm3fgLsqF1X6ezu9uY5cVSfdO2f7d3LcrHNtHXO7OMc9C77vDl1cqqC7ibdxfLgeJvkv31njbGPA8tlzFwenRNIdhrs5HJ1I9OVw9x7cyefr7+FwhglF/CX30TjbFLDOEd7XxbvpvLafc9x0rj7AxbvpPHCAcTCd6EfzoYBv2FXS2RKnryxCL6uj9qbfvnXvpVyz9R1v8jbN6zZQX0anrW+B87iPYfMrkUZpGXq1r7Ya+afvkWW4o/17Oc7A4yNq3qLGmeHbGsVeHb4ggcGiRvjdy9vwbixtZCqb4h0f4DibnBaebpE4nJMPmjqefppXPjWC47T0BlEXN8foaSxh9s5FFXpBEVe37NAI3+S29YWViIvI84vqf4xNw86EOluhxuk/S9uKX4A+5V379NLZwzOD2aUlM47/ReIvJ1xhhyULcCibv+u7JFEdNGEEPRLI0fh+Z9OuZD1QPoxBL/o047huVoiPbOO42/+8zcF1c6C7z7sA56lzx43F3S6nOybsvQPn0JhAnIsuh86T0xnROyLnbJ893nsnjrv2OHAbx117XHVw7G+NP729gMsWc56XI5wRe9C95S/Dcp6+IF9X0bvg7N7lXZRuuVl+YVoypF68hw2YDkdJwse22Dhuz4/cTcc7+nOIF96nBpzSM2mFL5w+dFheTkOZZcTgDRsKfz2Gwxs01p0imca9Kv0YD90TQ4zFRfc/Gc71HtjMMJkWyveLFQbhzC7Yd5SjgFtxIoV0zG1DjowXCXjvPhxDHO2K9512ICbThbL0fcK6631s5r//UXVd2/jxat6/NqF2QuCOJqmm8Q7Kanjeb5aIlPfHbwLcxrr1Jhx1OWpGRz7tt7t4t261kEeZVq0d69ZLTPjEOEZ8N+se3N1N2rEeQJopHARtnzSvAkymBSNCDHwPaoySR34Qf2qPDZloMq/y61seGvCO1cGf8W+7SeuXXpJGt3THaum88qVmbHjxJ6ATFo/QbKitvYvC4ckmDP8ZhkNzIP69f2rC57XvS11Gw/DD08cmrIZC+Es0DmXFcfLFuU+XiyHZdfGyhZtIRuw7FZttHEDC5hDDfCL2QcQwT9TfbEFM24Hq9arCdFw9bV5sBRzjo/qp8antiMvmQHLfHtPhrKug+4Pv26lxulyj/DqpV5bPW+977NY8rK8UR3tHjfGNBMT33AlxGQyw4tG7QYhTl8R8yN7Z4IP+NOp9gVMH1L4AGPj0AthphLCLiMFgNQTva/YTOAZffYGA+Os7OMCk+zLh8BYagIh9kDCZAR7vKmGzM4P1o0OU8HHC4Uu9HAy4vHDw447+luPSzYLBaS58j00d9eTrf5PGuXpaAyHO1GN9v444Fgdi7WbAWNYRey9iWFSUpi2EUVFZaXJxN02IY1FRmkYBw6Ji/ZRQ/ddZrJ04DwDdIAPfO5z3Tw5sAgzCumP06zYbDBsUjkPhjyEuSJ/uXKx0XECMz3HeRuHzs1b4NQyHjoXPfe5FduBzH8RYGijPDHfnPgzjcx+Fmfi6Y3s5ijjr5Gjeg3jvvGd8DPHOvGfvTsRYJ4P+zH7M12M=
*/