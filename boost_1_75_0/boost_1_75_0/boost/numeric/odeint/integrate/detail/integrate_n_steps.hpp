/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp

 [begin_description]
 integrate steps implementation
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Christoph Koke
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>

#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

// forward declaration
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive_checked(
        Stepper stepper , System system , State &start_state ,
        Time &start_time , Time end_time , Time &dt ,
        Observer observer, controlled_stepper_tag
);


/* basic version */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        st.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >( step+1 ) * dt;
    }
    obs( start_state , time );

    return time;
}


/* controlled version */
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , controlled_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;

    Time time = start_time;
    Time time_step = dt;

    for( size_t step = 0; step < num_of_steps ; ++step )
    {
        obs( start_state , time );
        // integrate_adaptive_checked uses the given checker to throw if an overflow occurs
        detail::integrate_adaptive(stepper, system, start_state, time, static_cast<Time>(time + time_step), dt,
                                   null_observer(), controlled_stepper_tag());
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step+1) * time_step;
    }
    obs( start_state , time );

    return time;
}


/* dense output version */
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , dense_output_stepper_tag )
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    const Time end_time = start_time + static_cast< typename unit_value_type<Time>::type >(num_of_steps) * dt;

    st.initialize( start_state , time , dt );

    size_t step = 0;

    while( step < num_of_steps )
    {
        while( less_with_sign( time , st.current_time() , st.current_time_step() ) )
        {
            st.calc_state( time , start_state );
            obs( start_state , time );
            ++step;
            // direct computation of the time avoids error propagation happening when using time += dt
            // we need clumsy type analysis to get boost units working here
            time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * dt;
        }

        // we have not reached the end, do another real step
        if( less_with_sign( static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            end_time ,
                            st.current_time_step() ) )
        {
            st.do_step( system );
        }
        else if( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
            st.do_step( system );
        }
    }

    // make sure we really end exactly where we should end
    while( st.current_time() < end_time )
    {
        if( less_with_sign( end_time ,
                            static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            st.current_time_step() ) )
            st.initialize( st.current_state() , st.current_time() , static_cast<Time>(end_time - st.current_time()) );
        st.do_step( system );
    }

    // observation at final point
    obs( st.current_state() , end_time );

    return time;
}


}
}
}
}

#endif /* BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_N_STEPS_HPP_INCLUDED */

/* integrate_n_steps.hpp
UKmyj8lcDJ4Q3IanMJybr8DYFjPbAZi2+Pb9L3bl7Lbdn6ESpeNt5fzFszU/wcP7WB5k++o3OmIXorxCUkHXfYwfrsZIsiV++uNcp9nvDYudCZbkGOk5XUA5xh9Z7tFeCuTSpJypmZrNNkRLaoJDAqJ9GqHFUv5zouFIdfDh6acFjwmdFG6WAWgki4JzODFZus+w1QnNRlr0w5D/qe5+jdBjTsksJ/C71EDygcfyJ3VHZYYfm48FVm335LYCPpbWEXcaylVF53Lop6AItf0GmtsbAkI2hZuLcHx+gAfiSqoHw0PcUEmkfiUmKGDlJuysqQbyev4E0/Gx0IzgDt7j4x5Wwcc1h9W2f25d5R2xbcjmBVd6O3RX8LIbe5yxARVqM5eHsU+io1Bp0cSryJMTHOvpcx42Lo+aDEe1JSPOYG0a6/q2Tfv7WLp9yfiFT0E8z62Xdfm6Wl+G0sTLJzx/Cg9Z/8capxLsuWfkh5AnO7UcChTA9i+HaItUfXBxcgosudzmfSHsyfkBvCvGSk7XlVSWMD4q7U0sEhfvbIBcafja4o5hUo2BrWGtJmLi2q6WHXg5MuY7sodjut90HzlWg1GUbSd7BGAV0GT7WV6o7YNhYb1uPakhEjdTa38V8G8/nh52WbMVLkdtlm+YRrRoobZN3HDtjQ20SZO8nJt6Kp13Wbm6yceTa4kQszfMhwO+GYCWTQ/7ZkH8fpYL
*/