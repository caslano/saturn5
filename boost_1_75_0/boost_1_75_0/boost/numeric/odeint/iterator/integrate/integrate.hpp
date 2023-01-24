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
ZHnVC2PTJ1aIeN+PP3R8Vji82VSuurPLz+qmwnYUoEi66PVjyxjV2JZqM9bA12C1thui2ZCRLe5LxCGjO5m055uPSe7lpPfeU8ekbz2F5XUf+5SaB1VsmCc/5xn3vx8nw0bZ4ecodmZf7vTqwfnELH3SJLvqAHBorcGPYlJj6HF27P0hk/NOpIzY2phim4cNFREmTIulD9O7ThV5l3hlERMlDetzidoNa1zJa6wSES8dkJvbg0ExCsA3bnjrE9dm8GkK1yajJoVm2tqNqx1w9ETUr/3jqdnIQTzTh4I7sANWt/JBv1LizU0M0PRNBw8s7J1VM7vx8nDl+b/H7t0djo8EtF1QMzJ6RjT6klt6v7kvoO655+kjHsm1b87CNuAB+NhMNrxMEVijfenzpgq0GX38lPAIyp1sOZPC6kcJV+wbjhxbWA/NLtUIR4l+6AQiz6B6tJsibpI12Ctjix7XDEOTvkvcROlo+ltwXJtH+iudXxtmHnNbe4opFz/G84WAAZ2H3nZFhP+SaJ3hbIZduKpqlNqU2qNmKaq22LF3UStG7aqtLZKoGlFqE61W7NHS0KLUiL3VHlW1Ys8gNCKJz/d9/871vs91znPd537u+33e67zV/cyA5FV0blx9fTawNABCh6qBj5L+8jSJMzpFXUT+OEV9vQCdZA1ibMS0felsBfUpTv52l/XOU7tPLnbYEXHxg70f+rsT5dHS
*/