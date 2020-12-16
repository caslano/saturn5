//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_8_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_8_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
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


}}}} // namespaces

#endif // include guard


/* rational_horner3_8.hpp
YokmlmRiKSamtqRuLhNzm1igiQWRtdW2k2zFdxF7kBeyh15s9cvXTOZ1Lq3K25stzZaGv6Euu6wq3MK2rtXxT8jLbqu6r9jy+s4ogNj3Uj1hhtjJMmnbQfbVuTsG8ZFVELZ4c2RD9BeyysIKNb3QBO1H5oB5ri+VZDD5f9gUg8l1otQ+fX7XljfQwc9MyWRdSueuVR25Jivmxbb/aXNeH/ogHScsbJv7pkxHXg5bVRMvtgWPMoainkesars3289D6/IaYCes6gfFFpHrz/uo50mrChX2zc9FyiIvZD5im+0nTNqMGM7qa1Fttn0RmZGXc3q+pO3I3LQH0Q5kn0R8/z47gP+FfVFf/2l76H72b8SeaFXxcn9ly8FSyMoKC+zTrTn6yyWraiRsXPFcS5EXsqVebIf3DmqEel7R9y609eu+24acXdX3LrTZ9537Ads0sQQyp4i9SqPWH3jNOH0tqq1mnRLbsT+ySGHZGr19hdj/W87C1vCFfzKvt2ZVgxRbq5qtb/FaZVb1ExvN2eMXod3JrDDD8czE1M3UzWVibhMLNLEgEwsxsXATizKxGBOLNbE4E4s3sQQTSzSxJBNLMTF1y6T9yPZo+4Vs27QmZVDutr43o+3MgBXzEQNZHmGzzv1VFXUh6y0sOCBNdeSabjVVE7Yrsta/EDvZa2GlfonGeFBJnlbvVZcO6Ev39NxNW9zXKzEod5/mRBa21zdubIY91PdwtV0e8p6/RyCTeSk2viuvofHIqnpa2MoNmPgEdXliVasUm29EGpw7VDKd/0S555tqreD3e6yqhbAc/m8PoY2e6/c1tKXUTDsGY4Xshg/b1laHAzFWXutjj7YKi+fw9/ZkZYVlPTLcgX5G1lHU5aB1/FiMhzf6nqq2heVe8/1BsoXCvjvK793H/0n3EixsLZ+84HXy3+n7u9pq9HnC70qTWWGGcWtisSYWZ2LxJpZgYokmlmRiKSam3qduLjKbtu3GZ3VkFmFp5kd6oX+SldG2zXB/MIosQFs82aTSzrPIC5kdZrjvTeYS1jtqPX/7TxYsLDlsC38H9sGqKgl7Pdx1Be1nsLLdTvpim2QOmOc3aSkfUq+n+suqhmjbSran8QVeD4mslrBOC3ovQbmPek6krcrdb8phjJHVE/Ysz9LhyBnZWWGZR63eAPukx5+2LeOtFsRAdliY94ls/Ozlsz4ma7O3qM4xfLGq/MKyRdwKQf8ks8IM/dPEUkxM/Z26uUzMbWKBJhZkYiEmFm5iUSYWY2KxJhZnYvFk2YWVP/NlLNqIbKmwHFu3JmF/X7l/biGbeHlFHNqIrICw8B1jf0SulS1VCyELENZiT9tH2B9ZdmH1HL2aIAayGGGRQ4sXxDYtNuVjY7sbdYHvqTpsNGdgc5xtyu8eOG0qs7BLuQ7wPX8yp7BP/T5ORp8gs8EM7xeYWDhZCQvbi9a766GeaWyqomJ7Fl42EHVJa1NBwmInulqgv5AVE7a4SMdeOEaSWWGGcwdZC2EdJr/Ojvh8baqDzHXI30loB7KiPmx3rpWogz7hZ8NxfrPhOB+Y0YbvuTaRLc3brBTanWyKsJANKRGoSyYdu7aCl4byt7lk44QdL/9yBPaX2aYGCsv0vtUV5IVsgrBLbl5PICqLTc0TdnTEwnLYZlabaiUsrOkZXs+RbI6wpyV4ve3wbDaVQVj7Y5tyoP3IAoRtPJvYB/UkKymsyMJ3vGZ4dpsaK6xa1n+PQl3IMgv7vPTYH9imwW4O9OV3qcgWCvOv9gPfw83hGfuI6IwYKy5/m4oUNjrd6o0oRyZjSM4d7Y39GWzrq1rou+6cnm00uXlNXveHrLywlurGOZTLZVM5hP2cztE=
*/