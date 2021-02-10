//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

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


/* rational_horner2_2.hpp
SCRgZZJBS8NAEIXvA/kPg6UXoW7rQTAsASlii2JKm/YqazJpgulu2B2V/nsniW0FL8lu9s373j6imQLnJlACI8xkjVyZ7kFYerM/kGWsA1rHGMgWaAK2xjO6ste0hqsb0LUtXQL6g47fzhchgUWWrWC+Xb+kq+xNXqDV5VCrQS/EDfkv8pNQFwTaU9sc5bgwbAYLNbuZ4e10iukzzJ1lSTN5IbvnKsY7gIqaxondMKDVr4H4zpu60w6+eb8RQehpCVTMrchPW9TWHGgg4tNjht81Vyiphy5yAZvahkshpmTy5/vLvBoMUOfucDC2GBCxUuNFusmWq3jcea/SdaZms+n9qCtdApzVsvzN2IXfka/LI3a3+oPqZrCS/t+JLF6FyvEV6K9eKw6td+xy1yTQ3aDH4KnCCBYucIz/0kSwlRImD3thx5h/+kaNd4/rzTJ9jeAhz6mVz9fqOoJIMl4QWp256vID/QBQSwMECgAAAAgALWdKUkbmIA5AAQAA6wEAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxMTFVVAUAAbZIJGBNkdFLwzAQxt8D/R+OyR41m6LICMUxOywIq2030bfYXFmxTUaSbda/3mtXNp9yl/u+734kwqPzhXQYMlHp0tDx
*/