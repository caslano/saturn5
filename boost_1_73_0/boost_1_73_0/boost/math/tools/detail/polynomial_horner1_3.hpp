//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_3_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_3_HPP

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


}}}} // namespaces

#endif // include guard


/* polynomial_horner1_3.hpp
SmIrKkmDdWhoFmfRibRDwBQ1SYnglzE89o289q93JIlC3GvBpw8f7jd3q68eu84ybOj6nJ+7sG0f3BLlzpYRhMHxLuka2pa0aUQ17Cp/9tu29Qula58wUWYqx7xfj6PbJ1p/u9j/tXjK8ZBCn+lLNPz4o/wOUEsDBAoAAAAIAC1nSlLmot2lOgIAAGYEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTA1NVVUBQABtkgkYK1UUW+bMBB+P8n/4ZQqL9WoydaqK2LRqjZbomUNCyTVHj04ElQHI+O0yb+fjZtkWl/LA+Dju8/3fXcmNtSaXLQ0hLiqS2UfT7R/UbpohzDOsqS7YbLIoFRSqhepcmEqVcM3+22UpEtIs9kcYn5Ki7lngjM4w5T0M+mgrQqCWFMj9xZQCCM8PR9cDPBTeI2zHwzuhaEIsy19wPAGH9QzfgwHIQ4uo8ubKAzx+8+MgSeM0BUetN2Cl+KJsH1pc6laYnCnakO1CbJ9Qw64M3xtNpLB9LX4CEvTRJz3x7M0myRR34pJZvOMD8Krq1P+lOqVWUcYdqGacp/7uguzQr2QmL8K6xTfycole8V5t7AQX+kQ1sY0YHe3SYcQxrXY0PDoNJ7K1FRU2u6LRqGtERfzqYVz
*/