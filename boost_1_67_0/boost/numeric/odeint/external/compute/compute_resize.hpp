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