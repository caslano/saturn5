/*
 [auto_generated]
 boost/numeric/odeint/stepper/rosenbrock4_dense_output.hpp

 [begin_description]
 Dense output for Rosenbrock 4.
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED


#include <utility>

#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/rosenbrock4_controller.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>

#include <boost/numeric/odeint/integrate/max_step_checker.hpp>


namespace boost {
namespace numeric {
namespace odeint {

template< class ControlledStepper >
class rosenbrock4_dense_output
{

public:

    typedef ControlledStepper controlled_stepper_type;
    typedef typename unwrap_reference< controlled_stepper_type >::type unwrapped_controlled_stepper_type;
    typedef typename unwrapped_controlled_stepper_type::stepper_type stepper_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_type::resizer_type resizer_type;
    typedef dense_output_stepper_tag stepper_category;

    typedef rosenbrock4_dense_output< ControlledStepper > dense_output_stepper_type;

    rosenbrock4_dense_output( const controlled_stepper_type &stepper = controlled_stepper_type() )
    : m_stepper( stepper ) , 
      m_x1() , m_x2() , 
      m_current_state_x1( true ) ,
      m_t() , m_t_old() , m_dt()
    {
    }



    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &dense_output_stepper_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        get_current_state() = x0;
        m_t = t0;
        m_dt = dt0;
    }

    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
        controlled_step_result res = fail;
        m_t_old = m_t;
        do
        {
            res = stepper.try_step( system , get_current_state() , m_t , get_old_state() , m_dt );
            fail_checker();  // check for overflow of failed steps
        }
        while( res == fail );
        stepper.stepper().prepare_dense_output();
        this->toggle_current_state();
        return std::make_pair( m_t_old , m_t );
    }


    /*
     * The two overloads are needed in order to solve the forwarding problem.
     */
    template< class StateOut >
    void calc_state( time_type t , StateOut &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.stepper().calc_state( t , x , get_old_state() , m_t_old , get_current_state() , m_t );
    }

    template< class StateOut >
    void calc_state( time_type t , const StateOut &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.stepper().calc_state( t , x , get_old_state() , m_t_old , get_current_state() , m_t );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        unwrapped_controlled_stepper_type &stepper = m_stepper;
        stepper.adjust_size( x );
        resize_impl( x );
    }




    const state_type& current_state( void ) const
    {
        return get_current_state();
    }

    time_type current_time( void ) const
    {
        return m_t;
    }

    const state_type& previous_state( void ) const
    {
        return get_old_state();
    }

    time_type previous_time( void ) const
    {
        return m_t_old;
    }

    time_type current_time_step( void ) const
    {
        return m_dt;
    }




private:

    state_type& get_current_state( void )
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    const state_type& get_current_state( void ) const
    {
        return m_current_state_x1 ? m_x1.m_v : m_x2.m_v ;
    }
    
    state_type& get_old_state( void )
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }
    
    const state_type& get_old_state( void ) const
    {
        return m_current_state_x1 ? m_x2.m_v : m_x1.m_v ;
    }

    void toggle_current_state( void )
    {
        m_current_state_x1 = ! m_current_state_x1;
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x2 , x , typename is_resizeable<state_type>::type() );
        return resized;
    }


    controlled_stepper_type m_stepper;
    resizer_type m_resizer;
    wrapped_state_type m_x1 , m_x2;
    bool m_current_state_x1;
    time_type m_t , m_t_old , m_dt;
};



} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_ROSENBROCK4_DENSE_OUTPUT_HPP_INCLUDED

