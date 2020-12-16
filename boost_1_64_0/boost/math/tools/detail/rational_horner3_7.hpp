//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_7_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_7_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[5] * x2 + a[3];
      t[1] = a[4] * x2 + a[2];
      t[2] = b[5] * x2 + b[3];
      t[3] = b[4] * x2 + b[2];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[6] * x2 + a[4];
      t[1] = a[5] * x2 + a[3];
      t[2] = b[6] * x2 + b[4];
      t[3] = b[5] * x2 + b[3];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[2]);
      t[1] += static_cast<V>(a[1]);
      t[2] += static_cast<V>(b[2]);
      t[3] += static_cast<V>(b[1]);
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[2] += static_cast<V>(b[6]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_7.hpp
1Tl1c5H1E9Yk8N4NHF9MysWbWALZaGGtvQ5UxfGlS+rlokwsxsRiTSzOxOJNLMHEEk0sycRSTEyFmbSRiblNLNDEgkwsxMTCTSzKxGJMLNbE4kws3sQSyAKFHatkdfK9e5Ncm5jbxAJNLMjEQkws3MSiTCyGbKyw0JN++fmev0kMZDm1HSZ7t/rgPtSFrAjM8x9qsSaWYGIpZJmFDUw/jb/H66bnNtpyv6j8BPnslnq5cLLswr4fdOAj8mJicWQuYVuuDEqPGMhkXur6P7zDz0k848v0yXoeue6euoWYWAyZjO9BqfNO1JNM5mXu+dG8PopJuRQyGbuj1V9XkOuI1C0wwjMv1d5WdCMGsu7aDpLVm1o0HHUha2th23Tgkgvx9aT5mWL7bV1YW8RHdknbAbJKkZPuY7z3sqquwvY+ysnfaPa2qs3ebLtXn8yLunyrz+Habjf6MADHgkgr1rXdT3ZsZm7EF0XWXlhky7MLcZwnixLWvYGD17vob1VuYUX2tj2J+MgWCKv9Q6sE9N0BVjVAWJlFn+1oP7LqwtbNmDGPnyNYVTthFRbWzYickdUWlq267360+0CrqiEs9MmNTagLWUVhLZr1HYhtktlhnvOzBLIUC1sav/X8f6doq3qj2IYlu/i5/RDPutT+kOMz9kcWIGzi2/l8TiX7U1hUZBO+Jz7MqlZbRNuuyVAXORthVUHCrJfu8HduI61qg7Cr3osaYn+jrWqysHXr9oSiT4y1qoOKzRV67SavyWVV3wlLd2/Bv3H8jLGqucISilzuizE23qoWCgt49N15tN8Eq5onLHPi8u3YH1l5Yb/lyv0Wx6WJVlVC2ODu5behHcisMMO/PUwsxsRiTSzOxOJNLMHEEsnKaNtnfC9vklWd0raX7GyvbK9hk/VxSVuQd7aj6EtkXYXlSf68A/UkyyCswObxPFckmyhsfs51RZCzKVY1TFjr8sOCeD0yGu/ebO8ah31BXWZa1VXF1n1iujfo1/S5Zn1hE1YX34tck10Qdihdzm6IYbY+x2krNTv5LPo1WTZht/YG4LpfzaF2gBnW/zQxt4kFzuH97THsL4Sss7DyrxfzeuJkBYT1/fCF1ymdm7oFkhUS1n6GDe0QbmKxZAWF9d955RT659zUY0giay3spxEpgxFfrGe5Ug+Pr8H4M7FYsrzCwuN/4/sMsXws3022YNVV/t/nPKtaK2zFL8XeoJ5kW4Q9TqkcjW1+Z1VNhdV8cLI12na+Hkfa6sy5sBz9k+yRsG05wusg1wusqqSwc3fed0ffJQsTdvVMzV+xv4V6bGpbV6PiepQjK2Bhu74jYixiX2xVyYqta5WVg/jZoFWtE1as51+8luVS6oMWtkbrA16gD35vVZR4WON/z7mGnP1AfR5mOGaZWJKJpfzAud5lOGa5lunjkjZ5XAokyyvsXqEVr9EOZCuFBbxetxHlllvVGmHrCubawN9sWdVDYV//6tYPbfSjvueobcm/00egz5MVEZZBbaiAYyRZCWG1X1ebgnySBVpEubtleZ2hn2guLGzk2kP50SdWWukePFuLcQu7YH+rrCqrsD7n/S0oR2aHec574sn+JSznkwd7Uc/VdB9TWMbTsxBf4hp9L0jbuVq/25HPtfoerrbv8ufxQRuRRQp71ShvCvoEWR9hmU9H/4b41lnVGWFHbrW6AfvZquKERc6cwO/yr9f3+bS975mUC7GTyXpuPfO6DPrgBn0PUFv+5BcDkReylnKbHfZPQj/baFXlhNmfL16AepLlln0inVcP1IVsjjC/LznG4Pi5yapGCKuTt6Eb9dysz3/a5PkviCwbzPNYHk5mhRnmSyYWY2KxJhZnYvEmlmA=
*/