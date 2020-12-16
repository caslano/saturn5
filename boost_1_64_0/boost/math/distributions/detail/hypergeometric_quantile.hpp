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
zvlDrJPyhxp7RjW/ml/Nr+ZX86v5/Zv2/+fNXRTc/v/PffsvuJ//6lTH7A8cr3vUl+JcnQt9nknS1xLK91znFecslMs7uj8w9M2pYvteAw2r69z9Qjbe8+cWFPW07vusWL6Xdd+nT76/yAcTl1lcUpRjW9dG3r9+T5HavlPlk50ucRfKR2Zse6y8sllNzb406z4pr+ysZNEBKi717BnaK+cLndb8PypyT+qFXj2U9ETZk2r2A3RsEpoEupBI0vj7V42CrPq+02BdNqEuvfqe1AF+WmfqH2f8Td0YHRHd923qwKcXTVmX75WZLrJSpmavDGWn+28i94jvrxNK8N0BZOEd8B3aZmGipW1mUJ5VbJ+FidVrn4WJ1WufyFfUPs1e2AMi855raa+Er3p7RdbbrvhLy0H1SVbI+esCtvZr0mn0mFkzzYi0jdCkcVBiE9daaOwdRMrrfnRtn6slzrWBgHuF0dPY2yjo10/SWCI1ynfRPHt728g1jjolrETdxsCGXqDsj/pUwnV0XxM/7Q9SlnnZ/v0CJUafJF90LI7hf72kZVUg8ny5rseXEn8j841E7fP8pH2a9D0k8XQLFLolzD1FW/tmAuwl8SVr2YXz3RxtoG9NngLi1zjwB2efGTfMnmBtGxvker0CY2gfYf2RPVJGw4z+yCaRKQnMcGZIfa4j4F7iehMXHA9mkfArWpNCOk5JI0NZoPseMjcj04WApYTbEI+/x+1LEqffZqxYv6QB++/2SbqcnKKif9+YQrvHT8dTtUWheu/ansv3ZYT0AEwbMt+PLBF/bR/oB/xJype54rAemo5Jr+l3wxYwFtVX3o3MziZmTArfKqV+vw2NRb2yPXqC1ycFZa9yr3Z2oCvW1jZGEV/1xqidTao3RiFf8RilfXlM06BEV+s9VcMja/ZAZRZnlrfhH0keb3bnOdE2nWTCW++zZhx5UMIvc9c7P7LdewlvvfcanbyGEr5p4Gsnn3WH05lz72C7LxNPZWOg6udKXGe47Zy6biuNv7b4pTIa/IX525bOU+zDOsbesyTdS79dzi9xf45OdxK92DZmhnXq35I0TA087VzNHHotpxY69V0CbYJxSVt+V+I6x72JuD4jx75nCKOT5orct+xf/sS5wG2D5npjs99+r1xjckDHLh2Dy8eum5NUJ1bHqfdEfmIgQh9br5Mgsi+4K1lZWk7Zhseoa5qW27cptozHByXOMQHvvhn/tz39Y/Tjcq14M0afx3jX2PPcc2tiyL3ciLGPAEW6NzI8xnVGrgvuKs84x/ORGeM4Nt9IbnGCsW5d0+PHum9lrKN/fwdjne5Bo19V/fmpgX5DUvdgmvGt2De+rZdylfTL8RfmuFwfakegYn0Zu35T9fV9qqv/MiU2gP+uczOblDzVecRHT7ePO2f4Z/VPnt5QdfWk7Hpb1deTsusHVf97Q9XVU7PrSVWkB1exXthNc4P+712a/cO7m37x6OEmcz7cvfqpLtXXn7LrYVWk11axvlVIb0nfu/T9tgzn1Vsq0XX0JTAGLoVx8CLYHn4fdoRrYCd4MRwGl8MzVc9ggp6fCC+BeXA1LIaXwVI5r+vprj5z6ztNGewk64mq2676G9fBNLhOr3cDPBveAqfBDXCu6rXIvk24BG6C18I74I2q13IrvB/eDbfC5+ADqu/yMHwHPgL/DB+DDVzqBraFO2Fn1V8ZBZ+B4+GzcB58AV4Ed8PVqseyCb4EH4CvwzfhL+Eh+C78BH4A/wT3QTfAuA3bw7dgB/gyHA1fgRPhjbAAfggvhb+BN8ID8A54UMu31NX7uT6XlcE0XL6Wb4quM7aBibAtTIbttL47aD13hINgJzgOdoHnwO4=
*/