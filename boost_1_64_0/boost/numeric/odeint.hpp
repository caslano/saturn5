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
LS95Ep2lciaM6VeHNf5DzBcJooJHeniWerBAV3zj1eF6cekWe+8bDwM3UBcC6Fuvax6ZU43Y580F4udqEdkXpZfghuVpYinxdujxZaqqAI0pivq4pGC46V1QDKpASuYRa2UpKk6h97ubzGp1vdr6SqtZyV7A3maAYxvatRi/AYguPtqHSpk2zDY/T5wMZ5I8aVOWAgf2dUDFlP4unCWEZ2ZHPOe6FJlSQ/p3d3J2+e75KC6LizOCELHW4enIRQGrAS+lftbhMB+IhxLby8Zd9XEh+PwZpt+ZRhj15I5oXBAt03CxmkmvLDMvGCnNLzgCH4yAOLvWPHJxaG3I7U/d+Af4IuMI9QGGLKDfSobUHsOz2VQzrpDgSQFOIqf9iAD9kubLw7VeSmc6t+gzESAO42/wU0/jYaUP+SjE6xSTmGOiXm8+mW/XEwTurh5YRqJY6CYNqNrfQ5Z+uyf/ES3HTpTvi9ogHf2VS2Jxa8vT5/xM3WT0+TQo3htbuE6bzfCgWlB19OnBG65e/J+tp8RvWjHhmQe4T/OSDBrFMesja2d7bQHyjZEJAUc1GQ==
*/