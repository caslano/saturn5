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