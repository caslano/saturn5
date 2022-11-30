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


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_IMPLICIT_EULER_MTL4_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_IMPLICIT_EULER_MTL4_HPP_INCLUDED


#include <utility>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/external/mtl4/mtl4_resize.hpp>

#include <boost/numeric/mtl/mtl.hpp>
#include <boost/numeric/itl/itl.hpp>




namespace boost {
namespace numeric {
namespace odeint {


template< class ValueType , class Resizer = initially_resizer >
class implicit_euler_mtl4
{

public:

    typedef ValueType value_type;
    typedef value_type time_type;
    typedef mtl::dense_vector<value_type> state_type;

    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_type deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef mtl::compressed2D< value_type > matrix_type;
    typedef state_wrapper< matrix_type > wrapped_matrix_type;

    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef implicit_euler_mtl4< ValueType , Resizer > stepper_type;


    implicit_euler_mtl4( const value_type epsilon = 1E-6 )
        : m_epsilon( epsilon ) , m_resizer() ,
          m_dxdt() , m_x() ,
          m_identity() , m_jacobi()
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

        m_resizer.adjust_size( x , detail::bind(
                                   &stepper_type::template resize_impl< state_type > , detail::ref( *this ) , detail::_1 ) );

        m_identity.m_v = 1;

        t += dt;
        m_x.m_v = x;

        deriv_func( x , m_dxdt.m_v , t );
        jacobi_func( x , m_jacobi.m_v , t );


        m_dxdt.m_v *= -dt;

        m_jacobi.m_v *= dt;
        m_jacobi.m_v -= m_identity.m_v ;



        // using ilu_0 preconditioning -incomplete LU factorisation
        // itl::pc::diagonal<matrix_type,double> L(m_jacobi.m_v);
        itl::pc::ilu_0<matrix_type> L( m_jacobi.m_v );

        solve( m_jacobi.m_v , m_x.m_v , m_dxdt.m_v , L );
        x+= m_x.m_v;


    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }


private:


    /*
      Applying approximate iterative linear solvers
      default solver is Biconjugate gradient stabilized method
      itl::bicgstab(A, x, b, L, iter);
    */
    template < class LinearOperator, class HilbertSpaceX, class HilbertSpaceB, class Preconditioner>
    void solve(const LinearOperator& A, HilbertSpaceX& x, const HilbertSpaceB& b,
               const Preconditioner& L, int max_iteractions =500)
    {
        // Termination criterion: r < 1e-6 * b or N iterations
        itl::basic_iteration< double > iter( b , max_iteractions , 1e-6 );
        itl::bicgstab( A , x , b , L , iter );

    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_x , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_identity , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_jacobi , x , typename is_resizeable<matrix_type>::type() );
        return resized;
    }


private:

    value_type m_epsilon;
    resizer_type m_resizer;
    wrapped_deriv_type m_dxdt;
    wrapped_state_type m_x;
    wrapped_matrix_type m_identity;
    wrapped_matrix_type m_jacobi;
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_IMPLICIT_EULER_MTL4_HPP_INCLUDED

/* implicit_euler_mtl4.hpp
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
*/