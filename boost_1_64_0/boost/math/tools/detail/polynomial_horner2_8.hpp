//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_8_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_8_HPP

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
   V x2 = x * x;
   return static_cast<V>((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>(((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   V x2 = x * x;
   return static_cast<V>((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_8.hpp
5s68+UaWrmYWKkK2HV+23Nhi1PadjaG/xdLUutuOSzexND/e+/mbWhr2rbd5f+5Wi1ErKtCCnecO+/T294y+5uOQX77N0/w2jGvmj83M0WKGb4YxsMerNGbyfd7D+HR2c0uHPMC+Fhrrt1u62oawZb4Fpskb1GjyfBdrJywOdtiaslr612/l0UF1Tjo7dlq6v4KwcprNGYsDGaowhr7Lp8vEHJ0nt7V0vAKxmInbIUxrvbDbI0xrvezbjTE+vXMHTFfNzerkjpjuNTe75r6Tj7PNbUqPWXsGYlomTc7Z6F0tn4qKaP3G9wJtwLUS983du/Xh/C5o3+26B2A3v95ixqd9fXi3eRnc4j37cbZ52Dq5ci/A+VMoG0fpN6/HcyiRJzyPEmoDeK2cWl89BdG15KVgc+e9uTfW6OwNOOZVXVYVZWFu+Ve7EArHiWEahDr+KOLNSVSVcUBz7vIurx9V7h2Tx8BTxI8VPY1kcJLmAcuTMDAy+mPambILxJuSjFNRp3lieSFMQ1/qJu0jrxhCaXMRcl6GBZHHITJd7Q1hYsShuKQub0VonKYc/DtkJnVQQNmqcXqLXlkZT+oIYpmpqHdXK+sLEG9MaFkKyjNKluWqXcV9ak6nVZi3nhcj7pxXz2EZ14wWEdERM8GPqMmACU5nYr19BvEGJMvyNAh4SFoDRlq+L3y+g/hoFsZ5VhU4RtwzDZ/JK6oXSuI04HlRZJLPqZaeo2HL+wXEGxJa52Ec8wp4rXobFZn2bHycvPZUVDxOo6KC1/B0nEjIuoruZQqs+X/l1RGrAqmoMiCrcnYDtQRBAZwS+HGiL7t5FyQpRRjzhBLTA3GAyLVQz9HeiOND8kLwSgQ5WX2q1dZYY8y9OJ02PsBeJCOTOk8yAXG/YCcJWgiEBJCSFo77ImwbI0qGqTcaR0VOayND/tMrWx2v0cQJRrwxSbIkLXPBgRcFd4VKaAZ8/LbgustPAyJ4WrGwyAk8drmyZCInTirj7c40/XJ0XonbXxpAKyo4ka+crUk8FGIF18UB866Wm4/9sayFqAwT0ltsQp1C/eO4sucV3tigmFFOWUlkUNSuVBUkZzb9vPiBlxBvQPKS5xmnicvbrOBV/zKxhl2+mlRZXrM8BranLq88Y1kda2B79yvMU5Z1KWqRaR6UkInB6bWHrCyCMi9yyWR70CTsBpo6MO1h+5u8OPRlHvG4pOQZaytgKZsmgKxBI2FB5/c+Ln9JeJ1mEasTxe7mtrOkeaYxTxqleRDnjIQV7Mmc6Eozp/O5pOsgQfkMSZpUrM6KjMyNLcxyKrz8rWndPBHxMRKXQSLKqtZ8uc/p2ON1L82axkGRlLHm3bByuR5CiImLjfgCwkReJFEi+VZmXc++DTbL93YvvYgJRpNMuUYs9eTaEpZ7hs/ELUZ8GeFJSVleW8Zm4rfRqWahT6k6NPExfd3WOY1iERG8taLLecLYYcSXNr6yQVLWBLky+ew23c6bcboikg03yBjx3fk2GM9ovl2IL5DlFXkSpiXB7oo6vTOmrb4Z98eARkURpooNpWXawLSXxzTPkyAJBfFdAxs+m1aB0ypoUIqkyoiJgQGLKs9ePNHlqUgZZyzKWa14UJlM/ha9/BUhi7M6hDqASWzTb8fgCEDlT/eL5yI+RlKeFDQvY5dPOfr39YuziJeSvOZBloal5rUBLLw4LB5fTEUQs7hw+brL/Xxf98qYFUkOZkbznTqGkrPvVnh8UVLmCaXc8pnkEN8Vjy+nYVHzJFN8oM2xRkEe35azWKc5D+q0DEm/xy+233sQX0zSIKzCKMtIq6sw5p1GvBHhKY+rImsSzVuTtWuaGcSbEhHmmSjiGvP6Kds=
*/