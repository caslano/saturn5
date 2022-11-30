/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_const.hpp

 [begin_description]
 Constant integration of ODEs, meaning that the state of the ODE is observed on constant time intervals.
 The routines makes full use of adaptive and dense-output methods.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>

namespace boost {
namespace numeric {
namespace odeint {





/*
 * Integrates with constant time step dt.
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer
)
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end
    if( boost::is_same< null_observer , Observer >::value )
    {
        return detail::integrate_adaptive(
                stepper , system , start_state ,
                start_time , end_time  , dt ,
                observer , stepper_category() );
    }
    else
    {
        return detail::integrate_const( stepper , system , start_state , 
                                        start_time , end_time , dt ,
                                        observer , stepper_category() );
      }
}

/**
 * \brief Second version to solve the forwarding problem, 
 * can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time , class Observer >
size_t integrate_const(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time end_time , Time dt ,
        Observer observer
)
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end
    if( boost::is_same< null_observer , Observer >::value )
    {
        return detail::integrate_adaptive(
                stepper , system , start_state ,
                start_time , end_time  , dt ,
                observer , stepper_category() );
    }
    else
    {
        return detail::integrate_const( stepper , system , start_state , 
                                        start_time , end_time , dt ,
                                        observer , stepper_category() );
    }
}





/**
 * \brief integrate_const without observer calls
 */
template< class Stepper , class System , class State , class Time >
size_t integrate_const(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time end_time , Time dt
)
{
    return integrate_const( stepper , system , start_state , start_time , end_time , dt , null_observer() );
}

/**
 * \brief Second version to solve the forwarding problem,
 * can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time >
size_t integrate_const(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time end_time , Time dt
)
{
    return integrate_const( stepper , system , start_state , start_time , end_time , dt , null_observer() );
}






/********* DOXYGEN *********/
    /**
     * \fn integrate_const( Stepper stepper , System system , State &start_state , Time start_time , Time end_time , Time dt , Observer observer )
     * \brief Integrates the ODE with constant step size.
     *
     * Integrates the ODE defined by system using the given stepper.
     * This method ensures that the observer is called at constant intervals dt.
     * If the Stepper is a normal stepper without step size control, dt is also
     * used for the numerical scheme. If a ControlledStepper is provided, the 
     * algorithm might reduce the step size to meet the error bounds, but it is 
     * ensured that the observer is always called at equidistant time points
     * t0 + n*dt. If a DenseOutputStepper is used, the step size also may vary
     * and the dense output is used to call the observer at equidistant time
     * points.
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



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

/* integrate_const.hpp
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
*/