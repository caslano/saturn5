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
T+6mTBhq+0KhEgjl62iVNFTn0AiR5ujhdKCDwugvgp1y/z8jMACkVM+BmABkMqPF0wQXI4B+4cMH05f6TudL1xv1xq49comBB8g/x269Qf8GhJbxYpIJylGswAX7yk1tUm1ByRM+IZG4/ho4N2uOczw9z/lMZONR1i1NkHptXpYNFMuJIAVfBWQ/PSyeERaG5/DnWi8I30C8sp5TgkrePFJTFnlCCm2C6X0aOEf2wLMHgzo8yQkjePdydMdKHWa4b+DBnWJxkXGvNxp5X+w/nJF3ZHfzvMQfMoIIjS3O0mVh6TAH+oTGHwawoXTH/SZCipfM4tqjkVEMvJRr3MwYwizDiHPqenixaEE1pu4Xw8XvyBn3LNjfJXmCqdgbFYLFOroKJeYaKpnMCphmlGqnztjN101GOyoOsRJlGjKQWRQ9p62NkIz2KbRjwaZnEvB+DGTzuN8bdMc/9Zd8STI4Xr08QGtLLPh844nOGe6/KOHJA0E00AzOWYJbMrYuhB3+sTbdwfHZsOPihsG63Wx20GdUu7ZrW/Bb2Ywf1qDaX/vaXAwfobjFE3JzjjtIe0gd1SxDBRNmEadIqUxTGHXJk1kXarjJ8UOlDL+Ur2Emv/Kg/uTxwer/jQlWi5Sc17esLau632XsEUl6OnL+
*/