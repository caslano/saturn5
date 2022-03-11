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