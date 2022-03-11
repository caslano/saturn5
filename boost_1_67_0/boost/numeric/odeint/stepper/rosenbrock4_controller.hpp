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