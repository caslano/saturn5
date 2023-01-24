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
dyjH3CPHcs5cMzNz794ez/P39/X6nu/v+/P5vD/vmIKlXX/54KTTmJETj8zU7/uMzsg+BKeZfianRqO/nytzqO+iHpnRL0NB9OzOPdUmJv9US7pxQbfBGpGs9C0l4XKL+yWNO72RN3fedTJvelCl9vex2pB/vieJt2b+nxvsmuviob1VF1CGrwGXbY6Gz9BSZCgyxlb0bf/KD4P+/VWsjSxY1PUgK0RYcUsRDvB7mD9tqwp1/RAZ3Rd7534DO7az6E5K1I/mGaJBmlLdvVf30rU7h0KDslfT5lHB3Vl74oeAq67NqxlgmM76K45b2ZLMytENlQO9To1GxPIMRHDEdrIi+05nSKEw+Bu7x97rzT/6IZbm1jEvr6H2pnae7x1Y3bJYnHbgCmcXyVvvNVsaH6MEtzWXXZvp3WtHse7sLv7ngymdvoQxAA9oE5qa6hMeuJfRe3ZtyrxYoiccvGDwDtLTfHK1vOxYslfVhOehTuEXgy6ZniZRz4Mz/cFXjU7vfPXqrOSjzK6B11HwA9+6xObhGbicx0FfFdweG+tQE16SnGmJxqU+F3MfXDc/+wwU96r/68OZaaszfzZ67/3o2M3LZPZbR704YdE6d9B7ttqrrNLXAreT66O/LwBfZ5+l3mX4DVt8iH2wZnGH3ESYxU1F5xdLWqWUxRNP6ZzTha+NKzLOdbtg0F1v74IPmv0130QPBTSCYc+ae+XA
*/