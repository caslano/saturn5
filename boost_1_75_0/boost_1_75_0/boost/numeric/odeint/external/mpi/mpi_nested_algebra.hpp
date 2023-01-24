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
YzYwa6XiCsA7HSR1PLZfJ1fkXFJwPk904J3XKHCqQzVK9l0tCCBjwxgTy2H6TmVPwaA+wuGxQK6imqmIFjne/HjK87Q8g+eZjN1Noqy1ZAqR3FfsSCTk/VRw3qKad7BtC84fuA+NU30kUb6/j+jpIvcXaAHRFdjgvb4I0hdIXzHJJxGzPKxaCQQarvC8FyTEZjU4H1vv0c7Hiu4higxzramw2KDtEgWI42QUgKZFZ3BE1yJv3EwXwpT+B6+HSzloLaEjH3RTW85VOHPugTn0G1gNlE7RIuhafy9dwHvtezone9XAXt9OJEVLzJ/FmPFSKojY5DmQmmDqXGnj3DpZZFNcPD20rWQmM4R68WjazfcaLXIEraExt1iWIpzNvb1lNvcu/53JqJAqHIJgfmHJ6AJvKeaPX3Cmw6x++4WyeiggqxKW5piW5ghLMyEgzdMsTbGW5hOWZriWpsAJ8S+zeIh44xfEIptiJrCq4OqYDQH95e7AgOSAQYKrGHYmOMLEbMzi2ckrmG/ng5T8w6QKvoj/m5yR4QblTBy40v8646xjHNr9eKr1gPz8ZbyaGXDG+XnLz1ibr9miNDmIKhlBavYyIGynss1mqHzaHtOa7Wiz485NFTS7mcC0OUEYe435m1EUDAfXCnINi6ochsIUNEJMt98i1MWHuwK+HxWiILbuYjfPlIoo7LVvpy6aCAd8XH7/Cu1kcg6iBAMj
*/