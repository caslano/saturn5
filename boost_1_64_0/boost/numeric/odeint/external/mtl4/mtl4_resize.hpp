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
dPVNcHOLWWlLtwavx3D5eQic1rSGAqb3LiA6upxafdQIhjy5qq+ny+6GQoWComIiLfeMAKMY1Bi5z3gy6rD1000iOirbyWXPlOBRN4xaj+nQlzQy4DUJj5xn71XR+7A/vkZ/QfiVzvfsnDEBAPyvzVxYdQIlDE0kE2Kjy90Yb52cwfqjSQHcarx56e17EUHd/UGnvme2/LqRbcfdFxgu/0ahfUknyIJrLHEFykzpH1mFnGTkfHAoMnxBCc/Qcbl4t83nUydHLqa1lw53Wl3tYMUvSl8VEvxHJ9GjoqzdbDwbdtCJeWlR6bKoMuyAZ5JBnjaHE6xCBo4Aw9Cr98LIrIld5hnhmX5n188jJLD2LVsrs5kX/g5/O+2gnz1MZgQtVNaWjUnodpHbqakbCPMPMDuBuPkM3aHEmjb7hpSlHDrVG+D7w7Obtt6R/vS1HvVmFhBvAhDFonjivWRN5UbzZJqMbTnKuF21Iz2r9x51heXG6adZpYzIjzI8ssDVuHhsLEBNsbSBzm8l2DpUoCQDPNK6nQ1yYK3l5iCkCrz0FWk74mVeG+8jLLgMdA==
*/