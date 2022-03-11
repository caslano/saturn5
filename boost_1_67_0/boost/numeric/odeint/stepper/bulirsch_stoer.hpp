/*
  [auto_generated]
  boost/numeric/odeint/stepper/bulirsch_stoer.hpp

  [begin_description]
  Implementation of the Burlish-Stoer method. As described in
  Ernst Hairer, Syvert Paul Norsett, Gerhard Wanner
  Solving Ordinary Differential Equations I. Nonstiff Problems.
  Springer Series in Comput. Mathematics, Vol. 8, Springer-Verlag 1987, Second revised edition 1993.
  [end_description]

  Copyright 2011-2013 Mario Mulansky
  Copyright 2011-2013 Karsten Ahnert
  Copyright 2012 Christoph Koke

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_HPP_INCLUDED


#include <iostream>

#include <algorithm>

#include <boost/config.hpp> // for min/max guidelines

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

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
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

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
class bulirsch_stoer {

public:

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
#ifndef DOXYGEN_SKIP
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef controlled_stepper_tag stepper_category;

    typedef bulirsch_stoer< State , Value , Deriv , Time , Algebra , Operations , Resizer > controlled_error_bs_type;

    typedef typename inverse_time< time_type >::type inv_time_type;

    typedef std::vector< value_type > value_vector;
    typedef std::vector< time_type > time_vector;
    typedef std::vector< inv_time_type > inv_time_vector;  //should be 1/time_type for boost.units
    typedef std::vector< value_vector > value_matrix;
    typedef std::vector< size_t > int_vector;
    typedef std::vector< wrapped_state_type > state_table_type;
#endif //DOXYGEN_SKIP
    const static size_t m_k_max = 8;

    bulirsch_stoer(
        value_type eps_abs = 1E-6 , value_type eps_rel = 1E-6 ,
        value_type factor_x = 1.0 , value_type factor_dxdt = 1.0 ,
        time_type max_dt = static_cast<time_type>(0))
        : m_error_checker( eps_abs , eps_rel , factor_x, factor_dxdt ) , m_midpoint() ,
          m_last_step_rejected( false ) , m_first( true ) ,
          m_max_dt(max_dt) ,
          m_interval_sequence( m_k_max+1 ) ,
          m_coeff( m_k_max+1 ) ,
          m_cost( m_k_max+1 ) ,
          m_facmin_table( m_k_max+1 ) ,
          m_table( m_k_max ) ,
          STEPFAC1( 0.65 ) , STEPFAC2( 0.94 ) , STEPFAC3( 0.02 ) , STEPFAC4( 4.0 ) , KFAC1( 0.8 ) , KFAC2( 0.9 )
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        /* initialize sequence of stage numbers and work */
        for( unsigned short i = 0; i < m_k_max+1; i++ )
        {
            m_interval_sequence[i] = 2 * (i+1);
            if( i == 0 )
                m_cost[i] = m_interval_sequence[i];
            else
                m_cost[i] = m_cost[i-1] + m_interval_sequence[i];
            m_coeff[i].resize(i);
            m_facmin_table[i] = pow BOOST_PREVENT_MACRO_SUBSTITUTION( STEPFAC3 , static_cast< value_type >(1) / static_cast< value_type >( 2*i+1 ) );
            for( size_t k = 0 ; k < i ; ++k  )
            {
                const value_type r = static_cast< value_type >( m_interval_sequence[i] ) / static_cast< value_type >( m_interval_sequence[k] );
                m_coeff[i][k] = 1.0 / ( r*r - static_cast< value_type >( 1.0 ) ); // coefficients for extrapolation
            }
        }
        reset();
    }


    /*
     * Version 1 : try_step( sys , x , t , dt )
     *
     * The overloads are needed to solve the forwarding problem
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t, dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be used with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut >
    controlled_step_result try_step( System system , const StateInOut &x , time_type &t , time_type &dt )
    {
        return try_step_v1( system , x , t, dt );
    }

    /*
     * Version 2 : try_step( sys , x , dxdt , t , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateInOut , class DerivIn >
    controlled_step_result try_step( System system , StateInOut &x , const DerivIn &dxdt , time_type &t , time_type &dt )
    {
        m_xnew_resizer.adjust_size( x , detail::bind( &controlled_error_bs_type::template resize_m_xnew< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        controlled_step_result res = try_step( system , x , dxdt , t , m_xnew.m_v , dt );
        if( res == success )
        {
            boost::numeric::odeint::copy( m_xnew.m_v , x );
        }
        return res;
    }

    /*
     * Version 3 : try_step( sys , in , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class StateOut >
    typename boost::disable_if< boost::is_same< StateIn , time_type > , controlled_step_result >::type
    try_step( System system , const StateIn &in , time_type &t , StateOut &out , time_type &dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_dxdt_resizer.adjust_size( in , detail::bind( &controlled_error_bs_type::template resize_m_dxdt< StateIn > , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v , t );
        return try_step( system , in , m_dxdt.m_v , t , out , dt );
    }


    /*
     * Full version : try_step( sys , in , dxdt_in , t , out , dt )
     *
     * contains the actual implementation
     */
    template< class System , class StateIn , class DerivIn , class StateOut >
    controlled_step_result try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , time_type &dt )
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

        static const value_type val1( 1.0 );

        if( m_resizer.adjust_size( in , detail::bind( &controlled_error_bs_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) ) )
        {
            reset(); // system resized -> reset
        }

        if( dt != m_dt_last )
        {
            reset(); // step size changed from outside -> reset
        }

        bool reject( true );

        time_vector h_opt( m_k_max+1 );
        inv_time_vector work( m_k_max+1 );

        time_type new_h = dt;

        /* m_current_k_opt is the estimated current optimal stage number */
        for( size_t k = 0 ; k <= m_current_k_opt+1 ; k++ )
        {
            /* the stage counts are stored in m_interval_sequence */
            m_midpoint.set_steps( m_interval_sequence[k] );
            if( k == 0 )
            {
                m_midpoint.do_step( system , in , dxdt , t , out , dt );
                /* the first step, nothing more to do */
            }
            else
            {
                m_midpoint.do_step( system , in , dxdt , t , m_table[k-1].m_v , dt );
                extrapolate( k , m_table , m_coeff , out );
                // get error estimate
                m_algebra.for_each3( m_err.m_v , out , m_table[0].m_v ,
                                     typename operations_type::template scale_sum2< value_type , value_type >( val1 , -val1 ) );
                const value_type error = m_error_checker.error( m_algebra , in , dxdt , m_err.m_v , dt );
                h_opt[k] = calc_h_opt( dt , error , k );
                work[k] = static_cast<value_type>( m_cost[k] ) / h_opt[k];

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
                            new_h = h_opt[k];
                            new_h *= static_cast<value_type>( m_cost[k+1] ) / static_cast<value_type>( m_cost[k] );
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
                            m_current_k_opt = min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<int>(m_k_max-1) , static_cast<int>(m_current_k_opt)+1 );
                            new_h = h_opt[k];
                            new_h *= static_cast<value_type>(m_cost[m_current_k_opt])/static_cast<value_type>(m_cost[k]);
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
            t += dt;
        }

        if( !m_last_step_rejected || boost::numeric::odeint::detail::less_with_sign(new_h, dt, dt) )
        {
            // limit step size
            if( m_max_dt != static_cast<time_type>(0) )
            {
                new_h = detail::min_abs(m_max_dt, new_h);
            }
            m_dt_last = new_h;
            dt = new_h;
        }

        m_last_step_rejected = reject;
        m_first = false;

        if( reject )
            return fail;
        else
            return success;
    }

    /** \brief Resets the internal state of the stepper */
    void reset()
    {
        m_first = true;
        m_last_step_rejected = false;
        // crude estimate of optimal order
        m_current_k_opt = 4;
        /* no calculation because log10 might not exist for value_type!
        const value_type logfact( -log10( max BOOST_PREVENT_MACRO_SUBSTITUTION( eps_rel , static_cast< value_type >(1.0E-12) ) ) * 0.6 + 0.5 );
        m_current_k_opt = max BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>( 1 ) , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>( m_k_max-1 ) , logfact ));
        */
    }


    /* Resizer methods */

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_m_dxdt( x );
        resize_m_xnew( x );
        resize_impl( x );
        m_midpoint.adjust_size( x );
    }


