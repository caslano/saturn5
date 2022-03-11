// math_fwd.hpp

// TODO revise completely for new distribution classes.

// Copyright Paul A. Bristow 2006.
// Copyright John Maddock 2006.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Omnibus list of forward declarations of math special functions.

// IT = Integer type.
// RT = Real type (built-in floating-point types, float, double, long double) & User Defined Types
// AT = Integer or Real type

#ifndef BOOST_MATH_SPECIAL_MATH_FWD_HPP
#define BOOST_MATH_SPECIAL_MATH_FWD_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <vector>
#include <boost/math/special_functions/detail/round_fwd.hpp>
#include <boost/math/tools/promotion.hpp> // for argument promotion.
#include <boost/math/policies/policy.hpp>
#include <boost/mpl/comparison.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config/no_tr1/complex.hpp>

#define BOOST_NO_MACRO_EXPAND /**/

namespace boost
{
   namespace math
   { // Math functions (in roughly alphabetic order).

   // Beta functions.
   template <class RT1, class RT2>
   typename tools::promote_args<RT1, RT2>::type
         beta(RT1 a, RT2 b); // Beta function (2 arguments).

   template <class RT1, class RT2, class A>
   typename tools::promote_args<RT1, RT2, A>::type
         beta(RT1 a, RT2 b, A x); // Beta function (3 arguments).

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         beta(RT1 a, RT2 b, RT3 x, const Policy& pol); // Beta function (3 arguments).

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         betac(RT1 a, RT2 b, RT3 x);

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         betac(RT1 a, RT2 b, RT3 x, const Policy& pol);

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta(RT1 a, RT2 b, RT3 x); // Incomplete beta function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta(RT1 a, RT2 b, RT3 x, const Policy& pol); // Incomplete beta function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac(RT1 a, RT2 b, RT3 x); // Incomplete beta complement function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac(RT1 a, RT2 b, RT3 x, const Policy& pol); // Incomplete beta complement function.

   template <class T1, class T2, class T3, class T4>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ibeta_inv(T1 a, T2 b, T3 p, T4* py);

   template <class T1, class T2, class T3, class T4, class Policy>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ibeta_inv(T1 a, T2 b, T3 p, T4* py, const Policy& pol);

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_inv(RT1 a, RT2 b, RT3 p); // Incomplete beta inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_inv(RT1 a, RT2 b, RT3 p, const Policy&); // Incomplete beta inverse function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_inva(RT1 a, RT2 b, RT3 p); // Incomplete beta inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_inva(RT1 a, RT2 b, RT3 p, const Policy&); // Incomplete beta inverse function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_invb(RT1 a, RT2 b, RT3 p); // Incomplete beta inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_invb(RT1 a, RT2 b, RT3 p, const Policy&); // Incomplete beta inverse function.

   template <class T1, class T2, class T3, class T4>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ibetac_inv(T1 a, T2 b, T3 q, T4* py);

   template <class T1, class T2, class T3, class T4, class Policy>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ibetac_inv(T1 a, T2 b, T3 q, T4* py, const Policy& pol);

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_inv(RT1 a, RT2 b, RT3 q); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_inv(RT1 a, RT2 b, RT3 q, const Policy&); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_inva(RT1 a, RT2 b, RT3 q); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_inva(RT1 a, RT2 b, RT3 q, const Policy&); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_invb(RT1 a, RT2 b, RT3 q); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibetac_invb(RT1 a, RT2 b, RT3 q, const Policy&); // Incomplete beta complement inverse function.

   template <class RT1, class RT2, class RT3>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_derivative(RT1 a, RT2 b, RT3 x);  // derivative of incomplete beta

   template <class RT1, class RT2, class RT3, class Policy>
   typename tools::promote_args<RT1, RT2, RT3>::type
         ibeta_derivative(RT1 a, RT2 b, RT3 x, const Policy& pol);  // derivative of incomplete beta

   // Binomial:
   template <class T, class Policy>
   T binomial_coefficient(unsigned n, unsigned k, const Policy& pol);
   template <class T>
   T binomial_coefficient(unsigned n, unsigned k);

   // erf & erfc error functions.
   template <class RT> // Error function.
   typename tools::promote_args<RT>::type erf(RT z);
   template <class RT, class Policy> // Error function.
   typename tools::promote_args<RT>::type erf(RT z, const Policy&);

   template <class RT>// Error function complement.
   typename tools::promote_args<RT>::type erfc(RT z);
   template <class RT, class Policy>// Error function complement.
   typename tools::promote_args<RT>::type erfc(RT z, const Policy&);

   template <class RT>// Error function inverse.
   typename tools::promote_args<RT>::type erf_inv(RT z);
   template <class RT, class Policy>// Error function inverse.
   typename tools::promote_args<RT>::type erf_inv(RT z, const Policy& pol);

   template <class RT>// Error function complement inverse.
   typename tools::promote_args<RT>::type erfc_inv(RT z);
   template <class RT, class Policy>// Error function complement inverse.
   typename tools::promote_args<RT>::type erfc_inv(RT z, const Policy& pol);

   // Polynomials:
   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
         legendre_next(unsigned l, T1 x, T2 Pl, T3 Plm1);

   template <class T>
   typename tools::promote_args<T>::type
         legendre_p(int l, T x);
   template <class T>
   typename tools::promote_args<T>::type
          legendre_p_prime(int l, T x);


   template <class T, class Policy>
   inline std::vector<T> legendre_p_zeros(int l, const Policy& pol);

   template <class T>
   inline std::vector<T> legendre_p_zeros(int l);

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
   template <class T, class Policy>
   typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
         legendre_p(int l, T x, const Policy& pol);
   template <class T, class Policy>
   inline typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
      legendre_p_prime(int l, T x, const Policy& pol);
#endif
   template <class T>
   typename tools::promote_args<T>::type
         legendre_q(unsigned l, T x);
#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1310)
   template <class T, class Policy>
   typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
         legendre_q(unsigned l, T x, const Policy& pol);
#endif
   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
         legendre_next(unsigned l, unsigned m, T1 x, T2 Pl, T3 Plm1);

