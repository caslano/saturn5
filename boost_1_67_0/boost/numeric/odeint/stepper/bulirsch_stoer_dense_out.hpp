/*
 [auto_generated]
 boost/numeric/odeint/stepper/bulirsch_stoer_dense_out.hpp

 [begin_description]
 Implementaiton of the Burlish-Stoer method with dense output
 [end_description]

 Copyright 2011-2015 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_DENSE_OUT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_DENSE_OUT_HPP_INCLUDED


#include <iostream>

#include <algorithm>

#include <boost/config.hpp> // for min/max guidelines

#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/math/special_functions/binomial.hpp>

#include <boost/numeric/odeint/stepper/controlled_runge_kutta.hpp>
#include <boost/numeric/odeint/stepper/modified_midpoint.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>

#include <boost/numeric/odeint/integrate/max_step_checker.hpp>

#include <boost/type_traits.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template<
    class State ,
    class Value = double ,
    class Deriv = State ,
    class Time = Value ,
    class Algebra = typename algebra_dispatcher< State >::algebra_type ,
    class Operations = typename operations_dispatcher< State >::operations_type ,
    class Resizer = initially_resizer
    >
class bulirsch_stoer_dense_out {


public:

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef dense_output_stepper_tag stepper_category;
#ifndef DOXYGEN_SKIP
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;

    typedef bulirsch_stoer_dense_out< State , Value , Deriv , Time , Algebra , Operations , Resizer > controlled_error_bs_type;

    typedef typename inverse_time< time_type >::type inv_time_type;

    typedef std::vector< value_type > value_vector;
    typedef std::vector< time_type > time_vector;
    typedef std::vector< inv_time_type > inv_time_vector;  //should be 1/time_type for boost.units
    typedef std::vector< value_vector > value_matrix;
    typedef std::vector< size_t > int_vector;
    typedef std::vector< wrapped_state_type > state_vector_type;
    typedef std::vector< wrapped_deriv_type > deriv_vector_type;
    typedef std::vector< deriv_vector_type > deriv_table_type;
#endif //DOXYGEN_SKIP

    const static size_t m_k_max = 8;



    bulirsch_stoer_dense_out(
        value_type eps_abs = 1E-6 , value_type eps_rel = 1E-6 ,
        value_type factor_x = 1.0 , value_type factor_dxdt = 1.0 ,
        time_type max_dt = static_cast<time_type>(0) ,
        bool control_interpolation = false )
        : m_error_checker( eps_abs , eps_rel , factor_x, factor_dxdt ) ,
          m_max_dt(max_dt) ,
          m_control_interpolation( control_interpolation) ,
          m_last_step_rejected( false ) , m_first( true ) ,
          m_current_state_x1( true ) ,
          m_error( m_k_max ) ,
          m_interval_sequence( m_k_max+1 ) ,
          m_coeff( m_k_max+1 ) ,
          m_cost( m_k_max+1 ) ,
          m_facmin_table( m_k_max+1 ) ,
          m_table( m_k_max ) ,
          m_mp_states( m_k_max+1 ) ,
          m_derivs( m_k_max+1 ) ,
          m_diffs( 2*m_k_max+2 ) ,
          STEPFAC1( 0.65 ) , STEPFAC2( 0.94 ) , STEPFAC3( 0.02 ) , STEPFAC4( 4.0 ) , KFAC1( 0.8 ) , KFAC2( 0.9 )
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();

        for( unsigned short i = 0; i < m_k_max+1; i++ )
        {
            /* only this specific sequence allows for dense output */
            m_interval_sequence[i] = 2 + 4*i;  // 2 6 10 14 ...
            m_derivs[i].resize( m_interval_sequence[i] );
            if( i == 0 )
            {
                m_cost[i] = m_interval_sequence[i];
            } else
            {
                m_cost[i] = m_cost[i-1] + m_interval_sequence[i];
            }
            m_facmin_table[i] = pow BOOST_PREVENT_MACRO_SUBSTITUTION( STEPFAC3 , static_cast< value_type >(1) / static_cast< value_type >( 2*i+1 ) );
            m_coeff[i].resize(i);
            for( size_t k = 0 ; k < i ; ++k  )
            {
                const value_type r = static_cast< value_type >( m_interval_sequence[i] ) / static_cast< value_type >( m_interval_sequence[k] );
                m_coeff[i][k] = 1.0 / ( r*r - static_cast< value_type >( 1.0 ) ); // coefficients for extrapolation
            }
            // crude estimate of optimal order

            m_current_k_opt = 4;
            /* no calculation because log10 might not exist for value_type!
            const value_type logfact( -log10( max BOOST_PREVENT_MACRO_SUBSTITUTION( eps_rel , static_cast< value_type >( 1.0E-12 ) ) ) * 0.6 + 0.5 );
            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 1 , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>( m_k_max-1 ) , static_cast<int>( logfact ) ));
            */
        }
        int num = 1;
        for( int i = 2*(m_k_max)+1 ; i >=0  ; i-- )
        {
            m_diffs[i].resize( num );
            num += (i+1)%2;
        }
    }

    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut >
    controlled_step_result try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , DerivOut &dxdt_new , time_type &dt )
    {
        if( m_max_dt != static_cast<time_type>(0) && detail::less_with_sign(m_max_dt, dt, dt) )
        {
            // given step size is bigger then max_dt
            // set limit and return fail
            dt = m_max_dt;
            return fail;
        }

        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;
        
        static const value_type val1( 1.0 );

        bool reject( true );

        time_vector h_opt( m_k_max+1 );
        inv_time_vector work( m_k_max+1 );

        m_k_final = 0;
        time_type new_h = dt;

        //std::cout << "t=" << t <<", dt=" << dt << ", k_opt=" << m_current_k_opt << ", first: " << m_first << std::endl;

        for( size_t k = 0 ; k <= m_current_k_opt+1 ; k++ )
        {
            m_midpoint.set_steps( m_interval_sequence[k] );
            if( k == 0 )
            {
                m_midpoint.do_step( system , in , dxdt , t , out , dt , m_mp_states[k].m_v , m_derivs[k]);
            }
            else
            {
                m_midpoint.do_step( system , in , dxdt , t , m_table[k-1].m_v , dt , m_mp_states[k].m_v , m_derivs[k] );
                extrapolate( k , m_table , m_coeff , out );
                // get error estimate
                m_algebra.for_each3( m_err.m_v , out , m_table[0].m_v ,
                                     typename operations_type::template scale_sum2< value_type , value_type >( val1 , -val1 ) );
                const value_type error = m_error_checker.error( m_algebra , in , dxdt , m_err.m_v , dt );
                h_opt[k] = calc_h_opt( dt , error , k );
                work[k] = static_cast<value_type>( m_cost[k] ) / h_opt[k];

                m_k_final = k;

                if( (k == m_current_k_opt-1) || m_first )
                { // convergence before k_opt ?
                    if( error < 1.0 )
                    {
                        //convergence
                        reject = false;
                        if( (work[k] < KFAC2*work[k-1]) || (m_current_k_opt <= 2) )
                        {
                            // leave order as is (except we were in first round)
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(k)+1 ) );
                            new_h = h_opt[k] * static_cast<value_type>( m_cost[k+1] ) / static_cast<value_type>( m_cost[k] );
                        } else {
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(k) ) );
                            new_h = h_opt[k];
                        }
                        break;
                    }
                    else if( should_reject( error , k ) && !m_first )
                    {
                        reject = true;
                        new_h = h_opt[k];
                        break;
                    }
                }
                if( k == m_current_k_opt )
                { // convergence at k_opt ?
                    if( error < 1.0 )
                    {
                        //convergence
                        reject = false;
                        if( (work[k-1] < KFAC2*work[k]) )
                        {
                            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(m_current_k_opt)-1 );
                            new_h = h_opt[m_current_k_opt];
                        }
                        else if( (work[k] < KFAC2*work[k-1]) && !m_last_step_rejected )
                        {
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , static_cast<int>(m_current_k_opt)+1 );
                            new_h = h_opt[k]*static_cast<value_type>( m_cost[m_current_k_opt] ) / static_cast<value_type>( m_cost[k] );
                        } else
                            new_h = h_opt[m_current_k_opt];
                        break;
                    }
                    else if( should_reject( error , k ) )
                    {
                        reject = true;
                        new_h = h_opt[m_current_k_opt];
                        break;
                    }
                }
                if( k == m_current_k_opt+1 )
                { // convergence at k_opt+1 ?
                    if( error < 1.0 )
                    {   //convergence
                        reject = false;
                        if( work[k-2] < KFAC2*work[k-1] )
                            m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( 2 , static_cast<int>(m_current_k_opt)-1 );
                        if( (work[k] < KFAC2*work[m_current_k_opt]) && !m_last_step_rejected )
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max)-1 , static_cast<int>(k) );
                        new_h = h_opt[m_current_k_opt];
                    } else
                    {
                        reject = true;
                        new_h = h_opt[m_current_k_opt];
                    }
                    break;
                }
            }
        }

        if( !reject )
        {

            //calculate dxdt for next step and dense output
            typename odeint::unwrap_reference< System >::type &sys = system;
            sys( out , dxdt_new , t+dt );

            //prepare dense output
            value_type error = prepare_dense_output( m_k_final , in , dxdt , out , dxdt_new , dt );

            if( error > static_cast<value_type>(10) ) // we are not as accurate for interpolation as for the steps
            {
                reject = true;
                new_h = dt * pow BOOST_PREVENT_MACRO_SUBSTITUTION( error , static_cast<value_type>(-1)/(2*m_k_final+2) );
            } else {
                t += dt;
            }
        }
        //set next stepsize
        if( !m_last_step_rejected || (new_h < dt) )
        {
            // limit step size
            if( m_max_dt != static_cast<time_type>(0) )
            {
                new_h = detail::min_abs(m_max_dt, new_h);
            }
            dt = new_h;
        }

        m_last_step_rejected = reject;
        if( reject )
            return fail;
        else
            return success;
    }

    template< class StateType >
    void initialize( const StateType &x0 , const time_type &t0 , const time_type &dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &controlled_error_bs_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::copy( x0 , get_current_state() );
        m_t = t0;
        m_dt = dt0;
        reset();
    }


    /*  =======================================================
     *  the actual step method that should be called from outside (maybe make try_step private?)
     */
    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        if( m_first )
        {
            typename odeint::unwrap_reference< System >::type &sys = system;
            sys( get_current_state() , get_current_deriv() , m_t );
        }

        failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
        controlled_step_result res = fail;
        m_t_last = m_t;
        while( res == fail )
        {
            res = try_step( system , get_current_state() , get_current_deriv() , m_t , get_old_state() , get_old_deriv() , m_dt );
            m_first = false;
            fail_checker();  // check for overflow of failed steps
        }
        toggle_current_state();
        return std::make_pair( m_t_last , m_t );
    }

    /* performs the interpolation from a calculated step */
    template< class StateOut >
    void calc_state( time_type t , StateOut &x ) const
    {
        do_interpolation( t , x );
    }

    const state_type& current_state( void ) const
    {
        return get_current_state();
    }

    time_type current_time( void ) const
    {
        return m_t;
    }

    const state_type& previous_state( void ) const
    {
        return get_old_state();
    }

    time_type previous_time( void ) const
    {
        return m_t_last;
    }

    time_type current_time_step( void ) const
    {
        return m_dt;
    }

    /** \brief Resets the internal state of the stepper. */
    void reset()
    {
        m_first = true;
        m_last_step_rejected = false;
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        m_midpoint.adjust_size( x );
    }


