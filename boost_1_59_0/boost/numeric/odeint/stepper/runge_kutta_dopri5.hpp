/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta_dopri5.hpp

 [begin_description]
 Implementation of the Dormand-Prince 5(4) method. This stepper can also be used with the dense-output controlled stepper.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_fsal_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/same_instance.hpp>

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
class runge_kutta_dopri5
#ifndef DOXYGEN_SKIP
: public explicit_error_stepper_fsal_base<
  runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
: public explicit_error_stepper_fsal_base
#endif
{

public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_fsal_base<
    runge_kutta_dopri5< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_error_stepper_fsal_base< runge_kutta_dopri5< ... > , ... > stepper_base_type;
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


    runge_kutta_dopri5( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t ,
            StateOut &out , DerivOut &dxdt_out , time_type dt )
    {
        const value_type a2 = static_cast<value_type> ( 1 ) / static_cast<value_type>( 5 );
        const value_type a3 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type a4 = static_cast<value_type> ( 4 ) / static_cast<value_type> ( 5 );
        const value_type a5 = static_cast<value_type> ( 8 )/static_cast<value_type> ( 9 );

        const value_type b21 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );

        const value_type b31 = static_cast<value_type> ( 3 ) / static_cast<value_type>( 40 );
        const value_type b32 = static_cast<value_type> ( 9 ) / static_cast<value_type>( 40 );

        const value_type b41 = static_cast<value_type> ( 44 ) / static_cast<value_type> ( 45 );
        const value_type b42 = static_cast<value_type> ( -56 ) / static_cast<value_type> ( 15 );
        const value_type b43 = static_cast<value_type> ( 32 ) / static_cast<value_type> ( 9 );

        const value_type b51 = static_cast<value_type> ( 19372 ) / static_cast<value_type>( 6561 );
        const value_type b52 = static_cast<value_type> ( -25360 ) / static_cast<value_type> ( 2187 );
        const value_type b53 = static_cast<value_type> ( 64448 ) / static_cast<value_type>( 6561 );
        const value_type b54 = static_cast<value_type> ( -212 ) / static_cast<value_type>( 729 );

        const value_type b61 = static_cast<value_type> ( 9017 ) / static_cast<value_type>( 3168 );
        const value_type b62 = static_cast<value_type> ( -355 ) / static_cast<value_type>( 33 );
        const value_type b63 = static_cast<value_type> ( 46732 ) / static_cast<value_type>( 5247 );
        const value_type b64 = static_cast<value_type> ( 49 ) / static_cast<value_type>( 176 );
        const value_type b65 = static_cast<value_type> ( -5103 ) / static_cast<value_type>( 18656 );

        const value_type c1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type c3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type c5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type c6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        m_k_x_tmp_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_k_x_tmp_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        //m_x_tmp = x + dt*b21*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt_in ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

        sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
        // m_x_tmp = x + dt*b31*dxdt + dt*b32*m_k2
        stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v ,
                typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

        sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
        // m_x_tmp = x + dt * (b41*dxdt + b42*m_k2 + b43*m_k3)
        stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v ,
                typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

        sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
        stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

        sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
        stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt_in , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

        sys( m_x_tmp.m_v , m_k6.m_v , t + dt );
        stepper_base_type::m_algebra.for_each7( out , in , dxdt_in , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c5 , dt*c6 ));

        // the new derivative
        sys( out , dxdt_out , t + dt );
    }



    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t ,
            StateOut &out , DerivOut &dxdt_out , time_type dt , Err &xerr )
    {
        const value_type c1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type c3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type c5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type c6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        const value_type dc1 = c1 - static_cast<value_type> ( 5179 ) / static_cast<value_type>( 57600 );
        const value_type dc3 = c3 - static_cast<value_type> ( 7571 ) / static_cast<value_type>( 16695 );
        const value_type dc4 = c4 - static_cast<value_type> ( 393 ) / static_cast<value_type>( 640 );
        const value_type dc5 = c5 - static_cast<value_type> ( -92097 ) / static_cast<value_type>( 339200 );
        const value_type dc6 = c6 - static_cast<value_type> ( 187 ) / static_cast<value_type>( 2100 );
        const value_type dc7 = static_cast<value_type>( -1 ) / static_cast<value_type> ( 40 );

        /* ToDo: copy only if &dxdt_in == &dxdt_out ? */
        if( same_instance( dxdt_in , dxdt_out ) )
        {
            m_dxdt_tmp_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_dxdt_tmp_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
            boost::numeric::odeint::copy( dxdt_in , m_dxdt_tmp.m_v );
            do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt );
            //error estimate
            stepper_base_type::m_algebra.for_each7( xerr , m_dxdt_tmp.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , dxdt_out ,
                                                    typename operations_type::template scale_sum6< time_type , time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 , dt*dc7 ) );

        }
        else
        {
            do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt );
            //error estimate
            stepper_base_type::m_algebra.for_each7( xerr , dxdt_in , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , dxdt_out ,
                                                    typename operations_type::template scale_sum6< time_type , time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 , dt*dc7 ) );
        
        }

    }


    /*
     * Calculates Dense-Output for Dopri5
     *
     * See Hairer, Norsett, Wanner: Solving Ordinary Differential Equations, Nonstiff Problems. I, p.191/192
     *
     * y(t+theta) = y(t) + h * sum_i^7 b_i(theta) * k_i
     *
     * A = theta^2 * ( 3 - 2 theta )
     * B = theta^2 * ( theta - 1 )
     * C = theta^2 * ( theta - 1 )^2
     * D = theta   * ( theta - 1 )^2
     *
     * b_1( theta ) = A * b_1 - C * X1( theta ) + D
     * b_2( theta ) = 0
     * b_3( theta ) = A * b_3 + C * X3( theta )
     * b_4( theta ) = A * b_4 - C * X4( theta )
     * b_5( theta ) = A * b_5 + C * X5( theta )
     * b_6( theta ) = A * b_6 - C * X6( theta )
     * b_7( theta ) = B + C * X7( theta )
     *
     * An alternative Method is described in:
     *
     * www-m2.ma.tum.de/homepages/simeon/numerik3/kap3.ps
     */
    template< class StateOut , class StateIn1 , class DerivIn1 , class StateIn2 , class DerivIn2 >
    void calc_state( time_type t , StateOut &x ,
                     const StateIn1 &x_old , const DerivIn1 &deriv_old , time_type t_old ,
                     const StateIn2 & /* x_new */ , const DerivIn2 &deriv_new , time_type t_new ) const
    {
        const value_type b1 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 384 );
        const value_type b3 = static_cast<value_type> ( 500 ) / static_cast<value_type>( 1113 );
        const value_type b4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 192 );
        const value_type b5 = static_cast<value_type> ( -2187 ) / static_cast<value_type>( 6784 );
        const value_type b6 = static_cast<value_type> ( 11 ) / static_cast<value_type>( 84 );

        const time_type dt = ( t_new - t_old );
        const value_type theta = ( t - t_old ) / dt;
        const value_type X1 = static_cast< value_type >( 5 ) * ( static_cast< value_type >( 2558722523LL ) - static_cast< value_type >( 31403016 ) * theta ) / static_cast< value_type >( 11282082432LL );
        const value_type X3 = static_cast< value_type >( 100 ) * ( static_cast< value_type >( 882725551 ) - static_cast< value_type >( 15701508 ) * theta ) / static_cast< value_type >( 32700410799LL );
        const value_type X4 = static_cast< value_type >( 25 ) * ( static_cast< value_type >( 443332067 ) - static_cast< value_type >( 31403016 ) * theta ) / static_cast< value_type >( 1880347072LL ) ;
        const value_type X5 = static_cast< value_type >( 32805 ) * ( static_cast< value_type >( 23143187 ) - static_cast< value_type >( 3489224 ) * theta ) / static_cast< value_type >( 199316789632LL );
        const value_type X6 = static_cast< value_type >( 55 ) * ( static_cast< value_type >( 29972135 ) - static_cast< value_type >( 7076736 ) * theta ) / static_cast< value_type >( 822651844 );
        const value_type X7 = static_cast< value_type >( 10 ) * ( static_cast< value_type >( 7414447 ) - static_cast< value_type >( 829305 ) * theta ) / static_cast< value_type >( 29380423 );

        const value_type theta_m_1 = theta - static_cast< value_type >( 1 );
        const value_type theta_sq = theta * theta;
        const value_type A = theta_sq * ( static_cast< value_type >( 3 ) - static_cast< value_type >( 2 ) * theta );
        const value_type B = theta_sq * theta_m_1;
        const value_type C = theta_sq * theta_m_1 * theta_m_1;
        const value_type D = theta * theta_m_1 * theta_m_1;

        const value_type b1_theta = A * b1 - C * X1 + D;
        const value_type b3_theta = A * b3 + C * X3;
        const value_type b4_theta = A * b4 - C * X4;
        const value_type b5_theta = A * b5 + C * X5;
        const value_type b6_theta = A * b6 - C * X6;
        const value_type b7_theta = B + C * X7;

        // const state_type &k1 = *m_old_deriv;
        // const state_type &k3 = dopri5().m_k3;
        // const state_type &k4 = dopri5().m_k4;
        // const state_type &k5 = dopri5().m_k5;
        // const state_type &k6 = dopri5().m_k6;
        // const state_type &k7 = *m_current_deriv;

        stepper_base_type::m_algebra.for_each8( x , x_old , deriv_old , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v , deriv_new ,
                typename operations_type::template scale_sum7< value_type , time_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt * b1_theta , dt * b3_theta , dt * b4_theta , dt * b5_theta , dt * b6_theta , dt * b7_theta ) );
    }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_k_x_tmp_impl( x );
        resize_dxdt_tmp_impl( x );
        stepper_base_type::adjust_size( x );
    }
    

