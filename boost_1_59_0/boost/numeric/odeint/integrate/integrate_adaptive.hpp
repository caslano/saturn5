/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_adaptive.hpp

 [begin_description]
 Adaptive integration of ODEs.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_adaptive(
            stepper , system , start_state ,
            start_time , end_time , dt ,
            observer , stepper_category() );

    /*
     * Suggestion for a new extendable version:
     *
     * integrator_adaptive< Stepper , System, State , Time , Observer , typename Stepper::stepper_category > integrator;
     * return integrator.run( stepper , system , start_state , start_time , end_time , dt , observer );
     */
}

/**
 * \brief Second version to solve the forwarding problem,
 * can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_adaptive(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_adaptive(
            stepper , system , start_state ,
            start_time , end_time , dt ,
            observer , stepper_category() );
}




/**
 * \brief integrate_adaptive without an observer.
 */
template< class Stepper , class System , class State , class Time >
size_t integrate_adaptive(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt )
{
    return integrate_adaptive( stepper , system , start_state , start_time , end_time , dt , null_observer() );
}

/**
 * \brief Second version to solve the forwarding problem,
 * can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time >
size_t integrate_adaptive(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time end_time , Time dt )
{
    return integrate_adaptive( stepper , system , start_state , start_time , end_time , dt , null_observer() );
}


/************* DOXYGEN ************/

    /** 
     * \fn integrate_adaptive( Stepper stepper , System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
     * \brief Integrates the ODE with adaptive step size.
     * 
     * This function integrates the ODE given by system with the given stepper.
     * The observer is called after each step. If the stepper has no error 
     * control, the step size remains constant and the observer is called at
     * equidistant time points t0+n*dt. If the stepper is a ControlledStepper,
     * the step size is adjusted and the observer is called in non-equidistant
     * intervals.
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param start_time The initial time t0.
     * \param end_time The final integration time tend.
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \return The number of steps performed.
     */

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED

/* integrate_adaptive.hpp
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
*/