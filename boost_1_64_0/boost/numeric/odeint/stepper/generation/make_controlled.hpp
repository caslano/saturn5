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
7BcE8NANBmtMuI9HcF6nK0VvPR3bp0hYALV5id3A/AON8d2+af/Wd2E1+r+0ugag5l81IDACQK2tsJWyXEDbx3eiXc37kD9xHPQizcF+Vusrqs7uRg+PawAw6YX18ybptBDDA3rw2qrWaL7kYkC7RTsTNa0n0D/i5ahLw3106Pq3VonL/Jb552duRIoZfELnDyK8g0yKqw8SPUOI7ftdX3ALuDFohqv7FpLm5fFdrbJGGL8OtmVyjY2UOm3RapbVOgxIFXsBVTYZl1zH7SH6rnI05VXaWMdZxP83Wv7FL6ObGr5PBCzUbtzjpxwYGNeoAoKsvkF6/XJocpkuCMueiYnkqvhAa/gLL53gsamYEokiVVL1JS/KBJIpPuTyPINHvqiE/L79/rCqqq7K6ddTHwZnNhNUljbG8L4DzycQrsNz+TKPwL4UVzfoIo+NGAHHVl2Z+xkAIVgfPbLiV6Q7Q6I+lIPemKPgy5xjWWgOhJH8oZ7TY64gz3j1QOePeBAfnGOlZ06q/h7YZ6tQ6ZbaInd5ESlLdNYWsV0RbSgQvY9DK62PlLD/GR79bA==
*/