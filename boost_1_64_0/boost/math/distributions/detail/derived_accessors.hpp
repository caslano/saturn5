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
WxJaH8AgQ/m+3Tw5P539VbXNnHCJ6BqceN7JrIXimmjZs3apZYefKWP8I+bcTNmZNdG26k+ZiF9j4yd5jVgXOKLthPPya4N7i0j2V9ROsugei0oKta3Qhk05mPWZQ50j7ZG7XcI6INhi5nq7cRcG11Bq142L4VpmXSRB586rsGYYbudl0eX2q5vg8nHfJ03xXSpIP3YgqtrOicP3Tcq87FJPPofI+UYmn9lyXF/kc2XxOHdROO7DzCkH8380mH8iXxLMf/KUuKgW5fkv0/wnqtwR5EqDcg37GZnP4yNl4sn/0qBM/VQjM0rjSXImS/0UxQRIhBljTPp7dpHcSdtMDp6owrcAbO0UP8kfecZP8hzRxo5FH79efYhxc9vxdUTtZGTn5GZiVURGvRP2G29bmK2T/1fjRFcDd0Er3uWOu46sMM5ZmnHWGczx+NekTPnskXDN7fO1nrbxcWXz9D5Z4hdZZsptY5uRTfTI5hYULeRP63im8v72bBu/kPWPX9xDPOPX7+T8QObLonUNzayPGfsavu+zmnX05K7BsD0I2ZL5tygzvjq+sflruUYbs5Z+USr9FTfWYre6ln2M9K5xmfn5jy1rEtJGtayTvDpZpkzN+Ohvz5JX8q9rq5HtOUbX5+tp4oKHLxJJYVdrO/O2Z/89y9a2NB73hLobWh7e8V7SOVrTuUwTeC6DQiycDC8LTvadOJ0ZmYuzzPce0KFyWuka6jUStpWb7HRgzOUdFRdwA/a1LM2Hvy200jazQ843c+N5kprCbOoNuL248Hi6W84HPGu1OYuyPW0xaNsijsJvXI+8BsfA6JWXxEUPD/1zyu8ltaqwrh5aRy80dc/1OOZ6qit0o6QFc5FJoeOH9XhQc/1eia4HbQkWtGeuqDluBWNwj1OlzCcOPzNjzuKczKKseRlmPNb+yPkFOUut9yINr2W5U2Tn8JRqH2+Q9Y8JJQut64JG1nMPOrGeX7jdlUj/IM2efrhT/CRtvn5IGsL9SMtqQ5y5HxheRlnNDpUVrfD423duHlVS/uyBHC3KXmYaj+sp30L6sr3MVNZ7D63yWhzpIH+kw5SDlo1cT+9Rmucp9Y/P85WEL6wkz2g6yP2gQPKQxSsEbyoV5LnQl48xVchHkuajQNJs4texRNPd4Ph0X0y6V1aS7sKCQlGRq2p9EZe595VKXoOhc0sWZVWw/u3La1oV8mqpM/OczTXxM9eMaKtjG9rballl+S9ZPK+qeS+rRlst8+X7SPw/lm9bW/XmOT3++DxfSviNleRZrPRonledIM8b/eOUPl9b1/J9ef68GnleZcmzPgdwPf0Gu+a5lq7nA6OXs4iDbSbPMmyLKT7R5ahYV0HDuB65Oba8IXfC+32kPobPLl6+xy5eN83Hds1AK42gJW4Jfq9pPoq1Z5r2ps+C4Wfft0QuyW5H0FcXG6rxfhtqa1zLV+7fJOo33DTQM/oe53TT9Eqp83pQxXc3wvmedYsulL6uzzET5XwR5VWL9cyA/53e2AhLE7kbOO86U3DLcMF3rx3IriXNF8v72XmevqjvZyqzDZnl8n5W1zMmq4znGfju+GA5nthulu39y1uOuxoZHV2jf311sBxDe0lM4w3r2uysuP1qGFflKmy/yJ2w/UbsD9jpa7/6zOC5T+LX+Ph8XEPs8b58ZAyfPGrYOSPGZoyYMClj9FkeG22ZGRWMO8Tht+c2J8P+7qayWue7Kdti0rUiWJ9xVZur0PpSG2akyYxB6qfXDuvsDA1UrANi1+WpWDfErrNTse7P4JgA/gc/nrL6/AsmF2149NphgwsPjP332d6y6wRVX6emujpEdp2ainVn7Lo21depOZm2urJx/GQ=
*/