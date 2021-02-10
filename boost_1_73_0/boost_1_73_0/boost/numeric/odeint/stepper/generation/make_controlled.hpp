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
S5zWEwME7K3gLIj21XYTkf72oBaZoJoRpmE8cXnekbkqBOddb/AWWIjmrsIo3Oxev2V/9AGGFTsIaZzoVVs5NTgfO+3O24t3Zxf9U86NvZywlKQNXNyRbHqpvVAMMJxPfWsyAWEZDkkkgoC/gGFjyJCRzXj4z87w7WDU0YjyvEJDZtN+T3sEVSAsEuQoES5/i1A54U8TOlLrpz8zCK/g7hHt7kp91iqbk+QkqWxJ2i7p+bn+pdR5Hmf5Jlu5KZWGvpABhiz1ymkPOiPndNCHLyMEZqQlnsbRrUj1cZk5tR+Ytlqj0253k67xsNUfnXWGPBkanS8w2cjA2DsyMXLR6Q16/Iz5Z91Or819FSAWxtG0/jB6G+qD0aAqqrVOvEzfJWP4T1t1OeyOO5XI9QawlNllnKSgiDz+trdJJgBs3KtkroPspo1zPhx8urJxqp0oGjedHmxiwc3mr1BLc1ueJxI+Kd+TW+SzPXqLgzEfAdVnykkxNRBRYEJa+VzV7r7rcInx9zZPt7W5+g57F6c3KJ3YVl8l+uPex43JZi9aF+P3ZaL5BT87rf6VtlODoDpjKWhJRAoT5yW6PHEWeUQL/m1ffaexQFmHRBatrPJC4UZFcrilBwLDZ1YrHeqVQb7y5epQWsplnP8fUEsD
*/