
//  (C) Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_LEGENDRE_HPP
#define BOOST_MATH_SPECIAL_LEGENDRE_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <utility>
#include <vector>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/tools/roots.hpp>
#include <boost/math/tools/config.hpp>
#include <boost/math/tools/cxx03_warn.hpp>

namespace boost{
namespace math{

// Recurrence relation for legendre P and Q polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type
   legendre_next(unsigned l, T1 x, T2 Pl, T3 Plm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * l + 1) * result_type(x) * result_type(Pl) - l * result_type(Plm1)) / (l + 1);
}

namespace detail{

// Implement Legendre P and Q polynomials via recurrence:
template <class T, class Policy>
T legendre_imp(unsigned l, T x, const Policy& pol, bool second = false)
{
   static const char* function = "boost::math::legrendre_p<%1%>(unsigned, %1%)";
   // Error handling:
   if((x < -1) || (x > 1))
      return policies::raise_domain_error<T>(
         function,
         "The Legendre Polynomial is defined for"
         " -1 <= x <= 1, but got x = %1%.", x, pol);

   T p0, p1;
   if(second)
   {
      // A solution of the second kind (Q):
      p0 = (boost::math::log1p(x, pol) - boost::math::log1p(-x, pol)) / 2;
      p1 = x * p0 - 1;
   }
   else
   {
      // A solution of the first kind (P):
      p0 = 1;
      p1 = x;
   }
   if(l == 0)
      return p0;

   unsigned n = 1;

   while(n < l)
   {
      std::swap(p0, p1);
      p1 = boost::math::legendre_next(n, x, p0, p1);
      ++n;
   }
   return p1;
}

template <class T, class Policy>
T legendre_p_prime_imp(unsigned l, T x, const Policy& pol, T* Pn 
#ifdef BOOST_NO_CXX11_NULLPTR
   = 0
#else
   = nullptr
#endif
)
{
   static const char* function = "boost::math::legrendre_p_prime<%1%>(unsigned, %1%)";
   // Error handling:
   if ((x < -1) || (x > 1))
      return policies::raise_domain_error<T>(
         function,
         "The Legendre Polynomial is defined for"
         " -1 <= x <= 1, but got x = %1%.", x, pol);
   
   if (l == 0)
    {
        if (Pn)
        {
           *Pn = 1;
        }
        return 0;
    }
    T p0 = 1;
    T p1 = x;
    T p_prime;
    bool odd = l & 1;
    // If the order is odd, we sum all the even polynomials:
    if (odd)
    {
        p_prime = p0;
    }
    else // Otherwise we sum the odd polynomials * (2n+1)
    {
        p_prime = 3*p1;
    }

    unsigned n = 1;
    while(n < l - 1)
    {
       std::swap(p0, p1);
       p1 = boost::math::legendre_next(n, x, p0, p1);
       ++n;
       if (odd)
       {
          p_prime += (2*n+1)*p1;
          odd = false;
       }
       else
       {
           odd = true;
       }
    }
    // This allows us to evaluate the derivative and the function for the same cost.
    if (Pn)
    {
        std::swap(p0, p1);
        *Pn = boost::math::legendre_next(n, x, p0, p1);
    }
    return p_prime;
}

template <class T, class Policy>
struct legendre_p_zero_func
{
   int n;
   const Policy& pol;

   legendre_p_zero_func(int n_, const Policy& p) : n(n_), pol(p) {}

   std::pair<T, T> operator()(T x) const
   { 
      T Pn;
      T Pn_prime = detail::legendre_p_prime_imp(n, x, pol, &Pn);
      return std::pair<T, T>(Pn, Pn_prime); 
   };
};

template <class T, class Policy>
std::vector<T> legendre_p_zeros_imp(int n, const Policy& pol)
{
    using std::cos;
    using std::sin;
    using std::ceil;
    using std::sqrt;
    using boost::math::constants::pi;
    using boost::math::constants::half;
    using boost::math::tools::newton_raphson_iterate;

    BOOST_ASSERT(n >= 0);
    std::vector<T> zeros;
    if (n == 0)
    {
        // There are no zeros of P_0(x) = 1.
        return zeros;
    }
    int k;
    if (n & 1)
    {
        zeros.resize((n-1)/2 + 1, std::numeric_limits<T>::quiet_NaN());
        zeros[0] = 0;
        k = 1;
    }
    else
    {
        zeros.resize(n/2, std::numeric_limits<T>::quiet_NaN());
        k = 0;
    }
    T half_n = ceil(n*half<T>());

    while (k < (int)zeros.size())
    {
        // Bracket the root: Szego:
        // Gabriel Szego, Inequalities for the Zeros of Legendre Polynomials and Related Functions, Transactions of the American Mathematical Society, Vol. 39, No. 1 (1936)
        T theta_nk =  ((half_n - half<T>()*half<T>() - static_cast<T>(k))*pi<T>())/(static_cast<T>(n)+half<T>());
        T lower_bound = cos( (half_n - static_cast<T>(k))*pi<T>()/static_cast<T>(n + 1));
        T cos_nk = cos(theta_nk);
        T upper_bound = cos_nk;
        // First guess follows from:
        //  F. G. Tricomi, Sugli zeri dei polinomi sferici ed ultrasferici, Ann. Mat. Pura Appl., 31 (1950), pp. 93-97;
        T inv_n_sq = 1/static_cast<T>(n*n);
        T sin_nk = sin(theta_nk);
        T x_nk_guess = (1 - inv_n_sq/static_cast<T>(8) + inv_n_sq /static_cast<T>(8*n) - (inv_n_sq*inv_n_sq/384)*(39  - 28 / (sin_nk*sin_nk) ) )*cos_nk;

        boost::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

        legendre_p_zero_func<T, Policy> f(n, pol);

        const T x_nk = newton_raphson_iterate(f, x_nk_guess,
                                              lower_bound, upper_bound,
                                              policies::digits<T, Policy>(),
                                              number_of_iterations);

        BOOST_ASSERT(lower_bound < x_nk);
        BOOST_ASSERT(upper_bound > x_nk);
        zeros[k] = x_nk;
        ++k;
    }
    return zeros;
}

} // namespace detail