/* rosenbrock4_dense_output.hpp
zPEjMCrf9f51vk6n53YBt8aoz2nMEbRmKo1YCa2W68lB6ElRffv0q/mPbi6NDduIp9ju66/+i7JlNtLUNM/+Vl+pS3oOrHkIPGEpzXEtDa9jDU+p3V4Ywhgdble5bIxtQuDJXrZ0fdo10eW0LurZwD3hdKaMywnSy+1gUr/5LrcVvjr9djKli6hovkVFB7HVi03zjIpmQ0G6L3mJTr/t6K+t6I8/w/txQeuo0ui7QTMu25dvK5T4SfdQ5uMZIPWTHqHxlJ7/76XTUYKqD87P0kEUtGRBi9TQUi5Rzyq2C4NmfDxlHpusT9E3lDmWYggSnv1C4VnskvZT+ofEU/5MwsBQeLrKXDKsf3koPB1Ou6xmvSIUnnavNL4ODY2nRzb3uFB4ErRlc08IiadPumebFBJPh9Svk43HfGdpnqeyuKBUuj4p5vg5S61VtgrJ2YCR5vlxrkjPL800P3k/N8M0P4+0drsqBH4DJHaYbZqfm26Gnl+uaX7yvtto0/yUJ1T1+htrmp+873a1Lu85LlXz2QXks7UGZXD4XiLjGp2M1ciYcwU72vBdV/18hKB9qKGtEzSvhvayoEVqaK8J2vUa2huCtllDe0vQ2mhoWwQtX6HVcr5uu8+jPAHHd0mvukg33/f8MtT96fWCtkPQBmtou/w07tbQPhO0hzS0vYL2skIzMmblH+mZdbduzH8IGZkW5AhaeFeVNlahGZbr81bq5Pp0cjsgo2CIem5sg2EZsvclVBr2mRp+0rqqSjfmyxnzO0PUnsPfDMsokvSbJ4cwZtkZ7htC4SfpYdwYAj+7ZD/m5hD4ASf054p0a9SnG+dQhqrvV3ijlviC0/q8h8+nfLdWeZ0F+nHfahizaHgGyRnTQ+Ipj/MzdPrIQx9Lr1T9bFP1MzPQ9kBrpKHZoLXggdzFEQFaqbiuoeY6j4RWoeVnYi4OmwzP3qebywrkpDHGuuSst6vPRAraRRraepXGnj80o+PxPxIoq4HmNDF6TsFtLQ/SA3owwKuW56LdvKJP758PmRgTpZMU8z5iglcBH8j2DR8zw8vl8UnPE+nsQPl9ba9ipxPhuU3Q2kN7JZ4qSKHVWqcOl16nT+rkRcN7UIKyN0dsqWXcUt5E6MurKqdwGaCPJ0t0MgYhw4OMC1UZar4RtKYa2hWC5jQ8lolem4fB6M8HGY7JKj+2laRzW66bW6rQ3wPw/UDQMgVtoUIzJtcul7tSJ3eykFEM3+2CdoOgXaPQDMkttJcKuSfEPR16piQOUu/hZYt25xm3/+nHAe6uMntJhcP5T67+p5flV7hKHOLinpW+6D5R/Ws+qxoQ25NDbV5e0edw5lcUVn+ujqBDrcaJrs4Lq553YkZmUnp2dqryknflXcGpKekjoSZmZ1hHp6T3jdZckTM8izfCZmso6RnWxLG85Tclwcp7mFPSkzSfZaYk8JNKzuadrlfkdWJs2sHVjM7BOzzPmO8/nXAeqTgvz1lWqLwUuGeUNSqvU0C4EXGWal3UUi4fKqJG9+3Qc6Ijps/APh16JvuUf4bxNalDzzJ3ibvQrVFE9tjsGlX6v1uVF1daeb+5NY3/QE1Fe4kp/v9aE7JylNdT52Yl+bWblMnLcHkJOR/lpqck8L5V5aKa/6YlOjr0zHBA87+/W/lM/Gecq0NPu2oPDmdlnhj9qIS8HB798eWlZfPfqJheUX16RfdTPonLSU0bZjki/CGh2kgNcAjc0SlhUF6m113otZV2GMYGqa9DV9TZLW+0q8zhnujrMNJFeuZF8sPGZCeOzIvpFdsrqvruvIrSTrXlENWn5i4G0adXVL8+sX179cmroFVXCyZqfqpD3OEJWyLNS0SdNXyt5Ws=
*/