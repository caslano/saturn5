//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_3_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_3_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner2_3.hpp
izfS6DhwKBYcZqwvwZnPpfQ1bGVbVxnDy1+/gVMfYtVR+4szU1kTocdzl6dRMThE7Fo+hb4LZWs1Lc7AfsMjqpzbP983woHRg9JE6HvQBWl0PTiMtXNGPn5tlGyN0U7EdEd65PtAnjTeeVFSaH8NzWHLGNElKD/ytjR6DQzGCQalG37C3rOGkrDXWpwi45hNe7LGMdHD3KHDmBlAgtpfXZpGRyF2VyIY7PrtgVVylOMpOxN34cCghTeWix7mcJ77uWWoGKbgcDN0odS+v3Dm6dhNTXD2mSWWPAPN7GGEQ4hxvXTLUP5kNM25H3qJfT+0cvNKOdKJ9HCCfs5Xx+s3xCKR4vZvoaqxfBZSF6LfdRIs9gOLMsGi+Jfr9sfpBvWN11UFi7mmWETCBlhASMd8MsHiALAoFyxGFbbtI1svo60uvVhrikXYhF5ASMf4g2DRBywq7JhU6J6jZevlzhzxgEWbMRZFYQMsbCH6HDk6jc4OShaVgoV11oGvydYrqLkTXs9JknZzJLPdRDfZdlxKgCsX+Yg0moP8wiq7VuYbKRW4SS9q0Kg65TaOMZWsednVsUL7K1R76OCccVwcNCFuv/LwNBqOuREVLPa5KhX3Q6+ipBScEifJ/VaU16/s0E22qIxbhtpvHZpGC8HhUsHhkNTGu+RIJ1F5Mu6GgkOzGQ6MGROaCP0eea6wlfAvqwWHc3/bgdo8V1MbzoZHpsjc9JG3s+YaopOsJ11uGcpGHJxGP0AfYoLDwY9kj8NJMDWrN5PaOTRPN8OhsIrtUMctQ/nZ/dKcejQ1gkOo86i75UivoR14SyuaIudFficj8yIaY8cAER3nxX5pdAw4jBccrpkXQ1juWrFewk4mSg5zDXHge11NE6Hf+UtTcakJtv/QKzJRtl5H05CDOzNdtNt3N3jfBXI6WRGpKWEnASFabMqTRmVgMVGwGLrXYxfL1uvJk4GzTsSmoh+zxqacbpaxL50Q0dG//jFIc+FP1dr5hnfP7yxbb6CevWE10+TcSE83MjeqDCyecRkqNrMtSCGsnZfZ55xf5J0hR3ojDekpf1sLfVix2Yg+VBVG2K4zuWWoO6CfB50143LB4eteg1FH4CY6zoscXNjKWjP6UDmer2qVW4ZaMwSHc8DhCsEhfd2U4bjVRsOxZmSDQ4shDowxKrcMlQPREqTrwOFKwSHco/dJcqRTaCDOdGq9cr81ucLIfsvEkhGXofYYG4OUBg5XCQ6vvzirsr1RRDKXdkfsFnUUxpjxKRnPMnQRei3tIPUCh0mCw+UPxLJk61QamIr/MFnOixGdjcyLcXylHjUR+hmf4BDPi7lay4uZRiWuvOzJvLEYdJIzM0YTocdj1gVpNjjUCQ4HPXo97nXdQpSI+Bzs5CIz+lAcibKDiMtQdvLtIKWDwzWCQ9OSlsFypLeKPFucaWCvldnFCIdwdZTtbMctQ9mH14PUCRyuFRxWPtkZdf1uo98T1boZsP0oM/MiXMKWA6CJ0O9wrQ46e87rBIfKhEfgNUxvz0en9prycr1ovc3IesGZMeWWoezD/CDdAQ7X2/ZhTgEyZG6nvvGXB7pRe4x/0brZRjiYcCAgRM8nnRd0zj1v0M49Z9Bw17lnG/PcKI1GKooLqiuKOU8+dSl6reSpQRqK/daNgsXsc7y17Y1CWxoysG54pZ3I7mmKBedxuEuMuzbVlKCTX3mTll85k4rj768myByROub1IzzE/grFGMuqu2WofdcNQfoMdakmCw5LPuu2SI70TnGWgZhlouTQaoZDpJLttE8Tob91f22QNmB+TLFzyDZvjMrWu2hxMuIR9n9r554/z3ovujqca3+JM/thQ/hAKBl6DLs=
*/