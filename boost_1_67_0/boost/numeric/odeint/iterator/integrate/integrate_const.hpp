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