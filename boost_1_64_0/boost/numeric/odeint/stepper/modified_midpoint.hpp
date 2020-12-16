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
nzpVB9Ip+hrKn64b1S9M2VJE3az8mcLTneH8HheQgHui05vrc3ozvU6fs6zcckyhhwXo6e7y6o++938WHvgspcxmL3dVOi0KPSJAT7NVuUrpTx07nc71lbYSl8NybJjlnOZ1MbtyMXZrbnZSljUuISdlVErOWGtmVlJ2UnpCEmcV40bHBPnwyistx56tmUdOpjUhLjU1Pi5hJFekZGQplw5PSR7O2JiP/PP0jKy0uNTqecmvSc0YLeYh/zwlfVRcakrin16TkJGbnmM5/v2x+Jp5848yb9nl6qylHylzXivmDBLNiLdmxI9ISsixpiflWLPicpIQlZ6TlZFqTUqPi09NQqY6tz+9Ni1ujDU+Lj1xdEpijqqvOn96fWJ2QqY1Jy5ZnfM5f3qtXznWYalxydnoeRzzxzaZP5iN+f/Jneo9qi7+6WWKXmbK9JKSIVWLXyd/dl12DvqIS81IT7KOykjNTUsS63v6PcGnit6ZK3eoc63HXE+7szZT5SrpTOHdPaJ6rgkZaSlpcclJ6qfWFIacOlad35mf9Y2OT8nJSroqNyUrSdhrHf391tSU+Ky4LJVH/TM/z2Yk6cnpcWlJ2SnJ6bBR7SvyzOvS4/DWJGsSIx+bmZGC9avywDu6MedkYeKJSfG5yYlxOXEWcV2Q8eP9w5KymEDNHLOso5KyslMy0rHjEcpP0ciSf8Y99NBPp6cQBKrnCj0xKTUpJynRqkzRmpqUnoxHMMeaz0flKAaUHJd52hXqWohJ54zNTPL7VEJ8tf+dUu5FuWlJOcMzEq3ZyvJmE3pU31OmnZ0yLqk69qqT5g5GN9yq3pM1Kq46Tp3xedLwwGf1z/gsHr4J8akZCSOreQfmoOrzNF2p9NiYGnodLX1YVkaaNTc9LS4dEYmqzoJ/bs1KyolLSbfGZWYmZqTxv2pdRGrvIcKhg4zsHBSfhfKEXXbQzCMpLmeENWd4bvpIq19JfE7w8Os3NS4bU2MdFN4Beib2xN3qJ8ey8MMLhR/Wxw+znJ4Sm93pS3B7hzu86RWlTq/LnugscJU5faoP/tkVqv/xTlUqVfrWBLNGcEUyf8A08D+PyN5A+Y4NV18XccZ154vrGgWuiwTS8Qm8oUcK+qvEtPOZFzCCP2k2exFj4BpBY90YXb7Tm1GQ7SQTu8t8Fv9nPNrM2uW4Sp2JtnJndrmt1GNR6eiAfOwqK3d6c9zZk0rz3SU5tvwSZ+C+hjU81Y99AXmsXbbrOmdGQYZHEWYrGe60OZxeS83nTSwJRTYvoACN+cpddu4l59Vtfg5DbcKcqv80s1iFZ6dgBMOT4lh9Rfe5evKVV8KjF3qoHh8dPJe3vMJWEudwAEx8rIdmzsr4wBfIDEdmM43M+tUyFXezJqZk4YQZxDlFrPQTJLMurFlgXVqcvq70j9R1VcdFbSXW9UL1Oj6LaM66MjZyAC0N7c8efh4l5sVWPH98PmuBrdRVMom1or8AD9CtFarH5oiCBv5W5qHSAFKFZdVzb8u1kTXXRlvQuT/PttPM/yaLz20vtqE0q6/c7bUVOq1VHv/sJXTmrvDgLtSo+WOQR/cafJaWEJdNSktPSM1NVH04TNCSxqi0IfhpuPDTDpHckZuak6JcQXxIVKOq6p6SDxDl1+1Fkapub0K340+zmcICq9/oC3Bs1V65Fl1CL/S6KzzChqFNV2gFpW6HxifuVGhlFaU+r131I667R6H5SrBzy7FYdKXgus4afUeG+RlbC1wlyPUrSUtQ7Po0e2jEmLuf5u8+m9YeuvjtAZrDVm7z+4Rq45doZdasj3ZRVFkvCt7olz/lpVaf015tP9DwHWilrjINDf1AK3JXeC0BWkP/dQ7bJA0=
*/