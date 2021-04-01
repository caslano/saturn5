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
NzEEcx2waw8+TmMeKYBmlX4VZtmDFOoraQDwO7JIbO0uDugXbY9INpbjXQ4RQIal2fkpzhz043+TUUufumn/QkkplLTbEeol+kNzYSwdW/zSm3gNotYh+pms+i49TiEJG8gtWpCSQL2/zZwxSpQ434xxr8w/BK4RP6RyqH3GQ+QfE1b730qKRIL3cOkxPWdFNr8WCBFpW+ofo3T6I4cHqvOt4ArJSJxX6RQ4V2I8g4JsBOBE0u7FWhd9W+Hjha1y8QuPZqDijSbnHoPn+skLXTnZcNb1aKeru9bpplqnzckfkasRAKxJGPFTP8/BO4sdKB+omhHpYMABFHDPQNjYLWOu36O5u2QEvNg4laaEYR1G9t0/qPyw0jcERI0QtpPk4ch5arbIxiWG/rDc44Wrt6ZC1k4NwR/GtgNWYCyQx+Scx0h+NFx0MopEqnyMOmv2NYzSRn1+6jwrYajdadBsXZN6Ii5dC9BZDoRhiM3ernobdY2/du12MFbE8UzGxu/YJiqHYAyAi9vcng3Qnh1dTZFv/gX93LE7gH6Zrh24FcNfGBjgl4TUWaUgow==
*/