/*
 boost/numeric/odeint/stepper/detail/generation_controlled_adams_bashforth_moulton.hpp

 [begin_description]
 Spezialization of the generation functions for creation of the controlled adams bashforth moulton stepper.
 [end_description]

 Copyright 2017 Valentin Noah Hartmann

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef GENERATION_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED
#define GENERATION_CONTROLLED_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/adaptive_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/controlled_adams_bashforth_moulton.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< size_t Steps, class State , class Value , class Deriv , class Time , class Algebra , class Operations , class Resizer >
struct get_controller< adaptive_adams_bashforth_moulton< Steps, State , Value , Deriv , Time , Algebra , Operations , Resizer > >
{
	typedef adaptive_adams_bashforth_moulton<Steps, State, Value, Deriv, Time, Algebra, Operations, Resizer> stepper_type;
    typedef controlled_adams_bashforth_moulton< stepper_type > type;
};

// controller factory for controlled_adams_bashforth_moulton
template< class Stepper >
struct controller_factory< Stepper , controlled_adams_bashforth_moulton< Stepper > >
{
    typedef Stepper stepper_type;
    typedef controlled_adams_bashforth_moulton< stepper_type > controller_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::value_type time_type;

    controller_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return controller_type(step_adjuster_type(abs_error, rel_error));
    }

    controller_type operator()( value_type abs_error , value_type rel_error ,
                                time_type max_dt, const stepper_type &stepper )
    {
        return controller_type( step_adjuster_type(abs_error, rel_error, max_dt));
    }
};

}
}
}

#endif
/* generation_controlled_adams_bashforth_moulton.hpp
SohHislr+gFqOwUTaqca3KYITxYY0Hla2S1w2GEUucs29ny3U1AqVL5tGxH+Qn3nkz44BxeyXQ6vNkp1plH7ekd/NQ83RDjLb8ZdEIbXsaNw0zjHSC+KhH0JtEGL0axM2WvMQ4mNiSEUSG38GmyD2EG/eYZ/FLRW9q8/FG882S6ncpHPODQhWZ/nQ/TsY8jobfGkO9k8HVL0zJ//cTS9dUt/N2qTthIgxHRGdUx69eMhjCRwM6gikF1RWG7l81iRqsKikZIRLiVAcqUm6l2t9sqt9VkuuyBbZ3/NYwpd8el4MtyVru3DjKhqtoQoJ1cp+IN6Gxy0vqI5vL0veKB5V5PcECTfZp0q3nr/n3iOcVfT5CHUW+8K6PCkNVY1SAV1Lt1o9Qlf6QSqSR2ASIfG6dh7uNB35QubHn0dfEghQTUkad2fnPYtcdVysm8MfzIpw96faymaVHCFazuhvBsLy+7Tm7u0tLAQ7P/3Jzgm4D5nxTlkuoZ0ghuAnEPjrla663+yHr5bDet3UZni2xw+kqtLbp6CxXIwKzyNlCwMMJwqMBNWbmfNDn7YRQ==
*/