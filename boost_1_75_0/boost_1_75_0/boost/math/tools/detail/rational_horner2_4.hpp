//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


/* rational_horner2_4.hpp
3mTOGa0nc844MolzRv9JnDPuTOSc8eFE3lf5Y6HnLDGooxuWqP0rYYnv7pSUxRIzOqK+iuUVlypapfOkin5Pr0xf5czTleKIqjrP+io56Zwjfnn6Ifoql7SK+rqgrWxf5b+TXFgiJLP8vkp0W+e+yu5zqK/ya5oLmdT080TrJaZVrq9i7OA5n8z19ayv8kwa45Ow9g/PJ4KPUiG9fB4Vn+zWeiJZ3/kPwCc/tK8EnzTSVsgnYJXbv3rZhU/qTFP5ZPov3kSKWiFS4ZO8pzmfiE9zPgl8mvPJ1gjOJ8924HxyOoTzSUoI55NmIU580vcVzCevveQBn1xpXYpPClqXxyfX02U+mUVKtr9I5pPj81yU1R/enigr07wH45MGT3nKJ4O8K+QTmBG06+dxPsn+yZuU0P/+NIVPDkzjfJI2jfOJ/zTOJ2+8xPmk1UucTw4mcz55IZnzSc1kzier0zznk4nBbvjkjSuET2w3y+STV0mi/RdlPmk516WKoqt4UkXvz6kMn6S1rRSf7PPyjE9emsP55G7Lh+ATq6SV1dciclQ5PhnzkgufXH25fD75p6Uzn+zNRXyyfLYLnxzWeKL1AmZXjk+KWnvOJ201nvHJT7MYn0Q//vB8UnxfqZBb991UyL/CJy+Sqq5Ysp+mPgCfLH2yEnxSUKL1qH+yINWFTzJmqHyyZ2UV4JOQngqfzGjL+aRLW84nx9twPnnP
*/