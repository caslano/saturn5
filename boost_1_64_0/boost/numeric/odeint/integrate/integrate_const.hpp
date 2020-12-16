/*
 [auto_generated]
 boost/numeric/odeint/integrate/integrate_const.hpp

 [begin_description]
 Constant integration of ODEs, meaning that the state of the ODE is observed on constant time intervals.
 The routines makes full use of adaptive and dense-output methods.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/integrate/null_observer.hpp>
#include <boost/numeric/odeint/integrate/check_adapter.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/detail/integrate_adaptive.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Integrates with constant time step dt.
 */
template<class Stepper, class System, class State, class Time, class Observer, class StepOverflowChecker>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt,
        Observer observer, StepOverflowChecker checker
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end
    // no overflow checks needed
    if (boost::is_same<null_observer, Observer>::value) {
        return detail::integrate_adaptive(
                stepper, system, start_state,
                start_time, end_time, dt,
                observer, stepper_category());
    }
    else {
        // unwrap references
        typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;

        return detail::integrate_const(checked_stepper<stepper_type, checker_type>(stepper, checker),
                                       system, start_state,
                                       start_time, end_time, dt,
                                       checked_observer<observer_type, checker_type>(observer, checker),
                                       stepper_category());
    }
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time, class Observer, class StepOverflowChecker >
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt,
        Observer observer, StepOverflowChecker checker
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    // we want to get as fast as possible to the end

    if (boost::is_same<null_observer, Observer>::value) {
        return detail::integrate_adaptive(
                stepper, system, start_state,
                start_time, end_time, dt,
                observer, stepper_category());
    }
    else {
        typedef typename odeint::unwrap_reference< Stepper >::type stepper_type;
        typedef typename odeint::unwrap_reference< Observer >::type observer_type;
        typedef typename odeint::unwrap_reference< StepOverflowChecker >::type checker_type;

        return detail::integrate_const(checked_stepper<stepper_type, checker_type>(stepper, checker),
                                       system, start_state,
                                       start_time, end_time, dt,
                                       checked_observer<observer_type, checker_type>(observer, checker),
                                       stepper_category());
    }
}


/**
* \brief integrate_const without step overflow checker
*/
template<class Stepper, class System, class State, class Time, class Observer>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt, Observer observer)
{
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    return detail::integrate_const(stepper, system, start_state,
                                   start_time, end_time, dt, observer, stepper_category());
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time, class Observer>
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt, Observer observer
) {
    typedef typename odeint::unwrap_reference<Stepper>::type::stepper_category stepper_category;
    return detail::integrate_const(stepper, system, start_state,
                                   start_time, end_time, dt, observer, stepper_category());
}


/**
* \brief integrate_const without observer calls
*/
template<class Stepper, class System, class State, class Time>
size_t integrate_const(
        Stepper stepper, System system, State &start_state,
        Time start_time, Time end_time, Time dt
) {
    return integrate_const(stepper, system, start_state, start_time, end_time, dt, null_observer());
}

/**
* \brief Second version to solve the forwarding problem,
* can be called with Boost.Range as start_state.
*/
template<class Stepper, class System, class State, class Time>
size_t integrate_const(
        Stepper stepper, System system, const State &start_state,
        Time start_time, Time end_time, Time dt
) {
    return integrate_const(stepper, system, start_state, start_time, end_time, dt, null_observer());
}






/********* DOXYGEN *********/
/**
 * \fn integrate_const( Stepper stepper , System system , State &start_state , Time start_time ,
 *                      Time end_time , Time dt , Observer observer , StepOverflowChecker checker )
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
 * If a max_step_checker is provided as StepOverflowChecker, a
 * no_progress_error is thrown if too many steps (default: 500) are performed
 * without progress, i.e. in between observer calls. If no checker is provided,
 * no such overflow check is performed.
 *
 * \param stepper The stepper to be used for numerical integration.
 * \param system Function/Functor defining the rhs of the ODE.
 * \param start_state The initial condition x0.
 * \param start_time The initial time t0.
 * \param end_time The final integration time tend.
 * \param dt The time step between observer calls, _not_ necessarily the
 * time step of the integration.
 * \param observer [optional] Function/Functor called at equidistant time intervals.
 * \param checker [optional] Functor to check for step count overflows, if no
 * checker is provided, no exception is thrown.
 * \return The number of steps performed.
 */

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_INTEGRATE_CONST_HPP_INCLUDED

