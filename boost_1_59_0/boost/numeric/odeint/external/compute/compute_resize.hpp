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
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
*/