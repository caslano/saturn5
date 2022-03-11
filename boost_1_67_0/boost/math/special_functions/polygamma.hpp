
///////////////////////////////////////////////////////////////////////////////
//  Copyright 2013 Nikhar Agrawal
//  Copyright 2013 Christopher Kormanyos
//  Copyright 2014 John Maddock
//  Copyright 2013 Paul Bristow
//  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef _BOOST_POLYGAMMA_2013_07_30_HPP_
  #define _BOOST_POLYGAMMA_2013_07_30_HPP_

#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/detail/polygamma.hpp>
#include <boost/math/special_functions/trigamma.hpp>

namespace boost { namespace math {

  
  template<class T, class Policy>
  inline typename tools::promote_args<T>::type polygamma(const int n, T x, const Policy& pol)
  {
     //
     // Filter off special cases right at the start:
     //
     if(n == 0)
        return boost::math::digamma(x, pol);
     if(n == 1)
        return boost::math::trigamma(x, pol);
     //
     // We've found some standard library functions to misbehave if any FPU exception flags
     // are set prior to their call, this code will clear those flags, then reset them
     // on exit:
     //
     BOOST_FPU_EXCEPTION_GUARD
     //
     // The type of the result - the common type of T and U after
     // any integer types have been promoted to double:
     //
     typedef typename tools::promote_args<T>::type result_type;
     //
     // The type used for the calculation.  This may be a wider type than
     // the result in order to ensure full precision:
     //
     typedef typename policies::evaluation<result_type, Policy>::type value_type;
     //
     // The type of the policy to forward to the actual implementation.
     // We disable promotion of float and double as that's [possibly]
     // happened already in the line above.  Also reset to the default
     // any policies we don't use (reduces code bloat if we're called
     // multiple times with differing policies we don't actually use).
     // Also normalise the type, again to reduce code bloat in case we're
     // called multiple times with functionally identical policies that happen
     // to be different types.
     //
     typedef typename policies::normalise<
        Policy,
        policies::promote_float<false>,
        policies::promote_double<false>,
        policies::discrete_quantile<>,
        policies::assert_undefined<> >::type forwarding_policy;
     //
     // Whew.  Now we can make the actual call to the implementation.
     // Arguments are explicitly cast to the evaluation type, and the result
     // passed through checked_narrowing_cast which handles things like overflow
     // according to the policy passed:
     //
     return policies::checked_narrowing_cast<result_type, forwarding_policy>(
        detail::polygamma_imp(n, static_cast<value_type>(x), forwarding_policy()),
        "boost::math::polygamma<%1%>(int, %1%)");
  }

  template<class T>
  inline typename tools::promote_args<T>::type polygamma(const int n, T x)
  {
      return boost::math::polygamma(n, x, policies::policy<>());
  }

} } // namespace boost::math

#endif // _BOOST_BERNOULLI_2013_05_30_HPP_


/* polygamma.hpp
+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
*/