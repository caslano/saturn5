/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate.hpp

 [begin_description]
 Convenience methods which choose the stepper for the current ODE.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>

// for has_value_type trait
#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>


namespace boost {
namespace numeric {
namespace odeint {


/*
 * ToDo :
 *
 * determine type of dxdt for units
 *
 */
template< class System , class State , class Time , class Observer >
typename boost::enable_if< typename has_value_type<State>::type , size_t >::type
integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
{
    typedef controlled_runge_kutta< runge_kutta_dopri5< State , typename State::value_type , State , Time > > stepper_type;
    return integrate_adaptive( stepper_type() , system , start_state , start_time , end_time , dt , observer );
}

template< class Value , class System , class State , class Time , class Observer >
size_t 
integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
{
    typedef controlled_runge_kutta< runge_kutta_dopri5< State , Value , State , Time > > stepper_type;
    return integrate_adaptive( stepper_type() , system , start_state , start_time , end_time , dt , observer );
}




/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class System , class State , class Time >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
{
    return integrate( system , start_state , start_time , end_time , dt , null_observer() );
}

template< class Value , class System , class State , class Time >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
{
    return integrate< Value >( system , start_state , start_time , end_time , dt , null_observer() );
}



/**
 * \fn integrate( System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
 * \brief Integrates the ODE.
 *
 * Integrates the ODE given by system from start_time to end_time starting 
 * with start_state as initial condition and dt as initial time step.
 * This function uses a dense output dopri5 stepper and performs an adaptive
 * integration with step size control, thus dt changes during the integration.
 * This method uses standard error bounds of 1E-6.
 * After each step, the observer is called.
 * 
 * \attention A second version of this function template exists which explicitly
 * expects the value type as template parameter, i.e. integrate< double >( sys , x , t0 , t1 , dt , obs );
 *
 * \param system The system function to solve, hence the r.h.s. of the 
 * ordinary differential equation.
 * \param start_state The initial state.
 * \param start_time Start time of the integration.
 * \param end_time End time of the integration.
 * \param dt Initial step size, will be adjusted during the integration.
 * \param observer Observer that will be called after each time step.
 * \return The number of steps performed.
 */


/**
 * \fn integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
 * \brief Integrates the ODE without observer calls.
 *
 * Integrates the ODE given by system from start_time to end_time starting 
 * with start_state as initial condition and dt as initial time step.
 * This function uses a dense output dopri5 stepper and performs an adaptive
 * integration with step size control, thus dt changes during the integration.
 * This method uses standard error bounds of 1E-6.
 * No observer is called.
 * 
 * \attention A second version of this function template exists which explicitly
 * expects the value type as template parameter, i.e. integrate< double >( sys , x , t0 , t1 , dt );
 *
 * \param system The system function to solve, hence the r.h.s. of the 
 * ordinary differential equation.
 * \param start_state The initial state.
 * \param start_time Start time of the integration.
 * \param end_time End time of the integration.
 * \param dt Initial step size, will be adjusted during the integration.
 * \return The number of steps performed.
 */

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

/* integrate.hpp
SQaxWEPw6ZYEj4fD1+crYvpJ8oGvk3N/DVl0aC+LpKUxW6So0xkqHZNL6pD7+x8OIMaUk/mhMv8B7ATv4roDDYRsKkVauimTmKjo6QvpGj0uYJJqJlGhuMCQoFvMOsoxyQXRiLOGdlMj6XtrGCOLkSFIMkrlBn9HKBloz4Z9mTlAleKTJ8r4VYIAO7vPBPy+I97neyJ6jvK13ecUX/bexJdiVVkhyl9UcGXxXeGlIbYIsD8tZFYj5v/xcb/40Db99gjRdEyM6IeVKHl0e5hYUUyg5ETuFyq7u5VQsUQfLlQoVqYZpw4PazCwWKY3pWCxxZTCQmB3JbFAMkmgjTWvQiyu2D7pGDG+rJeIvd5nCcH1FgsWB43BZb/vQNEbNHPJqIUKsvn8xlbuWRb71GQux3NrxlPW0Ld5lJL/+Qn2JfSnFKJrRC691S1BS6pLEb5qudU0cauzhq+6g5outwirCDNP3LjYeMiGUjp5Cq1b/1jx2WUkmGGfzMiqFf8A0lLuqkZs5GnNQa8VQkEPX2HT3KAFR0k8vJi4/+qNXgzHPYcoP90K42wyudCGcSzfbdDw4th2RClz9zmpYQtMnShOz/soZV1rwQaABVEZz6roDnIK1rEyqLTYrETVRW90Ohy9ycmRy5SNiUeCWZLO
*/