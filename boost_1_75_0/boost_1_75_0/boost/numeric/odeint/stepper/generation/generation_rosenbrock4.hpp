/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_rosenbrock4.hpp

 [begin_description]
 Enable the factory functions for the controller and the dense output of the Rosenbrock4 method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class Value , class Coefficients , class Resize >
struct get_controller< rosenbrock4< Value , Coefficients , Resize > >
{
    typedef rosenbrock4< Value , Coefficients , Resize > stepper_type;
    typedef rosenbrock4_controller< stepper_type > type;
};



template< class Value , class Coefficients , class Resize >
struct get_dense_output< rosenbrock4< Value , Coefficients , Resize > >
{
    typedef rosenbrock4< Value , Coefficients , Resize > stepper_type;
    typedef rosenbrock4_controller< stepper_type > controller_type;
    typedef rosenbrock4_dense_output< controller_type > type;
};



// controller factory for controlled_runge_kutta
template< class Stepper >
struct dense_output_factory< Stepper , rosenbrock4_dense_output< rosenbrock4_controller< Stepper > > >
{
    typedef Stepper stepper_type;
    typedef rosenbrock4_controller< stepper_type > controller_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::time_type time_type;
    typedef rosenbrock4_dense_output< controller_type > dense_output_type;

    dense_output_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return dense_output_type( controller_type( abs_error , rel_error , stepper ) );
    }

    dense_output_type operator()( value_type abs_error , value_type rel_error ,
                                  time_type max_dt, const stepper_type &stepper )
    {
        return dense_output_type( controller_type( abs_error , rel_error , max_dt , stepper ) );
    }
};



} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_ROSENBROCK4_HPP_INCLUDED

/* generation_rosenbrock4.hpp
BbQznZEln660PyOp1l5HeYJpOu259ZivwA4WpVbwySasdw3ejqI5fYfopQ2r54cmBwwIOtLQ2TGeuPCfUdsCz8ZHuJqZ7q9SVlXO2GYWZmJ1utOwfK0WWsiXw1hpz72PWs9gG6ViUbyd+Qf0f7Tz/TVjBsVeFIjS89zMOB67qnX7zxS3Wm8JvMSzLnLdeexDl6y3C0+9Ip/OFfM7v8SfV7rTqJsQe9bRyyvmq/X8DPEQVEeH2R6ANxXhelkVTAOxJwFZSNcjdqmi1Q1gYrOZDZ7nCnsWXm4hz1EH/T2pngxMefeFnAU19kW/pA+zOjv5X9SCwIlhjKbrgTRSq6wCRQLPY/GULPfm8rawveDGnO70/O315ocw460M82my2Z+bHc3cencpZ8qmi2S9UTkYqCgRqOe/7cKsbHeTD1GEp5TTG8Rt8npmR23CXUxd5HM+WIbnUXV6pijf76MO8yCoPKXrYQvsxXnS/ryj7mCvaG4MZhMwTZH3n+I5e0VgdO304VqR9VA87ySLpX6ZCycbg77MVC+IruRCOS0TdMfYz/fD/LVtuEaK0phVmIeAA7qslyvDgYkGvuF5DllYE3WcTzaxey+cqBVOsKxXRClr1ShjKcPzontF4Z1ulqdbdFEqE4E9mq/WA+Fp5Su24c72Ut81i9r9CyhqodHDZNs+WY843axX8y3M93Z+tJMNw8sMinlrZTbVar1Sz8G1
*/