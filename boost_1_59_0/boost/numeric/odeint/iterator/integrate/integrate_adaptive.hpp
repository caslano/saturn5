/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_adaptive.hpp

 [begin_description]
 Adaptive integration of ODEs.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>

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