
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
GqELeiA4g7YgC0qgdAbzMIN2ZjAXM2jnTtqBAqiBVuiAqK/Rd0iCDMiHMqiGFuiCYAbzAKMgHfKgPAPZGciG6JmMD2TORD5UzqSNmciHboi6i77DXMiHVXchH+qgEXpg1N2ME8y+G/lQCrWwC9ruph2IyGQtQQKkQC4Uw4ZM2sqkLYiaxXzMor1ZtAdFs3ieWbQFLdA+i7buYe4hHbKgBGoh8HWeBcZBCqTBfKiEGmiCDuiDMbNpA3JgFZRBBbRAFwTn0M4cngcK5yB/DuM1h2eZw7PMoZ17aQPmwxrYAK3QDXHfYC6gCOqgHYJzkQezoRSa5551yJED4yABMqF4HrLm0d959BWivok8mApzIQeKYBXUQTtE3odsmATpUAjlUAu7oO2+c4Z6BGRCARRDJTRBH0QtoM9QBtXQCC3QA+n3M6fQDJ0Q8S36C2mwBjZAPXRAH4zJoq9QkYUc6IJgNv2EydmMAWRBKVRlIxcC32YsIAXSYD4UwAaoh1bohj6IeoA2YCrkQzW0QBf0QGQO7eTQDhRCFeyCEznIXEifFyIXmhYiD8K+w/6BfKiAFoj8Ls8Ns6EQmqETArk8O6TBfCiADVAJrdABfTBmEfMGGZAP1VAHLdAOox5EPuRBIdRCM7RB9EPIh1yohBrogD6IyuO5IQOKoBG6ILgYmTAJJkPWYmRDKVRBLeyCTjgBgYdpB8ZBGsyHYqiHbkj6Hm3AKiiDRmiBLuiByHzagXSYnU9bUAq1+ciHiCXIhjQohkpogg4I+z7PATlQB+0w6hHkQTpkQR6UQDOcgIgC1gZkQjFUQj20QtRSxhvilrLuljIuS+n3UsZ8KfKX0nfoWkobj6JjYTYUQjlUwS5og4TH6C8UQCV0QFQhsiEOkiCjEPlQBhWFyIYeCD7O2EM6lEMtdELgCfoOCZAJubABKqEJumHMMuTDXMiHCqiDHhhfhFyYDSVQDrvgBEQsZw4hBeYvp9/LWdvLkb+cNbMc+ctZM8uR/QNkQz6UQR30wKgfIhsmQxaUQC10QkQxsiEBcouRCfXQCnErGAfIgVUrkAmN0AOjnqTPMBmyoBTKoQra4ARE/Ii1ASmQBmugBuqhA/ogrIQ2oAgqoA7aoQciV9IOpEMelMOulciHcT9GLuRCARRDJdRAE4T9hP7DVMiAuVANjdACXRBchWzIglKohWZog4jVyIc0yFxNG7AB6qEV+iDjp8iFMmiBLuiBrJ/RXyiE5p+dC5wkQApkQjHUQCt0QB/EraWvkA9FUAHV0A49MOrnrA3IgjyogjaI/gWyIRNyoQAqoR5aIawU2ZAEGZADq6AOumDSOmRC7Tr6ug6Z65D5FOMLaTAfimEDND2FTOiDMU8jD4qgDBqhB8aXMaYwGwqhFKqgGTrhBIxbz1isp7/rGZr19Hc9ctezR9Yj95f0FzKgCMqgBXpg1K/oL6RDCVRBLeyCExCxAdmQAGlQAGugBjqgG/ogaSPzBvkbGYuNjMVG5MP4ZxhbKIQSqIJOOAHjnmUsoACKYQPUQAf0QVQ5ciEHiqACqqERuiByE33fhPxNyIaIXzPOMA7SIBNyYQ3UQD10QDdE/QbZMBXmQhFUQAt0wagKZMNsKIRyqIJdcAIiNjPekAaZm2kH6qEVwp5jvGEuFEE1tEPwt8iEyTAbSqAWdkEzBCrpO6RAAayBDVAPrdANfTDmeeRDEmRADtRB8HeMCYyC8VAKtdAMJyD6BeYRUmADVEIT9MGYKmRCBhRBGTRCO3RB5Bb6DumQBeVb6Dd0bkH2FmT/nrGATFgDNdAB3dAHcS8yHpADZVANddACXTC+GtmQByVQBZ3VZxNT9BlyoXIrsiDpJWRBPqw=
*/