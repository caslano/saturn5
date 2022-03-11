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