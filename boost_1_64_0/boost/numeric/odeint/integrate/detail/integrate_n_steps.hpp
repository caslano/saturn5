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
ze6+9XJfpxRn8gZ5XvAg7hM+qr9vnV8SbkAOyVXHOCgWw7XVnTcaQGZg6inpIsavlLvh8TtEJbpOPB/xC1Wn0qhO3bZSApN4pdM5553A+QH1Y1p8AJ0Gf6bFdm12+3HmTafaeD7KxfKfRL7au3P9s8iccfptbZxnm+LZ6qH5jNCkH8F6KZp/MHx9OM9ynPxqD21X5b6oW4+nndPj8c+19j6mtEtkWxj8BTCmGZdBygHGekVt0DbjRds+4gktzJBSB+KYNpLWK8qnetj4VK8y/bDxoR5SPtTrxod6w/hQ/2QafU+a7Dvy22z8kX+r/J/RZ5J2AVqn4saZ+k6oi9I/M/V9UNV3J+Do+u6MtK7vJKQ1/1ZTv10k35W19dtV5V9Uxm91VX43k7+tNJ7/Dmkf8uPtm1zHfmee7vcp2XsQMfqSfyHvVe3B9g4UCr6lOYX6jLTDKTM4vR6cqRqH7bI404ysLyuTuuLbTtpLWeyj2nKVR1bvQb6Wz1fK/Do/xcy5FYauldG+RkZ/U+PtUtU2bSveV8e3ECvi+rW/qeNspgGPr6EQ134Pzq2L5uevl8R9vwvK5DtHy3DA2MIa1da9dx++dlSXayvx2Y55HCe6Tw+os+Xx1k0dZa74/7N0uJ/zAeBpGb5r9+hPy/CDrAvg0g8qffd7dFvwZ8ZmPfD1XPbu3fVYIL6it8iMlS+a2ESLjeysfi6hrJo8sjq0zuLjnRbD712mPstIr4H0wt8L3W8ptxzpFfiTcYWz14aunYNbjRxf3kP080JzT3QlcL1rQ+5OhnmdXYH0neEjWecT6eschTRjnEhcHEdvEMFvsGug4tYUCRwXBgS/OMClj/a+rhBbYuIQBkx936aU8d4T9NNW1Sk/zdHXaycqne+ewchlXD99xMwrxxhbdyz7Nkk8kbnktTOPfgZoyLo+/435GZ0s18Vyff5Y6LApcd/yOOBrH7gDaesDpwAryfVFkIOVUubAy/nBq7V8x6wnBdATmZfXivwgS4GvM3JdT7l2498Qq0fkzLTgHsW8Y4jbX2dlq+4tGtluUHTAK+YDpzVPpvU31Eye3zxK2fhZsZjSWLStz2QGm7oCxlhG/xCGdjfzvPYmkSv6q2FZa3J5GIf5sAixu2Mok3Pq/ZmUdbNPp3eAXtgvW9gvB+XOoLNdTV1YhO1e3Z2Lq873F6h7J4S6x3jS2TjkH1XtLHb1OqzxMKEjdTIZEptf1wH3pNalOjOHxary0mh1Wcm6nDisLi2pzu6BblAiRVOpkTBUXMvZEke7JbWxqW91/+L+wd522i3qQCw/eOlY6sFJw/WAeP2d7rCKkJNqjYBkY9RXurrhbE3/YHdmba/0m3pToIV1+eTwugx248JjeIFtRRZbauHPJv9K8i93/GW/WfhjRQ6xzpvxAj1y8O3Md1OG1aHJla3v62pVBaQWfgSrP+yjVANul6ITXch3qUsObt5VyYAcaKyi/pw8TH8a+zrbB9JDPVC7LpIIu0Jqlx9FYvxbHWrAZj0VSOmP5AVZWZ3i0R3iQEs7wdEozkgYqM1Kny35H/SBe9eFNiXbH6ciTb2wxYKRx7ucOT+tbixrwAuCd+eZO0935buCQynPM4bJsxVnglKDPstg89ha/1rYW7B7Lu4VZXbyCO9jnFUXzS/rsYXI8Y66w1ZD7wY3D2SAWZ8d/PE3RVIOAVp5mD7TVBKWVeePSsM0zx4dSp/g7JhPwCbQUJoB4MkbTddQnbbB9r60n2B+BJHbuZTbiDzq1wymUvl5WATL44vk4d3Pe4syCemeP2rdV7Sn08fjcRMvcYPgr/uF5DGK7+BlYHNt/S8m7Rbq7BecrqyHlxHp2HlRuj2bvsA=
*/