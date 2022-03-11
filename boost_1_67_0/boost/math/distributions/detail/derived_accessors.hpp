//  Copyright John Maddock 2006.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_DERIVED_HPP
#define BOOST_STATS_DERIVED_HPP

// This file implements various common properties of distributions
// that can be implemented in terms of other properties:
// variance OR standard deviation (see note below),
// hazard, cumulative hazard (chf), coefficient_of_variation.
//
// Note that while both variance and standard_deviation are provided
// here, each distribution MUST SPECIALIZE AT LEAST ONE OF THESE
// otherwise these two versions will just call each other over and over
// until stack space runs out ...

// Of course there may be more efficient means of implementing these
// that are specific to a particular distribution, but these generic
// versions give these properties "for free" with most distributions.
//
// In order to make use of this header, it must be included AT THE END
// of the distribution header, AFTER the distribution and its core
// property accessors have been defined: this is so that compilers
// that implement 2-phase lookup and early-type-checking of templates
// can find the definitions referred to herein.
//

#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4723) // potential divide by 0
// Suppressing spurious warning in coefficient_of_variation
#endif

namespace boost{ namespace math{

template <class Distribution>
typename Distribution::value_type variance(const Distribution& dist);

template <class Distribution>
inline typename Distribution::value_type standard_deviation(const Distribution& dist)
{
   BOOST_MATH_STD_USING  // ADL of sqrt.
   return sqrt(variance(dist));
}

template <class Distribution>
inline typename Distribution::value_type variance(const Distribution& dist)
{
   typename Distribution::value_type result = standard_deviation(dist);
   return result * result;
}

template <class Distribution, class RealType>
inline typename Distribution::value_type hazard(const Distribution& dist, const RealType& x)
{ // hazard function
  // http://www.itl.nist.gov/div898/handbook/eda/section3/eda362.htm#HAZ
   typedef typename Distribution::value_type value_type;
   typedef typename Distribution::policy_type policy_type;
   value_type p = cdf(complement(dist, x));
   value_type d = pdf(dist, x);
   if(d > p * tools::max_value<value_type>())
      return policies::raise_overflow_error<value_type>(
      "boost::math::hazard(const Distribution&, %1%)", 0, policy_type());
   if(d == 0)
   {
      // This protects against 0/0, but is it the right thing to do?
      return 0;
   }
   return d / p;
}

template <class Distribution, class RealType>
inline typename Distribution::value_type chf(const Distribution& dist, const RealType& x)
{ // cumulative hazard function.
  // http://www.itl.nist.gov/div898/handbook/eda/section3/eda362.htm#HAZ
   BOOST_MATH_STD_USING
   return -log(cdf(complement(dist, x)));
}

template <class Distribution>
inline typename Distribution::value_type coefficient_of_variation(const Distribution& dist)
{
   typedef typename Distribution::value_type value_type;
   typedef typename Distribution::policy_type policy_type;

   using std::abs;

   value_type m = mean(dist);
   value_type d = standard_deviation(dist);
   if((abs(m) < 1) && (d > abs(m) * tools::max_value<value_type>()))
   { // Checks too that m is not zero,
      return policies::raise_overflow_error<value_type>("boost::math::coefficient_of_variation(const Distribution&, %1%)", 0, policy_type());
   }
   return d / m; // so MSVC warning on zerodivide is spurious, and suppressed.
}
//
// Next follow overloads of some of the standard accessors with mixed
// argument types. We just use a typecast to forward on to the "real"
// implementation with all arguments of the same type:
//
template <class Distribution, class RealType>
inline typename Distribution::value_type pdf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return pdf(dist, static_cast<value_type>(x));
}
template <class Distribution, class RealType>
inline typename Distribution::value_type cdf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return cdf(dist, static_cast<value_type>(x));
}
template <class Distribution, class RealType>
inline typename Distribution::value_type quantile(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return quantile(dist, static_cast<value_type>(x));
}
/*
template <class Distribution, class RealType>
inline typename Distribution::value_type chf(const Distribution& dist, const RealType& x)
{
   typedef typename Distribution::value_type value_type;
   return chf(dist, static_cast<value_type>(x));
}
*/
template <class Distribution, class RealType>
inline typename Distribution::value_type cdf(const complemented2_type<Distribution, RealType>& c)
{
   typedef typename Distribution::value_type value_type;
   return cdf(complement(c.dist, static_cast<value_type>(c.param)));
}

template <class Distribution, class RealType>
inline typename Distribution::value_type quantile(const complemented2_type<Distribution, RealType>& c)
{
   typedef typename Distribution::value_type value_type;
   return quantile(complement(c.dist, static_cast<value_type>(c.param)));
}

template <class Dist>
inline typename Dist::value_type median(const Dist& d)
{ // median - default definition for those distributions for which a
  // simple closed form is not known,
  // and for which a domain_error and/or NaN generating function is NOT defined.
  typedef typename Dist::value_type value_type;
  return quantile(d, static_cast<value_type>(0.5f));
}

} // namespace math
} // namespace boost


#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif // BOOST_STATS_DERIVED_HPP

/* derived_accessors.hpp
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
*/