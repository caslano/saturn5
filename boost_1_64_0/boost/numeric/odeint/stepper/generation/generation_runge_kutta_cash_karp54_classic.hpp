/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54_classic.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the
 Runge-Kutta-Cash-Karp 54 method with the classical implementation.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// Specializations for runge_kutta_cash_karp54
template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

/* generation_runge_kutta_cash_karp54_classic.hpp
F92jtBQowlVtkXXmccS028TWKMEHXhXdieu6eG/0H+gHEfHAAhS1Dixa51uotESliGaHW3I/JUFuz4yHUKk1VEpwIiH5LKU8W87vQw5K3erhuCwjdQVK8TvFr62HNMwbZ8TWxumjZeeAlsVTJyaoy5Vk2cmSWZGCsSIkSUtVF/rIDGYvWo0zGbFQJfzgkKyeFP4tlU5XILzlwpNj+OGfLilgyiSU3OEy8HmxuqEO6br71gPUGoe4CRdrQJ4+LsuVj008k2kkLII0PSlvw9TbEktkEq2343OagZb817ZkFSdQwKks831eg485N9WXimkqB7UJAlDJCre6TbHU00UNOieAFmoMyNpkQfkQE4r3bPJn06L5yYVJen6r7y1SqDbLZCfaLWvnfE6ex8DyNYvU0BgMHMcsfbOvrPBFHqGd5sNVm3iQez+2mTkacFEUFGcE3JGbRULhjLKY2iPGUa2lfQI+wQ1cYqcvF9Y6qHPr+oo8dxgFDSLZt2pfk85GZzTCznAYYzMRlVPjlmxrJtNfX4WF0X5C00C5W/5C6ReuSBXNJUXbyeI90aSLug==
*/