   template <class T>
   typename tools::promote_args<T>::type
         legendre_p(int l, int m, T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type
         legendre_p(int l, int m, T x, const Policy& pol);

   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
         laguerre_next(unsigned n, T1 x, T2 Ln, T3 Lnm1);

   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
      laguerre_next(unsigned n, unsigned l, T1 x, T2 Pl, T3 Plm1);

   template <class T>
   typename tools::promote_args<T>::type
      laguerre(unsigned n, T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type
      laguerre(unsigned n, unsigned m, T x, const Policy& pol);

   template <class T1, class T2>
   struct laguerre_result
   {
      typedef typename mpl::if_<
         policies::is_policy<T2>,
         typename tools::promote_args<T1>::type,
         typename tools::promote_args<T2>::type
      >::type type;
   };

   template <class T1, class T2>
   typename laguerre_result<T1, T2>::type
      laguerre(unsigned n, T1 m, T2 x);

   template <class T>
   typename tools::promote_args<T>::type
      hermite(unsigned n, T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type
      hermite(unsigned n, T x, const Policy& pol);

   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
      hermite_next(unsigned n, T1 x, T2 Hn, T3 Hnm1);

   template<class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type chebyshev_next(T1 const & x, T2 const & Tn, T3 const & Tn_1);

   template <class Real, class Policy>
   typename tools::promote_args<Real>::type
      chebyshev_t(unsigned n, Real const & x, const Policy&);
   template<class Real>
   typename tools::promote_args<Real>::type chebyshev_t(unsigned n, Real const & x);
   
   template <class Real, class Policy>
   typename tools::promote_args<Real>::type
      chebyshev_u(unsigned n, Real const & x, const Policy&);
   template<class Real>
   typename tools::promote_args<Real>::type chebyshev_u(unsigned n, Real const & x);

   template <class Real, class Policy>
   typename tools::promote_args<Real>::type
      chebyshev_t_prime(unsigned n, Real const & x, const Policy&);
   template<class Real>
   typename tools::promote_args<Real>::type chebyshev_t_prime(unsigned n, Real const & x);

   template<class Real, class T2>
   Real chebyshev_clenshaw_recurrence(const Real* const c, size_t length, const T2& x);

   template <class T1, class T2>
   std::complex<typename tools::promote_args<T1, T2>::type>
         spherical_harmonic(unsigned n, int m, T1 theta, T2 phi);

   template <class T1, class T2, class Policy>
   std::complex<typename tools::promote_args<T1, T2>::type>
      spherical_harmonic(unsigned n, int m, T1 theta, T2 phi, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type
         spherical_harmonic_r(unsigned n, int m, T1 theta, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type
      spherical_harmonic_r(unsigned n, int m, T1 theta, T2 phi, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type
         spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type
      spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi, const Policy& pol);

   // Elliptic integrals:
   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
         ellint_rf(T1 x, T2 y, T3 z);

   template <class T1, class T2, class T3, class Policy>
   typename tools::promote_args<T1, T2, T3>::type
         ellint_rf(T1 x, T2 y, T3 z, const Policy& pol);

   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
         ellint_rd(T1 x, T2 y, T3 z);

   template <class T1, class T2, class T3, class Policy>
   typename tools::promote_args<T1, T2, T3>::type
         ellint_rd(T1 x, T2 y, T3 z, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type
         ellint_rc(T1 x, T2 y);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type
         ellint_rc(T1 x, T2 y, const Policy& pol);

   template <class T1, class T2, class T3, class T4>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ellint_rj(T1 x, T2 y, T3 z, T4 p);

   template <class T1, class T2, class T3, class T4, class Policy>
   typename tools::promote_args<T1, T2, T3, T4>::type
         ellint_rj(T1 x, T2 y, T3 z, T4 p, const Policy& pol);

   template <class T1, class T2, class T3>
   typename tools::promote_args<T1, T2, T3>::type
      ellint_rg(T1 x, T2 y, T3 z);

   template <class T1, class T2, class T3, class Policy>
   typename tools::promote_args<T1, T2, T3>::type
      ellint_rg(T1 x, T2 y, T3 z, const Policy& pol);

   template <typename T>
   typename tools::promote_args<T>::type ellint_2(T k);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi, const Policy& pol);

   template <typename T>
   typename tools::promote_args<T>::type ellint_1(T k);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi, const Policy& pol);

   template <typename T>
   typename tools::promote_args<T>::type ellint_d(T k);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi, const Policy& pol);

   namespace detail{

   template <class T, class U, class V>
   struct ellint_3_result
   {
      typedef typename mpl::if_<
         policies::is_policy<V>,
         typename tools::promote_args<T, U>::type,
         typename tools::promote_args<T, U, V>::type
      >::type type;
   };

   } // namespace detail


   template <class T1, class T2, class T3>
   typename detail::ellint_3_result<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi);

   template <class T1, class T2, class T3, class Policy>
   typename tools::promote_args<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type ellint_3(T1 k, T2 v);

   // Factorial functions.
   // Note: not for integral types, at present.
   template <class RT>
   struct max_factorial;
   template <class RT>
   RT factorial(unsigned int);
   template <class RT, class Policy>
   RT factorial(unsigned int, const Policy& pol);
   template <class RT>
   RT unchecked_factorial(unsigned int BOOST_MATH_APPEND_EXPLICIT_TEMPLATE_TYPE(RT));
   template <class RT>
   RT double_factorial(unsigned i);
   template <class RT, class Policy>
   RT double_factorial(unsigned i, const Policy& pol);

   template <class RT>
   typename tools::promote_args<RT>::type falling_factorial(RT x, unsigned n);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type falling_factorial(RT x, unsigned n, const Policy& pol);

   template <class RT>
   typename tools::promote_args<RT>::type rising_factorial(RT x, int n);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type rising_factorial(RT x, int n, const Policy& pol);

   // Gamma functions.
   template <class RT>
   typename tools::promote_args<RT>::type tgamma(RT z);

   template <class RT>
   typename tools::promote_args<RT>::type tgamma1pm1(RT z);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type tgamma1pm1(RT z, const Policy& pol);

   template <class RT1, class RT2>
   typename tools::promote_args<RT1, RT2>::type tgamma(RT1 a, RT2 z);

   template <class RT1, class RT2, class Policy>
   typename tools::promote_args<RT1, RT2>::type tgamma(RT1 a, RT2 z, const Policy& pol);

   template <class RT>
   typename tools::promote_args<RT>::type lgamma(RT z, int* sign);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type lgamma(RT z, int* sign, const Policy& pol);

   template <class RT>
   typename tools::promote_args<RT>::type lgamma(RT x);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type lgamma(RT x, const Policy& pol);

   template <class RT1, class RT2>
   typename tools::promote_args<RT1, RT2>::type tgamma_lower(RT1 a, RT2 z);

   template <class RT1, class RT2, class Policy>
   typename tools::promote_args<RT1, RT2>::type tgamma_lower(RT1 a, RT2 z, const Policy&);

   template <class RT1, class RT2>
   typename tools::promote_args<RT1, RT2>::type gamma_q(RT1 a, RT2 z);

   template <class RT1, class RT2, class Policy>
   typename tools::promote_args<RT1, RT2>::type gamma_q(RT1 a, RT2 z, const Policy&);

   template <class RT1, class RT2>
   typename tools::promote_args<RT1, RT2>::type gamma_p(RT1 a, RT2 z);

   template <class RT1, class RT2, class Policy>
   typename tools::promote_args<RT1, RT2>::type gamma_p(RT1 a, RT2 z, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type tgamma_delta_ratio(T1 z, T2 delta);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type tgamma_delta_ratio(T1 z, T2 delta, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type tgamma_ratio(T1 a, T2 b);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type tgamma_ratio(T1 a, T2 b, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type gamma_p_derivative(T1 a, T2 x);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type gamma_p_derivative(T1 a, T2 x, const Policy&);

   // gamma inverse.
   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type gamma_p_inv(T1 a, T2 p);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type gamma_p_inva(T1 a, T2 p, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type gamma_p_inva(T1 a, T2 p);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type gamma_p_inv(T1 a, T2 p, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type gamma_q_inv(T1 a, T2 q);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type gamma_q_inv(T1 a, T2 q, const Policy&);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type gamma_q_inva(T1 a, T2 q);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type gamma_q_inva(T1 a, T2 q, const Policy&);

   // digamma:
   template <class T>
   typename tools::promote_args<T>::type digamma(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type digamma(T x, const Policy&);

   // trigamma:
   template <class T>
   typename tools::promote_args<T>::type trigamma(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type trigamma(T x, const Policy&);

   // polygamma:
   template <class T>
   typename tools::promote_args<T>::type polygamma(int n, T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type polygamma(int n, T x, const Policy&);

   // Hypotenuse function sqrt(x ^ 2 + y ^ 2).
   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type
         hypot(T1 x, T2 y);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type
         hypot(T1 x, T2 y, const Policy&);

   // cbrt - cube root.
   template <class RT>
   typename tools::promote_args<RT>::type cbrt(RT z);

   template <class RT, class Policy>
   typename tools::promote_args<RT>::type cbrt(RT z, const Policy&);

   // log1p is log(x + 1)
   template <class T>
   typename tools::promote_args<T>::type log1p(T);

   template <class T, class Policy>
   typename tools::promote_args<T>::type log1p(T, const Policy&);

   // log1pmx is log(x + 1) - x
   template <class T>
   typename tools::promote_args<T>::type log1pmx(T);

   template <class T, class Policy>
   typename tools::promote_args<T>::type log1pmx(T, const Policy&);

   // Exp (x) minus 1 functions.
   template <class T>
   typename tools::promote_args<T>::type expm1(T);

   template <class T, class Policy>
   typename tools::promote_args<T>::type expm1(T, const Policy&);

   // Power - 1
   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type
         powm1(const T1 a, const T2 z);

   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type
         powm1(const T1 a, const T2 z, const Policy&);

   // sqrt(1+x) - 1
   template <class T>
   typename tools::promote_args<T>::type sqrt1pm1(const T& val);

   template <class T, class Policy>
   typename tools::promote_args<T>::type sqrt1pm1(const T& val, const Policy&);

   // sinus cardinals:
   template <class T>
   typename tools::promote_args<T>::type sinc_pi(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type sinc_pi(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type sinhc_pi(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type sinhc_pi(T x, const Policy&);

   // inverse hyperbolics:
   template<typename T>
   typename tools::promote_args<T>::type asinh(T x);

   template<typename T, class Policy>
   typename tools::promote_args<T>::type asinh(T x, const Policy&);

   template<typename T>
   typename tools::promote_args<T>::type acosh(T x);

   template<typename T, class Policy>
   typename tools::promote_args<T>::type acosh(T x, const Policy&);

   template<typename T>
   typename tools::promote_args<T>::type atanh(T x);

   template<typename T, class Policy>
   typename tools::promote_args<T>::type atanh(T x, const Policy&);

   namespace detail{

      typedef boost::integral_constant<int, 0> bessel_no_int_tag;      // No integer optimisation possible.
      typedef boost::integral_constant<int, 1> bessel_maybe_int_tag;   // Maybe integer optimisation.
      typedef boost::integral_constant<int, 2> bessel_int_tag;         // Definite integer optimisation.

      template <class T1, class T2, class Policy>
      struct bessel_traits
      {
         typedef typename mpl::if_<
            is_integral<T1>,
            typename tools::promote_args<T2>::type,
            typename tools::promote_args<T1, T2>::type
         >::type result_type;

         typedef typename policies::precision<result_type, Policy>::type precision_type;

         typedef typename mpl::if_<
            mpl::or_<
               mpl::less_equal<precision_type, boost::integral_constant<int, 0> >,
               mpl::greater<precision_type, boost::integral_constant<int, 64> > >,
            bessel_no_int_tag,
            typename mpl::if_<
               is_integral<T1>,
               bessel_int_tag,
               bessel_maybe_int_tag
            >::type
         >::type optimisation_tag;
         typedef typename mpl::if_<
            mpl::or_<
               mpl::less_equal<precision_type, boost::integral_constant<int, 0> >,
               mpl::greater<precision_type, boost::integral_constant<int, 113> > >,
            bessel_no_int_tag,
            typename mpl::if_<
               is_integral<T1>,
               bessel_int_tag,
               bessel_maybe_int_tag
            >::type
         >::type optimisation_tag128;
      };
   } // detail

   // Bessel functions:
   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_j(T1 v, T2 x, const Policy& pol);
   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_j_prime(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_j(T1 v, T2 x);
   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_j_prime(T1 v, T2 x);

   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type sph_bessel(unsigned v, T x, const Policy& pol);
   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type sph_bessel_prime(unsigned v, T x, const Policy& pol);

   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_bessel(unsigned v, T x);
   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_bessel_prime(unsigned v, T x);

   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_i(T1 v, T2 x, const Policy& pol);
   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_i_prime(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_i(T1 v, T2 x);
   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_i_prime(T1 v, T2 x);

   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_k(T1 v, T2 x, const Policy& pol);
   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_bessel_k_prime(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_k(T1 v, T2 x);
   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_bessel_k_prime(T1 v, T2 x);

   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_neumann(T1 v, T2 x, const Policy& pol);
   template <class T1, class T2, class Policy>
   typename detail::bessel_traits<T1, T2, Policy>::result_type cyl_neumann_prime(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_neumann(T1 v, T2 x);
   template <class T1, class T2>
   typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type cyl_neumann_prime(T1 v, T2 x);

   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type sph_neumann(unsigned v, T x, const Policy& pol);
   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type sph_neumann_prime(unsigned v, T x, const Policy& pol);

   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_neumann(unsigned v, T x);
   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type sph_neumann_prime(unsigned v, T x);

   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type cyl_bessel_j_zero(T v, int m, const Policy& pol);

   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_bessel_j_zero(T v, int m);

   template <class T, class OutputIterator>
   OutputIterator cyl_bessel_j_zero(T v,
                          int start_index,
                          unsigned number_of_zeros,
                          OutputIterator out_it);

   template <class T, class OutputIterator, class Policy>
   OutputIterator cyl_bessel_j_zero(T v,
                          int start_index,
                          unsigned number_of_zeros,
                          OutputIterator out_it,
                          const Policy&);

   template <class T, class Policy>
   typename detail::bessel_traits<T, T, Policy>::result_type cyl_neumann_zero(T v, int m, const Policy& pol);

   template <class T>
   typename detail::bessel_traits<T, T, policies::policy<> >::result_type cyl_neumann_zero(T v, int m);

   template <class T, class OutputIterator>
   OutputIterator cyl_neumann_zero(T v,
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it);

   template <class T, class OutputIterator, class Policy>
   OutputIterator cyl_neumann_zero(T v,
                         int start_index,
                         unsigned number_of_zeros,
                         OutputIterator out_it,
                         const Policy&);

   template <class T1, class T2>
   std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_1(T1 v, T2 x);

   template <class T1, class T2, class Policy>
   std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_1(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2, class Policy>
   std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> cyl_hankel_2(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> cyl_hankel_2(T1 v, T2 x);

   template <class T1, class T2, class Policy>
   std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_1(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_1(T1 v, T2 x);

   template <class T1, class T2, class Policy>
   std::complex<typename detail::bessel_traits<T1, T2, Policy>::result_type> sph_hankel_2(T1 v, T2 x, const Policy& pol);

   template <class T1, class T2>
   std::complex<typename detail::bessel_traits<T1, T2, policies::policy<> >::result_type> sph_hankel_2(T1 v, T2 x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type airy_ai(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type airy_ai(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type airy_bi(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type airy_bi(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type airy_ai_prime(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type airy_ai_prime(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type airy_bi_prime(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type airy_bi_prime(T x);

   template <class T>
   T airy_ai_zero(int m);
   template <class T, class Policy>
   T airy_ai_zero(int m, const Policy&);

   template <class OutputIterator>
   OutputIterator airy_ai_zero(
                     int start_index,
                     unsigned number_of_zeros,
                     OutputIterator out_it);
   template <class OutputIterator, class Policy>
   OutputIterator airy_ai_zero(
                     int start_index,
                     unsigned number_of_zeros,
                     OutputIterator out_it,
                     const Policy&);

   template <class T>
   T airy_bi_zero(int m);
   template <class T, class Policy>
   T airy_bi_zero(int m, const Policy&);

   template <class OutputIterator>
   OutputIterator airy_bi_zero(
                     int start_index,
                     unsigned number_of_zeros,
                     OutputIterator out_it);
   template <class OutputIterator, class Policy>
   OutputIterator airy_bi_zero(
                     int start_index,
                     unsigned number_of_zeros,
                     OutputIterator out_it,
                     const Policy&);

   template <class T, class Policy>
   typename tools::promote_args<T>::type sin_pi(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type sin_pi(T x);

   template <class T, class Policy>
   typename tools::promote_args<T>::type cos_pi(T x, const Policy&);

   template <class T>
   typename tools::promote_args<T>::type cos_pi(T x);

   template <class T>
   int fpclassify BOOST_NO_MACRO_EXPAND(T t);

   template <class T>
   bool isfinite BOOST_NO_MACRO_EXPAND(T z);

   template <class T>
   bool isinf BOOST_NO_MACRO_EXPAND(T t);

   template <class T>
   bool isnan BOOST_NO_MACRO_EXPAND(T t);

   template <class T>
   bool isnormal BOOST_NO_MACRO_EXPAND(T t);

   template<class T>
   int signbit BOOST_NO_MACRO_EXPAND(T x);

   template <class T>
   int sign BOOST_NO_MACRO_EXPAND(const T& z);

   template <class T, class U>
   typename tools::promote_args_permissive<T, U>::type copysign BOOST_NO_MACRO_EXPAND(const T& x, const U& y);

   template <class T>
   typename tools::promote_args_permissive<T>::type changesign BOOST_NO_MACRO_EXPAND(const T& z);

   // Exponential integrals:
   namespace detail{

   template <class T, class U>
   struct expint_result
   {
      typedef typename mpl::if_<
         policies::is_policy<U>,
         typename tools::promote_args<T>::type,
         typename tools::promote_args<U>::type
      >::type type;
   };

   } // namespace detail

   template <class T, class Policy>
   typename tools::promote_args<T>::type expint(unsigned n, T z, const Policy&);

   template <class T, class U>
   typename detail::expint_result<T, U>::type expint(T const z, U const u);

   template <class T>
   typename tools::promote_args<T>::type expint(T z);

   // Zeta:
   template <class T, class Policy>
   typename tools::promote_args<T>::type zeta(T s, const Policy&);

   // Owen's T function:
   template <class T1, class T2, class Policy>
   typename tools::promote_args<T1, T2>::type owens_t(T1 h, T2 a, const Policy& pol);

   template <class T1, class T2>
   typename tools::promote_args<T1, T2>::type owens_t(T1 h, T2 a);

   // Jacobi Functions:
   template <class T, class U, class V, class Policy>
   typename tools::promote_args<T, U, V>::type jacobi_elliptic(T k, U theta, V* pcn, V* pdn, const Policy&);

   template <class T, class U, class V>
   typename tools::promote_args<T, U, V>::type jacobi_elliptic(T k, U theta, V* pcn = 0, V* pdn = 0);

   template <class U, class T, class Policy>
   typename tools::promote_args<T, U>::type jacobi_sn(U k, T theta, const Policy& pol);

   template <class U, class T>
   typename tools::promote_args<T, U>::type jacobi_sn(U k, T theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_cn(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_cn(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_dn(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_dn(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_cd(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_cd(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_dc(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_dc(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_ns(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_ns(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_sd(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_sd(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_ds(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_ds(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_nc(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_nc(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_nd(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_nd(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_sc(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_sc(T k, U theta);

   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type jacobi_cs(T k, U theta, const Policy& pol);

   template <class T, class U>
   typename tools::promote_args<T, U>::type jacobi_cs(T k, U theta);


   template <class T>
   typename tools::promote_args<T>::type zeta(T s);

   // pow:
   template <int N, typename T, class Policy>
   typename tools::promote_args<T>::type pow(T base, const Policy& policy);

   template <int N, typename T>
   typename tools::promote_args<T>::type pow(T base);

   // next:
   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type nextafter(const T&, const U&, const Policy&);
   template <class T, class U>
   typename tools::promote_args<T, U>::type nextafter(const T&, const U&);
   template <class T, class Policy>
   typename tools::promote_args<T>::type float_next(const T&, const Policy&);
   template <class T>
   typename tools::promote_args<T>::type float_next(const T&);
   template <class T, class Policy>
   typename tools::promote_args<T>::type float_prior(const T&, const Policy&);
   template <class T>
   typename tools::promote_args<T>::type float_prior(const T&);
   template <class T, class U, class Policy>
   typename tools::promote_args<T, U>::type float_distance(const T&, const U&, const Policy&);
   template <class T, class U>
   typename tools::promote_args<T, U>::type float_distance(const T&, const U&);
   template <class T, class Policy>
   typename tools::promote_args<T>::type float_advance(T val, int distance, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type float_advance(const T& val, int distance);

   template <class T, class Policy>
   typename tools::promote_args<T>::type ulp(const T& val, const Policy& pol);
   template <class T>
   typename tools::promote_args<T>::type ulp(const T& val);

   template <class T, class U>
   typename tools::promote_args<T, U>::type relative_difference(const T&, const U&);
   template <class T, class U>
   typename tools::promote_args<T, U>::type epsilon_difference(const T&, const U&);

   template<class T>
   BOOST_MATH_CONSTEXPR_TABLE_FUNCTION T unchecked_bernoulli_b2n(const std::size_t n);
   template <class T, class Policy>
   T bernoulli_b2n(const int i, const Policy &pol);
   template <class T>
   T bernoulli_b2n(const int i);
   template <class T, class OutputIterator, class Policy>
   OutputIterator bernoulli_b2n(const int start_index,
                                       const unsigned number_of_bernoullis_b2n,
                                       OutputIterator out_it,
                                       const Policy& pol);
   template <class T, class OutputIterator>
   OutputIterator bernoulli_b2n(const int start_index,
                                       const unsigned number_of_bernoullis_b2n,
                                       OutputIterator out_it);
   template <class T, class Policy>
   T tangent_t2n(const int i, const Policy &pol);
   template <class T>
   T tangent_t2n(const int i);
   template <class T, class OutputIterator, class Policy>
   OutputIterator tangent_t2n(const int start_index,
                                       const unsigned number_of_bernoullis_b2n,
                                       OutputIterator out_it,
                                       const Policy& pol);
   template <class T, class OutputIterator>
   OutputIterator tangent_t2n(const int start_index,
                                       const unsigned number_of_bernoullis_b2n,
                                       OutputIterator out_it);

   // Lambert W:
   template <class T, class Policy>
   typename boost::math::tools::promote_args<T>::type lambert_w0(T z, const Policy& pol);
   template <class T>
   typename boost::math::tools::promote_args<T>::type lambert_w0(T z);
   template <class T, class Policy>
   typename boost::math::tools::promote_args<T>::type lambert_wm1(T z, const Policy& pol);
   template <class T>
   typename boost::math::tools::promote_args<T>::type lambert_wm1(T z);
   template <class T, class Policy>
   typename boost::math::tools::promote_args<T>::type lambert_w0_prime(T z, const Policy& pol);
   template <class T>
   typename boost::math::tools::promote_args<T>::type lambert_w0_prime(T z);
   template <class T, class Policy>
   typename boost::math::tools::promote_args<T>::type lambert_wm1_prime(T z, const Policy& pol);
   template <class T>
   typename boost::math::tools::promote_args<T>::type lambert_wm1_prime(T z);

   // Hypergeometrics:
   template <class T1, class T2> typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z);
   template <class T1, class T2, class Policy> typename tools::promote_args<T1, T2>::type hypergeometric_1F0(T1 a, T2 z, const Policy&);

   template <class T1, class T2> typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z);
   template <class T1, class T2, class Policy> typename tools::promote_args<T1, T2>::type hypergeometric_0F1(T1 b, T2 z, const Policy&);

   template <class T1, class T2, class T3> typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z);
   template <class T1, class T2, class T3, class Policy> typename tools::promote_args<T1, T2, T3>::type hypergeometric_2F0(T1 a1, T2 a2, T3 z, const Policy&);

   template <class T1, class T2, class T3> typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1(T1 a, T2 b, T3 z);
   template <class T1, class T2, class T3, class Policy> typename tools::promote_args<T1, T2, T3>::type hypergeometric_1F1(T1 a, T2 b, T3 z, const Policy&);


    } // namespace math
} // namespace boost

#ifdef BOOST_HAS_LONG_LONG
#define BOOST_MATH_DETAIL_LL_FUNC(Policy)\
   \
   template <class T>\
   inline T modf(const T& v, boost::long_long_type* ipart){ using boost::math::modf; return modf(v, ipart, Policy()); }\
   \
   template <class T>\
   inline boost::long_long_type lltrunc(const T& v){ using boost::math::lltrunc; return lltrunc(v, Policy()); }\
   \
   template <class T>\
   inline boost::long_long_type llround(const T& v){ using boost::math::llround; return llround(v, Policy()); }\

#else
#define BOOST_MATH_DETAIL_LL_FUNC(Policy)
#endif

#if !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_CXX11_AUTO_DECLARATIONS) && !defined(BOOST_NO_CXX11_HDR_ARRAY)
#  define BOOST_MATH_DETAIL_11_FUNC(Policy)\
   template <class T, class U, class V>\
   inline typename boost::math::tools::promote_args<T, U>::type hypergeometric_1F1(const T& a, const U& b, const V& z)\
   { return boost::math::hypergeometric_1F1(a, b, z, Policy()); }\

#else
#  define BOOST_MATH_DETAIL_11_FUNC(Policy)
#endif

#define BOOST_MATH_DECLARE_SPECIAL_FUNCTIONS(Policy)\
   \
   BOOST_MATH_DETAIL_LL_FUNC(Policy)\
   BOOST_MATH_DETAIL_11_FUNC(Policy)\
   \
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type \
   beta(RT1 a, RT2 b) { return ::boost::math::beta(a, b, Policy()); }\
\
   template <class RT1, class RT2, class A>\
   inline typename boost::math::tools::promote_args<RT1, RT2, A>::type \
   beta(RT1 a, RT2 b, A x){ return ::boost::math::beta(a, b, x, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   betac(RT1 a, RT2 b, RT3 x) { return ::boost::math::betac(a, b, x, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibeta(RT1 a, RT2 b, RT3 x){ return ::boost::math::ibeta(a, b, x, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibetac(RT1 a, RT2 b, RT3 x){ return ::boost::math::ibetac(a, b, x, Policy()); }\
\
   template <class T1, class T2, class T3, class T4>\
   inline typename boost::math::tools::promote_args<T1, T2, T3, T4>::type  \
   ibeta_inv(T1 a, T2 b, T3 p, T4* py){ return ::boost::math::ibeta_inv(a, b, p, py, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibeta_inv(RT1 a, RT2 b, RT3 p){ return ::boost::math::ibeta_inv(a, b, p, Policy()); }\
\
   template <class T1, class T2, class T3, class T4>\
   inline typename boost::math::tools::promote_args<T1, T2, T3, T4>::type \
   ibetac_inv(T1 a, T2 b, T3 q, T4* py){ return ::boost::math::ibetac_inv(a, b, q, py, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibeta_inva(RT1 a, RT2 b, RT3 p){ return ::boost::math::ibeta_inva(a, b, p, Policy()); }\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type \
   ibetac_inva(T1 a, T2 b, T3 q){ return ::boost::math::ibetac_inva(a, b, q, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibeta_invb(RT1 a, RT2 b, RT3 p){ return ::boost::math::ibeta_invb(a, b, p, Policy()); }\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type \
   ibetac_invb(T1 a, T2 b, T3 q){ return ::boost::math::ibetac_invb(a, b, q, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibetac_inv(RT1 a, RT2 b, RT3 q){ return ::boost::math::ibetac_inv(a, b, q, Policy()); }\
\
   template <class RT1, class RT2, class RT3>\
   inline typename boost::math::tools::promote_args<RT1, RT2, RT3>::type \
   ibeta_derivative(RT1 a, RT2 b, RT3 x){ return ::boost::math::ibeta_derivative(a, b, x, Policy()); }\
\
   template <class T> T binomial_coefficient(unsigned n, unsigned k){ return ::boost::math::binomial_coefficient<T, Policy>(n, k, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type erf(RT z) { return ::boost::math::erf(z, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type erfc(RT z){ return ::boost::math::erfc(z, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type erf_inv(RT z) { return ::boost::math::erf_inv(z, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type erfc_inv(RT z){ return ::boost::math::erfc_inv(z, Policy()); }\
\
   using boost::math::legendre_next;\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   legendre_p(int l, T x){ return ::boost::math::legendre_p(l, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   legendre_p_prime(int l, T x){ return ::boost::math::legendre_p(l, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   legendre_q(unsigned l, T x){ return ::boost::math::legendre_q(l, x, Policy()); }\
\
   using ::boost::math::legendre_next;\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   legendre_p(int l, int m, T x){ return ::boost::math::legendre_p(l, m, x, Policy()); }\
\
   using ::boost::math::laguerre_next;\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   laguerre(unsigned n, T x){ return ::boost::math::laguerre(n, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::laguerre_result<T1, T2>::type \
   laguerre(unsigned n, T1 m, T2 x) { return ::boost::math::laguerre(n, m, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type \
   hermite(unsigned n, T x){ return ::boost::math::hermite(n, x, Policy()); }\
\
   using boost::math::hermite_next;\
\
   using boost::math::chebyshev_next;\
\
  template<class Real>\
  Real chebyshev_t(unsigned n, Real const & x){ return ::boost::math::chebyshev_t(n, x, Policy()); }\
\
  template<class Real>\
  Real chebyshev_u(unsigned n, Real const & x){ return ::boost::math::chebyshev_u(n, x, Policy()); }\
\
  template<class Real>\
  Real chebyshev_t_prime(unsigned n, Real const & x){ return ::boost::math::chebyshev_t_prime(n, x, Policy()); }\
\
  using ::boost::math::chebyshev_clenshaw_recurrence;\
\
   template <class T1, class T2>\
   inline std::complex<typename boost::math::tools::promote_args<T1, T2>::type> \
   spherical_harmonic(unsigned n, int m, T1 theta, T2 phi){ return boost::math::spherical_harmonic(n, m, theta, phi, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
   spherical_harmonic_r(unsigned n, int m, T1 theta, T2 phi){ return ::boost::math::spherical_harmonic_r(n, m, theta, phi, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
   spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi){ return boost::math::spherical_harmonic_i(n, m, theta, phi, Policy()); }\
\
   template <class T1, class T2, class Policy>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
      spherical_harmonic_i(unsigned n, int m, T1 theta, T2 phi, const Policy& pol);\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type \
   ellint_rf(T1 x, T2 y, T3 z){ return ::boost::math::ellint_rf(x, y, z, Policy()); }\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type \
   ellint_rd(T1 x, T2 y, T3 z){ return ::boost::math::ellint_rd(x, y, z, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
   ellint_rc(T1 x, T2 y){ return ::boost::math::ellint_rc(x, y, Policy()); }\
\
   template <class T1, class T2, class T3, class T4>\
   inline typename boost::math::tools::promote_args<T1, T2, T3, T4>::type \
   ellint_rj(T1 x, T2 y, T3 z, T4 p){ return boost::math::ellint_rj(x, y, z, p, Policy()); }\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type \
   ellint_rg(T1 x, T2 y, T3 z){ return ::boost::math::ellint_rg(x, y, z, Policy()); }\
   \
   template <typename T>\
   inline typename boost::math::tools::promote_args<T>::type ellint_2(T k){ return boost::math::ellint_2(k, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type ellint_2(T1 k, T2 phi){ return boost::math::ellint_2(k, phi, Policy()); }\
\
   template <typename T>\
   inline typename boost::math::tools::promote_args<T>::type ellint_d(T k){ return boost::math::ellint_d(k, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type ellint_d(T1 k, T2 phi){ return boost::math::ellint_d(k, phi, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type jacobi_zeta(T1 k, T2 phi){ return boost::math::jacobi_zeta(k, phi, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type heuman_lambda(T1 k, T2 phi){ return boost::math::heuman_lambda(k, phi, Policy()); }\
\
   template <typename T>\
   inline typename boost::math::tools::promote_args<T>::type ellint_1(T k){ return boost::math::ellint_1(k, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type ellint_1(T1 k, T2 phi){ return boost::math::ellint_1(k, phi, Policy()); }\
\
   template <class T1, class T2, class T3>\
   inline typename boost::math::tools::promote_args<T1, T2, T3>::type ellint_3(T1 k, T2 v, T3 phi){ return boost::math::ellint_3(k, v, phi, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type ellint_3(T1 k, T2 v){ return boost::math::ellint_3(k, v, Policy()); }\
\
   using boost::math::max_factorial;\
   template <class RT>\
   inline RT factorial(unsigned int i) { return boost::math::factorial<RT>(i, Policy()); }\
   using boost::math::unchecked_factorial;\
   template <class RT>\
   inline RT double_factorial(unsigned i){ return boost::math::double_factorial<RT>(i, Policy()); }\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type falling_factorial(RT x, unsigned n){ return boost::math::falling_factorial(x, n, Policy()); }\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type rising_factorial(RT x, unsigned n){ return boost::math::rising_factorial(x, n, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type tgamma(RT z){ return boost::math::tgamma(z, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type tgamma1pm1(RT z){ return boost::math::tgamma1pm1(z, Policy()); }\
\
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type tgamma(RT1 a, RT2 z){ return boost::math::tgamma(a, z, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type lgamma(RT z, int* sign){ return boost::math::lgamma(z, sign, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type lgamma(RT x){ return boost::math::lgamma(x, Policy()); }\
\
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type tgamma_lower(RT1 a, RT2 z){ return boost::math::tgamma_lower(a, z, Policy()); }\
\
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type gamma_q(RT1 a, RT2 z){ return boost::math::gamma_q(a, z, Policy()); }\
\
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type gamma_p(RT1 a, RT2 z){ return boost::math::gamma_p(a, z, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type tgamma_delta_ratio(T1 z, T2 delta){ return boost::math::tgamma_delta_ratio(z, delta, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type tgamma_ratio(T1 a, T2 b) { return boost::math::tgamma_ratio(a, b, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type gamma_p_derivative(T1 a, T2 x){ return boost::math::gamma_p_derivative(a, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type gamma_p_inv(T1 a, T2 p){ return boost::math::gamma_p_inv(a, p, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type gamma_p_inva(T1 a, T2 p){ return boost::math::gamma_p_inva(a, p, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type gamma_q_inv(T1 a, T2 q){ return boost::math::gamma_q_inv(a, q, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type gamma_q_inva(T1 a, T2 q){ return boost::math::gamma_q_inva(a, q, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type digamma(T x){ return boost::math::digamma(x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type trigamma(T x){ return boost::math::trigamma(x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type polygamma(int n, T x){ return boost::math::polygamma(n, x, Policy()); }\
   \
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
   hypot(T1 x, T2 y){ return boost::math::hypot(x, y, Policy()); }\
\
   template <class RT>\
   inline typename boost::math::tools::promote_args<RT>::type cbrt(RT z){ return boost::math::cbrt(z, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type log1p(T x){ return boost::math::log1p(x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type log1pmx(T x){ return boost::math::log1pmx(x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type expm1(T x){ return boost::math::expm1(x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::tools::promote_args<T1, T2>::type \
   powm1(const T1 a, const T2 z){ return boost::math::powm1(a, z, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type sqrt1pm1(const T& val){ return boost::math::sqrt1pm1(val, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type sinc_pi(T x){ return boost::math::sinc_pi(x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type sinhc_pi(T x){ return boost::math::sinhc_pi(x, Policy()); }\
\
   template<typename T>\
   inline typename boost::math::tools::promote_args<T>::type asinh(const T x){ return boost::math::asinh(x, Policy()); }\
\
   template<typename T>\
   inline typename boost::math::tools::promote_args<T>::type acosh(const T x){ return boost::math::acosh(x, Policy()); }\
\
   template<typename T>\
   inline typename boost::math::tools::promote_args<T>::type atanh(const T x){ return boost::math::atanh(x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type cyl_bessel_j(T1 v, T2 x)\
   { return boost::math::cyl_bessel_j(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type cyl_bessel_j_prime(T1 v, T2 x)\
   { return boost::math::cyl_bessel_j_prime(v, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type sph_bessel(unsigned v, T x)\
   { return boost::math::sph_bessel(v, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type sph_bessel_prime(unsigned v, T x)\
   { return boost::math::sph_bessel_prime(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_bessel_i(T1 v, T2 x) { return boost::math::cyl_bessel_i(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_bessel_i_prime(T1 v, T2 x) { return boost::math::cyl_bessel_i_prime(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_bessel_k(T1 v, T2 x) { return boost::math::cyl_bessel_k(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_bessel_k_prime(T1 v, T2 x) { return boost::math::cyl_bessel_k_prime(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_neumann(T1 v, T2 x){ return boost::math::cyl_neumann(v, x, Policy()); }\
\
   template <class T1, class T2>\
   inline typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type \
   cyl_neumann_prime(T1 v, T2 x){ return boost::math::cyl_neumann_prime(v, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type \
   sph_neumann(unsigned v, T x){ return boost::math::sph_neumann(v, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type \
   sph_neumann_prime(unsigned v, T x){ return boost::math::sph_neumann_prime(v, x, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type cyl_bessel_j_zero(T v, int m)\
   { return boost::math::cyl_bessel_j_zero(v, m, Policy()); }\
\
template <class OutputIterator, class T>\
   inline void cyl_bessel_j_zero(T v,\
                                 int start_index,\
                                 unsigned number_of_zeros,\
                                 OutputIterator out_it)\
   { boost::math::cyl_bessel_j_zero(v, start_index, number_of_zeros, out_it, Policy()); }\
\
   template <class T>\
   inline typename boost::math::detail::bessel_traits<T, T, Policy >::result_type cyl_neumann_zero(T v, int m)\
   { return boost::math::cyl_neumann_zero(v, m, Policy()); }\
\
template <class OutputIterator, class T>\
   inline void cyl_neumann_zero(T v,\
                                int start_index,\
                                unsigned number_of_zeros,\
                                OutputIterator out_it)\
   { boost::math::cyl_neumann_zero(v, start_index, number_of_zeros, out_it, Policy()); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type sin_pi(T x){ return boost::math::sin_pi(x); }\
\
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type cos_pi(T x){ return boost::math::cos_pi(x); }\
\
   using boost::math::fpclassify;\
   using boost::math::isfinite;\
   using boost::math::isinf;\
   using boost::math::isnan;\
   using boost::math::isnormal;\
   using boost::math::signbit;\
   using boost::math::sign;\
   using boost::math::copysign;\
   using boost::math::changesign;\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T,U>::type expint(T const& z, U const& u)\
   { return boost::math::expint(z, u, Policy()); }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type expint(T z){ return boost::math::expint(z, Policy()); }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type zeta(T s){ return boost::math::zeta(s, Policy()); }\
   \
   template <class T>\
   inline T round(const T& v){ using boost::math::round; return round(v, Policy()); }\
   \
   template <class T>\
   inline int iround(const T& v){ using boost::math::iround; return iround(v, Policy()); }\
   \
   template <class T>\
   inline long lround(const T& v){ using boost::math::lround; return lround(v, Policy()); }\
   \
   template <class T>\
   inline T trunc(const T& v){ using boost::math::trunc; return trunc(v, Policy()); }\
   \
   template <class T>\
   inline int itrunc(const T& v){ using boost::math::itrunc; return itrunc(v, Policy()); }\
   \
   template <class T>\
   inline long ltrunc(const T& v){ using boost::math::ltrunc; return ltrunc(v, Policy()); }\
   \
   template <class T>\
   inline T modf(const T& v, T* ipart){ using boost::math::modf; return modf(v, ipart, Policy()); }\
   \
   template <class T>\
   inline T modf(const T& v, int* ipart){ using boost::math::modf; return modf(v, ipart, Policy()); }\
   \
   template <class T>\
   inline T modf(const T& v, long* ipart){ using boost::math::modf; return modf(v, ipart, Policy()); }\
   \
   template <int N, class T>\
   inline typename boost::math::tools::promote_args<T>::type pow(T v){ return boost::math::pow<N>(v, Policy()); }\
   \
   template <class T> T nextafter(const T& a, const T& b){ return boost::math::nextafter(a, b, Policy()); }\
   template <class T> T float_next(const T& a){ return boost::math::float_next(a, Policy()); }\
   template <class T> T float_prior(const T& a){ return boost::math::float_prior(a, Policy()); }\
   template <class T> T float_distance(const T& a, const T& b){ return boost::math::float_distance(a, b, Policy()); }\
   template <class T> T ulp(const T& a){ return boost::math::ulp(a, Policy()); }\
   \
   template <class RT1, class RT2>\
   inline typename boost::math::tools::promote_args<RT1, RT2>::type owens_t(RT1 a, RT2 z){ return boost::math::owens_t(a, z, Policy()); }\
   \
   template <class T1, class T2>\
   inline std::complex<typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type> cyl_hankel_1(T1 v, T2 x)\
   {  return boost::math::cyl_hankel_1(v, x, Policy()); }\
   \
   template <class T1, class T2>\
   inline std::complex<typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type> cyl_hankel_2(T1 v, T2 x)\
   { return boost::math::cyl_hankel_2(v, x, Policy()); }\
   \
   template <class T1, class T2>\
   inline std::complex<typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type> sph_hankel_1(T1 v, T2 x)\
   { return boost::math::sph_hankel_1(v, x, Policy()); }\
   \
   template <class T1, class T2>\
   inline std::complex<typename boost::math::detail::bessel_traits<T1, T2, Policy >::result_type> sph_hankel_2(T1 v, T2 x)\
   { return boost::math::sph_hankel_2(v, x, Policy()); }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type jacobi_elliptic(T k, T theta, T* pcn, T* pdn)\
   { return boost::math::jacobi_elliptic(k, theta, pcn, pdn, Policy()); }\
   \
   template <class U, class T>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_sn(U k, T theta)\
   { return boost::math::jacobi_sn(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_cn(T k, U theta)\
   { return boost::math::jacobi_cn(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_dn(T k, U theta)\
   { return boost::math::jacobi_dn(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_cd(T k, U theta)\
   { return boost::math::jacobi_cd(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_dc(T k, U theta)\
   { return boost::math::jacobi_dc(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_ns(T k, U theta)\
   { return boost::math::jacobi_ns(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_sd(T k, U theta)\
   { return boost::math::jacobi_sd(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_ds(T k, U theta)\
   { return boost::math::jacobi_ds(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_nc(T k, U theta)\
   { return boost::math::jacobi_nc(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_nd(T k, U theta)\
   { return boost::math::jacobi_nd(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_sc(T k, U theta)\
   { return boost::math::jacobi_sc(k, theta, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type jacobi_cs(T k, U theta)\
   { return boost::math::jacobi_cs(k, theta, Policy()); }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type airy_ai(T x)\
   {  return boost::math::airy_ai(x, Policy());  }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type airy_bi(T x)\
   {  return boost::math::airy_bi(x, Policy());  }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type airy_ai_prime(T x)\
   {  return boost::math::airy_ai_prime(x, Policy());  }\
   \
   template <class T>\
   inline typename boost::math::tools::promote_args<T>::type airy_bi_prime(T x)\
   {  return boost::math::airy_bi_prime(x, Policy());  }\
   \
   template <class T>\
   inline T airy_ai_zero(int m)\
   { return boost::math::airy_ai_zero<T>(m, Policy()); }\
   template <class T, class OutputIterator>\
   OutputIterator airy_ai_zero(int start_index, unsigned number_of_zeros, OutputIterator out_it)\
   { return boost::math::airy_ai_zero<T>(start_index, number_of_zeros, out_it, Policy()); }\
   \
   template <class T>\
   inline T airy_bi_zero(int m)\
   { return boost::math::airy_bi_zero<T>(m, Policy()); }\
   template <class T, class OutputIterator>\
   OutputIterator airy_bi_zero(int start_index, unsigned number_of_zeros, OutputIterator out_it)\
   { return boost::math::airy_bi_zero<T>(start_index, number_of_zeros, out_it, Policy()); }\
   \
   template <class T>\
   T bernoulli_b2n(const int i)\
   { return boost::math::bernoulli_b2n<T>(i, Policy()); }\
   template <class T, class OutputIterator>\
   OutputIterator bernoulli_b2n(int start_index, unsigned number_of_bernoullis_b2n, OutputIterator out_it)\
   { return boost::math::bernoulli_b2n<T>(start_index, number_of_bernoullis_b2n, out_it, Policy()); }\
   \
   template <class T>\
   T tangent_t2n(const int i)\
   { return boost::math::tangent_t2n<T>(i, Policy()); }\
   template <class T, class OutputIterator>\
   OutputIterator tangent_t2n(int start_index, unsigned number_of_bernoullis_b2n, OutputIterator out_it)\
   { return boost::math::tangent_t2n<T>(start_index, number_of_bernoullis_b2n, out_it, Policy()); }\
   \
   template <class T> inline typename boost::math::tools::promote_args<T>::type lambert_w0(T z) { return boost::math::lambert_w0(z, Policy()); }\
   template <class T> inline typename boost::math::tools::promote_args<T>::type lambert_wm1(T z) { return boost::math::lambert_w0(z, Policy()); }\
   template <class T> inline typename boost::math::tools::promote_args<T>::type lambert_w0_prime(T z) { return boost::math::lambert_w0(z, Policy()); }\
   template <class T> inline typename boost::math::tools::promote_args<T>::type lambert_wm1_prime(T z) { return boost::math::lambert_w0(z, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type hypergeometric_1F0(const T& a, const U& z)\
   { return boost::math::hypergeometric_1F0(a, z, Policy()); }\
   \
   template <class T, class U>\
   inline typename boost::math::tools::promote_args<T, U>::type hypergeometric_0F1(const T& a, const U& z)\
   { return boost::math::hypergeometric_0F1(a, z, Policy()); }\
   \
   template <class T, class U, class V>\
   inline typename boost::math::tools::promote_args<T, U>::type hypergeometric_2F0(const T& a1, const U& a2, const V& z)\
   { return boost::math::hypergeometric_2F0(a1, a2, z, Policy()); }\
   \






#endif // BOOST_MATH_SPECIAL_MATH_FWD_HPP

/* math_fwd.hpp
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
*/