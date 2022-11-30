/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_times.hpp

 [begin_description]
 Integration of ODEs with observation at user defined points
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/range.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_times.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
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
 * \brief The same function as above, but without observer calls.
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
            boost::begin( times ) , boost::end( times ) , dt , observer );
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
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param times_start Iterator to the start time
     * \param times_end Iterator to the end time
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

/* integrate_times.hpp
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
*/