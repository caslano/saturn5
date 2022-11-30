/*
 [auto_generated]
 boost/numeric/odeint/stepper/dense_output_runge_kutta.hpp

 [begin_description]
 Implementation of the Dense-output stepper for all steppers. Note, that this class does
 not computes the result but serves as an interface.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2015 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED


#include <utility>
#include <stdexcept>

#include <boost/throw_exception.hpp>

#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/integrate/max_step_checker.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< class Stepper , class StepperCategory = typename Stepper::stepper_category >
class dense_output_runge_kutta;


/**
 * \brief The class representing dense-output Runge-Kutta steppers.
 * \note In this stepper, the initialize method has to be called before using
 * the do_step method.
 *
 * The dense-output functionality allows to interpolate the solution between
 * subsequent integration points using intermediate results obtained during the
 * computation. This version works based on a normal stepper without step-size
 * control. 
 * 
 *
 * \tparam Stepper The stepper type of the underlying algorithm.
 */
template< class Stepper >
class dense_output_runge_kutta< Stepper , stepper_tag >
{

public:

    /*
     * We do not need all typedefs.
     */
    typedef Stepper stepper_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::algebra_type algebra_type;
    typedef typename stepper_type::operations_type operations_type;
    typedef typename stepper_type::resizer_type resizer_type;
    typedef dense_output_stepper_tag stepper_category;
    typedef dense_output_runge_kutta< Stepper > dense_output_stepper_type;


    /**
     * \brief Constructs the dense_output_runge_kutta class. An instance of the
     * underlying stepper can be provided.
     * \param stepper An instance of the underlying stepper.
     */
    dense_output_runge_kutta( const stepper_type &stepper = stepper_type() )
    : m_stepper( stepper ) , m_resizer() ,
      m_x1() , m_x2() , m_current_state_x1( true ) , 
      m_t() , m_t_old() , m_dt()
    { } 


    /**
     * \brief Initializes the stepper. Has to be called before do_step can be 
     * used to set the initial conditions and the step size.
     * \param x0 The initial state of the ODE which should be solved.
     * \param t0 The initial time, at which the step should be performed.
     * \param dt0 The step size.
     */
    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &dense_output_stepper_type::template resize_impl< StateType > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::copy( x0 , get_current_state() );
        m_t = t0;
        m_dt = dt0;
    }

    /**
     * \brief Does one time step.
     * \note initialize has to be called before using this method to set the
     * initial conditions x,t and the stepsize.
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \return Pair with start and end time of the integration step.
     */
    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        m_stepper.do_step( system , get_current_state() , m_t , get_old_state() , m_dt );
        m_t_old = m_t;
        m_t += m_dt;
        toggle_current_state();
        return std::make_pair( m_t_old , m_t );
    }

    /*
     * The next two overloads are needed to solve the forwarding problem
     */
    
    /**
     * \brief Calculates the solution at an intermediate point.
     * \param t The time at which the solution should be calculated, has to be
     * in the current time interval.
     * \param x The output variable where the result is written into.
     */
    template< class StateOut >
    void calc_state( time_type t , StateOut &x ) const
    {
        if( t == current_time() )
        {
            boost::numeric::odeint::copy( get_current_state() , x );
        }
        m_stepper.calc_state( x , t , get_old_state() , m_t_old , get_current_state() , m_t );
    }

    /**
     * \brief Calculates the solution at an intermediate point. Solves the forwarding problem
     * \param t The time at which the solution should be calculated, has to be
     * in the current time interval.
     * \param x The output variable where the result is written into, can be a boost range.
     */
    template< class StateOut >
    void calc_state( time_type t , const StateOut &x ) const
    {
        m_stepper.calc_state( x , t , get_old_state() , m_t_old , get_current_state() , m_t );
    }

    /**
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */
    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
        m_stepper.stepper().resize( x );
    }

    /**
     * \brief Returns the current state of the solution.
     * \return The current state of the solution x(t).
     */
    const state_type& current_state( void ) const
    {
        return get_current_state();
    }

    /**
     * \brief Returns the current time of the solution.
     * \return The current time of the solution t.
     */
    time_type current_time( void ) const
    {
        return m_t;
    }

    /**
     * \brief Returns the last state of the solution.
     * \return The last state of the solution x(t-dt).
     */
    const state_type& previous_state( void ) const
    {
        return get_old_state();
    }

    /**
     * \brief Returns the last time of the solution.
     * \return The last time of the solution t-dt.
     */
    time_type previous_time( void ) const
    {
        return m_t_old;
    }

    /**
     * \brief Returns the current time step.
     * \return dt.
     */
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


    stepper_type m_stepper;
    resizer_type m_resizer;
    wrapped_state_type m_x1 , m_x2;
    bool m_current_state_x1;    // if true, the current state is m_x1
    time_type m_t , m_t_old , m_dt;

};