protected:

    time_type m_max_dt;


private:

    template< class StateInOut , class StateVector >
    void extrapolate( size_t k , StateVector &table , const value_matrix &coeff , StateInOut &xest , size_t order_start_index = 0 )
    //polynomial extrapolation, see http://www.nr.com/webnotes/nr3web21.pdf
    {
        static const value_type val1( 1.0 );
        for( int j=k-1 ; j>0 ; --j )
        {
            m_algebra.for_each3( table[j-1].m_v , table[j].m_v , table[j-1].m_v ,
                                 typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k + order_start_index][j + order_start_index] ,
                                                                                                           -coeff[k + order_start_index][j + order_start_index] ) );
        }
        m_algebra.for_each3( xest , table[0].m_v , xest ,
                             typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k + order_start_index][0 + order_start_index] ,
                                                                                                       -coeff[k + order_start_index][0 + order_start_index]) );
    }


    template< class StateVector >
    void extrapolate_dense_out( size_t k , StateVector &table , const value_matrix &coeff , size_t order_start_index = 0 )
    //polynomial extrapolation, see http://www.nr.com/webnotes/nr3web21.pdf
    {
        // result is written into table[0]
        static const value_type val1( 1.0 );
        for( int j=k ; j>1 ; --j )
        {
            m_algebra.for_each3( table[j-1].m_v , table[j].m_v , table[j-1].m_v ,
                                 typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k + order_start_index][j + order_start_index - 1] ,
                                                                                                           -coeff[k + order_start_index][j + order_start_index - 1] ) );
        }
        m_algebra.for_each3( table[0].m_v , table[1].m_v , table[0].m_v ,
                             typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k + order_start_index][order_start_index] ,
                                                                                                       -coeff[k + order_start_index][order_start_index]) );
    }

    time_type calc_h_opt( time_type h , value_type error , size_t k ) const
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;

        value_type expo = static_cast<value_type>(1)/(m_interval_sequence[k-1]);
        value_type facmin = m_facmin_table[k];
        value_type fac;
        if (error == 0.0)
            fac = static_cast<value_type>(1)/facmin;
        else
        {
            fac = STEPFAC2 / pow BOOST_PREVENT_MACRO_SUBSTITUTION( error / STEPFAC1 , expo );
            fac = max BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>( facmin/STEPFAC4 ) , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>(static_cast<value_type>(1)/facmin) , fac ) );
        }
        return h*fac;
    }

    bool in_convergence_window( size_t k ) const
    {
        if( (k == m_current_k_opt-1) && !m_last_step_rejected )
            return true; // decrease order only if last step was not rejected
        return ( (k == m_current_k_opt) || (k == m_current_k_opt+1) );
    }

    bool should_reject( value_type error , size_t k ) const
    {
        if( k == m_current_k_opt-1 )
        {
            const value_type d = m_interval_sequence[m_current_k_opt] * m_interval_sequence[m_current_k_opt+1] /
                (m_interval_sequence[0]*m_interval_sequence[0]);
            //step will fail, criterion 17.3.17 in NR
            return ( error > d*d );
        }
        else if( k == m_current_k_opt )
        {
            const value_type d = m_interval_sequence[m_current_k_opt+1] / m_interval_sequence[0];
            return ( error > d*d );
        } else
            return error > 1.0;
    }

    template< class StateIn1 , class DerivIn1 , class StateIn2 , class DerivIn2 >
    value_type prepare_dense_output( int k , const StateIn1 &x_start , const DerivIn1 &dxdt_start ,
                                     const StateIn2 & /* x_end */ , const DerivIn2 & /*dxdt_end */ , time_type dt )  
    /* k is the order to which the result was approximated */
    {

        /* compute the coefficients of the interpolation polynomial
         * we parametrize the interval t .. t+dt by theta = -1 .. 1
         * we use 2k+3 values at the interval center theta=0 to obtain the interpolation coefficients
         * the values are x(t+dt/2) and the derivatives dx/dt , ... d^(2k+2) x / dt^(2k+2) at the midpoints
         * the derivatives are approximated via finite differences
         * all values are obtained from interpolation of the results from the increasing orders of the midpoint calls
         */

        // calculate finite difference approximations to derivatives at the midpoint
        for( int j = 0 ; j<=k ; j++ )
        {
            /* not working with boost units... */
            const value_type d = m_interval_sequence[j] / ( static_cast<value_type>(2) * dt );
            value_type f = 1.0; //factor 1/2 here because our interpolation interval has length 2 !!!
            for( int kappa = 0 ; kappa <= 2*j+1 ; ++kappa )
            {
                calculate_finite_difference( j , kappa , f , dxdt_start );
                f *= d;
            }

            if( j > 0 )
                extrapolate_dense_out( j , m_mp_states , m_coeff );
        }

        time_type d = dt/2;

        // extrapolate finite differences
        for( int kappa = 0 ; kappa<=2*k+1 ; kappa++ )
        {
            for( int j=1 ; j<=(k-kappa/2) ; ++j )
                extrapolate_dense_out( j , m_diffs[kappa] , m_coeff , kappa/2 );

            // extrapolation results are now stored in m_diffs[kappa][0]

            // divide kappa-th derivative by kappa because we need these terms for dense output interpolation
            m_algebra.for_each1( m_diffs[kappa][0].m_v , typename operations_type::template scale< time_type >( static_cast<time_type>(d) ) );

            d *= dt/(2*(kappa+2));
        }

        // dense output coefficients a_0 is stored in m_mp_states[0], a_i for i = 1...2k are stored in m_diffs[i-1][0]

        // the error is just the highest order coefficient of the interpolation polynomial
        // this is because we use only the midpoint theta=0 as support for the interpolation (remember that theta = -1 .. 1)

        value_type error = 0.0;
        if( m_control_interpolation )
        {
            boost::numeric::odeint::copy( m_diffs[2*k+1][0].m_v , m_err.m_v );
            error = m_error_checker.error( m_algebra , x_start , dxdt_start , m_err.m_v , dt );
        }

        return error;
    }

    template< class DerivIn >
    void calculate_finite_difference( size_t j , size_t kappa , value_type fac , const DerivIn &dxdt )
    {
        const int m = m_interval_sequence[j]/2-1;
        if( kappa == 0) // no calculation required for 0th derivative of f
        {
            m_algebra.for_each2( m_diffs[0][j].m_v , m_derivs[j][m].m_v ,
                                 typename operations_type::template scale_sum1< value_type >( fac ) );
        }
        else
        {
            // calculate the index of m_diffs for this kappa-j-combination
            const int j_diffs = j - kappa/2;

            m_algebra.for_each2( m_diffs[kappa][j_diffs].m_v , m_derivs[j][m+kappa].m_v ,
                                 typename operations_type::template scale_sum1< value_type >( fac ) );
            value_type sign = -1.0;
            int c = 1;
            //computes the j-th order finite difference for the kappa-th derivative of f at t+dt/2 using function evaluations stored in m_derivs
            for( int i = m+static_cast<int>(kappa)-2 ; i >= m-static_cast<int>(kappa) ; i -= 2 )
            {
                if( i >= 0 )
                {
                    m_algebra.for_each3( m_diffs[kappa][j_diffs].m_v , m_diffs[kappa][j_diffs].m_v , m_derivs[j][i].m_v ,
                                         typename operations_type::template scale_sum2< value_type , value_type >( 1.0 ,
                                                                                                                   sign * fac * boost::math::binomial_coefficient< value_type >( kappa , c ) ) );
                }
                else
                {
                    m_algebra.for_each3( m_diffs[kappa][j_diffs].m_v , m_diffs[kappa][j_diffs].m_v , dxdt ,
                                         typename operations_type::template scale_sum2< value_type , value_type >( 1.0 , sign * fac ) );
                }
                sign *= -1;
                ++c;
            }
        }
    }

    template< class StateOut >
    void do_interpolation( time_type t , StateOut &out ) const
    {
        // interpolation polynomial is defined for theta = -1 ... 1
        // m_k_final is the number of order-iterations done for the last step - it governs the order of the interpolation polynomial
        const value_type theta = 2 * get_unit_value( (t - m_t_last) / (m_t - m_t_last) ) - 1;
        // we use only values at interval center, that is theta=0, for interpolation
        // our interpolation polynomial is thus of order 2k+2, hence we have 2k+3 terms

        boost::numeric::odeint::copy( m_mp_states[0].m_v , out );
        // add remaining terms: x += a_1 theta + a2 theta^2 + ... + a_{2k} theta^{2k}
        value_type theta_pow( theta );
        for( size_t i=0 ; i<=2*m_k_final+1 ; ++i )
        {
            m_algebra.for_each3( out , out , m_diffs[i][0].m_v ,
                                 typename operations_type::template scale_sum2< value_type >( static_cast<value_type>(1) , theta_pow ) );
            theta_pow *= theta;
        }
    }

    /* Resizer methods */
    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );

        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x2 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt2 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_err , x , typename is_resizeable<state_type>::type() );

        for( size_t i = 0 ; i < m_k_max ; ++i )
            resized |= adjust_size_by_resizeability( m_table[i] , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < m_k_max+1 ; ++i )
            resized |= adjust_size_by_resizeability( m_mp_states[i] , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < m_k_max+1 ; ++i )
            for( size_t j = 0 ; j < m_derivs[i].size() ; ++j )
                resized |= adjust_size_by_resizeability( m_derivs[i][j] , x , typename is_resizeable<deriv_type>::type() );
        for( size_t i = 0 ; i < 2*m_k_max+2 ; ++i )
            for( size_t j = 0 ; j < m_diffs[i].size() ; ++j )
                resized |= adjust_size_by_resizeability( m_diffs[i][j] , x , typename is_resizeable<deriv_type>::type() );

        return resized;
    }


    state_type& get_current_state( void )
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    const state_type& get_current_state( void ) const
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    state_type& get_old_state( void )
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }
    
    const state_type& get_old_state( void ) const
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }

    deriv_type& get_current_deriv( void )
    {
        return m_current_state_x1 ? m_dxdt1.m_v : m_dxdt2.m_v ;
    }
    
    const deriv_type& get_current_deriv( void ) const
    {
        return m_current_state_x1 ? m_dxdt1.m_v : m_dxdt2.m_v ;
    }
    
    deriv_type& get_old_deriv( void )
    {
        return m_current_state_x1 ? m_dxdt2.m_v : m_dxdt1.m_v ;
    }
    
    const deriv_type& get_old_deriv( void ) const
    {
        return m_current_state_x1 ? m_dxdt2.m_v : m_dxdt1.m_v ;
    }

    
    void toggle_current_state( void )
    {
        m_current_state_x1 = ! m_current_state_x1;
    }



    default_error_checker< value_type, algebra_type , operations_type > m_error_checker;
    modified_midpoint_dense_out< state_type , value_type , deriv_type , time_type , algebra_type , operations_type , resizer_type > m_midpoint;

    bool m_control_interpolation;

    bool m_last_step_rejected;
    bool m_first;

    time_type m_t;
    time_type m_dt;
    time_type m_dt_last;
    time_type m_t_last;

    size_t m_current_k_opt;
    size_t m_k_final;

    algebra_type m_algebra;

    resizer_type m_resizer;

    wrapped_state_type m_x1 , m_x2;
    wrapped_deriv_type m_dxdt1 , m_dxdt2;
    wrapped_state_type m_err;
    bool m_current_state_x1;



    value_vector m_error; // errors of repeated midpoint steps and extrapolations
    int_vector m_interval_sequence; // stores the successive interval counts
    value_matrix m_coeff;
    int_vector m_cost; // costs for interval count
    value_vector m_facmin_table; // for precomputed facmin to save pow calls

    state_vector_type m_table; // sequence of states for extrapolation

    //for dense output:
    state_vector_type m_mp_states; // sequence of approximations of x at distance center
    deriv_table_type m_derivs; // table of function values
    deriv_table_type m_diffs; // table of function values

    //wrapped_state_type m_a1 , m_a2 , m_a3 , m_a4;

    value_type STEPFAC1 , STEPFAC2 , STEPFAC3 , STEPFAC4 , KFAC1 , KFAC2;
};



