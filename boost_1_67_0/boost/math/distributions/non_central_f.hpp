// boost\math\distributions\non_central_f.hpp

// Copyright John Maddock 2008.

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_SPECIAL_NON_CENTRAL_F_HPP
#define BOOST_MATH_SPECIAL_NON_CENTRAL_F_HPP

#include <boost/math/distributions/non_central_beta.hpp>
#include <boost/math/distributions/detail/generic_mode.hpp>
#include <boost/math/special_functions/pow.hpp>

namespace boost
{
   namespace math
   {
      template <class RealType = double, class Policy = policies::policy<> >
      class non_central_f_distribution
      {
      public:
         typedef RealType value_type;
         typedef Policy policy_type;

         non_central_f_distribution(RealType v1_, RealType v2_, RealType lambda) : v1(v1_), v2(v2_), ncp(lambda)
         {
            const char* function = "boost::math::non_central_f_distribution<%1%>::non_central_f_distribution(%1%,%1%)";
            RealType r;
            detail::check_df(
               function,
               v1, &r, Policy());
            detail::check_df(
               function,
               v2, &r, Policy());
            detail::check_non_centrality(
               function,
               lambda,
               &r,
               Policy());
         } // non_central_f_distribution constructor.

         RealType degrees_of_freedom1()const
         {
            return v1;
         }
         RealType degrees_of_freedom2()const
         {
            return v2;
         }
         RealType non_centrality() const
         { // Private data getter function.
            return ncp;
         }
      private:
         // Data member, initialized by constructor.
         RealType v1;   // alpha.
         RealType v2;   // beta.
         RealType ncp; // non-centrality parameter
      }; // template <class RealType, class Policy> class non_central_f_distribution

      typedef non_central_f_distribution<double> non_central_f; // Reserved name of type double.

      // Non-member functions to give properties of the distribution.

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> range(const non_central_f_distribution<RealType, Policy>& /* dist */)
      { // Range of permissible values for random variable k.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
      }

      template <class RealType, class Policy>
      inline const std::pair<RealType, RealType> support(const non_central_f_distribution<RealType, Policy>& /* dist */)
      { // Range of supported values for random variable k.
         // This is range where cdf rises from 0 to 1, and outside it, the pdf is zero.
         using boost::math::tools::max_value;
         return std::pair<RealType, RealType>(static_cast<RealType>(0), max_value<RealType>());
      }

      template <class RealType, class Policy>
      inline RealType mean(const non_central_f_distribution<RealType, Policy>& dist)
      {
         const char* function = "mean(non_central_f_distribution<%1%> const&)";
         RealType v1 = dist.degrees_of_freedom1();
         RealType v2 = dist.degrees_of_freedom2();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            v1, &r, Policy())
               ||
            !detail::check_df(
               function,
               v2, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
               return r;
         if(v2 <= 2)
            return policies::raise_domain_error(
               function,
               "Second degrees of freedom parameter was %1%, but must be > 2 !",
               v2, Policy());
         return v2 * (v1 + l) / (v1 * (v2 - 2));
      } // mean

      template <class RealType, class Policy>
      inline RealType mode(const non_central_f_distribution<RealType, Policy>& dist)
      { // mode.
         static const char* function = "mode(non_central_chi_squared_distribution<%1%> const&)";

         RealType n = dist.degrees_of_freedom1();
         RealType m = dist.degrees_of_freedom2();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            n, &r, Policy())
               ||
            !detail::check_df(
               function,
               m, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
               return r;
         RealType guess = m > 2 ? RealType(m * (n + l) / (n * (m - 2))) : RealType(1);
         return detail::generic_find_mode(
            dist,
            guess,
            function);
      }

      template <class RealType, class Policy>
      inline RealType variance(const non_central_f_distribution<RealType, Policy>& dist)
      { // variance.
         const char* function = "variance(non_central_f_distribution<%1%> const&)";
         RealType n = dist.degrees_of_freedom1();
         RealType m = dist.degrees_of_freedom2();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            n, &r, Policy())
               ||
            !detail::check_df(
               function,
               m, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
               return r;
         if(m <= 4)
            return policies::raise_domain_error(
               function,
               "Second degrees of freedom parameter was %1%, but must be > 4 !",
               m, Policy());
         RealType result = 2 * m * m * ((n + l) * (n + l)
            + (m - 2) * (n + 2 * l));
         result /= (m - 4) * (m - 2) * (m - 2) * n * n;
         return result;
      }

