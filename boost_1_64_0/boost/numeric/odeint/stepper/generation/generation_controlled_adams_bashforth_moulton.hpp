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
FTTjGA1RZskof5lw8v/X/6+/82Xs/8ZgQMsnz9pDa3K0FrGdWBiXGuuL8ADYo6XY715cHYg42t0MnvsMl8JBTcxpcZ8Q+ugYv4st4RvAP14JptgXSWatmqDd70cM2766yweGx7g2X2XDUf12cZxM/VHuJll2vtbIDIOzIW5I9n8A2/YpnPgOU2mNIq0Ij8FKtZt12/30lRawtpc14U8RGacP755QCWAZrYRhoO2fNVtmywUHsxYZCQvtnTFRgBRJaVPLI285QkOwkc49HhUJeRYvNPd5r3Z431jt0N5I2L3HVw1RHmJhJceVh0TqlphAAmJL/DROsyIUOVMpjCMjBinpFdd9cjS5Zo45eJqpIlvLBdIdmNzsWiLRB0u/Im/CNS3h1V0zhUGKeWa9NgORQjdR5FLyHmUQc22tBjcBs/W8OVJehl1/q5egZraTUtzmCOd6j9/pFBZJP0BtrNobhJ/1IPysB+vFehgjlwRMLTfBV1+Cp1mDB2pkDZ5PytTmXDwYRZoF9hVIbg33Am8jB//F2s6Fi/51G9f/yov6hqac9H7NOrtDgZWnrtzxhzPWo4lzht4SzpTXb4RXDQSP5MYprX/MkM/zGQvR2uiO8eqSFKpDdD0kUX3JbJNYINLVNoisMJvYllOyy6KwreipN3M514l2i61CD3jPddeVZJCfkvtW3Fqkix2lFdR010XwqmmNMAkvfexSc2Yur9FP3GJ2+ZHa5PyaFGvbjxyWR61LgfgLyRGlyxiTfJxlxO1X+CG5f4IV1td9lLm5YTyYFxMwtu9BClsXYQQLd2FHxGDhuAT+4JIOH8imV43+rZsFEFpr++cRrD0+Ff8l72lP+fEUohAaryULl/dVL0rLwdsXyhNgRmuR7XIxNBzc0SwKmG/DP6juG2g7C/alTjZF0OFe24gxZqdFpilMhOUdfLyHXeso2uFpMe18vouNImElkRufAjvAzo74UsXbqe10VXfyTevyPsXUyzwQ/oySOcV5lMQLR76VOL9sO3w9sVUNhd4dt+fEZyqxaQ2FFd5dy96hDRU3j9RaAn65m4SYe1pg7su3S911/tqO1dd5/xAqjjwtiGVguJdEmhLuX/Ib2ylNokN85LF9Lhesk1WK+OXl/UN4SBrHZr0FjqtVgWM0V2K8bBttV2KM+v40QhMuNZxqblcGRX5+Zoay4WFLStmw9HZJkv9lHx2Q58+UHdLWkb55EJDrHq4HtHX2PPHuCfXuWEckQ0RzSAScEBFpIfes6PCXcOAOxLewp2zkwUt9tXUVcE/1Hrg9e3JklyfxawzvL2sznRjaB7dWe9ijkh/Qqg7bqk5gVH9rujQsaEsMUz+bEuxzNFK/KNskZ4Zsk91JLdvbFr5ImXECWoXWbEEFoqxl67R1ljwaZCF/kj0OlYEdgRMxS3BAePsNJJ5qk0RCfeL2z7c2rAPEuJhqsdaM4ysaU/LDNWbRG6ab5PB3Paamm7y1tcIp2PkKNx9nOP+sdpj6DqCCqvmmaQJXsupnOY/MwWVIxnfF/Eh32S0iXWy1m9YGUg1tHu0e87lbffA8+3llKvuBBGEzORP9zaslGI1849WknAUesZcCYzgaieNXWbx6MJShgXh5hOcX0bzRzBpQxq7OqF18+TsUwr2+aHFrhKkt53RsiDi/++jHzHFeaaHGQ1jHvCDGXaf8gNpZsxD77Z0G11RRHnnTYbKMN/O7rQF8FzRe8NOpPiDhnQ+bU0t2fYvFTpZuKvmiltorYS4n6lSjPyarBFAG136QfvyE2IOStkpFmIcfyWuJSUbwIfJXWpoplDU+182gBr7d4hvU8uCAmFAZQyNchTpt68MOLDZgBoyu0JTFub8=
*/