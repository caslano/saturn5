// Copyright 2008 Gautam Sewani
// Copyright 2008 John Maddock
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

      hypergeometric_distribution(unsigned r, unsigned n, unsigned N) // Constructor.
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

      unsigned defective()const
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
      unsigned m_n;  // number of items picked
      unsigned m_N; // number of "total" items
      unsigned m_r; // number of "defective" items

   }; // class hypergeometric_distribution

   typedef hypergeometric_distribution<double> hypergeometric;

   template <class RealType, class Policy>
   inline const std::pair<unsigned, unsigned> range(const hypergeometric_distribution<RealType, Policy>& dist)
   { // Range of permissible values for random variable x.
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4267)
#endif
      unsigned r = dist.defective();
      unsigned n = dist.sample_count();
      unsigned N = dist.total();
      unsigned l = static_cast<unsigned>((std::max)(0, (int)(n + r) - (int)(N)));
      unsigned u = (std::min)(r, n);
      return std::pair<unsigned, unsigned>(l, u);
#ifdef BOOST_MSVC
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
      RealType r = static_cast<RealType>(dist.defective());
      RealType n = static_cast<RealType>(dist.sample_count());
      RealType N = static_cast<RealType>(dist.total());
      RealType t1 = N * N * (N - 1) / (r * (N - 2) * (N - 3) * (N - r));
      RealType t2 = (N * (N + 1) - 6 * N * (N - r)) / (n * (N - n))
         + 3 * r * (N - r) * (N + 6) / (N * N) - 6;
      return t1 * t2;
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