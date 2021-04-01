//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Unrolled polynomial evaluation using second order Horners rule
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


/* polynomial_horner3_2.hpp
fYc2fMz9JcASVsBlQzMOHb8ZmufayjGFbkUQXUG7Kx3/loe7krL/12PZf5/pgXkWW3P8uPTpz6miTwngn1XztAZU54WanDgVvCfNNKw0e9zNfIgud1ggwjnwAOSs0iirWLRDW0WNPMw8StHCUO4lLp9nsX4GxbJTFrvMuleOr93Ak5ky4TtmOj81JqdxLxbesc8XLPHd5K/Is0sQs9tBhVeb5ZI7yjTq5K4o2/aLvttph46/uc4ydBXAHXjyyVUNI7wKYKMzxyDRR5EJs/q/suS6QewUkyIK9MhqlV5+YylF101ONq+YuuJ7vwG1ne80I3mKu2ctEvahXPAIYG1zN3Yfa7hjvNDKUtJHU9/cBKnCZwToDI8336qbqpRUXT/KBsQajqLgHGgxZvckGY4gQYAwpRr+nxSQTewDWiaLVFUYMHfdLaWTyE+DHpUqR6bi4CodZZRY4CNqpJsmRolykgz+TCeEStdeVMGv5hSrpXt8wzBcLMc3og5ooO8dpFNjgVnvYxrb8G/KHie28V9sZ4FWOiE+ly28GcoU5gpwbEkkI6PchGBopsWG6g==
*/