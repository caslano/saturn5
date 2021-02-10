//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
D0K/JmnFMI6r7bY524m8wjFYRWekPS8a7kUkce9RZ0kDrfQgEkOQrctbzpCKEh4QJYzLVJkx83ZdLAFQLqMilZMUEuuc+ng2brAcz9ig3JuLhsF15D9VGvftK0cs6Er2qRdKZz+FyZR0+09OmN/ehPfL8M73z306ztVi4f/5OBuxO1LS8jckiQtRpXN+dH9xu16slkOKeb8HO/wrxMLy82yHrZ870/SN+4dC/kLAjyIs6PExP/59TznO4VnYFOiCKIo8izop+JNV17WVKL21CBNlpGKMW9IvvEFmGJrZfl34c4v54Y/gF1BLAwQKAAAACAAtZ0pSHX2+tNEBAAASBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEwOThVVAUAAbZIJGDFlN9vmzAQx98t8T+cUuWlKjNU1bQgDynKsqZqVxCh1fY0MXMEVGIj7KTlv98B+fHUx6oPgH0+333uezbCorEyMxgyUalC0+cFu1fd5iZkP9OYrdI0hqbVbx1bPCUPUZz+jZPo9x8m+NlR8HEvu2AXsMZ2j61rqhyZaLGpO3LIM5uB0rJE+fJ90qGZhENo7n/x4drzILp32I/MYgDpDq/Am8Gj3tOK74F/E9zMAvK5/ZU6bKGVRWXdB1QbWwbw
*/