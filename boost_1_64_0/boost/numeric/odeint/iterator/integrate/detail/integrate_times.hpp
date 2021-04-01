/*
 [auto_generated]
 boost/numeric/odeint/integrate/detail/integrate_times.hpp

 [begin_description]
 Default integrate times implementation.
 [end_description]

 Copyright 2009-2012 Karsten Ahnert
 Copyright 2009-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_TIMES_HPP_INCLUDED

#include <stdexcept>

#include <boost/config.hpp>
#include <boost/range/algorithm/for_each.hpp>

#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>
#include <boost/numeric/odeint/iterator/times_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/functors.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {



/*
 * integrate_times for all steppers
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepperTag >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator start_time , TimeIterator end_time , Time dt ,
        Observer observer , StepperTag
)
{
    size_t obs_calls = 0;

    boost::for_each( make_times_time_range( stepper , system , start_state ,
                                            start_time , end_time , dt ) ,
                         // should we use traits<Stepper>::state_type here instead of State? NO!
                     obs_caller< Observer >( obs_calls , observer ) );

        // step integration steps gives step+1 observer calls
    return obs_calls-1;
}


} // namespace detail
} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_DETAIL_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_times.hpp
zI+MiI1XIIOIusALAJPLd+N6BbkgUQDI8C1vYMt5EpDlWLuQDU3Vxl72euJHOUlRsrPAxBoF9ZHli+WoKtultTyrUYkYO1jl1GP3t8UAeS+E63toUrPUtTMRBVcuexYLzfjZsm+bXSL0Ji9jdBXKVTqfYMYtDogR8BSQwFXpncZ3oHcvrktOYL8c+o6IuteBfQWv8adpENMtMHJoJqsCsOlbdBvQDfZvpK1qQCmhkHi78Z3XSqg/LQbcmYsZ4d1oJNF24mXHJ6LzGMH21a1rvKgaWwB5jVXQhjyBV6uDLGUFPOXRBgz52h6DoXzrzBXcIX15PTHCTtczespOjGdgRCXsEc7PDEUOJRBhedoP7byQb3i8zxvO8iK4e2eoZS1wRw4fgxZkGBN0y0DAXAGDSVWx6sTKj8IGzvBF5AiYT2I8B4//jmaVhn8jGUtN2UHJBLoI7GVPN762PF9wv8KEwm4DUjwk4XckRqgyLaFRkpdmpIEs7C5/PbjCqxeOyyEl+3UW0FEb1Oqd0wuzq2K//jKBtcYQcat8dCnW7dLQ/wpdOg0raOWfnZGYqQ==
*/