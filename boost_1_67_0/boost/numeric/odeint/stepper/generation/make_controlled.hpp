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
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
*/