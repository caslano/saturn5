/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_const.hpp

 [begin_description]
 integrate const implementation
 [end_description]

 Copyright 2012-2015 Mario Mulansky
 Copyright 2012 Christoph Koke
 Copyright 2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>

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

    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    int step = 0;
    // cast time+dt explicitely in case of expression templates (e.g. multiprecision)
    while( less_eq_with_sign( static_cast<Time>(time+dt) , end_time , dt ) )
    {
        obs( start_state , time );
        st.do_step( system , start_state , time , dt );
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        ++step;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * dt;
    }
    obs( start_state , time );

    return step;
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
    int real_steps = 0;
    int step = 0;
    
    while( less_eq_with_sign( static_cast<Time>(time+time_step) , end_time , dt ) )
    {
        obs( start_state , time );
        // integrate_adaptive_checked uses the given checker to throw if an overflow occurs
        real_steps += detail::integrate_adaptive(stepper, system, start_state, time,
                                                 static_cast<Time>(time + time_step), dt,
                                                 null_observer(), controlled_stepper_tag());
        // direct computation of the time avoids error propagation happening when using time += dt
        // we need clumsy type analysis to get boost units working here
        step++;
        time = start_time + static_cast< typename unit_value_type<Time>::type >(step) * time_step;
    }
    obs( start_state , time );

    return real_steps;
}


template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer , dense_output_stepper_tag
)
{
    typename odeint::unwrap_reference< Observer >::type &obs = observer;
    typename odeint::unwrap_reference< Stepper >::type &st = stepper;

    Time time = start_time;
    
    st.initialize( start_state , time , dt );
    obs( start_state , time );
    time += dt;

    int obs_step( 1 );
    int real_step( 0 );
    
    while( less_eq_with_sign( static_cast<Time>(time+dt) , end_time , dt ) )
    {
        while( less_eq_with_sign( time , st.current_time() , dt ) )
        {
            st.calc_state( time , start_state );
            obs( start_state , time );
            ++obs_step;
            // direct computation of the time avoids error propagation happening when using time += dt
            // we need clumsy type analysis to get boost units working here
            time = start_time + static_cast< typename unit_value_type<Time>::type >(obs_step) * dt;
        }
        // we have not reached the end, do another real step
        if( less_with_sign( static_cast<Time>(st.current_time()+st.current_time_step()) ,
                            end_time ,
                            st.current_time_step() ) )
        {
            while( less_eq_with_sign( st.current_time() , time , dt ) )
            {
                st.do_step( system );
                ++real_step;
            }
        }
        else if( less_with_sign( st.current_time() , end_time , st.current_time_step() ) )
        { // do the last step ending exactly on the end point
            st.initialize( st.current_state() , st.current_time() , end_time - st.current_time() );
            st.do_step( system );
            ++real_step;
        }
        
    }
    // last observation, if we are still in observation interval
    // might happen due to finite precision problems when computing the the time
    if( less_eq_with_sign( time , end_time , dt ) )
    {
        st.calc_state( time , start_state );
        obs( start_state , time );
    }
    
    return real_step;
}


} } } }

#endif

/* integrate_const.hpp
DekApX8wlS2jQCO/1YpKdK4HShKK4kpqQG6/+a9mffbFKfgDrNfztvRL9K9fNH7Iy/FvFeRzr075soBBduY+Fb9V/qq+VV6ria+jvW7Wst4QmsiTOs6sjGi+CZiyQziR0Ixx0dIYN0JZG2SyQ+uSbGta1ojBtGwFx7/BaWtpbEwuqW9dgvfPlR36N8dWeFoEnY/O0YbIk0P7nD3L+eHoXjLXsjmmXDrU50DGVQ5mx1a3Q5Rx1U0kfd63E2c4cWs9Fr+eMBl/fLsU510B1mO1PIQRleM0PAs10N+5NhmO1mQ3ltjTsBU8yxnUqjMmTjp4e110n8kR3rMepUyoOxNqRXcm1sa/cwuRnlVp9kVrRW8X7GVw6ANNqo37e8V8IwK8Yrr5NqT1t9auTAMe30ck7tGToz/N6+21rC9xjpkcr2+JyV9i9oGnmPwZZv2yVLUXZfl2qNnLFBzUj9/wBqeslvHsOT555sbhB06HoGdM47WIdHpIdGcqyhYFObOV050Sj+4s5r2vdyndgY5m8M4iIlRsTqZgZrVK+HL0PtiLZu1y79o8byW/JR4TSvahTmibVF4b76P3SB85XbMxg2cQ/09cn99f6aNO/97kzzD5fzb5f9Rp2kirl4C58W7ve82WNjCty/jfMpsr7XQ4fzL2vtrk2zXdGpNv54s6k291/f0m/4+m/IG10Xyzj7IZH2D/6XLzTf99EGk9j9UBR/P9EOm+oOaxetLltwb0gnMqvzMXatsBb66hlnMwdYS4Bq8waJS6EM/c1SI+eLDvBX9GMBz/UODreymlgaxNlRv7tgzpKE9khPHu8pYzjfoyLTqq06AZj0tAPkcbu9dWG8+fij9d75Um3+rCkSr/dc965yrTxzNo39D/Md/mGMCfoa7LGMKdpVrt/xDH+D/HmTEjODJmOmqlDOVCPrRXRvdmmvlsNfIP9u2T852rQu1z08+oYLyf7Ps4lbwDu1bZ3Jn0PY3XSV91RH+zoQ0fRa5UHJTzOdfVUsas93rHFwzSgaNdgLr0qLoUjtEPXkx6U0lPzzeXljk6/X2rtS/V3ee89txXYncqDTqHUh59qg7Fug7uTlt8hrB5dh6aasbSgOgGxnjcnlZQxwZFR1mGukB6dh92CLBDR/2OGE/dJ5QcXyvnUad6/JqKrF4XxuePLcYOvZd6C/1jWtoCWK4t0+nHn1gbzy83+1wncbxON+P1k4BfVUZ6+r6Msl2bTF98mulNbN8TLAu91HcdoLdi3z9rfMHPmb46VdU/pPNBM2ecbvKnm3H9ecl3tAGPyecsl6/i+at1zE9SN6wMzq2V9chyzkOYo2E7BV9sz87BF6UOLs/a0POR71/HXnJEUzO+oZJJp2G5FHXqQsqukmP9+BI11kcsW+DkNzEbDy2k80np+0tqoz9rYy/l/Fyuyn6ZddA6iw/2cd6bWr4Ci3itS5Pwd1OD4TVCd+XJvakD+pPU2e1tSJs3aLhvzjipSr8nwR/4GvX7SlXPDYU8v1vK+xrM030UmHnwGurJBs7vAL3k9Ih3sHZj/a7z1G+vEqlbsiRev2+yfjewnNzTlPrd5PK4J1ei7paQ/nuC6G+6S8vvW2pdWvHbJfgW+d2q+bENf2cbbnN56l4e9BV88RfXiUno2dtJ77u2DJTk5HdGd+7sXb47aykfwfPf+4N8vqfG2ozA5aMOfDfP0sZY+z7rs93UZwPLrfLU5x6W2RDIGYijSuLvvd1bG9Xzvlp/Pe839RR+/no+QJ4/Zj21DTouwPfbKL7B8ubFyehGpngIJiPnJzxIHmOh2WSJ2hzanoeUTi7mPvE6+g3R/TVcNA3kPmuh8qcecd+xcl5wkTtzYM8LujU=
*/