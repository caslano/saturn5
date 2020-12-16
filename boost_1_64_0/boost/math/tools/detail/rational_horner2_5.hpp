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
7XuG2yeukCNd7uQu1YLD3OVGOHDWrnDLUDkZUwIUAYdnBIcHVi/5FK8g0dru+C1V1hrO/pz1jn68j1HOnYhLhrKRdWpeLNbmxUoaiDcVd3jkepFtRh+iZXn8GPLcsYurA3Q3OCwRHO6fNPhy2brKyfslzIvGZUY4VPHdntFE6DkpBQEaBw7PCg4n5331g2x9mXrm4nykC2rTd+P1pWQnWU9TlQh3jf4zhe8ADs/Z58rfp/dF5Juy4VOme6Q+5JvRh9LKsVXcIBwZ6k0gdUbUqJ0RvUolrveZd/DWAUMfOTPXNBH6PcNjAnQ2ODwvOCQcY1XK1tX0yijsudKlPjS9ZIRDIV+5Bk2EXjPxyAB9Cw4vCA6r9qoeK1tfo2hn3DNMxVsNvPahKhyLFkwYHBI/2ep3uGWo9SInQC3ISXpRcJj253rUa2iimYhqjg5Q+9u0+Re9xakPdt/sb6zVpzUh7jXjgAB9DJ1YKlhMfHQ7dpqvUytqV8zyYs3ozq8T7d2MVU/gZwEhHe+L9AlQGHvOlwSLn3rPf0O2ih/IZVzgkSxK1vU1w4KxCpYmxH0Pt0fAecdhmWBxxR4HPS1b36QFAZwapkgfu5HXx453k7UyuSbEHbPrFKCJYLFcsHh/+Oe/IsOXAqhJPcIvY1StpvSihC0a4Zahzo+TA87dmRX221inLcW7vG9R3hGIyaRjfqw3xCFSawAEhHS0m8nKt1qp+VZvU9T15k8T7zsnTjc5vStNiPu84w+/80bYKu2NsHdoR2/oRUDqRaspvQizOVhuGWr92Ol3Ytkva7HstbT+EJyDBaVOZG41pBOMoWxNiFsndvidtwxeESyevWjjetn6rlMLqkkojf3rmIt5fayiSyLhmpj9M1RbHWF7FcotR/c5v/VTJXi8at/JzeiMBMX3aD1OxOoTZe280Qf3ZtUN1U/WFVUX486vEDzi9nO1Zj/XUbmrNlR6L9Zczg4dZbWguhh33dENfnoavudrgseKL88pkq3rqe1wvE7aXb6HMzfbmH4UF/KtrroY9151jZ/SwKNJ8Ji3af/bZOv7dOX+ak1Jt2MYvPmtTkdDlaJiDVv+jUuMO6b1mp8GYb68Lni8vGTnM7J1A/UPYs+KuvYjmOdLqIbxvoj6dHX+s9JPZ2Hsb4ixfxP89GE5ug9oRVf5WxLeBlrRjfWuXVUoxndSjg/X92Fi7N0w9jftWv7PDoxX8KeR8VyjBLmOZoV411HWFCP16Urnl/upGDZgjRj7feOLMMAPaWki9qC4k93WnfnvPrYqyldDUX289rcX40/E3/4tMf5ber/wnWzdSHPj8VuMv2kP7vGXRvlMn/PpKmb7ot+5A/S2Xctl5Y24G/aR814BCXuXYf83L/P60qHiUsY5jw/vGG94zk9noL7TO3Z9wMNOexwZyZSH2T89Qdr6Ol5bX1FVHIkV1NaINA22gz23DOUzL/I753prBYefr0KClIhYtnUGh2Sp//WZrPov+zixujDKDkIJ0fZTT4p1ALbwXcHiqYl+ROE2i3mAewyoQ9BoQidEGSp2FEqG8gXu9VMmYvfvCQ5PXtSIWMMntBhv98/0Sg47jHAIG+DgyFBz4wo/vYO5sU5wmFI1pXO8YssiPPE0OSA59N/bAIdx4Qp2DkqGmhdRP/0KDuvt98fv3g8WcgttQp5+dorkMMYEh7ABW6lkqHhkuZ+yYB/eFxw+XzP7MznSTykPluLrRMmh3gyHagMcqnezD0V+uhccNggO0z8Z8Jwc6WfUgrP/POyT1hrhYMBOKhlKH0b56RHMiw/sd20+ewJvgG2l33uotxpsDp7eJjgYsA9KhvKlTvfTEqwXzYLDe6PeRrTtc5o=
*/