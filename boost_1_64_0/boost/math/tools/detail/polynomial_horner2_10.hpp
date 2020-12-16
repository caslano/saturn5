//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_10.hpp
8aGhrFqT7ElrK0Qw+jjFBp/uhZ7WmNXSd/KXHSWcYEa3MT89TzwPuDbgmexGnnSGqY4FHv/qr++0J4X+X3WywXP97OIgncec/+d18z1KWvNGaxLCAk7WQxjjLrwWaYd9jaT31zO9PtBj1JrO7K8d6Xv7nQ8JTNNvZrSNIk1A/297nms2xvo/fjzSI80M7z/l9pAGkUYqaqv6atdU4bEAtJDOcD4K9HVngkqxSszfO316t2+q+1OMlH/BXQ11deHlvp4IXZHelwX4WvyuoyQ7F475b5G7c8lP9/qvC2hhKR/z7ynXA7TOsyi/+/5XSO9O6e8c990B7WDia12qs+GuG6B3nmE76xdBPIIf3yDyjPxyPnSjSAN+OaduDL773Zykb/VkpCWfnaG/uFmkhUyO7fkhNw/fQ2mGWwzZfeHhTPpYtx8ZGObuRz4FlLtGTNY1xQ35X+tRvxfY40G43O/6g2H+2NG7J/N9mlPf9OVrl7SuD0r3Qa8T6L6qrR312ZNk6XUDLUB2to72Be96PUgPlQzs+V0f0st9w1/foKSP9w3VjSBPl3j/K5bVCUj3/7g42U1l9dfrpLJan+4+dCirhw9njT5v8/hLuMKsrgxH1pePnyafX5o9xhHE9oqzkbccg+XspBBVRcX/U86T2w5phUkty/kPC4OZQ7u9d7wX94dUR0Z5/eNrQ3oXM3Uj3P9NY8HHrxN5QHt42rHwfW9ns8vGMNb487msDD5/XUCf7PZ0n0+93jyfatRoZhqrrnqvKuzODntVb3+g7++eHdZj/Z5tyJ9+z+md+fdu2ymtH98DaKEWpfXd+wMt3IHPyWmB1/W97/G47IlrpFIKV0R2vlvvgt9WgC+wL48/Dv6O/i7roDvxhPEh8XSlmZjSGH7DOTx9dIB4X+1E4gk9do51r6FvvvGIJwUayPBO3izxBYZ56f7wLTOeacIDd5RuHXj6HsMPxQvZee/hbQLtv27Dg5gAfyzLJz9/AHRQfilWx+06nqNLl54TiiOm88+3j98H17Yo8+U7RlrIiijzgTuH7yETw5og1LM0J/76XTwt3EnPKka6KJ/SLO465utjaERdf57Hky7Lp370bmO+/rJ8iu9y9zk8YXzOeI6dGvP0F+rTOdLA8ywfVL1LSCqn198zoyWj01gD6MHYRHvLvXJaSHyivfjeGS0kOpN7531yWpfYeGaEntedGYWq5e8rpbOk/X9zdl3BXS5VPECAUFSuomJHRcUeIGCw7td7UaLijBpCiokGEvMPiI4PPDjqg+PcB3VwxgcfnLHPMOqoD469i4q9K/aGHXvds//dc/bs90XBy80ld3+/c3b3bN9v9+wLdbhM3dzSeQx//YsoXN5so3kh679y0TRh01bFTftUkR9p5PdFPkf9w0j0tHa69aPpgaLZa8WL2wGX3xoH0n2xvH26siZzvTo/q1zJwbQR2wZ8owLuUIcPVbFaumC3w6m7EP6UBkAaG68+DL5dTs+685h7mvMKr1T43CKhKHvJYBcsUMoafPy1Q3www3DUfe0tmwGft2LGsxkn36GxC4flg1fHe89mnGJlUomwTv0yLvxbL5Pdt33lkVLfkeG3DNmiZ6S5h8P9AOdg2laz3TmYwo2tmKk0ZmzFTKUxYycyE2HGRsxE+hyFsVGviVSevibz9IYX6D10giFP5KcA+phhPYSVJ8zJYdqA/fz6FhfHKRrquPfWDmfO9q1zYJuN43oDx6V/dHHliGx1fn5NJhp5b9jez4Oc2eNcOtbHmwYjwNBAfj/6ecDBM0yv2tHLkbVqzTRD0If34TgXnEscBnvRWerdjIPrJ9zD7cWnwfcYpunKHTqcgbSDnvdOw0ECtMU=
*/