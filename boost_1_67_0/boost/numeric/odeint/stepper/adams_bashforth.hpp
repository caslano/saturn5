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