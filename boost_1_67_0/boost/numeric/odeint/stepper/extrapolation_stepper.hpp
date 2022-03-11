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