//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_RAT_EVAL_6_HPP
#define BOOST_MATH_TOOLS_RAT_EVAL_6_HPP

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
      V t[4];
      t[0] = a[4] * x2 + a[2];
      t[1] = a[3] * x2 + a[1];
      t[2] = b[4] * x2 + b[2];
      t[3] = b[3] * x2 + b[1];
      t[0] *= x2;
      t[2] *= x2;
      t[0] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[0]);
      t[1] *= x;
      t[3] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[2] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[2] += static_cast<V>(b[4]);
      t[1] *= z;
      t[3] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}

template <class T, class U, class V>
inline V evaluate_rational_c_imp(const T* a, const U* b, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   if(x <= 1)
   {
      V x2 = x * x;
      V t[4];
      t[0] = a[5] * x2 + a[3];
      t[1] = a[4] * x2 + a[2];
      t[2] = b[5] * x2 + b[3];
      t[3] = b[4] * x2 + b[2];
      t[0] *= x2;
      t[1] *= x2;
      t[2] *= x2;
      t[3] *= x2;
      t[0] += static_cast<V>(a[1]);
      t[1] += static_cast<V>(a[0]);
      t[2] += static_cast<V>(b[1]);
      t[3] += static_cast<V>(b[0]);
      t[0] *= x;
      t[2] *= x;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
   else
   {
      V z = 1 / x;
      V z2 = 1 / (x * x);
      V t[4];
      t[0] = a[0] * z2 + a[2];
      t[1] = a[1] * z2 + a[3];
      t[2] = b[0] * z2 + b[2];
      t[3] = b[1] * z2 + b[3];
      t[0] *= z2;
      t[1] *= z2;
      t[2] *= z2;
      t[3] *= z2;
      t[0] += static_cast<V>(a[4]);
      t[1] += static_cast<V>(a[5]);
      t[2] += static_cast<V>(b[4]);
      t[3] += static_cast<V>(b[5]);
      t[0] *= z;
      t[2] *= z;
      return (t[0] + t[1]) / (t[2] + t[3]);
   }
}


}}}} // namespaces

#endif // include guard


/* rational_horner3_6.hpp
TUJfImsh7EvTa/x/++F0HeDF9uTU7NbI2Sg9r9P2Zp19AsbKKB7vd8k6/PSZ16sc7aMeCvu659UH9M8xPniX/w5ZjZ8az0XsMXSNZ2Hz6zaAv7OZ4KO+8WHr4qpwEnmZ5qPmKrYh1Qq8QDmy88LOhrpdsOk+ykfs78OszveRz5k+6l9if4/WF96DvMwj82arNHHkTPSXRT6qv4WtzF+jamJ/i/l4dttwPFNLUjeXiblNLNDEgsiWeLF9urWxFtrvBx/l8mbrWzF6L/rLj7RNH7acG0/yfH61j+opLP/jMbcQ+3ofddPC1uzs2n3I5yYfNVWxlYr7YzrystlHFRCWJTK4NeIjqyNska1dAsYmWX1tt8gOrqmSFXUhW+PF1jGuy2XkZZuPyqnYQhJrN0N8ZOu82RI6VK+Peu6ivFjYPq4e1QPx7aZzuLBzJU77oW336jmDti69h/bDWCFbLMq5k6/Ugu33UROFbXo0chxiP+ijNiu2HE3PHEYMh3xUX203yZ68bn8JMRym6wAvtq9L4ubgHHDER91XbHtyDU6P4+dROqda2HyezFoMO+6jdgqrmM79Hvs7qc+N2uy9a/P4I9smzPXJdQR9/pQ+fmq7k+FjH8RHhm0azrfxp7htb5Bd2DpmJY5nZBQ77HHZhzH8DYBnufOZGzXEMYssk7Dn19fydYCh3Jtx09ai3c95lru6PYLfFyYbbWEb2yLfQJS74KOuCOs1u0cXjM1EPd61yX8+R5GV1XadbEJglWDkhayQsIOr/AIQA1lFYbnPnuN795d0O2ibPCofjgUxZJFebEWb7TuBfF7R5w5tC3oueoNtXtXnP20VT7+9ij5/le9P/Iusbb0nPK+7RvfBFFvurkM7og+SDRPlPiYpf34HmfKp2NKO6rkbbXuD++41svb/dvH70Ld0/9TWZerie9jfbR8VI8rFvO2dgv3dpWsS/Wzpd7IBn14sRc6SfdRWvc0rZMtaTkFfCqcbsSeE3Qt8sgD2zEd1FVZvXufuaD+y7sJW3Hdxf3nuo04L6xRUbyrshQ++57pM9n3JRkf4fUwftU+xZbqxvD7Kpeh7jtoy1rnbBm372kdtEpb+7bRc/O4kz91+M9xPDiHrrO0SmWPneB/kmuyqsAqTI7fxu5M+6oOwEHf8Hn4H0keVEHa+SDV+p4asvLDg+MhktB9ZB2G7F+UojW2+o/vJwnaV7cjPp8lyaEskCyyX6Q/0a7L9DrZzud9/h7FisaoOvmwzUrqhLsrPmuo23WT7xDYvXFnBx55cVlz/XSQrE7YU55UgsgBtF8had/2QHzGYWIKJqdxs5w0WRFZI2zmySy2zRqOfkeXSdpZs09bR85AzE0skayzsQZqKD9AH81jxrsoZsjT976Bfh5P56T5/2uK5xoTKZ8UaE6csnmtMpJD9fx2JkxbPdSRc39A2hb2pt5ef/5WwqjTCCs6ufAt5KWPFOhInLJ7rSMSWs6rTfv/Yr2QH/t7A1zKNrCqTjuE4WUK1dxbks6lV7fdmaz+k/hT0l5ZWnDuOkWUtwesnB5JlgXm+XxBClkfbUbLPM4euQH8hKy3s04kwfn+CLL2woDR3N2DcktUTdmDzVyfy0kr3F21XXp4IR3xk2YVN+eXXC8gZ2VhhM7OtWYX4WluV1cL2tknwYsTQxqqKKLZ2Qz8G4lhAFqztCNncMBcfz9pa1SRh1UdUu4jYycKEzXwcXw7xtbMqO8zzfnIIWQNha698/wx1IbsorFOGHvxfjPZW1d3C1vRiaEte/8WqfpN1KeWPGGI76Vxru1rzBM97yDoIm9bvlhX5DOW+lGC87iDLI6xXgTH8r0WTcjFkbYXVe1d7AsafSTk=
*/