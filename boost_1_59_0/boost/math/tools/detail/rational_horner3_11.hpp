//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_11_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_11_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T*, const U*, const V&, const std::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V&, const std::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]) / static_cast<V>(b[0]);
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
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
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[7] * x2 + a[5];
      t[1] = a[6] * x2 + a[4];
      t[2] = b[7] * x2 + b[5];
      t[3] = b[6] * x2 + b[4];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
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
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[8] * x2 + a[6];
      t[1] = a[7] * x2 + a[5];
      t[2] = b[8] * x2 + b[6];
      t[3] = b[7] * x2 + b[5];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[2] += static_cast<V>(b[8]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[9] * x2 + a[7];
      t[1] = a[8] * x2 + a[6];
      t[2] = b[9] * x2 + b[7];
      t[3] = b[8] * x2 + b[6];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[5]);
      t[1] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[5]);
      t[3] += static_cast<V>(b[4]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[3]);
      t[1] += static_cast<V>(a[2]);
      t[2] += static_cast<V>(b[3]);
      t[3] += static_cast<V>(b[2]);
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
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const std::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[10] * x2 + a[8];
      t[1] = a[9] * x2 + a[7];
      t[2] = b[10] * x2 + b[8];
      t[3] = b[9] * x2 + b[7];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[3]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[3]);
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
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[6]);
      t[1] += static_cast<V>(a[7]);
      t[2] += static_cast<V>(b[6]);
      t[3] += static_cast<V>(b[7]);
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[8]);
      t[1] += static_cast<V>(a[9]);
      t[2] += static_cast<V>(b[8]);
      t[3] += static_cast<V>(b[9]);
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[10]);
      t[2] += static_cast<V>(b[10]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_11.hpp
c/V6A3MI7lbhTNlOPDpg1deVG2nXhoU8mcc8QMuKGV5ZifnOHNQEVQ+Fk+Wl2d05+yxbMp/t/nQLygoJpMVLul6B80ba/5AH5xOUJNL1RnkJoV4352Cr+54isLsvbuinaMppmq7d2xI57WEikqw8Xb2T843soy/OVDPyMGEwc9bfaEf3dLVFJCsppMfVmc9RKkQK9nJOs61X8k0VXqudhA9HdhNGvthuBlFaO28aCxSAx+lDBELPuhhW9pZJjTErOEAp2P06jN96nkYtWqBPXFzH5cSblgchdSTGlcrvecyQ9JbIwyLt+03ixzodoDTq0IfnEHoRjeg6ZDq3eJQs8xmbWm0VFIIsU1dJ9m8+jiaW7cDSiJdbb4I8yBF9s07JiFbQkBE8c1/+qFq7WHK2qv/yvJ8kMbHL1MplVO9+r9vo6nMDdw3pf+kZouqUbD5Vpng9pz4IH4LBINswREUn4amJD+cfKnmaREWRIv9DNZWAZwuyvEvUq5oF6E19a/c1K5tuIVb8BxwlcnUIFnpDSjVuZdWiKRoKFsa/wK7E4uPV5XaP0PkHmSR6yDN1hHRTxeGmZ1p/yJEoiSI8BZnJxbz4AIVryfIZjY2T6LaWeadyBmrkJoFJrvxV6DZHXxnW0Lgyqj5570P3mCGHYr9uDyhIrLrOj5Y8HEnAucS//z1YL8sDCUGl3T8Wtc7MXLzvTZDooI3Y5n6t36urqxzXUdd8Hmnr2PIilMHhXtLj0gEYwBOEshk2IN43wgPM2Y7AHq//Z387lqmb9CWgBJ9AsyOtifaB7KgpsCyuqtRXaaIWA8LWoi9hFHkFcgXOvG79v0q3BUUpiZOetUyXyc4oqwJjJTFJ+6BquMG0hlLbfhOf+sC3y0mgJE1r4gYhc13MI68fY7mrB91pYVfu7RCjY/e8Eymg2WfzYz158vxXQszckFRWBUz++LPZNbftsQcyOGyL+Wd8tSO+Quo9Em5/+3hd83zP9AIUfLU+Jo9+4yQWJRQnqM1gl9vllKTsNs/iHNRms2FYFeDj3qijuh6Zd1jLQ8gL+buPaUVxUAG0wPhe3xryz0RFeP3U9rjZlBXVsssTmTbA/N6EA9I9+beCJhRAZ8SxW1+9iXkfObcAvZu6OpBkgw7tT7uN7jp4+F9geRzdfXJsQPCxVaJ9egP1qTCMm4HaYGrccd+q9vczAzK0OZHgVgadEgIkA0U+3s9s3MugB5Zjmavm19fuiWfd4rSPQZdaeMywakoC2H4Csv6zX68L6dCEX1AX8lXI8nfdDCx7CKtWDLKevC73v81Qvk6oJbmYdQZ5Q8aDsp5iTpH/OFEI0dOAj4/p67fKWcVDt3sLyJF4A1kMciw6k0K4b5wHI6nRiUQjhyJT2pxLoBoP+4o2yZHXeUlZrPTrnfoqnSJmAIJeMvjw/HHEKzQAXoL6Qt999/3OFj3W7gNuvozIXDqTxpOuUopnv1ez44Qmg+I7ELR8EyHmOpzjxnLJPV4lNt9dcOWkgiDT3FiwpMdZbsI8jfaG5j61DmQcacCW+p0MOJJhGvmH9s6m6CMvku4/yC4DbBuBF/eoRIQaqOf9x9/O1wa43GCMoql1RxxTwYoh2feNuySd1KQXDTjwfMzpxvN2LNbTgp3S+XkWOCIBVGkStsmZK+REXeW00NGKLysLSQr125zxCjnbx8zuC4IBcyYWEbiWQN270VtTHLf6czwDN0Z/jDIVsMtawrWXkt7QFFh+pTQeIZpPyfVnl594WL1P2rS3jE7D3O09DFYcUjHwj1CJDIAXkUuH6aFC1g1H6EKrlbDfaw6fliMdsBXUizhjaR9pH3V8y1DbNLOOK8jVRSvt5SgQigIYf6aLZ8jz6wNfqtzwOojm7P0tt0RdPX7wyl606EOwPmTAbvSdZpkYd+3cFJqw5myTBjP8VSHY4/dR1YR4nSZZsgHuQaLAvDmJh7JVv2ZArjfDe2+LxnTq8rpc14vidZlv2z3S5t94yvJ7XJ7LgPJBBezbzcjo1dQsXMa9JDb5BwicsgHQpcZ1LZlOuzJxHHJ0iJRVUTmOC1MCK+sj2lzPoAFvA03D+Xg7ZszZxVKSdRJrfMu4cZH9CzJ+eF2pNP7XfgDpearWj2BgqjSpqaOrX6Mj2ZI8oXnI64/4u4d+xO2w3to8bM0GuR1B7qZIefQFSxGes8Etr6nc+bCHa8MEQRRezpMWsQYxNnkaEjotteDZOHqThsR4f2IZHSBDx4ElluPLEwSsskQrv3lKa74B1tng2DonJ8Ur159tMUrdWv9j/ZyyqxktuUfOmDl6C4/T8a7rw8+TmFtw09ir3DGQYuYopnPIbNfQpK5z793tZLhoKB4ZF0vmgRDIo+rcoXXfI0wDsLUqNdYB4Zq2RW/iC7pt54IQk9PMB29m61uSkA8Y//SX+lGf8NxOcTrbktl9pN/z0rQCX+WBFEzKKXKnxFNe6EeM8d2SjrYlQOj8h/prSCv9zm1VQ4vxsBspB9wIQrx+kJnyatGqHfQSEge5sVpbGmvFJ0A63uSZAEmtG0ct5QiTDCLTctNVyv62zi54cF77IUKRqy3aNSw5gtK7rqwdYTEo8q2/MisLsT/zpISqGUheBmmH46GWpsbyM/fxIwrK9vAQG4M8zMzZ0bhulGQcuJQWn12yEHclgmIReuDhuvN6/E1MChsDAMtlXot1v04zmTWK0lCREurcuCTS0pQL22GZ17Gw2bNjr9p9SfnxhGcDHuGkc8jrJciIZ3ieJNON7pYkRuK3wkFcaErgqvKABNxNlo6Qk93jsqyekKuV5Bj3rIw/UIaRsLoIRHKru3/27kHxy6kWZeMFmt9dx7be1SwpKXlRBTn//vpgRbdA2MSCG7p5k9kcR+Dz/vKL7RK1P4j5WYqJ1l9Pm3lDhB8eNmwNXSwmZ5cDBXX4d+3DMTLyuXLMI07hTzxoghLyWbCYQInTojWvWm21ESZ2hg1BwJqhJN39ohIdHjvhlBmfsJnSRmDsAsgwPATYOyqIODsOtBIFLod6Iu7sc6TyAfXnHhqKHAb5wYP7h7yssGT5EW8AuSdGp1MORtPv3DdxjdMLPZI/Odv1ULznT4aRR/p+K4gDTjiyeHtdoo9+yB3G98zgOk0WqziJInUeDc141/4cqeS9lEmwvb3DKi/VPQRSFYVgJ7wAoN2eekX38Dxm2kTzyIlpL3Vzq7FQGSl/iTyTxCxDb9sne7l6Y69WgiQwPI3lvuqXJ4Vkp/p1W+lvixLyfHf7exUsDpmnEG8W0jOJuTf/NkF4yxPC1bvEUokp3WUmDNU8AECyJiZwHrz/bSB+dMSakpWDin2Fl/ejjXthS3hFMAj58JNukCPokdC3FrZGtrVul7culMbxKSHchT3rEKybzLMLs6u0p7YrQMK+Yk5Zyw0FNfpRWjgetl67VaaXxtRb6YkbQ85JkBM79tRX4Ao2RPsLggu4Ym+aHuowM3O22ePEf3xH2fv2PXyBsdojyWdDD5u9VqtdpzkUG8emkZy/ifFSIo/jSFPJ8pIK6V7oNTJYF4Z63wvxoMCUfKZBLP++ckQTBxWNmxhhyemqYQCHRq+8LlG9VQrKzsL1pRBs+A5Wicc0cmgAuM2+mYcLk6FrQZeRxxSpD6HTnNYwrxdFxfLZe7UYORwPFlxxR2rp6G9hbhHc4LBvvHaXgCFhJhlgxMDNPh5jhbcggcD1ll9oRKSUptkRjzqWN+AgnVS1LgA302BpUrezfuUnuQx4jOU8DKQmEGkXVsWL0MdU7gfBefKVpUg1Ywmy7gx8C+ipNQMgTz35vnVrzZAjs7zROXw3BfK6zgKYYDMZ8FppFkYgL0FaK0xCv65oQN1LBt10ZtCDe8jXJzaq6kQAFSzhdsJoJz2rQvMN76bNeqoQ/LGBJNvCKcAyrgtRyg/GhFZMbvtp6kh5sdgXDhzmQ3wWSFjJw76VDZ+U5YzO9E6PnzzCHFioJvs+Y2b1HGTTCsl2nm785TOgvYebvwBWkLccR+NAvpLo9gDBBYc3CdvX8HBd2BZEIkp1MysWIyJ++9RS0UXXKrcDENHKmoYLUKQzocYdzxpAAQri/bLFw1/KpNERw8DGQG8sXy80FcYy+iYL8hZFwOyghepYsGwyE1SrrOVtQu86y2wELqCEk82rTZGN0PYg9qrOdW0a9WVlTTbVmmv0mjdGnjn06UXpMFYiZ+mOJZ5m3r954E2hanTfqvqS/kbI12DpOPLm0Yh2Nmh1/S9jp1TOf3unFL7DW35cmIgXll9Vb66KXtX4ErOrJEZq6R55dIR0DD0D7LeKXV2009aJA4W3hSIylXoTATnDTXdeLrBLN7au1p8SISFl+KU4HiTeWWJiNG2Ux0Z8mmGDEBm2AS2rz7Z4DPNu8He8wVeSxbixkB2p6W2pJwUeJ0KSMRdDzjDzGNKi+kPcYaoGhafmBy5xSmjL1tU1BC4ruSwLvcdVP9LIC2ydt+Dtc4ZJmLajQYW4jE05ZQWOkZk1J1W2e/BFJpp/I1wAoSGskseKJr08t7ao8Sx3NBubuVTq9FQ4t7Tl+G0K3tOdcM25NoBVBH3JCebdVEJA4YzJiuUWzixXV++KgaJ55jG5pSUGRs2gLH2oY+JWqNs/6hJZl8EiaaJozDYF8JtTs8kf0vHzBVHBuObRk7r465bm+/KbRcnGXoqvk0NEWsb5Wtv1aDeInrSe/Xz0qbGBTdABoqRN7EF8Ct4z//KmE8Yx4A61TyyJX3J2S3uSeuiFtXGiWvOy7o0m+1Ep2oMAtt6907o+btOWnFEno+fNgkyOBqX5TwI7x3tnKovth/Sfp1KkJ7/UO65WNAnmwcNRFKt5cyKjkpnctA0aHIV9a6OElBKP7yTEZuCP2AlvT47gfmhFohWqETc9YPIY0dBtfeq10g1nYI5lwO3kpiUAUkItF1kkhS8I9gaJ4AAvnBuAmb304as5hXAgUGPZH+d1E+rC9eWyvkSspKaPdF6Wc5O2O+K2iccjwM5WGEA1WaZdXyuYxNJU2wzbWYvlqRKuMvK3vqdI+brONvsQojZiIJznMCUTcbgyNP3P8/gNFsFOMHNrDbaYojtwn8gyf96ChtzU6K1E0IriFwz03tOOH7llJnUwHdXzjEciRJk7o4T9ywOEu3sZNhfHtN74RYAZBLn+uyG/E5bGdPrE9dSwE/1B5fZ96rEOmggRXfvDhAM0SGNHKdCwO2quTNSJczh6NCVMjGkEFXfYpK0YtNdynaugLsE2eNoacAU+gsgEkOydAGcN7rQpDdyZrVvPJ1KbaGeUC0tOZuMg59fEe20ZAYJJPBfuxurAm4Z75ZhqynbfcViPzsmXvSjJdofHt6DFkDlkioFLipVC2wbLL9KBpmoOPWeFIzzhNarSpeqLw4Tz6KmNcjaHt2EaZImcW5aivf0CqBMytDdQJ+XQhWBlWxuCIbTNdtAeDFffLqH66mOqMqSH+TK721b8N+fbaEuQ3JQe5ICmhouYIfS2prYxujXt4NGaRM1cPRSq3u43Fy0wBuOdvRJHu6pFWCvPAOKeCZTwB5mwk0OE8sxwnTxQAjXb629ROSXpo6p7t1ZtE5Z2XjUTWR4QtQwQ2A1T0lvsSGKEMsLGb8kRI2SbB9P0+EWp7UlLg77z/ZhqtYenvuwOIrsawunWQ8MZQhJLrpBkvxNdMJ5OkJiupOfqIEfgPX1WMs+jWVjSVdTI6RZQl/nbkDFREEbPRMgd0DAOqsbbc7h4lTaXr4J6WnwosLQh3sQcs/o4eccyT0BOPN0pdWbIoaBH3toeqZXkNXaSNdo9k2W99OxJdYMA10lEQSuGL07GAk4bY8s+TUdKpHfnWSCZskN/zYZoEHbMJDrh+ChyebDoEXCkMm138rOhLAYv/sfHUSikrmt6h6+NyUi/NTpMucYsN+RzsYCGVOyluMFHic/XVhk/UGWn0Uxp1mUjo55xaBhker0OHmz3A4WFnE4lR5jKlumSYC4TNSppIg6HxsJ8tEEturgWdchy1zTO84JTRdBcCs0dnfnCvbzsarD6lhaCdWMRW/IAkNxPwPpSdzoNfx3pHWIjD692eYNZV7gHovmCoGOVdP59aiuks0MLD7bbXwb/53WSgqbssVGnUVUmeyKzb8kWfSEXbm5dy8vN+LGnisKD9SgsbGMS88driFCjsRWxuOJId3pVIyMSJITMv4aaNllQscQJ3MfMqzd/LOehWQFx0x/TH+VxZ2IgxjiiT9up6ebS0I/lIOWk+EVYGZHy+tGewibSnej+tW7beTXJ+RKFHtvbszppD8FqJvH+HBPCRaddTl/sHhgcd0tdjlJFgYUSFEfqMcDZ72uZIYLMvo/2QkWtcUXRoa0O0kxClXTMeqH0mSvSzt77Sazt+foBpwPqeqhEapO79BnjCx2A0LQ8cStkSLFTf4zHkNjh6zyQTACO58Muzxtej+dQLbBV8tUyfLtDsH4X9XI8b244cJLh3zSAoQQJrgWZ8VEZ/TtHco+7GWwmN47KCsyaJw3xMrF5Q9F3cBlWX5swHIJhCw827CwW2hPMnLKvuoi+GORoK1a2KnrcGUFju3EImu5B9sJzUj+9yJmF1W25YUOrcq2ogV/COJDBuFciaD0SoziU7E7JaAAiL7kuOr6TGDMLMtc0Hgw2n154K3PaacoUusL/uVOMhgQqA0dNbkJ2cwwlD2t1j2KE6FqEE7WaZLGY0TPY2ad7qaHn9f5ZltGffKZ+8DjimUq7J/93a9GV5iHcOLjH+DgSahmPjaEk2p8RUFTcJBdRrg0geHg8pGuTbzHE8pXUohy15OUXSnzKkgpODtPiMsZSfqRDu5uXK6alt0t1RmGEJXZ+GFjIpMydH2wVrTvxNga56HTOO0kWEwR6Mc2l1Ls1CDlEHeGzBy3o8VflFAP7BbHjQrrZiUY1M5HlMbjF9k3Gi2OTyVHgN9fMcSanHtNiRkyMvDOTnTYcpVXrPES3H8a82iZogxNCatjAbQ7MMPEXBI+2WXSMKMlyvgJMBMvyK2ojT+SGt7C2Ei0/ih4eD7TnM+5diYXzYNfD0VCYzwGcDjf4Ri7+sgzoWr/yIT0H2HuzWyo7k5pUFV8+8n4vU8kTaK/Tk91a7K1pFG+0rXEd/h2XCCPf1J+odzQhkYzM3bjVl1SR7jq9d4ohmOch8Oro7jFBHJ26vDYbzQJ0P4wRpK4XezdXLSYTMp/6jxe8FCbbtGqp21YbvjkXoR6jEa1h0ZBsVP8jI0msxFKJoqsEiKhcPx+LwtcshyROaplQExiYie5EMoMdSgHf2aTCG9e1jrhyVKXvfSOmYUing0NNd1HzFLsPSEytWG0418owqsM9j5K7C/cXC5KlHjKOkGaGsOuFmbvarm8+US0coYO+vRqHjAmNveMgDmevr9EdHkGp/C92WgVNxkoqOHg44FwwEFvZlQwlvJyGRKkNgVfagCXVJu6tqt4OWbOTrF/Xxw6hWLS/o75HrdtJJ+ouDh5UxPZHuiiLv3bAE8M0b3nfUunlfQZMkqtcsgwyltvTlvRFGV96RIT5ZphSWmYXuErYzXozUwdKJteuKmKU/LeQd0tXMfMA0Jtkjjve/w9hsa6oOePcGegsFpCd6GE2uOI+ys97EjV4RQtIAx90i90wzq3t
*/