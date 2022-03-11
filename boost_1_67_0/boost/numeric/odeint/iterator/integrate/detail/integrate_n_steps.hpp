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
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
*/