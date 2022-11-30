/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp

 [begin_description]
 Default Integrate adaptive implementation.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>


#include <iostream>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
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
 * integrate adaptive for controlled stepper
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer , controlled_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
    size_t count = 0;
    while( less_with_sign( start_time , end_time , dt ) )
    {
        obs( start_state , start_time );
        if( less_with_sign( end_time , static_cast<Time>(start_time + dt) , dt ) )
        {
            dt = end_time - start_time;
        }

        controlled_step_result res;
        do
        {
            res = st.try_step( system , start_state , start_time , dt );
            fail_checker();  // check number of failed steps
        }
        while( res == fail );
        fail_checker.reset();  // if we reach here, the step was successful -> reset fail checker

        ++count;
    }
    obs( start_state , start_time );
    return count;
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
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    size_t count = 0;
    st.initialize( start_state , start_time , dt );

    while( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
    {
        while( less_eq_with_sign( static_cast<Time>(st.current_time() + st.current_time_step()) ,
               end_time ,
               st.current_time_step() ) )
        {   //make sure we don't go beyond the end_time
            obs( st.current_state() , st.current_time() );
            st.do_step( system );
            ++count;
        }
        // calculate time step to arrive exactly at end time
        st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
    }
    obs( st.current_state() , st.current_time() );
    // overwrite start_state with the final point
    boost::numeric::odeint::copy( st.current_state() , start_state );
    return count;
}




} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_adaptive.hpp
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
*/