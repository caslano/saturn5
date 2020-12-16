//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_7_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_7_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_7.hpp
g6JixCpUS6HMoZi+HeIHpZ/xVMsk+rI9ykyYMgXLEnj5Mk6YcZpJp021Gz+22k3qpxH4WrePQGGPY/pNhJi2gSoMUo/Hab8s7W36TYTYugsaRXHuFw3iKm58g+w9RLZkpSOGJO5F7FYmIZl7FcYNK4woS8sg8vKmMOxGqP0tW2VQ8DStHB6xgaeV6T3pkYTeVQ/cKvDiomR9x8do2R1IrPPoYSCGKqdk/VNan//+iYS0kyjKojJ2C6ZPpKHMSVVWPomvYlkaeYVf1X2m70ApLSxdVrMJLavAdeO8CnI28OghlX+lJZ/wPKsyj7OBRxLpmPNxIi+iTco8zsOqQZ62eGN++B4JA/T60Av8gDN6YNMe9phKw++tNOTc8VI/T9jg3YK+NIym1hzju06ReamsexkG7vTa7xUcIvIei9zAD3kYsD4rCr23fsKUe2SY+llY8Yjpw4q2H4E4pf0rLLMy9AN2K+upPcbPp3SMz9wijN0yZbZpXPoD0X4cUjrGl4HP4zIoWLM5ts+HxHuIvM+SIsm5HzisfxdQyTI9txHZgolCSnkaRuwWJt6+uS21/PyLBERlVDDrWIGUW1Tp/lNq36/PojDnOWtUU2n/GM1o20wDNyyqtGCDlxG6bar4D2e03HjKszAUld+vjusxRtUZy6yxNI2iyE856zNnNI8PZy35uAAXDnmDOB3lQtVmiDxnSZZlflQ4rNncYYWC4Xw8oz4pgqx0nNR32G3MUTIgXR8/IuEErArc0ilydjurE+iTKox/kTDgnczST12vYLczQzEM41BOfWf7VRoFue+z25mmRBiqTHhOy6QKyzwv8qSpbDsXRSCkhrFs16xwvDyOqqQsmsMhlUTCuWaFE8a+KN4swzzRcJRB0g7nezltM2HgVFkQe4PCkSa7vjZz0y6fOAjdKOVN4YgjrdqmaqdnX0HTUzp5wZOgsZxXSDHT9DArHLdy3azwikHh2H1BvxVb0PZXOKmTJqk7IF94FNKYM6+SMCJW+FHhlfGgssHh0QjjRkHnoiBxiyJ0E3arow3W3P3b/3J23cFVLlU8DQhFiIqKioqKHTWEBION/XovSlR01EvKDYmkXHNvFB1nZBz/wLFhx44z/uHYHfuIir2hYhu7omJ/Kvb2LHu+u7tnz957EXzzkpe3v9/Zena/LWfPZsb7HE5qZ2WRsu6mF/r8gflyvpfTdrZLN0zAo9//MN8wx4Z9ubHWTWMvc12vZzwqM7jWLHNj/eQkThklITNN09qCNTl/nNPlclbkeRHbocP0E0XTd1grp/6BA7fI8pSRg0bzLZPTOR3PkzyIoshmPa3eKnks35uM8gW5UyR2WTDz2NnwuXg+J77UuFTppjmTlyxE0fBdiM/mdA3lWvDyi+WwbmZ3Io9Kp4x2LD3X4m2QsWuYP3a8I1VQvz62Y3sWuNTqYl5rvrGzpzDeZArsPIui3JAln2xbzgcL2h98P0miOHZY7+sYInks/+MLuq4I3DIvHKdH+nSyd1B+twtDj+MktoPSYsa1GCE2K9v5pboc9OLcSjw3YLhPTe9Fv1Hnl6woXc+PgU9u19A58wdoGnno+46XhSDTdV33WVoWmDM7nusXbBp8wbcrVdxQVnpoy/2zgupSUOauF4Ee6u+iTy/BPjt//Qdyq+pSxtFX0vWN6+aJZ7s+iQNdNIluS8cmVhpjkxvwvp74rH2sg/7Dmp3+w3w5xpR0zM9jL7PzEuPgrhCn+a3lbtHpftReWtK+Ebp55Ac5rJV4EaBXVksXkof7Sj9QuuyD3Njx0tRuC8Ktb1JvHyhpXwitJC6KPGNCYxdxkDIfnZpQvgVLui6LY9f1ytKRcYh75vOr6yuyzhc=
*/