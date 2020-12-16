//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_4_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_4_HPP

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


/* rational_horner3_4.hpp
PpHeCWyKxDaUqfg55UNRA511fmaN+f5B4q6PovhOZHODO90lPU0GFimx+5syRD8L2AqJvbi+gNJLL2ZgwYpgCf0DPUjP4gbbfDmyC/VGr6G6DlhjiR2aXn8KxQSwLRLrvbfgMrLFzWAboyN71eJ7WiNiJUT+PdPknx8wZ8HU++eBvSl/T4G9v/hCMcpbYN9KLP9XJ5+SDyUNbIDEDvt9KeYx3zEwf4m1+jB0HpVbYPcMgk39epq4p6YcaobMwNqIPSDA+kgs0rNEd0qvvIE9kZjLucDfyL8KBtZQYntqTKU6Ob0C6oJMFdfAvkb22FoXtCs3mnyvaGAREuPLN2ZT7LqL8v5YU96DgP0gsSZrqlK/x6+Sgd1QBPus+eLVZOe7BlaUCfbzd8UaUlxr2KauFVZSLAGLFgzuZJ7SgLSuYmCjJfbd3FniHHRVoctjbduow8zARkgs4IOCX1HsVsU4Qzag/j5neq6agS2TWBu3p/cprqsbaOz0lwL91rEXWpOdwAyCqdb/3IGVkdi0kh95ktY6z/lXx3hBVvyxRcxLVcfyh2zrxtObyD9gBQRTzZFlVUfNkKnOcAALRPbI2sY1GjKd8qiGwdamIlvvFBxAz9UQcfZI24bXNLCXEvtmdEp9emctLGPIOrNic8k/YI0EU9fXwDwFw/oF06st/Huk7ScD2yCxBkt+YfSch9DzkaY+CwI2Ctmf1r5bm560BsY8sb5G9uyUd2Mqm8BWSaxwyWk0fgjyMrB2fQVb7zLnCpWjpdiuIPtP1rTyYi3LwOIk9smy7WXJlmUG2xwgssa1nlJ8ui/DmEDW6nMm7usC5iux4R7JGVRHAisomOqscxowV4lVeZz+HdVZwAYj+wNY9aJPh1N6y1EzZBFJ2weQ78DmS+yLqOh7ZEu6gZ0tK9gG774NqKzsMtjml5BVHS6NfYGtlJhXgT6n6Z27DayQxH5OEPvg04DlE0x13jd9N+qCrG3fRiUoPRVTa5YBrI3E5qVO2Ex5tMdA89cPFfV9h37AKkhs7MJYMZcH7B2J1b6ctoB8AOYsmHovo5TeA016GZgeMlV6OZgeMlV6pr0ivQfa+hrYLGT3gXkfTh1HdRaw7RLbcWvSabJln4F9IbHwB59UJB/2G2xjUWSXXeanUz4cMLDfkeVY+1kBDU6KuXsDKyWxWZu3U/+THcJ6Ahkf2CuTfAd2WhFs+N3lPSmPjhpYl3yCTXlgcqfy/quo53M09bwF2KcSO1o8nfrzfmcMbLmU3nufFf9AzBMZWLyzYEuLDx9I6V01sJFMsJTIzevIv98M7IXEmveetITSu2ag+brfgf3pl/on5dE1zD9kycMGH6BydN3ApiqCfRA66RL5d9Ng21ODrIPny2H0TmAugqnm67KANZPYk/YFtlEdko3jB2Rrvn83nWIeWEmJlbwfdZliAphJYtM/etyDbAF2TWIlCv+1gtH36gy2uXRkfU+N2UJ63rbVIchUc7im27mnZwb2pcRWfj62Cz13R5Sx/wDLzvHwoeeAuUns4fozZSgmNM+lJH8qzvVoWK2LV8qSZhr2VZPpG0gzDft2ypj2pJmG3ety8RhppmGrvLuJPVF3DawFsnvWd+73+g/F7l3Md2RjmuwUa4PABkns6d07s0mXe9iuIBvmdDKN6hBgxSTGp0V9THF2D/uDyJTEbHEu5D8G2x5IZDtviPNHa4Gdl9j38VHupMvvBtt8AbKEK+uPUrzkqH3fvzT9JeVfDo5FkTl/+XUJKmPASktsU49sis/0HIwzZOcepvYk34FNl9jDEWLvsuU+1CHI7lr7IaMfiT1tD3D8juyrpa3vkp0PcNyIbNUXNcVYG9gtnEu4DWw=
*/