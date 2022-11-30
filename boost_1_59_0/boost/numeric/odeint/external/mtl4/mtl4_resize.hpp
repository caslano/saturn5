/*
[begin_description]
Modification of the implicit Euler method, works with the MTL4 matrix library only. 
[end_description]

Copyright 2012-2013 Andreas Angelopoulos
Copyright 2012-2013 Karsten Ahnert
Copyright 2012-2013 Mario Mulansky

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or
copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MTL4_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MTL4_RESIZE_HPP_INCLUDED

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

#include <boost/numeric/mtl/vector/dense_vector.hpp>
#include <boost/numeric/mtl/matrix/dense2D.hpp>
#include <boost/numeric/mtl/matrix/compressed2D.hpp>


namespace boost {
namespace numeric {
namespace odeint {


template< class Value , class Parameters >
struct is_resizeable< mtl::dense_vector< Value , Parameters > >
{ 
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< class Value , class Parameters >
struct is_resizeable< mtl::dense2D< Value , Parameters > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};

template< class Value , class Parameters >
struct is_resizeable< mtl::compressed2D< Value , Parameters > >
{
    typedef boost::true_type type;
    const static bool value = type::value;
};




template< class Value , class Parameters >
struct same_size_impl< mtl::dense_vector< Value , Parameters > , mtl::dense_vector< Value , Parameters > >
{
    static bool same_size( const mtl::dense_vector< Value , Parameters > &v1 ,
                           const mtl::dense_vector< Value , Parameters > &v2 )
    {
        return mtl::size( v1 ) == mtl::size( v2 );
    }
};

template< class Value , class Parameters >
struct resize_impl< mtl::dense_vector< Value , Parameters > , mtl::dense_vector< Value , Parameters > >
{
    static void resize( mtl::dense_vector< Value , Parameters > &v1 ,
                        const mtl::dense_vector< Value , Parameters > &v2 )
    {
        v1.change_dim( mtl::size( v2 ) );
    }
};



template< class Value , class MatrixParameters , class VectorParameters >
struct same_size_impl< mtl::dense2D< Value , MatrixParameters > , mtl::dense_vector< Value , VectorParameters > >
{
    static bool same_size( const mtl::dense2D< Value , MatrixParameters > &m , 
                           const mtl::dense_vector< Value , VectorParameters > &v )
    {
        return ( ( mtl::size( v ) == m.num_cols() ) && ( mtl::size( v ) == m.num_rows() ) );
    }
};

template< class Value , class MatrixParameters , class VectorParameters >
struct resize_impl< mtl::dense2D< Value , MatrixParameters > , mtl::dense_vector< Value , VectorParameters > >
{
    static void resize( mtl::dense2D< Value , MatrixParameters > &m , 
                        const mtl::dense_vector< Value , VectorParameters > &v )
    {
        m.change_dim( mtl::size( v ) , mtl::size( v ) , false );
    }
};




template< class Value , class MatrixParameters , class VectorParameters >
struct same_size_impl< mtl::compressed2D< Value , MatrixParameters > , mtl::dense_vector< Value , VectorParameters > >
{
    static bool same_size( const mtl::compressed2D< Value , MatrixParameters > &m , 
                           const mtl::dense_vector< Value , VectorParameters > &v )
    {
        return ( ( mtl::size( v ) == m.num_cols() ) && ( mtl::size( v ) == m.num_rows() ) );
    }
};

template< class Value , class MatrixParameters , class VectorParameters >
struct resize_impl< mtl::compressed2D< Value , MatrixParameters > , mtl::dense_vector< Value , VectorParameters > >
{
    static void resize( mtl::compressed2D< Value , MatrixParameters > &m , 
                        const mtl::dense_vector< Value , VectorParameters > &v )
    {
        m.change_dim( mtl::size( v ) , mtl::size( v ) );
    }
};








} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_MTL4_RESIZE_HPP_INCLUDED

/* mtl4_resize.hpp
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
*/