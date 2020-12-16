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
i8VJuffkqVt9NtPGMVX/pYj+/8lP3u/dP1G73+ObvcFK33hDFMIMVw9JJs84y7iipOs2PmUlYJzJE3WFN0kcG8xXeJcQRSuEbRp/0/CXrl+BZdn0Kw8lNQyWixyKSua7CHACDGOo5CKJCoMc9MeLVMwZ+I3v+driFzbJIjY1vL/98bh9Qtvx+CquzXi8rfF/pZ48Hj00xqb2huXAoNMZltSoYRk8tKNhSf2Ww0IYffAxQY2E+ooycpC7aVwq/dFvLejK4nTzmzqdn/h1RAf8OhLfs44HyY7Uafiy5+FZv8rfSQaUYZlhWuh+runVsD6HypzV2YhJr05JGH0sMC3HUXvE2gTOzOBHtiIX9OGrXd32gDP4tC1Yb0PYzR8HT3zlL6ruOtoeODd44rj/R9VXmEfnmQP9gydO+K+rvsIyOs8S6A5Bff+V1VdYR+dZ/ZcR3WuSo7bB2urGEzFFt9HndNTa0i+zCje1btn18knJdKZ5ENUXp4DZoaTqPuSG3rjlSdc2IF4KRra8tevb/CQ+VdyWfkv3OY+cHSUfYDfQNY2BpyP5Cpmfr4560O3QD1EKl5BIvplU5lVUJB0LEUjabMGk+E4K49gIOCWlui0/ZxEKbJ/fl2LfOjOG91Hqx9P111TRRMPrSeVZZqb4xqt303btDa9nBKoMMKNr302X7GZxhNDgao3/iO5unRvB4RV3XijRWn5QWruXD8qwEPuCTxH6RMjTlO76YlBMyFNpijz0bqLmEIq5ggb3VkrtXkmIV6CkrJFKqLmT0KqC4EFbUZJqccdLMGy0IQBgePQr//Bqy+j4wNXBo8f9Z1ePN4/ONQfGB4+e8PeuHm8ZnWsJXIi3JPEC2Hjr6FxrIF0NMlZXRRU5nEGJuREnHfmapY8wt5nQ2Yiehrl94uzRksHgbvKpDbNmfzOydKd/DE9g8EwxR1hGRUEOPg0jEcnQFCtGjoO3EpitTi70iDuBkxMXKkLlT62k3srIW7RIBJ1SpFiTB2qKkQd6vp8mD7SjrTzQzDNj5YGeiZIHIiyT9D/0/+byQAS/TkMJk8tdYg8MkFpru3nEg/3042tuorvZUX4/dTns7+4+FujiEz+Qscji9xlZitpkCWQgokC90S4jC6IjxUx/T1oYVg+UU7rETprjKKRSD4ma+PMGRk/8ufChZAqYlUhE+Hy8B5DMooX4ZKengS76Fyv/xNOuMKvDO3ZdfomnUxmdqqQIEy4TIsyAGeI3WVGyTLXJEVmmz9rKMjnk95yW3DlZJvwi8GyKgueKsTo8pxA8f/+Sk+C5Kflr4PlPyacLz5o81ZWFPbXb5i4XRISqzG2Fqm6Vnby5b0QKV7LBmQvHgQ+OL7AJmN6XolYKo+LzOiFqxb/Y2Ig8jHaH0WF8envxEfp5EyY59Vd8BAdeuOpjsM+ANSxk0ydlglIvkbHb+2gfUVcsXKjg1IC8Xi/8qSI7m9nB68ydGF/tMn7wGXILJa9x3u17xinlofT9i2qn/av9/ps6pm/q8mZt5Z/ybB6SaiB8L0b+hXjCpfwTXB3JPyWeQv6JTl9f359H+39Nf/LSGtqWN8rSXnnyPl3qGO7uEetd8j7gENaohSTmMs4rLpNhY+Pi6Aq60EQkO6+4ySVJo/geAXBAeeElLrBn+knUY6FdB1fxJII8Is4VAZhU5ZEogHlaAsz1LkPKUFeDo4DK20+WK9dVF8rt1DTo6KfjW6eQ/9rRCfmvnW3lv97Q5L96tSP/RShB3B4p/zWyI/mv2O8nacD5vDc9btbp3uosm/ttqEeyYldJdicE4kIlthaXOoEYX+CEDmk4iEKyx/2TFOjMvDpFfXrm7NBVydgT3D9JBlI2ifY=
*/