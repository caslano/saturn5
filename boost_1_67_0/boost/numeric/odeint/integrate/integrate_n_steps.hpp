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