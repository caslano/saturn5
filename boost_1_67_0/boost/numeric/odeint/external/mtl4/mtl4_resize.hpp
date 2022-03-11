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
+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
*/