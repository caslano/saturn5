//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_6_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_6_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_6.hpp
qfB0mAk3m+V66JSB8SBJ1VbEYbTicc8vRWRwZrNoYFlb1XDHGj0Xe8NfbNw+vAS7ujQPf4op5kpS4BZb3BnuW93l7QmwP55FwzTM3i1Qzs63v7s3pvow5DEN8S0yU8STFNZyLmyfCX0qYG7w4V6HgWUvaUurmpL/kI7wDPLIT+rLBsRcr4SQuHZdLtj0Bkjq975vijM73nDrsJiLu3e41e0dpNk5inc2LLzXXzFhcVX1pufQyTfslhbuk9VCNqa287GHB9D912mo+9mbGo+0xd4BF9hZKrKyz43fHcreAfwKGdlYIlQ9Fz/raXxv2zf3VPaXbeFnRUilak5A2cOc2I5nl0DWIUxEKwyfXwdTGPyUDJ+O6LdrQfk7aW3r3Ox8/hkhEmonkb1dbWG9a7i0ijbz8yC4h3ejbcRF8a2wogyY47qStd/MbjwoKaI7LBzEN3XKOmAJ4+4Kth9E22ep8HXgzoNv03V9HVxYW9u+tO//mPq98O1D/9kOdAXp6zs+8NhAv3bwx/v1jRautbC2d83T1zZ2Juu7R/trfkq5YM2wb+HydFokW9e0jbHo/KL/7/Tsz71973Iy3fGue+cX/f8PuXD+9MbsBudpr3iSx8F4ogO+I5Rx0QodtJ0ifOco+jPeeuHEzV59f1+utwhvYE53QwqnnjB8v8+p8H0HfH+N//6mxfA9mBMIs++HYXw4s7BwnQX/sNja7vam//nm/vvrPP/mc8L39U1/2aD79nr/7aWkw9xb6PW+4f6+vJ4avnnZTm+QP36zN/rvFaWMrlncLsy+vdl/s7hdM5VmQf7O/ttb/bfpM7pPa/xxhqys+dcgJxeOdjdm9HeM6CHkTqK/bw59/zkD/Z6zfL2Wn4N1yN4Wn8awsRq+376nP+06A/2a2ROGa0n22HVL2uTyWpf2e8/2VI+X9J3dhYz+lBsU9ICf0d98w5I+3c3T9u0bDXR/acH3M+Hb3XvaXW8Cab1p01z+AycHnouTw4esbfqlbrL7ZgPNz10vHm7lcsdvHmm7p33R5rSH3GqgxToTaSduHWnbm6d3gC2vv01OC/mQaHe8XU6DefC22w80L3Ma4rk75bTDy4cZ7ct3H2jTkQ3/vOdA8zKFzu/fK6PFdN67fx8r0Lo2MesYLu2nsr4/pG2tT7fyuvD8BwZ635U8dG1zb31nJ6effFBGPz2mvy2nn4n0mLYnPjjQQ4e+1iWiqys97esdbWdrLTbKsf6PPqTk6Rpj1LH/0BF9e3fq+/9Mx+ppwNNXkpSOR54Z0f1lHH9h5VmThfv1PKcWRzz+DMyn99m7azt7651dt+55b7vU8e6Ggsjt/Xb2fQ2vsOqxRKwR7da4iW37+2cDT9m9J923PBfpnfJ79d/pcvw+Vp7JLz488E1Haftr/D4Wv3U/9jztlTcPY48PbT0TNsMZ3YnrgDGHcd3ICrv/dcwJffd3fX1d7fr44J44XdvZ8uXYjwm/PpO+H/rJ9Vo3Ns7o3/dyT4xya6GznfqUrm88I40pT+noofoEcV+HfF/9Sy9nHTP+scM1JdaorZTqOu3qsfVCP0b8yfOkzjy1yfv4PvwTcfQI9Tv20T5EMqD1hZnoJ68H6Jt7a7OKf6+efnj9OfS1afeS0ULen9wA8PkONdG+fiNAC40w9tNbJwAtdJrbPpTa5S4/h37+poDnYHJpz7eIrC7dPND7pF3Yje1t8RbhO0gy6JNuecsR3YununjyVp4e2loyv3usNO8X/jzmCV1HbK/fv/VcevhxVsiZrlvetuT1D0ruHUT6h0f0UIdS29u6XUm/mHcN0a473r7gS11VxFq4Q+RJRZO105+X9NAI1rZ9qJFp5HnTHQue2J0=
*/