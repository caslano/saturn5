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