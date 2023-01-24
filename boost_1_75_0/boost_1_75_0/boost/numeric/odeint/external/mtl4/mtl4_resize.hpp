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
TDd4DWODZC2wry9Qw9uHgBp2kZ4W1R8e42p89oCOKbjLgFUZe6BfMs77gsaYH6/Ml0gDZPwDPq007oAQLLbS+OlBJuVUGndxV0kUcukHylByKccvKyMMYUHhUoxvFmbsiIhXA6HyMXvVQPjwMHA+WcGpE/qX0+gWTCu30gwteDUTeTWznqZqRuEGqVRF9dwOxcsP8wMViYD9W4dYPRN5PQceono+eYjqGX4Q6+Y7oNbthwNq3X470LhuP0EYnWL0dADZNaY3YpzBME6kfo3nJ1iPKGYfPo4pba3la1ng5ftBXlfMu55i42cAM61BZWY2PeXtkOiASLKDPb+UQzokVBVMxK2gVU+xBUY+O266l98Fr5Y2n6I/xNJSFDJYpB1IkBfu5OUN1MvLpydt9PLofayZweV1gc+USrcStuB9KnHyXfq8eFFRuBGIaluTIVlhitqdLh2Q8VEQXQ4nPO1SHF795P6h1iHtsp4TIhzSAeeVVskSlZGbGXH+sCP8gJhb5eh5ID23YqTUAZa9w2Jhyscb2M7ZDOEmZ1vTZoDu4zWO8CpHChSz6y7f3POK0vyZt3TpTkDoDA1OH6AFTYGv7nqHRcjTge1J9oiEvHOHCU971zLr+cO28DJb4bAI1DHtp4NQX8GMLH8WoS3rtEk4QFjmb0cydVI83v85E6hq64BXv7/+uSSUkipcTtE9NQ7NG+IU8zOrMTc7WobH
*/