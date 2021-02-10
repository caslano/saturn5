//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_3_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_3_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_3.hpp
KHnElqc/+RdQSwMECgAAAAgALWdKUh71k3yGAgAAFAYAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMDk3VVQFAAG2SCRgzVVhb5swEP1uKf/hlqnSVgkcskrVEI1Es0qN2iaood1nF46ASmxmTCj79TsgNK02TZXWD0NAbDi/e/fumXgGSxOJEmfMy2Si6OcRm1rpuJyxyzAMuhsEq3XYj+ar5fJivp8UWj01L4awDK9vQFQmZR4/4Hi8h2YfYY16h9oqsxiZp7HIG3odCyP6bNyxHZhOJvAdQWiEJJM0kDFESuUj1q92wS9ElCIFf7Gnp/Dpm9K1Iz9DcBnwkxPbsacjNlfSoDTWNcqNSV2Yno7YiIVpVgKdIs8P2DHdGiLZ0yCSQ5RJcagXNJaFkiWxjpSUGBlnMnHem/SIWLyC77WhZdHj++f6LwTf1+bxvRlI/nmetUC9R6JuQgFlR2XGUmOKkuKHuZegMBW1Z8Za97H1+pp9WK+DBevd6fFDAHhSbHF28DRUZSY3z02uM5OCZXULLWnyLTxUBqTqLN2WofFHlWmMCYn3UEB+2G6poJ6Zy3m7o2xhb0Qunho7Ebq7RC0a25l8PXWP2uzB6jbk7XRIB/vVR5dEaxEcop75VFQxJEq5
*/