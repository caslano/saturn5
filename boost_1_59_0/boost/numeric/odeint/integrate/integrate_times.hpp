/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_times.hpp

 [begin_description]
 Integration of ODEs with observation at user defined points
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/range.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_times.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * \brief Integrates while calling the observer at the time points given by sequence [times_start, time_end)
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    // unwrap references
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    // pass on checked stepper and observer
    // checked_stepper/observer use references internally, so passing by value is fine
    return detail::integrate_times(
            checked_stepper<stepper_type, checker_type>(stepper, checker) ,
            system , start_state ,
            times_start , times_end , dt ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    stepper_type &st = stepper;
    observer_type &obs = observer;
    checker_type &chk = checker;

    return detail::integrate_times(
            checked_stepper<stepper_type, checker_type>(stepper, checker) ,
            system , start_state ,
            times_start , times_end , dt ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}

/**
 * \brief The same function as above, but with the observation times given as range.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer , checker );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer , checker );
}




/*
* The same functions as above, but without a StepOverflowChecker
*/
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    // simply don't use checked_* adapters
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
* \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
*/
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
* \brief The same function as above, but with the observation times given as range.
*/
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer );
}

/**
* \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
*/
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer);
}


/********* DOXYGEN ***********/

    /**
     * \fn size_t integrate_times( Stepper stepper , System system , State &start_state , TimeIterator times_start , TimeIterator times_end , Time dt , Observer observer )
     * \brief Integrates the ODE with observer calls at given time points.
     *
     * Integrates the ODE given by system using the given stepper. This function
     * does observer calls at the subsequent time points given by the range 
     * times_start, times_end. If the stepper has not step size control, the 
     * step size might be reduced occasionally to ensure observer calls exactly
     * at the time points from the given sequence. If the stepper is a 
     * ControlledStepper, the step size is adjusted to meet the error bounds, 
     * but also might be reduced occasionally to ensure correct observer calls.
     * If a DenseOutputStepper is provided, the dense output functionality is
     * used to call the observer at the given times. The end time of the 
     * integration is always *(end_time-1).
     * If a max_step_checker is provided as StepOverflowChecker, a
     * no_progress_error is thrown if too many steps (default: 500) are
     * performed without progress, i.e. in between observer calls. If no
     * checker is provided, no such overflow check is performed.
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param times_start Iterator to the start time
     * \param times_end Iterator to the end time
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \param checker [optional] Functor to check for step count overflows, if no
     * checker is provided, no exception is thrown.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

/* integrate_times.hpp
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
*/