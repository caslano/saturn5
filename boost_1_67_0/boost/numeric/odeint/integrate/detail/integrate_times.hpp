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