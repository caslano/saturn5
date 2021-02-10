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
Q3CZIdQqF4VbyRAKNu2iEqYM79QQlcwjpcFgVTksqhNotrIRZp09oUuDhhQL6xajpHFU16Wqf0gkHx1K0WpJROQDJeWKbA6hlTlqn+zffEfReeoNfrA1d3pzUJLEQC+ewXjWgwU3woTweZy+Sz6m8DmeTuOLdA7JG4gv5g7sw/jinFoviEwDrhuNhsg1iLqpBOYd5997oiByPV2ujuAVfJxOti1ero7p2Gi13uwCJxSQSj75ilpRhzhZGs+G4zFYTfsCNSVGQfBYyKxqc4SeRUON790P1VjnuGiXPiwk9Z9y+lnJNRwQ9yD4FgAMaZep3E2nOe3OcOAG6zSgoyj6bs+WlVrwigkpbN+lsLeT5CyesHgyGcCjV75sxJIPA3CgAEWjibHoG0uN1SH0fkIZQEETjfmV7A1OfY1GS6MB6WiWstF0yv6N3ydTdhafu39/d2ocCBnjsZCbTYd0uhX6yMV/L+Be0U/09xVmFVneNv0/VuasZQYt/cy8YaF3JLlM2eU0+TIP6QJZ+Bxq7rFHfbiCltANx540D8xSGunZmxFpSs5HIRztq/o0mp4ls7tM8u2etJOdfTSmKLfXjcmEiCyurbsx0I2dS3iYYacoHX1Jb2m8STRiP3SPLotC6drXU1bgMTvrX+z6vU3d
*/