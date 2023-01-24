//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_2_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_2_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_2.hpp
P3IjJ2rnIqv5y3pS8yOe1FI7VZ+1m9U8rPWkcQu2Q6B9yWB4g0a5vEg+un2/lyLMEEiTOjv0xNiMedv9BWvMmRQ/OKxqgV159sqKa9ZaX/o4HbmHEV6muCLkIBK8YuFuNQHCSlh7hbjWKWkZcrrqVLnJyw1JNiVD2lLwL2Mj/fqoe6QO+5Jas2ijmnUvjDTbMqEmZVcD8+3v8noFeMWIp0DpNoTAtULzM/aBVTVsd0dD2ssBGvBPBxkWL/HV0Mpl4nMXPII77EdWw6MGVB8yHUeqkBiR2mcOqAZ36GXqO2YnHQa2VTz1Z9qhYYGYQuRe+Nf2EIgfJ14kKAtRqnUMydIBWq2AvxjC36minmRqGkS9CYOoN0mRYqxOsC2k8L39PenG+VCPkGjboBqkwNFW2BucmDDiMbN40h7uR6zeDmUm6c2SROIkj/vCbjWF3taRPjj+YVVafkFWg3zdbQ6xp4TR5hDB+3OzeEaKC7Z6q/MLyjwCUQfaOvu5gILl+SFl+iB5sTItNEGeOAhSFrcZooeiaaHUZ+T5oCA8HxSkgIVOEZC8rtCpsRpD2NRBUKmnSUk31sZriNNmBUAIxD576awx6TJZGtAlwnS9oBqRUMgYrWPekrncTxJ6XKH7cE/RNRblvNddO+KkFnR0TzlSrO68Az7mdU86h3v8lB4Wm886bv+uFl9nSCEJrkNr96quQ3TZ6TckX+61fr3X
*/