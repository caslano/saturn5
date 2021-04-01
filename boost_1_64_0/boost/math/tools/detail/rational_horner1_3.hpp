//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_3_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_3_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((a[2] * x + a[1]) * x + a[0]) / ((b[2] * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((a[0] * z + a[1]) * z + a[2]) / ((b[0] * z + b[1]) * z + b[2]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_3.hpp
nkI+AVJZyvcF5Flx7KvlNV7snLZjKGxGRughnWejSX/wh+iFSHMtQHTIQkDXKZK808VFtDaPee55DDhtPwIng7DiyKrf/tcfIuF1OQ1O6fNzX6z3oVnq5oLtItykVm+05stkXvqur61NKW16d9h5NmP5BsRk44I0Biyp4bi2m3uY7RVow8mmmdMscqq5hvxc1KtE6F/+1K6aEy/aULyHs+L9l/cZxVEEsT1E7x33BTddc0uqurTFnOdFdezhYcUhPVfskoqEnRrHrNbSlSK4a87Zemkn2uOtu7fEvxipC8PN1Qlwa19qbLi++ek1zPRpZUrlV4LahYr8eFfMuKiW5CMJKPwzuvvh1nDDnE1zxVOXGDJBp6mmyQ86ow4BFJdFxf8rN1Pd0InwkzSxE49FUcQ4j63ojp0CgKrYSvH+3vmUFFuSAX7WJI/hUaQCiJ/SN9MZPpTHVQ0cs2Br+vTXM7xz90XbicbQAM5vAD+wyJhW/wo1zFoQFCpz79RAI1d4/oetjj/owueLL6MyWphjuCMayYhsBGmeJ1E7qseuDRD2m+plmuJVDIKqeg==
*/