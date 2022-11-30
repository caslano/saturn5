//  (C) Copyright Nick Thompson 2017.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#define BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#include <cmath>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/policies/error_handling.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/promotion.hpp>

#if (__cplusplus > 201103) || (defined(_CPPLIB_VER) && (_CPPLIB_VER >= 610))
#  define BOOST_MATH_CHEB_USE_STD_ACOSH
#endif

#ifndef BOOST_MATH_CHEB_USE_STD_ACOSH
#  include <boost/math/special_functions/acosh.hpp>
#endif

namespace boost { namespace math {

template<class T1, class T2, class T3>
inline typename tools::promote_args<T1, T2, T3>::type chebyshev_next(T1 const & x, T2 const & Tn, T3 const & Tn_1)
{
    return 2*x*Tn - Tn_1;
}

namespace detail {

template<class Real, bool second, class Policy>
inline Real chebyshev_imp(unsigned n, Real const & x, const Policy&)
{
#ifdef BOOST_MATH_CHEB_USE_STD_ACOSH
    using std::acosh;
#define BOOST_MATH_ACOSH_POLICY
#else
   using boost::math::acosh;
#define BOOST_MATH_ACOSH_POLICY , Policy()
#endif
    using std::cosh;
    using std::pow;
    using std::sqrt;
    Real T0 = 1;
    Real T1;
    if (second)
    {
        if (x > 1 || x < -1)
        {
            Real t = sqrt(x*x -1);
            return static_cast<Real>((pow(x+t, (int)(n+1)) - pow(x-t, (int)(n+1)))/(2*t));
        }
        T1 = 2*x;
    }
    else
    {
        if (x > 1)
        {
            return cosh(n*acosh(x BOOST_MATH_ACOSH_POLICY));
        }
        if (x < -1)
        {
            if (n & 1)
            {
                return -cosh(n*acosh(-x BOOST_MATH_ACOSH_POLICY));
            }
            else
            {
                return cosh(n*acosh(-x BOOST_MATH_ACOSH_POLICY));
            }
        }
        T1 = x;
    }

    if (n == 0)
    {
        return T0;
    }

    unsigned l = 1;
    while(l < n)
    {
       std::swap(T0, T1);
       T1 = boost::math::chebyshev_next(x, T0, T1);
       ++l;
    }
    return T1;
}
} // namespace detail

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_t(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, false>(n, static_cast<value_type>(x), forwarding_policy()), "boost::math::chebyshev_t<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_t(unsigned n, Real const & x)
{
    return chebyshev_t(n, x, policies::policy<>());
}

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_u(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;

   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, true>(n, static_cast<value_type>(x), forwarding_policy()), "boost::math::chebyshev_u<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_u(unsigned n, Real const & x)
{
    return chebyshev_u(n, x, policies::policy<>());
}

template <class Real, class Policy>
inline typename tools::promote_args<Real>::type
chebyshev_t_prime(unsigned n, Real const & x, const Policy&)
{
   typedef typename tools::promote_args<Real>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy,
      policies::promote_float<false>,
      policies::promote_double<false>,
      policies::discrete_quantile<>,
      policies::assert_undefined<> >::type forwarding_policy;
   if (n == 0)
   {
      return result_type(0);
   }
   return policies::checked_narrowing_cast<result_type, Policy>(n * detail::chebyshev_imp<value_type, true>(n - 1, static_cast<value_type>(x), forwarding_policy()), "boost::math::chebyshev_t_prime<%1%>(unsigned, %1%)");
}

template<class Real>
inline typename tools::promote_args<Real>::type chebyshev_t_prime(unsigned n, Real const & x)
{
   return chebyshev_t_prime(n, x, policies::policy<>());
}

/*
 * This is Algorithm 3.1 of
 * Gil, Amparo, Javier Segura, and Nico M. Temme.
 * Numerical methods for special functions.
 * Society for Industrial and Applied Mathematics, 2007.
 * https://www.siam.org/books/ot99/OT99SampleChapter.pdf
 * However, our definition of c0 differs by a factor of 1/2, as stated in the docs. . .
 */
template<class Real, class T2>
inline Real chebyshev_clenshaw_recurrence(const Real* const c, size_t length, const T2& x)
{
    using boost::math::constants::half;
    if (length < 2)
    {
        if (length == 0)
        {
            return 0;
        }
        return c[0]/2;
    }
    Real b2 = 0;
    Real b1 = c[length -1];
    for(size_t j = length - 2; j >= 1; --j)
    {
        Real tmp = 2*x*b1 - b2 + c[j];
        b2 = b1;
        b1 = tmp;
    }
    return x*b1 - b2 + half<Real>()*c[0];
}



namespace detail {
template<class Real>
inline Real unchecked_chebyshev_clenshaw_recurrence(const Real* const c, size_t length, const Real & a, const Real & b, const Real& x)
{
    Real t;
    Real u;
    // This cutoff is not super well defined, but it's a good estimate.
    // See "An Error Analysis of the Modified Clenshaw Method for Evaluating Chebyshev and Fourier Series"
    // J. OLIVER, IMA Journal of Applied Mathematics, Volume 20, Issue 3, November 1977, Pages 379-391
    // https://doi.org/10.1093/imamat/20.3.379
    const Real cutoff = 0.6;
    if (x - a < b - x)
    {
        u = 2*(x-a)/(b-a);
        t = u - 1;
        if (t > -cutoff)
        {
            Real b2 = 0;
            Real b1 = c[length -1];
            for(size_t j = length - 2; j >= 1; --j)
            {
                Real tmp = 2*t*b1 - b2 + c[j];
                b2 = b1;
                b1 = tmp;
            }
            return t*b1 - b2 + c[0]/2;
        }
        else
        {
            Real b = c[length -1];
            Real d = b;
            Real b2 = 0;
            for (size_t r = length - 2; r >= 1; --r)
            {
                d = 2*u*b - d + c[r];
                b2 = b;
                b = d - b;
            }
            return t*b - b2 + c[0]/2;
        }
    }
    else
    {
        u = -2*(b-x)/(b-a);
        t = u + 1;
        if (t < cutoff)
        {
            Real b2 = 0;
            Real b1 = c[length -1];
            for(size_t j = length - 2; j >= 1; --j)
            {
                Real tmp = 2*t*b1 - b2 + c[j];
                b2 = b1;
                b1 = tmp;
            }
            return t*b1 - b2 + c[0]/2;
        }
        else
        {
            Real b = c[length -1];
            Real d = b;
            Real b2 = 0;
            for (size_t r = length - 2; r >= 1; --r)
            {
                d = 2*u*b + d + c[r];
                b2 = b;
                b = d + b;
            }
            return t*b - b2 + c[0]/2;
        }
    }
}

} // namespace detail

template<class Real>
inline Real chebyshev_clenshaw_recurrence(const Real* const c, size_t length, const Real & a, const Real & b, const Real& x)
{
    if (x < a || x > b)
    {
        throw std::domain_error("x in [a, b] is required.");
    }
    if (length < 2)
    {
        if (length == 0)
        {
            return 0;
        }
        return c[0]/2;
    }
    return detail::unchecked_chebyshev_clenshaw_recurrence(c, length, a, b, x);
}


}}
#endif

/* chebyshev.hpp
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
*/