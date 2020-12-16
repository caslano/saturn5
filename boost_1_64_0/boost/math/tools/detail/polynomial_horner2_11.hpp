//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_11.hpp
njt1uX22+Esvj3O+vafDAc8ZrL6IOzMO1DfYYBq37fS2u3Q5sG5gnL1dzoKcqNicS3frcHD8xrtWd+9yoNIMrWTdYdnXy+vcdX/TPfp5kH6+D9XLo/NJprzv1cOjzRy6o3afXp45Q4G8j963n+fejXv8/l6emVYhb//9e3m4xsI7pQ/o56lTQ5Jp6xw90MuFxSnjLT6ol4cLXDyP+OB+3nlpm4UX0pwzPPjfeNNrck0jf6U8ff2h/40PKbD8Rz68w4WGi2mce0QXH/TUr6lH9vPc+jX5qH6eW7/WH93D4/UL/fp1ed36tedwP8+tXzCWdnnd+hVO9PPc+nX70X4er1/ks6/L7dave0/289z6tXy8n+fWr/c+to+3cf16xON7+bx+mfnvEySX+QBdBT7O8S4/EXDYw5FyUPOsNcwVAZjiw2If1xav8li462aQ/H75kgfza0xqFU2lTag7ZORdDPp5OjnImwz7eXrKj7yDUT9P+aizeF/fgGfWLbU5H8nmi6Uoyqr0iiq81fmivRf9Ryw/nBvIhS6V8dSmPg4bqsk/yuYOd6D10Z3SLYyjmwnpuH20B9et7gHor4VxYH6h95Msvz/bbQ42M2wT18d68U77vrEDeNJyapam8zO9Dvf0luVWI9bRn+0EngqXBCqzv2zmZZYnRRmE6S2Xmb3u+hOmG7tBuuO9uQ9X2SJ/v6M2B7tI8k+ztQfH/Sa9f7KtjwPmgVmvNa6M2TzsZsnHwM4+XO/vmjnLLsaB7o3mm3foYLS/asr6jjYHuz3a09/Tgzv5/fJtjMO7RGovcAduY57WWZtvK07dCMsgTZJbXv6xuvFnFffTVLT64wPGdzuLLxdR7Udp6N+0L28T4T2t+P6i4oMn01RsDPvrEJN3uxBDPwSEZcwmz3TSWIZpmMX5Te9H96XxbyquRgq56bAxno4vb+Lf0bKgLLIivenvaDodeG9p1M6X34o6ypuyDjx1UUbetZEfsOGl88Uz6rtZoELVL0fPnR2cW11VXk3pHs2mw2ZMsPWWooi8KmvKULRqb1y9uIPvD+DbnrZMJWo/bJqqlTKyDcs+zRKiuxwlj6f1k6AO20S05lT9oPuN9O/UDmYGw8kL4vs2M3x4cHLO+ua1heNL6wPE9o4yTA792E7ldysXm17FJNpz822MB9NTm4hxiTHGY98r5NraxeSVVisPOxkOyzY6K9XFpsOU7PO2XT34CY98e+3u4lEAX99JxyPu0OU8xdJxvYurrx9233ngTi7nEEunPBPUxa04Jm/r4m46wzt3OJBOnJe2d+ngcBtEf6SZW10Z7rUj/017Xf60dsSnj2A5/ty/fFfGZ3sVy3djmL5NwqoK6pm8O+OyfZEvc2x1TaZ5qGVAfuju0ceBRsnv/U/dq4+nGjzq2nsfxhnMnJ+3E4289L6MZ55QUw3Orgd77sd5bj24uJ/jbj24cX8X79aDxQdyjlsPvn2A4/31gPRNPdjlaz/dGhcP6cVhUwjLdPUg48A3RXoj4KEMA1mMu3wYw+THIflQlPWdYvLhEqd5JXwrNWtfXBO97xHAARzThvvrex8tMVgznDw6fnzam5p6SuY/dSqiTyvW+mnPOHDVOAIHpXCMe4MzxhVtkCdeddN+G/vWE//APONcTn5UpXF13YnTD4s4C9Jb/g5hx/lPinNu3ooT71K8XN0zaYvgxNHp84enW78I48OwXlg6/xzLN+welrZSxG2R5Glw8994VdooryHTl4q4zKsy8Iv+szMyOdKFrn2ARp2a0edv5UM3uEL0I7m2KumREMAXOjg9EgLfeRclDmCQtWmk3KsOz2Y9V4YP7dF6T/EqpWulo4seLAGZZSUTaQk=
*/