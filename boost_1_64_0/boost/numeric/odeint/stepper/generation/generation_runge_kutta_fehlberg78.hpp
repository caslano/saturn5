/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_runge_kutta_fehlberg78.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Runge-Kutta-Fehlberg 78 method.
 [end_description]

 Copyright 2011 Karsten Ahnert
 Copyright 2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta_fehlberg78.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template< class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resize >
struct get_controller< runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > >
{
    typedef runge_kutta_fehlberg78< State , Value , Deriv , Time , Algebra , Operations , Resize > stepper_type;
    typedef controlled_runge_kutta< stepper_type > type;
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_RUNGE_KUTTA_FEHLBERG78_HPP_INCLUDED

/* generation_runge_kutta_fehlberg78.hpp
W4LcTbnWCuu/5BKifxLGjjfOytq0S7lqr2XXXe+9D6Q+ODD/zDI1UyyTjlCcu33LjyvhIU0JV5dmlHOB3sG6sj29H10MMhhh9cAyFvfFdMLC8GD/4x8rdgeycTJsiOhnopFfu10oGqtAg7+5lU0+ED+qtkFjRHS6KFAxwUdBOItNAbBYKJTidhFbR0j9I2AJ4xMKdS++TaE3XuiQVlJVUeBbrUGdCP3VvG6lvj/0o6m0efRFn7dchJr6RtkiblA7K/EH9tXOozZve4YHBHAsct6RERkKfJYf1T2l9iq1hEI1VbPbDxGbaHLqZg2MrcXQEIIY6+4w+9RZ+F0isW8lYzjciq3hU2F3hKl0AveGOqFiM/JrbsLC/WY/xFUZjBfaIVTKj7d9QGM6IHrw9wVeyH5KEyGj/X3wN6eM9NtaV4tbFFJts9or4dxwOl+UOtcmrxVjEjjAbMYkqIdgL3MoFa6dK3D0Xad0rKXOzP1qYDkx1EL+33obEIChdBoUzbIgy4ROV0nXeuT9afeekES+70sa+QsA451r2SvZvOB4Zl9S3wq7gyca9DIuKQ==
*/