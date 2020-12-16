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
Pb1srLWb4cqv4EIq8ZD3ed8Saz/rro84txS/4r+rzhGPbqwusuA2Pu8OWJb4KQ1p3DE/wqRjsEkc6mSXi3Tpvdo0+Br115WvBCPX228f1kEeTeGb97LWlWjk9DAyH01urA340U/oml0NcfJx+4pPYH4y3sAsOPRM7f+kb8VV90vgfpx9Lg0uyWbPrBWt4hp//m2d1HvoNJzzHF08Or4UTT7oH1roaYTfF2CeF2iPUebD7xhRHXf5/ETvPR14HS3VB7z5PqW5r5CbavehWn5X77p7N6+hp16/v3gfVk9w/7n++2R585lAe9ARx5fo487iqjZyLJqPCfei3XPAUTxj3eqOEWsYdrUDXIcJn+gnd+UJfjcCHqUZ53eiY3+wD1Yefk3Tq+kRMpnbefladat+/Aztb9znF8mB+jDNGu5Wg1mayMk7fJgM1rwqfJ8Mf+mZL+6rbX5b/QewdJXzEM95m/n1y9no4QH4eC09XAQfWdvs5hOVMcL5V7U7y9qo98QV9QC0an/zy7CFboQJG6rSRkvgAj5NOk/PFmBTBfhOj/+kX05Di52oAw+zWJth9phoqKNyN6v5TJxPr4pvl+DZcDx54s+435t1NrV55RZz+nUPrG7otcGl+GAvYFtmsdIDhn7BL/JzyF0+BD2c/C+1GuyxdzWG7XD3Hfh2gxeWFA8WoxlprosNcNkDe93RetELvLumcGUozahugj2WHgvlJE15oaq8xhV1cWHmvfigNh8llzqarD6SmacaLpzF3zTulmz8wFL6p9Lq3ufKbuYHiGnttnoB/cXwInq5IcH3UFvPz+m7qv6/A0bh6J5HrE807D8jH0ry2vT/H22DnfBt+nK9UW5epff9cUms3XdDH3VkjjtOefZKziSC23dgTjU91kdy4p+yNL35zT0hl5KLpWtPoCPv5oj7XTVtdntPPRz1qbXIgItx9GI1kk5et9vBG6kqH1rbNztMw/TmMTbWn0w1xoV8MLk2/309W7BnpT8IdYVHDXgd7jlgI0z5QG9zgmYqF/xedJyFG7Omtybz6T8aYsou2uhP+0/l6Ub89sV4+SE2M6aKL7x/OXPYfoLemUZ5z3rXqS3e6np+G+/rH3Avn0asL6nbJGpgRNCLXId3J63zR86h0wgtbrt/TxgnfsG8kvfku9Cw4+mMn61hGnObKgaJ/pST5reS/hkz23iqwfSwGAW/KzUh7P0hwncS+zlvcn86sfzRep0xFpwwNZG//2uvTczfGiCHnsCAVOKIA87m03t355kkgNfqosZ2lEJj5LzvOd+QM9kXzcv5iyU0WbPBPBbx/SUJjfMQXi0O24Nw/0rOMLUQd73Vzl3Wq5Nzf/31xrmsdRU95iJ1WEPN6y9v698u4et7RWF5N/6pfClYUy8XT+/4ET4OfqeivvSjIeo9Syj2rH3xQs4SmMN9GFaunNqw9i+poRc8zt0hdU8n/pMJRohzfti5cit9sVQP5E+0uAae75FonDzPPNtG8O75/xPVlPnHa00rbXQfNfpjN3vtU+VrCbz8ndfVcYq5Yb6XPV2fL/QyvrGOSU+py1vOqKyWp3hrdEK1Y5+qI/xuDz/7JdJfb1KjIc8Z3tdDPFQ/crE/Hmv3sj+L4r4LKyu9GyXvJ7/umg3wSLxQ7O+ZyZXC3ncmsVFPXdRv5Hfi/pGa0atH9ISNetXq78kJ98vfS33rX0Pfqhv3LjeF5ofJqZKra3izbxsNjntGlQzxsJ2X/QE39uFdxcejrWFvFbn8QdDn0NA/8UEK87nGqWN9z7HP9Qry9ZjrVMaTi405Ma+wUr0Ifa98tCYV14din70ofw8f00FJxtOrrjVJrm6l525k5VmWoGN/pKs=
*/