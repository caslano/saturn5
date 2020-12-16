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
#include <boost/static_assert.hpp>
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
  // enforced by BOOST_STATIC_ASSERT below.

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
#if !defined(BOOST_NO_SFINAE) && !BOOST_WORKAROUND(__SUNPRO_CC, BOOST_TESTED_AT(0x590))
      // Will fail to compile here if try to use with a distribution without scale & location,
      // for example pareto, and many others.  These tests are disabled by the pp-logic
      // above if the compiler doesn't support the SFINAE tricks used in the traits class.
      BOOST_STATIC_ASSERT(::boost::math::tools::is_distribution<Dist>::value); 
      BOOST_STATIC_ASSERT(::boost::math::tools::is_scaled_distribution<Dist>::value);
#endif
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
ZJx8FIyHR8C2cCzsAMfDXDnuJMc94QTYB04Uu4RJcBQsghPhUdAPj4bT5XiGHM+Bx8C5sBReBcvgdfB4eD30wyVwmuiYy+H9MAAfgZXwSTgdroUz4PMS/wU4C74Kj4Pvw9nwezkv9SLPU/XOUadeMpBrAdUrEtxO6qED3AXmwj1gJzgYdpbyd4FjYDYsgtuLbr0NPAnmw1PEjuJqsZO4Ge4KH4C7wZWwJ1wD95By9YIvi73BO3AvuB72hZ/BfvBL2B9+CwfAH+T3foJ50C7zIJgJ94Pt4P6wI8zX9g7y3IHNZPzSae9Av9JySxuQmx3l/kKBf9keQ3FD//v7DH043NtrKJoxin/zXkNLGONYh6/GJ8/0xjs85znPec5znvOc5zznOc95znNbltsc8/8nlEwtKJtUNLkp5v/bNgDVuej0ZGwzIVbmOvkYC4R7w48YM1h/rxpz6T/4kIKyomMLhgwctJ9jbd+plWq8mqGuJJi/3JZdptd8DqjjwxlHGWAciyFtPVY4TI3FTB9fGjr+omVkbEbJ/qjGOUsCzvH+aiXXxfeJ1YzRxWakQZ6C8SlVsTVfpyvhehxohZr7a9dswfjKGbXzTzNU/t9l76t49btXdlTrbY8vP6pmrOg7GZf8bG87nKgOe4ZvVfqdfB9R0ma+ONJUdYajKQtoSce4fUf1O89at1nN9fjj9ch+TfscQYbzEPomlzTxYzle5FoHO6mB8ce3lodbA1i1nx4fpw0IkzaQMUjqmjDqWsLsMlMPhKl6UOONC1T6DKPm1Yxn7SrjeGkygOeXDE3F35PH8X2qT6kK95cXTS6h4lrUrhdt7CvE0X3ll5pxbhYjrq3DG9T57tYOpvkkrviBOBWfQVTDfBKXbGyNrJRV+rU6n6b6fbKWz9Rp6DBz/9J2IbOVzFg1v3kEvnbNeb9O+wwlc5jDRmVSUbnKueRHy2yt1xFYQoUsTLYZyXyUkDWhdV+gjjmWOpa+QL0RpupNz1uPVWFSPxKWUxMWMva8RGwn9pO5iYOkL1gr3H1BDec22B+IZ+oPprZHNvK2R9bU9vqe0Eydb8GV6jPZPxA/bLtru55tlMxOekyZa7m+eewHNHU7Oa/R3ltZyq3GJ+IfkXYpdLRLReXkiK5R4tR7jb6hzvfCWqO5ef2HKNqpsIF2mqrOb02+msu1FIyzv7O9CGv4OTBbyVzMPmNx2lalQoXFRvxcCNrfnKzi7RByrafW5E/SvJMc71zv9b5CySXrvRl+kf4U7vpP2kzXv/n5oO8J2j7luhX6eRFyj4iT4YACuUeMC/bF+0P6YsT3iML7I79HFN4fRd9D1tj3pJ8XqfOHW6PM9wgdvz22cHlbcf/mgf9dLmkn+BJLEvvHxyclpsa2jo9JahHvvEfUe08pVWkerOzndJwo1pFpivYP2rL09kVvqxHOFuFaZVNScdu1z7311X5vrVt+3dDvy58bFb2NgtnWJLyNhdkGJXobC7NtRPh1J37Q73A1fSIfnolX65oH31vlPT3fua65jMcnwd6wFdwb7mDLwl4yDr8/7Cdz6wbBYrgf9MPBcA48AFbBYXABHCX2DIfBx+E4WZe+UMbtJ8Pf4ESZMzcJpsIimAknw2yYB3vBPnBvCbfLtUC/L0F8vtTBPLwl6+TbLIMJ8GTYAk6T8lbATBiAXWEl7CFyu8GZsK/YWxwCZ8MjxM6iQOQK4YnwaHgSnCrh38Bi/VynriR/LfBjJX+niX3KmXAreJbkaz7cGs6D28BzYTt4PuwJL5B8XQgHifw38An9XOK5LL+Xjn/AsR9CIrxJ2vlmmA4fh1lwCcyGt8H28A7YGd4Ju8O7pD/cDYfA5XAMvA9Ogys=
*/