//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_2_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_2_HPP

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


/* rational_horner3_2.hpp
b4l9+PEXYu8WsEkS6zSzA83XsdKcmblgc76MLUo+lOW2cSOy+d16n6L0ynFb2UR20dJ9CsVEec6qMsFuruw1k3wHtk9i0xptW06sgvC9qlaXCiL/qgCLz+9ShnyoyJmLYKp1CxOwfIKp1i3cVc+p1xHMKqZuc/w0bLXbntOkNTCzxF6MSXSj/hKwQhKbfb1tBGkGrKBgqjWUtZrnPvgyR6z/adh095qFSU8N+3Xc+3dIT2DNJZZysJDov7hzFm6QtK5WOJXalSqcBXLBNjcYeZZYdc7qM8GqXzpXjmwBdkZihaqs+4JsqcFt61zIdvR6ScyvJmdREkusPY/anExgCRIbvGNgcSrTtTi7rAjW7+Xh9fSch4izKto402E5HiIG37WuLTVaSOXI5IkxgSxwTf+dFGcqpo5PM7B8gqni00/1nDo+/T2xbCJbNW2AP8WSJ+Y7Mo+ff35OsQTMGVllbb8cmJNg6jpL57ksT4xdZAWr3/qVNNN5J/PK/Z0mL/U7e3pucSI9dZ4ze+Wenp/Oc/6a9H4u9Lw2tWM6z1l00kvWeS5Nk57bwNUulH8671yr884MzTvfuZH2G+WfzjuzdN6Zo3nn6ugYWotkdXJ/p6lO7u90r6N+Z73OtRtS/gFzFUw17vDXeWcQsCKCqcYdyTrPpemwdB3/1uo8l6HxL65pvXqUD3V08kHnnTmad/62qh3NGTNz7pq5m3XKijl3zfzNOlrrMIsOSzbn7nuaznPpZrXvS3782JXyQee5DB1dsnR8Z946ce2tE9feajtjXnRWSGudd/p569RLmncudv76CeWDzjst3jr5oHnnlLFXq1E+6LwzXeedazXvrDmrRyHKB2+dfPDWiXnv3PPI5JP7O80+ub/Tzyf3dwb5iHFVZe18gQ5L12EZOixLh7G6uTN3Heanw4J0WLIOS9dhGTosS4cxXx3/dJifDgvSYck6LF2HZeiwLB3G6nFWUjDV/JK7DvPTYUE6LFmHpeuwDB2WpcNYfR3/dJifDgvSYck6LF2HZeiwLB3GGuj4p8P8dFiQDkvWYenAMpBVsq77/hK3nerrhpx9LbF2SuUC1AY04rZ1UWTNr/wSS74DayIx3nMhzSuaG3M2RGJLOi33o3oeWLLEds/3Cqa2qglnxSTmkbMlhWwBVkNiruMrnKR3NsE6GZnT3W3iXEgT1AVZ8e4lylH70ETU8+6aep41zZ2ZgDWU2AdL/nxEedQU2xVk716p1oPySMOwzcF996gnsk+bTl9IdjYV/rlr27FmnCVKbNCt5zVJF2D1JBb5KnYW+ddc1D3u2vpTh/k1F3q6a+NThyUDK4GsIrDac1wPku86LKM5zgkgGzU21YV8h4XdvhJ71XX9OEoPWJjEZh9LDiLf/XCOBZnpD/Nz8g+Yj8SqPmtDeiYDcxZMPQ7QYenAWiKrACzfxaq/ki0t0RZkpQ65DyBbgFVCVt46Dx2T1IrKA7AKEtt3aeNvlF5LnGdAtvHuWnHeEFhPid03HDJTuW3FWWFFsJohBS6R7625bW0C2eKlJ09QGWutttP7QWcL+ddGbeen9bzFOY02kJ7Ept3Y8Tn5DqyZxLYtGHCetAb2riLYjyMX9Kf03sN4QbZ7n6sY/wFzFkw9JtFhFh2WrMPSdFi6DlurwzJ0WOZ7Yn63nHUebMM+iomc97AOQVZl3nhXKkftOFsisStFO1OcZQK7LrG5mz+uRO9sz1kpif06eDXtlTZ1EHaW045zdJgZWF2J9e/QdAnlQwfRHpW1nsf7su80ao+AzZfY83lNu5HWHUW9W0a7/t4R4xPZnDrVBpJ/Osy9E/qATOVDJ9QamWpcDKyMYKq61QKspGCq+jM=
*/