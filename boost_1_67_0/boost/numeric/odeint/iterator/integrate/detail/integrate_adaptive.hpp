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