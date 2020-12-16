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
3j9fp6t+bdWeS33stK+g9W+r5vNfLAFatrguQrnO4FhKpHNrYnJu/FM+yePUza2ZeX4+T7G+Hmxhnp/X59Tjj1bm+WH5+vm2Ns/PLhtfW/P8rJWeUh2/9jpbs9LIzMPn4uE7qLpPKWjdNbQJgjZAoRkfS4E+TnYOZW599X7eJQR+5VV63V8aCj+vT8evWwj8ZLZxWQj8SLc6fj1D4RddpePXOwR+7vzxOn5RIfArqdDbS98Q+Dkl9tIvFH5er45f/xD4OZwFOn4DQ+EXrdff5SHws5d6dOO7IgR+pFYdv6Hm+JUHw7ZxZvkFwbYJZvkFwSVJ5vjlT1K25iW1RrIuV+RdREeWLwVnpwnaNYLWTkPLV2ngU2gGx+JweSW6T9WNpUjI2K6RO52fP+OrNbT0WtZcE4u8JR63uyRvosfqKKRho9NDpk72nIuQyab1B/DOMCHHfwZZZ6/ZOjnzhJxDYaqc7rWQU0HjRq+/UTreC+HdqCNS4XeVoK0QtGYa2lqVBr6EVsu1rHDxl/07l9ROr9aN5Q1keJCRFME5NUMyxGc6XV5zmoxeteYn68dfa5KXLKbn6+Yez/o+gEMxfUtuLecOWrE68tVv+vE6dTLsyDiFjGILliBoLkG7QEMrFbRKDc0raI9raJUqDXwIrZb2X+7jr7WSE3IFdDfKq/R+VqIb92Ih50J4jxa0ZYJ2s4a2XNCyNLSVgmbV0F4QtIEKzdC4vT6PGLt+3L7GRvs8AZ74iLTnXaHTRUxHdey3wXusYTk+Ts3JfLFKJ2cKcgZdTCUI73GG5Xi87EBJ5jPZrI6cE4Lq6IYQeAYb542Gfd3PUxo3bjbJSxY3bjGc2/28gu5r/NUkP5uvLErG7zZ9XMNWX7KAIurQb6veuxW09SMCtBGCtkuh1XYsRV5O4HKmy1UmWcM7jduF4OdR/yPhOdO4vlSeNMbLJNjqHp2+nOjh3S5qX85RSxm+cpu9WP1XMuZZOhmPISP8EuU8F1lC0J4WtE4a2lpBG6KhbVRp2CW02o7P61G+RPWvO39iWKfV/PA2Cb+HdPPt0Bkpl6g5oLC2Mopsyle/qGjpGRWdjL6qDPARvWZjMqL7xcpkLNDJiEOGm3eb/u6XodIS/HLVdXMZkxslx7lP6uRmIKM3IH6eCRlWqd0v0cnIQsberqqtFddWhtPp8P9jdRfo4+4y43ZVw89p1/N7JgR+dsn4lofCL9+u4/ec4TxTw0/Ha6VufSazPl6AXh94egTtRkFrqNBqOQevz6Z8WasG9o0q1MldbVgnWn56O1tjmh+fSGLLOvP8QF768b1snp/N7dPze8U0P49Phq02mufnleXk1/T1JzZUvwcdePhOrN4jgjYVwhiFZlRuqbO8SGdXb5mfR3GUZB5vm+bn5iP9um0xz8/m9Oj5bTXNr6yiRDK+beb5SeP/e6b5Kcur5/eBaX5yDPGhaX6cQpPw+8g0P6oA2dkW0/wcTo9Xr79PTPOzez0SDPGpeX5FMgz7uS5uXEttmsdh+W/hO6263yhoJxSaQblUNJL88YXpedikcehL3TxmMuY4kmpb+N5ayzrF6/I4Sx153lKHgq6k51gM1z4angoslJ1j0Y39Yca+j7E3h/f02urHHqN8+U+j6/X9rXF9q/w4QWmXjPmobsxPMuY3olR9z6i1jGjlC5AZG6Mf8/cmxuznZ5fz+8EsvyA6PWGaHyhYotOfTPMDtUr4/WKcn60MS+UfNiz0e++/6dZ868Vqb6FzBBW3oL0HzdKA3dNwaEblKh2HM+XSKjM9D2tlqX6fOLyJYR+u4VdR5qqSxYU6TXTPFKCHv/RV8dcsw+OW9bvOCUEPsp7XuaHwK9TXNg0=
*/