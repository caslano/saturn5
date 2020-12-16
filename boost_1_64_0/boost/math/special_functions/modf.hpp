//  Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_MODF_HPP
#define BOOST_MATH_MODF_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/special_functions/trunc.hpp>

namespace boost{ namespace math{

template <class T, class Policy>
inline T modf(const T& v, T* ipart, const Policy& pol)
{
   *ipart = trunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, T* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

template <class T, class Policy>
inline T modf(const T& v, int* ipart, const Policy& pol)
{
   *ipart = itrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, int* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

template <class T, class Policy>
inline T modf(const T& v, long* ipart, const Policy& pol)
{
   *ipart = ltrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, long* ipart)
{
   return modf(v, ipart, policies::policy<>());
}

#ifdef BOOST_HAS_LONG_LONG
template <class T, class Policy>
inline T modf(const T& v, boost::long_long_type* ipart, const Policy& pol)
{
   *ipart = lltrunc(v, pol);
   return v - *ipart;
}
template <class T>
inline T modf(const T& v, boost::long_long_type* ipart)
{
   return modf(v, ipart, policies::policy<>());
}
#endif

}} // namespaces

#endif // BOOST_MATH_MODF_HPP

/* modf.hpp
y4zD9m8znqa/n7xN/aA9s/5yx+3hIdpTxuf1K7bcqH+xcrDe3DjBJPWI9dgLvuv5oX+z3Pzw8Z+oL6PcD28GtKedh6POS4H7Y7DuKsrzcqXnV7R1wosc56Qh+iXDPFeHGWfQ7jYvOU9/YFu8/VXfxOvvN7g+9xlni9/qurOdkIn6P92eq782fhC0/vty9Znje0B/a7rvW2y5Tb2QYF7E83HFI7Z/qX7xIevbTllflq39v1H9/4L7Z13Q7wsZ7xjrufOLC7TrzvO8t7/fdJ19bH2fcf/HrZdZOML81zva6Y+b337fdWM92H7X60r3154/GBf/k/p2jXUt17lvRmtv6k8enWw8+kX16nbj9k/pj/ld1gVj1XMB9cBX9L+u1k74mfbI9SHOo+f8eOMc/zCvsU8/2vu1Rhp32vGxdRGLwh0X12OO95AlGk9/WDvSOv/kle7zC10nNZ5Pb7kvztd/C2jvX2teYDAO9ecQ4ybamxPDvI846P3J2iXLtZtdx3MmqC9m+e+Hhag3vJ/EeEGDeYj9lcaDl+pvjfCeLcd9Xannqf7VPv2S7Dnm8y7wHLpX/2Ca8ZF8z1PvP57xS+V4TmY/bV3mnx3PXvXBTO8Bsv1Q1+H0r2rPbdTuuufcn5/cOngPju8ZbXCelgzmue2n9lJInfOWa5zvHc+XKdqpxiWm/Mx8jf73/uWh5+Z1sC60Qv9iwLj+6z6fcatQ46bLtZM3T/ccXea4ek/g0lD9/Edc5736Eb4Hv8734EMn63cP7tviEP1G44ve07Z0wHV1qXmsvxoXDhivNA638Hbjufe4HjY5Xo+aj8jR//1Y//a6UOvbrWs54X77qXaFdc4Hjrt+e4znPe97Fdb5bfm3+1A92+/7XdneW/P4AvW6fl+49cgjhvheiPvv+YfVu+HGPY17pA5VL35DO8uf277Dc919ted86xqMK8a/5jmp/5sY1E/1vO7VL19+i3HhC6xLv9V8tn7GFu2oHSMj/N6A9/O5L0PHuh69LznkXvd9pvvYeqKVW623/ZI/f5Fx4ktCbN+6XP2hg/o1K282H6Q/Pv2//r7Q55ypn7zQfTzBPI9xzPhfaheo99ff7Hx/Ltzzwnt9v6z9c59xtl/43J+G+x0b/a7HbSfJuOcVEefW4WHj8MYNZ2TZzwbrXpZqPxknmnaV8T7XV+yfzvP75fo9a43bOt+7r9OOf919Ha5dq1/Zaxy5v8h1EGo//2q9muts882ur/fNZy3Sj9BPm/Ij40Grze94/2Lof7THLvf9ki+oV39kPeQF5hsbzK96z1i2+2//k8atPA/Hfhii3+x++oZ/v1H/Ilx9YL9Sr/Qeqrvcb496f6dx/8Mj9Ju2+v70DO1f61uWu772Pu0+dxymRZpPu1a7UznHx7uvLtP+f0O7tsd6FeOm257xuT/1779hHGmddsKPtU/8nvtR73fp3ab+Mf8X63oJGWdc6VHz45/XHh9nvPBrtlPh75UTr71x8q4Qz23rTn6hvXdUPzNH/26c9eDjgtZ7Gs/Trzp5Uj9mivrqReunj3oeDb53+oFxDONvoW9ZB/+J/u/D2uH+/Enzs/0jvW/8bu3vgP74e/qbfndhn3H93lLHWT298aT+sH5H6GDe7aTz6f5c/bT+jX506g3ao2M9Fz/yvLzWukf99PAK9ecS61i021foRybOdr1eZFw2RX3xoetC+3H4yz6X87RIO3xEu3ao5/PSYcbLYhzPA8aTmtSD1mX06n+OWOy46v+sne73RgbrLBrNe37Nc0f9dSAy1HNd/fWIdnC2/niL56X+71bttcXeP7UxJqA+dJ8vtr29rtM3jRct9/w4z/i79WF79ZPmPez8GXc=
*/