/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_dense_output_runge_kutta.hpp

 [begin_description]
 Specialization of the controller factory for the dense_output_runge_kutta class.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/generation/make_dense_output.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// controller factory for controlled_runge_kutta
template< class Stepper >
struct dense_output_factory< Stepper , dense_output_runge_kutta< controlled_runge_kutta< Stepper > > >
{
    typedef Stepper stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef typename controller_type::error_checker_type error_checker_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::time_type time_type;
    typedef dense_output_runge_kutta< controller_type > dense_output_type;

    dense_output_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return dense_output_type( controller_type( error_checker_type( abs_error , rel_error ) ,
                                                   step_adjuster_type() , stepper ) );
    }

    dense_output_type operator()( value_type abs_error , value_type rel_error ,
                                  time_type max_dt , const stepper_type &stepper )
    {
        return dense_output_type(
                controller_type( error_checker_type( abs_error , rel_error) ,
                                 step_adjuster_type( max_dt ) , stepper ) );
    }
};





} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED

/* generation_dense_output_runge_kutta.hpp
C6fdrtYbdQastbvUF3IhlfQ1k7/1AYOLGJOum02yHn6FiCiXhfN5Zi6O+UPw18B2yC13ulep/4WvBoc1k8cukvi5C6v6FPLOddRzxkyPxT5ZD88Bhg0Cmc7v2cufez4EM/OqoD+5Vv6/W623lw/lCRE9ma/n+XTchTPhKvTkoAe7iVSPotOeFxZmHXST8T6Md/r80QWEVsFe2f2wsldYyq0s0Jmez15ndxfuVyNHRO3dioFNeL5Suh4VbKv8V8ogsQdwRKioO8emOwW/iv54kawHn2qUR2JeljtBUEvk+W3l2d2FuBXyx/Q9r8fqdNnCIqwmWzfq827C9eStPDtMIroImNuQ6inAroC17q4oNLOM17GrRjvNFMuAsLThTqd0Pc+kAaXLtbbPi/kMrlYRL8K/Yq5Aig/104naaJe9zssyTw57YJYB6Bv1yEZIFczoZT0sLPof8Os24X4md/kxH8kc+mq2pNy4tN+Pil2rZw/fIoss3B/g99vJm/Zz7kUdzHFqut4oD+yu36We7KwDVhX4CwxKqu0oAI1JfNUrr6TLgNhsmQc5hPtJrNQFz4Qsq49eUeB6PfPore2/3I9linqup4tSlmdmwqNsVp8Xr0wUaH0Gxy9WsURNy9Op+bvEqGDLu2S9Uu88D8/K24S5dGbqwHbZ6PaANMBCZLV8tR71pSzMsN+GuQv0Zp8JMTAHiGqdZw4QcSzrocRo
*/