//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[7] * x2 + a[5];
   t[1] = a[6] * x2 + a[4];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[3]);
   t[1] += static_cast<V>(a[2]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[1]);
   t[1] += static_cast<V>(a[0]);
   t[0] *= x;
   return t[0] + t[1];
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner3_8.hpp
5Fh5lcgGMEfzA9uyUBaWOR1pj8n63vYI4439MLECN0uovMjBrNqfa1ch7yLKHxuJx2J57pa257ld48El1ARunKFPp8c/gn6zI9vNyjSPu8YFXYNGhG+BkXh85tipE+ZOiPGInohKQHxlvlWXh62mMgrsLGLwaWx7pVGPl63Zcv+bpBmzpHBcL8lD6YOQz1FalSu+9hu02ltvOGe+idRlwJLECi0/SmUc0I+rOMR2ZXu7iPdwfulJ/z7sfqS53ndd2/F9GU9T5AXzgGPKOJHNWJZEQZDacYes2taGIZ/25aOPNHz75IHl8Ezgu391uflS5QGf/6P18YxHUh1N/CIMytTHeEBYRAZDAY4SpD7OG/WR+3GUuqHDlnkUsOFSjShEGxoyD18nefCZ6/mp48cpM9tAXjw7PPHUNe4ID8qkr8v6jtDxwuWdLS4z14gHhbFC6urbTeJw4UGW3CqhHM3jvDuIKIhSt2Q5JnVZx2Ge7/lB6NtEVnSMxfZWhVR18v0+RvKQsNwK4ywrfRoPLYa5H3WKxGExO3SLwi0ytlIHjVgFd2/6qYc6gzhizLvKIooKN2TVgDCNYwL5/KMevNOsvygKk9K3QB51ko4pD5Df6SPE30ZoOZYf+G1JvtATSeH5zNdJWg5LHdtLrDIFCaG302A8BA7YzHzeZMj6ThRHYVxosi24P99YlRMszOfQlD6XDcMgLALPa0vCQkfwm7Hgj0wZ62I384M4cxh1cQJfoTWe7MJiU+RA7aKhL89JPa5DQWSFSWK3HV22v+KCL/VgV9RH324tk8T1c6eSIGM+/U4/Y4r4VM/TkiuPx8T8hM4Vn61zS5b4gRe6QaLIlbdQNVPFecTZKWNfK/WyMHErueqD2nYoqx8YTUg9fSeRDVhY2FkZpChLB9COfbGLhnxcZllqpN35jCbW6y+IvMWK0smtNGoXmvRT+nbTzbpcxtK0LKM4qKSMZSmuubY9itSv69mhZdltmbXFp8DsUTQK7R+jj6L1mxVOmVkZ9EXVf+EP7dCVqXUikfVZ6jk2Fw+YkhNPVeNQSOrnjY8yfW4HfpCGMcMm0SRR7nuGXBJZfpQVKYOm6JhWYlmHHm3saach7NGErHrJm359zL3lXUQ2ZikXjnPeKl2mZ3TowjesJ/U4ClZEiZ8GZYJREDHU45CkHbIyz6w8cnMUlD2ApizzPkfkI+blQeGGBea916jL827Lb4URRxY5ReanGfuf00qM4zUkjpR5pZ0lTuARf7rQfvCwjxh5Thp7zZeMfARu5nmRa6EvXTUTqI4QF4y15E26fMoCz0psq0xQHJdVS77sj482vtlBWfpWUupvu2LrV1/saXF+Sb7Z7mPoNztwiigovZzEA18xlBe5x32sucfQeVAch3FZ2gmJg8zHMD/6POjMY4wzhyi3kjij0Wj9UDusWfPl+EriKJjrp1FYuk5HJGp+SuKxlN+zx9B5fllmrgdtUt1mIj2yflDu3+gyJSvSLHQtx5UydHWg7bv8jeTZZ3YZJGXu2YzMuKi4sic4SvcU4BTT5XGYueTUdfAx9sxJvm++o/Ixlh0xHoAD/BTHR26FOLooA7sjfB/uQ+iDDIjCBRnaTo8u0DtS5omweafqncevzeeUVWnnfRnvSRmnpOjP4SpyTLdSQGspe/Aa8rq5HtLjHEVuh8st4OXyG+RTW0Dfywsv9W74vtU9Nfu98/29DpWRd7kfeD0PyBTv5oHuPNE5lY1fa6grz3QngDaBG5Df89BE41/cdA1+F3vmxmbk9zwE0fintiC/9+EC2lg/fltvvnFDXdlW7t5OZcxN/0rH0b66N7cBZGzLl4505Yr7QsibvCXwuhvF6bzdt0U=
*/