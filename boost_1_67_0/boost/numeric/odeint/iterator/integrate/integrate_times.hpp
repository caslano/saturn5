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