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