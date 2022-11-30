/*
 [auto_generated]
 boost/numeric/odeint/stepper/adams_bashforth.hpp

 [begin_description]
 Implementaton of the Adam-Bashforth method a multistep method used for the predictor step in the
 Adams-Bashforth-Moulton method.
 [end_description]

 Copyright 2011-2013 Karsten Ahnert
 Copyright 2011-2013 Mario Mulansky
 Copyright 2012 Christoph Koke
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_HPP_INCLUDED

#include <boost/static_assert.hpp>

#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/numeric/odeint/stepper/extrapolation_stepper.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>

#include <boost/numeric/odeint/stepper/detail/adams_bashforth_coefficients.hpp>
#include <boost/numeric/odeint/stepper/detail/adams_bashforth_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/rotating_buffer.hpp>

#include <boost/mpl/arithmetic.hpp>
#include <boost/mpl/min_max.hpp>
#include <boost/mpl/equal_to.hpp>

namespace mpl = boost::mpl;


namespace boost {
namespace numeric {
namespace odeint {

    using mpl::int_;

    /* if N >= 4, returns the smallest even number > N, otherwise returns 4 */
    template < int N >
    struct order_helper
        : mpl::max< typename mpl::eval_if<
                        mpl::equal_to< mpl::modulus< int_< N >, int_< 2 > >,
                                       int_< 0 > >,
                        int_< N >, int_< N + 1 > >::type,
                    int_< 4 > >::type
    { };

template<
size_t Steps ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer ,
class InitializingStepper = extrapolation_stepper< order_helper<Steps>::value, 
                                                   State, Value, Deriv, Time,
                                                   Algebra, Operations, Resizer >
>
class adams_bashforth : public algebra_stepper_base< Algebra , Operations >
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
    typedef Resizer resizer_type;
    typedef stepper_tag stepper_category;

    typedef InitializingStepper initializing_stepper_type;

    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;
    typedef typename algebra_stepper_base_type::operations_type operations_type;
#ifndef DOXYGEN_SKIP
    typedef adams_bashforth< Steps , State , Value , Deriv , Time , Algebra , Operations , Resizer , InitializingStepper > stepper_type;
#endif
    static const size_t steps = Steps;



    typedef unsigned short order_type;
    static const order_type order_value = steps;

    typedef detail::rotating_buffer< wrapped_deriv_type , steps > step_storage_type;


    
    order_type order( void ) const { return order_value; }

    adams_bashforth( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra ) ,
      m_step_storage() , m_resizer() , m_coefficients() ,
      m_steps_initialized( 0 ) , m_initializing_stepper()
    { }



    /*
     * Version 1 : do_step( system , x , t , dt );
     *
     * solves the forwarding problem
     */
    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step( system , x , t , x , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step( system , x , t , x , dt );
    }



    /*
     * Version 2 : do_step( system , in , t , out , dt );
     *
     * solves the forwarding problem
     */

    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        do_step_impl( system , in , t , out , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateOut.
     */
    template< class System , class StateIn , class StateOut >
    void do_step( System system , const StateIn &in , time_type t , const StateOut &out , time_type dt )
    {
        do_step_impl( system , in , t , out , dt );
    }


    template< class StateType >
    void adjust_size( const StateType &x )
    {
        resize_impl( x );
    }

    const step_storage_type& step_storage( void ) const
    {
        return m_step_storage;
    }

    step_storage_type& step_storage( void )
    {
        return m_step_storage;
    }

    template< class ExplicitStepper , class System , class StateIn >
    void initialize( ExplicitStepper explicit_stepper , System system , StateIn &x , time_type &t , time_type dt )
    {
        typename odeint::unwrap_reference< ExplicitStepper >::type &stepper = explicit_stepper;
        typename odeint::unwrap_reference< System >::type &sys = system;

        m_resizer.adjust_size( x , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        for( size_t i=0 ; i+1<steps ; ++i )
        {
            if( i != 0 ) m_step_storage.rotate();
            sys( x , m_step_storage[0].m_v , t );
            stepper.do_step_dxdt_impl( system, x, m_step_storage[0].m_v, t,
                                       dt );
            t += dt;
        }
        m_steps_initialized = steps;
    }

    template< class System , class StateIn >
    void initialize( System system , StateIn &x , time_type &t , time_type dt )
    {
        initialize( detail::ref( m_initializing_stepper ) , system , x , t , dt );
    }

    void reset( void )
    {
        m_steps_initialized = 0;
    }

    bool is_initialized( void ) const
    {
        return m_steps_initialized >= ( steps - 1 );
    }

    const initializing_stepper_type& initializing_stepper( void ) const { return m_initializing_stepper; }

    initializing_stepper_type& initializing_stepper( void ) { return m_initializing_stepper; }

private:

    template< class System , class StateIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        if( m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) ) )
        {
            m_steps_initialized = 0;
        }

        if( m_steps_initialized + 1 < steps )
        {
            if( m_steps_initialized != 0 ) m_step_storage.rotate();
            sys( in , m_step_storage[0].m_v , t );
            m_initializing_stepper.do_step_dxdt_impl(
                system, in, m_step_storage[0].m_v, t, out, dt );
            ++m_steps_initialized;
        }
        else
        {
            m_step_storage.rotate();
            sys( in , m_step_storage[0].m_v , t );
            detail::adams_bashforth_call_algebra< steps , algebra_type , operations_type >()( this->m_algebra , in , out , m_step_storage , m_coefficients , dt );
        }
    }


    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        for( size_t i=0 ; i<steps ; ++i )
        {
            resized |= adjust_size_by_resizeability( m_step_storage[i] , x , typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    }

    step_storage_type m_step_storage;
    resizer_type m_resizer;
    detail::adams_bashforth_coefficients< value_type , steps > m_coefficients;
    size_t m_steps_initialized;
    initializing_stepper_type m_initializing_stepper;

};


