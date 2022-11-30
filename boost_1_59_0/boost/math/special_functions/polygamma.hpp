
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
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
*/