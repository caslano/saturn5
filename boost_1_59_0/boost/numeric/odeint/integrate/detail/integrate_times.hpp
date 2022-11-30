/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_times.hpp

 [begin_description]
 Default integrate times implementation.
 [end_description]

 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED

#include <stdexcept>

#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>


namespace boost {
namespace numeric {
namespace odeint {
namespace detail {



/*
 * integrate_times for simple stepper
 */
template<class Stepper, class System, class State, class TimeIterator, class Time, class Observer>
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , stepper_tag
)
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;

    stepper_type &st = stepper;
    observer_type &obs = observer;
    typedef typename unit_value_type<Time>::type time_type;

    size_t steps = 0;
    Time current_dt = dt;
    while( true )
    {
        Time current_time = *start_time++;
        obs( start_state , current_time );
        if( start_time == end_time )
            break;
        while( less_with_sign( current_time , static_cast<time_type>(*start_time) , current_dt ) )
        {
            current_dt = min_abs( dt , *start_time - current_time );
            st.do_step( system , start_state , current_time , current_dt );
            current_time += current_dt;
            steps++;
        }
    }
    return steps;
}

/*
 * integrate_times for controlled stepper
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , controlled_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;
    typedef typename unit_value_type<Time>::type time_type;

    failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
    size_t steps = 0;
    while( true )
    {
        Time current_time = *start_time++;
        obs( start_state , current_time );
        if( start_time == end_time )
            break;
        while( less_with_sign( current_time , static_cast<time_type>(*start_time) , dt ) )
        {
            // adjust stepsize to end up exactly at the observation point
            Time current_dt = min_abs( dt , *start_time - current_time );
            if( st.try_step( system , start_state , current_time , current_dt ) == success )
            {
                ++steps;
                // successful step -> reset the fail counter, see #173
                fail_checker.reset();
                // continue with the original step size if dt was reduced due to observation
                dt = max_abs( dt , current_dt );
            }
            else
            {
                fail_checker();  // check for possible overflow of failed steps in step size adjustment
                dt = current_dt;
            }
        }
    }
    return steps;
}

/*
 * integrate_times for dense output stepper
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , dense_output_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    typedef typename unit_value_type<Time>::type time_type;

    if( start_time == end_time )
        return 0;

    TimeIterator last_time_iterator = end_time;
    --last_time_iterator;
    Time last_time_point = static_cast<time_type>(*last_time_iterator);

    st.initialize( start_state , *start_time , dt );
    obs( start_state , *start_time++ );

    size_t count = 0;
    while( start_time != end_time )
    {
        while( ( start_time != end_time ) && less_eq_with_sign( static_cast<time_type>(*start_time) , st.current_time() , st.current_time_step() ) )
        {
            st.calc_state( *start_time , start_state );
            obs( start_state , *start_time );
            start_time++;
        }

        // we have not reached the end, do another real step
        if( less_eq_with_sign( st.current_time() + st.current_time_step() ,
                               last_time_point ,
                               st.current_time_step() ) )
        {
            st.do_step( system );
            ++count;
        }
        else if( start_time != end_time )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , last_time_point - st.current_time() );
            st.do_step( system );
            ++count;
        }
    }
    return count;
}


} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_times.hpp
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
*/