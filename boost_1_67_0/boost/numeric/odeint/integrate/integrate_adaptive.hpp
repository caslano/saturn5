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