      // RealType standard_deviation(const non_central_f_distribution<RealType, Policy>& dist)
      // standard_deviation provided by derived accessors.

      template <class RealType, class Policy>
      inline RealType skewness(const non_central_f_distribution<RealType, Policy>& dist)
      { // skewness = sqrt(l).
         const char* function = "skewness(non_central_f_distribution<%1%> const&)";
         BOOST_MATH_STD_USING
         RealType n = dist.degrees_of_freedom1();
         RealType m = dist.degrees_of_freedom2();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            n, &r, Policy())
               ||
            !detail::check_df(
               function,
               m, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
               return r;
         if(m <= 6)
            return policies::raise_domain_error(
               function,
               "Second degrees of freedom parameter was %1%, but must be > 6 !",
               m, Policy());
         RealType result = 2 * constants::root_two<RealType>();
         result *= sqrt(m - 4);
         result *= (n * (m + n - 2) *(m + 2 * n - 2)
            + 3 * (m + n - 2) * (m + 2 * n - 2) * l
            + 6 * (m + n - 2) * l * l + 2 * l * l * l);
         result /= (m - 6) * pow(n * (m + n - 2) + 2 * (m + n - 2) * l + l * l, RealType(1.5f));
         return result;
      }

      template <class RealType, class Policy>
      inline RealType kurtosis_excess(const non_central_f_distribution<RealType, Policy>& dist)
      {
         const char* function = "kurtosis_excess(non_central_f_distribution<%1%> const&)";
         BOOST_MATH_STD_USING
         RealType n = dist.degrees_of_freedom1();
         RealType m = dist.degrees_of_freedom2();
         RealType l = dist.non_centrality();
         RealType r;
         if(!detail::check_df(
            function,
            n, &r, Policy())
               ||
            !detail::check_df(
               function,
               m, &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               l,
               &r,
               Policy()))
               return r;
         if(m <= 8)
            return policies::raise_domain_error(
               function,
               "Second degrees of freedom parameter was %1%, but must be > 8 !",
               m, Policy());
         RealType l2 = l * l;
         RealType l3 = l2 * l;
         RealType l4 = l2 * l2;
         RealType result = (3 * (m - 4) * (n * (m + n - 2)
            * (4 * (m - 2) * (m - 2)
            + (m - 2) * (m + 10) * n
            + (10 + m) * n * n)
            + 4 * (m + n - 2) * (4 * (m - 2) * (m - 2)
            + (m - 2) * (10 + m) * n
            + (10 + m) * n * n) * l + 2 * (10 + m)
            * (m + n - 2) * (2 * m + 3 * n - 4) * l2
            + 4 * (10 + m) * (-2 + m + n) * l3
            + (10 + m) * l4))
            /
            ((-8 + m) * (-6 + m) * boost::math::pow<2>(n * (-2 + m + n)
            + 2 * (-2 + m + n) * l + l2));
            return result;
      } // kurtosis_excess

      template <class RealType, class Policy>
      inline RealType kurtosis(const non_central_f_distribution<RealType, Policy>& dist)
      {
         return kurtosis_excess(dist) + 3;
      }

      template <class RealType, class Policy>
      inline RealType pdf(const non_central_f_distribution<RealType, Policy>& dist, const RealType& x)
      { // Probability Density/Mass Function.
         typedef typename policies::evaluation<RealType, Policy>::type value_type;
         typedef typename policies::normalise<
            Policy,
            policies::promote_float<false>,
            policies::promote_double<false>,
            policies::discrete_quantile<>,
            policies::assert_undefined<> >::type forwarding_policy;

         value_type alpha = dist.degrees_of_freedom1() / 2;
         value_type beta = dist.degrees_of_freedom2() / 2;
         value_type y = x * alpha / beta;
         value_type r = pdf(boost::math::non_central_beta_distribution<value_type, forwarding_policy>(alpha, beta, dist.non_centrality()), y / (1 + y));
         return policies::checked_narrowing_cast<RealType, forwarding_policy>(
            r * (dist.degrees_of_freedom1() / dist.degrees_of_freedom2()) / ((1 + y) * (1 + y)),
            "pdf(non_central_f_distribution<%1%>, %1%)");
      } // pdf

