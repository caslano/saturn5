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
pBchhiZIQOrMARdTZDhqUnAZL4TgKzXTeaiuUH+Rprukm9ohtW/g6xMBYU0X2gp47ruhvoK/0yp8Z0AW7bM8GZqkR/MqGoYsmcj/F6sVxd3Cy29f4mof6sqRIEc0eb5C0X8YO1ie0HGACtglXO+tKGjpcVSKUjDYgbZNvWQpe8RkNBCc/E6zMJITgAwMyJVVRrjzrWXn5bjqYxJaXkh0P+wekIdtGgxtFvQ7oDpVfdQjnxpv43SWuYreZaZZu65Qmos+TaeEMQSHlPTQBmTlyyDsvvDMsJ+xVeUKVd6W9nio7bx9dI2Jk7MYrvZbZP7+s19U1aOKwKKCTo5rsJErRxcWB/dXhz5z1zl/RvpCJS/JDJibkErfHGNxFJ+ERnu7eJtjDnee+PA2sR0LlzCAuYQ9mCqd7wzegZ5yvbLrVUr+qX4W15oEiAPQ29vY2Y+ZVa5mtlFBrUTXtfVUUUbPLFFj8k+3A14ns/hcgvT3P11K84fSMQqQ2pGhLdFnhbGlugxQTmbozYcE2Nrh6JiZjMgunG3yrCl/e/Qj4ugLFn8N28AQgjVc+lUHWKgTVK27LigG/WS0/ZIkGvnWIRhjJR1GzSaVFDXQLZ0rB4EBqG6BC1ldFGT2EcYZfe5c1S4DmjQX60PRgfbhBC0lNHs6TyqV1tZxLpHKsqHr7e0k2njVsCFFWIUbPZA+lRyyEu4NUlNAG/m8jCi9tme0
*/