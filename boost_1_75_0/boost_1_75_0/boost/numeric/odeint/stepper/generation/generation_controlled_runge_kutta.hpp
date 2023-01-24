/*
 [auto_generated]
 boost/numeric/odeint/stepper/generation/generation_controlled_runge_kutta.hpp

 [begin_description]
 Specialization of the controller factory for the controlled_runge_kutta class.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/generation/make_controlled.hpp>


namespace boost {
namespace numeric {
namespace odeint {


// controller factory for controlled_runge_kutta
template< class Stepper >
struct controller_factory< Stepper , controlled_runge_kutta< Stepper > >
{
    typedef Stepper stepper_type;
    typedef controlled_runge_kutta< stepper_type > controller_type;
    typedef typename controller_type::error_checker_type error_checker_type;
    typedef typename controller_type::step_adjuster_type step_adjuster_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::value_type time_type;

    controller_type operator()( value_type abs_error , value_type rel_error , const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type() , stepper );
    }

    controller_type operator()( value_type abs_error , value_type rel_error ,
                                time_type max_dt, const stepper_type &stepper )
    {
        return controller_type( error_checker_type( abs_error , rel_error ) ,
                                step_adjuster_type(max_dt) , stepper );
    }
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_GENERATION_GENERATION_CONTROLLED_RUNGE_KUTTA_HPP_INCLUDED

/* generation_controlled_runge_kutta.hpp
wamsN2ft8Vp4Xho/d9NTY7rWTvbUU9rKGSWB4UY9GRuPCl8nPzas1qumt0HWCmJj/lU3Pz/6uh3/wYGn3gjDOF0PBXjXUmEVWG+4Vby2VQyyEX5obf5RNmNZrxAG5d5NOqxHPT/rvZbKXDfKZohAB0Ub7Wo9T7sY5x24P2qrzJUbBp8wE/rI5Fp0GvrVenQYF1GE643md3qmAFgF6hfOBVphJ8Td6/X6oArF/vqwnqU9O3xC7ClMeWvLc0fW+9srB6TKQ8XJ9rQOz5DOhQbk4W44IxzFan90D7sjjAqH9W6sZAd6DjvB9Tn6OphCMqzWQ4fJ+9soAjmT5SDK3cgHMOtio1uMouk+8ZedPhWTZIhPrcQG/8U+mcr3oEzfCKQx73Q9uh67cAcZE1h5Hxt93p18KNjVqBhgO539drU/OhKt04+/tNbQGG14/qC7dXzyYCzCK8/OrecOOBC5Ohb9U/MP8jneRUmazmmmLqd6ql0wHct9zGeKfNzvVymfQa2OeV7kjnQ5YCvT84LeZRFZWB9piKX/0iyzrdaD+YwG5KDYKMWHqIpQg9rEMnvP9ZRxtlcozdfTSoWiIrhEKf7cxdLRZhbcPhYtQsfjVv5yvNjKO4MhdKv16tnOgmB4Ejq1mFE+xTFcpp/DLDROR3ZuPXqqN7JIriwTsTZ6anTCwTPB6vNJt+fuG7Zt4Y9TO3X8V4XnqefCw6gj0++Y
*/