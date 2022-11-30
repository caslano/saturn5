/*
  [auto_generated]
  boost/numeric/odeint/stepper/extrapolation_stepper.hpp

  [begin_description]
  extrapolation stepper
  [end_description]

  Copyright 2009-2015 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EXTRAPOLATION_STEPPER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EXTRAPOLATION_STEPPER_HPP_INCLUDED

#include <iostream>

#include <algorithm>

#include <boost/config.hpp> // for min/max guidelines
#include <boost/static_assert.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp>
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

namespace boost
{
namespace numeric
{
namespace odeint
{

template < unsigned short Order, class State, class Value = double,
           class Deriv = State, class Time = Value,
           class Algebra = typename algebra_dispatcher< State >::algebra_type,
           class Operations =
               typename operations_dispatcher< State >::operations_type,
           class Resizer = initially_resizer >
#ifndef DOXYGEN_SKIP
class extrapolation_stepper
    : public explicit_error_stepper_base<
          extrapolation_stepper< Order, State, Value, Deriv, Time, Algebra,
                                 Operations, Resizer >,
          Order, Order, Order - 2, State, Value, Deriv, Time, Algebra,
          Operations, Resizer >
#else
class extrapolation_stepper : public explicit_error_stepper_base
#endif
{

  private:
    // check for Order being odd
    BOOST_STATIC_ASSERT_MSG(
        ( ( Order % 2 ) == 0 ) && ( Order > 2 ),
        "extrapolation_stepper requires even Order larger than 2" );

  public:
#ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_base<
        extrapolation_stepper< Order, State, Value, Deriv, Time, Algebra,
                               Operations, Resizer >,
        Order, Order, Order - 2, State, Value, Deriv, Time, Algebra, Operations,
        Resizer > stepper_base_type;
#else
    typedef explicit_error_stepper_base< extrapolation_stepper< ... >, ... >
    stepper_base_type;
#endif

    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;

#ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::stepper_type stepper_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;

    typedef std::vector< value_type > value_vector;
    typedef std::vector< value_vector > value_matrix;
    typedef std::vector< size_t > int_vector;
    typedef std::vector< wrapped_state_type > state_table_type;
    typedef modified_midpoint< state_type, value_type, deriv_type, time_type,
                               algebra_type, operations_type,
                               resizer_type > midpoint_stepper_type;

#endif // DOXYGEN_SKIP

    typedef unsigned short order_type;
    static const order_type order_value = stepper_base_type::order_value;
    static const order_type stepper_order_value =
        stepper_base_type::stepper_order_value;
    static const order_type error_order_value =
        stepper_base_type::error_order_value;

    const static size_t m_k_max = ( order_value - 2 ) / 2;

    extrapolation_stepper( const algebra_type &algebra = algebra_type() )
        : stepper_base_type( algebra ), m_interval_sequence( m_k_max + 1 ),
          m_coeff( m_k_max + 1 ), m_table( m_k_max )
    {
        for ( unsigned short i = 0; i < m_k_max + 1; i++ )
        {
            m_interval_sequence[i] = 2 * ( i + 1 );
            m_coeff[i].resize( i );
            for ( size_t k = 0; k < i; ++k )
            {
                const value_type r =
                    static_cast< value_type >( m_interval_sequence[i] ) /
                    static_cast< value_type >( m_interval_sequence[k] );
                m_coeff[i][k] =
                    static_cast< value_type >( 1 ) /
                    ( r * r - static_cast< value_type >(
                                  1 ) ); // coefficients for extrapolation
            }
        }
    }

    template < class System, class StateIn, class DerivIn, class StateOut,
               class Err >
    void do_step_impl( System system, const StateIn &in, const DerivIn &dxdt,
                       time_type t, StateOut &out, time_type dt, Err &xerr )
    {
        // std::cout << "dt: " << dt << std::endl;
        // normal step
        do_step_impl( system, in, dxdt, t, out, dt );

        static const value_type val1( 1.0 );
        // additionally, perform the error calculation
        stepper_base_type::m_algebra.for_each3(
            xerr, out, m_table[0].m_v,
            typename operations_type::template scale_sum2<
                value_type, value_type >( val1, -val1 ) );
    }

    template < class System, class StateInOut, class DerivIn, class Err >
    void do_step_impl_io( System system, StateInOut &inout, const DerivIn &dxdt,
                          time_type t, time_type dt, Err &xerr )
    {
        // normal step
        do_step_impl_io( system, inout, dxdt, t, dt );

        static const value_type val1( 1.0 );
        // additionally, perform the error calculation
        stepper_base_type::m_algebra.for_each3(
            xerr, inout, m_table[0].m_v,
            typename operations_type::template scale_sum2<
                value_type, value_type >( val1, -val1 ) );
    }

    template < class System, class StateIn, class DerivIn, class StateOut >
    void do_step_impl( System system, const StateIn &in, const DerivIn &dxdt,
                       time_type t, StateOut &out, time_type dt )
    {
        m_resizer.adjust_size(
            in, detail::bind( &stepper_type::template resize_impl< StateIn >,
                              detail::ref( *this ), detail::_1 ) );
        size_t k = 0;
        m_midpoint.set_steps( m_interval_sequence[k] );
        m_midpoint.do_step( system, in, dxdt, t, out, dt );
        for ( k = 1; k <= m_k_max; ++k )
        {
            m_midpoint.set_steps( m_interval_sequence[k] );
            m_midpoint.do_step( system, in, dxdt, t, m_table[k - 1].m_v, dt );
            extrapolate( k, m_table, m_coeff, out );
        }
    }

    template < class System, class StateInOut, class DerivIn >
    void do_step_impl_io( System system, StateInOut &inout, const DerivIn &dxdt,
                          time_type t, time_type dt )
    {
        // special care for inout
        m_xout_resizer.adjust_size(
            inout,
            detail::bind( &stepper_type::template resize_m_xout< StateInOut >,
                          detail::ref( *this ), detail::_1 ) );
        do_step_impl( system, inout, dxdt, t, m_xout.m_v, dt );
        boost::numeric::odeint::copy( m_xout.m_v, inout );
    }

    template < class System, class StateInOut, class DerivIn >
    void do_step_dxdt_impl( System system, StateInOut &x, const DerivIn &dxdt,
                            time_type t, time_type dt )
    {
        do_step_impl_io( system , x , dxdt , t , dt );
    }

    template < class System, class StateIn, class DerivIn, class StateOut >
    void do_step_dxdt_impl( System system, const StateIn &in,
                            const DerivIn &dxdt, time_type t, StateOut &out,
                            time_type dt )
    {
        do_step_impl( system , in , dxdt , t , out , dt );
    }


    template < class StateIn > void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        m_midpoint.adjust_size( x );
    }

  private:
    template < class StateIn > bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        for ( size_t i = 0; i < m_k_max; ++i )
            resized |= adjust_size_by_resizeability(
                m_table[i], x, typename is_resizeable< state_type >::type() );
        return resized;
    }

    template < class StateIn > bool resize_m_xout( const StateIn &x )
    {
        return adjust_size_by_resizeability(
            m_xout, x, typename is_resizeable< state_type >::type() );
    }

    template < class StateInOut >
    void extrapolate( size_t k, state_table_type &table,
                      const value_matrix &coeff, StateInOut &xest )
    /* polynomial extrapolation, see http://www.nr.com/webnotes/nr3web21.pdf
       uses the obtained intermediate results to extrapolate to dt->0
    */
    {
        static const value_type val1 = static_cast< value_type >( 1.0 );

        for ( int j = k - 1; j > 0; --j )
        {
            stepper_base_type::m_algebra.for_each3(
                table[j - 1].m_v, table[j].m_v, table[j - 1].m_v,
                typename operations_type::template scale_sum2<
                    value_type, value_type >( val1 + coeff[k][j],
                                              -coeff[k][j] ) );
        }
        stepper_base_type::m_algebra.for_each3(
            xest, table[0].m_v, xest,
            typename operations_type::template scale_sum2<
                value_type, value_type >( val1 + coeff[k][0], -coeff[k][0] ) );
    }

  private:
    midpoint_stepper_type m_midpoint;

    resizer_type m_resizer;
    resizer_type m_xout_resizer;

    int_vector m_interval_sequence; // stores the successive interval counts
    value_matrix m_coeff;

    wrapped_state_type m_xout;
    state_table_type m_table; // sequence of states for extrapolation
};

/******** DOXYGEN *******/

/**
 * \class extrapolation_stepper
 * \brief Extrapolation stepper with configurable order, and error estimation.
 *
 * The extrapolation stepper is a stepper with error estimation and configurable
 * order. The order is given as template parameter and needs to be an _odd_
 * number. The stepper is based on several executions of the modified midpoint
 * method and a Richardson extrapolation. This is essentially the same technique
 * as for bulirsch_stoer, but without the variable order.
 *
 * \note The Order parameter has to be an even number greater 2.
 */
}
}
}
#endif

/* extrapolation_stepper.hpp
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
*/