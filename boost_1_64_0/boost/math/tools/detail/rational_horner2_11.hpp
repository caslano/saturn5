//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_11_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_11_HPP

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

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 5>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((a[4] * x2 + a[2]) * x2 + a[0] + (a[3] * x2 + a[1]) * x) / ((b[4] * x2 + b[2]) * x2 + b[0] + (b[3] * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((a[0] * z2 + a[2]) * z2 + a[4] + (a[1] * z2 + a[3]) * z) / ((b[0] * z2 + b[2]) * z2 + b[4] + (b[1] * z2 + b[3]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[5] * x2 + a[3]) * x2 + a[1]) * x + (a[4] * x2 + a[2]) * x2 + a[0]) / (((b[5] * x2 + b[3]) * x2 + b[1]) * x + (b[4] * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z + (a[1] * z2 + a[3]) * z2 + a[5]) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z + (b[1] * z2 + b[3]) * z2 + b[5]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((a[5] * x2 + a[3]) * x2 + a[1]) * x) / (((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((b[5] * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6] + ((a[1] * z2 + a[3]) * z2 + a[5]) * z) / (((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6] + ((b[1] * z2 + b[3]) * z2 + b[5]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + ((a[6] * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / ((((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + ((b[6] * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z + ((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z + ((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>(((((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + (((a[7] * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / ((((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + (((b[7] * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>(((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8] + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z) / ((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8] + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x + (((a[8] * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0]) / (((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x + (((b[8] * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0]));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z + (((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z + (((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]));
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 11>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      return static_cast<V>((((((a[10] * x2 + a[8]) * x2 + a[6]) * x2 + a[4]) * x2 + a[2]) * x2 + a[0] + ((((a[9] * x2 + a[7]) * x2 + a[5]) * x2 + a[3]) * x2 + a[1]) * x) / (((((b[10] * x2 + b[8]) * x2 + b[6]) * x2 + b[4]) * x2 + b[2]) * x2 + b[0] + ((((b[9] * x2 + b[7]) * x2 + b[5]) * x2 + b[3]) * x2 + b[1]) * x));
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      return static_cast<V>((((((a[0] * z2 + a[2]) * z2 + a[4]) * z2 + a[6]) * z2 + a[8]) * z2 + a[10] + ((((a[1] * z2 + a[3]) * z2 + a[5]) * z2 + a[7]) * z2 + a[9]) * z) / (((((b[0] * z2 + b[2]) * z2 + b[4]) * z2 + b[6]) * z2 + b[8]) * z2 + b[10] + ((((b[1] * z2 + b[3]) * z2 + b[5]) * z2 + b[7]) * z2 + b[9]) * z));
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner2_11.hpp
Mic6lFRJlMZVZJywQP79kb3jtaDuFc+jqFBSC+2AHui7IIhZAkFLlnYuueeNq7H9hgT1VzKLYpFxtq7X7peWNrpQkXbQrm3t6BYYOTd7mofvkLlMy6LANMxANHaV7kyDB3auIm+SgntyK5e1xuim2jFKg+8UX+Jk3NS8zvNYlSgalNXZSwp6/yFFlEVtjXKXe/ZgkNk2PiKofuZ6dEe1jFBo/Yrf0eGeZUYE64445W2USitPNRvtpzmRy1lZt3nJhZfvpv6/7o5nrrvT6+Sx3A8E8nA718qMyPdBD+fIGpS5szVB372IpMx4VKE43GaaeAfubE3QPk1krire5lTILy/q0Y8EvYOoszjKeWpF6QD2/HxcD/qnKJJWlVHtCXYe++FvS5tfHhm/z4nAF0LStDmvk1C+r/8C09CgB2PKHCd569n/BP1cxFnWqtQrx/ZweWDOYdw5cErbrKxlXTcxtlnXP71VLD3OfccD2TSWkYjLzJNdv4L6QfSLpbTdeFxEos4alP1Kb0fPHOYdum23K7FdT6fBXVVbNCpVBTPqbGY8HXBmfT0YkIPU6hhJo9JtprKmyRWmgZNXl4b+O35HMd7SD1M6B9eRSluuUmajI88tw/C0MxlMajCzr9kC2TrdCOrEszJq2zLCdHARg2sJOse8kNJzbxXzJoklJqE/0uvB2vClNDjXyNMkkapAIXg3ar7mwVw4nQVnSnFVNqqKPVn9VkB/RXbot2OGyEkmVJxVUZShnBlw+NqAfDurLDi3zIWMpVQob3aZc9s2Aks/vMPayIK75SRJM57mXho9kB7gkrZv8/9GRnWn5brXZVpaWexu8E5GBgHG6SJpKNZUVVZlhdcGVzf1BLvTX9oY2+u2Hs9kwbwHboryhHvpDNbm/dNEjC/9Ykb0RURFUQtRW1FSbivzckb9hRRp0rZSMr00Hey2h5jKg3kSbpbjJmZD1drEoU70bGDreDQP9t1VW9a8qIw82X6Ec/RskHeTlYWo48jI7rJ/QTsJ9V/2rjw6yqSIf0wCBAibhEXEFVdURFwBkxAwKi5z35dJOFR0nGQmZCTJjDMTCIq66qqoqKiroqKi4r36vO/b9Xi6KvpWn8c+XXXVfboqKs9zPaq6q7u6v8xw+Jz5i7xlCV2/ru6ur7q7uru6OmrHVEn4/IFUxKtsou3grKx9pfT8F7XXu5l42BeOp6Ocq1aEBheElTRe1GWq/Mdd+dG5JRuLZL0zShVwfGMFccvrnVFXn44n4n5/Kq3yqzUBGw3cLz4ftfUpFg9EUwmou5qyad3HCsV5f+DKm0qH4Cfr986WZ4WBYxlWdt5zrm+cigT8fvQI5qG8qR3YGXPtj/kziWAoFsa8OIaU5w6AGc27wX61drLyxbzBcCyKFrwXNVKY3NBGrHO5NGEPgbzmjMZcY1E8GUyGkiHkweG50BItHJFRYVV4EdbRqZjLryaQjPjTSTcLV6wUzn9jzP0GezAYSiajyAA13N293PlPWfnDUH40kwz74140mZovYtkOcskxEUhl4wGfV43izT6hyn+bq/6RTDqZTEYS3nKB+8j28qRUH17H+dXeo10+5I/FUvGEz2t1M3tKd3/HrrgrRlrYn45G00ng8dQ5mIaKDddjNo9NLh6ZWDIayKRSzGPhUsz97mI0btsTsXAo5E9FQgYPWuKiFV0s1AS7yRL1Rd53idt3m2PBUCqb8damYB2OWxmzRfsbHI27xpxkNpnCh9OE/jQ1BkrafyhufwNoesKX9spDAOxG1k6Aajj7en3Yyu/DvbdYJulLkIep+nZl95nY1+Kuvbd4JpCJJqJ2Ptlst96vS7j2rGPRUMwXz3jRdG2utiUl42E=
*/