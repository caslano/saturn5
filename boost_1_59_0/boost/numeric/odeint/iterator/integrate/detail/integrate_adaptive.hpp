/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp

 [begin_description]
 Default Integrate adaptive implementation.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <stdexcept>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/iterator/adaptive_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>
#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer>
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag );

/*
 * integrate_adaptive for simple stepper is basically an integrate_const + some last step
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    size_t steps = detail::integrate_const( stepper , system , start_state , start_time ,
                                            end_time , dt , observer , stepper_tag() );
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time end = start_time + dt*steps;
    if( less_with_sign( end , end_time , dt ) )
    {   //make a last step to end exactly at end_time
        st.do_step( system , start_state , end , end_time - end );
        steps++;
        obs( start_state , end_time );
    }
    return steps;
}


/*
 * classical integrate adaptive
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
)
{
    size_t obs_calls = 0;

    boost::for_each( make_adaptive_time_range( stepper , system , start_state ,
                                               start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );

    return obs_calls-1;
}


/*
 * integrate adaptive for dense output steppers
 *
 * step size control is used if the stepper supports it
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag )
{
    size_t obs_calls = 0;

    boost::for_each( make_adaptive_time_range( stepper , system , start_state ,
                                               start_time , end_time , dt ) ,
                     obs_caller< Observer >( obs_calls , observer ) );

    return obs_calls-1;
}




} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_adaptive.hpp
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
*/