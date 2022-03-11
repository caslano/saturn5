//  (C) Copyright Nick Thompson 2017.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#define BOOST_MATH_SPECIAL_CHEBYSHEV_HPP
#include <cmath>
#include <boost/math/constants/constants.hpp>

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

template<class Real, bool second>
inline Real chebyshev_imp(unsigned n, Real const & x)
{
#ifdef BOOST_MATH_CHEB_USE_STD_ACOSH
    using std::acosh;
#else
   using boost::math::acosh;
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
            return cosh(n*acosh(x));
        }
        if (x < -1)
        {
            if (n & 1)
            {
                return -cosh(n*acosh(-x));
            }
            else
            {
                return cosh(n*acosh(-x));
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, false>(n, static_cast<value_type>(x)), "boost::math::chebyshev_t<%1%>(unsigned, %1%)");
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
   return policies::checked_narrowing_cast<result_type, Policy>(detail::chebyshev_imp<value_type, true>(n, static_cast<value_type>(x)), "boost::math::chebyshev_u<%1%>(unsigned, %1%)");
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
   if (n == 0)
   {
      return result_type(0);
   }
   return policies::checked_narrowing_cast<result_type, Policy>(n * detail::chebyshev_imp<value_type, true>(n - 1, static_cast<value_type>(x)), "boost::math::chebyshev_t_prime<%1%>(unsigned, %1%)");
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


}}
#endif

/* chebyshev.hpp
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
*/