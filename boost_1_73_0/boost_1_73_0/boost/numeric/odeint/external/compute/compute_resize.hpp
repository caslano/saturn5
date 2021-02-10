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
r/IdOl4lbry8pX0cP+fojmKjjwFp3sW0xRNUI81jXT4aMc8ddI67sPfmzWt4Bfu7+3sBnDAluIRrx9WMm3kAb1N/8lfOHh76lr8PgDtgst+YinJhwerMLZjhgHspEq4sT4FZSLlNjJjhF6HA5RwyITkcTy5vR+FZAItcJDkZedQV2FxXMoWc3XMwPOHivrZRMuNAZ6iOxlNhHRqsnNCqj745OG4KSzbIPZNWA7tnQrIZOmIOcudKezAYJJWRGP0g1YkdJMv0+7krVpncYhAFewRdOnAaKssDIMkACp2KjJ4ICB6W1UwKmwfraNCVSgfagOVSki3UE9zWYXO4buAJSAxKjFg4elitLLla5LrYEEQcyUpWGYWOEAcUSjXCHEClUm68sM986aLB1AP8ZGnW8aagFQYD7eE1jK7bMGNW2ABuRtH5ZBrBzfDqahhGtzD5AMPwlox9HIUnWHqBzgzwh9Jwi84NiKKUgqeNz9+3Bq0/hUpklXJoO26xVO3WT0fIAknH61NMVEkMbPO04EXKZ9Xcmxj0PG0K9iCKqgACRM1BcjV3OXKXKtM5nl6N44vhp3gUXk6jeHwankXnXUIQIRMKgVcMywzI70woDkq7mhSJfCRsNNEfmbjgSAgkb2VALxRQTo3Gz8bh9a5f
*/