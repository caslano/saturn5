// Copyright 2008 Gautam Sewani
// Copyright 2008 John Maddock
// Copyright 2021 Paul A. Bristow
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_DISTRIBUTIONS_HYPERGEOMETRIC_HPP
#define BOOST_MATH_DISTRIBUTIONS_HYPERGEOMETRIC_HPP

#include <boost/math/distributions/detail/common_error_handling.hpp>
#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/detail/hypergeometric_pdf.hpp>
#include <boost/math/distributions/detail/hypergeometric_cdf.hpp>
#include <boost/math/distributions/detail/hypergeometric_quantile.hpp>
#include <boost/math/special_functions/fpclassify.hpp>

namespace boost { namespace math {

   template <class RealType = double, class Policy = policies::policy<> >
   class hypergeometric_distribution
   {
   public:
      typedef RealType value_type;
      typedef Policy policy_type;

      hypergeometric_distribution(unsigned r, unsigned n, unsigned N) // Constructor. r=defective/failures/success, n=trials/draws, N=total population.
         : m_n(n), m_N(N), m_r(r)
      {
         static const char* function = "boost::math::hypergeometric_distribution<%1%>::hypergeometric_distribution";
         RealType ret;
         check_params(function, &ret);
      }
      // Accessor functions.
      unsigned total()const
      {
         return m_N;
      }

      unsigned defective()const // successes/failures/events
      {
         return m_r;
      }

      unsigned sample_count()const
      {
         return m_n;
      }

