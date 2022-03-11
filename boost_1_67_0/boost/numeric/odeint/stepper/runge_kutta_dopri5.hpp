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