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
fJlQQH7GtWppmjUyWMOYFkbMkne6Grb5tDJ4o0vgnN8q2/6g1tsKCCRrMb5pXmwijp1I8SEv391RbVicDJ1gYIAqcV6GedlMEmjWKWh58tqm73anA0VhP8zDGSaR9eMtiqNW8HWYGDpoLl8hEwgIay/5M09O53ZpSZSENvlQeAtBrNduiBbkVw+LTn0EMTn5tufvYmQfCAwlYX5EDDdzDGMAfShnOCHCK2vzdPst5A65VyqvKJSGce645jY2jUu7td3RLshsiU7B2L/MVQs5RBg488s1zv4qysAd1YDfEK3tHRNmTrKcARtVhY6ulD/yiYlu5q+snoHpCJygs+yg3s+9CaMJ34q42AQa+uQk/jnHVaujJTs5JiTM03ouF4GjcJ7svXHyirl02p8gAN4xW/eXZC2TFy/EsL8rbfo7aCKL5q1OImVxDGkxTQS4ONniJ5M1eT2epK2SA9zKtv2XWvXE4UYE8QkskDf7NK+kT3L7a5J8L8HT4bSPy84eS4q2wqyQvCLgQRF/s5cSAXBk8P3zicanixGq6UELt9PJWP8bHM+G4KQreEySLw==
*/