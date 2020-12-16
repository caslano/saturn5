//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_4_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_4_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_4.hpp
IkcX4YqajI0GDb+ru7qNM8ZQuhkpizxiiUz36NrJU0vdZYiK1mvu5Ku79kvHTMF1ueeQDEZYUrC4SksixzPF6o/BXc37LMTLCS3rMs5p2cQHO7os+dePPrXbk7lYlhcecdt4g6ezPBBRXdEA8za5b+W/gPhjEqVBlkZRTaCSpIFZh15jjt4WjPIiHbcE8VekyuK4LOqYNDOHSZOLRgMLMNMEhdpKMPHhXDlgsliYyuqD8FYmwAK+dw+GFsdxCQWnNKJkrreiEjyxcsrG9lnVZd5xEZe5jnPBqkLZdlBWr9tsQ+DACHOhPqtE/AURWZlGRUhNPCwbG84XEmi9FUhGTuo8COM0Do0M0+IWmtgKXQieYYd/U3+LSE5EKtnbWFwnRg4uSl/bf4lXFibqKC0KSlQQ0qbPNG1gY8CSEs2Qo2Wc98siKy7IY9Eioxm0rAhb/1/HdVkUdZRHASfKpKmYqDjdH1707GIaB2VMM3JgWjbUaRkffE0GTJ0Gewx/qaggeAw4u95BMRgKmkW0rExwCpuqtXF/RulyWXc1K4I0tQE1mrpCKjexvV7bQfNDmVgUxjXYR+lesSCVZYwOmm9t/wqeV1JZ0XUtcsvXGBp37DG8exEvI0LEPA2zCvO227VpjzdJRVRkVFjeDU01viHenFa4vIJklRCiKCLLiuf5geabQ2kGJOJhXcdRSKA/NOktSP6erphAz1lOu3wFSWkQ1WkAXNj0m9gzKB1O0jCtyjRNJUfTh+U+6qKNcNLw2j0Cl3c6EnHMEsYaTjm/6epHak7ptD7q1V/Jw7woCgEcTeb8hNy4cy5vReIqKhNQB7DKkbu7JqNYdr1YJt/Gui9hkRyJsuHpnTo+b2x6w2bj8fzqK968vk5LngRcxm91rfekXTNZfXa+inmjJMhoGmJWL/J7ptcxLi8NSB2HPGOiwszYgkxuhD3us4nsq36sRV5EQR4R+VxATyoYqgh2PaR5PrawuLCubNE6nMn9A+KK3AfOW/SMzoZEgfOYf0o6ua+l45Ahdn/kX9CgbRwHBbaX+yM9/n7GzasgUV5kUZLGhKnTYlVP1ohi/xdzhvoZtH8W87AC75dD9awIZpIGa9Jc/yyO61PmvGJRRg6tdo9D5NeeGnCkgublryvqT5jzT/LK9oHPuHL2J5XIWVJkpKpnH0MTTnNVMZORbscoXUHKuAg5C1KUsOp6C8unZJLSrw5q64S0L13r67Pjc/jt9TyRhY0q5sqBKLwbSpf8yjDCfEC9F2FkEVeWLFwZpJznQUYeO99dhxbe5OjoHBhmY0WM5HUk6zySVZM0SmSrSyo3X88wYm2/X1tZgnEKZJk62uXuc8F+JU1SEYQ1CebmoHjQjdbk0A4xfxsJIHoB+jXkzepKuHKogHfqoyCgESmatE+tNpVrS9RTWZW0Y1IyevfjJUhWRfJKZELw675ncD/dHtC5f0lZlQcpI0/fOJbA4/QNLrYkIhI0CFXwxllkyjqL2veqcx/nbF3t17m+V1ta6Pp8CWT8a0TOMZp+pYj2oM6czQ6DDENXB2oykdPqzv9/pAxNVQWDZxQa3+mhUUsDmYD/1wOab7MlL8GsQIAxwDc+2P+2tOY4BAjw/beyLEz29OjRFZ2deZzgymf7xlY+8Jg0bmG/m63LjsrvzR2ao9uG9k8n/SWbNftmq9xfDofc3Vt7XvOzLZZmU22K0ZhX95x/z1YH656PKPoFQ/c3fG1eHrDNxcCcwdIuIhp0QseH4OaWhjd3bf5WbwEY3G5c27/nlpbeiNcgdahn8tHg5DcT58R5h+VWmgYCQLbSzU743nuqcT9UMTtAgnvn/YZ2nDl6c/VJbt2OlRNCI+9KO8Y=
*/