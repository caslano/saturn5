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
8E9BaJzPbIU3uVpPvwyrV4G+3bg6L7V+bcL9PWaNl8qoOM/kM/sAf/bntt74sh5qI9sAWaCCv/TvG19jvhNsoK0w0532l0U6n455VZl+KhFKF+7/wN5T6UDv0Npu1kjGq67XaxXhgQ+ZhVkqEnUPPmy+Xv4LjdVR7yRdz51s2E765Y2/dOH+nkH2AM0munUH3ZUmWQ92HpYO/AC1Kc6Lp1Y4G2uUXdTyW6BZKf6ykT8owxO7+jD/D9yZGql9sieM+dzQ7ZPujykyVq2DGWD9xEr3dwhrmoxBHWCrzLk893mJm3nL7uX2/bA/R0cCdseo3LFTXouOz7LeXvfHKCcVzVyfN5/XQ70mU45YKv7j+W9X63V6enlY/958lTY834BuUOxfozu8i1zZZr1aD7zeWeVGtvVM/8v7aMP1AFahN69Qdp7eN3SkidfoeNgokln42ahY0M3rKdHkfZluTroe0Ria0We6l65/gEqC8fM+yFg3MSozhFG0Xm8vlAN8d5lHvwnzqZ15Me1mH7B5mhvYv1EZVKmIp9KnJ76qZMNgjdFPYsZ3q7hit7LPRI/F9CldkfD+8Cvmq/B0G+26kK0uz33eUWgnuGqaFcEu5X3sFcN5cnMR9ELQM77Yvy4yYW6ufcLI93zETvE4nCHflH2glwXylfIZqGuOyiesXW5+dqWceBdWzh2CCc5gB2jjpPMmzKOmZtTIwvl97OR1
*/