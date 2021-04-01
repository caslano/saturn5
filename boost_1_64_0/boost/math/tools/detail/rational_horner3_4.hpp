//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner3_4.hpp
cIMOR5Et06e6A5qH1OTmYqN2QKEj6jmuIIb1dK4Z977wmadicA0ydRb/kvLuy4ICZFVWpOZC1nOaBdZGIxFVH0TDNidrzcsd5611fKIzlcDFBZsBcjDk7VmYD1tU1QAwxfPtTPLByyis62rsR87qrV8ZKsQqfCksgPrnAIouQ8QiqETSwdDh1fzv2Oz9+osLPEhhSJ4eju7/YuI1LxmH+PT4jlG/7N3tHnH+ZRIcgQno7CVHd2MEoO3f5KpBQ8NHNV0F+UQbSpX0EByrwuP9uAqNNy97/OZuYooA3LAX7juLdV+V46RMMygyPJ2dYzStTAEFru3Ve6vcseWXV0BiCro9xYaTxJ4DB4s59S29mqnSwOHYciewRpRlsekqwlbIHKXupdNic0HVXKT2iAyaDE+6MRdKSVzd4yzvmBFyr9AZozI0JyMIdBvzklVg89ucIvdSPytVES5sHIPcs+qeWiTDQCm1h6rsefsUfDaRxXkgJhc8PhlLFi060vwrWeQdiZ3oTunXDTlQ77TUnepaRIwRFX7t5BwSHGxpLpSKtR2HKn8CCTSKzosdzw==
*/