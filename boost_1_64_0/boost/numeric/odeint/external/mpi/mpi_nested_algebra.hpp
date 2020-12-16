/*
 [auto_generated]
 boost/numeric/odeint/external/mpi/mpi_nested_algebra.hpp

 [begin_description]
 Nested parallelized algebra for MPI.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_NESTED_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MPI_MPI_NESTED_ALGEBRA_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/** \brief MPI-parallelized algebra, wrapping another algebra.
 */
template< class InnerAlgebra >
struct mpi_nested_algebra
{

// execute the InnerAlgebra on each node's local data.
#define BOOST_ODEINT_GEN_BODY(n) \
    InnerAlgebra::for_each##n( \
        BOOST_PP_ENUM_BINARY_PARAMS(n, s, () BOOST_PP_INTERCEPT) , \
        op \
    );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY


    template< class NestedState >
    static typename norm_result_type< typename NestedState::value_type >::type norm_inf( const NestedState &s )
    {
        typedef typename norm_result_type< typename NestedState::value_type >::type result_type;
        // local maximum
        result_type value = InnerAlgebra::norm_inf( s() );
        // global maximum
        return boost::mpi::all_reduce(s.world, value, boost::mpi::maximum<result_type>());
    }

};


}
}
}

#endif

/* mpi_nested_algebra.hpp
l6O5biga2+RfJwcsbtaVea0cML3paWAV2o4AlhjC0pvyYHs4sFwca4yMV+bANjAsp20wYGmnYJ7HVzuwDKpLsCq9VgZY2DHPyoPVa178sFkOLGJgMyGrPSGrHwtZzUd62JvPm/mGHu8onW0Z4qdovPuZt74rdS20JoLlIb+8QnrCyrIK9aAM7UvOJV/wF377u6o/42AYhtw3cDWq+cwI7azr8EuqQ0NemYRQLm6rjR/aoEnxq+c/j1PIROPPb4TP8JLlN/4W71meq+lcLxs5Yk0Af8+GXICrfDiIcSScPzBt4PPvD5TrvDrPq5p3bp/XLR5OQb7jyHfBb8M54b5h+TgunjOeTYRB+QvhvWnRRLq37/5zBxc03yLcvxGumbea8nOGttQprSFvl3PZOZaBLvsfRO+fRef9a/GhYH1TsDt3lgCvvVQF+/ljKtjPH1th7fNXmEf6+eMrDO5uFcX2PlMbI5nDXR7ohcufKMqfJMrf3Sp/D+fdKn9PKr+sopgccnFaI3R5YIDgY7LgYy/BR7nFR0UFHouPSuKjinDdvX+TPhRLbMgO+ueJeuZo9iT0HFr7c55dK1MDzsqt3idC8tiaCumLOvfZWTXyQFynxYV1wjmKnnCGPzd7AAoKKDuYv8SyHXlOEfJ8r5Dn3pY896nAY8lzKsnzfRUj6rezfsfVYIDnA+9b4e/H9RX+vbL9qKzpbtsV02GslsbSvj4VSJBlz+Cy8ZvlMdPi6f3E0wEVhqdZxNOBBq9YW5jbJrktGCT4OGhkOeq7vlmQAkLjwsEVbGOnFKXnXOobiacGYx49H4TWueYLeRxC9FZTv5mj5RBxPKRENsR9ZS7g45VmLJ4dNHsw8yr0HnwiEuI+1ABYmTIlmn1h048Olf2I2tTJSSVxmwYS/OP/HEuHDqP2WlhMh4ycV8NhXbou1NXY3biKxR1I4LZbxLqC3yyzIy0d+gDxdATp0FHE09FF2srokBawp0EMYB6O4bLwm3lotHhoIh6WEA/NxEOLyH+QyL/Uyr+M8s+h/MspfxvhmTxsS1ZatqS9Ao9lS1YRjQ7CbSiks/oWbtZY887630X5m4rqvGUdAmAj09t948Mmby7COg7lMx3Q0nGHJ4of0zoejUlYVuu1w7Z/zElB+asduO4jjDtFwwbSMepf3aA5VfSbIyleqqdC+oApE5sWEuKSIKpjfpu1xVH1oWRyYy7l5hUgqXN9lm6stvrcGmrXtYQ3u2B5siBuz+OYPn6zTp5glXsilXs86eRJVG7I7esjjpPZcP8Q969gAo+ZYcFHv9DziKXnUbxHLT2PEV8Doq80ChqDFo043uMWjZOJxkZBI2zJY9hqhwTlSVp4R1h4pxBeWtCebOXJWnlylGcT42E8ZxltEfXbatVvWwUeq36nEr3TuC8X9Stg+tOejgfArKunW/U4w6rHmVTuWTyeF/cxonnciyjr7jnF+PfGtU2xoWSKSQXAzP+5RK97RL7CiWiAcJF04ve8EuptroFmmgxjOheUVG99lS+zFwBzvS8iejeQPTZx0qlsGumu3VXCN9+u352amvcP6XevwkrvR3s4KAviYImbPBfqdFMz1z5frGHEItExY2gyC1Os92RhhydcUlFarO4A6mPmFq4t8uYWyB+cj2BdRi8/mHczrmTDkUHDs/HHysWc5VK8V6so+DJ7e5eJ8WFKkfleQ+H+hrBKN4t4d/e3rf61w+pfH6H+9dGivo62/9l0jrWMIVzWlYaGt359Fd4d25/1zc/HqaupzGsI/2TfmK6JKp7vDXjx19fqsVxfV2iKVjxGlymnGeVYjpv8DlHemmK1896gEBNu5H6dlHuJ9VOWLD9myfIGqtc=
*/