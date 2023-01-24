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
Mb2TRHZPLyWFFTg4yORRnADPyvIjrJ3DVrqYuwaBqaJGtKNRzo5MSSypPJyJrGx0Rk9VFSazPRbg9+LvfgvyfprLz4NOP4ZBeHiVhoORQ4nZtEZsdBmH4NTy3h8bUA5b6OJh14Xi4b91sMzhPzRY7FAF0xbzj/sVIP7fxQnkY3WLp8OrE//1+9+zf8zbLOo5vHLwX6dDctz1q6pcAP810NZO/63xLb8nNr7VAtDxQPbZrpNx2LijVdF5pbeWlQlaN/sxXtPVw/20NL5QoOXJLadvkm79LbGae0XBrt3f0j3WEwv1QTZQi0zTAGdHZMbq7KchAwTrlAPVCZVTLEVsz9X8B2vsdCxd7EgsYzFiKtFrDPep4st00B3GoxdbW5Lotm++GZUSOsnl9bIxd1BffO9+sdzue1sdmGgKaKg9ZjJYEp1vXgv4EFqJNUkud8WXzf/0NQCIeYTp3ns3uwEfp/+i2LliUTVovrmbZcdSJmmUpV0k/OylCOyFAPmhzs1F6ruL1Kuf+tsF018D0+9fCmyAstKhFnok3QZCUu7/Ao5z+u/jHne2Ld0kfsSu5zzNcsiweJ5YvcCU4+CmL6P/MJkgzLwrLpIih3AYum+Qndf7XYjcLHNnYwGuxJTFnkM7K9hJdTdfELYJo1UFPl1W6ozfpFpVEiheYORYT6lbB2Sc287n25bllw9VD4v+sCTILF8Mfni4ZDuPqRRS
*/