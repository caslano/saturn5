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
6aLCBwfMeM5EoDPxeKrZ20wH5hsKYj8deA/XBgu/SxVLEF2P06WnrtBH6DJYZwkw5cHK2n4BM33J/3WnNzVJuVFdBgdM+zRGNAcCfb3HHBl1IJsAgsucwqLScxNg4HfYrY6KR8mOpzBiFi2ukwOfbGEL0TNmCRpiQdi0e7yYhQcRLQVw0NMHkJOb+vkmQfYeU0bSu1mx/jSC/hwdGyd4n5K3KKWbXJyOASlekAYJXOIGq6JPQ0qNP+fy8edxVZClL08JuC9jzC6Py5jAyrhBU1YZE1zKODjLTRkTyypjAi9jhyxPypjh5baMQroDGoMjsANbN5toVK8tuQyecey4IAT2E3LoHHMu09Fo+mwY6g8xFmy3U2XBGCQfFzqcsqgUHZJOnFw4ujOS6jL4/CJPKHGdhoVMUwxtmdPDNUDk/mzsIoCAIc/bi9snLuOmoAsn71A5k44+YjW4dyEeewyBsccsOvbo7SX3iIa1CAun+idliiAuZ1GT6dxBVTkSXJDcpSLEa+jX3U8JcfwF1RwyzVSn8xhyCZcflG+FkUbcgFnlkOIDVdVRESjpwhQmXbxR7qLIslK0pLh4e6kbrCcry/vHTEVJhbl3waQs/IzENn9KgkHeZMrH8rDc4zo2EDClJvvtWbWMOWyv7eWOrT+XWdbcxTyXsI7i4jWuRdpDu+K2RbtpFcQWw0yHwx+V8p8FnqCqb4m2jGnurn54
*/