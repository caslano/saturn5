//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_7_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_7_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_7.hpp
xzYHnmlwPMs6tkdzoL1Nc9u6vbAXfgcRUn0cs1MGp1V3ODsI+EhfoZ0txUM7KhefBeMY969ub3d2uK9q7P3MhdCuNYmEFLcQWwfaF+MBb1+gd9BFG6m6yfVe+oz9E4tMNsbqAH/F/eiJ1N6Tk7QSFoui5GVceWmJhu+aEnP+Sv107ql4HaVRwfqXl86eOTl3OvABR7iyyNqCV82QfGreuWOds/ynCR/2p2mUySF/7sRJx7fz1LM+v2GpTr3Myopd2tKbi1OzJ06cPXPG5JI6n6UX6J1plsRRVbH+lfUrvbOz2/dcCfyx/Ju0W8r0eKlklqRMP+bR24alTstP6JUZXNvdoxss8F105JO+PIdLVx7JQJzIYt4zRFawOm650q1dg5ujM5/s7fS1NCwNQY/QZsaN99yXTyLWVjJp47JlCUR62RycPQOmbpDAFf0AYl3fOg/Onuhrm5weTJnVyPp3m5SnYFXdirLprIJsDLzhVJskXWn6zrwHfsEUT9v760+SvigyobtPMl0c3TIbl2xathz9T9t77KAcKuMQvj9jLp+5ZQh+urTzZZuG02colysgtpkbc0+RNkuZ0iqYZqlgC5fXtXkP/Luk1946vGjXC3OmueauDANhQjkT2/d/9dOqWNLkRVqkNQw5/BOUI7Z658s2rBKRitImYh11fAKunVw88U/57VQxGfO6Sis+2v9Bd2FXJam9PyNpCRbXjUpzOP2aA0Mf285uHPmNDCnZdJifTiK0DsVllTTSK9PO0mYfgiCfEZsrW6vGvmx5qd87zXBu3CDpxAzisBVp5aXD1/vbW/31gRkj2sxkaeXyFQ1B9bp+cvswUreStWkhFM/ghdSa3n39z/p5bZ/Y8v2UpBmzRKQ6SbVbB47rybOn7TroU9RHWyKEAt9TPR2BY2NrW6vfGTB6NGVAueepXCGKuJJ5w4zOntnprfTWtwdOzsXt8uVqVudRJes0M3IkM2ZlJi4SXZdpk4kiaRm8DdK129rccPc6zJbv8EVqN8lTVWfgJA08HENsR5IZxrY/dpH6Lu3smRucw78y5A9SO4+SfGLo37ZoeNC92KFUc9GWkZN0Mpa1eaFKnu4ynqA4/jwaxfYcIai3TApV8wLsNIdCZwbWBBnS8dNgNo3BRTo/tHnedkc5c/+zPiy1dhMXaczzNItLqQr+Cseisze8TstSJ21ZtmnMVkwypjqQ+Rmn00GfyCpRPE7ZmC8RyG19yOq0LzdfyjJL21IynO+Nv//UzsEkn5aVSQNHLMlu32+cBCEl7LND91E7XdlEqmmjhqYzPhFb9hk/jdOxqqukKks2MEpjy/4Fm+c8ybNgaQ67urbcreygO+F97UWSRs6SKE6SlHOaxkgCUWP1jMg3TOl/0qbJR3UeYsfplDaW1mHZP3xo27j1o/P95qdXsUY1VZm1BSPSIOH5gX/clzkZR7C5q+LhZzSc8568D+PIzyzd/A+sj927aV9u7eZ/fLmXPLlTMzf/48sd/rQnd8/N/4AcvJ//sz7P8hzBT8Bvf9S/ofN33O9ch0aZjE/PDo8vujOwCf/t5STgStQGh4MO4HThWZeuuLOHl6eAd77LYmVnY61zL69/d/gBxOEQxmb0JmvzcCfiuo+JLdEzr0YMS4l1WH094LArgvc221dD2/7VN1rciA/XjW7v/tW7AYeQqV3JgIj+O94CmPWhANW3Ncf07z4KHBgUi938Mnxlgfhf3+7wy6s7sKft3Ge7/B8+RnB4+OOw1XcRDN5QOOz5dxMMjgscduM9Pmb8MBns3+9zWFeQYY6I/+H9AQ65erj6YIhDzogf/pCP97sSkDjDc4B3M/hiX88uAw+7fgaw/hcguno=
*/