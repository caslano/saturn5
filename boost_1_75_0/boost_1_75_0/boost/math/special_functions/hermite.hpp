
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_HERMITE_HPP
#define BOOST_MATH_SPECIAL_HERMITE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/policies/error_handling.hpp>

namespace boost{
namespace math{

// Recurrence relation for Hermite polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type 
   hermite_next(unsigned n, T1 x, T2 Hn, T3 Hnm1)
{
   return (2 * x * Hn - 2 * n * Hnm1);
}

namespace detail{

// Implement Hermite polynomials via recurrence:
template <class T>
T hermite_imp(unsigned n, T x)
{
   T p0 = 1;
   T p1 = 2 * x;

   if(n == 0)
      return p0;

   unsigned c = 1;

   while(c < n)
   {
      std::swap(p0, p1);
      p1 = hermite_next(c, x, p0, p1);
      ++c;
   }
   return p1;
}

} // namespace detail

template <class T, class Policy>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x, const Policy&)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::hermite_imp(n, static_cast<value_type>(x)), "boost::math::hermite<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type 
   hermite(unsigned n, T x)
{
   return boost::math::hermite(n, x, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_HERMITE_HPP




/* hermite.hpp
6Qk+zNIFr5f6eAasWl7zg65NyHo9mqM8thdP5aC+Ovl2jKAx6uLONNiDvlfgIQEmn6fwwDB8+bUUoHCExerm3+J3ql6Ic24bVmfXuVao3ROrjD4/9KiJfOtlVpXiaDul+O7ArWr+sbOwB8uxprZq/hoD15H8l9G6XOrSjnIdmr8AlfEb3pMG/oJFe9Arw6pEjR8J56ctNTqvq4K0MFfd202nq51X5PTZ7Tk0OysRb/1PWlT5BvQU58ywvS7DbrV9n09gfNW6P+GTqEadLeuI1fKTift5n+lBU/yzdhyeRgLnMCMJ1v08ye91d9doUL34rNRGh+LVmOXsFscVW0TN/K802yb1tGuEle2+Qae7pg2EqX5ZY5Ri/GWWaiVYtY4mf7XoaTNUmCFtUjfELbVcog4H86C9t/1W3+bhec959Lp3Wr/qvB7Z6UirRetgMyCk3K9lW4QUmucav61qKOK74L4ue/qHuOpr09sH7Pk2L3IWkImhp2IvJHW5ZSOgbXGQMas5AGYTcDcdq1dnL5k8etk60X4T+YTHwwJJgR2w3qQ+VKpHmTn6WNpr9QgbJ9dJ93zmIi7gwBUTwiVfWNwrDC3bFhpDM5yD1pZIvG1TgPrLI7SLQCngXss5Rz5meLfZXuIUhZZhj3gvDYhr9L7qiM11Y9Oep2PSw3XtxqHqRHxI9WP5z78Git5eo8yfShmIoopof1eh7M9xSL8V
*/