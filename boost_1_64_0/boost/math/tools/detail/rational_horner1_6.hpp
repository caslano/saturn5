//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_6_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_6_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_6.hpp
nbUkQjv4Cu+99rzPrJ+Od/LjyWYJNQFcaFd2E65t5fdZ3dNtdWJyFy60uLd+uH4z7jqmOT+5Oy/0s/gEcLv2HM/3uX/YC1xo3125+GZ0CribfajuyjLOuc98zvexLvIkl1Gdsq1+8J72WZ93uqryoooS+FK4hTH27R98bizBP2PalkWFfSua7gMneOdUxMi7dzHTi/TNSlKpViUV0xuFB2F/72W56Hw7+jItg3j7TVNhll5Gi++za5LfdGuSXUrV9Yyw3Bs354JmoO+/Zzou6UTKn3Dcx4Zc0omUi2e3bMglVTL6IyzncMDB0iHnISwf4fnp3CDlohw7Bl/+LBlXtNhmEH7IjMFDn7sJF6c653NJET5lgU+D7907sVtq3f3s9zVOpM24sf7MTk7erCs114ybF27KXSd73Acmb8alNpDPES7xvYN+3faGHGrP/DeCYy62PBenAL+pGuJ7jH0ht2O4tB7fD7hWh1eQ1g8OhNyOgf6FPxvEeomzNKqiW16L+ecSp7r8hodh+igMz5yDvGRdJZxX//edEuQ1O8xrOBtBZt5Zw91+ficLpfK4qDjTOZ0eWT9cJGWrmaiajFd18/+WDe5R5iaXnJ1maMf1632Ar59cIjh+CyYu+GVXVcFVKls2MxPE6jlKyl2wIi8q3Ye3WuwJ/wzutC03tW/EfdEkcvBqwbMlOKBxrBtNw/nzRg6mgfV/6n5//yHzpIqVTJg+eOoawPFuEF5V8zpqecN00Ca6T3na5zVMxFJmUca6w2q4NQeBUCeeu5/qRJupqI7qW3bwZf3bXe7S87PEyfZ93h74HnwvAEcultwbGCsBu+aZ2htyCQ99Wk9RXv8maV7bH3IJD+M9HgAeqcv6wF+P3x+M9Vg1silu+QDBn1fmYU4cM69MBHnFdVJWaXLLNnn+GDjT5RVdHWzRueWtGFfCcEL8PS4m0Rm4h8Cm1Lrr2aMcCHG4xug+O65ez3wmsOXkMqszcct2F/AN/pn+Bg9vxvtDr6fm9+v69+491PkLSrXnFkKfAh+BWAWdRQKwPH86ewHrbni3d3pr62hzAjZHAdZVC2Wf3O/w/tU1KnvvwQCzawA7T/ttMptFcVxJlXbjeGT8PhC0X1bGuUzkLbffOXseTdJrWdVoJcvzXeKYaTucs2fAelOfwZO4Y93e6U06BsuNeyFVM//r+RH+F3rgrQbb42PqnFhMWgXfdis7ibh1NjXxDoPtHcWMOKY/5XMgXmDHQHwfyb89v9DhmP9+It82wos/ffwzfsxUaEmNgX8uLQcaBZIQMtXGSwXsaR8TF53jvnd4e+6Pgj6iSxCje8jZmAw5oEeUMzVFOP1x6VzbF3AwHfR9td9y1joW2mfB+AYMfoVIG2F0VxwLj0wTHsA4x95OsLUNfY+pL10x5uodBIeB4mR/cKePQTuAJOZ78XCI9x32w1cTDPx+YJ6vIRjxRXj9tQSD6LEod4Rg4IQYbaReR7C+KSvafL0hxK9uA8PiD72R4Cb6LM4DL386sJEpUtXmt2zqQNZ29/r2iLpjfZxPUvzqJjCwPJdJeRpWi4zniRC3WiC7tnnMT69hvKiLtswq1h8sb4AvKTw9ntiw66brvsxslUJ8x4ZdWep/gd7B3fB5c5lIhCpj1lnd2Pl203J/7XNP5wlv20YUbHMLk92053svEm4ZxWVRR5KtBbYf0bu9Nv9Y16Zwo6VN4OB2fPHK1urVjR7xAbcHeNrNzWAFggGQPdyTUxqDb27SNinaFrgxe/++ELcfZWoftrCf8tCGBznsAHCgB0whwexivbNDQL0POd1QQz05FuhtUog0K9UtH2q6OwM/vZrlSamEbBmY5hIteYfX5h8=
*/