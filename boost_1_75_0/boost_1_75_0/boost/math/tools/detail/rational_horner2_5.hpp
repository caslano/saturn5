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
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_5.hpp
xPnkemvOJ/Nbcz5p0ZrzydknnfikZA7mk38sHvDJzcal+ORq4/L45N05Mp98QkrG+yepM12U1er7Wg+U1Z8zHoxPTrTylE/87msr4hPaPzkyg/OJz7tVgE/GzFT4pPlMzif2GZxPLDM4n1SZwflkuYXzSVsL55OzKZxPXk7hfBI723M+md/QXf/kIuGTbjfK5JP3G6L+ydcWlyr6554nVdTXUhk+CXmiUnwy/l7pJuaiwtaACmtm4XxSs8EDj2F1uaMor/A7lWETGMM6bXFhkzdS5TGsZusITayRaSI5xYUmlt/1RJk5pldiDKugheccobtboYCBA+3Z0xlHHDQ8PEd8dVsR87nbj4ojjHc8Eesb0x6AIyY3rwRHbCz2jCMSp7lwRP05KkccuHefzo8YFY54/gnOEfWf4ByxrqU6P9KDc0ReC84RQ1twjtC04ByxtbkTR3xjwRyxZLYHHLGyVimOyKpVHkfMsMgc0e+f++oYVv+XXBTQnNueKKAvkh+MI9Y385Qjrt3yjCNWJnOO0N29D2NYd+YoHLFnDueIuXM4R1Sdwzni7dmcI9rM5hyRPYtzxJhZnCPYPjKUI9qkeM4RN2u64YhTZwhHNPi1TI54XI84YsdUlyq6+F9Pqqj11MpwRI2gSnFE1H8rVGHbQYXdn8I54pUaD8wR9W8qystws7IcMXq2C0dMmSZzhOUWaQfbZY6InuLCEdP/
*/