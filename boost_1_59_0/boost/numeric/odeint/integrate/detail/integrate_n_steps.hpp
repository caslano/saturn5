/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp

 [begin_description]
 integrate steps implementation
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Christoph Koke
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive_checked(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer, controlled_stepper_tag
);


/* basic version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        st.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >( step+1 ) * dt;
    }
    obs( start_state , time );

    return time;
}


/* controlled version */
template< class Stepper , class System , class State , class Time , class Observer >
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
        // integrate_adaptive_checked uses the given checker to throw if an overflow occurs
        detail::integrate_adaptive(stepper, system, start_state, time, static_cast<Time>(time + time_step), dt,
                                   null_observer(), controlled_stepper_tag());
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step+1) * time_step;
    }
    obs( start_state , time );

    return time;
}


/* dense output version */
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , dense_output_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    const Time end_time = start_time + static_cast< typename unit_value_type<Time>::type >(num_of_steps) * dt;

    st.initialize( start_state , time , dt );

    size_t step = 0;

    while( step < num_of_steps )
    {
        while( less_with_sign( time , st.current_time() , st.current_time_step() ) )
        {
            st.calc_state( time , start_state );
            obs( start_state , time );
            ++step;
            // direct computation of the time avoids error propagation happening when using time += dt
            // we need clumsy type analysis to get boost units working here
            time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * dt;
        }

        // we have not reached the end, do another real step
        if( less_with_sign( static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            end_time ,
                            st.current_time_step() ) )
        {
            st.do_step( system );
        }
        else if( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
            st.do_step( system );
        }
    }

    // make sure we really end exactly where we should end
    while( st.current_time() < end_time )
    {
        if( less_with_sign( end_time ,
                            static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            st.current_time_step() ) )
            st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
        st.do_step( system );
    }

    // observation at final point
    obs( st.current_state() , end_time );

    return time;
}


}
}
}
}

#endif /* BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED */

/* integrate_n_steps.hpp
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
*/