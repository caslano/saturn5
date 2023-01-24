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
nuf+nAZ47+b+Fzkcw9NN5jCfwzKO1688v5McHuZwL4fbeD6buf9tDl/i8EkOV6jf8Xwnc/8YNV8eLpYG4zvrP8y/nMNnOIzm8BLnIzncfwuH/+awhMO9HH7H4e8chvFx057DBA5tHGZzOJPDZRw+z+E7HHb8TwN6vTIMT7Jo8PhDkQSFGQ2g+mcWyF/WgcGPOBRiGYzmMI7DBA6TORzM4RQOH+PwCw4vqd9dweCLHFa3Z/Az7r/E4QYeXsNh3JW8HA5zOFzO4QYOP+KwjMNvOJQ5PMuhwOsXzWEchwkcJnM4mEORw3Ec5nA4ncMCDpdzWMThixxuUNuzwV9+VmST4aH+1r98XVzKkxNue+625274aGu/12s6snzir2aw9joGO1zLYIGZwek83a/PMroo4um+SGTwhjt5PXn6YTNmDb3/oSnjZoxxPeS8/8Gp9gJW/jfPnDP2Tcq96b/SZ6kvnnnzSkevH2NnP5jq2HjF8YgX+rUxTRzmGJtumyiMy5819Z4p9z90X8aMKVOnQ36CQxgrpAs2YSLlY515zyzng1MfQsvdoTOcuJsgDJ81dapaz/SHZs6akTt26qxHps5KGYDfTxfuEWbDP/ZnJfdU4UHhXoiZq7XPMGGGMAXCh1JqLTtIN1vIhbhZEDZV6AdppgvTefpZkPp+4SEIGwe+MYIL3E4IeRBS2oUCIRHS47/rAmpxN/8yOLUIYbPB
*/