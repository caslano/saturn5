/*
 [auto_generated]
 boost/numeric/odeint/external/mtl4/mtl4_algebra_dispatcher.hpp

 [begin_description]
 specialization of the algebra dispatcher for mtl4
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/mtl/mtl.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::dense_vector< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::dense2D< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value , size_t BitMask , typename Parameters>
struct algebra_dispatcher< mtl::morton_dense< Value , BitMask, Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

template<typename Value, typename Parameters>
struct algebra_dispatcher< mtl::compressed2D< Value , Parameters > >
{
    typedef vector_space_algebra algebra_type;
};

// specialization of infinity norm calculation

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::dense_vector< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::dense_vector< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::dense2D< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::dense2D< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value , size_t BitMask , typename Parameters>
struct vector_space_norm_inf< mtl::morton_dense< Value , BitMask , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::morton_dense< Value , BitMask , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

template<typename Value, typename Parameters>
struct vector_space_norm_inf< mtl::compressed2D< Value , Parameters > >
{
    typedef Value result_type;
    Value operator()( const mtl::compressed2D< Value , Parameters > &x ) const
    {
        return mtl::infinity_norm(x);
    }
};

}
}
}

#endif // BOOST_NUMERIC_ODEINT_MTL4_MTL4_ALGEBRA_DISPATCHER_INCLUDED

/* mtl4_algebra_dispatcher.hpp
0vSDMlLyTDOM5SgNuquUP02Ljd2xWh5jbwDo7c28/wKw01j3JfBaanFAYYsRaereSLKjdf8KLLC8JGOCIOQNNN6zuVZxFYi5MU+DA+14EITvXjow0w4i090lbcMwmTXONc6RtN1UbO1AB2LCq8HZSvRGL3F4o3eLng4J+P5EnDQy2pFWPqsNyFnh5TC/zQIJf3ui/3voPzzNgu3knpcgLERXG6DLVgDDiEzjKlgbrToi92yDvA/fyF1+zBUpPmru/WUE15io7dj1S2STR5wRyw+6ouU7Eohnjk7gJBakw3EPOfdFhAD85ggQ53bIGh84PIR2sRAsv8HLEk02GO7bA/Uy8lZc2J0/3LXs/GGlilGuDxhwwNiVjmBme+Q5baiPcG0gK60ZV/uF5SW6LyrOVvJ8CN0r/zcG9/JRnysSvxaBYY/l3Do1QzrNnifYaakCEr+QbnqvVgyvEz0FdPZL2YODZiZm3VlMqsd5GKSg/elo/Wbu9rIgKAf9X+/EGx1Rd0w38lUE3aOChyz5/nEmlVXjQGVvXcoxtgWY9p2zc3qSghnPZBkr5s9egsooFf5v/QIuZzL5ciaZryADzidCATPjRT4BqeUkZ6jGcryc7OMrsw+nQ0k9qARYepjveQlRF8OpRplQGGKT6D/KqsIsS5xkE5HMitTaHtdG7jV8S2vQs6i8nU7eqtLWEQLbgxeVXkueZvqGKGzkLZ0E
*/