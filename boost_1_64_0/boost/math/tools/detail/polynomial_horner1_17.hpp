//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_17_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_17_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((a[10] * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((a[11] * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((a[12] * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((a[13] * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_17.hpp
vfyrdcyWJnZ+l9g+nZv8Z0D5RpKQlFzKz5P9WP7nQfm5IRWmlM5PSNo9yGWxnE308pQjQXEkuVrTwiVPcnL5q9fyjfPu7rV5rql/+cp8gtf5HgJeG3SehE17I7Tw7prl2xnwKlTCpSQiKZLx5q28nbqxc/XajYV5Z2Legf/UuF/4LPjNS5RJRBSdwXffq+o5Vi+fjeNoeaFi/zuddxvvx7/+4N7WzBgjsEbtg2TQ+RbgFSjltUbJ+H/p/BGgs05YlK/pWed2r/iqWtdeftfrmAe4YPlL9+13sm7LxXCT/wrQzfPchiTi+oSpll/vEZ4Fx7NlnCTiw1q3yrVT+yzQJWlnNJXt2dOK60uAiyOeq2aZ1FP7lU9W0IZwvP601+u64FZYKkx7mjWTXatxowAXQ0RZJ22QqPDMzQNVg7lEftjjrztDiQvRVt0WvhvVBxDIW5+wJzSh0khXXvnKV63jyoOzLW8C15ghzTju+2D7Frv07CG+BilO1Bo009TPGxuqZ0vPBrrQ3OkMnV4N7PWd7kbNZdXLP0CSSTJlW3cdrp1DvQKUTWhxFjZxVqROIE2P61kevAuPtGgSRkVaozQ9HOCyPlKPXZj1aBPGKxc93gL0sC4x5Sib9Li+O+jxDlA2y23HvTWzHm2Cf2WNTdnLR5SiVcExN6tx5fqrruWFNLOM53YfBjw65QEatJ11qBN9y8H7sSwP3hbIaGVKsxJZ7eN1vv2LqW+1txhMcC5JPl9tvhZA/lOgToYGLoOgE0U+sFpOIJr8Z3v5V+euJAINKp+zQn+MFgtk6LslFifmhozGaocVjetrkItrxbF3RRew7u7WXFeAiyBntA4YlyTM77qxW1Q6axPMYIcfAi6bnApShUmv1jRdDtDfAi5e7tmcIYFsXxfSG8RUQptjHvscsOYrqkJIfm4nQVbz5zOfA/kisdxQQ8D6N08BTA25qQGX9kRxx23RDay1uzXOJuASKNqEQ3L2X0w4OyPfWwBfCmWPwHnWDd53vrL6hGR56JfmGRPBQt2KJZka904fBlxeepJ4ohvdTrbo9jHAxVBeGHB0yW2bg5pm7RvwMz3+qsFRU2qm92jwLuuzvRwVyHsbA9dNp9bzd+m0MUx547mbN63+4Dyfwy1834Z8gbCYYipvxDZ8Zun7gA8XhzXMJZfb+Ka8sDPV3RYwrLbfX4FNqc9tprCrzwerTRddH/lc+O3EkqOURb5tb3Yrf82kvRx/5+b8zLnP1QLKEchppgMP07vHf3G2v1fjNPRYWr65lXGe6HUdOnvPFenjb5325XhUZnasWKqbjTaLNv0/MugvrRHEeb22/Xb9axwGyM2tU57xtqlqM2zj/uJzh/2p4N5hG/5DP8stWWrRvl0/0++xAipByHmQ/SarKb5wf3/glqWPS+v/AzcZuR/7PBizIlHFpZVtw1UVb9zPfR7ktoFibOR/4qYzd3tv0Jfz6qhEcIyGonY/VzV73xp4S2xc4mP6D7xs5P0I4A25q9LSapPKbd5qvB8HvAHxvNgYRv6TvvF8fy/HVeres/XlXBdaGBmpnPc6VeHG++2BV2vDuA//M+8jn9/zRsm4SljMe5+qcPvuemovT03mxUxjo/4D7xt0buE8zME7UdWXtRPsdF4+HSUtDuLtOzM9H47lgCM2Agu4Fv3LuQzVc4m+nGw25QiWPKGDnC+uZe6Dtv7o84c1I4iYEmVr7u1j+YFlz/X88UxJaxdL9tE5M/b9sz7l4KlY+sbAL7jzxlC65v/34/lj/EEgX3TkInLD5hxTNbAm6N+/HLiNYJTL+J+46cj93BeAvblhMv+iS9YpNp2mjXZ/xQsgt/M400vyH7jZyP2Wvhw=
*/