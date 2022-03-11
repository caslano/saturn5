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