template <class T, class Policy>
inline typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
   legendre_p(int l, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   static const char* function = "boost::math::legendre_p<%1%>(unsigned, %1%)";
   if(l < 0)
      return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_imp(-l-1, static_cast<value_type>(x), pol, false), function);
   return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_imp(l, static_cast<value_type>(x), pol, false), function);
}


template <class T, class Policy>
inline typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
   legendre_p_prime(int l, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   static const char* function = "boost::math::legendre_p_prime<%1%>(unsigned, %1%)";
   if(l < 0)
      return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_p_prime_imp(-l-1, static_cast<value_type>(x), pol), function);
   return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_p_prime_imp(l, static_cast<value_type>(x), pol), function);
}

template <class T>
inline typename tools::promote_args<T>::type
   legendre_p(int l, T x)
{
   return boost::math::legendre_p(l, x, policies::policy<>());
}

template <class T>
inline typename tools::promote_args<T>::type
   legendre_p_prime(int l, T x)
{
   return boost::math::legendre_p_prime(l, x, policies::policy<>());
}

template <class T, class Policy>
inline std::vector<T> legendre_p_zeros(int l, const Policy& pol)
{
    if(l < 0)
        return detail::legendre_p_zeros_imp<T>(-l-1, pol);

    return detail::legendre_p_zeros_imp<T>(l, pol);
}


template <class T>
inline std::vector<T> legendre_p_zeros(int l)
{
   return boost::math::legendre_p_zeros<T>(l, policies::policy<>());
}

template <class T, class Policy>
inline typename boost::enable_if_c<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
   legendre_q(unsigned l, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_imp(l, static_cast<value_type>(x), pol, true), "boost::math::legendre_q<%1%>(unsigned, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type
   legendre_q(unsigned l, T x)
{
   return boost::math::legendre_q(l, x, policies::policy<>());
}

// Recurrence for associated polynomials:
template <class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type
   legendre_next(unsigned l, unsigned m, T1 x, T2 Pl, T3 Plm1)
{
   typedef typename tools::promote_args<T1, T2, T3>::type result_type;
   return ((2 * l + 1) * result_type(x) * result_type(Pl) - (l + m) * result_type(Plm1)) / (l + 1 - m);
}

namespace detail{
// Legendre P associated polynomial:
template <class T, class Policy>
T legendre_p_imp(int l, int m, T x, T sin_theta_power, const Policy& pol)
{
   // Error handling:
   if((x < -1) || (x > 1))
      return policies::raise_domain_error<T>(
      "boost::math::legendre_p<%1%>(int, int, %1%)",
         "The associated Legendre Polynomial is defined for"
         " -1 <= x <= 1, but got x = %1%.", x, pol);
   // Handle negative arguments first:
   if(l < 0)
      return legendre_p_imp(-l-1, m, x, sin_theta_power, pol);
   if(m < 0)
   {
      int sign = (m&1) ? -1 : 1;
      return sign * boost::math::tgamma_ratio(static_cast<T>(l+m+1), static_cast<T>(l+1-m), pol) * legendre_p_imp(l, -m, x, sin_theta_power, pol);
   }
   // Special cases:
   if(m > l)
      return 0;
   if(m == 0)
      return boost::math::legendre_p(l, x, pol);

   T p0 = boost::math::double_factorial<T>(2 * m - 1, pol) * sin_theta_power;

   if(m&1)
      p0 *= -1;
   if(m == l)
      return p0;

   T p1 = x * (2 * m + 1) * p0;

   int n = m + 1;

   while(n < l)
   {
      std::swap(p0, p1);
      p1 = boost::math::legendre_next(n, m, x, p0, p1);
      ++n;
   }
   return p1;
}

template <class T, class Policy>
inline T legendre_p_imp(int l, int m, T x, const Policy& pol)
{
   BOOST_MATH_STD_USING
   // TODO: we really could use that mythical "pow1p" function here:
   return legendre_p_imp(l, m, x, static_cast<T>(pow(1 - x*x, T(abs(m))/2)), pol);
}

}

template <class T, class Policy>
inline typename tools::promote_args<T>::type
   legendre_p(int l, int m, T x, const Policy& pol)
{
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   return policies::checked_narrowing_cast<result_type, Policy>(detail::legendre_p_imp(l, m, static_cast<value_type>(x), pol), "boost::math::legendre_p<%1%>(int, int, %1%)");
}

template <class T>
inline typename tools::promote_args<T>::type
   legendre_p(int l, int m, T x)
{
   return boost::math::legendre_p(l, m, x, policies::policy<>());
}

} // namespace math
} // namespace boost

#endif // BOOST_MATH_SPECIAL_LEGENDRE_HPP

/* legendre.hpp
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
*/