private:

    template< class StateIn >
    bool resize_m_dxdt( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }

    template< class StateIn >
    bool resize_m_xnew( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xnew , x , typename is_resizeable<state_type>::type() );
    }

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        for( size_t i = 0 ; i < m_k_max ; ++i )
            resized |= adjust_size_by_resizeability( m_table[i] , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_err , x , typename is_resizeable<state_type>::type() );
        return resized;
    }


    template< class System , class StateInOut >
    controlled_step_result try_step_v1( System system , StateInOut &x , time_type &t , time_type &dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_dxdt_resizer.adjust_size( x , detail::bind( &controlled_error_bs_type::template resize_m_dxdt< StateInOut > , detail::ref( *this ) , detail::_1 ) );
        sys( x , m_dxdt.m_v ,t );
        return try_step( system , x , m_dxdt.m_v , t , dt );
    }


    template< class StateInOut >
    void extrapolate( size_t k , state_table_type &table , const value_matrix &coeff , StateInOut &xest )
    /* polynomial extrapolation, see http://www.nr.com/webnotes/nr3web21.pdf
       uses the obtained intermediate results to extrapolate to dt->0 
    */
    {
        static const value_type val1 = static_cast< value_type >( 1.0 );
        for( int j=k-1 ; j>0 ; --j )
        {
            m_algebra.for_each3( table[j-1].m_v , table[j].m_v , table[j-1].m_v ,
                                 typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k][j] , -coeff[k][j] ) );
        }
        m_algebra.for_each3( xest , table[0].m_v , xest ,
                             typename operations_type::template scale_sum2< value_type , value_type >( val1 + coeff[k][0] , -coeff[k][0]) );
    }

    time_type calc_h_opt( time_type h , value_type error , size_t k ) const
    /* calculates the optimal step size for a given error and stage number */
    {
        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;
        value_type expo( 1.0/(2*k+1) );
        value_type facmin = m_facmin_table[k];
        value_type fac;
        if (error == 0.0)
            fac=1.0/facmin;
        else
        {
            fac = STEPFAC2 / pow BOOST_PREVENT_MACRO_SUBSTITUTION( error / STEPFAC1 , expo );
            fac = max BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>(facmin/STEPFAC4) , min BOOST_PREVENT_MACRO_SUBSTITUTION( static_cast<value_type>(1.0/facmin) , fac ) );
        }
        return h*fac;
    }

    controlled_step_result set_k_opt( size_t k , const inv_time_vector &work , const time_vector &h_opt , time_type &dt )
    /* calculates the optimal stage number */
    {
        if( k == 1 )
        {
            m_current_k_opt = 2;
            return success;
        }
        if( (work[k-1] < KFAC1*work[k]) || (k == m_k_max) )
        {   // order decrease
            m_current_k_opt = k-1;
            dt = h_opt[ m_current_k_opt ];
            return success;
        }
        else if( (work[k] < KFAC2*work[k-1]) || m_last_step_rejected || (k == m_k_max-1) )
        {   // same order - also do this if last step got rejected
            m_current_k_opt = k;
            dt = h_opt[ m_current_k_opt ];
            return success;
        }
        else
        {   // order increase - only if last step was not rejected
            m_current_k_opt = k+1;
            dt = h_opt[ m_current_k_opt-1 ] * m_cost[ m_current_k_opt ] / m_cost[ m_current_k_opt-1 ] ;
            return success;
        }
    }

    bool in_convergence_window( size_t k ) const
    {
        if( (k == m_current_k_opt-1) && !m_last_step_rejected )
            return true; // decrease stepsize only if last step was not rejected
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
            const value_type d = m_interval_sequence[m_current_k_opt] / m_interval_sequence[0];
            return ( error > d*d );
        } else
            return error > 1.0;
    }

    default_error_checker< value_type, algebra_type , operations_type > m_error_checker;
    modified_midpoint< state_type , value_type , deriv_type , time_type , algebra_type , operations_type , resizer_type > m_midpoint;

    bool m_last_step_rejected;
    bool m_first;

    time_type m_dt_last;
    time_type m_t_last;
    time_type m_max_dt;

    size_t m_current_k_opt;

    algebra_type m_algebra;

    resizer_type m_dxdt_resizer;
    resizer_type m_xnew_resizer;
    resizer_type m_resizer;

    wrapped_state_type m_xnew;
    wrapped_state_type m_err;
    wrapped_deriv_type m_dxdt;

    int_vector m_interval_sequence; // stores the successive interval counts
    value_matrix m_coeff;
    int_vector m_cost; // costs for interval count
    value_vector m_facmin_table; // for precomputed facmin to save pow calls

    state_table_type m_table; // sequence of states for extrapolation

    value_type STEPFAC1 , STEPFAC2 , STEPFAC3 , STEPFAC4 , KFAC1 , KFAC2;
};


