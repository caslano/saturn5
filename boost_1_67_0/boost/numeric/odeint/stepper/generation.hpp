/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation.hpp

 [begin_description]
 Forward header for the factory functions. Includes all files from the generation directory.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>
#include <boost/numeric/odeint/stepper/generation/make_dense_output.hpp>

#include <boost/numeric/odeint/stepper/generation/generation_controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/generation/generation_dense_output_runge_kutta.hpp>

#include <boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54_classic.hpp>
#include <boost/numeric/odeint/stepper/generation/generation_runge_kutta_cash_karp54.hpp>
#include <boost/numeric/odeint/stepper/generation/generation_runge_kutta_dopri5.hpp>
#include <boost/numeric/odeint/stepper/generation/generation_runge_kutta_fehlberg78.hpp>

#include <boost/numeric/odeint/stepper/generation/generation_controlled_adams_bashforth_moulton.hpp>

#include <boost/numeric/odeint/stepper/generation/generation_rosenbrock4.hpp>


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_HPP_INCLUDED

/* generation.hpp
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
*/