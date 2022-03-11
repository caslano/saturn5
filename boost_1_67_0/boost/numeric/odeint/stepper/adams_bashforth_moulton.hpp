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