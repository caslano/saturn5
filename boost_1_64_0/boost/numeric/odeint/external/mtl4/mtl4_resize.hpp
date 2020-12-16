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
Q1HxqPn+NOHNCvZ76AQ6vWiH+USrDxdBuLAFbj4H+Abb2EUFbOxRZIMW0neK1wpZLicbiX7N1pEAo4m37mxa0dpsQrbyJXj957gafxzD8TX8DSDzbmIY7PtvJymIL5xRbEchJyi7e59/Od1t4drEE0Qdq3Udzcm9cM7bAbCBRdYGscqFsWLYzcmvXr1Osmy/ibGPJWCvYxlfjM0wYuwG4u75kRDyTVL9W2HSjf6Ys5DhRDIRclrNzVfOMCfq2YufWy/rWcJ3XlcQf+frddLssLAPKCObzIaHTJma3rZYOhlKJTPiO4gGFklkEXtB+5X9cvxBrMTqhaGe3kajDN4bStex70XuOKbYPT77THf1csxKRn+v3T3fHxXllo/yW3Qj6rR3opB0Opjgtf0Atf3cIjHfGzSv4UxbNBjvPVjz7mJX4jp/zrv77uQa65y+d+2MP3wxmEIxPShnLOiSzWzvw/1bHa1qpwMb48GcvwY21oMhzkj7URP1Hq3D5xB4MamdnSv7ukK967r0fsOaBTYUBUMXLkTZrs1VQZtL/ij8S4qqde6UkzawOmADTQzUFMsmZ7WumnFPwuq9+6D5e0YJIc8ZJX4v5UNF4rSMHUgmhraaeyQ8fdew5kbZJ8o0LJMcjvEYzf01njA3Ehm5e/1W59GX2kLPTR1Sog5TdsGnyrtnvstjh7zbrbmxeTlf+hZMYBubqSlpX4tZN103CCcfMVeUno7Aw34kVt0akafHZdGGs8+5uaakc11WtK4mWijRq/vWEeaE3JMz+bp3Rsrx1GK0RjFWOrQ+SLQeJz83rfVMY5rvY5CftDzo68I/Dfq66/P4uk4McVTRkU9xJ/igA0uFs4P6HBDDhzQ8Qil8TjMFuHF/GZZ1YBtzmTAMvQvb4sC2GCDoerinOfBEBpXjeMszVcb43OSDbxc+eBbv59PdU6FIODJI9noT4Bc7/jW8c9c+XQ7/JivuP9gCnI+qRMQtfxver3buMDv08MPx8ZNolOzGaYBfz/AMyvZ875ss3/t0wB5SaEARJ/uo8bN1rHgt7MQZwk58rsA3gRfyNzN5fiu/mYl3tmns7yym2J2zRBllo1jP6ChtLkfRPppOoURPf8+p8cckbde8pWLp4Xg2G4si2DCbjkEVTZqJgYsM5aKcxN9fOVeOu6O0H0t99yAFv0k9XnxbNefeh+87G2gU2z0XeJ70jUbwX4+Ucx/2q7Vejg+uB6FsMy7L85wXyDYd5RqA/1s3CS+ulP3CBMWV8p1LF0lZF5zbFYlRHsU6ievTX6LLdFN5DjjVsm3gGX5C0LbNCto2czcLz3W1T3+pqNv84nfcjvRdyeARIk2jSLqjiyOOMaX5kTo+o8Z/b9UO8oOxeKD0u5nvRePiHruPyLYdxdjWVODbxMFvEfnXYsweXQqKb+LJkX3CFSX65G69hmv8PvmVOj/dt0T1ukrWq8Rvcen9Fm+vg//mrP2Wa2hd/Fprz6q+wpwlmW7tT1zv4iON8fm+9xuQLvFvrPHjZFUQ52YL57WKIM6tFg7qE8C5TewzvA/p2fH+fYhPEO/zKOZI4t6JNIl7l3lHPelul/IR1wQ7u7Aa39MegoHG4KMbpkCa+81Za1/luxRjfG+NKfM+3oeCLup6B9sQ2vKAkE0dyThnnbF6kOr+EJWp9SNIF3unfv14xOLB6FGQh0eZB6Zp6c5jYh8KdfTtQ32uhusuv3FxudjP3N867/1h5+92EaNUbp4vIU9qvJ+/J8S+4v6K+KO/OwJ7sxPUl0leX+HyoTesC3IdF393Gl1iHZdxVN8gWt+09l/hBwHf+qYo4d5r4X4X769Z+2pP1fBdXUjT5V5Xw/UKtudE9Qw=
*/