      template <class RealType, class Policy>
      RealType cdf(const non_central_f_distribution<RealType, Policy>& dist, const RealType& x)
      {
         const char* function = "cdf(const non_central_f_distribution<%1%>&, %1%)";
         RealType r;
         if(!detail::check_df(
            function,
            dist.degrees_of_freedom1(), &r, Policy())
               ||
            !detail::check_df(
               function,
               dist.degrees_of_freedom2(), &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               dist.non_centrality(),
               &r,
               Policy()))
               return r;

         if((x < 0) || !(boost::math::isfinite)(x))
         {
            return policies::raise_domain_error<RealType>(
               function, "Random Variable parameter was %1%, but must be > 0 !", x, Policy());
         }

         RealType alpha = dist.degrees_of_freedom1() / 2;
         RealType beta = dist.degrees_of_freedom2() / 2;
         RealType y = x * alpha / beta;
         RealType c = y / (1 + y);
         RealType cp = 1 / (1 + y);
         //
         // To ensure accuracy, we pass both x and 1-x to the
         // non-central beta cdf routine, this ensures accuracy
         // even when we compute x to be ~ 1:
         //
         r = detail::non_central_beta_cdf(c, cp, alpha, beta,
            dist.non_centrality(), false, Policy());
         return r;
      } // cdf

      template <class RealType, class Policy>
      RealType cdf(const complemented2_type<non_central_f_distribution<RealType, Policy>, RealType>& c)
      { // Complemented Cumulative Distribution Function
         const char* function = "cdf(complement(const non_central_f_distribution<%1%>&, %1%))";
         RealType r;
         if(!detail::check_df(
            function,
            c.dist.degrees_of_freedom1(), &r, Policy())
               ||
            !detail::check_df(
               function,
               c.dist.degrees_of_freedom2(), &r, Policy())
               ||
            !detail::check_non_centrality(
               function,
               c.dist.non_centrality(),
               &r,
               Policy()))
               return r;

         if((c.param < 0) || !(boost::math::isfinite)(c.param))
         {
            return policies::raise_domain_error<RealType>(
               function, "Random Variable parameter was %1%, but must be > 0 !", c.param, Policy());
         }

         RealType alpha = c.dist.degrees_of_freedom1() / 2;
         RealType beta = c.dist.degrees_of_freedom2() / 2;
         RealType y = c.param * alpha / beta;
         RealType x = y / (1 + y);
         RealType cx = 1 / (1 + y);
         //
         // To ensure accuracy, we pass both x and 1-x to the
         // non-central beta cdf routine, this ensures accuracy
         // even when we compute x to be ~ 1:
         //
         r = detail::non_central_beta_cdf(x, cx, alpha, beta,
            c.dist.non_centrality(), true, Policy());
         return r;
      } // ccdf

      template <class RealType, class Policy>
      inline RealType quantile(const non_central_f_distribution<RealType, Policy>& dist, const RealType& p)
      { // Quantile (or Percent Point) function.
         RealType alpha = dist.degrees_of_freedom1() / 2;
         RealType beta = dist.degrees_of_freedom2() / 2;
         RealType x = quantile(boost::math::non_central_beta_distribution<RealType, Policy>(alpha, beta, dist.non_centrality()), p);
         if(x == 1)
            return policies::raise_overflow_error<RealType>(
               "quantile(const non_central_f_distribution<%1%>&, %1%)",
               "Result of non central F quantile is too large to represent.",
               Policy());
         return (x / (1 - x)) * (dist.degrees_of_freedom2() / dist.degrees_of_freedom1());
      } // quantile

      template <class RealType, class Policy>
      inline RealType quantile(const complemented2_type<non_central_f_distribution<RealType, Policy>, RealType>& c)
      { // Quantile (or Percent Point) function.
         RealType alpha = c.dist.degrees_of_freedom1() / 2;
         RealType beta = c.dist.degrees_of_freedom2() / 2;
         RealType x = quantile(complement(boost::math::non_central_beta_distribution<RealType, Policy>(alpha, beta, c.dist.non_centrality()), c.param));
         if(x == 1)
            return policies::raise_overflow_error<RealType>(
               "quantile(complement(const non_central_f_distribution<%1%>&, %1%))",
               "Result of non central F quantile is too large to represent.",
               Policy());
         return (x / (1 - x)) * (c.dist.degrees_of_freedom2() / c.dist.degrees_of_freedom1());
      } // quantile complement.

   } // namespace math
} // namespace boost

// This include must be at the end, *after* the accessors
// for this distribution have been defined, in order to
// keep compilers that support two-phase lookup happy.
#include <boost/math/distributions/detail/derived_accessors.hpp>

#endif // BOOST_MATH_SPECIAL_NON_CENTRAL_F_HPP




/* non_central_f.hpp
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
*/