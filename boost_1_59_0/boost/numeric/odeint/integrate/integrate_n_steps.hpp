/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_n_steps.hpp

 [begin_description]
 Integration of n steps with constant time size. Adaptive and dense-output methods are fully supported.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Integrates n steps
 *
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class Time , class Observer , class StepOverflowChecker >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , StepOverflowChecker checker )
{
    // unwrap references
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    return detail::integrate_n_steps(
                checked_stepper<stepper_type, checker_type>(stepper, checker),
                system , start_state ,
                start_time , dt , num_of_steps ,
                checked_observer<observer_type, checker_type>(observer, checker),
                stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time , class Observer , class StepOverflowChecker >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , StepOverflowChecker checker )
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    return detail::integrate_n_steps(
            checked_stepper<stepper_type, checker_type>(stepper, checker),
            system , start_state ,
            start_time , dt , num_of_steps ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}


/**
* \brief The same function as above, but without checker.
*/
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps , Observer observer )
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;

    return detail::integrate_n_steps(
            stepper , system , start_state ,
            start_time , dt , num_of_steps ,
            observer , stepper_category() );
}

/**
* \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
*/
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps , Observer observer )
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;

    return detail::integrate_n_steps(
            stepper , system , start_state ,
            start_time , dt , num_of_steps ,
            observer , stepper_category() );
}

/**
 * \brief The same function as above, but without observer calls.
 */
template< class Stepper , class System , class State , class Time >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps )
{
    return integrate_n_steps(stepper, system, start_state, start_time,
                             dt, num_of_steps, null_observer());
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps )
{
    return integrate_n_steps(stepper, system, start_state, start_time,
                             dt, num_of_steps, null_observer());
}



/************* DOXYGEN *************/
    /**
     * \fn Time integrate_n_steps( Stepper stepper , System system , State &start_state , Time start_time , Time dt , size_t num_of_steps , Observer observer )
     * \brief Integrates the ODE with constant step size.
     *
     * This function is similar to integrate_const. The observer is called at
     * equidistant time intervals t0 + n*dt.
     * If the Stepper is a normal stepper without step size control, dt is also
     * used for the numerical scheme. If a ControlledStepper is provided, the 
     * algorithm might reduce the step size to meet the error bounds, but it is 
     * ensured that the observer is always called at equidistant time points
     * t0 + n*dt. If a DenseOutputStepper is used, the step size also may vary
     * and the dense output is used to call the observer at equidistant time
     * points. The final integration time is always t0 + num_of_steps*dt.
     * If a max_step_checker is provided as StepOverflowChecker, a
     * no_progress_errror is thrown if too many steps (default: 500) are
     * performed without progress, i.e. in between observer calls. If no
     * checker is provided, no such overflow check is performed.

     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param start_time The initial time t0.
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param num_of_steps Number of steps to be performed
     * \param observer Function/Functor called at equidistant time intervals.
     * \param checker [optional] Functor to check for step count overflows, if no
     * checker is provided, no exception is thrown.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

/* integrate_n_steps.hpp
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
*/