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
nZtzvJMybnrLfgTnChefjzeanJqa5NRMPj/JHC/s61QS65FTYvckufWNPN7EJqPg5NRMlq5q1Q7jG/fNffV6i4MWMu9W1rB8THIsmgs9O7SPXPiq1lc/X2Pdf3GZY2syr5TFgwyO4e+bvU4S5Gva00DuT+AwVr2ArWttamnjgX/999d/f/33139//ffXf3/999d/f/33139//feM/1zPKGJRTb5nOV8Vrx3le2d/MF7+DWOKcRbxxikhNn6viLw/s27hMrWt6gr76KhiVR5VlEhVxW/8/esoRbwazdhZSUV8eIK5cl8LcXqDRVx6pIqXamkLLRSxxVkR9axUz06zA2iaRby8hnURfqpoXkgRk+YqotBhvmf8oSJGPmBP7TuKKDjfIj6uoAifICFafct8gDdYR7dKFR99rIrpf6ii1G1VbP/cIi7EM19hLN9hSGejsfEW0fQ6dajdFnErQYgfi6miT3+yiLcZk04S4ocoVbzhRk0l2SJqNrUI72LMIXyfd72tiuVfqGJWNVUcoJ27dqhiyQH20bzH/OUpqrhzj7a6kff+pooPQ1Qx+yHjJZxb3dYi5t9kLXdli3itLyvilyni4mMyvkdCfBnIfkP7hHhymLFy5OQ71SIa11XFmN2qCKxPpWOeRVT9XRHXPRVRZrwivjzB9xsXqSL8KH/fFeJv5ZBzYYvon6CIR+Msog/rxb86yfzSgRaR+b4q7i6l5jSa7wXMUsSKw7y/tCJurVPF1RaKWKuyv/YsVSytynrkDciqrSqanWOO5TZVbPjaIho2Jieew/fS7/D9Zp498Rx19uWKeC9JFYXRZ8ohIRZr3+e9KMSx6czVdrWIh8uZp9iQ71+MV8WW6arIXGYRZy2qeIxcN/OMpWdU8e4a3o8sv1xiEZ/kZd/GghbxQT9VtMqviOb/UEQgc4yGrUa/HYWYiJ4Gano+hD3UUsT+B4qI76iIDR7YWSWL2NhJEW48/48ZzHmpz57TKxTR8CK76Q5gfk5nIU5NVcUZRld/rqGKrX3Jmy/zje5e2Ce2WDi/Kr5daBGBZZjPuw+73smcp59VkcDvAxf4FrG/EIcPCFGqAKMxP1JHU5HJK6r4mOd3ok3fZCiiwgRVfEGbz2yziJF84DhtryJ2pCti535VfGDFvgepoulwdnwoh+2eRUfH+V76MOSAH13MUMW94sxZLqEICzbiedAi/vGOIhZiB2u+sojWC9DLI0Wkh/GtQezgJ2yq5CXm568U4vvOikj4G2uJ4tFNGyEmJyJDP2yxnBA70OnwqvSrDt+WD7WInXvZuWkmX15YwvcEX0Gfo1URE2URb+Izg8/yhYW/q6Ir36g96oTtVbMIf/6+8gXzZz9jDGY93zcJUcRvr+G7Jfjm7WAhPrrGPG18IATZ7qmiiha1LOJzsvZ27yqiNfbZgIS9cbQiUvDLaWyaZR1KjTORb2qcQU8BjMlvYa1gYeqB3fjWbhns7jNVVDquil+wt9+R14XFquiexpgMvhJAv69h2x/xvOhI9vTYZRFftqceOYP6TE/GZSbQr9rsD4St70NXnWcxnxsfXTiCeRD4eUR1ZP82ex3GKsKf56e04ws4HVjTsJRvqLqqolg3ReRfjy4iWfPawiKaZVjEsXZ83zNSFd74UP8i+F17i/ge7DvYC92HgFGF8b0dfOejMbalfQMEWxxdktG59rQbPOt9ShEDFiO3C/inuyL2tQIHD3DNP8CZh2BXV4vojI+PW0QbfgK3rirIkrVcyGVlJbBspiLq1sZe8eOqt3gucg/+BVwpzfeF+qPjI4o4y/jI2h9YD0+fNvHsvvx9Dttv+bUiFPD0GnY9Eny6sloV08COOc0s4tQ=
*/