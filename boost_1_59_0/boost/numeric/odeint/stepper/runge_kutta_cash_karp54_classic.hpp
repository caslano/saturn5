/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp

 [begin_description]
 Classical implementation of the Runge-Kutta Cash-Karp 5(4) method.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
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
class runge_kutta_cash_karp54_classic
: public explicit_error_stepper_base<
  runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class runge_kutta_cash_karp54_classic : public explicit_error_stepper_base
#endif 
{


public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_base<
    runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_error_stepper_base< runge_kutta_cash_karp54_classic< ... > , ... > stepper_base_type;
    #endif

    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;

    #ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::stepper_type stepper_type;
    #endif


    runge_kutta_cash_karp54_classic( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        const value_type dc1 = c1 - static_cast<value_type> ( 2825 ) / static_cast<value_type>( 27648 );
        const value_type dc3 = c3 - static_cast<value_type> ( 18575 ) / static_cast<value_type>( 48384 );
        const value_type dc4 = c4 - static_cast<value_type> ( 13525 ) / static_cast<value_type>( 55296 );
        const value_type dc5 = static_cast<value_type> ( -277 ) / static_cast<value_type>( 14336 );
        const value_type dc6 = c6 - static_cast<value_type> ( 1 ) / static_cast<value_type> ( 4 );

        do_step_impl( system , in , dxdt , t , out , dt );

        //error estimate
        stepper_base_type::m_algebra.for_each6( xerr , dxdt , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 ));

    }



    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        const value_type a2 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type a3 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type a4 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 5 );
        const value_type a5 = static_cast<value_type> ( 1 );
        const value_type a6 = static_cast<value_type> ( 7 ) / static_cast<value_type> ( 8 );

        const value_type b21 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type b31 = static_cast<value_type> ( 3 ) / static_cast<value_type>( 40 );
        const value_type b32 = static_cast<value_type> ( 9 ) / static_cast<value_type>( 40 );
        const value_type b41 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type b42 = static_cast<value_type> ( -9 ) / static_cast<value_type> ( 10 );
        const value_type b43 = static_cast<value_type> ( 6 ) / static_cast<value_type> ( 5 );
        const value_type b51 = static_cast<value_type> ( -11 ) / static_cast<value_type>( 54 );
        const value_type b52 = static_cast<value_type> ( 5 ) / static_cast<value_type> ( 2 );
        const value_type b53 = static_cast<value_type> ( -70 ) / static_cast<value_type>( 27 );
        const value_type b54 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 27 );
        const value_type b61 = static_cast<value_type> ( 1631 ) / static_cast<value_type>( 55296 );
        const value_type b62 = static_cast<value_type> ( 175 ) / static_cast<value_type>( 512 );
        const value_type b63 = static_cast<value_type> ( 575 ) / static_cast<value_type>( 13824 );
        const value_type b64 = static_cast<value_type> ( 44275 ) / static_cast<value_type>( 110592 );
        const value_type b65 = static_cast<value_type> ( 253 ) / static_cast<value_type>( 4096 );

        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        //m_x1 = x + dt*b21*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

        sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
        // m_x_tmp = x + dt*b31*dxdt + dt*b32*m_x2
        stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt , m_k2.m_v ,
                typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

        sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
        // m_x_tmp = x + dt * (b41*dxdt + b42*m_x2 + b43*m_x3)
        stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v ,
                typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

        sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
        stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

        sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
        stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

        sys( m_x_tmp.m_v , m_k6.m_v , t + dt*a6 );
        stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_k3.m_v , m_k4.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c6 ));

    }

    /**
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */
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
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_k2 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k3 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k4 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k5 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k6 , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_k2, m_k3, m_k4, m_k5, m_k6;
    resizer_type m_resizer;

};



/************ DOXYGEN *************/

/**
 * \class runge_kutta_cash_karp54_classic
 * \brief The Runge-Kutta Cash-Karp method implemented without the generic Runge-Kutta algorithm.
 *
 * The Runge-Kutta Cash-Karp method is one of the standard methods for
 * solving ordinary differential equations, see
 * <a href="http://en.wikipedia.org/wiki/Cash%E2%80%93Karp_method">en.wikipedia.org/wiki/Cash-Karp_method</a>.
 * The method is explicit and fulfills the Error Stepper concept. Step size control
 * is provided but continuous output is not available for this method.
 * 
 * This class derives from explicit_error_stepper_base and inherits its interface via CRTP (current recurring
 * template pattern). This class implements the method directly, hence the generic Runge-Kutta algorithm is not used.
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
     * \fn runge_kutta_cash_karp54_classic::runge_kutta_cash_karp54_classic( const algebra_type &algebra )
     * \brief Constructs the runge_kutta_cash_karp54_classic class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn runge_kutta_cash_karp54_classic::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     *
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`. Futhermore, an
     * estimation of the error is stored in `xerr`. 
     * Access to this step functionality is provided by explicit_error_stepper_base and 
     * `do_step_impl` should not be called directly.

     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     * \param xerr The result of the error estimation is written in xerr.
     */

    /**
     * \fn runge_kutta_cash_karp54_classic::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_error_stepper_base and 
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

} // odeint
} // numeric
} // boost




#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

/* runge_kutta_cash_karp54_classic.hpp
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
*/