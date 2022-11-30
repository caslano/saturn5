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

      #ifdef __cpp_deduction_guides
      template <class RealType>
      non_central_f_distribution(RealType,RealType,RealType)->non_central_f_distribution<typename boost::math::tools::promote_args<RealType>::type>;
      #endif

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