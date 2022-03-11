/*
 [auto_generated]
 boost/numeric/odeint/stepper/adams_moulton.hpp

 [begin_description]
 Implementation of the Adams-Moulton method. This is method is not a real stepper, it is more a helper class
 which computes the corrector step in the Adams-Bashforth-Moulton method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4_classic.hpp>

#include <boost/numeric/odeint/stepper/detail/adams_moulton_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/adams_moulton_coefficients.hpp>
#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>




namespace boost {
namespace numeric {
namespace odeint {


/*
 * Static implicit Adams-Moulton multistep-solver without step size control and without dense output.
 */
template<
size_t Steps ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class adams_moulton
{
private:


public :

    typedef State state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef adams_moulton< Steps , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;

    static const size_t steps = Steps;

    typedef unsigned short order_type;
    static const order_type order_value = steps + 1;

    typedef detail::rotating_buffer< wrapped_deriv_type , steps > step_storage_type;

    adams_moulton( )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( m_algebra_instance )
    { }

    adams_moulton( algebra_type &algebra )
    : m_coefficients() , m_dxdt() , m_resizer() ,
      m_algebra_instance() , m_algebra( algebra )
    { }

    adams_moulton& operator=( const adams_moulton &stepper )
    {
        m_dxdt = stepper.m_dxdt;
        m_resizer = stepper.m_resizer;
        m_algebra = stepper.m_algebra;
        return *this;
    }

    order_type order( void ) const { return order_value; }


    /*
     * Version 1 : do_step( system , x , t , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }

    template< class System , class StateInOut , class StateIn , class ABBuf >
    void do_step( System system , const StateInOut &x , StateIn const & pred , time_type t , time_type dt , const ABBuf &buf )
    {
        do_step( system , x , pred , t , x , dt , buf );
    }



    /*
     * Version 2 : do_step( system , in , t , out , dt , buf );
     *
     * solves the forwarding problem
     */
    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }

    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step( System system , const StateIn &in , const PredIn &pred , time_type t , const StateOut &out , time_type dt , const ABBuf &buf )
    {
        do_step_impl( system , in , pred , t , out , dt , buf );
    }



    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }

    algebra_type& algebra()
    {   return m_algebra; }

    const algebra_type& algebra() const
    {   return m_algebra; }


private:


    template< class System , class StateIn , class PredIn , class StateOut , class ABBuf >
    void do_step_impl( System system , const StateIn &in , const PredIn &pred , time_type t , StateOut &out , time_type dt , const ABBuf &buf )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( pred , m_dxdt.m_v , t );
        detail::adams_moulton_call_algebra< steps , algebra_type , operations_type >()( m_algebra , in , out , m_dxdt.m_v , buf , m_coefficients , dt );
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }


    const detail::adams_moulton_coefficients< value_type , steps > m_coefficients;
    wrapped_deriv_type m_dxdt;
    resizer_type m_resizer;

protected:

    algebra_type m_algebra_instance;
    algebra_type &m_algebra;
};




} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_MOULTON_HPP_INCLUDED

/* adams_moulton.hpp
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
*/