/* integrate_const.hpp
yXxLe2LwE9K+XtG+cYZdt5d9HdCJrV0evZ/ar+IaKmCxso9yHfP+qfFzLQ+a9A9N+scmvV2lyZtvN1EO5A0+MTk8MSee/6DJf9Lk/9Dk/9bk2z2c35n8H5vyvzf5GVP+jyZ/uyn/J9WPvSX+86h/Zj8+T/3S+AOFw/FfIP5fiU/+pB/n/xJx/0ZcOZeq7+vp97QKg1dY5u8s474f36d1X8pPVnSmmDvWr5HO67ZdLPPGnPg7Xv8k/pvEv8X/1qHjWaje//2L27/oOH6wW2LyvDjHnRMdTDFO0ctIlwQdA0OYrbL5pUHHmhTTryJdFn4fcc35H0hPCzpRnjQJQ/yjFKx9f3Zd41+AVQS5G5qOwDzOA/9W8wBijXb3J8P7qv1duW8ADYGN0Xs42/FNcreOnabPvBJW6GB4g0LBioiHOa59Y0rHhSIu4bk5LghjKkm6NIgibjNWjLM9Zby3LPH3nA/TP6TKlYdvunf3O1kGlZAJ18IqKYuCSuUblvSvT0KIQ52RHHIp+jPz9xF/ZmKlnE0rrBT75f/GGoEuaO1MWgeNa20lDPyXPr59IIpBrvuofHLw0rUxHbV+s+0j+htG5sUic+kXtIUyd3uMpea8NOYc9Euo3u6JlIyGT4vgqT7S26USdWV/JLjW9TbVHwsm40tFC06Suf2hKWZMF1eqtXeO6ZH2cN8OfL+PMwJv6kBJpdghyIL6IO8G/2an4KXb3lI/4Pq9wSt2sL4eypN9kXI7l4RxnERiz6bLVJ+u2M+NkfZ0al5ttszu0gcu/cK+iKO4E3iFfcIxUip9gkZ2zKvVcpHkCN/6w8tYWe5ZOfwN1yHPvZeySt51cfgqnhbS9uzMuwCbHui39TLuvJike0JALg7v3pVjGXeNLS14rKe7L5N0Ec/SiCrLuLnaP7lvn3z7qunO3Dtt+Cln0324nZme/jVZbCZEZu/J6V8BfottmuHg4jtVVPL8TGVUt/dShvsq/S1XtMoVrfcZWrNIayZp7U9as4kXlRG/r9L009zK8M/cjSONasMr5KFlWkO8WsVrhuI1z/B6fyX+DK8DSONAw2u64fUB4s0nnj6rcj7WA5pHfo86VJLWtpam5kPc64Ku//Jl5vrzQx5eQWFk21F/xgWM0tNNeqAwnp5cIumrOAYWuj6D1iblLHRDJXAcDDZgtdjxRYCf5OBci2f5u3IwEiF+Y0i7wNHGi46Cv8DBwvMaaj2/ACGuArUeVtDRn8n097o1dsYHXaxszimORizYpwaMcG549HKh3JcYXWgyunAo0vpueWDOyi01+QPGDjWr/OnM1++nrqik3VP5NjZ6S6XMLdLP8tb9hXx/FHoTGwPPlMnZlOmszxGV9Lcl3+DxXSzKoUn5N7qdK83Y+kil5xyqjf/MefdY055y6u1xlVH6qXdE8UCQljjTig/6Cm0VO9Vlxn4K6ZSp3+pK9jHz9ZnCtUjreCGZEWWzc7CO5SEDllffzcIb+bwjqHgvMPrVb8quNGU30BZ1K7u3xrQ3jXSG5Raw3FBlvrUFGKHoikTSPQ7lhoaBZffsyedgvge5zn3j9KxNNjYf0tTcmFzRtLQx2TXU27vZTZW+jNw4O2FP9a3He8H9ewfBlsrhdxVPYJs/que43aW/TzRj9uPZ/uS52pNY/hPEO3QUOSAuZXvf0ICLFqvEYbNy9xc/pebIrWoO+rTpl5Mr8Wf08DOs2ymqPxOTh8vmc5V+2ZzK8qdVjni3Zi0/4lxzcil+y5yh6v/5bB/7bWhnuE5tPhEtMCeXsxTds1X7Hpk6vH3n5mnfF9i+L6ryxXsNL39+nvIXsPyFqvwZtIv/5l3PyG7KnQD77V4ISRQFg+l218Y=
*/