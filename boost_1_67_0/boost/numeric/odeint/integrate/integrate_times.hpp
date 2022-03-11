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