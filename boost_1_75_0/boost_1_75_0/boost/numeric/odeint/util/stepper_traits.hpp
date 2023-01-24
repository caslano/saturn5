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
uGqP6Nv2zsivYIeLZXS7uk9G9AetMnpsEu+jv0a3oMH78qm9T2j3398lrKd/dvKQOb7xveYKc2ldfiZVfb1CrthZvs2x8zu0e7D4hnLgtJcASDopuI2xujzyXPET/EObED2VhrU3EqLfi+jevW7TNJrg/UjIkPW5GHa8zNdLrl8RmiOpOkxvL/0FCFV/e9eyo3ItqS8S9LsgiQa+GIzqDqZq/X6wIC1eeM4f3RyaH3ta8axq4ph5VheKmdFbs/Yroti7KoF3s6YoUJJm6PFY3WFA6wHBVkSuz0+hlRdrLGc9lFSaXS8EbFj84E7v3atKF/slkgJzvBSmn0nuRBIUjX4voCIAVHww6Tl7wltq4MLdcHfqvhy/tXFdeqzXvu77oxID+cCbYZT6S7/dmXfZv1o2x82Q7tylvpAc9fH9rHof/Y/Yb4rfJw56NAI2PHr22FEtdmZVgKKUmhz/8oNwE5G599fHAe8q9Oq3CgZe0HT80/J9tsY7C1iy43j+tHCPHWorLQx7S9loUKgWz/uuk0JxlruEKHbqp/TM+pRnXQecWrnp1eLDSqAjb1QGpS4hFBwaAn64XVwKqOg8FTCRI3XLR7eFc7aA5WFnfUrH4VfrhXjiCZ0pb7YKWEe45rjjCePzssT00e1cWNoZ7r4RtbJzLF8xFPOSnb7tiuTSMhHyHkLy77X9E3r4VHNs7hdk8a8YWAJc176OsKhg
*/