//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_5_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_5_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_5.hpp
mDgEZ3x8IkFXvfmG1Kx8Clr1qqL6Oqib2e8icehHzaItNyaTwZ6CvgX1c9kLn6378Tu2r8VxVaXNqPOsUczLU6bHgjFInmjjS8N39d0SRDn17xsQRRVo4ewFuDuU8XqOmndCvHu54IUOwLJz6ACRdhh7p1aLasHve+7I+bXUFzQT82kE3cA6U790F04eRDhatNl1ScgqYbCEKMa4oY4I4i7vAWDGx6//mrtXDiNG+1ykB49Ah8gxss/pdMvBdVe4r/muUJYn07djHz+jH//qZ7p0/2DGdbnqPoDY5zoTbyAuFwWigYldhO+x9HeYkcYZmo917ABvRddTWKCO1V/XFsecZe0Z+uaPwIeVPiLlYQrqxW/OGkNUznWniEzhGqr6yAVCgAcFB2fVC2//tFsBJtS7YWyTHolJuXN05EdO5lu+B8My7DVTzvsqhcJzMZXJyg++wP/pWumJZVSgeDloHDcH3SutaqHiPKrfWCXPYTR8KWt11UjodVWypZsF26e7n7AXl8V/kK55nb6iQ1RLh1frZXLfVN5o6wwHQYlhfnr7arTlye7Foyz9Rw==
*/