/******** DOXYGEN ********/
/**
 * \class bulirsch_stoer
 * \brief The Bulirsch-Stoer algorithm.
 * 
 * The Bulirsch-Stoer is a controlled stepper that adjusts both step size
 * and order of the method. The algorithm uses the modified midpoint and
 * a polynomial extrapolation compute the solution.
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
     * \fn bulirsch_stoer::bulirsch_stoer( value_type eps_abs , value_type eps_rel , value_type factor_x , value_type factor_dxdt )
     * \brief Constructs the bulirsch_stoer class, including initialization of 
     * the error bounds.
     *
     * \param eps_abs Absolute tolerance level.
     * \param eps_rel Relative tolerance level.
     * \param factor_x Factor for the weight of the state.
     * \param factor_dxdt Factor for the weight of the derivative.
     */

    /**
     * \fn bulirsch_stoer::try_step( System system , StateInOut &x , time_type &t , time_type &dt )
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
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */

    /**
     * \fn bulirsch_stoer::try_step( System system , StateInOut &x , const DerivIn &dxdt , time_type &t , time_type &dt )
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
     * \param x The state of the ODE which should be solved. Overwritten if 
     * the step is successful.
     * \param dxdt The derivative of state.
     * \param t The value of the time. Updated if the step is successful.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */

    /**
     * \fn bulirsch_stoer::try_step( System system , const StateIn &in , time_type &t , StateOut &out , time_type &dt )
     * \brief Tries to perform one step.
     *
     * \note This method is disabled if state_type=time_type to avoid ambiguity.
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
     * \param t The value of the time. Updated if the step is successful.
     * \param out Used to store the result of the step.
     * \param dt The step size. Updated.
     * \return success if the step was accepted, fail otherwise.
     */


    /**
     * \fn bulirsch_stoer::try_step( System system , const StateIn &in , const DerivIn &dxdt , time_type &t , StateOut &out , time_type &dt )
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
     * \fn bulirsch_stoer::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_BULIRSCH_STOER_HPP_INCLUDED

/* bulirsch_stoer.hpp
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
*/