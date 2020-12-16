/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_adaptive.hpp

 [begin_description]
 Adaptive integration of ODEs.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_ADAPTIVE_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/integrate/null_observer.hpp>
#include <boost/numeric/odeint/iterator/integrate/detail/integrate_adaptive.hpp>

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
g+lbE/SR+JftG2KR7ZOebt8W2yZrrfRBqTfzGfqR9e3iQ+bxzX/B5vs8V7bJ9utpeE9MrJwGrR9brMvTPq4ZManoM2LSEVP7XQxZJ7PlEisK2uqVSm0zJztBO75CzgsxybSjVnqQ67N1OSZrM32FIb9jZvn9C/WUpzhaxMc8n1MRJ/it6ftyVSNeab9/L2r81ufaF7VhZvOs+ZAZSdpcX6u2njZrf8asI9C8p3vpma8iLzDNyzzjY8zc0jeipPFRTERO0f5Nl5M0n3EBHTPapuO+bJtpvwdF7vfQXNszUr73vPFe25p0zeCM19kdN+ooTaQM5Px8/jb2h77AM2814ZuiUr7pcr7sr/yWY3VcI8+bvyfKbzlvNisOajagmHT2u/kezlwx/5bvMOvQyaxD+bu6lI2rXMOZaJsR/nRSSmRavLV7ur7XL3OCpJxuOphTk+O9cp5P7q835Eo7s33j+bZtjkt3a6ptjE4e0/wiIYpD8rfmB6xeMuZQ3MnOWZKZPmxNj9RzBbk81e4YTajlOC6whS7Qr98j/5Z85Z7E+uXGOkbzuh194roxVyBc+4CSht9Zx5xtx0LZEpO+mdcvhWdEh/djEVZihDVamNa4B1tZuqTHQ2P9gWltvbyOde+p0dZ08Jw94+JS5ex023Pu63ybdYXdhb622BlZPTBz7Bz629PYN8BYvxEeFKCtAZKj7/ZrpFtb02KMhdp2x30dPsJmB7VYJ2js80v0kPuQPpI2aP8KruWcJk/tt3ndhlzLIFeBmeNBUX2tSNvu7aIyzfJEdlJcEcnylPG80qZzcU9XT6QZ58sb50OtSZrRo600Y46Dq1x7xluN201rIypnnTffbl67wX7UqVExvAHTssZo54Ll3gKPTTqs4Vg/ukZzEnujbDE1LL5fmjXGEJzRBvFUppr4OI5daPvv5n2i+eR/2S4ccuZ/oa+a7yq+ckxHYo55/ZnF14apNuxRhJOvgdsjy8g9/E3fdsnra3uOq8i+j5Ozr369fq3qK79tJK/9Ub5TtiXr7/3Z2mLECDeJ94Xl/cPkdTnUESKCpAPzR9acn2J6n+V6PF9jfrN8vvxtfLOhaVFj3cc5mcNua579208v+xpt/dmuraV8s/8uLdfjnS2RvY+cz7ber5xJ3nJPIfkc+U0O0zuJc/o5/tXvrWh+p3xWZYd57NM01pbFupvtX89+cj9fr4qvmY85KAXJQyZe7biOlMt79e/YSl1WdvQcu75Jviz3jUyxbSdqNXKL6jzLSefCtj6+ym9ndgu0pmkLnRLYV4WpW6bvELvoe2+3TTXz6SL6nioxySn9tAVNct2s5Ms1fO1qOAHa4ikt7Gqv1Btqf5BW57APwgvcr/GnWr5Gbvaar1GTqe1rcNrm2WojSdke9BT76ugykvUauyue8vK6Rj+51r5JRjrp8Awtfifb+viY6Kf66a3bYEJK1qpN03FnjmMevdKTU8TTYwU5FmFNT4jLtk4+NrOT6bcLvzubfpfWzktMN+IZ19gdc9Wu09eqabEoTRixiWsdHK/B8WBrQoLdvoJyHSHnWOBmjoFuIjM8PjmzIztqJGeajrsjD+OrEPpx/ZsqHvTV/rg+P0bEh6fHhiSlZBgcrKl+rG1GOgfNfMtXP67vzyC074QXR5duJl0GCm2vpnYR7cO0jf072nRoPoLu3nS4L09QS7tV3N7eQS2Npef6k8wHfO1v0GvOy/+P1sprPMwd2ZhbLd/Fcc2uUrTjHJPfuoCbNDDJ0vXPMpFS+HPHG+Xk/xHxLJrRlujrt5oPZPl9Q5PfN5J+3yabHBOjelhjbB00yQMczGqInqdLfPPUMTHFeLO2p6DcU8jL1L+C/yE=
*/