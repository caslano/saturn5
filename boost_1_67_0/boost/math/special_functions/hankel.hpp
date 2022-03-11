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