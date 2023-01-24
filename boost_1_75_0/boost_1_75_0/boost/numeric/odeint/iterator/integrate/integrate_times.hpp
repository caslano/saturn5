/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_times.hpp

 [begin_description]
 Integration of ODEs with observation at user defined points
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/range.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_times.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * the two overloads are needed in order to solve the forwarding problem
 */
template< class Stepper , class System , class State , class TimeIterator , class Time , class Observer >
size_t integrate_times(
        Stepper stepper , System system , State &start_state ,
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
 * \brief The same function as above, but without observer calls.
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
            boost::begin( times ) , boost::end( times ) , dt , observer );
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
     *
     * \param stepper The stepper to be used for numerical integration.
     * \param system Function/Functor defining the rhs of the ODE.
     * \param start_state The initial condition x0.
     * \param times_start Iterator to the start time
     * \param times_end Iterator to the end time
     * \param dt The time step between observer calls, _not_ necessarily the 
     * time step of the integration.
     * \param observer Function/Functor called at equidistant time intervals.
     * \return The number of steps performed.
     */



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_TIMES_HPP_INCLUDED

/* integrate_times.hpp
z66TkehTeOD0ASkhh/s5oddnOFErW6yezXFa+e0ojPX8Z68NgnOm/F6xuvzVo9oVJ+0Wvwr09MN37j8f8sh3u0uG9daaGG7Iyw1VezTVc6zPeGY5+En8yPlvYDUUvGNn6pTJBJbJNGXWL49wOD+VRKkXE/DJx7v+67PfCRF3EbOZo1fxTPmgCdoBMa6+QfBXOyJtl+CzLl2Kfkr2AJiljU7MmItNTByKfRzBxWeUpt+m/Zh25cWKnTNld+QHbJAGVbMltKoiHstKPTmXLBsAYUFiVjJ2PsV/F88KdpJKfyOlLXKbM6JhFqcAengQW9WC4Yj4oKSdHdB/VHI0HHVXlnR6F6qJfj+Eu3X324IjIojiJGkwGT6Ek7MNzF36cJQgU8wih0rrFvpw/j69jAdtO4cb/ah5MvTMXqON/u72V/2VTfn8iHf/nqNBJw5yv2SEltxyRiTsms6Hhf10HPWeGxzt9NDdkSeFQjwjQpwMrI9DqSFk54PdowRxIbvzG9JyqNhl95ydR5Ced6CNjyBOVHS6gHhOyZPdKLT0gGOUbNdmNr733T8ytK35zp3MTZkBefGgPGVUgTlz/QPUKFzRlJlXDpC6tegJztRTKigxsxnKvaP3O8OT1psTVVPn3ykqLFCffEsqnYWo+i2/V6RBbWsz54NOSZvUk8dow/VNr8j36aXPO6TFPOIpUEIO/EL+PMw7eMuF9fS5qQKX
*/