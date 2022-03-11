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