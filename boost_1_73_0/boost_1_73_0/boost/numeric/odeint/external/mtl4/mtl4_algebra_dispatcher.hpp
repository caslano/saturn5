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
c4xVGxHH/o4xd9eb6D9svKYx0bGQs/mtSSPHY1y5GnoPf1GJMecMxFJPII7cAL+yF7Fld+B2A/raR9yFj3EmHbH5oHYG3dQJdiRiZ+hVEN/3rQPG8N9/rzepCcbkrzE/uB1+9rtdiBF3mXTXIqIdvS16Cr7gHsRTF21F/IuY++wjMYbnQgaQ1VjE3/ciXi/8n0mfwQaX34H4G33Iaoxx6nnEj4gZP4BfWXCmSe3Qj1sxtzpiLnwK/Mga/D0Bvjw=
*/