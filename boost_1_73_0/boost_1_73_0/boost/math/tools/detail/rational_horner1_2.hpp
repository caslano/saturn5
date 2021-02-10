//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_2_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_2_HPP

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
   if(x <= 1)
     return static_cast<V>((a[1] * x + a[0]) / (b[1] * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((a[0] * z + a[1]) / (b[0] * z + b[1]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_2.hpp
F2A2huXK8AZxQDGMC8oyjn6dVrsPby+p3gj5DmbXs6DbilrtBrm7u/MrOC6tYNTyeJ+m5jRfD72qRrj3bCbMvecOm03vDKSSjA+9KOx1zsNu1O15DfJBSYs4frotEMfybzbI7Dp/Dyyj2nA7FEb5Fxe9gR8djT9zubJZDO3zBmmQFOMA/qSygEnVAaGgK+QjcEQgTXsjUxYFlrsAq+ChsrWllrjdYDW1t6lpgBW3Big6vuDtUGkuJMcYBpF8IWGp1br2ZrnABJ0AURiGP4nQDkOYfvojwv+OpM6BpMn8JUHNHUMuU5c1psIe/5ve+RfU2SmCu914Y1d+qPtsN/Wu6XDsXe+OSGZtgeb7bbLkFNuc473RnM9nE8L0trAKLY4vIJF0zZ3usBE2O1w9cuFkcKdPpbIoff0w6BU4N0iYWq/R1gWPg+DkejpPJ7P4pEKcTW/SIAoHPfBLqCQuMbe4WlQzBL6/qINhRgcYXO7KwnJvuRbLLVRsAF1anM+KqbpXMmpwkHF4PZMp65HkubZFgEIrq5jKRwSvU3Dh93qj8srYGH7JskG+Ymr+eIWhY2ClzoOT26ub+WT6pUHGjPECj0+D00q1V8H+/h6peKgYdI1f7bDXXz0KZ1BqMfTqXGp/Uyhp0IZGrD/oRJzx
*/