/*
 boost/numeric/odeint/stepper/detail/generation_controlled_adams_bashforth_moulton.hpp

 [begin_description]
 Spezialization of the generation functions for creation of the controlled adams bashforth moulton stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GENERATION_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED
#define GENERATION_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/adaptive_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/controlled_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< size_t Steps, class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resizer >
struct get_controller< adaptive_adams_bashforth_moulton< Steps, State , Value , Deriv , Time , Algebra , Operations , Resizer > >
{
	typedef adaptive_adams_bashforth_moulton<Steps, State, Value, Deriv, Time, Algebra, Operations, Resizer> stepper_type;
    typedef controlled_adams_bashforth_moulton< stepper_type > type;
};

// controller factory for controlled_adams_bashforth_moulton
template< class Stepper >
struct controller_factory< Stepper , controlled_adams_bashforth_moulton< Stepper > >
{
    typedef Stepper stepper_type;
    typedef controlled_adams_bashforth_moulton< stepper_type > controller_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::value_type time_type;

    controller_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return controller_type(step_adjuster_type(abs_error, rel_error));
    }

    controller_type operator()( value_type abs_error , value_type rel_error ,
                                time_type max_dt, const stepper_type &stepper )
    {
        return controller_type( step_adjuster_type(abs_error, rel_error, max_dt));
    }
};

}
}
}

#endif
/* generation_controlled_adams_bashforth_moulton.hpp
iEUcCR4UPn/d0aw0Kabzy334AGejQR7i+WUbH+NEXS/LgRflAAYseRezNL1SSYBvm5XKUyH9KAs4VDVPMdrVzaEFXwR8ms2L4VnAZ9BBT17X6Y29jjP8szca953huEKF2wB73On3MTVp6lxqRjkIV0gIYJazmGPwv2Vc+hj3GRIjlXyeq8QR0ziCwUJMTwGrYiYkh7PTgWN33ZP+GKqT64OXk+vXb/B8i/cvJtft1u371ftXxbt2FSaVrbWP1l77qIGSB22SLCwcrLXN/T6ePLfcbj1kzfieFZpktZV7oDFjBd+3WLXylEcpv2eGpnzxn5J1GmXJFK44XDGZ11ocKRZMJJmQWGsmHpICMugfvXr5ppIS3T6k4l/uaYwBC3wWRVPmf635IUsAGrFOrO0TyI9ClS6PkZOYHdMHBS+VCKDhY/JLHdcr31FW4GwavsokliZmZc081wuRwwpJzGqlQB2+G/OYWUpGS6pvw5HCDDJ9ApmSONVvmaDOBn7EWSLkfNULMZlIfxbjqJ7VUo2NIbGgOurZXbAHdLmArjPsPUFi64dGOOEaewq06OkGzzWaZ88OCco0W8SmdAxWIgPLzJABHwG7R8RlbR3WejmJrSA2/KKmHy9rFKSNrLgN6q71EuX2KQ4dF477G9Nb
*/