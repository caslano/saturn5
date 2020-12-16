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
YCV8SOxAHoYXwEfgIvgoXCy/dyN8TOxDVsEH4BrpL4/r+pN7Hiww1N8Cqb+Fks/L4W5yPECOD5Z1/kfAKyW/V0k7XgbHyfFYn9Xg+hVilxFij/Eafi7j0WJ7oe0t3OtTbLA5lPFsZOe5bCPm49PE9mHDML3WhJ4XmZcdq+dGXj61GbYMwfUlIOfixC5B1pBwzHl0rh1hXjdC5jliU+CY22heH0LsAZALs/7DYTIvcRllXIffiE+alWh1muWN13vOc57znOc85znPec5znvOc5/7fbnON/zfV+v9ZrEH8IhN7Oh1h622nFAWKp06qUKnXrPv/s2N9gGJZHzBP9Da98Y9zULVM2wbYEe3l3CMezyWuHndZnad06BLVqJ/X8ukueRkKMOnpdZw26NlfUpNM0WtTrsQW8TGxGYm5toYdfZ3WsTO2blznPQXeZqclc4pXKR180QxmFdu/q/bPVvPW0bWT1wbXCBddu54TSnk4ri1/FuFJrnApp3PfaSrS3C7r67ZLxGN46+u2C1HDtouWT3fJ19cu6x3tUkqbLIhtfLv8senbhfIY24Vwc7sExO6hh7TLzvgHidP97tB2qYjieiGubpf7VT1LTHO7aPl0l7xk19QuOk4W7RIXRxjl+FW1S2JH2iQtIbRNNkmdk1eOpWy6ziXcVQZnnW+IN9e5313nUVwL/jp1Tszwda7l053yDdS531HnM6jvOfH/VJ2TV2OdE+6qc2zG9HoC7nXxV+cw57K2zifXPFIa3o/eOf9/nhQiSwTswHW7UFfLatfbt5+FrJtfOmH8xGMKJgbKS60I2nOZe2+CiVMmmdrSJfvsLmqdAPP6s05ZbeNVRuPU3qNmqvMpHI9JieH4IgarRmzfcJ2Yx2Zl7QjJe3BsljwSRh5dexesE5X9Bh/hwidpo/VLQ+tSVaGrDneV8eyPlez7vmRS2I9fPAqpGfBSeCdhD7HmTzI2bjv7jPv581vmeu8mtntxd3CWXbp3tNLUKhyHwQA8i9q90mKuIKlu7TPbjOi09ZolDEX3MLYTsu5xe2R3pZ+JbUZnlY9CqzW57obfH28av3em84y6FicGuHBUfWXAL9X5N3xb8f8h+GL8SfiF+FvwD+ETfT5rR+pM5dvwXHtL5SVN7xP0hzrOYp3+2Dr9rJvYHMYrmUd9O/Ae2I+cjoYV8Ezq8Ara6iuu0CRfvBVcX2fY9jV98TfuN7/jh3M8tnUk6+skAd437uT3HMeZcpyKzeGtKi9W7kFDevSwJGxhbVh3S2wTz9Rhe6pjvz7urY5H6+Ne6ngffbyHOt5BH/eM6npR66iovuKyZVB9Qp4tcg0tZhBX9hcnnHFI/PO0+8q7Q6+hyaWVFcUFRTOsCO5FxA3pQz7pQ3qNbHX+YlquOesQxJjXyK7zfJrIt0NZpd9hb9TrHmUrZLwenHlYqeKr/mTq88ga90HS6wL9rM5PwLorVu/VYvetNSlBRtKvzO1H/XAs9RPybNLl1W24UoXL/Rdbo0Gq/Mi7bI2qWtbdo+ojClJ9l6tNeey52lPbb36vZEcrW8AsvKGdSc94r9C2QvHq2TCI9ozR+3txXWK7U+MP4+9Dt4/ejsdZ1pESc295N+qFf9L+frsnpKzqO6Eogveiqnsif44i6/qeKOJdgqVvzM9SLZ8eIk8jSCRT35Q4Yb8Rbr2n/m8E5/tVnXeoCO0wnfeYdOd3gqO8WaqPSrirXKSj8rJKzpG/kDZckOJ+J8K1p78vrdOGFRHdfxzPML96FrIflLkNkXW3d0XJLPO3HbL1vws9ubTuu9DnrRv/LkTeObbz7trHSfLorMPFqTUJ9sUrGyr8i/b3sus6KClT9u7ue7O+p/4=
*/