/**
 * \brief The class representing dense-output Runge-Kutta steppers with FSAL property.
 *
 * The interface is the same as for dense_output_runge_kutta< Stepper , stepper_tag >.
 * This class provides dense output functionality based on methods with step size controlled 
 * 
 *
 * \tparam Stepper The stepper type of the underlying algorithm.
 */
template< class Stepper >
class dense_output_runge_kutta< Stepper , explicit_controlled_stepper_fsal_tag >
{
public:

    /*
     * We do not need all typedefs.
     */
    typedef Stepper controlled_stepper_type;

    typedef typename controlled_stepper_type::stepper_type stepper_type;
    typedef typename stepper_type::state_type state_type;
    typedef typename stepper_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_type::value_type value_type;
    typedef typename stepper_type::deriv_type deriv_type;
    typedef typename stepper_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_type::time_type time_type;
    typedef typename stepper_type::algebra_type algebra_type;
    typedef typename stepper_type::operations_type operations_type;
    typedef typename stepper_type::resizer_type resizer_type;
    typedef dense_output_stepper_tag stepper_category;
    typedef dense_output_runge_kutta< Stepper > dense_output_stepper_type;


    dense_output_runge_kutta( const controlled_stepper_type &stepper = controlled_stepper_type() )
    : m_stepper( stepper ) , m_resizer() ,
      m_current_state_x1( true ) ,
      m_x1() , m_x2() , m_dxdt1() , m_dxdt2() ,
      m_t() , m_t_old() , m_dt() ,
      m_is_deriv_initialized( false )
    { }


    template< class StateType >
    void initialize( const StateType &x0 , time_type t0 , time_type dt0 )
    {
        m_resizer.adjust_size( x0 , detail::bind( &dense_output_stepper_type::template resize< StateType > , detail::ref( *this ) , detail::_1 ) );
        boost::numeric::odeint::copy( x0 , get_current_state() );
        m_t = t0;
        m_dt = dt0;
        m_is_deriv_initialized = false;
    }

    template< class System >
    std::pair< time_type , time_type > do_step( System system )
    {
        if( !m_is_deriv_initialized )
        {
            typename odeint::unwrap_reference< System >::type &sys = system;
            sys( get_current_state() , get_current_deriv() , m_t );
            m_is_deriv_initialized = true;
        }

        failed_step_checker fail_checker;  // to throw a runtime_error if step size adjustment fails
        controlled_step_result res = fail;
        m_t_old = m_t;
        do
        {
            res = m_stepper.try_step( system , get_current_state() , get_current_deriv() , m_t ,
                                      get_old_state() , get_old_deriv() , m_dt );
            fail_checker();  // check for overflow of failed steps
        }
        while( res == fail );
        toggle_current_state();
        return std::make_pair( m_t_old , m_t );
    }


    /*
     * The two overloads are needed in order to solve the forwarding problem.
     */
    template< class StateOut >
    void calc_state( time_type t , StateOut &x ) const
    {
        m_stepper.stepper().calc_state( t , x , get_old_state() , get_old_deriv() , m_t_old ,
                                        get_current_state() , get_current_deriv() , m_t );
    }

    template< class StateOut >
    void calc_state( time_type t , const StateOut &x ) const
    {
        m_stepper.stepper().calc_state( t , x , get_old_state() , get_old_deriv() , m_t_old ,
                                        get_current_state() , get_current_deriv() , m_t );
    }


    template< class StateIn >
    bool resize( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x1 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_x2 , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt1 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_dxdt2 , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize( x );
        m_stepper.stepper().resize( x );
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

    deriv_type& get_current_deriv( void )
    {
        return m_current_state_x1 ? m_dxdt1.m_v : m_dxdt2.m_v ;
    }
    
    const deriv_type& get_current_deriv( void ) const
    {
        return m_current_state_x1 ? m_dxdt1.m_v : m_dxdt2.m_v ;
    }
    
    deriv_type& get_old_deriv( void )
    {
        return m_current_state_x1 ? m_dxdt2.m_v : m_dxdt1.m_v ;
    }
    
    const deriv_type& get_old_deriv( void ) const
    {
        return m_current_state_x1 ? m_dxdt2.m_v : m_dxdt1.m_v ;
    }

    
    void toggle_current_state( void )
    {
        m_current_state_x1 = ! m_current_state_x1;
    }


    controlled_stepper_type m_stepper;
    resizer_type m_resizer;
    bool m_current_state_x1;
    wrapped_state_type m_x1 , m_x2;
    wrapped_deriv_type m_dxdt1 , m_dxdt2;
    time_type m_t , m_t_old , m_dt;
    bool m_is_deriv_initialized;

};

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_DENSE_OUTPUT_RUNGE_KUTTA_HPP_INCLUDED

/* dense_output_runge_kutta.hpp
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
*/