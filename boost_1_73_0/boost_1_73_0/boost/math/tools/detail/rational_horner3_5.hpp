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
      V t[4];
      t[0] = a[4] * x2 + a[2];
      t[1] = a[3] * x2 + a[1];
      t[2] = b[4] * x2 + b[2];
      t[3] = b[3] * x2 + b[1];
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[4]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_5.hpp
u87zOk6KwExvtliGgz7QcDr/LPkAuBgkqJc68QPgR1fuBCdncOYH7Tt3UvO4b9RfGLyBnRv3knc7LiAvSVyk544fdE5G6tRV585AVliw7vSTHG6R2RtV7Q4/dp3UYOoj23uv1vIbD5ZmEeQN7L7zpAbz/37ZwBKY9rdPN83LTolV8wVrYB9QNzIvDsGvieAE9tMTS7V5YveIM++V4MaZu4ffp4PKZ6YKdiOxDuTvk0DlM0kFu5HA9+vvk1Qv48bl6Y4Evi0jFwSx+/tUV8iZ8EZxo02T8PcJofKZqoLdSBxg/T4JVD6TVLAbSZztf58EKp9JKthdvjKn2i//jZydAJe8neF307xIYdgy8Haev5fmXWK22b+Rkm12ScY2uyOpKoffZ6m0zzRH4I0n9NM0Tn+f6aR/5jqD7/Maxm+XXMHHkyTw4SYHQ6BIBjZDYVWWwZD5RYjKJ0EDu2ic9av3VP6eggBcI/eh+/1cv73VXgjyBRZIvxD/Al3VVTUWrzMfgJcC6yOmqos+L5w+UzyNBftsMA24jwI4YC/O33MPvqphzD50nTTNIoeVTHZ16dS+NK8d5x3YjODJGdVh1Qvf8G4Duxd+gMAsfZ73/7VM1wFVku80P8DTOABv6i4C6VXv2HXxFLt39dK6TOHq
*/