/*
  [auto_generated]
  boost/numeric/odeint/util/stepper_traits.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_UTIL_STEPPER_TRAITS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_UTIL_STEPPER_TRAITS_HPP_DEFINED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace traits {

template< class Stepper >
struct state_type
{
    typedef typename boost::numeric::odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename stepper_type::state_type type;
};

template< class Stepper >
struct time_type
{
    typedef typename boost::numeric::odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename stepper_type::time_type type;
};

template< class Stepper >
struct stepper_category
{
    typedef typename boost::numeric::odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename stepper_type::stepper_category type;
};

template< class Stepper >
struct value_type
{
    typedef typename boost::numeric::odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename stepper_type::value_type type;
};

} // namespace traits
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_STEPPER_TRAITS_HPP_DEFINED

/* stepper_traits.hpp
t9EsbZyOfMkil2kqYO3UrPt7y6YT0Rm2eXjJTi432fUwiZNd9reTq5/PP1yxvx1eXByeXf3Kzo/Z4dmvEuwvJ2dvxdTHgtmMRV8fZlEimM9YfP8wjqPbnGd7PwcbGwf5KCIh8dnDNIlWy2AeJXM5ICGW+3gS3w/H40fRqWh2E4tW4/haTvfrRKw6IaTJMJsS8dHgfudhJj4csdF0dj+cz+PJJ3YzfBhex+N4LmdMTtCd+M9YfiPYJdP7iN0O50M2f3yIEjlM0bOX8eRmvLiN2Kbsyf7dZuGj78axmN5k/+4H+eHoNhqxnw//ejQ4Pe8fnh4Nft54ydi67fRmKCbs7gd2sCP7JBbQPPtsa1tyehlNxNIrMryP7m+j68WnnOmIbV2e/P3o/HjQ/3BxOjg/Ph5csR9Y/tnp+dlP25Kh6EU8idi79xdnV4PLD8fHJ78UCdjpqWA1TiJS21WvluNLvz25PO+/f18DSIkG/cHPR6fvjy7crb8Ox7uXi9Eo/rrNxN/Zy5cs+1XTAYT+QKyUFX3aq5cAuVMiRxmosWSLbQbgayS3LQWWA/744fjy71JPu0Fn9eGHy5/PL64GV0eXV5cDsQNFC4d9wxzOV00u8SYfTs7KDVgdBW/yQS6dcpsaCt6kLwZ+pW6ysSF0
*/