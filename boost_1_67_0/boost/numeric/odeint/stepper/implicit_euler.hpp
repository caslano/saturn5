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