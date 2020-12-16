//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_10_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_10_HPP

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
   return static_cast<V>((((a[4] * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 6>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((a[5] * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 7>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((a[6] * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 8>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((a[7] * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 9>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((((((((a[8] * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 10>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((((((((a[9] * x + a[8]) * x + a[7]) * x + a[6]) * x + a[5]) * x + a[4]) * x + a[3]) * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_10.hpp
ammER3wLZtHB9ZhXZ9u7xBNBp5sc34N/B5ClQgcjrUKpybZ193Yve90T4ZTRJE9f+Ry5beva/cspkOfM2uQoRTdH+XqH0Ms/wKzyQcWIzo/vnb7vyuCf9VEga5iJ0qmIbmZtV7IfB21quLQBK52b6fBodSfzyV7Wo+KKkqUZOih5FLMF21LV2uizEEM5TyV5DOJbMNUPDNimOCraZC26vd8e0oC+9hUgL1OwRjKZ5SOUX8bpN3r5K9YrQxJTiNHhPvXbvRzBWWFshcUK5Q/FHCi0JEY8Oa49+dJu9UkB9ndWa4kjn1HzvXadC4CsEkwIk+3Petml3t+9eql/f6CJFEmh5hZCljkD1NsgwlhQjOHcG8vl/AG8bC9BLlsbkGWs/wKW4XE0uniz31zK2MFzGXN6uHU7XuvL2OU0j+jy4mL/KD/uax+5zacC9fKv9koRzhRGxadwtzplZvll/XdZHvgOsShsSLZ4W775cHJG5NOJTz2ga+va3R7rEbFYW8ld3sJNp7cf+GDbiJ8s/eEDgI8izTXRlmS73p86Wvn+w9PXHGyPTwCcQ9ELHYnLttzgNlflZ/fmaLNdES2G3BdAGRglLoQKon0HlsOt0iLncA77ao+7prEPibiIui+4S8f1e2rUzzhPiWLo9CQfzX+Q5s3oxVnulheDfj8AOItY8MRJj0rIxPflREepwPP6DQuAMfIe+kvIXVYLE5JHm4v6zkBwD/hcgONIc0qFoKqSY5q7J7zsr/2zxzqUOyjDktq8kc7p6/D76hQoZnkGuBJi3OY1kDeucAIz301llC09XOuOIK8jPvcIalA+lM0Ozm/ZvbH7QPWTqz7AEKNwtFIlgXC4qW/sZMy1NebjPcYjJ105fS+L3eQu04fUviCLzwTQ0SCV7ektDagcM+zlgZ+n7IvDcob8/hNYRPtG/vIv4f6PR2K133yXH+xvLnpaGLo2/r8NdRS5HbUgalPfV+1eyWcG0Od2sElUKcjAm/wVKP9LKC+V5FEZ0eQHP7JLvwLyWViVhLAb+StXd8f6PBHKSyEsc8E2+aE+L4TyynOCrXFNfqjPK6G8MYLrENMsv/PAUp/qD5TlwfpVHqnHPKY2/si77z8sDn83FR78Wm/1uFeTZLFNxqL8adMCDtYzd8DBkGKcS+oI8of7ZyfnJ+/Ks9v0TVShbQ7+wK/gHExDNkAkCPOb+ZHulev58RMl8zu1+r0OMT6GpG3xBTo4nzEH++8cMNe/+WAYO05KwrnreCihA+ZTkCcxGXT0uuPZf+f+gPkcxChnKaMydjxRjPp8CWKssiYP0tDxnLxr1OdrEMOIyv0gyF6fFc93ISYGlYgSotdnxfNDiHGEa6lUmHl2r2xrnz9CTB6OLIUUC8+MWbfPh2H7aJ+sZEE1ni3t88hfAx6BU8k6yxvPlvZ5JsQEzSIXiTaeLe3zcojhTISkSKNpzdP1N4gxNOpkue31WfGogSdGJrE3jWhL+7wFYiRLkuvkNzx5PtjWPnchxqVUbuhS4Zkx6/b5CmwfETnnXsjGs6V9PgB5NOVlbhaNZ0v7fAxirMbSKtZoWvN043RoU6ldwgk3ntZAbZwOtsYi18y7Xp/1OB3a1Ityl6wbT9c+r1nG6a+Hc0LLkysH1Hezf4Eue6H70x1sTsRY32y+blnbAFYip0hiHgekMjZvGBs6z68N387iBm6bK5tUMiN3PkFd3cM+9TeQO/cirYK027g7PKp3bgBvEQ/cKuXJSu+9o6M5nzrYZyWAD0gbG5IWdBt/KSP/1VwKjM95MehBGMZUGz7W4w0H0y4c3ukCrC4+FuXci22rw4yH7556/LVkogtMMlSTaGSRs5ctfauXvUo=
*/