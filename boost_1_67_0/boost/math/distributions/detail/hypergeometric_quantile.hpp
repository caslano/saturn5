// Copyright 2008 John Maddock
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_QUANTILE_HPP
#define BOOST_MATH_DISTRIBUTIONS_DETAIL_HG_QUANTILE_HPP

#include <boost/math/policies/error_handling.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>

namespace boost{ namespace math{ namespace detail{

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_down>&)
{
   if((p < cum * fudge_factor) && (x != lbound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x-1);
      return --x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned /*lbound*/, unsigned ubound, const policies::discrete_quantile<policies::integer_round_up>&)
{
   if((cum < p * fudge_factor) && (x != ubound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x+1);
      return ++x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_inwards>&)
{
   if(p >= 0.5)
      return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T p, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_outwards>&)
{
   if(p >= 0.5)
      return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
   return round_x_from_p(x, p, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
}

template <class T>
inline unsigned round_x_from_p(unsigned x, T /*p*/, T /*cum*/, T /*fudge_factor*/, unsigned /*lbound*/, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_nearest>&)
{
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_down>&)
{
   if((q * fudge_factor > cum) && (x != lbound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x-1);
      return --x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned /*lbound*/, unsigned ubound, const policies::discrete_quantile<policies::integer_round_up>&)
{
   if((q < cum * fudge_factor) && (x != ubound))
   {
      BOOST_MATH_INSTRUMENT_VARIABLE(x+1);
      return ++x;
   }
   return x;
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_inwards>&)
{
   if(q < 0.5)
      return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T q, T cum, T fudge_factor, unsigned lbound, unsigned ubound, const policies::discrete_quantile<policies::integer_round_outwards>&)
{
   if(q >= 0.5)
      return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_down>());
   return round_x_from_q(x, q, cum, fudge_factor, lbound, ubound, policies::discrete_quantile<policies::integer_round_up>());
}

template <class T>
inline unsigned round_x_from_q(unsigned x, T /*q*/, T /*cum*/, T /*fudge_factor*/, unsigned /*lbound*/, unsigned /*ubound*/, const policies::discrete_quantile<policies::integer_round_nearest>&)
{
   return x;
}

template <class T, class Policy>
unsigned hypergeometric_quantile_imp(T p, T q, unsigned r, unsigned n, unsigned N, const Policy& pol)
{
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
   typedef typename Policy::discrete_quantile_type discrete_quantile_type;
   BOOST_MATH_STD_USING
   BOOST_FPU_EXCEPTION_GUARD
   T result;
   T fudge_factor = 1 + tools::epsilon<T>() * ((N <= boost::math::prime(boost::math::max_prime - 1)) ? 50 : 2 * N);
   unsigned base = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
   unsigned lim = (std::min)(r, n);

   BOOST_MATH_INSTRUMENT_VARIABLE(p);
   BOOST_MATH_INSTRUMENT_VARIABLE(q);
   BOOST_MATH_INSTRUMENT_VARIABLE(r);
   BOOST_MATH_INSTRUMENT_VARIABLE(n);
   BOOST_MATH_INSTRUMENT_VARIABLE(N);
   BOOST_MATH_INSTRUMENT_VARIABLE(fudge_factor);
   BOOST_MATH_INSTRUMENT_VARIABLE(base);
   BOOST_MATH_INSTRUMENT_VARIABLE(lim);

   if(p <= 0.5)
   {
      unsigned x = base;
      result = hypergeometric_pdf<T>(x, r, n, N, pol);
      T diff = result;
      if (diff == 0)
      {
         ++x;
         // We want to skip through x values as fast as we can until we start getting non-zero values,
         // otherwise we're just making lots of expensive PDF calls:
         T log_pdf = boost::math::lgamma(static_cast<T>(n + 1), pol)
            + boost::math::lgamma(static_cast<T>(r + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - n + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - r + 1), pol)
            - boost::math::lgamma(static_cast<T>(N + 1), pol)
            - boost::math::lgamma(static_cast<T>(x + 1), pol)
            - boost::math::lgamma(static_cast<T>(n - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(r - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(N - n - r + x + 1), pol);
         while (log_pdf < tools::log_min_value<T>())
         {
            log_pdf += -log(static_cast<T>(x + 1)) + log(static_cast<T>(n - x)) + log(static_cast<T>(r - x)) - log(static_cast<T>(N - n - r + x + 1));
            ++x;
         }
         // By the time we get here, log_pdf may be fairly inaccurate due to
         // roundoff errors, get a fresh PDF calculation before proceeding:
         diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      }
      while(result < p)
      {
         diff = (diff > tools::min_value<T>() * 8) 
            ? T(n - x) * T(r - x) * diff / (T(x + 1) * T(N + x + 1 - n - r))
            : hypergeometric_pdf<T>(x + 1, r, n, N, pol);
         if(result + diff / 2 > p)
            break;
         ++x;
         result += diff;
#ifdef BOOST_MATH_INSTRUMENT
         if(diff != 0)
         {
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
#endif
      }
      return round_x_from_p(x, p, result, fudge_factor, base, lim, discrete_quantile_type());
   }
   else
   {
      unsigned x = lim;
      result = 0;
      T diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      if (diff == 0)
      {
         // We want to skip through x values as fast as we can until we start getting non-zero values,
         // otherwise we're just making lots of expensive PDF calls:
         --x;
         T log_pdf = boost::math::lgamma(static_cast<T>(n + 1), pol)
            + boost::math::lgamma(static_cast<T>(r + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - n + 1), pol)
            + boost::math::lgamma(static_cast<T>(N - r + 1), pol)
            - boost::math::lgamma(static_cast<T>(N + 1), pol)
            - boost::math::lgamma(static_cast<T>(x + 1), pol)
            - boost::math::lgamma(static_cast<T>(n - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(r - x + 1), pol)
            - boost::math::lgamma(static_cast<T>(N - n - r + x + 1), pol);
         while (log_pdf < tools::log_min_value<T>())
         {
            log_pdf += log(static_cast<T>(x)) - log(static_cast<T>(n - x + 1)) - log(static_cast<T>(r - x + 1)) + log(static_cast<T>(N - n - r + x));
            --x;
         }
         // By the time we get here, log_pdf may be fairly inaccurate due to
         // roundoff errors, get a fresh PDF calculation before proceeding:
         diff = hypergeometric_pdf<T>(x, r, n, N, pol);
      }
      while(result + diff / 2 < q)
      {
         result += diff;
         diff = (diff > tools::min_value<T>() * 8)
            ? x * T(N + x - n - r) * diff / (T(1 + n - x) * T(1 + r - x))
            : hypergeometric_pdf<T>(x - 1, r, n, N, pol);
         --x;
#ifdef BOOST_MATH_INSTRUMENT
         if(diff != 0)
         {
            BOOST_MATH_INSTRUMENT_VARIABLE(x);
            BOOST_MATH_INSTRUMENT_VARIABLE(diff);
            BOOST_MATH_INSTRUMENT_VARIABLE(result);
         }
#endif
      }
      return round_x_from_q(x, q, result, fudge_factor, base, lim, discrete_quantile_type());
   }
#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
}

template <class T, class Policy>
inline unsigned hypergeometric_quantile(T p, T q, unsigned r, unsigned n, unsigned N, const Policy&)
{
   BOOST_FPU_EXCEPTION_GUARD
   typedef typename tools::promote_args<T>::type result_type;
   typedef typename policies::evaluation<result_type, Policy>::type value_type;
   typedef typename policies::normalise<
      Policy, 
      policies::promote_float<false>, 
      policies::promote_double<false>, 
      policies::assert_undefined<> >::type forwarding_policy;

   return detail::hypergeometric_quantile_imp<value_type>(p, q, r, n, N, forwarding_policy());
}

}}} // namespaces

#endif


/* hypergeometric_quantile.hpp
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
*/