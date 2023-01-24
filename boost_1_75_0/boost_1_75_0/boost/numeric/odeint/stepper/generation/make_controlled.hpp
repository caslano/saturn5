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
Y59r8+FWksiiVDWvR+EEw+EL9WhV0QzlzumiRr5/Ctu4o2Zvi/LwevN7d8OHrHdQ44XXMBBQXkP6Rfedz2uO1V7maWK3kAdnDw/Ro3vv2pdM4qLA7cVROLneGO6Tul5bx/UY8bpJ7sl3Fd81vU/nPueeBawlnxmHnrcyHD79znSI+W/Fr0kL52Yf8661spD8g3WLTxHbxGbQMlKWWvwJstHqd8JzgXoxJOB31G2Q/j55zFBnsZrxav06uynIQHFK+digQnMmqwBNis/JmiP6hHW+u7Z8b7ootfWTZZDmJ8Mj4ztOXvxW4+iqewY2f/evTkyIcIp9B3LE8urBncf1ZkExm/fKrqzZc99Pox/zcZ3mTbk9aqa7KwGKks0LOB3CSbW9Eqpri/L0RoWQGitJt+zD+0FRdAlfAub1A/lUFB+DZBURHnNy9MXdWN4kR+QHEU4BcZxptuivKhE+ShGvoOGrMkYcSZVEuOAKFodj4ItUUQtqvSfVnZ9hKeDCxMMY0TBMXEnkQxHtIAkWI1izFHwiirxd2ZIUirC/MhUhmYbydS1XEo0lTZGiUTaSq0vg4qmboTmpSP6+IEkzVahPnMOKS8ww4jr9aLItckWXIKbrI/rZPAt9QZyuZFrxLEbQIYMUjHqu+erjS6KncyaQs8riIl3q6jhAWAZBsAG4uQoQcpEiWZBBUo2RPbZYCYXIdrYUH6Tyjdm8DZB4
*/