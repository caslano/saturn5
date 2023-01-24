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
SYSe4NhZfscLasqJErdyvNDPMoo8CytjxzYBo8cVhetk+CehnSt7HMEgIXmdKAlZUocVuVJXGkfFLRwRg0ScZlqup6Dx0/1UFG8GJm6X0Kmo1XHJohuQP0kUr6AE7SheCltYN32m1lz8xy1FEhvC3WhtwpJQ3GvmYoTrMVFlSQJU30zIX6eRwYgl8tJ5YQyF9S8xhFsJ7cNYQCWRbqsbDZKCkpU+jmdiJIEzZznN5WDsxcKvoShO7QsJmwoUs7lEgBoSsT5GtUMt6VNjz3luEHRXYMgEzCgOxluj4GGiyFT/sXk6YQFhLKnDmAhzOGpiIV8QJA5NZS8qtGNQ/OUNHoZVhYvgr1EFSkixGUAydzAhkt/lx+UlUNSGAfooce8KfMwH4Lk2s0sQZfOjtQk2RlzxT5awbkWKhqD8H6mSJlvLzWWKeIT7nyYOiULg5UzkEXklE9w5NrecRBUOwcSbNeab3dTlTWPi7KhaWQeJ4MWXJ0avRRJFfKD4Sw2R18dM9ZQMyZRb8l2GRHtE58XQCO6Gpihn4h+KPHvyO3dHKqrJTI0o6YOBxcMlYOYyjjAnj2CPEkRcfBFBlBI/m8iL5fjdceenmE05o9qosbZwPqpOQw/D56DW+xgyFghbd0v4TxkCr6/GXJwpqCHBPCSW7JeuQErHD6ykFXYeF9/E1geiqJbCLwJiPSwVRRcx2XgaF5+qRuC0Ba5xCKtc
*/