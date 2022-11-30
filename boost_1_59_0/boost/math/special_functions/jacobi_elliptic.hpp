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
   return policies::checked_narrowing_cast<result_type, Policy>(sn, function);
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
nONMRZOANTYkqNucLVpUZrI4AbyV0876X9VktN8ozYyGlvfEdsBI0ZBq2aAS++ykCBFZkwa3KjivipGTt7VFuXnBjW7if4T8+mEzzeP8ky2X1jPOOp5tRvl90gruRHsYrUOcYDeC9k3ZEvgEdhwGsyHyKB/VwLHNLukP+OEPwY9COCXqtxtVB9AVjzVVBktqrPSYz8JirjcL4w0vz8Ifj3YjAgW6Sw+CbRZ8mZHZ0DD42NpUyEc1Obj79NCm3UTzN2+T8IMpXvkU4+/t0xxztByymiNZ9h2Gi/p85CN8B2Nn/fFH4m6nw4FiCEmIQNwjjb6+saN4azdmcS//pS+WN7dOtb1hqJHqLD1prUGg01daz6WLCGns6Zcd1cB/k1hx5nc5bubBRdw0aduqZ/RDET9WYduzRnOj+nTeydgrtic8qT0iKtmverBFfoDHVx8NcuNnhZ6z7OTUYNhaiyY4xeuIUs8IduyL1l1qX3b3lPXk0eBbdL88XY9iW4ROg/J1xhc5aqcLHRAMOclbmMy21McnzbvCTWOOM6zjpxT1nsvCip8VnNCG/dZR3/7nO395Pni2yNUHuoXt/7gmC4v73PXLFfxTp21eq6ZewtiO1mYmLfQfiNMznx0zToeAHzImjxu12VcgQ2tp/hWmbZd7LcINt7Jq4UpvKWltxjp24Z2W308/aBep9Wz387f1TNdLdHt6NPC9xL5AYLuAUN1/PasB8qmB1df297OrlFxuXsLwpIDXicsU0RoF1JvAMfjwat52XTced52slRAVZAb/toOb0zkcAE+zTKR6o5G5anJYrA84hGINi9RkfuPpbbcuEUmtuKjEtwoMo2GY9SShEBCOUY8SN1u2v4BklUOJDpNQnz1F1ZVtc/4T/Le5r/IfJIFA+ZQCnKUc5ueUr2vvzboTK/C2AYYjvoD+715u3T5OLuzj1b6HAAZxBhyXq8uIyM1KDUOxc5X2ZpRTU4N22+n90edll46PsUpsV4OFiUo1H7dtK9HoxdQV89ES/4NKreq6QuWajdzFvP5ScisFOQ9vzdGle3TNf8NKLtlujhr1p0FkLO2qz3WYkcWuKzbTgDqWzVijaHYDRgBXxU/+BlfZ1cQONy91F7CPgOmO4mn3REPdAcYTHisGOLrF8xlHAoL5v3hNddoySmvjMLMEirp0bGS1gjq/pAY1ivYGX2/VrE8ITzvOFD5yORwVOuBZfMm8nv3c8vLsiW2Yh1/15Z1kp/deudfWT9RAiY6/v+v2DV1nlwg/i4vn1Li0rSjIr4m3DxLL3vjKE4+hIl0P7FpQXHYvxstM1owPWUDz8KjjTYkfUYPK+j0VDHq/w4eOAXuLzIfN41v5hju1b/6k3W1DGVOm+pCkzuJ1maXjhgYA+PLx2UEWvZ/PMuStii874/L3KtzeSTDTTvb+NVOirv1HcdJVEhb/9KZHgTkJE0NNN7sGmCjBj8K8i9ehDt27iFeMEugOYDF00XpEh1WwYNVswgg6XiC9zt8sxB36mUrOFNWs3t3QW92wRk5qC4BecDraHUtFlLO5PKg0nq7rB7G4rds0Nngm49nxszQaoPnFguKOB9C22su3EdHWw1sBXVm1VMBIFrUQlyqkhVvm0aJnQzV50oQVlXukiT+26hcT9tNnjFufd4BR5PFlYsXl5cN1gUEdd2XafTWz6nfF0Io3RwGhZHYJ1rrTH6MGTWj7BKGHxQHYnC3OYUcSriZ9sPAjPPEl0YH6WzK3h5UpTdhzbUxIkButpRleq2aqy+Delq6Ttf0s4ljJBwkL49zIS9caaAUQTnr4YHgoYazC60DDt1HYXMVfBeKpG+xXgqKe8ce6527RegXw+7o4gTo0K361dBhKTndu6UeFrwiKsJeRal7Esnfnhua5N7cM11rfvmYHS8NNegPBeAlbeR6LELxFEOTvKuN0Bv45UtqJwI6FfKrwUkRdrt9UuLl78fxXmpjZDiUd5OTvfsMZr5Kku4frP8dIEZJR/3GDv7q3wMY1B30Ki+BAsgR0FYapRp1b+z3MMduERIWzXy66eHOdWJRbMP+Wf3mdbSR0yOlAudOZGTSaHbyL6e/jzqVBJNQi6707ugzLsFAz/Z3KEDH9Oc613ZYjJXHdECB2SCFnY53PLE8TKyFOizSJRBpOmzPJ21MkmGK7/0y61XkFnQBq6bcgZqp5IBEyy3XXllC8zwulJBy6aYTJed7kSMAkZWGXIczx6yVylj01Pf8MjFofXdFgHnkm4hxqcY3c/W7YHyClKYoUep75dj8gMOhjmtgstCTCi3npY2CxiraXqQXkfOz4Zp3RGSPotH6ag4V7y+Zr49YHiB+h2ikUzxwm6AyjIV+RZ2NSHfhf9/KrXb1QZ/7NnbSHZ/QzFZsL0X/TJ+aihPANnV+vtgNFBbNUgqvGM6Xtdv5GeXv3GIwURjh0rJFfHYk9fO12OdEUbvtReZlhd+3bxastXnhynwQEsdourWuxPshn59FkBL5C0fNYmS0KXMWpthtJT8Lj+3JzYr1UWF5t+eQIFp/cTXyzEiYaRPi2VmDBqzbxt+L322vorxPW+NqtHw7ctqXorxrZAKEANpMx8TTJZZbO1pD1k9rdDDuT23d0W3Qz5Pt7dLcD+p0fNZ/5dNfmxH1bg2y4s8cQWmQru+AoKaP2cDXn1Z3WUO3jPQmgErQrXx9jvO//CfEwgdVgZbm2KwsZIlgele/KVEgn2Ct+muAZyNerKRe4nliawsLbnj7CK2XGyVB9N4oIzSOYJ1FeGeqQBGH5okd1QWeZqxtCrQGqT65eXaVC8IpRLriDKRkzX9EeCe1B7PK1539zseXtS7fyhM523IEsnWhc4jb7JPxAzOCdcRSIhuWqr02C1P32pzMIIKq4jjrb/urRH0HXhxCEocjk0OYRTbBQ0yl+j/M4KmDhMKeJXEtwkWvtdK0qwIB/kvt4GOKPGR1WL5XcuhDDFVWgjVYMEGY3tFNNxPsFEAbl5f0XMoXCjEIcNk6NAdVDvP/BlC9m9CWgrpIjMr05EYuC5ZpYX2JABZf42jibplaCwRziPBstEvcdfcoLCfB51Iot6NN5KImU+8kr6PPW7Ff4UxVz0ZF7+RvbRVXy/fDhXUeXi7fh55QNskxsNwkOkeeLlfUy+fPvFR9GP9ZuvEdDyycul7pjo452Cvmu8ES3Sw3Xp1jDOjqvdF9xPh/zhLzlS2k5rTzm5LXAQB4HKaj6OoiqN+E7/p2HCMeVfx5CO10OIxi39a0XGYGazfAnz6lfltfxvSr6vL93WkwPDOb3A6YwfxqztYI+iOOm7edJepbzIVos7Gtqgl/lOdxbv4x7irqS00kzr0L9FyyWBekbpvbqCvy6AN6f8o4r0y8mz5kTbYSpBJfCmXqRjL3JSJ/3PxWCE1dLVEekIkPrrfoig/XSihpbZh5MFROf4voeTOlXqx/zUNBSSR8pDPWM03h7d3/u5Dib4QJuGnT83UUO3Al+P0j8G/xBqILkqw/K2aZw7rpQtDsk7V4CXx8Km5VOvjuEV+X5xR/q1l36o27yx39YP6JnENasJSn03cKxXV5umImmN3VhyZGD5J3CuarvASkYOLVvNtluph+d4cYSnoBUHlHU+77gQojD4pPh3sq/7+AyMB17PPI6R7BMzSdkqXlGvRnKPyvcXzrT+k9vG7FqBv1y+ybzAmQxUuFx3FP/QYINxoBDxOwCHjbWvlumJIXWvl/qzH4gYlq8q+bZhPlw2ous8UnNdvKdBdveoftXbUBcJlqh1kBq/yK18gTs+wXswT18zzYQ6wSKKHLCPZw9MWxwlMf1ctO4EoCbuqdVL6RaxV049tRhBbEExi4pcy6RDRZwIUrit2JAqc+I2cT4XRGG+yI5UDRkCNP+FGPN9x01+JIfAs/tx398Ft4WAV8q4hTjkClpJySH1C3g/v7dvUXM+0o7w3H/I7qduhDW7OlBz+trxQGNLnxIyQvdANhGOap5+AmHUE1IpCjigLDBmYTGmCpCiGYvM2pYE+xKKr9Te2lOhsLuGIYpjzM1w+soUtXIdvXwzJZdY9bfwPBMuvyPKcFEY3SKvPwEkDjUrZ7sTAcsTJEHrNejHc+iRg/xtG6eeodKi2sVBKdXel88NnP4NEreKPVZVFSmcV0E3MYlLKDZKm33wG09RKUgLzMPo2Uc/OKY7PoVa8zJMV9IodkuUVKfTEx2DTVAZP4EzZtBCqzzlzatw0nxPd31dnUb4IDE9D1yFP62u+TKkx+Hg6f9iEdSTxfFcDf3SY+FJVd2VewYWWUAlcwmZ7/UuYzoOzlrcH+GQY9bdsYWXNdNLFIi98xy+sQPpEDMG8L4Y3zsakQrHZP7dPPXQBcnSC9LbuUZ4KHGAReA/+EMjeSe14qraOdHXsDuSRkYALvnaAHhy4fejzpLVgMVD0Los/iOt5h6ZBP0mOvqoTU4w7cgTtD8p1UOkUe2kycHj7OlV9OxCLBprgP6G2l9KQ2VlJVvmTejjW2R4Q3aaAU9vu3iLXVjgyEC2XJSlj2JifBZ6RQU15gCQfH2puT22U74wb50lwxmHrf+ckHesvxdkJg118U1D8GLJwosjsDSK510ZB9ptYVaLF+M7sENeOExqgySoxLbfBLM6Q6RIg1J6gpNIvJMH0wZZZz6jHRpWS/mYiw5NMLpsUr7dX5brKf8kZHOLWy6DJ7rVNFitWVLAj3SvAELHtJMNSnb1fUWMS0F0WnskKtls0raZX4YAbWK5yNC4Ctl+J3EocYwKHUAAWu0EB9QxmZEOLAE1Z6jBIyymZbsuZ4+g3NjnHO0sCoKB1u4KUWr8wA5Xvla8vop2OZYIsojg3hwKKmYuURUnUIyw6uos+PTeAenLB0VFS5pgCkgu2MyIh03qT2iLJqGncA4NTSzmficn0ezewe3fpOi0GU4TUQ4FpfLl8FaZdhgteQ5h4AM0fkTpxarlTueIXraFjxTllQeFzu7YK6/3VFdfDCQJlJgzHlNesQif8Kr37F4WHVkMytPWYnCNu+Bb9m9UV5PVSdEkOgHjGQpnJCpDCZfLDOBuURSBt+anKrAGw2D8zZGbuNOhoTr9aNnFMS9bORBacldeCPOkoVk8cOnpoPQ44hMn+ZS3I/WK89vzsitXmhc/a0HpNhvBjU/GgSHoB4SgBu2jgHDFCycLihtVsZ35T27xq0WCpEahnEYKAXbcVLZEZqXeCiUPTkp3fpYMwXMcWUyiSNZz/Cbp11gGLFJmAbCgRHo59dTrZaHN+eCrmG4RDemwFtrrAL2PLfA95cCUX8/Uek7XXhstn0jMAFE9aP3sXJhF/wy8aDo1Tf26daHGFUOrA/I+OhXRl0VII8pndNjP1wY1ooJpOu7Tpc2duFnHR1yBdImXNyRstnWKxHwhkrfydf1Ua9KkftJrIIlb0n5nrmZT9xCXN7krSUq/ChcQXO7j3nJacSYZJqj6WLmoMm4sKcyev9UVOD5mr/dUd+c2+LN4BINk4AeOhdZxg3sSyo6DoIVCOX5qL4pi33JrKfCjTP+fMLu3zf7qwllr7qNWaVMJxVie1mKjJpVs7vyPwtKgND4RB0Lm9vCh8ixuKb5Sm63zLOn7qvN6H/Inq9nHfy47Ls8gxlP+kWxphWx+hnWR/unirZHLttQzzD82GUcrsZYHovsgf55/811zCkx4/oK9TPJjqAo4I9aT49ytrTIe+zpYpgs6Kevpm+0xfhpfmItsMRG5j9a3SnQu99kANeyqq/NAP23jn3EV+DuaBQPBf5Rhc/iGXtZTK9QnzOHdKraHSZ9r7Mo9bLPvm8K8IaPj/qb8lzHyHnWW5h2qGZrCIC79eV0qtyTdcAr0j08EZny3dKiEkjdqFhPl8/NHaFVaqF11VkqSRxnB2sidJE4jiVixNScvUv/yG0gbyy0nzZ3NoqIrbLWm6qkWAVPlGzHbqpl9T3GTs4BxHAw6FupsstfE0K2x2bc49s7+qIL51kqXF8RbVSAPEUBVHtjrt1HPvT1n1ZJktAKMqLgdkPuaW2NdhctuDiTGspO/HhqQaQMzetWj/ZCSevEKgbgvM0WC9d/mMPTCxkJeHmt24Pc1vVP6fdztwH6Uo1jlO+TE6HBiPHjQVSeOC8NrFeMpFCMt8LUVs7rDEOdM85T6lsO3KZzcAlJZYJp2GsjrClrSZJ+X/VWupsIPBYj2RM3aNk4CC/vIUNaI2hPCj9M1BwC6V5QycToP5AuVhuSDX4tcws5wrC/MTbCLhfuKNHj/ejexliv4Gc2ad2izOorUWEBlz8JA+oeUw25uV7u0calrvHVP9ndOxkkw9njQwYxpibCgvAevwLKW16SYIyn0rwvtZ4QuWQe4ZZifDHUF21bUM8LHoM+a892UyWe0esEV3VuVZZk/Mp7/G626ekl5WsT1bJAKyqCJoX6ZYePppfvRFaVhfg4MfDDKpNTB5L5B2TiCytDPLD37ZnQUkthCYOymxUkTXaXp1oBs069tJzoEWIta2GDfrESV56EljupJuuj+hki6VMoxehd4q290qBCkX7H0wpS5g53qb3Hpkt9gXW0PvKk2UKDbCxGE1jVLeIX6o13NuuAfGr4ujq4IISvpphhuZvJWW8UvtX0I4DDLxeCtCbJaaydlmBoZJP/PXHf1p84D/Y/+ZlJHZaj2snN1ARTVbH40xYSW/K7LW8fBsMk/ZdnmoELxcojycQNKqaT1orXWk0ve+BbPmuNfyW11STn8CASZcbehPNx0Xkw85/VMy8RYDjdPCy66wg9LVbbZ6Ox26nqOv9p9uUPhPBoN2jP6cpZkPSOziK9+0npZWUEZUxEUp0UAM0rbUOFaJCAvzYE68MIS+zgpLjf4sIJgPDg7W6gdfsFyRflTqt219U/NV9JTdZl+UnSoWvcPeC5K1a6O9t96gMtt1nb4WA1OzJKrK3FLM7pmSOi/yg11vedAWv+sRfaeG6EzidbF9c3toyuK+/TwMnKmEOxpv5jvJGfKQiESsUy+ve1zWJ9SIoeVSrY1nzGkI+DkLCC5lQmXzMOtNpme65T5voktsp2nyRPvL2+pZkSupcbdhcLLTQSYZCVY9VCqPRiT1WVuteJKhhcRbRtWN1vhcaUDqBy+4CTMvqU/3hc+Gr6XOQLdk89/pOUDkDYdbz6+TOZv/1fUrhvEy80T0oWnU8ADJOpmB5BrFjHHYsfP7Ny343vqe5JI/o4b+NnAUcbjs3OHuDpL6CSUSsSkbQKnJQnT2o7MRNW2M/9V8/Yy68jnuyLIOx3HQRQrO+ZzbbpqPrc+aa4x1BZhaZWgqCvdlegMl5mW6BBocoFJQ5ioMZdyYdiaXKeNRnpvPzp/TkhhUsarD3YPinuwa6IBoya8wFhAnRC2mZI5ybb1H2v40ug0edXOlRWzrJpVBYxcGvtTPgkyHoTJCn4OyCj+ChsQF5xDba/brdhLRLbImLmx+UC17s3fmBoMa6vPFvefwhjGip4qbuSzizgP892hj4vYTKcrsutabAHmGTeLVna2oByxxyIn72CXJxnC5Hf3PS6c86KJ+J3sdZDR4BoR1Pgs8EkRDDw4LXC7ypoVAPqvsWMkZ/3VP6XwGaZn84CP2w2m7+FSWjoCPO9vIHD37O4b+T9PrggDXYHJUfq
*/