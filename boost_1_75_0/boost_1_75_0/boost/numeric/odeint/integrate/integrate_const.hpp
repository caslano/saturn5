/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_const.hpp

 [begin_description]
 Constant integration of ODEs, meaning that the state of the ODE is observed on constant time intervals.
 The routines makes full use of adaptive and dense-output methods.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Integrates with constant time step dt.
 */
template<class Stepper, class System, class State, class Time, class Observer, class StepOverflowChecker>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt,
        Observer observer, StepOverflowChecker checker
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end
    // no overflow checks needed
    if (boost::is_same<null_observer, Observer>::value) {
        return detail::integrate_adaptive(
                stepper, system, start_state,
                start_time, end_time, dt,
                observer, stepper_category());
    }
    else {
        // unwrap references
        typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;

        return detail::integrate_const(checked_stepper<stepper_type, checker_type>(stepper, checker),
                                       system, start_state,
                                       start_time, end_time, dt,
                                       checked_observer<observer_type, checker_type>(observer, checker),
                                       stepper_category());
    }
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time, class Observer, class StepOverflowChecker >
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt,
        Observer observer, StepOverflowChecker checker
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end

    if (boost::is_same<null_observer, Observer>::value) {
        return detail::integrate_adaptive(
                stepper, system, start_state,
                start_time, end_time, dt,
                observer, stepper_category());
    }
    else {
        typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;

        return detail::integrate_const(checked_stepper<stepper_type, checker_type>(stepper, checker),
                                       system, start_state,
                                       start_time, end_time, dt,
                                       checked_observer<observer_type, checker_type>(observer, checker),
                                       stepper_category());
    }
}


/**
* \brief integrate_const without step overflow checker
*/
template<class Stepper, class System, class State, class Time, class Observer>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt, Observer observer)
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    return detail::integrate_const(stepper, system, start_state,
                                   start_time, end_time, dt, observer, stepper_category());
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time, class Observer>
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt, Observer observer
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    return detail::integrate_const(stepper, system, start_state,
                                   start_time, end_time, dt, observer, stepper_category());
}


/**
* \brief integrate_const without observer calls
*/
template<class Stepper, class System, class State, class Time>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt
) {
    return integrate_const(stepper, system, start_state, start_time, end_time, dt, null_observer());
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time>
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt
) {
    return integrate_const(stepper, system, start_state, start_time, end_time, dt, null_observer());
}






/********* DOXYGEN *********/
/**
 * \fn integrate_const( Stepper stepper , System system , State &start_state , Time start_time ,
 *                      Time end_time , Time dt , Observer observer , StepOverflowChecker checker )
 * \brief Integrates the ODE with constant step size.
 *
 * Integrates the ODE defined by system using the given stepper.
 * This method ensures that the observer is called at constant intervals dt.
 * If the Stepper is a normal stepper without step size control, dt is also
 * used for the numerical scheme. If a ControlledStepper is provided, the
 * algorithm might reduce the step size to meet the error bounds, but it is
 * ensured that the observer is always called at equidistant time points
 * t0 + n*dt. If a DenseOutputStepper is used, the step size also may vary
 * and the dense output is used to call the observer at equidistant time
 * points.
 * If a max_step_checker is provided as StepOverflowChecker, a
 * no_progress_error is thrown if too many steps (default: 500) are performed
 * without progress, i.e. in between observer calls. If no checker is provided,
 * no such overflow check is performed.
 *
 * \param stepper The stepper to be used for numerical integration.
 * \param system Function/Functor defining the rhs of the ODE.
 * \param start_state The initial condition x0.
 * \param start_time The initial time t0.
 * \param end_time The final integration time tend.
 * \param dt The time step between observer calls, _not_ necessarily the
 * time step of the integration.
 * \param observer [optional] Function/Functor called at equidistant time intervals.
 * \param checker [optional] Functor to check for step count overflows, if no
 * checker is provided, no exception is thrown.
 * \return The number of steps performed.
 */

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

/* integrate_const.hpp
dx3/oq8QL+QBJvdDWVMh/3hhDridQj64psLXsyiPePhujDAIYC+hp5AM36VCqWzG/u+cBxatyL5fXDX74MdzR1w3LgO+z6XvZsP/PMgrXrgDwmYDHvdAKfGAnxPcUyBsBvjGQTnTqZ2mQvgsaKlBUMoUyrsH/O87c9HE6PXjR28zT9vxxS0Fe/ZMzv336NJwx+PX14/f8ciUGUun3/TX+v/H3vcAaDWl/x8kJBQhtAzKNzT1/v9Dad6/zdTUjGZiolVjZtSsqZmdJoowKGVFoVVsCFlJiEIIod1tCSE2q92NzWp3W0JWiP3d+3w+533fe3vvzNQ7dvf7+/0u0/Pee8895znPec5znuc5zznn258kr3/9mXcDf72ox769Xz7yt3VXJx4c3vD9qpeOObT3p1Y+1r+XXXKgPD/Q9tzpGtm0cP8TRvypePnPjjrwzgPdXdYXIN+K1ykPeN95IODmMOAWPq8+A7AwAriM6dYPbDmfpcxnTSv5lPO+aR3lRhT342KAq/l+8SfW/t48vxP64yC8/5ftWnZCZ3lemtfZ8t1Ofrf0XOTXUEF4e/bnF1ZW51XW1dVXVTbV1k8w6umQrnfvordDkQ0ly7e9f/sRFzxyXcLgvOGqxPjLEw4cYXBzpfSpGuOuSXjI7Bu1wuMmh9Wqy+SdyYV4WkXOM/tblTypN77Ad3lGP4kYz+pSPXKo9NBJUkKn3fhghFzl
*/