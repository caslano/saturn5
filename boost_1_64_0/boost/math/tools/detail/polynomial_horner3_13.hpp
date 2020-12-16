//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_13_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_13_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[6] * x2 + a[4]);
   t[1] = static_cast<V>(a[5] * x2 + a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[11] * x2 + a[9];
   t[1] = a[10] * x2 + a[8];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[7]);
   t[1] += static_cast<V>(a[6]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[12] * x2 + a[10]);
   t[1] = static_cast<V>(a[11] * x2 + a[9]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[8]);
   t[1] += static_cast<V>(a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[2]);
   t[1] += static_cast<V>(a[1]);
   t[0] *= x2;
   t[0] += static_cast<V>(a[0]);
   t[1] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_13.hpp
vmu9FzAwRBsbYfjn72Zp2OLaNF5xd4Sxrcjpw1vuaTEWAXTz3pOlm7mhpZ+7r6ajdmR08bX7Ab0lSJujr8MPMhg/GJvRxa9GAQNTkX5dfG3M0Abq4vw4wrTqQkwaTKsukilDb9XFDdOKjnVh6Bf2A927UOek//CHAd1cQjN0EztnFN+BYDlLozqO3bdz5OHo4skVCNxs4tYO3UXHamn4Z5vIkY2uNx6xiStFnx/DezSC80Kk1/9Wup7Td14/5K4xaZbXNOWUKN0d2G/XAYvmDX2XpyBRmZU8DyjZ0IfDInlMrNox725WyfIi2djrObDfvyxpY9FdebGTVk1qIURVUEakv0HU23isn6bwx5y60EGzA8o/e/UunVvs7O7WOvVVCnW6defnxiEVFaFAtodqRrcKSx/y6I8Oi5Q6/DfC9KZxSzJ6C/TYUH9wTncecXYIMG5gBmsTf3wjoHnBgJ03/nfdFOjd4+pBKPvWuvoOgQBm7QBl+vTlrYoOd/5dgNPvd2xTGBUL34GZudUljYEbc95byb+5haL1utKkyLvCTSYt/Ve3BLofsdh9yxjRu8uKrvc2P3NbRG+eEpo7sZFLtxw/vH0fDsK3ywxbWdN3whgcBNnmSdwFcH7AXJvWE/caOgqM6+bn4t08DBStwdh0zt/dxzQ1b+h79ik6DqJr6Mm9MF0lYeXfB9OVeFOvu+/n0E8dg2ZkeF9zf0TTSRv6hQciOiSN6P96MKKrpC19cdTSbQBdm7eZcaBLHmkq1eBuaH9zac2k3Or97RNAw5eB/br516SPsXXT7EM0iZg3qv3InubNK7NncRXsCQnuzYM9Vu8wD8bqZ5AaDpSXvw/k0c8iLTxIY/+BsO3h4OQwo/F7/zkYf7IFf24w3n1IdX5K718MxrdEGLNlfs2/Br4lrvW/YPTz74FYrc0Frf+RwVhf/0dN/Q7mUfq38n82GOtHVTBvru/4z1V52t7lGdK8P7sK78kBvOY97/+28cIToHb/iWwZbsE0z3XO3kvrpw1jn7ecfZDOazvOf+byuKnXm7Tg8XOXZ3Q+L9y0Dds8Rzqr5T13GGH6wxxCbHgtb5uPbQ8pCMti83b2zVp4bDBK+/59G84GnjS41avg5uSzRnfXuF+31SOkaOvoCMIMfnt9788RrvVN4Tvqvr2k35x/Rvf06tFlaDd30XkSmta04MXFWbiW3Tle6TuAo57vYpoEaZH8X2/7H2/W7lYF5g1JfW47BJi25m7lXLiJxeBmZDGXhi0Gd4mOfb/7ZhiDq87ivnZzhPObjL3neguMw03Gvrt68ZaAu2Zza/Y+Tu8Avs2HJZ2fYifC+0OS2Tt47q0H4bREm4fiNhjbPhRZ/OJtB+Hb3/TedzuE94d0I7dze4xrH0Kdt/nuYPC++TN6eOIdEabN9BnszJ0stt3sdQz29F0Q1jdpSF/n9wJ286HP7AvebRAe1/G5uw/C2Tp+qK6zewD2eoYrW38X7jmQFxRo0njFvQB3PcOpfUv4M/cB3msavo1eL90XeDYfKswafwSf1xRByZIguF7Th+7Kz5n0/ei7FvftLRiHo+xaG/LDbQjXHoHWas+MB8LY/JONqlYd35OJEWzv0yDP6qzOr7fQ93PK3B262jAF9XPvDX0PWezgxwLOWJt8UwffL9aOOVstDg+7du1+5eaAgSAfs6UcaswaZu5W9vvcitxY6Vqer+20tNNnNnyVxmW/+c27YK/kqeHK+vrK0thkKBfahnYF0aYQ7W8btJmV1fH9DaGjZULnNbRpl/YL8InboI1NylsWYkMLnVvKs5zbSIxU3NTE7HrnZvLvX0rsCci/0guT+j4xdLjhc23Vz25kv+tIkbA=
*/