/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp

 [begin_description]
 integrate steps implementation
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
#include <boost/numeric/odeint/iterator/n_step_time_iterator.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
);


/* basic version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , stepper_tag )
{
    // ToDo: is there a better way to extract the final time?
    Time t = start_time; // Assignment is only here to avoid warnings.
    boost::for_each( make_n_step_time_range( stepper , system , start_state ,
                                             start_time , dt , num_of_steps ) ,
                     obs_caller_time< Observer , Time >( t , observer ) );
    return t;
}


/* controlled version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , controlled_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    Time time = start_time;
    Time time_step = dt;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        detail::integrate_adaptive( stepper , system , start_state , time , static_cast<Time>(time+time_step) , dt ,
                null_observer() , controlled_stepper_tag() );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step+1) * time_step;
    }
    obs( start_state , time );

    return time;
}


/* dense output version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , dense_output_stepper_tag )
{
    // ToDo: is there a better way to extract the final time?
    Time t = start_time;  // Assignment is only here to avoid warnings.
    boost::for_each( make_n_step_time_range( stepper , system , start_state ,
                                             start_time , dt , num_of_steps ) ,
                     obs_caller_time< Observer , Time >( t , observer ) );
    return t;
}


}
}
}
}

#endif /* BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED */

/* integrate_n_steps.hpp
aaw+aPruyCi3HagPmMlDBe5zG2tqLwSjshyE8zjyfXgCqbpthdjOKnpyjc1FqA3SOcQDEdnnPNV1BP8jw9PpRBKeUdBIlpuAu2wYUhfRtvCeYmDZScR+HZwMj05NlEkSQ20AC3clr7s24yFYn82FvEwpOw10JTGJUhghNJuq94ZHdBZIJYSHWbqdWGIub11y18VLsfpapqIHudS6qg+SN1ypCNKdCkBhNAvdY7HsFASWhDadTkaFdkN+gcJb58B07Fs232UfOBPnXpxPrraGVBmCyI6nEjzZ2KSZlM/LQmGG3RGbcKHU2mjyyVLT9VG1Yak7GjXcfNkAWrdJbCr8euWLgeyes4xYS6fVd1PirLgQtkEW3tvL053baxNxsXoIl2Nd9Sx1ZaJTGla5hIQgWHr3uXZW285C4Z2F1IZLjfro1T3dv2NTG7b1LsJPKSqs3NybAL/XK1//Un1wTG0lJlplwWZRBsiSO3L16GGM9XrCHsws+/zSSiBO21EQg9sCzjygO8U84GFqyZ4qwAzI5dEdaDongSLuUk4EqOj4qhDAi45WIHIooKvS/qKhDayhVoGrnIoQdv/JEygQLgDmCetpJZwAT0QUFZhJLSZhiS1RXKiDn36qoJEuNlxyebEdcn/vbG3DiA5XaOyM
*/