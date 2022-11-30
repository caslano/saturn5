/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/make_dense_output.hpp

 [begin_description]
 Factory function to simplify the creation of dense output steppers from error steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {


// default template for the dense output
template< class Stepper > struct get_dense_output { };



// default dense output factory
template< class Stepper , class DenseOutput >
struct dense_output_factory
{
    DenseOutput operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            const Stepper &stepper )
    {
        return DenseOutput( abs_error , rel_error , stepper );
    }

    DenseOutput operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            typename Stepper::time_type max_dt ,
            const Stepper &stepper )
    {
        return DenseOutput( abs_error , rel_error , max_dt , stepper );
    }
};



namespace result_of
{
    template< class Stepper >
    struct make_dense_output
    {
        typedef typename get_dense_output< Stepper >::type type;
    };
}



template< class Stepper >
typename result_of::make_dense_output< Stepper >::type make_dense_output(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        const Stepper &stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_dense_output< stepper_type >::type dense_output_type;
    typedef dense_output_factory< stepper_type , dense_output_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , stepper );
}


template< class Stepper >
typename result_of::make_dense_output< Stepper >::type make_dense_output(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        typename Stepper::time_type max_dt ,
        const Stepper &stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_dense_output< stepper_type >::type dense_output_type;
    typedef dense_output_factory< stepper_type , dense_output_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , max_dt, stepper );
}


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_DENSE_OUTPUT_HPP_INCLUDED

/* make_dense_output.hpp
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
*/