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