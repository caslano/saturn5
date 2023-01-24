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
lWAqHhoGnjvQ0wk8EeAZg542eQOntXJFmEpxxEbSrZz2lF14uyZu/Ev7lcycwrKCztgu9FxBpPtkfdtDEIEvkCiZ2fylwuk6T1FxVNlJXeHBgjx8pHxx0nZ3rWHBBGW7d0Kk+4fatEOLb8MNnNw9hcdcESm7/HH4/gPQyPnT6Wllswakm96rEt11v8xJFL23x4nS6CjshVikso74NJB3lOIRo0VPaqUF90z44w9aQ2HDwpiEPJVetXu4fU2AnZT+VJrBIV1wJNUSKZ22STNr7PhkSjnR7UHA7Dd/u/TcaiTRbUOwO2R6NCxpnzXtc9Njz+Py2tutX+Ex08rHqdc60l3I0tCzSSNrkyraVsHwJqXMVtoH6piRVj8nYqR38CBH7o50b3THwt/wRNAuZ0e8Sr0NngCKhVL8nVIOyleCQ74FfiqFjkha11PxrdKyzy7uTQ9We7Jr8B03eqgtdw+xduQC+qNtbMg/N121HW9k115nWXVKlFpLD9eABF14rGC0ZD3LjIVsSVZA39a2jOG/X77YHks3WVZeB4wgEpG4Rjf+IkwiORLJKhIqAnHTA3lO8Nvh/E14dq92a1PxKQ2XcYCL3QtLsIaYHGCY5Hmue5hj0rcRJvQKPEcnz+a5gT8JzxF69AHtffqmaMJmKj4jnaY3Ds3RRkFOhIa3fspMqA5bJQVpMMsm7QTZJCLPHl6Jt53bTcWfo5VcK4Fv
*/