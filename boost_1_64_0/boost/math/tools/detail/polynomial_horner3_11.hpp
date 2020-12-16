//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[8] * x2 + a[6]);
   t[1] = static_cast<V>(a[7] * x2 + a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
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
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = a[9] * x2 + a[7];
   t[1] = a[8] * x2 + a[6];
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[5]);
   t[1] += static_cast<V>(a[4]);
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

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   V t[2];
   t[0] = static_cast<V>(a[10] * x2 + a[8]);
   t[1] = static_cast<V>(a[9] * x2 + a[7]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[6]);
   t[1] += static_cast<V>(a[5]);
   t[0] *= x2;
   t[1] *= x2;
   t[0] += static_cast<V>(a[4]);
   t[1] += static_cast<V>(a[3]);
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


/* polynomial_horner3_11.hpp
qecixPpql+jra+Rlnr6iKOAsZoPytf8q+jriy6oTSrNgkL6gMQ6U9ZqXeWVMRJJwHm7Emx3dVKIr62tevsowS8usTAfkCxr+wHz92ctXKaTGeMKumq/x6dZ83eflXhkpzwrGoqvKgu7TIuuJriwWkkQWkcdZoWQd3n9gYmoMycS16so6i/KVkDDJaJhxsiFk00aB3jv/uieL1iENOB8sbGx8PxZmZf0NySrhXkTGqyIiuHSD65NYWQ94Bc5XndS1CJPBdmJcyTgmZ9hrZ1AZn4hklYSLOi2KOL96fxwf1RJRu/fyFWUZT8OgwPnypbTn69IrcJvIq6KoywD1oYHWQpbXPW/9l5evOIcVcTTQfHnqsnp/JdZVQtOcFbXK0qbSUPmOIFkJSXIW0aTkA22XnylX76/EuhIVBYfZ6hp0BRMGbOu9fNGCFmEdVzhffotvz9e/PH3FUVnHOcuvbgenTUmRrX+Vp3vGqpxuIgumLS2y5jxZXPbFvKBXFQWzmrZ6PItkpYRGIgkzlqp+vWnzIq698WQldZjnouSDZT1kapCsv/n5qqoyln37KoYQ9UZk61/t5StgVVZROtgOjkwPknXYk5UmcRQUwTWYVCPKyHqJJ6suY3CdjAYLe8jYoHx9wZMlaB3UVTFQ1PjIxMB8/caTFbJU8FpcRdjk/kH52v0aLCsuSp6yOBssa2qg7hNPlkjqnKeCDZQ1gS20a1NPI1kJEQGnWRITMDPXMgRlel8PyYlJVYsqrvKQbDpz7p/f/NCTlYVhklZSV5vOKvtlDb/Wy1cJvZEnjaxrnA+auIiurCQkRRzTkHNBZKz/h6TikNy+Gk1zfmC0PvrUxe4ZLR3eA2DjTSKgeivvkicvTYMyjmp+LfImrDzbLl6HfbjhdC4IZGUejKi0fFPQBa+iPBBGtKxnebKSsihExQosq30O5su64MtKsixLohTLaq8IX9av/DKmCZPyAiyrffLly9r9eiwrzKI4KcKr5mt8rF1fhScrFnVRJHF+VVnT7WV8rieLFSIJijq5mqzJUaz7Sq+BPVkJp3HGa3a9sWtgr+mHY9JW3xX2kxoP2yYLPdhLkrQfS9qlZr0Ne0gwAsNr1CWflY2iozA/lb+dfmgLRla2xvxCYpKHtWDGpw3m1xLzmoe3YOS6pOPkhzxSY5pQ6zZDjxkzmL8NxIw3mN9IzIUDbRg5oj1m1GBeQgZhxgzmSDAAo9L6ncRMh20Y2YJVWn+QmL1UY2COoyDSoh4c7RjM2UEYSQPMH+X/72BtmLFpKcdgzg7AaDl/hvzwNszUSK7k/BV0OABz0MEcjtoxOq1/QEuKEcZUl07r3xJzDmFsG9OYzrisiwRhjJoBA239xhIzkmoMDBaz0zL1hvZnSAPT9mvaTYEvc2lSW6pNbpO032QoXZoEB8dkvYxLPRjMfN6O0XrYDnJaMeOjUo7BnC7aMW7dDZeoHynM1HjesZizJZJjMDItg7lP1S4nVHJuJfPzhapNzn6QYzCn61aMKfutJWZa9KcluxHk2fS1zqPaMWHHyvmhwdi0oDvqdnJbiTl3sE3OtElrt8S85FArxqR1J8DMtGDkukbLuYvEfPvR7Rgt527Qth7bgpGLGi1nn8RcOdyOCTu2r3398cjO2AoDO6Mwq08YhBkzmN1PHIBRNu3eMj+X2jEPkTbN2OEjT2rF7B91MLufPAhj7fm3B2FUfu4HdTHbhpGLncdae06OtGGwzd99tA2Dbf6VVoy1+Q8cl3VxrA0jFzkqPyMSc+F4G0auXhRmHDBzrZhJnecpsBvdVsyULvt+idl9sg0zAcbF2MbVeWzjmnhNkvZwSfuZoclJrPw5Ojk5m7JxoDc=
*/