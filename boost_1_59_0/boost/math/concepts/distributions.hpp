//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// distributions.hpp provides definitions of the concept of a distribution
// and non-member accessor functions that must be implemented by all distributions.
// This is used to verify that
// all the features of a distributions have been fully implemented.

#ifndef BOOST_MATH_DISTRIBUTION_CONCEPT_HPP
#define BOOST_MATH_DISTRIBUTION_CONCEPT_HPP

#ifndef BOOST_MATH_STANDALONE

#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/fwd.hpp>
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4510)
#pragma warning(disable: 4610)
#pragma warning(disable: 4189) // local variable is initialized but not referenced.
#endif
#include <boost/concept_check.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <utility>

namespace boost{
namespace math{

namespace concepts
{
// Begin by defining a concept archetype
// for a distribution class:
//
template <class RealType>
class distribution_archetype
{
public:
   typedef RealType value_type;

   distribution_archetype(const distribution_archetype&); // Copy constructible.
   distribution_archetype& operator=(const distribution_archetype&); // Assignable.

   // There is no default constructor,
   // but we need a way to instantiate the archetype:
   static distribution_archetype& get_object()
   {
      // will never get caled:
      return *reinterpret_cast<distribution_archetype*>(0);
   }
}; // template <class RealType>class distribution_archetype

// Non-member accessor functions:
// (This list defines the functions that must be implemented by all distributions).

template <class RealType>
RealType pdf(const distribution_archetype<RealType>& dist, const RealType& x);

template <class RealType>
RealType cdf(const distribution_archetype<RealType>& dist, const RealType& x);

template <class RealType>
RealType quantile(const distribution_archetype<RealType>& dist, const RealType& p);

template <class RealType>
RealType cdf(const complemented2_type<distribution_archetype<RealType>, RealType>& c);

template <class RealType>
RealType quantile(const complemented2_type<distribution_archetype<RealType>, RealType>& c);

template <class RealType>
RealType mean(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType standard_deviation(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType variance(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType hazard(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType chf(const distribution_archetype<RealType>& dist);
// http://en.wikipedia.org/wiki/Characteristic_function_%28probability_theory%29

template <class RealType>
RealType coefficient_of_variation(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType mode(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType skewness(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType kurtosis_excess(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType kurtosis(const distribution_archetype<RealType>& dist);

template <class RealType>
RealType median(const distribution_archetype<RealType>& dist);

template <class RealType>
std::pair<RealType, RealType> range(const distribution_archetype<RealType>& dist);

template <class RealType>
std::pair<RealType, RealType> support(const distribution_archetype<RealType>& dist);

//
// Next comes the concept checks for verifying that a class
// fulfils the requirements of a Distribution:
//
template <class Distribution>
struct DistributionConcept
{
   typedef typename Distribution::value_type value_type;

   void constraints()
   {
      function_requires<CopyConstructibleConcept<Distribution> >();
      function_requires<AssignableConcept<Distribution> >();

      const Distribution& dist = DistributionConcept<Distribution>::get_object();

      value_type x = 0;
       // The result values are ignored in all these checks.
       value_type v = cdf(dist, x);
      v = cdf(complement(dist, x));
      suppress_unused_variable_warning(v);
      v = pdf(dist, x);
      suppress_unused_variable_warning(v);
      v = quantile(dist, x);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, x));
      suppress_unused_variable_warning(v);
      v = mean(dist);
      suppress_unused_variable_warning(v);
      v = mode(dist);
      suppress_unused_variable_warning(v);
      v = standard_deviation(dist);
      suppress_unused_variable_warning(v);
      v = variance(dist);
      suppress_unused_variable_warning(v);
      v = hazard(dist, x);
      suppress_unused_variable_warning(v);
      v = chf(dist, x);
      suppress_unused_variable_warning(v);
      v = coefficient_of_variation(dist);
      suppress_unused_variable_warning(v);
      v = skewness(dist);
      suppress_unused_variable_warning(v);
      v = kurtosis(dist);
      suppress_unused_variable_warning(v);
      v = kurtosis_excess(dist);
      suppress_unused_variable_warning(v);
      v = median(dist);
      suppress_unused_variable_warning(v);
      std::pair<value_type, value_type> pv;
      pv = range(dist);
      suppress_unused_variable_warning(pv);
      pv = support(dist);
      suppress_unused_variable_warning(pv);

      float f = 1;
      v = cdf(dist, f);
      suppress_unused_variable_warning(v);
      v = cdf(complement(dist, f));
      suppress_unused_variable_warning(v);
      v = pdf(dist, f);
      suppress_unused_variable_warning(v);
      v = quantile(dist, f);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, f));
      suppress_unused_variable_warning(v);
      v = hazard(dist, f);
      suppress_unused_variable_warning(v);
      v = chf(dist, f);
      suppress_unused_variable_warning(v);
      double d = 1;
      v = cdf(dist, d);
      suppress_unused_variable_warning(v);
      v = cdf(complement(dist, d));
      suppress_unused_variable_warning(v);
      v = pdf(dist, d);
      suppress_unused_variable_warning(v);
      v = quantile(dist, d);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, d));
      suppress_unused_variable_warning(v);
      v = hazard(dist, d);
      suppress_unused_variable_warning(v);
      v = chf(dist, d);
      suppress_unused_variable_warning(v);
#ifndef TEST_MPFR
      long double ld = 1;
      v = cdf(dist, ld);
      suppress_unused_variable_warning(v);
      v = cdf(complement(dist, ld));
      suppress_unused_variable_warning(v);
      v = pdf(dist, ld);
      suppress_unused_variable_warning(v);
      v = quantile(dist, ld);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, ld));
      suppress_unused_variable_warning(v);
      v = hazard(dist, ld);
      suppress_unused_variable_warning(v);
      v = chf(dist, ld);
      suppress_unused_variable_warning(v);
#endif
      int i = 1;
      v = cdf(dist, i);
      suppress_unused_variable_warning(v);
      v = cdf(complement(dist, i));
      suppress_unused_variable_warning(v);
      v = pdf(dist, i);
      suppress_unused_variable_warning(v);
      v = quantile(dist, i);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, i));
      suppress_unused_variable_warning(v);
      v = hazard(dist, i);
      suppress_unused_variable_warning(v);
      v = chf(dist, i);
      suppress_unused_variable_warning(v);
      unsigned long li = 1;
      v = cdf(dist, li);
      suppress_unused_variable_warning(v);
      v = cdf(complement(dist, li));
      suppress_unused_variable_warning(v);
      v = pdf(dist, li);
      suppress_unused_variable_warning(v);
      v = quantile(dist, li);
      suppress_unused_variable_warning(v);
      v = quantile(complement(dist, li));
      suppress_unused_variable_warning(v);
      v = hazard(dist, li);
      suppress_unused_variable_warning(v);
      v = chf(dist, li);
      suppress_unused_variable_warning(v);
      test_extra_members(dist);
   }
   template <class D>
   static void test_extra_members(const D&)
   {}
   template <class R, class P>
   static void test_extra_members(const boost::math::bernoulli_distribution<R, P>& d)
   {
      value_type r = d.success_fraction();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::beta_distribution<R, P>& d)
   {
      value_type r1 = d.alpha();
      value_type r2 = d.beta();
      r1 = boost::math::beta_distribution<R, P>::find_alpha(r1, r2);
      suppress_unused_variable_warning(r1);
      r1 = boost::math::beta_distribution<R, P>::find_beta(r1, r2);
      suppress_unused_variable_warning(r1);
      r1 = boost::math::beta_distribution<R, P>::find_alpha(r1, r2, r1);
      suppress_unused_variable_warning(r1);
      r1 = boost::math::beta_distribution<R, P>::find_beta(r1, r2, r1);
      suppress_unused_variable_warning(r1);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::binomial_distribution<R, P>& d)
   {
      value_type r = d.success_fraction();
      r = d.trials();
      r = Distribution::find_lower_bound_on_p(r, r, r);
      r = Distribution::find_lower_bound_on_p(r, r, r, Distribution::clopper_pearson_exact_interval);
      r = Distribution::find_lower_bound_on_p(r, r, r, Distribution::jeffreys_prior_interval);
      r = Distribution::find_upper_bound_on_p(r, r, r);
      r = Distribution::find_upper_bound_on_p(r, r, r, Distribution::clopper_pearson_exact_interval);
      r = Distribution::find_upper_bound_on_p(r, r, r, Distribution::jeffreys_prior_interval);
      r = Distribution::find_minimum_number_of_trials(r, r, r);
      r = Distribution::find_maximum_number_of_trials(r, r, r);
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::cauchy_distribution<R, P>& d)
   {
      value_type r = d.location();
      r = d.scale();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::chi_squared_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom();
      r = Distribution::find_degrees_of_freedom(r, r, r, r);
      r = Distribution::find_degrees_of_freedom(r, r, r, r, r);
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::exponential_distribution<R, P>& d)
   {
      value_type r = d.lambda();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::extreme_value_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.location();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::fisher_f_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom1();
      r = d.degrees_of_freedom2();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::gamma_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.shape();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::inverse_chi_squared_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.degrees_of_freedom();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::inverse_gamma_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.shape();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::hypergeometric_distribution<R, P>& d)
   {
      unsigned u = d.defective();
      u = d.sample_count();
      u = d.total();
      suppress_unused_variable_warning(u);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::laplace_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.location();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::logistic_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.location();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::lognormal_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.location();
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::negative_binomial_distribution<R, P>& d)
   {
      value_type r = d.success_fraction();
      r = d.successes();
      r = Distribution::find_lower_bound_on_p(r, r, r);
      r = Distribution::find_upper_bound_on_p(r, r, r);
      r = Distribution::find_minimum_number_of_trials(r, r, r);
      r = Distribution::find_maximum_number_of_trials(r, r, r);
      suppress_unused_variable_warning(r);
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::non_central_beta_distribution<R, P>& d)
   {
      value_type r1 = d.alpha();
      value_type r2 = d.beta();
      r1 = d.non_centrality();
      (void)r1; // warning suppression
      (void)r2; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::non_central_chi_squared_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom();
      r = d.non_centrality();
      r = Distribution::find_degrees_of_freedom(r, r, r);
      r = Distribution::find_degrees_of_freedom(boost::math::complement(r, r, r));
      r = Distribution::find_non_centrality(r, r, r);
      r = Distribution::find_non_centrality(boost::math::complement(r, r, r));
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::non_central_f_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom1();
      r = d.degrees_of_freedom2();
      r = d.non_centrality();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::non_central_t_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom();
      r = d.non_centrality();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::normal_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.location();
      r = d.mean();
      r = d.standard_deviation();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::pareto_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.shape();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::poisson_distribution<R, P>& d)
   {
      value_type r = d.mean();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::rayleigh_distribution<R, P>& d)
   {
      value_type r = d.sigma();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::students_t_distribution<R, P>& d)
   {
      value_type r = d.degrees_of_freedom();
      r = d.find_degrees_of_freedom(r, r, r, r);
      r = d.find_degrees_of_freedom(r, r, r, r, r);
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::triangular_distribution<R, P>& d)
   {
      value_type r = d.lower();
      r = d.mode();
      r = d.upper();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::weibull_distribution<R, P>& d)
   {
      value_type r = d.scale();
      r = d.shape();
      (void)r; // warning suppression
   }
   template <class R, class P>
   static void test_extra_members(const boost::math::uniform_distribution<R, P>& d)
   {
      value_type r = d.lower();
      r = d.upper();
      (void)r; // warning suppression
   }
private:
   static Distribution* pd;
   static Distribution& get_object()
   {
      // In reality this will never get called:
      return *pd;
   }
}; // struct DistributionConcept

template <class Distribution>
Distribution* DistributionConcept<Distribution>::pd = 0;

} // namespace concepts
} // namespace math
} // namespace boost

#else
#error This header can not be used in standalone mode.
#endif // BOOST_MATH_STANDALONE

#endif // BOOST_MATH_DISTRIBUTION_CONCEPT_HPP


/* distributions.hpp
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
*/