/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_dopri5.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Dormand-Prince5 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>
#include <boost/numeric/odeint/stepper/generation/make_dense_output.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_dense_output< runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef dense_output_runge_kutta< controller_type > type;
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED

/* generation_runge_kutta_dopri5.hpp
u/WvULFU0ccGCD0jg345Vz2GacrKmNArvhG5ZN4f/Mu0bUOoAuiTvkeQHrxhEpnxZk/ek7RS1xYXp67LPHYEAVZ1OkmryyqeZWUrXw/h/tly8oQVz99J/i7HDN3wQu4c3H5arn6g8Set5guzT5BGeoDczLk9l5ZtOUzuOx1OdXI5HDHwI8/svIUdbv8R+JeHcind4Mw8DN7cF6v8rse6QFfh+bagA/23+Tyh3Crax/PoWNeT9iqXEei+nK/p+n87JnKgAWRHju6wh2I5zcBODj/pa/HPU/OxPve9v6YqZztGspVydTIO/rqaXxSI9yw8GQYSdjindpj++c2P3h9e/v6epc25LlMHisb59gPAVzH0FIxF6nDWy6Io344mCh81U98y073vThf4EOHdOVTED/BHl+FXGp8kt8qGSqpcvsi+vWbAy5x+rT6vjt045257rCA4XOy+4rn+qDT8bk9s0IOclwR40Rlr6I20yeHTNy4gv5rE1dSDPRKY0bOLrJqLZysQN0+jN17mZDVO3m4R3n8jXaA3NPqMuFMm4bF1w11Aij2wc6cfWZHzbthluLwk7eFzhR1TWPRGK+PD0zDFYC3lx6KSiwZt/zyIPRgzd3PKKC6vlBJq/Cwj+jXUlxbzg7mv+ezzENN38tFMhrlMqfxes7wniS/WskrjePN5QU6kyxXjjhW3Mv7G8l1GGA4x23f2UypQBGDYP7/R
*/