//  Copyright (c) 2011 John Maddock
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_JN_SERIES_HPP
#define BOOST_MATH_BESSEL_JN_SERIES_HPP

#ifdef _MSC_VER
#pragma once
#endif

namespace boost { namespace math { namespace detail{

template <class T, class Policy>
struct bessel_j_small_z_series_term
{
   typedef T result_type;

   bessel_j_small_z_series_term(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};
//
// Series evaluation for BesselJ(v, z) as z -> 0.
// See http://functions.wolfram.com/Bessel-TypeFunctions/BesselJ/06/01/04/01/01/0003/
// Converges rapidly for all z << v.
//
template <class T, class Policy>
inline T bessel_j_small_z_series(T v, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   T prefix;
   if(v < max_factorial<T>::value)
   {
      prefix = pow(x / 2, v) / boost::math::tgamma(v+1, pol);
   }
   else
   {
      prefix = v * log(x / 2) - boost::math::lgamma(v+1, pol);
      prefix = exp(prefix);
   }
   if(0 == prefix)
      return prefix;

   bessel_j_small_z_series_term<T, Policy> s(v, x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   policies::check_series_iterations<T>("boost::math::bessel_j_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   return prefix * result;
}

template <class T, class Policy>
struct bessel_y_small_z_series_term_a
{
   typedef T result_type;

   bessel_y_small_z_series_term_a(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      BOOST_MATH_STD_USING
      T r = term;
      ++N;
      term *= mult / (N * (N - v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};

template <class T, class Policy>
struct bessel_y_small_z_series_term_b
{
   typedef T result_type;

   bessel_y_small_z_series_term_b(T v_, T x)
      : N(0), v(v_)
   {
      BOOST_MATH_STD_USING
      mult = x / 2;
      mult *= -mult;
      term = 1;
   }
   T operator()()
   {
      T r = term;
      ++N;
      term *= mult / (N * (N + v));
      return r;
   }
private:
   unsigned N;
   T v;
   T mult;
   T term;
};
//
// Series form for BesselY as z -> 0, 
// see: http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/01/0003/
// This series is only useful when the second term is small compared to the first
// otherwise we get catastrophic cancellation errors.
//
// Approximating tgamma(v) by v^v, and assuming |tgamma(-z)| < eps we end up requiring:
// eps/2 * v^v(x/2)^-v > (x/2)^v or log(eps/2) > v log((x/2)^2/v)
//
template <class T, class Policy>
inline T bessel_y_small_z_series(T v, T x, T* pscale, const Policy& pol)
{
   BOOST_MATH_STD_USING
   static const char* function = "bessel_y_small_z_series<%1%>(%1%,%1%)";
   T prefix;
   T gam;
   T p = log(x / 2);
   T scale = 1;
   bool need_logs = (v >= max_factorial<T>::value) || (tools::log_max_value<T>() / v < fabs(p));
   if(!need_logs)
   {
      gam = boost::math::tgamma(v, pol);
      p = pow(x / 2, v);
      if(tools::max_value<T>() * p < gam)
      {
         scale /= gam;
         gam = 1;
         if(tools::max_value<T>() * p < gam)
         {
            return -policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -gam / (constants::pi<T>() * p);
   }
   else
   {
      gam = boost::math::lgamma(v, pol);
      p = v * p;
      prefix = gam - log(constants::pi<T>()) - p;
      if(tools::log_max_value<T>() < prefix)
      {
         prefix -= log(tools::max_value<T>() / 4);
         scale /= (tools::max_value<T>() / 4);
         if(tools::log_max_value<T>() < prefix)
         {
            return -policies::raise_overflow_error<T>(function, 0, pol);
         }
      }
      prefix = -exp(prefix);
   }
   bessel_y_small_z_series_term_a<T, Policy> s(v, x);
   boost::uintmax_t max_iter = policies::get_max_series_iterations<Policy>();
   *pscale = scale;
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T zero = 0;
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T result = boost::math::tools::sum_series(s, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   policies::check_series_iterations<T>("boost::math::bessel_y_small_z_series<%1%>(%1%,%1%)", max_iter, pol);
   result *= prefix;

   if(!need_logs)
   {
      prefix = boost::math::tgamma(-v, pol) * boost::math::cos_pi(v) * p / constants::pi<T>();
   }
   else
   {
      int sgn;
      prefix = boost::math::lgamma(-v, &sgn, pol) + p;
      prefix = exp(prefix) * sgn / constants::pi<T>();
   }
   bessel_y_small_z_series_term_b<T, Policy> s2(v, x);
   max_iter = policies::get_max_series_iterations<Policy>();
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x582))
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter, zero);
#else
   T b = boost::math::tools::sum_series(s2, boost::math::policies::get_epsilon<T, Policy>(), max_iter);
#endif
   result -= scale * prefix * b;
   return result;
}

template <class T, class Policy>
T bessel_yn_small_z(int n, T z, T* scale, const Policy& pol)
{
   //
   // See http://functions.wolfram.com/Bessel-TypeFunctions/BesselY/06/01/04/01/02/
   //
   // Note that when called we assume that x < epsilon and n is a positive integer.
   //
   BOOST_MATH_STD_USING
   BOOST_ASSERT(n >= 0);
   BOOST_ASSERT((z < policies::get_epsilon<T, Policy>()));

   if(n == 0)
   {
      return (2 / constants::pi<T>()) * (log(z / 2) +  constants::euler<T>());
   }
   else if(n == 1)
   {
      return (z / constants::pi<T>()) * log(z / 2) 
         - 2 / (constants::pi<T>() * z) 
         - (z / (2 * constants::pi<T>())) * (1 - 2 * constants::euler<T>());
   }
   else if(n == 2)
   {
      return (z * z) / (4 * constants::pi<T>()) * log(z / 2) 
         - (4 / (constants::pi<T>() * z * z)) 
         - ((z * z) / (8 * constants::pi<T>())) * (T(3)/2 - 2 * constants::euler<T>());
   }
   else
   {
      T p = pow(z / 2, n);
      T result = -((boost::math::factorial<T>(n - 1) / constants::pi<T>()));
      if(p * tools::max_value<T>() < result)
      {
         T div = tools::max_value<T>() / 8;
         result /= div;
         *scale /= div;
         if(p * tools::max_value<T>() < result)
         {
            return -policies::raise_overflow_error<T>("bessel_yn_small_z<%1%>(%1%,%1%)", 0, pol);
         }
      }
      return result / p;
   }
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_JN_SERIES_HPP


/* bessel_jy_series.hpp
ylZ78j+zMbRHxqCfSL4Q01rcYD3m9b5uHJyEZaTuk9/wOShE6v4dByfB8fPfc3EIT/mrzZ86dUQsiSJkXMY6nIvHFqLrmN3mcyALqeMVfRxWIT7TKYMKkNhhh4Mjcy3HLfSBi7ty7P7c50CO0k63jHWEpjFJ5ZG5kstBI3C7AscUr3dkGWFEU3j/mvbzZJCMb13aeb5ZXVnH8+z7LhPAC0utc7qdb7A5NK5KjDjl4GcqjeryeZZD/68ip7XFkYcezvZQBnFwD47Pgc2BJPWI1rgcsifU9gEVtptuxDjE1Ghqv9Z3MSjtmvITfZV3tIHpT32J22fWNebbcu/ygsfis2JC5SfQqglMStB9qlxlK63SysQihgD2XadtDM9LW+8kGIlb8jx26RE2V1pfqYw0Hxj1lYWhNHnOzGrMHts2T5KenZw9XLjHwZmFAhZBkql/WeacmXsFeKMqFG6c5BXijBaCajXk1sSNBDdP2pLGxXgR1xIGB77UM7p3Gh+1NFLPXpCHJqNsjq+DnCbyOluqxhmCi/xI5oq7WKtjKItKG1BBLKMRB+f4hUNrMAjAVhuVUlnkrDijZm40GhXEx/evLwJe5vq7PFQJZNitWWQfpjnxqJoUBg778mOa0ywslSIEBjLn6eUVjhbBcFAT8aO5uykcQUWDasqx6YLg8BtaMouJnNuvGundiYU7H5+bWThZmJk9crxw8PDh6fl58ttljvteNoYLbeZ1m3F5opuN9B3OoDvcu06fnJmyY8R8kGPHiMUgx7ajHO7LBOfQwfmZw4XDx2cR0B2cmV1I2nk2yWvyvik8lMhztrS8UKJBXuw3i+gD8I4UlhaXCpgJNc5HqPc8jxH3YXx5cf++hCFz+GXCsbRCzzY470KCVZYWJW+JZU4RLljEY1+UYPVgucUi41GriiAR5TLWIGxoj6cq5xW2OTnCZu40e+IYBKbtpt0kDMowNYVgGlqBeLhRaTa5H7sBznJprVpDIWxbIQ66UMcQA5+DrjmH+og+ZFoeB0N4vVVfqtcM+jDhtQO8JmwpXnzS8XnX5o08tJF1ur6DU7tOcVzl4miTXifIbNj4ar3ZWi9hDjkasmV8snnW/M+csTC4Ayx/0vM8jjicRuls0k011j2fs1Y6Jb4rc9bDo3pD7Cdn49CkxpnqEjdFxswXEw+qsrRUgYaaMxzrvtrBEIji5wLr29suwnhzfTgXQP9WlqvnJPbpBzjNjWWLk3u7zWkG8ok8jp9P/9Nc3yWMtouI4zBqNGo6rm1/hjk0wGPfRcm98xqF15uVWA8xNa9xPCQ4Jk3riJXMKbYtlTeCu6E9FBqVVgNx3hUS21IcVI19eu531u+QEx7FeIb/YIGniW6RGCMf4J5txBPLlY1So7TeglpzH37W5kaYe+o1wsjJC1rolixzRyevs0lm8E8cB3wi4cChLm6scE+Aw+PXrosxZ6VRwrygvg5jbZVqhUqjUYdJyzy281DJD0Et6+2W/Tu8v1knDI22MUxb1nlMtzGEDmVEILL3UAziyF7FV4NHhDgoRsfGn1UcVG+1VF038NXsQ0Sfl4cabaT+2afuFGyx1Kzs3ydjznsuqjAYQEXi5uLz1HNL1WgVGMf5H1bP1arrFXo2kfNmRz27JnPR3MfUc+uYJGKDETohcfwnNL5Rg7HJ+vyrJU9oU60aR19qfOhfNtEDxJueEohObV1O85qr9Y1ameyK7bb9OakH+mO0sQGbYbtj3J4zbH7e+r0AbeX6bb2EMZhY4gPJI6gYJP8FzRONZ50K4ti/aciYElkcZz/QwuCER3CB++hlFo5hC8vOav7Xtp+Po2UZx79hYRjKhup8DpDI6OUWB+OMPN8=
*/