private:

    template< class StateIn >
    bool resize_k_x_tmp_impl( const StateIn &x )
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

    template< class StateIn >
    bool resize_dxdt_tmp_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt_tmp , x , typename is_resizeable<deriv_type>::type() );
    }
        


    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_k2 , m_k3 , m_k4 , m_k5 , m_k6 ;
    wrapped_deriv_type m_dxdt_tmp;
    resizer_type m_k_x_tmp_resizer;
    resizer_type m_dxdt_tmp_resizer;
};



/************* DOXYGEN ************/
/**
 * \class runge_kutta_dopri5
 * \brief The Runge-Kutta Dormand-Prince 5 method.
 *
 * The Runge-Kutta Dormand-Prince 5 method is a very popular method for solving ODEs, see
 * <a href=""></a>.
 * The method is explicit and fulfills the Error Stepper concept. Step size control
 * is provided but continuous output is available which make this method favourable for many applications. 
 * 
 * This class derives from explicit_error_stepper_fsal_base and inherits its interface via CRTP (current recurring
 * template pattern). The method possesses the FSAL (first-same-as-last) property. See
 * explicit_error_stepper_fsal_base for more details.
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
     * \fn runge_kutta_dopri5::runge_kutta_dopri5( const algebra_type &algebra )
     * \brief Constructs the runge_kutta_dopri5 class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

    /**
     * \fn runge_kutta_dopri5::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t , StateOut &out , DerivOut &dxdt_out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt_in` of `in` at the time `t` is passed to the
     * method. The result is updated out-of-place, hence the input is in `in` and the output in `out`. Furthermore,
     * the derivative is update out-of-place, hence the input is assumed to be in `dxdt_in` and the output in
     * `dxdt_out`. 
     * Access to this step functionality is provided by explicit_error_stepper_fsal_base and 
     * `do_step_impl` should not be called directly.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt_in The derivative of x at t. dxdt_in is not modified by this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dxdt_out The result of the new derivative at time t+dt.
     * \param dt The step size.
     */

    /**
     * \fn runge_kutta_dopri5::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t , StateOut &out , DerivOut &dxdt_out , time_type dt , Err &xerr )
     * \brief This method performs one step. The derivative `dxdt_in` of `in` at the time `t` is passed to the
     * method. The result is updated out-of-place, hence the input is in `in` and the output in `out`. Furthermore,
     * the derivative is update out-of-place, hence the input is assumed to be in `dxdt_in` and the output in
     * `dxdt_out`. 
     * Access to this step functionality is provided by explicit_error_stepper_fsal_base and 
     * `do_step_impl` should not be called directly.
     * An estimation of the error is calculated.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt_in The derivative of x at t. dxdt_in is not modified by this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dxdt_out The result of the new derivative at time t+dt.
     * \param dt The step size.
     * \param xerr An estimation of the error.
     */

    /**
     * \fn runge_kutta_dopri5::calc_state( time_type t , StateOut &x , const StateIn1 &x_old , const DerivIn1 &deriv_old , time_type t_old , const StateIn2 &  , const DerivIn2 &deriv_new , time_type t_new ) const
     * \brief This method is used for continuous output and it calculates the state `x` at a time `t` from the 
     * knowledge of two states `old_state` and `current_state` at time points `t_old` and `t_new`. It also uses
     * internal variables to calculate the result. Hence this method must be called after two successful `do_step`
     * calls.
     */

    /**
     * \fn runge_kutta_dopri5::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_DOPRI5_HPP_INCLUDED

/* runge_kutta_dopri5.hpp
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
*/