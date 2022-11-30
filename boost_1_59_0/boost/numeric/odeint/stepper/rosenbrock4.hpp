/*
 [auto_generated]
 boost/numeric/odeint/stepper/rosenbrock4.hpp

 [begin_description]
 Implementation of the Rosenbrock 4 method for solving stiff ODEs. Note, that a
 controller and a dense-output stepper exist for this method,
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

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


/*
 * ToDo:
 *
 * 2. Interfacing for odeint, check if controlled_error_stepper can be used
 * 3. dense output
 */



template< class Value >
struct default_rosenbrock_coefficients
{
    typedef Value value_type;
    typedef unsigned short order_type;

    default_rosenbrock_coefficients( void )
    : gamma ( static_cast< value_type >( 0.25 ) ) ,
      d1 ( static_cast< value_type >( 0.25 ) ) ,
      d2 ( static_cast< value_type >( -0.1043 ) ) ,
      d3 ( static_cast< value_type >( 0.1035 ) ) ,
      d4 ( static_cast< value_type >( 0.3620000000000023e-01 ) ) ,
      c2 ( static_cast< value_type >( 0.386 ) ) ,
      c3 ( static_cast< value_type >( 0.21 ) ) ,
      c4 ( static_cast< value_type >( 0.63 ) ) ,
      c21 ( static_cast< value_type >( -0.5668800000000000e+01 ) ) ,
      a21 ( static_cast< value_type >( 0.1544000000000000e+01 ) ) ,
      c31 ( static_cast< value_type >( -0.2430093356833875e+01 ) ) ,
      c32 ( static_cast< value_type >( -0.2063599157091915e+00 ) ) ,
      a31 ( static_cast< value_type >( 0.9466785280815826e+00 ) ) ,
      a32 ( static_cast< value_type >( 0.2557011698983284e+00 ) ) ,
      c41 ( static_cast< value_type >( -0.1073529058151375e+00 ) ) ,
      c42 ( static_cast< value_type >( -0.9594562251023355e+01 ) ) ,
      c43 ( static_cast< value_type >( -0.2047028614809616e+02 ) ) ,
      a41 ( static_cast< value_type >( 0.3314825187068521e+01 ) ) ,
      a42 ( static_cast< value_type >( 0.2896124015972201e+01 ) ) ,
      a43 ( static_cast< value_type >( 0.9986419139977817e+00 ) ) ,
      c51 ( static_cast< value_type >( 0.7496443313967647e+01 ) ) ,
      c52 ( static_cast< value_type >( -0.1024680431464352e+02 ) ) ,
      c53 ( static_cast< value_type >( -0.3399990352819905e+02 ) ) ,
      c54 ( static_cast< value_type >(  0.1170890893206160e+02 ) ) ,
      a51 ( static_cast< value_type >( 0.1221224509226641e+01 ) ) ,
      a52 ( static_cast< value_type >( 0.6019134481288629e+01 ) ) ,
      a53 ( static_cast< value_type >( 0.1253708332932087e+02 ) ) ,
      a54 ( static_cast< value_type >( -0.6878860361058950e+00 ) ) ,
      c61 ( static_cast< value_type >( 0.8083246795921522e+01 ) ) ,
      c62 ( static_cast< value_type >( -0.7981132988064893e+01 ) ) ,
      c63 ( static_cast< value_type >( -0.3152159432874371e+02 ) ) ,
      c64 ( static_cast< value_type >( 0.1631930543123136e+02 ) ) ,
      c65 ( static_cast< value_type >( -0.6058818238834054e+01 ) ) ,
      d21 ( static_cast< value_type >( 0.1012623508344586e+02 ) ) ,
      d22 ( static_cast< value_type >( -0.7487995877610167e+01 ) ) ,
      d23 ( static_cast< value_type >( -0.3480091861555747e+02 ) ) ,
      d24 ( static_cast< value_type >( -0.7992771707568823e+01 ) ) ,
      d25 ( static_cast< value_type >( 0.1025137723295662e+01 ) ) ,
      d31 ( static_cast< value_type >( -0.6762803392801253e+00 ) ) ,
      d32 ( static_cast< value_type >( 0.6087714651680015e+01 ) ) ,
      d33 ( static_cast< value_type >( 0.1643084320892478e+02 ) ) ,
      d34 ( static_cast< value_type >( 0.2476722511418386e+02 ) ) ,
      d35 ( static_cast< value_type >( -0.6594389125716872e+01 ) )
    {}

