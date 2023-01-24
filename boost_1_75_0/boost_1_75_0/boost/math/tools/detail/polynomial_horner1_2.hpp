//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_2.hpp
y/8mi+6BpyJCk4YwxemMgSE4l3TVk+SNlJjnEKQojwcSsJZORqMCC/wbsoBYFA0ukGZgF6JN6OoTdA2q005mHQgN/RMuoK5dRShQamGfQ8UX4xFIS8VfUGcLjBHJY8elbQFJ20KHNMPML3IaBdKWznxwaSud9OOmSD9OQ8jRS5TGMmELNHtjmlyLGlZLE7eaMkV+WAsNpx5oOE27z8QvfUWVEXFSpnW2jHV27GTVguqnngsAEjpfy06GtFWN5EdN8Y/SIbSe8M4/spjRlQ6KdonD3zcd6ZUI4B1JE8cqgCCvlCHi4tecJ23hDWIAyAgl8T6iMKTk0wnswILADh6BvbtYjGHzHk9RuNQ7KUTap7sxyfx9N+VDNfvwKbwItd4Nulvog24drDM89M+zyud/r46Wz092Xj6/urozHNmQ0BFH/m9XnTwJuxvv4y1nhfuC1R2Lum0E/9is4PAqpGTLhiBbjIrrFLCT43WLUWErxyO7doDjy84O693+aBwzGCeKgbVsB+cHoTKr7iK/af7OgPpCXEd43dAlcv2G7Ab9PpLlr2uOeOJ/J+i2NgCadvC8tUqvABWAAmQv20lQW3zf0KxZwyAHYbfXOSRo2Zo62rK1q2Af8o4nSfQG4/JhLv/Hd8TTFaZq7nVmIbQJdDGw+ooi1fblGK51VkeMJKsNg7aqZnIPlZEUMkbS0gSQMAP0vVB2d50/v+cqNnvH
*/