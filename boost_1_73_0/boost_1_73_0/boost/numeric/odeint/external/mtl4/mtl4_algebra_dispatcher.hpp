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
0EtWMF31YM2NMBHcTNMPi+sUbpLlMpmnt7D4E5L5rQP7OJ1fkP+CyDTgptFoiFyDqBopMO84f16Lg19Enck2R+hZNGRVL3g2VWGV47q999OiJscoJsxKrmFwvZz1g78DgDGNYOD8H3VvmcrdFjNwBulklbLJcsk+JX8tluw8uXBBVKCWjrzLYYZctjDwzzOYX89mo4BCRBH6z/dSrblkohY2dNjscrY4T2Ysmc368OrM803Y4mMfnBaAotEktAiNJQd1BL0fUPpQ0P7F/K7u9Uc+R6OlPfCC1q9OjQMhdR4Ludl2SKOd0Fdu/r8FPEv6gf65wkwir9sm/N/KnCPMoKXz5AsW+YosrlL2ebI8X6wmEZzMPNrLkcnNiq2ml59/JbWbzaZ3JPzDJLmYLCN4cwyXugjcPnFhncEHzxlvGqzz0I2JeKxquhLt63Tb4CnQN7rnuLuG4i90go9qStOrvS4H2PebaLcHDwbQbVAoXflcF+HxupKf7n3u1BUakXEpww4OnuHsXepwXrQw+O4gKRkFX4NvUEsDBAoAAAAIAC1nSlLZMLBFPgMAAKUHAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxOTM0LmNVVAUAAbZIJGCtVF9v2zYQf9enuHov
*/