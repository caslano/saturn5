/* Boost interval/ext/integer.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP
#define BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>
#include <boost/numeric/interval/detail/test_input.hpp>

namespace boost {
namespace numeric {

template<class T, class Policies> inline
interval<T, Policies> operator+ (const interval<T, Policies>& x, int y)
{
  return x + static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator+ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) + y;
}

template<class T, class Policies> inline
interval<T, Policies> operator- (const interval<T, Policies>& x, int y)
{
  return x - static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator- (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) - y;
}

template<class T, class Policies> inline
interval<T, Policies> operator* (const interval<T, Policies>& x, int y)
{
  return x * static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator* (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) * y;
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (const interval<T, Policies>& x, int y)
{
  return x / static_cast<T>(y);
}

template<class T, class Policies> inline
interval<T, Policies> operator/ (int x, const interval<T, Policies>& y)
{
  return static_cast<T>(x) / y;
}

} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_INTERVAL_EXT_INTEGER_HPP

/* integer.hpp
gCLYTwwYkp3ELqWwk/Gk9BmCBXWX4ZTMrVifIthqDBl6k3Fo+e1zOTzexn/4PmJdKsHSW6+6K7ldvZX32Fdjm6fX34VvTAi+u944fX6PkSrcBnuEhD2cKr5WqYJKVnFd3n3Ek546aWGJZZfefq9iEdMWUsiEMOLnnfa/DT6CgcdRlau7e99d4myPYRTk47i7Y1pVXOOW7fmq+T6E3UcKQ4V8DjnqxOE3t/sGonFr/e1b1Y2Z+NdI1axsnoIzSokIMSzVjZL69TRK2m0bOM4dd+90xaDbylWvsyGctNZwXYNcKtUcTBLj5tsJ39sFY9Y4Pf61eyVflla4VN7bYFyHf3kLa4Pm2Tk/7ObL/rgeqpaGl1gEu01sLjp5+K9F8C82o/zOweTZGfvZw/nykjtVFjFnoffwJQ4GhN76DA9j19m8PsWiUUX+nENlZ52DmFUWs7AFgN3Pf0Ir54v/hGZayDHBqOd8drGlhTT0bKW6qxFppwp+EUPhlspVg9HgJ6/s7hqm12XSx0icoZ1M0++0e7acE2TiffNZobr39jg97n1xv3fKXULbHRA8U1XIM0SaGxAhm7I4kViBy3mnPby4h7wnB81pwYXneoW+hHD0HkPieplXDAVqMVvdmZZFOln4V7qrnU0EXhblqxgJU110o5ShDpZTNEN/K1xhJwP5CwFXxa5HPjsCwx6tyde3+5debHqeapNGCkn5vZy87juDsnWvc4hWw6uYLYwYjZxgpHY/ZRy/DXcfrMho/ifmRWXXaslvyd++/O1LSym1pq0UeyNzPfjPtM3/GmR7E1Xw7zXIGn1XR4O7F4ZzwRpp4T0qiycXWybEsBW5sL8KWDiXH9x9py4OG9BfTW24Rm4RNzeopsA4uhCvtTGq8KuKeN2EC+8njs9XVP+fA4Atg89PgrQT4TWe+j34mSi4mgyf6r/y02kptXFwPX3w+dwESsXwOQ5eqXuVWiT4/8x98DqDtxk8fp9Sm4+n1Hy4niTAF7tYqcmAerh6TKljCDz5rFIz4mLqHnydxcbw1EtKvTE+sB68tFAP/22l9g/+H+9XfuBNXGT+Uv7pArz5oVJz4/6P9LRf7SJcB/dvjOphFP789f5N4AsQ7T8KfJ7g/1P3wRNf0XgKOJqr2z4hPmmX/7VS+wXYBH3wFvAZgv+H/J77d4BXLbRdiP+F/61SV1vR+Xe+V+pa4NNH5K9+VGon3Td49cFrwA/U3P544ic9/SPL1wR+gOb3x1M/K/USKjsQUb4EBMxdAXfqv+Ja3FjqKM3tj7eAX0n0T8O2VN27T0T+mZilTkT7LfuX+0/Xxce11FTB/8fp03814BvjjyUj7t+c0FKzUP0PvEqUrzaRpabHxXwReGNySz2vx35E/0Be70v1zxSWupNov4EpLbJ/O8APC7Bx+uD1qSzdlios/1/mL4O3gc8U3X4oOM1PAC9oLKJ/gE9B9G8buEPULzUNnb/L4HUGb05D17/D4PFp6fsnGTzF4C7wUUJ+NKaztCkxScT4cae31Hr6uj/eBn4wUb/aDBbkczSemtFS1/eRf9N16z+TpQYJvAn8IqJ8tZktmEnR8yMxK/rHiq5/fTZLvRjI93gf/duZ3VJnUeWbw1Jng5+I0h9zWWrB6P6D8kX7a/0R0X/zWGoHIv/EvJbau7f//5o/8LkJ/ToKfBQXqQj7ILGIpZYj5q8LfCsC7wA/ksDri1pqdQIfBT6/vu6PJ5OWWlVfR8g/4AcSeHIxSy1N3L8GfDMrWv8ll7DU/VT5lrTUalo/9OfXgd9K6bel0L4h1qd9gG+n+6//+HBXsNS1WJcuFDW/V/b198xR+msVS2EIq+3D+v1lfKxqqXOo/ls=
*/