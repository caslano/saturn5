//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_3.hpp
FL8sFlj8hKXIitH5I7kd2wy/AljqOi90U4FWHwTCu+zaATvxVuNBAHFUy8Ey9wI/HVE7s6dJEX/cl3ho2aK4nmL61O85LdMwhTGcMYIxLuFRExHqyu/3xtWTVKbUbFVsy4d1Nhs01sWmVGmaLr6/fmu8fzHh+kQsrs6lsv0wPnT0TKFtjji0+kl9GCxamdcLyXCuovV8Bfp9xApDHzz7ync5DG39q4mngBNY+cgZ/ucxgSeJaH63ExMZVm+hU7Pn+832ofiVwF1VUS+/b9RNAomYvWhpdTagLi/vL1BLAwQKAAAACAAtZ0pS83KQiqMBAACsAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDExMTFVVAUAAbZIJGBlUl1r4zAQfBf4PywNoR+QU5NC4YzORwntJVyog+P09VDtdSTOkVxJV5N/f2u7SSj1i3et0czsrEVAHwrpMWEjyKmGoGQAY6FycrdHE0B7agN4NCVID410AWxFOKQ6KLrXKjR9v82WUFgTpDYeZnA5uoSr0uJAUNm6ti1kT3OY3X2/v2ZCm8omTPzFQ2td6RO2yPM1m2+zVbrO/9CLCX4+FHzAk+AG3Tu6idclMuGwqQ90XMogBwo+/TaF2e0tpL/ZnOzQFJMVml1Q
*/