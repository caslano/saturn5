/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_times.hpp

 [begin_description]
 Integration of ODEs with observation at user defined points
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/range.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_times.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * \brief Integrates while calling the observer at the time points given by sequence [times_start, time_end)
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    // unwrap references
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    // pass on checked stepper and observer
    // checked_stepper/observer use references internally, so passing by value is fine
    return detail::integrate_times(
            checked_stepper<stepper_type, checker_type>(stepper, checker) ,
            system , start_state ,
            times_start , times_end , dt ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
    typedef typename odeint::unwrap_reference< Observer >::type observer_type;
    typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;
    typedef typename stepper_type::stepper_category stepper_category;

    stepper_type &st = stepper;
    observer_type &obs = observer;
    checker_type &chk = checker;

    return detail::integrate_times(
            checked_stepper<stepper_type, checker_type>(stepper, checker) ,
            system , start_state ,
            times_start , times_end , dt ,
            checked_observer<observer_type, checker_type>(observer, checker),
            stepper_category() );
}

/**
 * \brief The same function as above, but with the observation times given as range.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer , checker );
}

/**
 * \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
 */
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer , class StepOverflowChecker >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer , StepOverflowChecker checker )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer , checker );
}




/*
* The same functions as above, but without a StepOverflowChecker
*/
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    // simply don't use checked_* adapters
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
* \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
*/
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        TimeIterator times_start , TimeIterator times_end , Time dt ,
        Observer observer )
{
    typedef typename odeint::unwrap_reference< Stepper >::type::stepper_category stepper_category;
    return detail::integrate_times(
            stepper , system , start_state ,
            times_start , times_end , dt ,
            observer , stepper_category() );
}

/**
* \brief The same function as above, but with the observation times given as range.
*/
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer );
}

/**
* \brief Solves the forwarding problem, can be called with Boost.Range as start_state.
*/
template< class Stepper , class System , class State , class TimeRange , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , const State &start_state ,
        const TimeRange &times , Time dt ,
        Observer observer )
{
    return integrate_times(
            stepper , system , start_state ,
            boost::begin( times ) , boost::end( times ) , dt , observer);
}


