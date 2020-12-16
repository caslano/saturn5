//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_10_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_10_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_10.hpp
aWPfUhm3L/NlzpR5xVVVGu3C3sY8vkrzaJpUpXmaM7L6C8bcd0kbZKwqWyFj3Rj+sRKd89A3D5HNWbd0KfOGyoZTGM7PTwf91hZlq9KyZsFxY/gO4g9BmXMVV0UVyHUnBGBHRcfsy0Q2YUkSN0I2tL6DrcXlYCwd+ji9x1KibbNYlCw82sR+dLLHA1lRqzyqdXnHuawN1oecyCasEjzLo4pTWciU9s39RE6yItIDP6tatosL3NC3zjVfvtXZJpWU0oQOpt/b7dh+40meLYvjVFapkuymLgOCdSpJo2RxJKOIxxlJg8jT/n2GyMesjGtZFpJjUHBS9nXnE9aXq1laFWnemvUZzlh0HfQSbSNetZmUuWLESpDOA1qLyTwuCl23tlGMWlcG69SzdE2XiTRqC8H81+/h/uCYL3MmjUtZtTxnbrMXzoUzZ4NvoO65PE05W96E4eCNDjouciInmCzgvWTGxjgAd2tCt9cisjH4GK5klKMw3TMxt9cichFTWaZz5QULvJKHdiEP+3LzvC4y1URlJ7WuH8Lb8i2ctN/3sK9Ew5tCgYCZ0kCXaV89TvuqTblsy6phvkfpcO94PahPpQerFDVbHVsdbIdngj5Lk6iRbZuj4AXbgPSOlchxVsmkjopEsFG3EiPr+P/QNskalcmyiTpRFAvszBhd+ye1zPImZ+gxw4ngWRAj+9tKtFki45bh61lapxlG9TDPapUnWhHHmOWG9+A5o29iqkqqvI06UX4+WlQXYucUzO2zSJ2gfGWteN3JiISIOJkNmk+TNbBpT0Bm17Z7iOaTV0UTZ5mRoW3nZB6h+bSNqlSRyU7mHK2Pa+8f+TLzmYiTOhEV29javET2c842nlGdbeq0ybMyYsGz2XCN8jStD895AR7OGTk5CmyHnmNUz+u2jpJEZmzEdSTVib8ROTiZbVVRJZyNdeNK2306CvYvaVOXVY6iuDD5ss3vroh+59u4KspGNmyca8TgOz9LZGMG1kG6E2IWur8M2iYP5JKybhouSxa4fg3l7o+CtZesEiHSggXm96aYuCaN6DtEwQsO5ixolU+/xw8F5StUnimRChY+LQ/Wvj+g+aRl3pRJXTKYd0+ddCqJ+kv5TRvXWZtHzMzTwCe68dOI6kah4lQ1qmadXXByroKl44xuhwe3vtBbpbrxbKAbeV7yKG07Uef3eijyBXc+ELQDz6OilEnJroFQ59+8M2My09oxt14N2y9ttOYnAuXsupHKTcdUTuRNk8VlSeRcOXEuvDumc3VVtDyOqq5u1nNcuLf5AJWJCx4nbZEx3YIwmOe8kw+McxCUT/KqjmKZD73lzHXTgbbs2tlxIwXfIak4fEddxjw3e5buGe34BNx5V0xsbGrFY9XUTDsiJAJ9W9ZrcWCTrMvZpm3JlpdWXe3mLush0zOi+NbrESJbMtHUCoYaW76ybdZTncnWl3a24K++w2O8k/LTON3WldRKluiVmeavL9O3vtfj4JxXxlwIlTATL2z33LB9Dyc0jTqSZVrGnTVkN8LnNrf0/8CoXdfRFvu9YI/1gYTqQ8LrQpUVg7WPl797Y2zlKl9OMRU3imdJxFZ722DZ1ru20uutQmZGLrXrSF8uSViVy7RuMmaOVfUj69UuMoWNvdiVHlwubO0Met4+7dGErotqETe6ryM2VIo5vfEYdB02sG/bMObgM0S2ZmmbNXWaKyvbt7Ir69uXwTSvexXTH2n7lxKq21VWFjxtOdP7tN7KMAnoRRO6zdmZun0qD87B2iguChFTeae1NH4lkS1YltRpUacRyOqFxvrAagy8qu9fWRqsON1h7l0rSaPpJu40ixovDf2RN33QWfHsXF0ZYKfaOeU=
*/