    const value_type gamma;
    const value_type d1 , d2 , d3 , d4;
    const value_type c2 , c3 , c4;
    const value_type c21 ;
    const value_type a21;
    const value_type c31 , c32;
    const value_type a31 , a32;
    const value_type c41 , c42 , c43;
    const value_type a41 , a42 , a43;
    const value_type c51 , c52 , c53 , c54;
    const value_type a51 , a52 , a53 , a54;
    const value_type c61 , c62 , c63 , c64 , c65;
    const value_type d21 , d22 , d23 , d24 , d25;
    const value_type d31 , d32 , d33 , d34 , d35;

    static const order_type stepper_order = 4;
    static const order_type error_order = 3;
};



template< class Value , class Coefficients = default_rosenbrock_coefficients< Value > , class Resizer = initially_resizer >
class rosenbrock4
{
private:

public:

    typedef Value value_type;
    typedef boost::numeric::ublas::vector< value_type > state_type;
    typedef state_type deriv_type;
    typedef value_type time_type;
    typedef boost::numeric::ublas::matrix< value_type > matrix_type;
    typedef boost::numeric::ublas::permutation_matrix< size_t > pmatrix_type;
    typedef Resizer resizer_type;
    typedef Coefficients rosenbrock_coefficients;
    typedef stepper_tag stepper_category;
    typedef unsigned short order_type;

    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef state_wrapper< matrix_type > wrapped_matrix_type;
    typedef state_wrapper< pmatrix_type > wrapped_pmatrix_type;

    typedef rosenbrock4< Value , Coefficients , Resizer > stepper_type;

    const static order_type stepper_order = rosenbrock_coefficients::stepper_order;
    const static order_type error_order = rosenbrock_coefficients::error_order;

    rosenbrock4( void )
    : m_resizer() , m_x_err_resizer() ,
      m_jac() , m_pm() ,
      m_dfdt() , m_dxdt() , m_dxdtnew() ,
      m_g1() , m_g2() , m_g3() , m_g4() , m_g5() ,
      m_cont3() , m_cont4() , m_xtmp() , m_x_err() ,
      m_coef()
    { }


    order_type order() const { return stepper_order; } 

    template< class System >
    void do_step( System system , const state_type &x , time_type t , state_type &xout , time_type dt , state_type &xerr )
    {
        // get the system and jacobi function
        typedef typename odeint::unwrap_reference< System >::type system_type;
        typedef typename odeint::unwrap_reference< typename system_type::first_type >::type deriv_func_type;
        typedef typename odeint::unwrap_reference< typename system_type::second_type >::type jacobi_func_type;
        system_type &sys = system;
        deriv_func_type &deriv_func = sys.first;
        jacobi_func_type &jacobi_func = sys.second;

        const size_t n = x.size();

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<state_type> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i<n ; ++i )
            m_pm.m_v( i ) = i;

        deriv_func( x , m_dxdt.m_v , t );
        jacobi_func( x , m_jac.m_v , t , m_dfdt.m_v );

        m_jac.m_v *= -1.0;
        m_jac.m_v += 1.0 / m_coef.gamma / dt * boost::numeric::ublas::identity_matrix< value_type >( n );
        boost::numeric::ublas::lu_factorize( m_jac.m_v , m_pm.m_v );

