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
U69jaoAmNqepXzIiUG5aAVjVL6RQfaX4NB79vpryq6BfPvyIMgECN7QtjkXnKd1oZNMS8z0zYj4iniEgGsWDmI45ZAP1zDx6WprFWrRBJsqPOc6YpsFMA6yB9uG3SFtPKRbi37URT4SEgOi96S7LUH3DESuzFYhu3GCW0cgUGSRE1hC9XwotikJO/fv9Bd/GltQnptynx5vWLx3v4HnSncJanaA/izbV0aNizCa5iaH6t3qL6YeJGAmWC+HZrIj4UFnDhhNiNNPq3FapRvkEPDoq3JUhbJdtgh+qjdPM8hCrjTS829UwHzHkVI88Yw5J91y7eowSd5yfWaJbe+CwRYpwhjKlJhYIn9+Lfy5zC/cl+F0KnlsQgi4USlWfEmm2Nv/SkXeYCiN29r1uU+aYHat8xpLIrX+BvG0s9Iwgkmrv8WU7F6K5Wog/MbsWtm9jWdMkJnp0omJPJroZ3aN/LxNL3KTAdJymjTo9K9K4u4UXGmG3u7o1S63SI+09PdIqGWkvS6cltOM/VoCDRo4B9I+pOGyA+Hc16HyvF0298WHRiUPny3EmZI25ZQhHozqyQCTfAsRwxBvJM3KvoSoCC/Amyh+/tMDVcC/yZOUzQLkZKtMMtEgq1B8FbXbzJRFlVG6OQJw7Fa4kXmdFNJ+xD8LqaihGWeO/d1jUpYB18YHelhr0lneMg+Abv7VK21hu8Igp5jnLJpmu/cVRlLLV2PV6AC+CZjkrM4/Wo8zj2t9ZDZG4FmUIUZSmUEmKUWZBIr6XeXzyOWNIbOSbjG4iFPrely0KNDeKO447Avf9uB/HvQv3cKvi3of7GO7zbIr7fbircX8I9ydw34d7L+4u3JAzuMdlKe4puG/KQjjuz+PegvsnuI/gDmYr7tW478X9BO6ncWdhEp6NuxDpvbjn4n4IsPwaZRYjX4sy0jpy5EgbdMUjz/XKGekwXFAuO3v3cfWM4O7b7zxPfzgGDBw5Mn/Q+RcUDB4ytHDkMPgMH1F0oRntouf+f/3/+tP8ZWT7sUjXB13rdlkEa7k9T7CWD+IhF56b0gtP0UUzFqj5eO/pFzqD31LTL/VVgEhsO94LY/Ubzh4UPXvQxjMU0pXyw/rYNdTyeq7i/gPuXqjJYNzTcF+K+ybcd+G+H7fF8RddSsplNR02hwMd25Hz3D/kEvufgvFJJyNdq1dch9ZxnCdap66faJ18oXHb4kyz6WslC12esKaUkjj/q3eKS0f0p1PRfWb0LBldHKon+PZHsIGcK+AMvn1zb5NvH602OzP5djOXbb8m317/TlqUiNK1dZsMzl1FAN9Mzt2Mob6QAmiSmVXo12n4UU/Ma6TD05n4fMHEv4YM2o+d4uwyRZRuF3h5K5XvKjPfgl9n4qWfjMw9ppyfTpo8vccvDoWqt1sFO+LgQ6/PEjOoARAZGkyB0YJMGqWQMHtx3OenJhi5hEaox1KYmpKBqfvau1cvcswbvsLlVhYvcvWtKxQG3T43nKXSWQhnhXSWwumXzgo4r0sV73KLhMxBgVuk7ItM3ExJZyGcfukshdNMyfcKE8d1TlRVvBABrB89RLRutV5pJjYTCh9O3TFHd/9QD3/KrtWS3ine/F74Ru4WvVpv/5VYCxWJT38wgBfn/YNWsRS6Q9loroVeNFZCc4R3yhfndizzqWVm9rP1V9rl4ojZicXRPVaElZsRaivNFrHp6RZRS81w9YaMRnvzV+koHHFQLSKjvslERqsYliwnLO6M8NSQ1SCj9cDv0ylf8rfkSNvrYLjM9HjJ70GD/XsZXJ7Io9aSZg3FbtfnRbA7M7jACFpu75ZS6ZHy091TKhkpJ6RSEkK2ZUbga70slnQgbrDcekE=
*/