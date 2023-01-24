/*
 [auto_generated]
 boost/numeric/odeint.hpp

 [begin_description]
 Forward include for odeint. Includes nearly everything.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_HPP_INCLUDED

#include <boost/numeric/odeint/version.hpp>
#include <boost/numeric/odeint/config.hpp>

// start with ublas wrapper because we need its specializations before including state_wrapper.hpp
#include <boost/numeric/odeint/util/ublas_wrapper.hpp>

#include <boost/numeric/odeint/stepper/euler.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4_classic.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>

#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>

#include <boost/numeric/odeint/stepper/bulirsch_stoer.hpp>

#ifndef __CUDACC__
/* Bulirsch Stoer with Dense Output does not compile with nvcc
 * because of the binomial library used there which relies on unsupported SSE functions
 */
#include <boost/numeric/odeint/stepper/bulirsch_stoer_dense_out.hpp>
#endif

#include <boost/numeric/odeint/stepper/symplectic_euler.hpp>
#include <boost/numeric/odeint/stepper/symplectic_rkn_sb3a_mclachlan.hpp>
#include <boost/numeric/odeint/stepper/velocity_verlet.hpp>

#include <boost/numeric/odeint/stepper/adams_bashforth_moulton.hpp>

#include <boost/numeric/odeint/stepper/adaptive_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/controlled_adams_bashforth_moulton.hpp>

#include <boost/numeric/odeint/stepper/implicit_euler.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp>

#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/multi_array_algebra.hpp>
#include <boost/numeric/odeint/util/multi_array_adaption.hpp>
/*
 * Including this algebra slows down the compilation time
 */
// #include <boost/numeric/odeint/algebra/fusion_algebra.hpp>

#include <boost/numeric/odeint/integrate/integrate.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_n_steps.hpp>
#include <boost/numeric/odeint/integrate/integrate_times.hpp>

#include <boost/numeric/odeint/integrate/observer_collection.hpp>
#include <boost/numeric/odeint/integrate/max_step_checker.hpp>

#include <boost/numeric/odeint/stepper/generation.hpp>

#include <boost/numeric/odeint/iterator/adaptive_iterator.hpp>
#include <boost/numeric/odeint/iterator/adaptive_time_iterator.hpp>
#include <boost/numeric/odeint/iterator/const_step_iterator.hpp>
#include <boost/numeric/odeint/iterator/const_step_time_iterator.hpp>


#endif // BOOST_NUMERIC_ODEINT_HPP_INCLUDED

/* odeint.hpp
i+bdfk2X9ourjR3sF65rzofO3fFSR/vF7tEda0Tr83nuk/B8YKHmJyJ3fznc/yvcr5/AtzTSKgBr9wCA9b4fw7u6UfXil2jGZ7PbnOp3rnnfO/b87Dbesecz7/tf7DjvAxld2G24FHRrZGSSFG2vCcuJjWOilackJ9qjlMOLOhTaRKCo24EYYOoiKZHlaC9MBWwfX4tAxlqZDRUsECmqViZtM7KXVPt6y6eiq4NcP+Z8Kl2Wv9AheK0gOh4nVjZGf7vSvpEQSW6ossdOfK+NByVGJl4UZajCOlS6oSqLzsP1uMXUxlXcKwUgiqowtN5MJg1ZAWBU7r0RLZj5sBbRyqivIAENvsSoDknYwZeYGsw8e7NRYPUtr6arCQjEwBJmgsrhRS2zkPDmeMiiCejbO2zxoaDKnrYYJ7miToI1BVVmPx9xkotOlU6WUW6PyGuP2CaGR11PZddMj/TjsP95fE5M7Nf6PueOoRp9Ncvbn1VV7RFdtR5WenkyVuJStyQKxP6V54W3kvHq86kAlP5c5xgv2E83pvP9ZI9NZ4Vo1TMyzlKXfJJliKNwzlfTUUeFQRTod9WxPtuduZ3rs+H40eKFATHoSxodELNfCDtANwl6QEwjijow4c9M0RNm65+rTzgmqDYyYbb+zxo65FImf/7S4dF6pph1Gdr73OvyeM7Z12W60Gld7so5n3VZ/kyX61IzLIbOpcbaiyqO
*/