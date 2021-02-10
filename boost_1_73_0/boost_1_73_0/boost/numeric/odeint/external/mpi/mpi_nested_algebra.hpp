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
2BsNXVVPzKPvpB0nnSjB6Ocq8xLhig5wFozjkLY+LZXHs+HD92WhLLW0+A5K2QpzA4S69J8LaFsBq6+1PEraqj92/i4Cui9hx9CvY02WunBvVlmR+rAe83pk3n9xxmfemDZG4JqGb7QIkSAigXvkw/1aCrKkKRPIx19QqfBu5JOpthI9Ya4aYXTHImUjGfHnkUu1WqLtkcXPdofT+6/mvVO2o+oqVTPBjEnrphB+HYy+dAZhZzDwnBfBUIzzZdZWnq5N3hlZ/KD8jYdBS//veM13pYxOpiE9fODa2//DmYkZH3V6x6fD7rQ/GvrrI+VN4b3OtOPD7noDvh51Nu5Pj7azulG9DeDtecPulPlhk/s8Gna+DI7K8NV8NyD0T36u9MJx/zRBlKLIiny9dv9kzA/rj2VaI4V59M4i/QdQSwMECgAAAAgALWdKUuXbzzkEAwAApAYAACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE5MTYuY1VUBQABtkgkYK1TXW8bNxB816+YKAggCQdfnJeiUVpU/kiqRLUMSUFgwABBHfd8LCjyQPJsC7X/e5anU9Q0KZyH0LDIW+7MLGfJfPTzRg8jPDlE+y948NwiLr37m4r4/WwhHrD7Y9Q1z0+J5DhA
*/