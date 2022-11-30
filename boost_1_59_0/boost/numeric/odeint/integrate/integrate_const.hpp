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
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
*/