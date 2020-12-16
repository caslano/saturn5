//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_10_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_10_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((b[5] * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) / (((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((b[6] * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) / ((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((b[7] * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) / (((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>(((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / ((((((((b[8] * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>(((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) / ((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
     return static_cast<V>((((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]) / (((((((((b[9] * x + b[8]) * x + b[7]) * x + b[6]) * x + b[5]) * x + b[4]) * x + b[3]) * x + b[2]) * x + b[1]) * x + b[0]));
   else
   {
      V z = 1 / x;
      return static_cast<V>((((((((((a[0] * z + a[1]) * z + a[2]) * z + a[3]) * z + a[4]) * z + a[5]) * z + a[6]) * z + a[7]) * z + a[8]) * z + a[9]) / (((((((((b[0] * z + b[1]) * z + b[2]) * z + b[3]) * z + b[4]) * z + b[5]) * z + b[6]) * z + b[7]) * z + b[8]) * z + b[9]));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner1_10.hpp
rlsWYcgM9z7mmzANWjeJFSeQWxBDj4JHqM482yhfaYWZlZYJ6+L12dSZ11jG3ZfUSuMkjFlXT9C0jB8w6sb18tBzC7+q16WlYs1fXGu2puQ3He8563IFr5osz7PYAjFx+pyq15rVubGRVpxYVuIkMI+kl/yNu4ZXLWP+GEZ2ablBdd6MgyfOPoz22GaTfuFEYeD4sTgmp0kuqjeEbTLvs207znzHVzJTq7T99tm03yaFn1hB6nS5Q9Qxl3OJbMyK0nfDMLS1D9ERaeSAMwQs35xN7zXGoZX5EalWtR6R39eWLvOgzMmTPM4cmCp1fvNO0fhtLw4Dj8cP9d162qP0LlCXMmeoTG5ZhZVENoODST7R7ypzzib9xnaj2M8ct20SvcBfDZ5DMXlOdQrPqXB0RN/Ya8qWxDbOftMsTENxqairR0WquzcReYv5XpKlvI3ZqnwMpnoFRlb0jNSjPkf/VjmubaVeiUKCjncHtznGXU3Lif0kg+9oj4dnUJ/Ue9YOvXed+06elXE13KEw1d+HOh1jSJG3J3P1k7x7zfF+ZsrK9I469F5EkXuR7+cg+5T9MP5gSaelzAKV8QvXLfyiEhmjIn3Taox06DzY8fMohqrpuqVO5/fniGzE3DxwsyCsvgGLvZufSfnzRtppnMZumJQg31yfeVJ9tuvinSkbZyLvszBK3NIONXN/Uxbb80+0rjzbivMgSxk6GETbAGX/5pK7HEViJW7oSZHO+wgjLrV39QOHdz5evms8NCPzKde+4y5589JOgtCOc9YUqzxcz7uGXZYdBLHrRqw9czDmRmiPnOpyGVyHcsPSjcVngMzj8P6NS99pd3MvS/2Qz/2IFPUL4dK5jZ0lURr6xtUM2n/OuoZNZer4bp7yMVw8OgUipL/iG/7vdEn7ZoWd+plvEVFpI67udbl0b6PILT/MMvjeXOOhK7rGuqLHMWF7Vug5Vl4NE/LuU135jnDpNyqLLaeI8pT1OvMRfguUfZyny0OfLe3S62xz0RazUm6PIef5flwWFld+0MkOZZxVd/09atMSJF6YFJl+nUPd1ZL14eoy44GbgGFwzHhlKL1qKl3UuXDVOeK1l3qsqfSjUxcf7xG9ivw4LLzIQ73qMgdteFSv7CK1cjc09rCwAmypj55hX+QHgRPE6l7DNfZ6cW5o1H1oFXHuOj6uW8losqi+tZ7hKyAsrbSIMlwLdl/z5lLXPOqnz0mcNCn9/+Psb9st73w7rnv7IL6uG7r8/O/JtRb4QeTce/G9+VJxu2/KSoExEfebBP+aG6r8sjvIQH7ufXtePiXT3ana9PpJyE8V/9D9r8nF/At+qPjmxqrGhrmxKO/zkN9rR1Tkvk/l/4qU6b7TqPL/ljvyfYgHXJOrcnRPkZ9nSD7dUFQ8yMM3ebxXdV73KCEPFZc9UHLpRh4VQH15K/BRX7qS7ybq4qridtbBPUUdDI925ch6VbzTkkc3aLCORHmG9wMPN2QoDeuyJXl0A4aU9zLn/ULwumxsdLTPa8aAS6bbhAh2dTfdls9ZKh7vifKpcgBF3l47Cb5TATf9YU/PzbRmloAn6/ci5WHtQlyiva505aCu31fk6d7jwOv+jFJ9GcjIPYpccwEt2Sr904JLF7GyebHuLiKPLAhRp4S+TlCeIkC9iLjOKA6ujARNjQW/kJzuC5yOsWPfQeD3XmhIgfsKfW0Ifvcn/xZIn7qquOZsF+tJjqnjD5Jcc+Jpti3qyckH0filmkjOPe7E66wLxxzPJycFp/ckqqPeniFkuk+EoHyY17vCme4kyQf2H02npg51GZcxv+p7dVby6Ie151h4VfK7H7xif5dn9dye4WP9vZ4eQ97SMOU=
*/