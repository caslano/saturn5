//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_FIND_SCALE_HPP
#define BOOST_STATS_FIND_SCALE_HPP

#include <boost/math/distributions/fwd.hpp> // for all distribution signatures.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/policies/policy.hpp>
// using boost::math::policies::policy;
#include <boost/math/tools/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/policies/error_handling.hpp>
// using boost::math::complement; // will be needed by users who want complement,
// but NOT placed here to avoid putting it in global scope.

namespace boost
{
  namespace math
  {
    // Function to find location of random variable z
    // to give probability p (given scale)
    // Applies to normal, lognormal, extreme value, Cauchy, (and symmetrical triangular),
    // distributions that have scale.
    // BOOST_STATIC_ASSERTs, see below, are used to enforce this.

    template <class Dist, class Policy>
    inline
      typename Dist::value_type find_scale( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable weight z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type location, // location parameter, for example, normal distribution mean.
      const Policy& pol 
      )
    {
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
      BOOST_STATIC_ASSERT(::boost::math::tools::is_distribution<Dist>::value); 
      BOOST_STATIC_ASSERT(::boost::math::tools::is_scaled_distribution<Dist>::value); 
#endif
      static const char* function = "boost::math::find_scale<Dist, Policy>(%1%, %1%, %1%, Policy)";

      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, pol);
      }
      if(!(boost::math::isfinite)(z))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale z parameter was %1%, but must be finite!", z, pol);
      }
      if(!(boost::math::isfinite)(location))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale location parameter was %1%, but must be finite!", location, pol);
      }

      //cout << "z " << z << ", p " << p << ",  quantile(Dist(), p) "
      //<< quantile(Dist(), p) << ", z - mean " << z - location 
      //<<", sd " << (z - location)  / quantile(Dist(), p) << endl;

      //quantile(N01, 0.001) -3.09023
      //quantile(N01, 0.01) -2.32635
      //quantile(N01, 0.05) -1.64485
      //quantile(N01, 0.333333) -0.430728
      //quantile(N01, 0.5) 0  
      //quantile(N01, 0.666667) 0.430728
      //quantile(N01, 0.9) 1.28155
      //quantile(N01, 0.95) 1.64485
      //quantile(N01, 0.99) 2.32635
      //quantile(N01, 0.999) 3.09023

      typename Dist::value_type result = 
        (z - location)  // difference between desired x and current location.
        / quantile(Dist(), p); // standard distribution.

      if (result <= 0)
      { // If policy isn't to throw, return the scale <= 0.
        policies::raise_evaluation_error<typename Dist::value_type>(function,
          "Computed scale (%1%) is <= 0!" " Was the complement intended?",
          result, Policy());
      }
      return result;
    } // template <class Dist, class Policy> find_scale

    template <class Dist>
    inline // with default policy.
      typename Dist::value_type find_scale( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type location) // location parameter, for example, mean.
    { // Forward to find_scale using the default policy.
      return (find_scale<Dist>(z, p, location, policies::policy<>()));
    } // find_scale

    template <class Dist, class Real1, class Real2, class Real3, class Policy>
    inline typename Dist::value_type find_scale(
      complemented4_type<Real1, Real2, Real3, Policy> const& c)
    {
      //cout << "cparam1 q " << c.param1 // q
      //  << ", c.dist z " << c.dist // z
      //  << ", c.param2 l " << c.param2 // l
      //  << ", quantile (Dist(), c.param1 = q) "
      //  << quantile(Dist(), c.param1) //q
      //  << endl;

#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
      BOOST_STATIC_ASSERT(::boost::math::tools::is_distribution<Dist>::value); 
      BOOST_STATIC_ASSERT(::boost::math::tools::is_scaled_distribution<Dist>::value); 
#endif
      static const char* function = "boost::math::find_scale<Dist, Policy>(complement(%1%, %1%, %1%, Policy))";

      // Checks on arguments, as not complemented version,
      // Explicit policy.
      typename Dist::value_type q = c.param1;
      if(!(boost::math::isfinite)(q) || (q < 0) || (q > 1))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "Probability parameter was %1%, but must be >= 0 and <= 1!", q, c.param3);
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale z parameter was %1%, but must be finite!", z, c.param3);
      }
      typename Dist::value_type location = c.param2;
      if(!(boost::math::isfinite)(location))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale location parameter was %1%, but must be finite!", location, c.param3);
      }

      typename Dist::value_type result = 
        (c.dist - c.param2)  // difference between desired x and current location.
        / quantile(complement(Dist(), c.param1));
      //     (  z    - location) / (quantile(complement(Dist(),  q)) 
      if (result <= 0)
      { // If policy isn't to throw, return the scale <= 0.
        policies::raise_evaluation_error<typename Dist::value_type>(function,
          "Computed scale (%1%) is <= 0!" " Was the complement intended?",
          result, Policy());
      }
      return result;
    } // template <class Dist, class Policy, class Real1, class Real2, class Real3> typename Dist::value_type find_scale

    // So the user can start from the complement q = (1 - p) of the probability p,
    // for example, s = find_scale<normal>(complement(z, q, l));

    template <class Dist, class Real1, class Real2, class Real3>
    inline typename Dist::value_type find_scale(
      complemented3_type<Real1, Real2, Real3> const& c)
    {
      //cout << "cparam1 q " << c.param1 // q
      //  << ", c.dist z " << c.dist // z
      //  << ", c.param2 l " << c.param2 // l
      //  << ", quantile (Dist(), c.param1 = q) "
      //  << quantile(Dist(), c.param1) //q
      //  << endl;

#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
      BOOST_STATIC_ASSERT(::boost::math::tools::is_distribution<Dist>::value); 
      BOOST_STATIC_ASSERT(::boost::math::tools::is_scaled_distribution<Dist>::value); 
#endif
      static const char* function = "boost::math::find_scale<Dist, Policy>(complement(%1%, %1%, %1%, Policy))";

      // Checks on arguments, as not complemented version,
      // default policy policies::policy<>().
      typename Dist::value_type q = c.param1;
      if(!(boost::math::isfinite)(q) || (q < 0) || (q > 1))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "Probability parameter was %1%, but must be >= 0 and <= 1!", q, policies::policy<>());
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale z parameter was %1%, but must be finite!", z, policies::policy<>());
      }
      typename Dist::value_type location = c.param2;
      if(!(boost::math::isfinite)(location))
      {
        return policies::raise_domain_error<typename Dist::value_type>(
          function, "find_scale location parameter was %1%, but must be finite!", location, policies::policy<>());
      }

      typename Dist::value_type result = 
        (z - location)  // difference between desired x and current location.
        / quantile(complement(Dist(), q));
      //     (  z    - location) / (quantile(complement(Dist(),  q)) 
      if (result <= 0)
      { // If policy isn't to throw, return the scale <= 0.
        policies::raise_evaluation_error<typename Dist::value_type>(function,
          "Computed scale (%1%) is <= 0!" " Was the complement intended?",
          result, policies::policy<>()); // This is only the default policy - also Want a version with Policy here.
      }
      return result;
    } // template <class Dist, class Real1, class Real2, class Real3> typename Dist::value_type find_scale

  } // namespace boost
} // namespace math

#endif // BOOST_STATS_FIND_SCALE_HPP

/* find_scale.hpp
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
*/