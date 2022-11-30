/*
 [auto_generated]
 boost/numeric/odeint/stepper/implicit_euler.hpp

 [begin_description]
 Impementation of the implicit Euler method. Works with ublas::vector as state type.
 [end_description]

 Copyright 2010-2012 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED


#include <utility>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/util/ublas_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

namespace boost {
namespace numeric {
namespace odeint {








template< class ValueType , class Resizer = initially_resizer >
class implicit_euler
{

public:

    typedef ValueType value_type;
    typedef value_type time_type;
    typedef boost::numeric::ublas::vector< value_type > state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_type deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef boost::numeric::ublas::matrix< value_type > matrix_type;
    typedef state_wrapper< matrix_type > wrapped_matrix_type;
    typedef boost::numeric::ublas::permutation_matrix< size_t > pmatrix_type;
    typedef state_wrapper< pmatrix_type > wrapped_pmatrix_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;
    typedef implicit_euler< ValueType , Resizer > stepper_type;

    implicit_euler( value_type epsilon = 1E-6 )
    : m_epsilon( epsilon ) 
    { }


    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt )
    {
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<state_type> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i<x.size() ; ++i )
            m_pm.m_v[i] = i;

        t += dt;

        // apply first Newton step
        deriv_func( x , m_dxdt.m_v , t );

        m_b.m_v = dt * m_dxdt.m_v;

        jacobi_func( x , m_jacobi.m_v  , t );
        m_jacobi.m_v *= dt;
        m_jacobi.m_v -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

        solve( m_b.m_v , m_jacobi.m_v );

        m_x.m_v = x - m_b.m_v;

        // iterate Newton until some precision is reached
        // ToDo: maybe we should apply only one Newton step -> linear implicit one-step scheme
        while( boost::numeric::ublas::norm_2( m_b.m_v ) > m_epsilon )
        {
            deriv_func( m_x.m_v , m_dxdt.m_v , t );
            m_b.m_v = x - m_x.m_v + dt*m_dxdt.m_v;

            // simplified version, only the first Jacobian is used
            //            jacobi( m_x , m_jacobi , t );
            //            m_jacobi *= dt;
            //            m_jacobi -= boost::numeric::ublas::identity_matrix< value_type >( x.size() );

            solve( m_b.m_v , m_jacobi.m_v );

            m_x.m_v -= m_b.m_v;
        }
        x = m_x.m_v;
    }

    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }


private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_x , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_b , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_jacobi , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_pm , x , typename is_resizeable<pmatrix_type>::type() );
        return resized;
    }


    void solve( state_type &x , matrix_type &m )
    {
        int res = boost::numeric::ublas::lu_factorize( m , m_pm.m_v );
        if( res != 0 ) std::exit(0);
        boost::numeric::ublas::lu_substitute( m , m_pm.m_v , x );
    }

private:

    value_type m_epsilon;
    resizer_type m_resizer;
    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_x;
    wrapped_deriv_type m_b;
    wrapped_matrix_type m_jacobi;
    wrapped_pmatrix_type m_pm;


};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_IMPLICIT_EULER_HPP_INCLUDED

/* implicit_euler.hpp
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
*/