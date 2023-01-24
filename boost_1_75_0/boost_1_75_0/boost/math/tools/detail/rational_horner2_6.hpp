//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_6.hpp
9kSZHZtcCY7Y2MRzjvjpZoUCXgECXjWZcUQABN99SI7Y/qci5o//fFQc0eimJ2KdMukBOMLcmIs3gcVtpzvfgoyNqoI5ThTMcbr/819MwnGqgolzUTCwTtD+LMlLNI3czlii3ZN0L5dgyhKWuTBsru3U3VdjtvYClXKtGz0ElbKXHdKFhSHkIISojqKpOpI4hWn6dt/PZJo+WgnkHgY1ZYyBmlquUerG1jdMMtQpUiqnVhFUTlH6KaVyiNpIfdqU1yvRy6xEbs/0A3aA2OxmFr+9qn2anzM7tI6xPmVSm8UgkjEzNItbpEj7oeRmiFU9UdU9cSC1YX866Z64UronAerv4wnl0UM5dZjZENeh0kRkkneqvtyiiqrPFptsnzeBsQNJb4Rmcmw2zEy1/IV2BpsTQb05g1PEeLkbAevfpigKHvgY9m1Cel7l48v6BXuUWhJsfYIkw+TflVqa+LubWuqeFyF4cWroqnVDDfGfE2ooueqOGrqzLP9g4Vn+lB0G5EcEytW4ZLKOkkbIHFKLyTKDTB3vUotv/+FJLdqTKrG2wbkeDzWohL1W/HtF9pqtT4J9Z5KLtZZuodYa7KfQO4j8hZA/o2DtHUd+g8lfGDkWskbGETndoq4CvQOjrVODSPVOnOS8AKVzmZ1y/YJNagXHBkuG135TKvjV39xUcIe83nFeqo1WpbSNVsW5FXZzstHOTaQbTrdawLIL
*/