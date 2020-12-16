//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_11_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_11_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_11.hpp
NKPEJHR//2j4Vv9yL7djNREsprx9OTyq53xni+5fBfVnKHCpVcR6I10/3dor97x/q74HACsQZVwoRcWAna9yhvsRgCWoXMBjzfwGu/kgp0fZqWvId//Y38I1zXnOsKAbmCx3VOt78+f2GIIn/7M8/i06xDs3p4ANtYqgf78S4Cxy3HlZvCz3s5uZvnOc87XobSVUP1NYV0+poMmmXsWlrnfq+x+ICVQyyvWMSdPdbcUs7X3aY16dPHOclCl0f7q6hHvDD/ey1w3nLI8Zks8c9u/fa0cUrS99rJe/xq2gXsRUspisfXE/0csmFHHijKlUC7+ZPwoOBr/oz45to3H55mXoTNDrV66UmKxH2S/wYnyb8qUet0silVJ6i26Hm+1IpMjXfg54OIp59leBxvm05Q0HRyXxVd8ora9+b6ijs0qXIA3oXVmf49tHH6SbK+LxLu+Xvx3GRwwuKKbReXE6PFjO8DrSxvnY38Hv3OSYpV7Pfefszt7x4YfaZ247/7vc4677VF4hz6OD3cRwT/5KwMERYyL6zFFee+R6ub13Hhwd9a8jcvHLXKR67FVvmIyMBfTGMdau6+UecIk7qi1H989bJOajpT63fgftlU2lrWF6cjbPJzQnt3MLvaE4ytdzj8t1DPwO+kNbl4q33b3ufPJ23XP0shElFgSPyqGzd+3nLucz5J0n81A+r++iHw7O4jXL81U22eG2twsf+x30fcFeUJ7H/bv23ndSWvyAnWVHEDguP91jHGLlfDWIOA207Nf/zoOzYd3o5XdY1IIli9Hp3exQOMb6/2Ivu0tpkl5xP7VBN8V28VKALWNk0RmP0d1t74G/1su+2qRyz6USujcd3w/3cN8B7cuQ5+V5Bo91gli/Q7hc7xlhmxGmGSaYVuitw4ujg+Fc9q+ADyOpYglAUzFvytPpPILAPPbE34P2y0TMWNEmyfLIbowTfTljQOz5KCwTpmLcfNgz7r+uAxxHNDlsXSh7j3sHt/IZam7R44PaA0C7ph67y0sCkWDLVWgODHWxV+ej+4teb+vlA8qWt9yJhE6yc8oZ6PaXzha9jga9nHKYUJ1Q7jgX/uT29CqsOT7j6k8Cbcip4wYbA2BkrmGNm9NjXq1J8CQagrL34v7J2eB/+JksC+5YtfaGZen1vuXKqydos9uXe+x1JkTutomhe2/pifJ0VONQAXlBXJ7HJUbHN/+F/HdAu0QqFDNGoPOIAeDWYqvvZ3nwhotjmSJH+yUGF+S48sCytgzt4rnwmtiI8ng+2T8si9m8EMJ2eegf4BptYhRBkg7WDmAWrmdmDMjlmIwt/pZTH015Vtg76ifllo+zx0VEqXKMSIkWF7Q2ZtueEv1hfEOaMHFOonsn7zw8GkfEECvnD2O8KcpYtgs6LXPRVmjFfgBgOfKSYSGpH9f4Zp2G/cTAq3FwxHiBTto6ndXtb/urjT7fYwNiMpBApEHv3js+uIBj8n71tRv4oojKMqqn1S5N72HyIf/s2j7wfRfypYixi4qid94/PCpekU2/7j1pj3HI+dySRDl0+yZ+/WarANvhj6B+DHHFYsLMzjkf3EF+dgmAnS2f+EfY/spHTokX5e7kIscN9IfHh/fu39vK+4oBK/LkxmXiFbv3gQHb+rgCWIooiUIHQefO+i/z27zjj+NZBIks5rVC33rDweZGfeWnddpjdmzQGFudUHmieDLmwfvAUC+bbW+kbGvmdEx+fnccC58AOIG4oDQ3gUUfyM4Vbzw+zJ6wq9W2vm3ssddVnu4SYRptHs/eu3u+2osDeRbyuswzk9ee39jx6uZqLz7oFLTwlHDTMezePdgr3XHhan5KAIuRj4IGzXmPfWdeXw4=
*/