//  Copyright (c) 2009 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_ICONV_HPP
#define BOOST_MATH_ICONV_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/round.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace math { namespace detail{

template <class T, class Policy>
inline int iconv_imp(T v, Policy const&, boost::true_type const&)
{
   return static_cast<int>(v);
}

template <class T, class Policy>
inline int iconv_imp(T v, Policy const& pol, boost::false_type const&)
{
   BOOST_MATH_STD_USING
   return iround(v, pol);
}

template <class T, class Policy>
inline int iconv(T v, Policy const& pol)
{
   typedef typename boost::is_convertible<T, int>::type tag_type;
   return iconv_imp(v, pol, tag_type());
}


}}} // namespaces

#endif // BOOST_MATH_ICONV_HPP


/* iconv.hpp
AkBb8rt8p4W4JYDPVsCfK6h1NGLjX3EJolMbqPbXwiUNuhzpzL8r6SKYV8Eo4/sLlwa6+doZaWDWK/e5TAHO0He/KMTY+u78ZQtxoFEAw+8j25hMJ1LdPnh5wNhzAqWxdQWLjilw+6xeUWCMCC2pX3CPcSUf79PdYW/G9yG2tD0FX7y4BVtySqiEQ9g7alg4r+1B1KUnt98s7AEVe49KJOLz4AUQvEfA2At4iKNgYac8raciuq43oS1P2l9w1XTvJjYr4xLsgfS7xv6Cr+IOiiuZwIHWyPLHwlKar1pW8geFkMYlr1Z2ad9yBXFRS48VqMIjMRBtUpWLZfjTmB7BIuOlYAO8FXtpF+8OpEvuL5H7CbZaRhxGE7ZpPLF7cHdK9QGjoX7P2NpUvdyqHOd7uS1jjx4ObjSTcun/1GvedTK9hjJDIiN11U1Ab8zkd+xKWAI+vD3Lzpsh/b1MR2q2xr450ORXxU7/E/y5oqNep8K0U5dQaFJfMA0yYJrUFbxW6yLNDphmfbN7GcZwMDanca3/kHatMXpuU/hrO7232kNVVVVRFMWcdupMKd77997f18ygKGM6M9VhOjPm+3pUUlEiVFQiQlxS0oiIRIlIEyci+NHQHy6HCJX4UeLHSTRBIuGHH9be33rX2pf3Gy1kor71rL3X3u++r9tmpBuG0ygDzlvCoOTMf3or0+CU3SrDyHYNY8lwaodOZxn4PHFlJ2MW+vz7ff5d9A79Xj9N/D4H64SkUVsWd2m/J4FSx9XdggbmiQbP3CP4O/HweuQ8HWhrrGn3Lbq9pt19BmKweFmAQr+yR6fj0kv088/U6VgBnbnqvYIuBzcYX65yjv19/DusqHTm+PEbcQ1tPAY6naJs3twm9DNFXsYFvLpFDzn3eK29M6KstVUCT36gb3OUjEmdN+wfzFOUi8XCcUjvNtvxrmY4SBDmx+sEptWJgs6a79qAGKqEz32Ha93GUZgP5HnowDEbFMOLC4rOa/GVzf5Qa7k1crD792F9ht5RGbgOR6+jLoMycoN4UAcsh7BZWHXUWh1RmORVWqeiDpWB9axnat0uwavDtO6moDSe78OBXYQGNasj+foqr3CZi2PQBYbOUs+qrkO6N5WnhiEThJ4P6/bkGx4tkiLkRFnoR9C06wtau0BEsPEAa43ehYUL84LFtB36Wm3YDlTdsqq7Plc0vwTjUFPWUR43lbeELonSMC/qQWXIZvL8TO+LIszyNM5dB540zTYtURxhleexpCr8wK1jB3wbqEVU/lN6+WUhnvBhy3SXQPVco1kMlt/s8f+qtZjSXgrtAHXlDLBoZf/bKDusoYPgkFPJdCPn5xdX6EMuNd9jxxt1378i9sMU7IfE25bCQePsAOJJd5oLQ4jEc6YWLogx1p+5sGJ0FMk3pvJWTuGCY0cCavi++PaCURkAZaM3VXl8+IhZ4pZe9dD6LRHb793PEvNK3FUuQXVLc3C5lL8vwO//uiJ/X+kLLTrGS1gW+Inq9FunKaAb36rxXf59gLHcX/Cd+r0NPzo7qOv/UzJnBXzL6bO9+RlQUU4vLczpdwqgmwbhvDbe2GTRZ4XJ48UVLuPwZgsDW/Eo64Xb6RgtsUO461vacT0JZJyztQ03fRaXXMLd3DYMJ0sk3MqOVtws2FdgnAFs585WHFTKdd5ux4D+safd5c4/jXFsUK+8te+WdH5jnnkv1MPnqnc93aDPzjDvMwyaNNGYo3Z8YY9BRzM5te++8SzCiG9ArjC4sdFb9NV9Km7guzI3PydxF3sz71a/28qzNSwZXQxSzHA/1/tVnFYUtXH0ORpGWOiAfQ7XteOARpc2N4xS9COM6xFOyKPIffW5jLE=
*/