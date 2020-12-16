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
UKtyxCjDbcF/EeaI2weqP7abo+DS+Zg/PnuFQLmcW15OhT3CsDtlmDbDiQYq7zxAzWzkzSshdiq3dWEYV8RQMBqfvc3V2ksS9e/Sp6asI2UcHNSnLZCsPejFe2tRoSuyUQK9nY/nS2A7gkwLtAqPsEfaqe0rA6BlczBLrEx27iWz+97QEV3aTni7O9/I26shWtnLzb8e2nlwPewVW/Mwg08ZsYOf6h1xLIaX4c15nRqActgvn6Tt0XaUPFvWUvZsXlvZHrDNna+O2EettC+G+CyYMC2Llu0Hd/U+DHOl2q7I4cL19nGuzfYrqqL2UTjI91ltVxnyyGubVPaCzOK33peWvYJx/4n0uH/wOo77j/7rxn3UyilGaqdPW+jwPrs8ayEPOtCmeMD4HMfRLPlJW1vJ0bKjkCpqLWXNiJ+f16XtK3kF1XulrDlvb9lxoLps30zg9qoRx0Z0aq2dP4m8qZS8nte6GCf+Of708o/rCbEEwHaX5PJ8lTN4crknuYlUqS+dIKZX8JzitPVYlQPW+eC0ziyu4CXyou1R+Hy1v9WkSvJl+lteSVJVOCiIn7kXWYpiPSpnej8HiOSmp1nwScZlwSsPikILwL81KefwESVMfU4lRKM7wWADifCA/cEWEm4iWwPvRMktC09A97BClGOPbDtsEdymZOM45r9tmB2RN0Pz5Ae0KQ7ObnoISUiLZO3sMMYuwK7f0OUordACC7vmz3Ye16bk26Y4Sg7W2J6ttchp9CRUxMpCB6qPwFPPshWjCxxJjcmZMtwfsr3csv1ac+cR2D7k4JBGYmdWMpyfDHsCehbhlKf/OBAmvlBgMJuPXm5aog8wfO6Hj19fL/wdCVgcEMIyWc5of81c/eA8wSkhI0ix0MNl27PZhTIMbSzaKR8Rzgnpf8PV9KDg/xdkjo8PiKYwNSBlh35IGIBpZxBKP7jj33nTzsah4ks76arcwelGWjlxuDx9XZrlioxDOgjbD8Hy3p9anWZhp/qi1Or0WzlyF37PFWloWWRrfh4dN9d5LXcuqfuEVQkvaq0+McCCaNVdVmFDzBWmEnlrjVxkuqSmL6Jji4Nr3cfoPNrLFfkOTQeK8adus5h942G67pESrUXjbJb2vjliYZxaCGedaSF8ovtCeMtu17bmWHWXa3ONjVTKlbH4OCiH/thAc8Xr1BDmzXattQOi+rdopN5Es7EbAeXar4PNNsAGve0F2PCgOCyypsuq5YRtEd2GGX4gV1B+cCazFqZQtzSbSdNoY1MwFYRe260JGwykNVes2m2urI9wCVftnIwTs1urxYxDU2mUZC5emQ9RzsuL/Q63T46seW5geGLGBoFLtUZ2Ze4OwSroMlL8I/hPaXL6BnQ31nPG8lenaTpNxYlJecg/eV7ZxWMWC1JfJ/KYg39z/0Z+5GiFa91NCmlwPKBbvlg7qeXAEvOuSvhpH3VCNJ5j02lwboHBeRwT9xnMzQ2ui6FYWOULGJ2ESWgDUMpkVN6L7Jd9hchGbvH7D9jZ3jWzUdlA5jo1H4uutV0kmEbFpJ/6NP3EV/bXL/gASOgF8gNPpkhsVzrKNhKt3vF+RPoGI+1PRcpT0nT4CsKNc8VdW9q07LLmb1A+Eh5mbIMJw9D4R8LhMo70cDXczEbts62Ky+ZZzHpFCkRqubd5TCCC+goWP8oOT7EcvI0s93u01LvRTFKbbcLrJ7xVTEDTSgxiRWg/VQiSjOX4tXhJt+3aaQoXH2IgjL8/tTr/QNqXpfv1W/CfsTp/UOm2OveKlE7OIamdJK7GTmOFMn4xTARfTi9yLhU5Xoj/0xbt1Yj5rXTMHBHzeHn3mPk1JBss3JdqO/36azVy3T4UR+U=
*/