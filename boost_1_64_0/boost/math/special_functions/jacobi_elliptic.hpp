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
gp8vzpGXP3KfofiEfpiCD/GfZ+T1x+He2foB99AD2uAfGeLGX/YnHc4fztcvsgCP/R97m+/6dPcea+GUo+HYrsalEd7hR4Vj9Xl9pc47y/qT7czjQ+JVE7w3j47PP1L2iXOD+bv9CWrF+7J6uEg8q5rrvX8M26/C/qMX0l/cLzsVjrpUnv0b30jVx3aO+keuentn9T96bYv8mNcKnlFn3U4PXl6Jh5bRab7VB4rfF+M12TnwzVjx9X7jeL58lC3P3E8PnIMXGO+M8XTYPvLcXDxwub6CSfSxw8zXGDh9FvvbFWf/efpad3ldHa/qIOtAfeV+x/Nz+b3mTbpUNr3uNXavLtvURv1KvbhiToje5f2uov81qaNk0S88b8MQOk8sXq1+MfM3Os2X9t2Byxq/lec/xxuGBdcvmB2Gg81bSF9pPVzVz3lLPJ96WOE06ywsE4d30kcH4ZkN4uA+ukUbvFz/TCn8FKGLz87hT1d4T7gy7Rx6V5w+Qfg2Ms8+BrfoL/YeC2P0TxnHPLpb8j38bAw8PlXfhXiTPcv8VegXfyg4rqIPhX52va/oloXivveuoRNXjJNPjpMPlqoz3EjHNP4Fp8If/aP7otF9PUfnU/hZF3EjDJfcyJ7f8txN7Oex1sE4XKre8Zd8zt5CcfyaPWfBtbPhl5KL9XE8zD+WwAm/ef6l9J2P+P3R8sloeu02z72YXtGJPvI8nN4KPviXvma/7OqX8d5X1G0WwVHZdJhn8Br6U7eV4ofvq0pSrSMHB2SMYaej4bA5MXCx+nN7z+m8xq/k10x8Bq/s8Zm45Xkqx8iLx8E7a/VBW5++8FLx/nX53H0W/2W/Q/hl9jnyqH1Y9uNfi6P69ynqvansI5muH5JnR9Gr2sD/8GSjfSNzvoKPi/nbJ3ALPJs83/vJo+sa4Vn2FWqtjrIBvoH/1m2QJ76GY6wLtbwdPWGBeD9eXVJ9s2IiHH9FyH7a+NS5dNk0ffU30GcWw3tZ6n4V5vteuGIZXNMzjL/pJ/5N/j0c34R7I3DOcnkluZw9lKo3XRWyjwH8oK5YVMeO2X/7h9VrjH+yOlb8s2H7FaoX86dNtfSyR1rZR4num2e8WuQJ/jzX/fPHuN+rdKJ/2d9GcblQ/JdnFk1X56zFT66nj9awn8/FtZflqUfwqC9d7w75qI5fhtnjAri5G17UNYQnsvMfxN0r1YdG6sP/hh7SCr5Unyx6Q/zF/5tugDf3Oq8SX4Kn6q71ni/SHQaqTy2OEXfozpdbT8vztbzNrrPhlWnqpvhY0WTv8bJ415oOXUf3+pF+lCEPP6iO21d9KD/G/mXWvVLPyICXuqnfLN5qfaw9vvOaTCc4l/+8II400A2W4Zld6a6fiO8XwwmvwENHmZ8PoutzqcuP5d8d9SM8Jr59Et0P2/5mWcFxeZG48Br/0yeS9Dt+Rp+euZR9/oKP6YdrGKlvJ/o93Cb87YJW4lLwHnX4Uo73zttgfuby46/4qf0xmuhq+6P7IU7S33WZ77zujZO/xcXH+EmjOlEyXP+yePWa+AWfb5InCl7l31/CPZPsu5upTko/CQ3AW+iXq4+hz11FvzjS+lP2h2mK1oXoJ4WPs9tO6jY3wW3saPNT+lmqxAv3b74fP6j23HSMzDVx8gueei29e4L9A8vp/5tj5DE8S//eKry4ogmeKonuv8UfpogXY/W7PYKXVMg/9sWqf5p9X68OTeeoU09qphPGZ+pLZCfdMoJxSD6dH7pewUb90WXqBPSShmbxoUJfy+nyCp60eCDd+Hi8LWIfk2Z8bSN/edDzPQ73Z4St/y3e2C8ymT/Xvgjn0QVrdtiXcZ3+kMPE6Xo4yjo/Fa+wVzo=
*/