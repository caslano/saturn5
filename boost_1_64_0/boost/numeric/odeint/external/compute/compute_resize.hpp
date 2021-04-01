/*
 [auto_generated]
 boost/numeric/odeint/external/compute/compute_resize.hpp

 [begin_description]
 Enable resizing for Boost.Compute vector
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class T, class A >
struct is_resizeable< boost::compute::vector< T , A > >
{
    struct type : public boost::true_type { };
    const static bool value = type::value;
};

template< class T, class A >
struct same_size_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static bool same_size( const boost::compute::vector< T, A > &x , const boost::compute::vector< T, A > &y )
    {
        return x.size() == y.size();
    }
};

template< class T, class A >
struct resize_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static void resize( boost::compute::vector< T, A > &x , const boost::compute::vector< T, A > &y )
    {
        x.resize( y.size() );
    }
};


template< class Container1, class T, class A >
struct copy_impl< Container1 , boost::compute::vector< T, A > >
{
    static void copy( const Container1 &from , boost::compute::vector< T, A > &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};

template< class T, class A, class Container2 >
struct copy_impl< boost::compute::vector< T, A > , Container2 >
{
    static void copy( const boost::compute::vector< T, A > &from , Container2 &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};

template< class T, class A >
struct copy_impl< boost::compute::vector< T, A > , boost::compute::vector< T, A > >
{
    static void copy( const boost::compute::vector< T, A > &from , boost::compute::vector< T, A > &to )
    {
        boost::compute::copy( boost::begin( from ) , boost::end( from ) , boost::begin( to ) );
    }
};




} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_RESIZE_HPP_DEFINED

/* compute_resize.hpp
W5AgvcXBc25rqh3w8KnXSYUmN8i4ZYWx2PXexrL/Ax2k0k1m0NICtkzOXM6VfdPMFQdc5hEetezpsFjsrP2nOgaRj/TuYSAA+AC+lpHFybMsh08EzMoIxPQYqP7qEkejSKccFg6ybJj4PybAYo0J9+/RqIg24NXGrXiQVxRao46E8lK+1JxxCoL6Az8og3kn9KKltgTE24cUoe5ro9NPDW25BE4nhLTBBfTtJ//3pQSSWH5HpGx1asiqflPJfpxL9N/PYAncpEDv2cYSjTktqQNNho4D3tdQ6G0rUHpLQP5//ApG0OJN1tM3qp/KBaB1teOBVXKPoTqVZF4itmUZ2dXHN5oEvTgmioq8D4cvDHfYrU5wHzawPZt/SwZqPH3M6uDuGhAnXUzMRpP5n1doT7TeiIEnEDwAnaDThgron5DzU1n7bugA3a5/wgRJAnxjmDPLoHvC5Mq1pxgFlrOyhYoGr4rqla27xafKnJczZ4dr9cDD7ksAR+notXrkCafeEfkegL2SjNLpYDo9Pogq88y8cr9tBUCtSz53z1QI6iii74CjOYDLfJtcXw==
*/