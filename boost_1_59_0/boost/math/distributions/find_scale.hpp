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
#include <boost/math/tools/assert.hpp>
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
      static_assert(::boost::math::tools::is_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a distribution."); 
      static_assert(::boost::math::tools::is_scaled_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a scaled distribution."); 
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

      static_assert(::boost::math::tools::is_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a distribution."); 
      static_assert(::boost::math::tools::is_scaled_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a scaled distribution."); 
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

      static_assert(::boost::math::tools::is_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a distribution."); 
      static_assert(::boost::math::tools::is_scaled_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a scaled distribution.");  
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