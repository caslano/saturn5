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