/********* DOXYGEN ***********/

    /**
     * \fn size_t integrate_times( Stepper stepper , System system , State &start_state , TimeIterator times_start , TimeIterator times_end , Time dt , Observer observer )
     * \brief Integrates the ODE with observer calls at given time points.
     *
     * Integrates the ODE given by system using the given stepper. This function
     * does observer calls at the subsequent time points given by the range 
     * times_start, times_end. If the stepper has not step size control, the 
     * step size might be reduced occasionally to ensure observer calls exactly
     * at the time points from the given sequence. If the stepper is a 
     * ControlledStepper, the step size is adjusted to meet the error bounds, 
     * but also might be reduced occasionally to ensure correct observer calls.
     * If a DenseOutputStepper is provided, the dense output functionality is
     * used to call the observer at the given times. The end time of the 
     * integration is always *(end_time-1).
     * If a max_step_checker is provided as StepOverflowChecker, a
     * no_progress_error is thrown if too many steps (default: 500) are
     * performed without progress, i.e. in between observer calls. If no
     * checker is provided, no such overflow check is performed.
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param times_start Iterator to the start time
     * \param times_end Iterator to the end time
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \param checker [optional] Functor to check for step count overflows, if no
     * checker is provided, no exception is thrown.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

/* integrate_times.hpp
mk93l9or7+lGk9u7upIb23uGUnptcFqO/uJqDS8XeEKvU1VgDW8weo7Mwa6FxGeGsHTg+n5X9P0G1fezlfzdWlYu1I0Hrs9l2r53q4BKAZiGFow+zsbAN+zDjLLtQ3P9882QsYPHs/+HWFbjbja4W9S8N2Rs/keRpg9NXZOzYn8pGe5Dnwh8zuPE98dGPElsnps3rJ3+pMm3NnGr1Bn58TqfLPMG+du79PBlzHy+H9PAzc3vod2ZsEdI5chEXV31gckVhy9c2tQQAAaMLKylaWV9W2Ooi4CjZoTDwTmksRl6M8nZnZDvaeCR6tzkVvLx5pBTmSNqNQQd/nK+b9DwMfKBRKI2iYXW6BE7Kp0vI/9dQdRgGAWCpOxIddiSqJvnq4PNsOdTbB36caRDV4Bp6vxZ1Nt17APs2i5vam5LNixvXtnY0tq0vBk/l61oaWxtbVwURLIvHI5zeLPCCnF2Ho6z5KiFLU0hjcWqr84B/6hKOM+zEfsFiFGYXN0/2JvttjyZqP5Lf0CduS+RfZtilNiWpBFwT2C/0L6uwQWHgeiuGupSEmDZPym+952loU0NtwhCoJzvKwP9TndUIIKdi7LTgrCaroKBnNPDin5qEMipdNyOcl+Aa/0z1Vq/vI/uri64tf3i8G6bsqtV3L+SnpVbF+5uFeseRpXjb8gkHWS/H84TWpBLY8Oi1vpka9MhWXICGPkcQuew/TPP3tkFal69kPrmzn6ot5poy1w9vzQ9+nt0etyWfYm29hLSGMzZjRUNbXgLEr3t9LMgSnO4RrAJAsPwiWATBVaXqA6o21nYlhzeTg6W6kT/Od3dmbp7GeqRO0OVQtiOOdl6HBzpbp7MUHfd3h3bMZId8tsAmyG+0FdGp4m2+mhKhqW5jTTD32eq35/n747sfTqkxX7ybRaBocqMo0AY5R7ddXEwyp14VzoY5M47cTth4vv63LGcZVsQfI77oRcBX9uGs115XFJLDbZn+mVs4P26wa6UpIsxlle3dwIldnZ3aBCPh4KROZvotimdMcjagjLCaAt4TjT+JmS5S/M+GPnCLnSneiLf7WLQmRmEV4wlf0HQnqvjIkg+W4clQXuyO413TfuG0jXKhiyN6DnTUq3gKxQ8Qfil4NdGeC+GsAsjy3b2zAj3I3tx5tIVcXy/DHzsR1JjokB2LkYK4Mfl4NEba6juhKuVzekKbYczvWI6mFZv6tmY1QXBN2gDrlW+2kSTdz3zQtvzuIqJdoP20Uj7RuOj3UQaN3tw375PHPdbxL11OC7sVxz3NuJ+R9XtLGUXv+uhcYep252kcRdxaTNdnPahQodv2lMY3M0y32cZxseS+Ityn4Z218q8KPgBadxj+ALP2eiH+Kf53ssy97GMd/4Yw7wT0vgRaXA9ivUeXt8H5jLeJHn/hOXoV0ub5V+WFb/6QZb9meqnH6l+eljLQNF5ZC5pKRk8Slo/Z5lKfUaDZzLkvLT4A9cBv0idZ/gm0sXmPMMtc6O7BAO0Dd9GuhT2JJMUf+Z2Z4cAc0ccwiUDnm8HfFoEH+ro6Y7GOPmWS/xIB9sOWIV7A3sok1J+0Q+dbcIdBNqu+5Ge7dJJEEYFWP6ngFcR3k1f6SHAakNfrHv15izeLwA7gDCHCXg2Nvdjym7MH8e5nUMD7xxAX+hIZfuPUnZ/VSD2flVoU51fkY2l+StVl9JR/Wu+Vblf3IY9Tr14Qtswk/ektgekYe3Pb4n7tB4fxOXYoB9lYmWy3O9NOdCHDOTPlvsjyz3Lcmwf6yXte454fzZtAJ6hibeHiPuCoXm2+T5+kXgvaZmZvJc1P9KwNvTvxH11WN2Ab3BfI+7rxo4Q1y9j2pF/suybw8s=
*/