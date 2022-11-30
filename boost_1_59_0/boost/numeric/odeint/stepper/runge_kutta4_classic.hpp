/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta4_classic.hpp

 [begin_description]
 Implementation for the classical Runge Kutta stepper.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_CLASSIC_HPP_INCLUDED



#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

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
class runge_kutta4_classic
: public explicit_stepper_base<
  runge_kutta4_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  4 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class runge_kutta4_classic : public explicit_stepper_base
#endif
{

public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_stepper_base<
    runge_kutta4_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    4 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_stepper_base< runge_kutta4_classic< ... > , ... > stepper_base_type;
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
    #endif // DOXYGEN_SKIP



    runge_kutta4_classic( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        // ToDo : check if size of in,dxdt,out are equal?

        static const value_type val1 = static_cast< value_type >( 1 );

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        typename odeint::unwrap_reference< System >::type &sys = system;

        const time_type dh = dt / static_cast< value_type >( 2 );
        const time_type th = t + dh;

        // dt * dxdt = k1
        // m_x_tmp = x + dh*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dh ) );


        // dt * m_dxt = k2
        sys( m_x_tmp.m_v , m_dxt.m_v , th );

        // m_x_tmp = x + dh*m_dxt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , m_dxt.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dh ) );


        // dt * m_dxm = k3
        sys( m_x_tmp.m_v , m_dxm.m_v , th );
        //m_x_tmp = x + dt*m_dxm
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , m_dxm.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( val1 , dt ) );


        // dt * m_dxh = k4
        sys( m_x_tmp.m_v , m_dxh.m_v , t + dt );

        //x += dt/6 * ( m_dxdt + m_dxt + val2*m_dxm )
        time_type dt6 = dt / static_cast< value_type >( 6 );
        time_type dt3 = dt / static_cast< value_type >( 3 );
        stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_dxt.m_v , m_dxm.m_v , m_dxh.m_v ,
                                             typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt6 , dt3 , dt3 , dt6 ) );
        
        // x += dt/6 * m_dxdt + dt/3 * m_dxt )
        // stepper_base_type::m_algebra.for_each4( out , in , dxdt , m_dxt.m_v , 
        //                                         typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt6 , dt3 ) ); 
        // // x += dt/3 * m_dxm + dt/6 * m_dxh )
        // stepper_base_type::m_algebra.for_each4( out , out , m_dxm.m_v , m_dxh.m_v , 
        //                                         typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt3 , dt6 ) ); 

    }

    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }

private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxm , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxt , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxh , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    resizer_type m_resizer;

    wrapped_deriv_type m_dxt;
    wrapped_deriv_type m_dxm;
    wrapped_deriv_type m_dxh;
    wrapped_state_type m_x_tmp;

};


/********* DOXYGEN *********/

/**
 * \class runge_kutta4_classic
 * \brief The classical Runge-Kutta stepper of fourth order.
 *
 * The Runge-Kutta method of fourth order is one standard method for
 * solving ordinary differential equations and is widely used, see also
 * <a href="http://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods">en.wikipedia.org/wiki/Runge-Kutta_methods</a>
 * The method is explicit and fulfills the Stepper concept. Step size control
 * or continuous output are not provided.  This class implements the method directly, hence the 
 * generic Runge-Kutta algorithm is not used.
 * 
 * This class derives from explicit_stepper_base and inherits its interface via
 * CRTP (current recurring template pattern). For more details see
 * explicit_stepper_base.
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
     * \fn runge_kutta4_classic::runge_kutta4_classic( const algebra_type &algebra )
     * \brief Constructs the runge_kutta4_classic class. This constructor can be used as a default
     * constructor if the algebra has a default constructor. 
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn runge_kutta4_classic::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out of place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_stepper_base and 
     * `do_step_impl` should not be called directly.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn runge_kutta4_classic::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_CLASSIC_HPP_INCLUDED

/* runge_kutta4_classic.hpp
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
*/