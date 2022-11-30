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
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
*/