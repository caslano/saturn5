/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_const.hpp

 [begin_description]
 integrate const implementation
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Christoph Koke
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>

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


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag
)
{

    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    int step = 0;
    // cast time+dt explicitely in case of expression templates (e.g. multiprecision)
    while( less_eq_with_sign( static_cast<Time>(time+dt) , end_time , dt ) )
    {
        obs( start_state , time );
        st.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        ++step;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * dt;
    }
    obs( start_state , time );

    return step;
}



template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , controlled_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    Time time = start_time;
    const Time time_step = dt;
    int real_steps = 0;
    int step = 0;
    
    while( less_eq_with_sign( static_cast<Time>(time+time_step) , end_time , dt ) )
    {
        obs( start_state , time );
        // integrate_adaptive_checked uses the given checker to throw if an overflow occurs
        real_steps += detail::integrate_adaptive(stepper, system, start_state, time,
                                                 static_cast<Time>(time + time_step), dt,
                                                 null_observer(), controlled_stepper_tag());
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        step++;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * time_step;
    }
    obs( start_state , time );

    return real_steps;
}


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    
    st.initialize( start_state , time , dt );
    obs( start_state , time );
    time += dt;

    int obs_step( 1 );
    int real_step( 0 );
    
    while( less_eq_with_sign( static_cast<Time>(time+dt) , end_time , dt ) )
    {
        while( less_eq_with_sign( time , st.current_time() , dt ) )
        {
            st.calc_state( time , start_state );
            obs( start_state , time );
            ++obs_step;
            // direct computation of the time avoids error propagation happening when using time += dt
            // we need clumsy type analysis to get boost units working here
            time = start_time + static_cast< typename unit_value_type<Time>::type >(obs_step) * dt;
        }
        // we have not reached the end, do another real step
        if( less_with_sign( static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            end_time ,
                            st.current_time_step() ) )
        {
            while( less_eq_with_sign( st.current_time() , time , dt ) )
            {
                st.do_step( system );
                ++real_step;
            }
        }
        else if( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , end_time - st.current_time() );
            st.do_step( system );
            ++real_step;
        }
        
    }
    // last observation, if we are still in observation interval
    // might happen due to finite precision problems when computing the the time
    if( less_eq_with_sign( time , end_time , dt ) )
    {
        st.calc_state( time , start_state );
        obs( start_state , time );
    }
    
    return real_step;
}


} } } }

#endif

/* integrate_const.hpp
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
*/