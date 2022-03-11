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