/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/make_controlled.hpp

 [begin_description]
 Factory function to simplify the creation of controlled steppers from error steppers.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_CONTROLLED_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_CONTROLLED_HPP_INCLUDED




namespace boost {
namespace numeric {
namespace odeint {



// default template for the controller
template< class Stepper > struct get_controller { };



// default controller factory
template< class Stepper , class Controller >
struct controller_factory
{
    Controller operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            const Stepper &stepper )
    {
        return Controller( abs_error , rel_error , stepper );
    }

    Controller operator()(
            typename Stepper::value_type abs_error ,
            typename Stepper::value_type rel_error ,
            typename Stepper::time_type max_dt ,
            const Stepper &stepper )
    {
        return Controller( abs_error , rel_error , max_dt, stepper );
    }
};




namespace result_of
{
    template< class Stepper >
    struct make_controlled
    {
        typedef typename get_controller< Stepper >::type type;
    };
}


template< class Stepper >
typename result_of::make_controlled< Stepper >::type make_controlled(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        const Stepper & stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_controlled< stepper_type >::type controller_type;
    typedef controller_factory< stepper_type , controller_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , stepper );
}


template< class Stepper >
typename result_of::make_controlled< Stepper >::type make_controlled(
        typename Stepper::value_type abs_error ,
        typename Stepper::value_type rel_error ,
        typename Stepper::time_type max_dt ,
        const Stepper & stepper = Stepper() )
{
    typedef Stepper stepper_type;
    typedef typename result_of::make_controlled< stepper_type >::type controller_type;
    typedef controller_factory< stepper_type , controller_type > factory_type;
    factory_type factory;
    return factory( abs_error , rel_error , max_dt, stepper );
}

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_MAKE_CONTROLLED_HPP_INCLUDED

/* make_controlled.hpp
goPQjm/qqKqfKgGuU3Bannc+vtZijfgC1gj2LRaJ9Arm1omt9fdqJnVn3pCUOfClaA7QnK2pU/4Voru76IQP0DGR/dWRvt4BOrfkEdc4CZf7nIYEHGuherv9GpV9lHbGhQqrBR2+0n2lhrhvPLRC77nYb+X+gNNl8U8getcWDsvGhD7B/a1vJZ8/7dIoAHuu9hOxUF1Gt8chvpov61wNR4myZ0d78Wb4mdY8bwEMNUp928zC
*/