//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_14_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_14_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_14.hpp
bD93LneyZCpr8T9fCHAGEeWcoLp/1lrxRxXf/KfRI0BbWoelkz6zvjGF2Vg3xSyrelnKUIpG5WVQ9mTZtSt/4ZwXdVP2Ms9hNMtvwx7qcqtd9OUEZE3wmIcI34UOcdc+CjEhOBJCiPBd6ID5JMQI7CVXXsL3jQPmsxBDc4/NM5yE7xsHzBchxlvruBUJvtMbMF+FGJc5DBPtfeM2nu9AjNIkumQUtNt1iPnBUDfFpDQKmm2GVMxvIUYTzJPXCdht5HnoIwEmCWmo0AnabcA8FWKIkyYPPwntNmAuQ4xMmFNNJLTb9eE7vsdc59KI6JSY59LaMs0/GwF56whJ3Mt5Lq2t0uQdkDdKKIGZr+VfH+XfAuSVDYwnnWr5Vb76XfTyESkvssaSbQg441eBGpfSgrsYcIqo4LjZEB3cPrja1AG4j0KcDcbaQO3Ad32F++SAk0FInGUgX8PVHJo97oES2c/y4i1RfGbnGXu/+itDDikMDoSyWRi4gaPqb58xIDYfU4Z6gU4n1/H2KnWpzzdAfSjGSbIlIufp0TAmYX1c1CHbWaApNkv5Pm3BNpFYxmSPIZNjupCERZQyqMQf6V3oxogi/V37o+A+TuVGYnmWqzXd3TvOr6iO79xf/Jxa7LMXPgqOPU4El44ifJwrcAQwd+p7LcBHUaLcaC0a3eHx3bx5u8BHy5unxqd6rEdCOJzKEZXeQEqYtKPR9/gtgA+jwIhP0gV0nJ3EQZAWeDd2BHAaeWfKstbCn2Q4jPIC78Y+NtjV+NymmqZe0dsHOUt7OXUZ3jd8BurpnbfKZLvqhqj3rAvmCz3GIaqpTk7rTUChmwrnaW119/6VQcfofCBCSZTjkmf5fxFWqHF+D3Jaq/JwZb5yXr1+re6hay6XgdPJRI10vHBm+f/I+chHw3Eo87wSo6mcc8IrwPnMR0NOKkpMOyMKZ5b/j5zXICdJguikU7PtlbWebOBUkQUnyKRnlv+XnMv88Y4e/4Cy2nqlEGjIN9QYo0A2ls/AYCaitewpkNUiWWY9Q11rNdkPQFlPbW6qUApey34EyCZDbP5PorlFoOzHoCz2NlqnS7lr2U8AWZYn6qAVRrPVoeynoKzBxLsQS7lNtsbwHdonMCKi1xgdLsegt+GGfR7fNYbvo+EeIiZihGYb1+X9k3tTMvcN5kM1FluPuVri8UhMFXr/chxXYwP1cq+2huQ+ruQkt/v+8/YtL5ZxmOXBt0OKlEW8WW22xjIqAW/PV3lzLz2m5zXcMy24QyfHpIpX2ccCWU0T48kKdHG6RfaZQFY6w4lI6LQXbfmasyyI2SlcbvGI9q+cHr/zVQ9cHeMQXYPydgp0xEOTvwLlGZR3SQaVe2CTH+IQ3Rrqo6LwvMq/+oGxPrehfNIxEhZ0lr/I8ruvGuUvoHxgnnFMXJMf6v9RKO9t0IoI2+SH+n9ysM/kwM5Ilj/ZyF+D8p8d7EOJwlbhJr8D5b8I5QXlXiknN/a58srr7x/0/epgH5INSthsny1xpr4z2McKhmlyTX6wzw+gfLamZszZJj/Y57eDfajxyoTZPll+tM9DHwvt47Ti2uAmP9jnqVBep0C483S2z6uvjPa5/NixP8jpin+Sv/rKa6P8taE+QlKlWCj6ZvmdlT0ZlCdSYEEcm8t/YNVet6B8FMYySuSm/GtXX3U29v9efpcFEwMn03ve01e96soi3cb7KZAn0jGtAqnyV0b5D0N5oRmPVk7y+VN0Xf7HYH2ijSRIUeVX5X8SykuOhVZz+Q+88j2r8j8D5KlwymNtFvl1fT4P5KOxhnG7iNfqNPkvQX0jMVhRvwHsXlnX56tA3luWuw9Pk3xeBNfy3wbywZRU2A4=
*/