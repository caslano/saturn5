/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_n_steps.hpp

 [begin_description]
 Integration of n steps with constant time size. Adaptive and dense-output methods are fully supported.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_n_steps.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Integrates n steps
 *
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class Time , class Observer , class StepOverflowChecker >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , StepOverflowChecker checker )
{
    // unwrap references
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    return detail::integrate_n_steps(
                checked_stepper<stepper_type, checker_type>(stepper, checker),
                system , start_state ,
                start_time , dt , num_of_steps ,
                checked_observer<observer_type, checker_type>(observer, checker),
                stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time , class Observer , class StepOverflowChecker >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps ,
        Observer observer , StepOverflowChecker checker )
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    return detail::integrate_n_steps(
            checked_stepper<stepper_type, checker_type>(stepper, checker),
            system , start_state ,
            start_time , dt , num_of_steps ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}


/**
* \brief The same function as above, but without checker.
*/
template< class Stepper , class System , class State , class Time , class Observer >
Time integrate_n_steps(
        Stepper stepper , System system , State &start_state ,
        Time start_time , Time dt , size_t num_of_steps , Observer observer )
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;

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
        Time start_time , Time dt , size_t num_of_steps , Observer observer )
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;

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
    return integrate_n_steps(stepper, system, start_state, start_time,
                             dt, num_of_steps, null_observer());
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class Time >
Time integrate_n_steps(
        Stepper stepper , System system , const State &start_state ,
        Time start_time , Time dt , size_t num_of_steps )
{
    return integrate_n_steps(stepper, system, start_state, start_time,
                             dt, num_of_steps, null_observer());
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
     * If a max_step_checker is provided as StepOverflowChecker, a
     * no_progress_errror is thrown if too many steps (default: 500) are
     * performed without progress, i.e. in between observer calls. If no
     * checker is provided, no such overflow check is performed.

     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param start_time The initial time t0.
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param num_of_steps Number of steps to be performed
     * \param observer Function/Functor called at equidistant time intervals.
     * \param checker [optional] Functor to check for step count overflows, if no
     * checker is provided, no exception is thrown.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_N_STEPS_HPP_INCLUDED

/* integrate_n_steps.hpp
CDYBsOKgKwY7EzxKsrLmnHYOYKWQm4b9tsJ9F2ErNoKGsNOBN43fT2nifQywct5pysLOc9+tA1mB5+bciwCfGcHb033VzIzy9sV8MFuvCRBWFYTnFIJcupbfeFmaawA7QK031CM9P3AHE+D0bgQvgS8gfKhDzlOcAfiiCI4okBg73Sl4yp2pQfK8GHVeEnSGl69Sq/vSue+UpbyfJfdgow8EhCJerb9v2lwsSAd2uOugB0fi7Ke6y+V04yO4L5raGOTSxzEmZzhW3hneC6xUI4X3xXLKzRS0elT7OdAt5lOBGA9Lxwnt7HBvRHP/9DLFv/At2iE9h1Rw/r9c6fyJyi5dYezStkr8Gbv0VY6brykan1K/txqbexXLf51z4NUsf43BC/N1Xa8l3nUyt4iM38LckpXzN109ogKLKecbtJzFP1eEnJR9GTkZwxZwTmE77DsetEfAi8nzFuJj7Et5hQ94DP/bJt/G9PiOmuN0vDHYBy99wGP072T6nDz45xj8u5mG3fPiAx7D/wHxj5gWr+/H8vADPH6vjukz8+CfafAfYDoxOc7v9DzlTzflH7T+kb3LRnWIVMTA6B89RB3W97seroz42XvDjwB+MHU16sPozNnyvcLc9mhe4FxUFNq/2PpP/Kzezyv1+TdqrXvNHl+Wrr4GhvqGdQEvykp9c+wuPrrg4N0aygvzTMynAn5srebxSn/5J4z8QSe+R5JP/mNsT1iX3yr/8CHle/zO2KBnNG9g/V7q5vIA59ji/glgi2Nrd3LXEP2L/mKcBPZlUTQvBdJfQwOZfnd7ONdnf9J9NsY5xHvX8i3YsayN/LOrQ0g+HWTjUz6vbeQ4vg0erYyf530Bac5z8ZiU4J+NUf1XxavIyCDpboALQ5ORs8dDgXyP6nnlX4xFeKnSg5fNvPdKJf6MHv5dvs2YJ9+F/6DObzL69LqZ095Q4wm4Thb2/YE35RvTlYdf4HQn/C7KeN7v/zd5X6rbwLJWXwvmxvOnm7dKJs6VugcOV+q+E9KLx+DnjKV/wvpOAj0r8yLAdH12QZptZf0Z51S3lXW1bdmNuDsbPsVIv8PwKSHu2x0u+4i4U4bRxno48d/mwd9jLtuh8PdUci02ci1DWuomcse/rm5Tyes15WO9ato/DTh7s1wxy73b0IV8Y3TLVf7DHl2ZbvIBj+VXSN8wzTYSX7dxP+ICHhuT9aVxn+kMpu2cDLwYr9mgp/PPMPmVyKe94Vtw/PbgnZYSOavr7E0V8OWtg7bG1rbYpRYNyOnvFaXxmGEJ0JgFXt/DCBkwsZdq5sqa1wz8bSuN5sKzSyzuTkEd+3ue1i1FPzD76QcouW8x89dByGOf8T6lpPk9oOWI9RHztgfKrxyL75NsWNpY33w4rtW0NS7j2M+PkJPhArYx5IlvvpgurDG6se9w3XD1tTFdG5Ve6vKQt1e3LjZ2vsno1hqjW4eZ/H1N/jLki8/kj8u23Iyd75g62XMQLdpm8C0EflMxLTzrgQv4sHMXK0kD+fF1Wpa53vT9UdJO0ozX6Wgjh6Egnn8M8vUeRRXOtOt0OdNnTJF7oDKnylp1B3VkYb65p2szFmS6OxHTdlkSiwXUPgvWsZ3QH9ThDBDCf7ie0zXXxcZP9TpCf8udg08p+1CieHr45XgtJK9n3Nn1XvfiEzIDwNwbg4XY584B6Qs9C3gRY2/3hTR4pnKN4l88zjbP8q/7pfuzCxn4qfc5uilvr889xraH/tX6ueJf9ZCm/ZboBVzraB9tXz/x36AM17n2Z7mgwrTlna6/NiY716Y61xM2AFgRzqv0ddH5yMIL3ft8RzXXL2tqSC5tWogfjYHeJ8f7VxsjSln80uw=
*/