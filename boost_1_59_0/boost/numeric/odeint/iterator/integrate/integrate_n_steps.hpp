/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_n_steps.hpp

 [begin_description]
 Integration of n steps with constant time size. Adaptive and dense-output methods are fully supported.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_n_steps.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Integrates n steps
 *
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class Time , class Observer>
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_n_steps(
                stepper , system , start_state ,
                start_time , dt , num_of_steps ,
                observer , stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_n_steps(
                 stepper , system , start_state ,
                 start_time , dt , num_of_steps ,
                 observer , stepper_category() );
}


/**
 * \brief The same function as above, but without observer calls.
 */
template< class Stepper , class System , class State , class Time >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps )
{
    return integrate_n_steps( stepper , system , start_state , start_time , dt , num_of_steps , null_observer() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps )
{
    return integrate_n_steps( stepper , system , start_state , start_time , dt , num_of_steps , null_observer() );
}



/************* DOXYGEN *************/
    /**
     * \fn Time integrate_n_steps( Stepper stepper , System system , State &start_state , Time start_time , Time dt , size_t num_of_steps , Observer observer )
     * \brief Integrates the ODE with constant step size.
     *
     * This function is similar to integrate_const. The observer is called at
     * equidistant time intervals t0 + n*dt.
     * If the Stepper is a normal stepper without step size control, dt is also
     * used for the numerical scheme. If a ControlledStepper is provided, the 
     * algorithm might reduce the step size to meet the error bounds, but it is 
     * ensured that the observer is always called at equidistant time points
     * t0 + n*dt. If a DenseOutputStepper is used, the step size also may vary
     * and the dense output is used to call the observer at equidistant time
     * points. The final integration time is always t0 + num_of_steps*dt.
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param start_time The initial time t0.
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param num_of_steps Number of steps to be performed
     * \param observer Function/Functor called at equidistant time intervals.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

/* integrate_n_steps.hpp
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
*/