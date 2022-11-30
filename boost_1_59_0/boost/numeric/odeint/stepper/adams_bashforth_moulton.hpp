/*
 [auto_generated]
 boost/numeric/odeint/stepper/adams_bashforth_moulton.hpp

 [begin_description]
 Implementation of the Adams-Bashforth-Moulton method, a predictor-corrector multistep method.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/adams_bashforth.hpp>
#include <boost/numeric/odeint/stepper/adams_moulton.hpp>



namespace boost {
namespace numeric {
namespace odeint {


template<
size_t Steps ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer,
class InitializingStepper = runge_kutta4< State , Value , Deriv , Time , Algebra , Operations, Resizer >
>
class adams_bashforth_moulton
{

#ifndef DOXYGEN_SKIP
    BOOST_STATIC_ASSERT(( Steps > 0 ));
    BOOST_STATIC_ASSERT(( Steps < 9 ));
#endif

public :

    typedef State state_type;
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef Time time_type;
    typedef Algebra algebra_type;
    typedef Operations operations_type;
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;
    typedef InitializingStepper initializing_stepper_type;

    static const size_t steps = Steps;
#ifndef DOXYGEN_SKIP
    typedef adams_bashforth< steps , state_type , value_type , deriv_type , time_type , algebra_type , operations_type , resizer_type, initializing_stepper_type > adams_bashforth_type;
    typedef adams_moulton< steps , state_type , value_type , deriv_type , time_type , algebra_type , operations_type , resizer_type > adams_moulton_type;
    typedef adams_bashforth_moulton< steps , state_type , value_type , deriv_type , time_type , algebra_type , operations_type , resizer_type , initializing_stepper_type> stepper_type;
#endif //DOXYGEN_SKIP
    typedef unsigned short order_type;
    static const order_type order_value = steps;

    /** \brief Constructs the adams_bashforth class. */
    adams_bashforth_moulton( void )
    : m_adams_bashforth() , m_adams_moulton( m_adams_bashforth.algebra() )
    , m_x() , m_resizer()
    { }

    adams_bashforth_moulton( const algebra_type &algebra )
    : m_adams_bashforth( algebra ) , m_adams_moulton( m_adams_bashforth.algebra() )
    , m_x() , m_resizer()    
    { }

    order_type order( void ) const { return order_value; }

    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_impl1( system , x , t , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_impl1( system , x , t , dt );
    }

    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , const StateOut &out , time_type dt )
    {
        do_step_impl2( system , in , t , out , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateOut.
     */
    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        do_step_impl2( system , in ,t , out , dt );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        m_adams_bashforth.adjust_size( x );
        m_adams_moulton.adjust_size( x );
        resize_impl( x );
    }


    template< class ExplicitStepper , class System , class StateIn >
    void initialize( ExplicitStepper explicit_stepper , System system , StateIn &x , time_type &t , time_type dt )
    {
        m_adams_bashforth.initialize( explicit_stepper , system , x , t , dt );
    }


    template< class System , class StateIn >
    void initialize( System system , StateIn &x , time_type &t , time_type dt )
    {
        m_adams_bashforth.initialize( system , x , t , dt );
    }


    void reset(void)
    {
        m_adams_bashforth.reset();
    }



private:
    
    template< typename System , typename StateInOut >
    void do_step_impl1( System system , StateInOut &x , time_type t , time_type dt )
    {
        if( m_adams_bashforth.is_initialized() )
        {
            m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );
            m_adams_bashforth.do_step( system , x , t , m_x.m_v , dt );
            m_adams_moulton.do_step( system , x , m_x.m_v , t+dt , x , dt , m_adams_bashforth.step_storage() );
        }
        else
        {
            m_adams_bashforth.do_step( system , x , t , dt );
        }
    }
    
    template< typename System , typename StateIn , typename StateInOut >
    void do_step_impl2( System system , StateIn const &in , time_type t , StateInOut & out , time_type dt )
    {
        if( m_adams_bashforth.is_initialized() )
        {
            m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) );        
            m_adams_bashforth.do_step( system , in , t , m_x.m_v , dt );
            m_adams_moulton.do_step( system , in , m_x.m_v , t+dt , out , dt , m_adams_bashforth.step_storage() );
        }
        else
        {
            m_adams_bashforth.do_step( system , in , t , out , dt );
        }
    }

    
    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_x , x , typename is_resizeable< state_type >::type() );
    }

    adams_bashforth_type m_adams_bashforth;
    adams_moulton_type m_adams_moulton;
    wrapped_state_type m_x;
    resizer_type m_resizer;
};


/********* DOXYGEN ********/

/**
 * \class adams_bashforth_moulton
 * \brief The Adams-Bashforth-Moulton multistep algorithm.
 *
 * The Adams-Bashforth method is a multi-step predictor-corrector algorithm 
 * with configurable step number. The step number is specified as template 
 * parameter Steps and it then uses the result from the previous Steps steps. 
 * See also
 * <a href="http://en.wikipedia.org/wiki/Linear_multistep_method">en.wikipedia.org/wiki/Linear_multistep_method</a>.
 * Currently, a maximum of Steps=8 is supported.
 * The method is explicit and fulfills the Stepper concept. Step size control
 * or continuous output are not provided.
 * 
 * This class derives from algebra_base and inherits its interface via
 * CRTP (current recurring template pattern). For more details see
 * algebra_stepper_base.
 *
 * \tparam Steps The number of steps (maximal 8).
 * \tparam State The state type.
 * \tparam Value The value type.
 * \tparam Deriv The type representing the time derivative of the state.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 * \tparam InitializingStepper The stepper for the first two steps.
 */

    /**
     * \fn adams_bashforth_moulton::adams_bashforth_moulton( const algebra_type &algebra )
     * \brief Constructs the adams_bashforth class. This constructor can be used as a default
     * constructor if the algebra has a default constructor. 
     * \param algebra A copy of algebra is made and stored.
     */

    /**
     * \fn adams_bashforth_moulton::order( void ) const
     * \brief Returns the order of the algorithm, which is equal to the number of steps+1.
     * \return order of the method.
     */

    /**
     * \fn adams_bashforth_moulton::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */


    /**
     * \fn adams_bashforth_moulton::do_step( System system , const StateIn &in , time_type t , const StateOut &out , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn adams_bashforth_moulton::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

    /**
     * \fn adams_bashforth_moulton::initialize( ExplicitStepper explicit_stepper , System system , StateIn &x , time_type &t , time_type dt )
     * \brief Initialized the stepper. Does Steps-1 steps with the explicit_stepper to fill the buffer.
     * \note The state x and time t are updated to the values after Steps-1 initial steps.
     * \param explicit_stepper the stepper used to fill the buffer of previous step results
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The initial state of the ODE which should be solved, updated after in this method.
     * \param t The initial time, updated in this method.
     * \param dt The step size.
     */

    /**
     * \fn adams_bashforth_moulton::initialize( System system , StateIn &x , time_type &t , time_type dt )
     * \brief Initialized the stepper. Does Steps-1 steps using the standard initializing stepper 
     * of the underlying adams_bashforth stepper.
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn adams_bashforth_moulton::reset( void )
     * \brief Resets the internal buffers of the stepper.
     */


} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_MOULTON_HPP_INCLUDED

/* adams_bashforth_moulton.hpp
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
*/