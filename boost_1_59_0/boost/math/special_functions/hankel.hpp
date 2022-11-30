// Copyright John Maddock 2012.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_HANKEL_HPP
#define BOOST_MATH_HANKEL_HPP

#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/bessel.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
std::complex<T> hankel_imp(T v, T x, const bessel_no_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   static const char* function = "boost::math::cyl_hankel_1<%1%>(%1%,%1%)";

   if(x < 0)
   {
      bool isint_v = floor(v) == v;
      T j, y;
      bessel_jy(v, -x, &j, &y, need_j | need_y, pol);
      std::complex<T> cx(x), cv(v);
      std::complex<T> j_result, y_result;
      if(isint_v)
      {
         int s = (iround(v) & 1) ? -1 : 1;
         j_result = j * s;
         y_result = T(s) * (y - (2 / constants::pi<T>()) * (log(-x) - log(cx)) * j);
      }
      else
      {
         j_result = pow(cx, v) * pow(-cx, -v) * j;
         T p1 = pow(-x, v);
         std::complex<T> p2 = pow(cx, v);
         y_result = p1 * y / p2
            + (p2 / p1 - p1 / p2) * j / tan(constants::pi<T>() * v);
      }
      // multiply y_result by i:
      y_result = std::complex<T>(-sign * y_result.imag(), sign * y_result.real());
      return j_result + y_result;
   }

   if(x == 0)
   {
      if(v == 0)
      {
         // J is 1, Y is -INF
         return std::complex<T>(1, sign * -policies::raise_overflow_error<T>(function, 0, pol));
      }
      else
      {
         // At least one of J and Y is complex infinity:
         return std::complex<T>(policies::raise_overflow_error<T>(function, 0, pol), sign * policies::raise_overflow_error<T>(function, 0, pol));
      }
   }

   T j, y;
   bessel_jy(v, x, &j, &y, need_j | need_y, pol);
   return std::complex<T>(j, sign * y);
}

template <class T, class Policy>
std::complex<T> hankel_imp(int v, T x, const bessel_int_tag&, const Policy& pol, int sign);

template <class T, class Policy>
inline std::complex<T> hankel_imp(T v, T x, const bessel_maybe_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING  // ADL of std names.
   int ival = detail::iconv(v, pol);
   if(0 == v - ival)
   {
      return hankel_imp(ival, x, bessel_int_tag(), pol, sign);
   }
   return hankel_imp(v, x, bessel_no_int_tag(), pol, sign);
}

template <class T, class Policy>
inline std::complex<T> hankel_imp(int v, T x, const bessel_int_tag&, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   if((std::abs(v) < 200) && (x > 0))
      return std::complex<T>(bessel_jn(v, x, pol), sign * bessel_yn(v, x, pol));
   return hankel_imp(static_cast<T>(v), x, bessel_no_int_tag(), pol, sign);
}

template <class T, class Policy>
inline std::complex<T> sph_hankel_imp(T v, T x, const Policy& pol, int sign)
{
   BOOST_MATH_STD_USING
   return constants::root_half_pi<T>() * hankel_imp(v + 0.5f, x, bessel_no_int_tag(), pol, sign) / sqrt(std::complex<T>(x));
}

} // namespace detail

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_1(T1 v, T2 x, const Policy& pol)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::hankel_imp<value_type>(v, static_cast<value_type>(x), tag_type(), pol, 1), "boost::math::cyl_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_1(T1 v, T2 x)
{
   return cyl_hankel_1(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_2(T1 v, T2 x, const Policy& pol)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename detail::bessel_traits<T1, T2, Policy>::optimisation_tag tag_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::hankel_imp<value_type>(v, static_cast<value_type>(x), tag_type(), pol, -1), "boost::math::cyl_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_2(T1 v, T2 x)
{
   return cyl_hankel_2(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_1(T1 v, T2 x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::sph_hankel_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy(), 1), "boost::math::sph_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_1(T1 v, T2 x)
{
   return sph_hankel_1(v, x, policies::policy<>());
}

template <class T1, class T2, class Policy>
inline std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_2(T1 v, T2 x, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename detail::bessel_traits<T1, T2, Policy>::result_type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<std::complex<result_type>, Policy>(detail::sph_hankel_imp<value_type>(static_cast<value_type>(v), static_cast<value_type>(x), forwarding_policy(), -1), "boost::math::sph_hankel_1<%1%>(%1%,%1%)");
}

template <class T1, class T2>
inline std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_2(T1 v, T2 x)
{
   return sph_hankel_2(v, x, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_HANKEL_HPP


/* hankel.hpp
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
*/