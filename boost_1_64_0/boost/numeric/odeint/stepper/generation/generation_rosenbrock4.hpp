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
VN7mj+P9JKehdkRQvkG6Q7DACc7S2Mpm4Hno52hm7OGdElU79ghfxUSXqj2QPOMNiYpLJXrNcwiKHKvoZ4piE+tBEsgUhn2kf83nfJ5wg6u2Mlkagt0iAvNVc9aiH7eJOk+nh64Hjua0GRh1POF8GopRRBeW+E2x7nnoVDI4QaM0VyaQGF0w9/Xeb1gLe6mJQ0wNP0hJ7lr25OiiyAnifEMATHxWiWaM4eVztaOZ+696dKWpMmAEtHhRGl8aSGkmGn70zo1g6TOl0EV93FR3CeuOf5pOIIzPYL4R5N6PhKvcBd2JKQQX2Gz1rf2KCnhS9Hwm0OfHDvXoXZXLAJ7XshCtTjtNrerlesV5RB2XJe+P3VSuVwkC0cRYLe5Is0n/fkqZTc5d4qFLYE0Gco14ydv8aJZIv6imRPyKSPEZKn0boM0Qy3LuYTu8Ql+8wI+o+LKbXwT4mO8l0V92ofFeI6uWzxKj+CB0sqGM59cNIia+36VwItwBoSUBk5/4yBQO1Mkx0FaXlNeDvTs7MdneKES386IXSc7Gd72JBuO3BdhQw2B3Kro94JFEhg==
*/