/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate.hpp

 [begin_description]
 Convenience methods which choose the stepper for the current ODE.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>

#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/integrate_adaptive.hpp>

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



/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class System , class State , class Time >
size_t integrate( System system , State &start_state , Time start_time , Time end_time , Time dt )
{
    return integrate( system , start_state , start_time , end_time , dt , null_observer() );
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
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
*/