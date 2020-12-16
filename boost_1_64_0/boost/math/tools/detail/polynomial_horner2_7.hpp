//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_7.hpp
3oIwDX3s2LKR0dnaQpeS3Hqe+wguM+dRXmbhdftHaN2fdeWFlIQFzYqqKkn3+Mbp88mu2lrz3ud3+SpCkyQIiyA1bDDR9mN+XXJ5piMaVEURZqR7elUeFFnfqcD4FLv4snG14DSMCTg/zZlM4Tf2f4x5siDI01wkpGmcT507ISPVGR4TswDpgBEqqkA2pHCD6bgatcHLyKQ3cRfnHP+x+lzXxLOyZ8YvGUJ0mLEb2pUbWZr2x9Vyn7jVp4HjoaGD/bF0c9xsZZ+7uUuHmb31MZjb7tBAKZbfxqK5pYMxx9WWfniHpduWYtP/2k6X3hhY61ewy6GZccOehZO/bDVr0LGla9k16gyZPZk/Yl5/Z0rjyB8wzt/pqnQ7/zC+y1CGaU5Zft39zZ27HTZ9HG2tGcwXbmQx1k6cOmExEP8NYWwB3b23rQgzWIGNDizfyLZr51t15hWk3AI6PbZsRoFnVEHUuZWZM7xwGOicgtqluAY2O3fKlXHpBQpjAeDMYmO/tckw/i6qDbxY72FA+s1Sfsm0jze4NJCg8gqwdbunNIJlzB99ercPbN7DRm0kI5EIWBqw6z6vu7Xcp+Vyn/YmHUFnZNLa/+hxYxs+SQd5s/+L2tLjhlrVad/7HbIYrC7bH2+4EWBcAAREs/sAX7+xog9UBejezgcsFp/tveLWDq1fhN2reqHSPcLA/kMTDc3ofdjrm0lalTysr3u/3cyhXHksJUUQZiKpKIF33NfAA13fOIUVXLMXcmA/uNXBNtXGbydJozdbP48f0l5ibYeLtp5uGMJY2ApS9WRjV90YY5ZWLW1+K6LBQGPXG8OIBi3E0G7YhmiQoqmvB9zcpcFh1IgZDd19p2/345QbCABtGde39+PAqcXF7LpFP6YnF8Fuep/pwzR+g014O7ftH76ljzPZN7LecCuEMYeoyiQanNg5ELfq5m37bdpxJi6ewl1AOHQga99+3OVj3F5gZe27rY8zajVneDO38zHm2HJZXbuclbfvlly5W27v8zRVMbvYXbZvGCFMq3Gwa6bdLlZt7s6unHDXv/e5A8KAITL8M3dENOsP5ehs750QxsuKxU3vQbie14bsXaE7+7j29vHDu/i49vbxhr3tOD+O5em7+TjTpVC9HrmHhxtcr/YN832YR9WrHTPuCXS134PjghrMG+7lYHoIY8pw6d6AMZ6zIErthq/LHUNb53P3AZyZb4DbiUlH3A/RWu3invsjDLKLlx6AadYuwlk+ooG7iqG95sGIhmzm5RFEa3IzpW3TqEvb1CXF1OOPxzGfPZT352mW5+uT18bTzK/MubzLY1wxrD/BfkzHbhi2XthDPZx1wbA27mEIg879TezbRyBMq024iDDQkS3tJQTRwF6YunhD4NI2dScwer1IMd+11MVH+bXxrLpvUsSIx3emsPFoExeHHCjsm/sZwoCS7P5tqWjeBPB+Wn5Dv4q7qTuHqxS2dWpm5/HihNm30s6esD68lYmZ9CEc46VKeJgGsbB3UjZsixdEYMjsLbv8NCdxlBY1j8PrnfvBXSjw019t5AGDzbFqjQ3m0SMyzWZ/SF3ccjHunp/89wSpa5agrTBTl5duDHR0K8DeDdVxgLcgjLGdjkA7TtykFavP8gyODbfi1Mre4si2dhys4FH8hJu14tRq3upjfnsfDjqpKSu7RT+9N6CsI7dsx/plfcOOdpxf1ufubMfZsto5XT+uv6yHdzk41Y7RvNWhu294qnZm5Oy5Lcb59IsOHZSp6Pbd7ds59F5LOsYPEuEMXfexDupjKaEJC3lZXve+vJY34spjESmSLGBx3r686h6X1aUWVXalRVDMZdgn0/k/fnRZVZyhiyFLtz4=
*/