      bool check_params(const char* function, RealType* result)const
      {
         if(m_r > m_N)
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Parameter r out of range: must be <= N but got %1%", static_cast<RealType>(m_r), Policy());
            return false;
         }
         if(m_n > m_N)
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Parameter n out of range: must be <= N but got %1%", static_cast<RealType>(m_n), Policy());
            return false;
         }
         return true;
      }
      bool check_x(unsigned x, const char* function, RealType* result)const
      {
         if(x < static_cast<unsigned>((std::max)(0, (int)(m_n + m_r) - (int)(m_N))))
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Random variable out of range: must be > 0 and > m + r - N but got %1%", static_cast<RealType>(x), Policy());
            return false;
         }
         if(x > (std::min)(m_r, m_n))
         {
            *result = boost::math::policies::raise_domain_error<RealType>(
               function, "Random variable out of range: must be less than both n and r but got %1%", static_cast<RealType>(x), Policy());
            return false;
         }
         return true;
      }

   private:
      // Data members:
      unsigned m_n;  // number of items picked or drawn.
      unsigned m_N; // number of "total" items.
      unsigned m_r; // number of "defective/successes/failures/events items.

   }; // class hypergeometric_distribution

   typedef hypergeometric_distribution<double> hypergeometric;

   template <class RealType, class Policy>
   inline const std::pair<unsigned, unsigned> range(const hypergeometric_distribution<RealType, Policy>& dist)
   { // Range of permissible values for random variable x.
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
      unsigned r = dist.defective();
      unsigned n = dist.sample_count();
      unsigned N = dist.total();
      unsigned l = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
      unsigned u = (std::min)(r, n);
      return std::pair<unsigned, unsigned>(l, u);
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
   }

   template <class RealType, class Policy>
   inline const std::pair<unsigned, unsigned> support(const hypergeometric_distribution<RealType, Policy>& d)
   { 
      return range(d);
   }

   template <class RealType, class Policy>
   inline RealType pdf(const hypergeometric_distribution<RealType, Policy>& dist, const unsigned& x)
   {
      static const char* function = "boost::math::pdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!dist.check_params(function, &result))
         return result;
      if(!dist.check_x(x, function, &result))
         return result;

      return boost::math::detail::hypergeometric_pdf<RealType>(
         x, dist.defective(), dist.sample_count(), dist.total(), Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType pdf(const hypergeometric_distribution<RealType, Policy>& dist, const U& x)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::pdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(x);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return pdf(dist, u);
   }

   template <class RealType, class Policy>
   inline RealType cdf(const hypergeometric_distribution<RealType, Policy>& dist, const unsigned& x)
   {
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!dist.check_params(function, &result))
         return result;
      if(!dist.check_x(x, function, &result))
         return result;

      return boost::math::detail::hypergeometric_cdf<RealType>(
         x, dist.defective(), dist.sample_count(), dist.total(), false, Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType cdf(const hypergeometric_distribution<RealType, Policy>& dist, const U& x)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(x);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return cdf(dist, u);
   }

   template <class RealType, class Policy>
   inline RealType cdf(const complemented2_type<hypergeometric_distribution<RealType, Policy>, unsigned>& c)
   {
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType result = 0;
      if(!c.dist.check_params(function, &result))
         return result;
      if(!c.dist.check_x(c.param, function, &result))
         return result;

      return boost::math::detail::hypergeometric_cdf<RealType>(
         c.param, c.dist.defective(), c.dist.sample_count(), c.dist.total(), true, Policy());
   }

   template <class RealType, class Policy, class U>
   inline RealType cdf(const complemented2_type<hypergeometric_distribution<RealType, Policy>, U>& c)
   {
      BOOST_MATH_STD_USING
      static const char* function = "boost::math::cdf(const hypergeometric_distribution<%1%>&, const %1%&)";
      RealType r = static_cast<RealType>(c.param);
      unsigned u = itrunc(r, typename policies::normalise<Policy, policies::rounding_error<policies::ignore_error> >::type());
      if(u != r)
      {
         return boost::math::policies::raise_domain_error<RealType>(
            function, "Random variable out of range: must be an integer but got %1%", r, Policy());
      }
      return cdf(complement(c.dist, u));
   }

   template <class RealType, class Policy>
   inline RealType quantile(const hypergeometric_distribution<RealType, Policy>& dist, const RealType& p)
   {
      BOOST_MATH_STD_USING // for ADL of std functions

         // Checking function argument
         RealType result = 0;
      const char* function = "boost::math::quantile(const hypergeometric_distribution<%1%>&, %1%)";
      if (false == dist.check_params(function, &result)) return result;
      if(false == detail::check_probability(function, p, &result, Policy())) return result;

      return static_cast<RealType>(detail::hypergeometric_quantile(p, RealType(1 - p), dist.defective(), dist.sample_count(), dist.total(), Policy()));
   } // quantile

   template <class RealType, class Policy>
   inline RealType quantile(const complemented2_type<hypergeometric_distribution<RealType, Policy>, RealType>& c)
   {
      BOOST_MATH_STD_USING // for ADL of std functions

      // Checking function argument
      RealType result = 0;
      const char* function = "quantile(const complemented2_type<hypergeometric_distribution<%1%>, %1%>&)";
      if (false == c.dist.check_params(function, &result)) return result;
      if(false == detail::check_probability(function, c.param, &result, Policy())) return result;

      return static_cast<RealType>(detail::hypergeometric_quantile(RealType(1 - c.param), c.param, c.dist.defective(), c.dist.sample_count(), c.dist.total(), Policy()));
   } // quantile

   // https://www.wolframalpha.com/input/?i=kurtosis+hypergeometric+distribution 

   template <class RealType, class Policy>
   inline RealType mean(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      return static_cast<RealType>(dist.defective() * dist.sample_count()) / dist.total();
   } // RealType mean(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType variance(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return n * r  * (N - r) * (N - n) / (N * N * (N - 1));
   } // RealType variance(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType mode(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      BOOST_MATH_STD_USING
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return floor((r + 1) * (n + 1) / (N + 2));
   }

   template <class RealType, class Policy>
   inline RealType skewness(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      BOOST_MATH_STD_USING
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      return (N - 2 * r) * sqrt(N - 1) * (N - 2 * n) / (sqrt(n * r * (N - r) * (N - n)) * (N - 2));
   } // RealType skewness(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      // https://www.wolframalpha.com/input/?i=kurtosis+hypergeometric+distribution shown as plain text:
      //  mean | (m n)/N
      //  standard deviation | sqrt((m n(N - m) (N - n))/(N - 1))/N
      //  variance | (m n(1 - m/N) (N - n))/((N - 1) N)
      //  skewness | (sqrt(N - 1) (N - 2 m) (N - 2 n))/((N - 2) sqrt(m n(N - m) (N - n)))
      //  kurtosis | ((N - 1) N^2 ((3 m(N - m) (n^2 (-N) + (n - 2) N^2 + 6 n(N - n)))/N^2 - 6 n(N - n) + N(N + 1)))/(m n(N - 3) (N - 2) (N - m) (N - n))
     // Kurtosis[HypergeometricDistribution[n, m, N]]
      RealType m = static_cast<RealType>(dist.defective()); // Failures or success events. (Also symbols K or M are used).
      RealType n = static_cast<RealType>(dist.sample_count()); // draws or trials.
      RealType n2 = n * n; // n^2
      RealType N = static_cast<RealType>(dist.total()); // Total population from which n draws or trials are made. 
      RealType N2 = N * N; // N^2
      // result = ((N - 1) N^2 ((3 m(N - m) (n^2 (-N) + (n - 2) N^2 + 6 n(N - n)))/N^2 - 6 n(N - n) + N(N + 1)))/(m n(N - 3) (N - 2) (N - m) (N - n));
      RealType result = ((N-1)*N2*((3*m*(N-m)*(n2*(-N)+(n-2)*N2+6*n*(N-n)))/N2-6*n*(N-n)+N*(N+1)))/(m*n*(N-3)*(N-2)*(N-m)*(N-n));
      // Agrees with kurtosis hypergeometric distribution(50,200,500) kurtosis = 2.96917 
      // N[kurtosis[hypergeometricdistribution(50,200,500)], 55]  2.969174035736058474901169623721804275002985337280263464
      return result;
   } // RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)

   template <class RealType, class Policy>
   inline RealType kurtosis(const hypergeometric_distribution<RealType, Policy>& dist)
   {
      return kurtosis_excess(dist) + 3;
   } // RealType kurtosis_excess(const hypergeometric_distribution<RealType, Policy>& dist)
}} // namespaces

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // include guard

/* hypergeometric.hpp
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
*/