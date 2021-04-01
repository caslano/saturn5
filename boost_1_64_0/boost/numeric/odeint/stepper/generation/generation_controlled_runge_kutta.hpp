/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_controlled_runge_kutta.hpp

 [begin_description]
 Specialization of the controller factory for the controlled_runge_kutta class.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// controller factory for controlled_runge_kutta
template< class Stepper >
struct controller_factory< Stepper , controlled_runge_kutta< Stepper > >
{
    typedef Stepper stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef typename controller_type::error_checker_type error_checker_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::value_type time_type;

    controller_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type() , stepper );
    }

    controller_type operator()( value_type abs_error , value_type rel_error ,
                                time_type max_dt, const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type(max_dt) , stepper );
    }
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

/* generation_controlled_runge_kutta.hpp
keBAVWiCdFW05VHjYhY1SiPRL5Ns/yxJI9v2udNyZ+52QiySPcI8BEwpv9/xLqRM+exiCh1ee6+LlM2zXXxir03afNOQfkQZUpvxMPy0uOgnpZaoqCNm5/rQzapiYlt1StDURGmSYtZV+iYORdXEi0LrHWh6ovkJ+0xFdpJOpaPS4vavCEg8jSHIzhWMWLgQ/lgIDaB0jGQ3JHwXlxmmEq0Xw15RcKb1tmDkpAMWCC5bcPBU+jTOgAE/LRor/k486+WV9G2EgjSX5TospDEFmF+0k3xa5Ustnndx4ybh6ZDVTiS3s+BUr+7Tz7v/J6LKUuMlwcjxD0ZoYRqDqhTkltyqW3tYQbkQorjlsfyIATWTkmtVpgVEaJaWmE9RpMFYAHArlI341UJmqaHafxjnhQl2+CMuTGgFAtv7CEVmZi3KzptmoFXr8cMVlbayvmuLQGrVcVtY7u7RewMnSMLU3v2G6ul64yzpWV4Fw9GZjDAVo9q7GaIUR+H6KIEu/5x/39QfiUuVJRBGT3r68i0ufaBCbypQCuZ2JuWM/PbVw4Nvt25Xv9BXWP1pnQ==
*/