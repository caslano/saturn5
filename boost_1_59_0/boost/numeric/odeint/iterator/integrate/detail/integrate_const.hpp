/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_const.hpp

 [begin_description]
 integrate const implementation
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/range/algorithm/for_each.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/iterator/const_step_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
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
    size_t obs_calls = 0;

    boost::for_each( make_const_step_time_range( stepper , system , start_state ,
                                                 start_time , end_time , dt ) ,
                     // should we use traits<Stepper>::state_type here instead of State? NO!
                     obs_caller< Observer >( obs_calls , observer ) );

    // step integration steps gives step+1 observer calls
    return obs_calls-1;
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
    int step = 0;
    
    while( less_eq_with_sign( static_cast<Time>(time+time_step) , end_time , dt ) )
    {
        obs( start_state , time );
        detail::integrate_adaptive( stepper , system , start_state , time , time+time_step , dt ,
                                    null_observer() , controlled_stepper_tag() );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        ++step;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * time_step;
    }
    obs( start_state , time );
    
    return step;
}


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag 
)
{
    size_t obs_calls = 0;

    boost::for_each( make_const_step_time_range( stepper , system , start_state ,
                                                 start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );
    return obs_calls-1;
}


} } } }

#endif

/* integrate_const.hpp
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
*/