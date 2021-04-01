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
CxokpVqMmfJOhyNw7lNBPA7rhkK3qkBVcfG7jccESdin9qaqxwCyOwiQBJrshkF8iqbLXg28fm0lCOG1DBaPfcL/mTEUCPd0k3T7Kn802VNgrN0ohE4zunLnvNTPDAI6rSG035BmDkhv9ntiknMQGzOlGY8B0ZSo6sN3ykHfTyDS6TotNhaRomIxmq9e4f4SCLWgN5kSQ50CcvpiFZnFlR51/EtH0s7PWOcDo6zlnnj0NhH+Z74NlR1WR6d8+ztJTUXYHMT5xd6Qs81F5OXwgOQw+5yT8GnsnMqEDh5WF5KaIFNnkjv/9wK19Y2gVqeiMmKjC6aIVynitWFNi71YY5wjpkJEr0r2j8Zzk/0f6gPrCtNfNgvcY2ZtnvL6Xw5E5ZkB3FG+A+0pRhjpU8HZnlsos27n+0LMTTFn6IITEkBAG9zo8wmN8Gz2AAvD27jBaMU2DsifvYHMOmevDJSEZot6+xA10b5wKyfTLoRkCDzkCbrOijbTwvzO6+ASACg5ms03y4Z7cE4xSQCr7QvDszMFSXWfxzj/NlCvXU60c8fIcOHHh7M6zCxD1w==
*/