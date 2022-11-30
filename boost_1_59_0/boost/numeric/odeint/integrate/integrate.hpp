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
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
*/