        for( size_t i=0 ; i<n ; ++i )
            m_g1.m_v[i] = m_dxdt.m_v[i] + dt * m_coef.d1 * m_dfdt.m_v[i];
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g1.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a21 * m_g1.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c2 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g2.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d2 * m_dfdt.m_v[i] + m_coef.c21 * m_g1.m_v[i] / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g2.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a31 * m_g1.m_v[i] + m_coef.a32 * m_g2.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c3 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g3.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d3 * m_dfdt.m_v[i] + ( m_coef.c31 * m_g1.m_v[i] + m_coef.c32 * m_g2.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g3.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a41 * m_g1.m_v[i] + m_coef.a42 * m_g2.m_v[i] + m_coef.a43 * m_g3.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + m_coef.c4 * dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g4.m_v[i] = m_dxdtnew.m_v[i] + dt * m_coef.d4 * m_dfdt.m_v[i] + ( m_coef.c41 * m_g1.m_v[i] + m_coef.c42 * m_g2.m_v[i] + m_coef.c43 * m_g3.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g4.m_v );


        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] = x[i] + m_coef.a51 * m_g1.m_v[i] + m_coef.a52 * m_g2.m_v[i] + m_coef.a53 * m_g3.m_v[i] + m_coef.a54 * m_g4.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + dt );
        for( size_t i=0 ; i<n ; ++i )
            m_g5.m_v[i] = m_dxdtnew.m_v[i] + ( m_coef.c51 * m_g1.m_v[i] + m_coef.c52 * m_g2.m_v[i] + m_coef.c53 * m_g3.m_v[i] + m_coef.c54 * m_g4.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , m_g5.m_v );

        for( size_t i=0 ; i<n ; ++i )
            m_xtmp.m_v[i] += m_g5.m_v[i];
        deriv_func( m_xtmp.m_v , m_dxdtnew.m_v , t + dt );
        for( size_t i=0 ; i<n ; ++i )
            xerr[i] = m_dxdtnew.m_v[i] + ( m_coef.c61 * m_g1.m_v[i] + m_coef.c62 * m_g2.m_v[i] + m_coef.c63 * m_g3.m_v[i] + m_coef.c64 * m_g4.m_v[i] + m_coef.c65 * m_g5.m_v[i] ) / dt;
        boost::numeric::ublas::lu_substitute( m_jac.m_v , m_pm.m_v , xerr );

        for( size_t i=0 ; i<n ; ++i )
            xout[i] = m_xtmp.m_v[i] + xerr[i];
    }

    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt , state_type &xerr )
    {
        do_step( system , x , t , x , dt , xerr );
    }

    /*
     * do_step without error output - just calls above functions with and neglects the error estimate
     */
    template< class System >
    void do_step( System system , const state_type &x , time_type t , state_type &xout , time_type dt )
    {
        m_x_err_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_x_err<state_type> , detail::ref( *this ) , detail::_1 ) );
        do_step( system , x , t , xout , dt , m_x_err.m_v );
    }

    template< class System >
    void do_step( System system , state_type &x , time_type t , time_type dt )
    {
        m_x_err_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_x_err<state_type> , detail::ref( *this ) , detail::_1 ) );
        do_step( system , x , t , dt , m_x_err.m_v );
    }

    void prepare_dense_output()
    {
        const size_t n = m_g1.m_v.size();
        for( size_t i=0 ; i<n ; ++i )
        {
            m_cont3.m_v[i] = m_coef.d21 * m_g1.m_v[i] + m_coef.d22 * m_g2.m_v[i] + m_coef.d23 * m_g3.m_v[i] + m_coef.d24 * m_g4.m_v[i] + m_coef.d25 * m_g5.m_v[i];
            m_cont4.m_v[i] = m_coef.d31 * m_g1.m_v[i] + m_coef.d32 * m_g2.m_v[i] + m_coef.d33 * m_g3.m_v[i] + m_coef.d34 * m_g4.m_v[i] + m_coef.d35 * m_g5.m_v[i];
        }
    }


    void calc_state( time_type t , state_type &x ,
            const state_type &x_old , time_type t_old ,
            const state_type &x_new , time_type t_new )
    {
        const size_t n = m_g1.m_v.size();
        time_type dt = t_new - t_old;
        time_type s = ( t - t_old ) / dt;
        time_type s1 = 1.0 - s;
        for( size_t i=0 ; i<n ; ++i )
            x[i] = x_old[i] * s1 + s * ( x_new[i] + s1 * ( m_cont3.m_v[i] + s * m_cont4.m_v[i] ) );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
        resize_x_err( x );
    }


protected:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dfdt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdtnew , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_xtmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g2 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g3 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g4 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_g5 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_cont3 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_cont4 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_jac , x , typename is_resizeable<matrix_type>::type() );
        resized |= adjust_size_by_resizeability( m_pm , x , typename is_resizeable<pmatrix_type>::type() );
        return resized;
    }

    template< class StateIn >
    bool resize_x_err( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_x_err , x , typename is_resizeable<state_type>::type() );
    }

private:


    resizer_type m_resizer;
    resizer_type m_x_err_resizer;

    wrapped_matrix_type m_jac;
    wrapped_pmatrix_type m_pm;
    wrapped_deriv_type m_dfdt , m_dxdt , m_dxdtnew;
    wrapped_state_type m_g1 , m_g2 , m_g3 , m_g4 , m_g5;
    wrapped_state_type m_cont3 , m_cont4;
    wrapped_state_type m_xtmp;
    wrapped_state_type m_x_err;

    const rosenbrock_coefficients m_coef;
};


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_HPP_INCLUDED

/* rosenbrock4.hpp
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
*/