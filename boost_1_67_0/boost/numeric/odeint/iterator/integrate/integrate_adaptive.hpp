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