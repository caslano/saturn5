//  Copyright John Maddock 2007.
//  Copyright Paul A. Bristow 2007.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_STATS_FIND_LOCATION_HPP
#define BOOST_STATS_FIND_LOCATION_HPP

#include <boost/math/distributions/fwd.hpp> // for all distribution signatures.
#include <boost/math/distributions/complement.hpp>
#include <boost/math/policies/policy.hpp>
#include <boost/math/tools/traits.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/policies/error_handling.hpp>
// using boost::math::policies::policy;
// using boost::math::complement; // will be needed by users who want complement,
// but NOT placed here to avoid putting it in global scope.

namespace boost
{
  namespace math
  {
  // Function to find location of random variable z
  // to give probability p (given scale)
  // Applies to normal, lognormal, extreme value, Cauchy, (and symmetrical triangular),
  // enforced by static_assert below.

    template <class Dist, class Policy>
    inline
      typename Dist::value_type find_location( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type scale, // scale parameter, for example, normal standard deviation.
      const Policy& pol 
      )
    {
      static_assert(::boost::math::tools::is_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a distribution."); 
      static_assert(::boost::math::tools::is_scaled_distribution<Dist>::value, "The provided distribution does not meet the conceptual requirements of a scaled distribution."); 
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, pol);
      }
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, pol);
      }
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, pol);
      }
        
      //cout << "z " << z << ", p " << p << ",  quantile(Dist(), p) "
      //  << quantile(Dist(), p) << ", quan * scale " << quantile(Dist(), p) * scale << endl;
      return z - (quantile(Dist(), p) * scale);
    } // find_location

    template <class Dist>
    inline // with default policy.
      typename Dist::value_type find_location( // For example, normal mean.
      typename Dist::value_type z, // location of random variable z to give probability, P(X > z) == p.
      // For example, a nominal minimum acceptable z, so that p * 100 % are > z
      typename Dist::value_type p, // probability value desired at x, say 0.95 for 95% > z.
      typename Dist::value_type scale) // scale parameter, for example, normal standard deviation.
    { // Forward to find_location with default policy.
       return (find_location<Dist>(z, p, scale, policies::policy<>()));
    } // find_location

    // So the user can start from the complement q = (1 - p) of the probability p,
    // for example, l = find_location<normal>(complement(z, q, sd));

    template <class Dist, class Real1, class Real2, class Real3>
    inline typename Dist::value_type find_location( // Default policy.
      complemented3_type<Real1, Real2, Real3> const& c)
    {
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      typename Dist::value_type p = c.param1;
      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, policies::policy<>());
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, policies::policy<>());
      }
      typename Dist::value_type scale = c.param2;
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, policies::policy<>());
      }
       // cout << "z " << c.dist << ", quantile (Dist(), " << c.param1 << ") * scale " << c.param2 << endl;
       return z - quantile(Dist(), p) * scale;
    } // find_location complement


    template <class Dist, class Real1, class Real2, class Real3, class Real4>
    inline typename Dist::value_type find_location( // Explicit policy.
      complemented4_type<Real1, Real2, Real3, Real4> const& c)
    {
      static const char* function = "boost::math::find_location<Dist, Policy>&, %1%)";

      typename Dist::value_type p = c.param1;
      if(!(boost::math::isfinite)(p) || (p < 0) || (p > 1))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "Probability parameter was %1%, but must be >= 0 and <= 1!", p, c.param3);
      }
      typename Dist::value_type z = c.dist;
      if(!(boost::math::isfinite)(z))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "z parameter was %1%, but must be finite!", z, c.param3);
      }
      typename Dist::value_type scale = c.param2;
      if(!(boost::math::isfinite)(scale))
      {
       return policies::raise_domain_error<typename Dist::value_type>(
           function, "scale parameter was %1%, but must be finite!", scale, c.param3);
      }
       // cout << "z " << c.dist << ", quantile (Dist(), " << c.param1 << ") * scale " << c.param2 << endl;
       return z - quantile(Dist(), p) * scale;
    } // find_location complement

  } // namespace boost
} // namespace math

#endif // BOOST_STATS_FIND_LOCATION_HPP


/* find_location.hpp
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
*/