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
#include <type_traits>
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
   }
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

    BOOST_MATH_ASSERT(n >= 0);
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

        std::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

        legendre_p_zero_func<T, Policy> f(n, pol);

        const T x_nk = newton_raphson_iterate(f, x_nk_guess,
                                              lower_bound, upper_bound,
                                              policies::digits<T, Policy>(),
                                              number_of_iterations);

        BOOST_MATH_ASSERT(lower_bound < x_nk);
        BOOST_MATH_ASSERT(upper_bound > x_nk);
        zeros[k] = x_nk;
        ++k;
    }
    return zeros;
}

} // namespace detail

template <class T, class Policy>
inline typename std::enable_if<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
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
inline typename std::enable_if<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
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
inline typename std::enable_if<policies::is_policy<Policy>::value, typename tools::promote_args<T>::type>::type
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
   BOOST_MATH_STD_USING
   // Error handling:
   if((x < -1) || (x > 1))
      return policies::raise_domain_error<T>(
      "boost::math::legendre_p<%1%>(int, int, %1%)",
         "The associated Legendre Polynomial is defined for"
         " -1 <= x <= 1, but got x = %1%.", x, pol);
   // Handle negative arguments first:
   if(l < 0)
      return legendre_p_imp(-l-1, m, x, sin_theta_power, pol);
   if ((l == 0) && (m == -1))
   {
      return sqrt((1 - x) / (1 + x));
   }
   if ((l == 1) && (m == 0))
   {
      return x;
   }
   if (-m == l)
   {
      return pow((1 - x * x) / 4, T(l) / 2) / boost::math::tgamma(l + 1, pol);
   }
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