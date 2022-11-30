/*
 [auto_generated]
 boost/numeric/odeint/stepper/rosenbrock4_controller.hpp

 [begin_description]
 Controller for the Rosenbrock4 method.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_CONTROLLER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_CONTROLLER_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/util/copy.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/detail/less_with_sign.hpp>

#include <boost/numeric/odeint/stepper/rosenbrock4.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class Stepper >
class rosenbrock4_controller
{
private:


public:

    typedef Stepper stepper_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_type::resizer_type resizer_type;
    typedef controlled_stepper_tag stepper_category;

    typedef rosenbrock4_controller< Stepper > controller_type;


    rosenbrock4_controller( value_type atol = 1.0e-6 , value_type rtol = 1.0e-6 ,
                            const stepper_type &stepper = stepper_type() )
        : m_stepper( stepper ) , m_atol( atol ) , m_rtol( rtol ) ,
          m_max_dt( static_cast<time_type>(0) ) ,
          m_first_step( true ) , m_err_old( 0.0 ) , m_dt_old( 0.0 ) ,
          m_last_rejected( false )
    { }

    rosenbrock4_controller( value_type atol, value_type rtol, time_type max_dt,
                            const stepper_type &stepper = stepper_type() )
            : m_stepper( stepper ) , m_atol( atol ) , m_rtol( rtol ) , m_max_dt( max_dt ) ,
              m_first_step( true ) , m_err_old( 0.0 ) , m_dt_old( 0.0 ) ,
              m_last_rejected( false )
    { }

    value_type error( const state_type &x , const state_type &xold , const state_type &xerr )
    {
        BOOST_USING_STD_MAX();
        using std::abs;
        using std::sqrt;
        
        const size_t n = x.size();
        value_type err = 0.0 , sk = 0.0;
        for( size_t i=0 ; i<n ; ++i )
        {
            sk = m_atol + m_rtol * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( xold[i] ) , abs( x[i] ) );
            err += xerr[i] * xerr[i] / sk / sk;
        }
        return sqrt( err / value_type( n ) );
    }

    value_type last_error( void ) const
    {
        return m_err_old;
    }




    template< class System >
    boost::numeric::odeint::controlled_step_result
    try_step( System sys , state_type &x , time_type &t , time_type &dt )
    {
        m_xnew_resizer.adjust_size( x , detail::bind( &controller_type::template resize_m_xnew< state_type > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::controlled_step_result res = try_step( sys , x , t , m_xnew.m_v , dt );
        if( res == success )
        {
            boost::numeric::odeint::copy( m_xnew.m_v , x );
        }
        return res;
    }


    template< class System >
    boost::numeric::odeint::controlled_step_result
    try_step( System sys , const state_type &x , time_type &t , state_type &xout , time_type &dt )
    {
        if( m_max_dt != static_cast<time_type>(0) && detail::less_with_sign(m_max_dt, dt, dt) )
        {
            // given step size is bigger then max_dt
            // set limit and return fail
            dt = m_max_dt;
            return fail;
        }

        BOOST_USING_STD_MIN();
        BOOST_USING_STD_MAX();
        using std::pow;

        static const value_type safe = 0.9 , fac1 = 5.0 , fac2 = 1.0 / 6.0;

        m_xerr_resizer.adjust_size( x , detail::bind( &controller_type::template resize_m_xerr< state_type > , detail::ref( *this ) , detail::_1 ) );

        m_stepper.do_step( sys , x , t , xout , dt , m_xerr.m_v );
        value_type err = error( xout , x , m_xerr.m_v );

        value_type fac = max BOOST_PREVENT_MACRO_SUBSTITUTION (
            fac2 , min BOOST_PREVENT_MACRO_SUBSTITUTION (
                fac1 ,
                static_cast< value_type >( pow( err , 0.25 ) / safe ) ) );
        value_type dt_new = dt / fac;
        if ( err <= 1.0 )
        {
            if( m_first_step )
            {
                m_first_step = false;
            }
            else
            {
                value_type fac_pred = ( m_dt_old / dt ) * pow( err * err / m_err_old , 0.25 ) / safe;
                fac_pred = max BOOST_PREVENT_MACRO_SUBSTITUTION (
                    fac2 , min BOOST_PREVENT_MACRO_SUBSTITUTION ( fac1 , fac_pred ) );
                fac = max BOOST_PREVENT_MACRO_SUBSTITUTION ( fac , fac_pred );
                dt_new = dt / fac;
            }

            m_dt_old = dt;
            m_err_old = max BOOST_PREVENT_MACRO_SUBSTITUTION ( static_cast< value_type >( 0.01 ) , err );
            if( m_last_rejected )
                dt_new = ( dt >= 0.0 ?
                min BOOST_PREVENT_MACRO_SUBSTITUTION ( dt_new , dt ) :
                max BOOST_PREVENT_MACRO_SUBSTITUTION ( dt_new , dt ) );
            t += dt;
            // limit step size to max_dt
            if( m_max_dt != static_cast<time_type>(0) )
            {
                dt = detail::min_abs(m_max_dt, dt_new);
            } else {
                dt = dt_new;
            }
            m_last_rejected = false;
            return success;
        }
        else
        {
            dt = dt_new;
            m_last_rejected = true;
            return fail;
        }
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_m_xerr( x );
        resize_m_xnew( x );
    }



    stepper_type& stepper( void )
    {
        return m_stepper;
    }

    const stepper_type& stepper( void ) const
    {
        return m_stepper;
    }




protected:

    template< class StateIn >
    bool resize_m_xerr( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xerr , x , typename is_resizeable<state_type>::type() );
    }

    template< class StateIn >
    bool resize_m_xnew( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_xnew , x , typename is_resizeable<state_type>::type() );
    }


    stepper_type m_stepper;
    resizer_type m_xerr_resizer;
    resizer_type m_xnew_resizer;
    wrapped_state_type m_xerr;
    wrapped_state_type m_xnew;
    value_type m_atol , m_rtol;
    time_type m_max_dt;
    bool m_first_step;
    value_type m_err_old , m_dt_old;
    bool m_last_rejected;
};






} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_CONTROLLER_HPP_INCLUDED

/* rosenbrock4_controller.hpp
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
*/