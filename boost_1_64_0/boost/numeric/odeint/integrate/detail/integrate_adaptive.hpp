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
GEf0c2WNc3B1Z111dW3UhCDrI5cZH3kg1BsdM4lnsyocrD86P00eMz1xlGZ74ihV5YmjVOuJo7QbZHpAjf52XrTEuNZLRo+jNHIZFw+gJr6m9AGkqbO0yxOC+dTZM2KxQuSN34NrovH3ITV3ARabu+qz6ULBFf9a0tDjWLrSpPc36YyhXyv5rJvxl1k36y8fBpjOt/7yMpOPesbyl5v8SpP/YZO/v8lvNfnW1znc5Nea8keI7GG/zD6eKvtrT3yMo6WvrB3V/ivzxK6emsd/Pa6GttDgWP+1g3zP1PFCqCO6XlN0O2g/rP8KmNeHWSt1IY7ff10nMqD+aNp+/7XXyHWK6bN+k2/fxN4g+U5Ots/Ten7aquaarXIex8bAmz05Xxy8ouB48c/gC7k/4Kvy5rt6s8jA4U7x7KOeoOezrXH/97IgHo9jQL2Jk+EffWD2K9/3snIxY/WTMR1kLG/TN1uBs68+Y05fR2Ll069R941OFnvr3ipAhN61GznThdYzBoH99K6BjKFcKK9TauQMN+vkJCT1E5+tSK3/FtN/+6yb17NcZB3nc6oNpazLpgNrE/iHdVEQ1CX33SDnIlVf4D4Q6HnbOQbabs6oUW/rGL/sTOPXI9/xPMv0v/Xbz4lsHWjLd9AXzDz2RY+/f56yH9aWle7lb/+FwNHfBKfm+Sa42NAaXm/cT5F2ubUs+57KZcbmkFeMxuUcb6vmqLdPOH7LC6P6XwGcY5HPP7H31OxtyJf9OsHTNvxrqq7EYT7js/Hb6dwZ6t1QpKuYBhvuibGsfu9GaLu8K8xcdp3YYkmD9pY9I9oLHC/mk950OaPa3NBy1Iq23F7Uokam8X0xyY3zkM9NKNOVSmMzO9prin5He0tTc7QaFrozrDzfutDQuCWi4eJsOiJMgAr2P/S7x4cvamzlfjX9Q8I6hlbjThf3IG8Nx/Soe5ALgo2kfRVsp6uB+g64GTSKHEz27b8FWLGDuaq+lC1b4mCItN2p3oBzMPkG/DbKTnN1RT155+c2ZWNmh/jK1uVSqGel127kx3ex4GI2Qs7ufLfGrIkjrd/OgR6hDHCpUzre510y75lxYsYH5727LT7roMto/O2j0S+M499Tk2/c8s+W47i9V9mioUKHx3WquF91f406m8nxYt60hFzj56d+jDL6jvEuMlejLjJOM4bXg9J2hSd/VrYPmTZoXE33kbHKyNi2n4ttI32Dg7Y+ViPf+rZ//XQnBb+SMnn72JZ5HHnRPuPo/azKOun/xpZ1OGORwS7BU96xQXwzNp4G7HM5e9eK5/xalx/e0tCI1y8Pa15+RHPwMu2fzmtb2ppsPLKtsTl8A5NvEer8I+uqDlxZo1AiGhM1zvKG1hXJ1rb6FUsbFyXxyOaK5c2tuEsQvnlaSPv6DOqW7sSl4f6hwc5U9laAgvBewLxs/U/6T8iAb3PitACYNbahfmybZK2sdt/Zypb/gby4cifMFCi066uFF+gtXX5I0p26SbYdtaIxyxG0ydOiRKIRmQ7Px3ujDY0tbcHB6pzEs6gb6tHTvyaJNYrBzW5JIlvD4Rmuns+xnmx3/dImXEpH00ORtx3emqsq+9aLQxUIq8hzHH48B5E+9uI0NUdYIU5hXn7on6bFTY2L+EblKPVibwb6/crnsv3Y3tONCRf95l4WH0pLj/oyncwSXIv6Y425Q8s5uzCkjLTEfkaacyVxMM+GvdHdpdd3SghzqITPcHNtButVqEH0dgPj86c2aR4VSMd4uDNja9vTa5PtPWuCHOx94XtkDqTXoADT608OR2j9KVxHCERzsnX7PeAHBG6M5WB/Bmx+MExwwSy+Z/a88gkWOLlw0RY/R3xTGJo=
*/