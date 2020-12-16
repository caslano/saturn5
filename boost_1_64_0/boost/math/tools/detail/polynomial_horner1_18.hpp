//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_18_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_18_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((a[14] * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((a[15] * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((((((((((a[16] * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((((((((((a[17] * x + a[16]) * x + a[15]) * x + a[14]) * x + a[13]) * x + a[12]) * x + a[11]) * x + a[10]) * x + a[9]) * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_18.hpp
j7Qh2Xg+oXJ2mJfZlrGz474LuDUSTnrJuf8P3G/Zv1uavbX5p14A27zE3vaRpc2l1cFZC4sG2/zzA7+nOmLKw3/mJ4D/e4CfomhVDEWP/J47JzQ+vnOwXODCefy3Az/DOAT9X9DTif5S9dV74RDrGdNEcRKgz8NxdyKW/S7AJpTtb1xietveGo76IY4yKCcixygNJHGUb+Km+53O76i5tkF7fOyF8IxNMlweFabtdRlnAdTeYb4QfJsznpTHAoWDizwzbxl/Xx14U17KhbLxP/JOo79rz8EGGmvCiYyNeYfm6677x3M44PPy57PTxW+tlvPMF8H6MCeZ1vI/14dCO6i+nF3DqGXBS3R8TkGSt7a+A16b7SAkCZb/R97cJfv6f+xFsE85laSVwjc7QC80vmSNG+zwhaE+kjmunBX/TX1IF6fgBy+C7961d7KkrjueUnesYx3/NsuDbzKlmbAmbhuYe7MPTM0P8eIhlozhxQUgNd1nb75Ge/K6ZRwDrECOSOK0E1t5yeH5eGaCerxHzuQVLFra798FGe4xE+CkyNuy5m+dg965yk8H+crhpLAh1L1r+8JufqEfgDpOsfM8lWIr4RYdP9njAwqClqj2fIhVBdvzs0ObeI6xtcJs20/t78N7rS9DPk6YCIm5IcYVnMe+0WNoyXMVEwsqrM99aL0W2Vmm1T4uG7RvYiRRQlpcrrZpbX5eD30JPPNkwmsh5zPMRbmuDZ/Yy3tEomJRSNHasG1Qz8hyf9Fjylls2WN5Pp//gEMEOtz7HNR4wi8BdjUpEem4b+3YKVfPQTMG5OJkkTor62Hz2HZvgxwuMok1a03XdGu+LEdAN4t0cVxgzg+6FbqVdjVeZu+Xes0m72iQETW3tLrnzrIvGfadVFsjnfpv73YWzs/0PqvXklQiuk2kpsp5zSzrI+BMSDumCcHm/7nX+cyka8tVbhnL2tbzkpm86ftLwK2QMcFnfv9f6XsFtdxhl2F8aIadEIJsNP4XByZm6Xs9lhGUl+iYnOD/j/4fuAzOaWU5QbcKsVn/VXt/9PKwTyJJWRf99jVtmRTavFR9LS9DvweuvKZkugIv2lfq2uaX4TdloNQoTljTufHOk9HBRYklntlzRwfvD34KdE5OOSGl2Oh8cnS77q9qvKmHPqTrm+W7QGLnphup1Zn5H3PZMM+XUoTSSbHWnoDnYOF54kt7P0gRidTUzw6os+xhPVPOsuD+zybug1TFIXTuubvToe0D1ypPzd35UrjO0siIDLktiw9ZPlrMJludmb8W8MlyjxWMDnLxDS2M2cNivKu4QZbvK4DXxf8gOuFpH4t14r+xYw+KL2arw8Vin4u+jAcsiVwSibPGlonZNWNn0fHDUMdkg/WKy5yePp+b5q+A7Fm3lG9rfuUeE1AM2pKMq4PhVa3ZWl4JoBdHlhttuZD1vYLYEGb1KmXNOTa0IWPOMcV9GwSA8jJZ7lYAziJSfDmS3nxvl86Vc7BnV9L8ub7Ks3BR70xeCu+ndF6JWCDz5nq9p/wj4BSISYmNoRGlmSsr2NgG3+CXwf1LELmTes6H/XS/p7xU+2qP9chTKuQmbd5eTtch7+dDqJVf+mt7zG6kWrLofVatuOa+8exojNGtQP1ICdJppCI6J/k/z++RSrz7i4M72dV08Jd+G8BRxLSimPRb5UyYfzbKptdFj43IYkKSTXKO8Qk+dm/UOKcvG/pLBiRsbdbsn5xdV2wdTRU2ECBAgNB7D70ndohpmZ22szsVbKpAxr99Exsc2/jaEIqAByQQRXTBAw8gIUCAgAceeOABISR67733XiS6xMze3Zk5szcQyP+neE/55kwvZ874Z5z2ZouyzL4=
*/