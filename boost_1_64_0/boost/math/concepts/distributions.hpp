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
N+ln7Q7h+vmpGO8Zofphtjr12/yHYsme9Bb047SgH+cw9PNDsXX9qG1Rdq7B+9GQfsLsSYqJeuaxoCePBT15hqGnaMqR1v/vZPCOxOuJtymY0JHXgo68FnTkHWUdaf3/zgbvSAY6oq/ciHryWdCTz4KefH+TnhbvEq6nNajD/iE9hdmM1Dr3s6Rt8lvQk9+CnvzD0NPPUbRNatu9wiHWU0CnJ7I3RdRPwIJ+Ahb0Exhl/aht0rt5Bu9HBaH6gf3H/PtRgXkdKQXmdaQURK+jaOqa1v/nh+voV+jcrtcRbDRqHfsuQ/J+ZEE/dgv6sQ9DP99lWNeP1v8XiMuQk9cPbzMx2WY7LejJaUFPzmHoaTjlqHySwXuSXk/uMlPftB4L+vFY0I9nlPWjtkVzdzN4P9LrB/YGs+NsXgs68lrQkXeUdaTWta5Cg/cjnY7IBmC6zfZZ0JPPgp58o6wntSwtLzIYRxrSkzY+b7Ys+S3oyG9BR/5R1pHaHr22u8EYEq8jbQw9sn4CFvQTsKCfwCjrR5uTNVm/ZxSN4U5Sz2rTj/ubmBs3Kd70eW3gjfq8tkLZeW38+r1isYx2TUb9uH1kGe0WZLSPgozeErGMTk1G/bh7ZBmdFmR0rkMZNZv0HmIZPZqMwnHziHJ6LMjpGQU5XXuK5fSK5TRdZr0W5PSuQznVMlswRSynTycnxq1Ny+izIKNvHcqo9j+pTrGMfp2MNO4cUT6/Bfn8oyDfjwL51gbHHkLko3FjE+tdAhbkCwxDvvZEc3Xx3VKD/nE3VT7BuK+JcqrsZl5OZbfo5Sw0WRf9Uw36SE1O3ZikCRntFmS0r0MZ1bxcWmbQRxrISF8WEeV0WpDTOQpydpWHy/kH6qRHk9N43LTbLuknLcjpGYac3XZzbU9bhVhOr05OGveMKJ/XgnzedSifWifd0wz6R518GLc03z9akNE3DBkLTfYfBdPDZZyUifYoREYadzQzb92CfP5hyDfDZF3MmiHOw4Amn27c0GSbE7AgZ2AYcprNx7ViORGATk53mal3cqXQvHxK4bqTT5u/XmnQP+rlw7id2e9kuwUZ7etQRrWsrtzLoH/UyUjjbqbbHKcFOZ3rUE41L5ftbfAdqck5NG5mNi89FmT0rEMZ1frYWWXwDanJyI97RZbPa0E+7zqU70dgUpzxfszifZeN9tW2vh/zXLZ/9ksL64987pFzm3ynv5ed9P6Nk433zxbvh219X22j/a3p7G/sQWZ8hruDOyPcT3zrCfi25Pj6tPDkfAHis0XgG5DEu73GB7czxRuBL4X4bFI+kCS8Mo7PsbNx+rbg+JxaeHI+l5Y+OZ9HEl4Fx9cmSd+2HJ9XC0/O16WlT87nk8SbzfH1aPHK+fxavHK+Pkm8W/PlT4tXzjegxivlg9vFON7N+fJHfOtL+UDEZ4vA5yC+cQK+XL5cSeLdkS9XxDcmQnheSXg78+VFwlfJlxeJ/rL48qKFJ+fza/qT8/VJ4t2KLy9avHK+ATVeOR8yzjjfJvPlwGEc7+58OXBQvkUIzyUJbx++HEj4duXbFwnfvnx5cRjreSJfXrTw5Hw+4rNF4OuRhFfOlxdJfkziy4GqZykfXJ6xvDl8e0B860v5QMRni8DnkMS7Dd8fafHK+VxavHI+jyReO19etHjlfF4tXjlflyTe7fjyosUr5+vR4pXz+fOMy4uTLy+SeKfw7QbxjYkQXkq+cbx78OUg3zjeEr4c5FO8EcLzEF9mhPc1r4Rvez4/JHxb8HqW8G3L61nlk78foPEiPml/DpLwbc7rT8KXy+tPwpfF60/jk7fjPgnfVrz+JHyzeP1J+Ny8/gqIT9rugiR8k3j9SfhyeP0=
*/