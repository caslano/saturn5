//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_5_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_5_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((a[3] * x + a[2]) * x + a[1]) * x + a[0]) / (((b[3] * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) / (((b[0] * z + b[1]) * z + b[2]) * z + b[3]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((b[4] * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) / ((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_5.hpp
DHrm42MycXYjr3Uc+KSAldnWVTLPA050wNQT7fc+8DbgrPZ2wIDMS/uBo/D7SL87/NDbR3AohMt7/h2IB3qBtkPTe4zdOLDs5cbEq6zeHH5uAvFd9ObwPygn1JvvBnpT16LiInvFPk+t3py067ge8VWWl0rkpf5CzOhdCCzGPR+WG3Z9/YwvczpTpZYoBEvBjscTYJb/nM+fy5KkyvO2ZGH6DGxJM70mfGkV+IOlSyf18nOC+r58r6en+tQI3+/upVjvGsAo++Q+h9uE8f3ofsA6vdIvHsEr5ZZWb8QHBwJ8oJ/y+X7V70B8awN2X6izf3iNxaA8ZGw4+XvfaDkah6730v7BWxzWBePVYXxd2jeOOgznVsjGH5sfAE44ZoCEa5LHZkY5m1u9a9tA88ry8mngmSqaHbZro3nAdh9fR8+M4ttb6APnmVHcRH3Ffc+9q4EfiYq3VZnWrOkN+itLsHXsXieecntHjINxP5GtWSuyuq6KtPOap64ub6yvnJ0rezpKSWQtZ3U6dA9u03qIpNWwvGnLSDRRl9YFP07O1hI4bjCp60f6rmAY54ikJVmdFkVSdykl5s0oVKtbOYwUaAJjoN0g6ZQsk5xXWZp1KZ3X1tdLA22aPLZ2NP6an849imdtImumM5zDPybzLT8WwvvoW0i31rdzwLMrdL9YSJW0id2zzpgaoe/RP6wE8UDyKi1VaiRM0U3sDNzyzlzrfrrmb1kxxshLK9QOvy1KKeIsv8W5M3JvZVfpO5ui5LEoTAlpP234fjTfP5yHrJE53p1OIXZ1zYDQtp7sBwAntiewjbFc3KM9NDmOCzb4S/0V4OE71lEefPmA57/3WiF6USW11vmabWul1qbm9I3QD3zubFHXRcrTquN2RH9MPxH0c8VlGsdVxlSZnJ+Hk4FPLsKbSXjIYPsTbIeO6znzr8sgO4aoPfReM771fv9m/ZeVXXjueSu2x7Rez35wMuDiKwu0BdmNR2wZoG1348FuAvv2hx4PGgq87p1YXBrobfXylxcbyX2/G1OUa2zZ0V/R/jF4l1YfYy6HnL7meOVePQg4fLLGlN3jffc24MGybzzv9e6NBPC6nFaWvfXHwjKx3ZNFXKdJVLIV7V9NBY8kXNzOZWK/WbZ5muaCdU45zjv/OGjrt71M/X0neZPHtZDwCgOmWB3XawmcgdH88Hz0EZIfTyHuZ6SYrkulp+fBZZPfpq3TD2mdGh5JkSnJzifn7lMLw+dj5pXFkl0bHn2+WzsSilGR+yznpT+Ncoxa3tfY8eTnnTSs5UVSRLfgembzhIuT8WM9dq4vQXo0y/Dd/vMwz3e6NLe4vdw7OVy9d0k6PTm0HzkPnjQoOJtbf/BSbxPTmr8NeDS/cA/3/CiH2Hao20dwchbxFOBaF1f6c6YgUGKc6+5d8ue6Uqi0VLyB/kZnU1Y3cp9bsTyO0zovG2acx2mtovyLSzSma5wkJTzPjsXJrqThe6BVwldlUVRFwaEsG6h7no+mbZ9/qonTTEVZxLZ31uh3fuDzasZVXeRlluuClDwlRcHzpG8s0b1HkcuojJtb/X66d0WXH4D0XNVRr8y8/WuDQ4koA9JAnxEfnsQ0QjueH+4hOLFROzRJMGKjNjAY5k3tN47sDXFqv/FwiAf2IS8BTscMkb+8bxRfXH8QbX0O+vgXVteA4dftDsBh/nb1Q9uoOx2G5fParHoV4DCnj5E9bDEq6+IhPODfvSRlVaSNikG/x+vU7AN0TdZkIuHRLbspcDr19CKkZ7Mb779iZtLiof8KglFfMQQb9RUzg31lzg3wnW2AzQw9r3h+MPcDB/rDpo/YkWnAoL0Rs9+1xxepDXuWtXFRVQI=
*/