/********** DOXYGEN **********/

/**
 * \class bulirsch_stoer_dense_out
 * \brief The Bulirsch-Stoer algorithm.
 * 
 * The Bulirsch-Stoer is a controlled stepper that adjusts both step size
 * and order of the method. The algorithm uses the modified midpoint and
 * a polynomial extrapolation compute the solution. This class also provides
 * dense output facility.
 *
 * \tparam State The state type.
 * \tparam Value The value type.
 * \tparam Deriv The type representing the time derivative of the state.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */

    /**
     * \fn bulirsch_stoer_dense_out::bulirsch_stoer_dense_out( value_type eps_abs , value_type eps_rel , value_type factor_x , value_type factor_dxdt , bool control_interpolation )
     * \brief Constructs the bulirsch_stoer class, including initialization of 
     * the error bounds.
     *
     * \param eps_abs Absolute tolerance level.
     * \param eps_rel Relative tolerance level.
     * \param factor_x Factor for the weight of the state.
     * \param factor_dxdt Factor for the weight of the derivative.
     * \param control_interpolation Set true to additionally control the error of 
     * the interpolation.
     */

    /**
     * \fn bulirsch_stoer_dense_out::try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , DerivOut &dxdt_new , time_type &dt )
     * \brief Tries to perform one step.
     *
     * This method tries to do one step with step size dt. If the error estimate
     * is to large, the step is rejected and the method returns fail and the 
     * step size dt is reduced. If the error estimate is acceptably small, the
     * step is performed, success is returned and dt might be increased to make 
     * the steps as large as possible. This method also updates t if a step is
     * performed. Also, the internal order of the stepper is adjusted if required.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. 
     * It must fulfill the Simple System concept.
     * \param in The state of the ODE which should be solved.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */

    /**
     * \fn bulirsch_stoer_dense_out::initialize( const StateType &x0 , const time_type &t0 , const time_type &dt0 )
     * \brief Initializes the dense output stepper.
     *
     * \param x0 The initial state.
     * \param t0 The initial time.
     * \param dt0 The initial time step.
     */

    /**
     * \fn bulirsch_stoer_dense_out::do_step( System system )
     * \brief Does one time step. This is the main method that should be used to 
     * integrate an ODE with this stepper.
     * \note initialize has to be called before using this method to set the
     * initial conditions x,t and the stepsize.
     * \param system The system function to solve, hence the r.h.s. of the
     * ordinary differential equation. It must fulfill the Simple System concept.
     * \return Pair with start and end time of the integration step.
     */

    /**
     * \fn bulirsch_stoer_dense_out::calc_state( time_type t , StateOut &x ) const
     * \brief Calculates the solution at an intermediate point within the last step
     * \param t The time at which the solution should be calculated, has to be
     * in the current time interval.
     * \param x The output variable where the result is written into.
     */

    /**
     * \fn bulirsch_stoer_dense_out::current_state( void ) const
     * \brief Returns the current state of the solution.
     * \return The current state of the solution x(t).
     */

    /**
     * \fn bulirsch_stoer_dense_out::current_time( void ) const
     * \brief Returns the current time of the solution.
     * \return The current time of the solution t.
     */

    /**
     * \fn bulirsch_stoer_dense_out::previous_state( void ) const
     * \brief Returns the last state of the solution.
     * \return The last state of the solution x(t-dt).
     */

    /**
     * \fn bulirsch_stoer_dense_out::previous_time( void ) const
     * \brief Returns the last time of the solution.
     * \return The last time of the solution t-dt.
     */

    /**
     * \fn bulirsch_stoer_dense_out::current_time_step( void ) const
     * \brief Returns the current step size.
     * \return The current step size.
     */

    /**
     * \fn bulirsch_stoer_dense_out::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_HPP_INCLUDED

/* bulirsch_stoer_dense_out.hpp
+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
*/