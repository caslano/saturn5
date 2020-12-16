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
HDBujyoKZCqiwSr8rwBrbgLx29/5BtZ8IeL6WcTXb+DnO9F7JbDgkCqqgE0xEfjVJnD5C0V0wHdmrVTFZ7TtK2y+RV32ipwpxL4jzGf+ShFH+qhi4qfgAHhZbiwYvBx7w57ixzAO8ASdXrWIrshnL+N10TeYU39IEctLCXHvPH6Wj3ZNY67INiHuM3Y16rEqHpZBnhUtYvKritjDvUkXVNGEtg94BRtrzPckwOF0lfcGW0TMfYtYxIaUd+Yg/5nM88BmJ65B/7eIT2BzdQtrlAozOwZZ3Z6ritb0YRb9LOJtEeN4ZgqYOsFqEYPQdxQ6eS1cFf3uEQu6KqL+B3zndjnXDcE2uqhibwHmTBNjXioIds+1iLeHq4INckWqBXkRF0+OZKZmXfTBwH8GPlOkE/FmqiLGFcRnF7M2Hz3OwG+veljEpsGq+IEY1AXbCwN3o7mmOj68+zw68OOdZ8FG4tOaFqqI/wd4GqCIuW60G/885KOITq2x6VjkEUVs+dIi4luzNhvZBD5iX4CGihjyGvfx/oB5ivB8k+/oM+I3GRxYtUsVw2qqonGYRfxyAwxqha1i1ydfUUQJT/bfZc55PT/8Daz7W1P+BltWYVvBZ6nL8cxleYgluxhNqwiegkWriyMX/OxCRWIwGNMIDPb2oI9vMWcTO/ToCe7xjP3d2P2zNrVK4nWhONp2h/aioylzkGVhnlORNuGje4jDi8HsR9sU8W0gGNbIIj4Dl17rbRHVflVFj4GqyBegirIfquJmvCouY++vHUEuC1XxelW4A9g1ErzvOJ71a1+CRT8o4mPadRA73c07xnVXhMsf7OCO3Bb3UUSTlRYxNRJ9rCN2IkPXgdjMcfpdVhHDaceHwcShBxbxHeXHSeihwDm+R4HdTqoLPvsqYt1e9o4Gt1qsEPAWcPd1/O+KKra1RCZrmRv6Hev+ymLTPfjuCnH4HPGqcBeL2HufOKvFjUZC/IN4cKOkRex+wt/X2FtlKe9C3hd6sVauDHL7UhV1lqmiDPGo/mZix1owKFYVn4bgk4N4x1ZsZwQ+EUD/sW+PjhY4E/No6ctN/Dt1DfhFfE4lJqyAN/T9VBH5zjNn1Ql9rMEuPlHFKGR8FntoE6yKdcThIWHYxRJFnO+qih2z4QzfcG8gNvuNRTyorIiIj+CA9G3Sj9jGRvAIfjgVH9v4E/q4gI29Rpw/CCcop4qvvyO24lOPufYb7M/lAs+nbaNdVFETXImoqOCbYHgdvkxWDe62Dls6hB27YCsn0f8JVWxsx2hAZWrH9OtXsDK0tSo+76uKoYnssYzfjBmJjd2FbyGPWz8T33qq4nY1+kAM1tZk+DRmj+APVDHhDtjqrYpuV+jTY2SGz7QbQYz6A5vxFuJ1cKvWE2S+wyIWOMNH0MOytxRxtBl2js2547ctsCvXEPwATrsBnvZgD1iEDNaOVkR7+nI5UYgH4Npn2N57QxVxKgbsps/5loKF4KlnGnYATmbAPQ8Se0/sJqZupm9sLB4O1nhX5RowcdY9MHCGKjZN4mtKvzJnB10Va0IMwMZag83sXYEdEFMT4NbYhYYbE5Dv72DmnCBVjL2HnYNr3uipRyeVtX3U1+HSYe60dQxfZSfGuGxWRcXS6N+be7Hjrj9aRF13vii4hziWAq7Ag5dr+1iDU08+hxuDYUOr2b4DdAN/6OlBrC6hCtfq8C18bNka2vIbsa84fUxFLwMYu+I5fqPRwdvI+3X2gKtiEXveAvdaYLvYQMEpxG3O9WxpES91JW6ECR3vRyfiAw34VsnPiqiFvfV6Fd+bQvwao4iav6KXT+DjadiZFxwPnF0VRLx/nzUn8Jtdk3j3J7wTvX2P/no=
*/