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
FmyUTcuu3zMNqe/8qmPaU0XnFoQQ6eCyMetO5cJ0vRn09Si/uWxPUZnggWDZSr+Tdy0u1I7jzyeB4h9JBJW9Ex1YynWgqq9+Jtf1P6SHTEjXt90xQFr4z51nKcWVjXBVEhxIWHR7CTBVO8cF5Rbg8RTkCEhw3HKD0jcBBNs+asVVhqdF689XasD3F8P8MVRm10vEtlzTcndEc+qt4r0YBDLopKMNwSAPv21NhHdoxTXvZMgSvrPb1OX9pyWMChkJRAbCf1mHtdgDRfPZcJsnBfUVFFj5Ezu5ivJFoV91bZj8C07rtIQMJUYSK5c4R/HmSj0bF0gZxXI2iTZYxq7QYqSgLPoMgCOjwFDAJPyjpRwcIHSDLo/lN33SziImH74WYn+RnDO9wceUtZbLH+eG1Kd/PZvn90PReyGUpiunNsGfG/JjxCjXwS/PnHbojdS3JiD634HoSbT67iuZZ0qAgShkL2pPvCz72RjZNZeJrrn4T20cst/iHeSPwiIOAtcl/aVz9iFbDuXvFhedAGSXLMF0O21/TBvF2b+T/aKUY/9wEt0qhYgFBq/TIg==
*/