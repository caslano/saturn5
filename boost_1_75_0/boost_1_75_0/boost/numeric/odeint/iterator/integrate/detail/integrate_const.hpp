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
Xx2CY56a/PvRiO2sWGbzinyZlQ8ay19kCPNMDq1pfVOSDsJD7kEsasu6pmJiaNRd+jeF9jt0Bk/eM2zvMi/eGuzf/7XMbpcGSZeBnIH9fdycB4ZIZL7dcbbMWRvUg5gKCsBwmY5uhO/9rjwPgn8SZL0snBNuc2JuGxRCmG5yIU2MLG7l/Iz1foLX3TRGU45qyZbq3mPxdHyxibK7i6OPkNrwrtPbEJw931KKaaWAivjmltAdFoflBbaPfpKDjH1ltkyxDTT4zOAvkXyD8VhRlIP54IUBiopGuNDEq280Uw5Ss6bWCYesZljzzAMhO3y5j+NKEgcREh70nf/SuAGgXzjd3/E8pZsRxKLqlzCQnRBdb11JFhmEfH0ZAFNsCOC7IlNRkM+lkCRt9QDOW3gjiVLRn/lCF3Vbn/71LOA7WMadDPlIr56v+lEz8ct6yBBeLeoGjwFSLZ5/lb2InS3sVojqMRWbzLZcjQP6Nk43pJf+iBEywPjdHuIbtsUbMSOqZVzYKhIrt9JU/8vW7shoLZm3KhL3ZgWaUrJ3P3mFjOIy6UxGT9cvaHJzhfk23RzmFg1YBpDJ4FiPUiuoQynuH8ay8eQ0YNIuqvG8G9cJXHe7DEfNIn0yY7NUhMFMz/7UJIsacPi9YQNTcZL3GuDcu7IoDXz1Kpgb5d7j7wlY3oD6EK+d2fJNt2GSdH+zu3UrtY/Tn+yrp+jLFPq2
*/