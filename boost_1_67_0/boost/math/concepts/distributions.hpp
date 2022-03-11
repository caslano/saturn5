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

#include <boost/math/distributions/complement.hpp>
#include <boost/math/distributions/fwd.hpp>
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4510)
#pragma warning(disable: 4610)
#pragma warning(disable: 4189) // local variable is initialized but not referenced.
#endif
#include <boost/concept_check.hpp>
#ifdef BOOST_MSVC
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

#endif // BOOST_MATH_DISTRIBUTION_CONCEPT_HPP


/* distributions.hpp
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
*/