/***** DOXYGEN *****/

/**
 * \class adams_bashforth
 * \brief The Adams-Bashforth multistep algorithm.
 *
 * The Adams-Bashforth method is a multi-step algorithm with configurable step
 * number. The step number is specified as template parameter Steps and it 
 * then uses the result from the previous Steps steps. See also
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
     * \fn adams_bashforth::adams_bashforth( const algebra_type &algebra )
     * \brief Constructs the adams_bashforth class. This constructor can be used as a default
     * constructor if the algebra has a default constructor. 
     * \param algebra A copy of algebra is made and stored.
     */

    /**
     * \fn order_type adams_bashforth::order( void ) const
     * \brief Returns the order of the algorithm, which is equal to the number of steps.
     * \return order of the method.
     */

    /**
     * \fn void adams_bashforth::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn void adams_bashforth::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
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
     * \fn void adams_bashforth::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */


    /**
     * \fn const step_storage_type& adams_bashforth::step_storage( void ) const
     * \brief Returns the storage of intermediate results.
     * \return The storage of intermediate results.
     */

    /**
     * \fn step_storage_type& adams_bashforth::step_storage( void )
     * \brief Returns the storage of intermediate results.
     * \return The storage of intermediate results.
     */

    /**
     * \fn void adams_bashforth::initialize( ExplicitStepper explicit_stepper , System system , StateIn &x , time_type &t , time_type dt )
     * \brief Initialized the stepper. Does Steps-1 steps with the explicit_stepper to fill the buffer.
     * \param explicit_stepper the stepper used to fill the buffer of previous step results
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn void adams_bashforth::initialize( System system , StateIn &x , time_type &t , time_type dt )
     * \brief Initialized the stepper. Does Steps-1 steps with an internal instance of InitializingStepper to fill the buffer.
     * \note The state x and time t are updated to the values after Steps-1 initial steps.
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The initial state of the ODE which should be solved, updated in this method.
     * \param t The initial value of the time, updated in this method.
     * \param dt The step size.
     */

    /**
     * \fn void adams_bashforth::reset( void )
     * \brief Resets the internal buffer of the stepper.
     */

    /**
     * \fn bool adams_bashforth::is_initialized( void ) const
     * \brief Returns true if the stepper has been initialized.
     * \return bool true if stepper is initialized, false otherwise
     */

    /**
     * \fn const initializing_stepper_type& adams_bashforth::initializing_stepper( void ) const
     * \brief Returns the internal initializing stepper instance.
     * \return initializing_stepper
     */

    /**
     * \fn const initializing_stepper_type& adams_bashforth::initializing_stepper( void ) const
     * \brief Returns the internal initializing stepper instance.
     * \return initializing_stepper
     */

    /**
     * \fn initializing_stepper_type& adams_bashforth::initializing_stepper( void )
     * \brief Returns the internal initializing stepper instance.
     * \return initializing_stepper
     */

} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_STEPPER_ADAMS_BASHFORTH_HPP_INCLUDED

/* adams_bashforth.hpp
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
*/