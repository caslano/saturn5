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
TZuPA0Qu6NCTEEtMfnbYcEXFDVJt/WnHJtAv5Pnf4OCkyzcsXRNkT9fOszpWMtgRmwATrr5rJpfFYaGuvQTB3HRPXwIxEnA3n5g4hykjigE+zCC33fl2XmNVciSKohUPPAgztc2OL0ZE7LR6bMFlwIHTB55pnYmKylTZoY+trRMCSRtcYJsLxL8NkOH86kor793X8GlaeOvrNv7hSL5FjvjQyBxx5lrNJe/fWx2H7MMYQ4kzU1tV52pYK254Fhg3IhUJnKv/gfo9ZoiG1RwTVPuicbZYDkDjSalrJKPDQayAyCzM0IyQpNl0nr9tYsT/xfmeBL89FdgiJpQzjklEDqdJv6SYglfycyrMKeOuPfZJB7wOp+BwOFVBPCHQCKBvvQSiWpX2FqAYRFGAZ/28cM+2ZE+rlyC0DwGbIct0XRRYVswdeFnBXQsA2ZJ6dYr+N7w8lGKwut7idRyyl6KwNuEI6F6HIl9J/O2eGHirWY2gm/yPcjBCPa0rakEVNfr17SezWRvQHd4IB7iMgUBiPOkAM9LkJx+WfhFkJjz/4zoBfPxi15THks5pOg==
*/