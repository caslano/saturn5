//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_19_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_19_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 12>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 13>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((a[11] * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 14>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((a[12] * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 15>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((a[13] * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 16>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((((((a[14] * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 17>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((((((a[15] * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 18>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((((((a[16] * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 19>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((((((((a[18] * x2 + a[16]) * x2 + a[14]) * x2 + a[12]) * x2 + a[10]) * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((((((a[17] * x2 + a[15]) * x2 + a[13]) * x2 + a[11]) * x2 + a[9]) * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_19.hpp
uK3iEOKUO0CuIPlOvTeTy0RStUUbtIkAf3wrZ+gdDelaEx56cd9EmmTysfBD6DqiSoQnGnzLyY3e8sM7xeQjkVVp2GZVI9aXzsxLBeszZ1Y3qjvLTp6rKg3yuAiF/Owh2Y4Y7a9dtOUaUeYZbI+0oglOtK6QkbndlpG5a7wgaetSPDXrZA5lXs/jqcI29qsgE3HWntgonsu2TC2qIvdjvxFBxSR4PB/k8bR+XkVJkoi08oKN4rnK81NmUVw0XimCqW48WK9tmVYUZRxVWdIK78Qzah4R90F8g+fJj4ogj5JSFGHsSNF+7OjHLJmjcVy0Zd3mYgGWKzqCecPdbXMfU3iZXwdpAz3hWRg6+PsjNrcRdVHmSZqVApbU82vnT7/wrNy8ctLy20sj9ncnPyrz1m/EQO6dzGv1Z3C/ztZfidZvm6AIE7G0Ip/KRwm+9zxpy0zUbZ3XVdUK6V1sDt8jMFxhc481TRiWRRmJ5aXBujYMcVPGrdqiioJCzMzOzq/imwVmr621uaUo66CO4iARTz/hyTa4Jh9k5N8BTjGbN63X5E3jCSieuaU1zl3mZZm2jZeHvliA2bRbl9e5/So/a728CaF85GbhGmyJof2MzEu4TF3nddkWCchAaTIZk98rrxmx8xsUaZ3FQSXkzgCU0oqxkOG/j/PDKA7CIIllHIyP+XgVT1MTxlGdl4HhQ7o6+XgDr5t+7AdF2qq8L64M1nvr5rtYGRcw5cniWiwsLJ8bLDp18328jOu4yuI4LOy5bKduXmH6A9gB9dtM+LVFx+8zrE60pV8mXlsK6bO9X/c1pjv3Ay9J61aEaY/unzHdflqnRRIrL+hct+Hf4GnJ0ziO4kD4T437+SMft/llWpVBWGai8fN+/m7Gr4o28BpPTTX7+fsYP/KrNs7iVIRkG84/YPMnw6QswyyI9EwABYg/zvipF2dRFeSya64PEd+y/eNt/rG4zr28KjIRBT22D1na08aL2jDwYArUn/bW5h9vY6/wQ7/V0x+UIP4zbX4pmrTMotBXeX3aERKg7w6cX0dJlnpJKaI6yeqoP00vZmmKs6b0q6SR+WUlQP7oX27z/UDkrRe0SVEKOVSph7lgnu48+GpkX89kfVGWgV83ZWPeEUThFZoPYXu2ZY/GXhXETS77ypl19AM/wDd0bG4r/Kb0Gj8pBTy+uzLbfWcxNmO/LRckIo8zL/BaT8D2isqbfrRNrSBeuHJOzsMWV84tDx/HpbnfyCf43LGq0rJoYrEq94y0GnDaZD2byOdv97blW1G2WZTUqS+WzkqqPA7nmHc9NnXdlgsjkft17RVN25/+9cUZOQF9wcwA9vYHM6epXq/aeo4nTdEmjR+pl0CV8Yy//trUoU9wu5WSXqfxzTsbXFuT+6l0PuRttr7DeVhnbZaEovb0OI5v2Ni8yTZOmyBOc6EqbZDpTaUDQe6+Q/Q+lr/Mq+O69H0BpukTfBK+fWPLVaKqqzAOy0gMPdD3xjmRm2+orE7EIitKP41iT6iiHO5yjU8un+zbBDPrbLgftmd8eBZ4ywjsW3X94/9YYhcfjjjzjw93G+8Ma6JnAy4j1memQO4BUO8wfH1Rvaa9vCJrjsS13G6D670kLa7wLXD/2cXRD62Ul+neo3DcaZtenBksqnNBEgc9Jx9h4dN6B2l6uNAy+buL1HNQ6TnxjBNO/h6m9exVuDzHRknRx2tXZA2UAuvTIw/Q3H2YZsnnHBXfhf1yTvcIsqdJ19L8QO3b3kOmB5ATU95UZPtalHuvj96EiPlkRX7lEZfTN20P8IRsc16/pcs5DyTbV/o2w4GzgGtDln2OFHFAjDkojjdt78Onz9rpOLjLcKCucUU=
*/