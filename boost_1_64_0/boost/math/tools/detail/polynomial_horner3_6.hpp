//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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
   V t[2];
   t[0] = static_cast<V>(a[4] * x2 + a[2]);
   t[1] = static_cast<V>(a[3] * x2 + a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[5] * x2 + a[3];
   t[1] = a[4] * x2 + a[2];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_6.hpp
8/X7z5T6ycMM/eQrw33Zlc/9y9wZ43e8QfJhrBtrLSuhJu7BLcC9ZbZwPXcH4F7sXBRrzWctTy+B8ma2kwM7FK5Q7CfXdgFmr3l010NdVddbs0kP6k3pkvwTqk707AET2ZwO67xtV7anPMMGPa+5epFHyci9uYpc2VQGcq/L/DSOppAZg3u2BdzBIyOwS3XfnbSxDPwDZU4Upv9rGzN14K8OW9Yq25/9sMVRI7Exb32/gSNvkIOiijrtRuCpNtpQNkYbvTlCuE1lg+/obiZc0Fc09vNRii3PG3cmthrYESr3220EI3IP2a4wmHhDULg0NrvDxBKYk9GX4Z0UBkOOVmXRD8CdCd6RpQluQzDu3YSzApg+52Bivfx06d0FE4c8dbXsp/cpbA7e4RQbvbPkrb2VuwGudFKSNnwLcL/BwUA0/re7A25vHWGd77uHxAcuWZH7kHvZXHspjPF+/CBw7SED58Ur95a4rBdsl60Z2TBRl7gP4XZUiHVFGGHO35fwlnX71UFi+k4cAq69/MayX7qfxO3lt3ke7P7AIctvvMvzAILVgZB3DR4IOPjDtfqwWf8PAg74xe3njKtzHg8GzmA9EjUFLKefg8w69dSrD7klV+lEmv/Khwr+OvRalf4XPUzzm0djnQOM41+3lyG68Jcefjs+5AL5nx4T/HXozkoP/PgR4Bv2vob7j3vGbQ5onVTHGz1qcyBdiN8kuIoD8TMTgA+2G8aTBIewUTd7obFHexlXU+a8uevtA3QzMCvXYwDa2a699RZcba/HsIfknEy3xJp1zoOS27y1CkwMlylus3UZ2DrN3ObaW6FANs7gXLX0zyivCqcK1u+DS+oG44Zu8LXhgUklY9DD9Duat5aBkdC0L10ZIXxaLbglpPn7tgzma3ubwb8yejs+TCmYZ3/r7fiLooohBxjH9u23k1nuXOxiHD+/BV8Fb5frvh23kOkqmyDyX7sT+Ldt7nouvXZnm293JRyvf79HcQGVc3irI8wv4gzs9DxMLrh2uIvmdi5KG425dti3X+Gwdqhj0uPeT+4usHXs3Sj+aw/cll8PMuNqbrjHbflyesA+dob0sZQlVeqngb/+c/PQxyw/9F8fdpPauw8kZAix9wwDVutSK6KMLw0RX1CA8aCoD2CBoPGW24iJgaIDOMqe3aTw+iAWgFqWbSaYEtZ6/qEtDTimUIfzjlHgnS6SIsAUmrbWrRqXIdG8P+8OgEt9BGIxsPZ2wEAP0RjqMXe0MCw73IvQ+0jq4A8MpPiu4yFrjcXz2KmSIPnf61js6wv7oxHRKXG7C6yKNdahWDcUHgyH5BnICxSDfqrbyzeG+0OUvXAMbYnwtnYzVxmXHoa+w5p5MHbpE84Y7uzmZj40YZP3K+Dh+omSDd7aqORBhDbPqNuRbcBrOgKGnPfskBx6tIvYcad2Acc+JjZEzgr043Um0Ka+GziyffYnGXh6rPyGbo82z7BT7xW829gwr9xFcNZhm1y5q+RFQRmccvJW6RTBaVTAxtXZ/JCc7Yw4j0M3chjZ9bfOdn6fyuRp5DlOVDGy8pYyj1U+mEPquzThrufHecoaTFWm729X2dWIfAFXppPIS2J2C1OX7Z/3QET9ueVZmjpeGbABzdP25XXckg+8yiuypEJ5TAMUge13fYrIO8xPssTJnJxZ21a2z7RZIheKeH03A9+zTVsjtTDe674S0XvqcZRxv4yYeYJHxndJ5fMtJL6M5X7k5UFSQHzWYSs55FBft18i8nAmEt6VjksqT81m9l35n0fWvegkCsq85Mw+clILol/iP0W0nfEgTLzQ91jz1k7ffeTRmNxH9jMvdb26uIjfvAuqfPfE1tnoMnI=
*/