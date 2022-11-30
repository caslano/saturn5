/*
 [auto_generated]
 boost/numeric/odeint/stepper/modified_midpoint.hpp

 [begin_description]
 Modified midpoint method for the use in Burlish-Stoer stepper.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED

#include <vector>

#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

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
#ifndef DOXYGEN_SKIP
class modified_midpoint
: public explicit_stepper_base<
  modified_midpoint< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  2 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class modified_midpoint : public explicit_stepper_base
#endif
{

public :

    typedef explicit_stepper_base<
    modified_midpoint< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    2 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;

    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;
    typedef typename stepper_base_type::stepper_type stepper_type;


    modified_midpoint( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_steps( steps )
    { }

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt /  static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>(2) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        stepper_base_type::m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        sys( m_x1.m_v , m_dxdt.m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            stepper_base_type::m_algebra.for_each3( m_x1.m_v , m_x0.m_v , m_dxdt.m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            th += h;
            sys( m_x1.m_v , m_dxdt.m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        stepper_base_type::m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , m_dxdt.m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }


    void set_steps( unsigned short steps )
    {   m_steps = steps; }


    unsigned short steps( void ) const
    {   return m_steps; }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }

private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    unsigned short m_steps;

    resizer_type m_resizer;

    wrapped_state_type m_x0;
    wrapped_state_type m_x1;
    wrapped_deriv_type m_dxdt;

};


/* Modified midpoint which stores derivatives and state at dt/2 in some external storage for later usage in dense output calculation
 * This Stepper is for use in Bulirsch Stoer only. It DOES NOT meet any stepper concept.
 */
template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class modified_midpoint_dense_out
{

public :

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;

    typedef modified_midpoint_dense_out< State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;
    typedef std::vector< wrapped_deriv_type > deriv_table_type;

    modified_midpoint_dense_out( unsigned short steps = 2 , const algebra_type &algebra = algebra_type() )
    : m_algebra( algebra ) , m_steps( steps )
    { }

    /*
     * performs a modified midpoint step with m_steps intermediate points
     * stores approximation for x(t+dt/2) in x_mp and all evaluated function results in derivs
     *
     */

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt ,
            state_type &x_mp , deriv_table_type &derivs )
    {

        static const value_type val1 = static_cast< value_type >( 1 );
        static const value_type val05 = static_cast< value_type >( 1 ) / static_cast< value_type >( 2 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize< StateIn > , detail::ref( *this ) , detail::_1 ) );

        const time_type h = dt / static_cast<value_type>( m_steps );
        const time_type h2 = static_cast<value_type>( 2 ) * h;

        typename odeint::unwrap_reference< System >::type &sys = system;

        time_type th = t + h;

        // m_x1 = x + h*dxdt
        m_algebra.for_each3( m_x1.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , h ) );

        if( m_steps == 2 )
            // result of first step already gives approximation at the center of the interval
            boost::numeric::odeint::copy( m_x1.m_v , x_mp );

        sys( m_x1.m_v , derivs[0].m_v , th );

        boost::numeric::odeint::copy( in , m_x0.m_v );

        unsigned short i = 1;
        while( i != m_steps )
        {
            // general step
            //tmp = m_x1; m_x1 = m_x0 + h2*m_dxdt; m_x0 = tmp
            m_algebra.for_each3( m_x1.m_v , m_x0.m_v , derivs[i-1].m_v ,
                    typename operations_type::template scale_sum_swap2< value_type , time_type >( val1 , h2 ) );
            if( i == m_steps/2-1 )
                // save approximation at the center of the interval
                boost::numeric::odeint::copy( m_x1.m_v , x_mp );

            th += h;
            sys( m_x1.m_v , derivs[i].m_v , th);
            i++;
        }

        // last step
        // x = 0.5*( m_x0 + m_x1 + h*m_dxdt )
        m_algebra.for_each4( out , m_x0.m_v , m_x1.m_v , derivs[m_steps-1].m_v ,
                typename operations_type::template scale_sum3< value_type , value_type , time_type >( val05 , val05 , val05*h ) );
    }


    void set_steps( unsigned short steps )
    {   m_steps = steps; }


    unsigned short steps( void ) const
    {   return m_steps; }


    template< class StateIn >
    bool resize( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x0 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        return resized;
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize( x );
    }

private:

    algebra_type m_algebra;

    unsigned short m_steps;

    resizer_type m_resizer;

    wrapped_state_type m_x0;
    wrapped_state_type m_x1;

};



/********** DOXYGEN ***********/

/**
 * \class modified_midpoint
 *
 * Implementation of the modified midpoint method with a configurable 
 * number of intermediate steps. This class is used by the Bulirsch-Stoer
 * algorithm and is not meant for direct usage.
 */


/**
 * \class modified_midpoint_dense_out
 *
 * Implementation of the modified midpoint method with a configurable 
 * number of intermediate steps. This class is used by the dense output
 * Bulirsch-Stoer algorithm and is not meant for direct usage.
 * \note This stepper is for internal use only and does not meet 
 * any stepper concept.
 */


}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_MODIFIED_MIDPOINT_HPP_INCLUDED

/* modified_midpoint.hpp
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
*/