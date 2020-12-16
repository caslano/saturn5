//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_8_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_8_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_8.hpp
ZZwMlATlb97ndeqFDrB9rLG9YBeGWXMDsAsp2JsOMcKAN2tOSVCxqtu9dD/04ADBYJ/AnXPlKA+xBsI21nvlve3M3rx3U2UPuc/6lAjNLl7rpf64w3+g4HDSlK3IEcqzAvE7/H7Joc4MB8ZSBpoIvWZknZe6YE4MFBz23dIPuXOHWpuSVQx7D9s2MnOorra/OF+D1EToORFXe+lkzItBgsPyYNFI2XqYVR9fJ1E3cWSWEQ6M7+dqIvRY9jgvFUAfDhIc8vtsHCJbD7dqcRo+M0NyyOpjggMzA/ceIuJ17iofLMb/57TN58nW4VZ6CvznJPhLH/H6CpXjSisjBTVFoeoYX0hCF6LbyGLFIluwePL+nr1k6xFWhotFqzEWhZV8a6YmRT/rK/RSPljkCBZfTvYVytEeaW1FZHNNMvRikyEW0TLOEhduOfod7jFKN3IFj4feffwpOeKjLI9bN0zxiIQ588h0Me4cqpDiMVjw+PWkpwfL1vzd7cbHhngUm7AbENIxBnGR13nXaIhg0fjpuq2y9WhruFf+Vp4M3TDGgjcS4ZKjnwteqHRjqODxWMarqBN0jJXk1o3NpngYsBvFLptxvtKLYYLD2HXf4F7rsbvrhSkO4dJoCeM9Nrcc/f0KtaYcInicv2LBQozY2toFdYJSkXf5iSEe4pnbChNripKj9OM0r5NDkCd4HH3moLVyxMdbWTg7ro2/QW6Eh/gRqiksKufLPvwHOcr/Ejzi958PtTrefz7ByoqPPkG+ZzGG9z2LDv2sLjbggilB7n3aycqWHiaYeK/e+bVsPdGKvwFUF7/T0WJKR1ivdehi3GdCR3upL3gcbufqrkoZFX/pwoPI/2Qf4v3GeMj/h2/7+o+SlF3N89I9YDJcMJl+2LIT5ahPstqgI/U+6MgWU0zKS9ndDyVG38fleJ3czSMEj2sv/glJqiLisTfy+wOwqwZ58B2I7CZF7e8P8tJCsDhSsCh4q+YWOdpTrOnJWHPjvtinplhwljb+m7izj89yCuP4OffzurX09KKGSaUYhjXFvM97FJIwlG09z9ae2stjz7YmIYQhGkJ5nfcktSiGMBWGsIgmbyE1RJNkyMu5d37PfTp3/tg/1+GT2sft0++c7+c651znOte5jkvGbRsHJrE88Dhe8JhQOh4+yCh+cgBnpn7MH8Z4FNE9ya2r6LFxwSILLHK0+0Bn8kr0vJXLfJQRlbTnA04rSa8EaSp63n//JPYZ7oidIFgcc/9ZHbK3Z/FVu2OcdMM4+caUXUQuowsNayo6i75J7FTYxYmCxZ0/lI6QvT2bN4QwfwYxfxpjIR4GNLHAQkY7M+ir/NKTNL90NE/0vhHjpM7YOJH/JVJYbQKKo6XZSY8klgouJwsuk7d/gJqf5/BRsJNtif3cBmN2QniFTFPRYx6CRT+wOEWwOPiwoYh0jOGZiZ57MGaMsaA8UtFUdLvwJbEzweJUO/+g4wysrOfyDPjorQl/9FtaFmHxqyaPNGysJNw1nL4IsrPB4TTB4Yq2n1E/fizPzUEeRqo8W6olPluyGxnLi5fG6AxCSbjP2NYE2b5YW0fYZ41r27GHPY9vTtQND0oO7UY4lIfp/C1HoYt36s7nq9gu/5CuIbKFZWLjFKuqjFIbhKPTRR4X/J88hmfR5XTqMl2uX5L7f/KgzALWZbrM48L/lUcWXc7Kf8gwtaa2BNleWEvOFHPotqa2z+XXi/i4JMSK8WZZ7iATc2gZZXxHSbjXklVB1h8czhIczh30dFR+vdipcVOLN1+bjHAoLS+j5gAJ7T7NiiD7BzVTzxYcjhh29xz5dRwf5XCQ+Vzp+9JzmEyaxqQpqFiOYDAUtjBaMLg=
*/