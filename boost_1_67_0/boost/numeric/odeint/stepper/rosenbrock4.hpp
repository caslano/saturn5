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