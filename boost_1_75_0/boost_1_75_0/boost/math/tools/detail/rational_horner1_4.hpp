//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_RAT_4_HPP
#define BOOST_MATH_TOOLS_POLY_RAT_4_HPP

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


}}}} // namespaces

#endif // include guard


/* rational_horner1_4.hpp
7N2pXE9uw+UC6ncq17QFpcp1mJVrPJAOAc7rSnFqK97KC+kVq1+ht2DV8zKEeVSGV++XVYZUXz7/4VtGHQ3/uNyyfJhRVlkmOEdMJoUqhcfDGzHsJmZ4tP7jn7IKs1nr6n/N139sLbcMP75SYX1sLFUfG93Vx8ZXPCnC3XtlFcHuo9TH9z7KGnLdQM5APDDh8S28QKkx4lUagpKoOVNGEF3ZmaDhKwF8X8Gu5Qma0FvyBI8+8xp1PI1QZ/VptxRmAYjituhg05HaZrGXrtAPBqWUWQA56JZA41DT8dNesjdYEumm9Q2TvcaT1PXiC+X7ibITdJASUJjF+0hJV+J9jJEfTFaGnZKJjhzekS8kpwNzySDTJspjdFCUrhRIZq+m19lyciUYkuIGpSw4oEO3dAUaLAiQDHUWUsPOaMr3acEMOOyXTv2lapB+WbqvRvGakuMh92elljszvdyna1c6XQ2cLkacEWiS8h0bSiRJmSyhNTcszWmyJBEvaFBVcSoAatMdLZ0poVo8/WiaRnV7UqZKXq/CdPGn3jChvN2bnRXo1HlzHHMi6SMcc0INHxLC+fvj+fIEosyE98JG2PWZ38GSBpIxFhiib5F95QZKe72K5Ekr5Ig7Nw36BvwOu9g0nQUfCuac9qwMqGB5HY4+K4PWH08IoQiCS4Ui+JS+vS95iG5YrHNO47pjQlYaDJP2vYgeiRGtVI500Z7p
*/