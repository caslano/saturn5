// Copyright John Maddock 2012.
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_JACOBI_ELLIPTIC_HPP
#define BOOST_MATH_JACOBI_ELLIPTIC_HPP

#include <boost/math/tools/precision.hpp>
#include <boost/math/tools/promotion.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/special_functions/math_fwd.hpp>

namespace boost{ namespace math{

namespace detail{

template <class T, class Policy>
T jacobi_recurse(const T& x, const T& k, T anm1, T bnm1, unsigned N, T* pTn, const Policy& pol)
{
   BOOST_MATH_STD_USING
   ++N;
   T Tn;
   T cn = (anm1 - bnm1) / 2;
   T an = (anm1 + bnm1) / 2;
   if(cn < policies::get_epsilon<T, Policy>())
   {
      Tn = ldexp(T(1), (int)N) * x * an;
   }
   else
      Tn = jacobi_recurse<T>(x, k, an, sqrt(anm1 * bnm1), N, 0, pol);
   if(pTn)
      *pTn = Tn;
   return (Tn + asin((cn / an) * sin(Tn))) / 2;
}

template <class T, class Policy>
T jacobi_imp(const T& x, const T& k, T* cn, T* dn, const Policy& pol, const char* function)
{
   BOOST_MATH_STD_USING
   if(k < 0)
   {
      *cn = policies::raise_domain_error<T>(function, "Modulus k must be positive but got %1%.", k, pol);
      *dn = *cn;
      return *cn;
   }
   if(k > 1)
   {
      T xp = x * k;
      T kp = 1 / k;
      T snp, cnp, dnp;
      snp = jacobi_imp(xp, kp, &cnp, &dnp, pol, function);
      *cn = dnp;
      *dn = cnp;
      return snp * kp;
   }
   //
   // Special cases first:
   //
   if(x == 0)
   {
      *cn = *dn = 1;
      return 0;
   }
   if(k == 0)
   {
      *cn = cos(x);
      *dn = 1;
      return sin(x);
   }
   if(k == 1)
   {
      *cn = *dn = 1 / cosh(x);
      return tanh(x);
   }
   //
   // Asymptotic forms from A&S 16.13:
   //
   if(k < tools::forth_root_epsilon<T>())
   {
      T su = sin(x);
      T cu = cos(x);
      T m = k * k;
      *dn = 1 - m * su * su / 2;
      *cn = cu + m * (x - su * cu) * su / 4;
      return su - m * (x - su * cu) * cu / 4;
   }
   /*  Can't get this to work to adequate precision - disabled for now...
   //
   // Asymptotic forms from A&S 16.15:
   //
   if(k > 1 - tools::root_epsilon<T>())
   {
      T tu = tanh(x);
      T su = sinh(x);
      T cu = cosh(x);
      T sec = 1 / cu;
      T kp = 1 - k;
      T m1 = 2 * kp - kp * kp;
      *dn = sec + m1 * (su * cu + x) * tu * sec / 4;
      *cn = sec - m1 * (su * cu - x) * tu * sec / 4;
      T sn = tu;
      T sn2 = m1 * (x * sec * sec - tu) / 4;
      T sn3 = (72 * x * cu + 4 * (8 * x * x - 5) * su - 19 * sinh(3 * x) + sinh(5 * x)) * sec * sec * sec * m1 * m1 / 512;
      return sn + sn2 - sn3;
   }*/
   T T1;
   T kc = 1 - k;
   T k_prime = k < 0.5 ? T(sqrt(1 - k * k)) : T(sqrt(2 * kc - kc * kc));
   T T0 = jacobi_recurse(x, k, T(1), k_prime, 0, &T1, pol);
   *cn = cos(T0);
   *dn = cos(T0) / cos(T1 - T0);
   return sin(T0);
}

} // namespace detail

template <class T, class U, class V, class Policy>
inline typename tools::promote_args<T, U, V>::type jacobi_elliptic(T k, U theta, V* pcn, V* pdn, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   static const char* function = "boost::math::jacobi_elliptic<%1%>(%1%)";

   value_type sn, cn, dn;
   sn = detail::jacobi_imp<value_type>(static_cast<value_type>(theta), static_cast<value_type>(k), &cn, &dn, forwarding_policy(), function);
   if(pcn)
      *pcn = policies::checked_narrowing_cast<result_type, Policy>(cn, function);
   if(pdn)
      *pdn = policies::checked_narrowing_cast<result_type, Policy>(dn, function);
   return policies::checked_narrowing_cast<result_type, Policy>(sn, function);;
}

template <class T, class U, class V>
inline typename tools::promote_args<T, U, V>::type jacobi_elliptic(T k, U theta, V* pcn, V* pdn)
{
   return jacobi_elliptic(k, theta, pcn, pdn, policies::policy<>());
}

template <class U, class T, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_sn(U k, T theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   return jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), static_cast<result_type*>(0), static_cast<result_type*>(0), pol);
}

template <class U, class T>
inline typename tools::promote_args<T, U>::type jacobi_sn(U k, T theta)
{
   return jacobi_sn(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_cn(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type cn;
   jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), &cn, static_cast<result_type*>(0), pol);
   return cn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_cn(T k, U theta)
{
   return jacobi_cn(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_dn(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type dn;
   jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), static_cast<result_type*>(0), &dn, pol);
   return dn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_dn(T k, U theta)
{
   return jacobi_dn(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_cd(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type cn, dn;
   jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), &cn, &dn, pol);
   return cn / dn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_cd(T k, U theta)
{
   return jacobi_cd(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_dc(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type cn, dn;
   jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), &cn, &dn, pol);
   return dn / cn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_dc(T k, U theta)
{
   return jacobi_dc(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_ns(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   return 1 / jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), static_cast<result_type*>(0), static_cast<result_type*>(0), pol);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_ns(T k, U theta)
{
   return jacobi_ns(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_sd(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type sn, dn;
   sn = jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), static_cast<result_type*>(0), &dn, pol);
   return sn / dn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_sd(T k, U theta)
{
   return jacobi_sd(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_ds(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type sn, dn;
   sn = jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), static_cast<result_type*>(0), &dn, pol);
   return dn / sn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_ds(T k, U theta)
{
   return jacobi_ds(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_nc(T k, U theta, const Policy& pol)
{
   return 1 / jacobi_cn(k, theta, pol);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_nc(T k, U theta)
{
   return jacobi_nc(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_nd(T k, U theta, const Policy& pol)
{
   return 1 / jacobi_dn(k, theta, pol);
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_nd(T k, U theta)
{
   return jacobi_nd(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_sc(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type sn, cn;
   sn = jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), &cn, static_cast<result_type*>(0), pol);
   return sn / cn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_sc(T k, U theta)
{
   return jacobi_sc(k, theta, policies::policy<>());
}

template <class T, class U, class Policy>
inline typename tools::promote_args<T, U>::type jacobi_cs(T k, U theta, const Policy& pol)
{
   typedef typename tools::promote_args<T, U>::type result_type;
   result_type sn, cn;
   sn = jacobi_elliptic(static_cast<result_type>(k), static_cast<result_type>(theta), &cn, static_cast<result_type*>(0), pol);
   return cn / sn;
}

template <class T, class U>
inline typename tools::promote_args<T, U>::type jacobi_cs(T k, U theta)
{
   return jacobi_cs(k, theta, policies::policy<>());
}

}} // namespaces

#endif // BOOST_MATH_JACOBI_ELLIPTIC_HPP

/* jacobi_elliptic.hpp
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
*/