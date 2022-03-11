/*
 [auto_generated]
 boost/numeric/odeint/stepper/base/explicit_error_stepper_fsal_base.hpp

 [begin_description]
 Base class for all explicit first-same-as-last Runge Kutta steppers.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2012 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_FSAL_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_FSAL_BASE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>


#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/util/copy.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>

namespace boost {
namespace numeric {
namespace odeint {

/*
 * base class for explicit stepper and error steppers with the fsal property
 * models the stepper AND the error stepper fsal concept
 * 
 * this class provides the following do_step overloads
    * do_step( sys , x , t , dt )
    * do_step( sys , x , dxdt , t , dt )
    * do_step( sys , in , t , out , dt )
    * do_step( sys , in , dxdt_in , t , out , dxdt_out , dt )
    * do_step( sys , x , t , dt , xerr )
    * do_step( sys , x , dxdt , t , dt , xerr )
    * do_step( sys , in , t , out , dt , xerr )
    * do_step( sys , in , dxdt_in , t , out , dxdt_out , dt , xerr )
 */
template<
class Stepper ,
unsigned short Order ,
unsigned short StepperOrder ,
unsigned short ErrorOrder ,
class State ,
class Value ,
class Deriv ,
class Time ,
class Algebra ,
class Operations ,
class Resizer
>
class explicit_error_stepper_fsal_base : public algebra_stepper_base< Algebra , Operations >
{
public:

    typedef algebra_stepper_base< Algebra , Operations > algebra_stepper_base_type;
    typedef typename algebra_stepper_base_type::algebra_type algebra_type;

    typedef State state_type;
    typedef Value value_type;
    typedef Deriv deriv_type;
    typedef Time time_type;
    typedef Resizer resizer_type;
    typedef Stepper stepper_type;
    typedef explicit_error_stepper_fsal_tag stepper_category;

    #ifndef DOXYGEN_SKIP
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef explicit_error_stepper_fsal_base< Stepper , Order , StepperOrder , ErrorOrder ,
            State , Value , Deriv , Time , Algebra , Operations , Resizer > internal_stepper_base_type;
    #endif 


    typedef unsigned short order_type;
    static const order_type order_value = Order;
    static const order_type stepper_order_value = StepperOrder;
    static const order_type error_order_value = ErrorOrder;

    explicit_error_stepper_fsal_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra ) , m_first_call( true )
    { }

    order_type order( void ) const
    {
        return order_value;
    }

    order_type stepper_order( void ) const
    {
        return stepper_order_value;
    }

    order_type error_order( void ) const
    {
        return error_order_value;
    }


    /*
     * version 1 : do_step( sys , x , t , dt )
     *
     * the two overloads are needed in order to solve the forwarding problem
     */
    template< class System , class StateInOut >
    void do_step( System system , StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt )
    {
        do_step_v1( system , x , t , dt );
    }


    /*
     * version 2 : do_step( sys , x , dxdt , t , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateInOut , class DerivInOut >
    typename boost::disable_if< boost::is_same< StateInOut , time_type > , void >::type
    do_step( System system , StateInOut &x , DerivInOut &dxdt , time_type t , time_type dt )
    {
        m_first_call = true;
        this->stepper().do_step_impl( system , x , dxdt , t , x , dxdt , dt );
    }


    /*
     * named Version 2: do_step_dxdt_impl( sys , in , dxdt , t , dt )
     *
     * this version is needed when this stepper is used for initializing 
     * multistep stepper like adams-bashforth. Hence we provide an explicitely
     * named version that is not disabled. Meant for internal use only.
     */
    template< class System , class StateInOut , class DerivInOut >
    void do_step_dxdt_impl( System system , StateInOut &x , DerivInOut &dxdt , time_type t , time_type dt )
    {
        m_first_call = true;
        this->stepper().do_step_impl( system , x , dxdt , t , x , dxdt , dt );
    }

    /*
     * version 3 : do_step( sys , in , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not
     * be used.
     *
     * the disable is needed to avoid ambiguous overloads if 
     * state_type = time_type
     */
    template< class System , class StateIn , class StateOut >
    typename boost::disable_if< boost::is_same< StateIn , time_type > , void >::type
    do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        if( m_resizer.adjust_size( in , detail::bind( &internal_stepper_base_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , in , t );
        }
        this->stepper().do_step_impl( system , in , m_dxdt.m_v , t , out , m_dxdt.m_v , dt );
    }


    /*
     * version 4 : do_step( sys , in , dxdt_in , t , out , dxdt_out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System, class StateIn, class DerivIn, class StateOut,
               class DerivOut >
    void do_step( System system, const StateIn &in, const DerivIn &dxdt_in,
                  time_type t, StateOut &out, DerivOut &dxdt_out, time_type dt )
    {
        m_first_call = true;
        this->stepper().do_step_impl( system, in, dxdt_in, t, out, dxdt_out,
                                      dt );
    }





    /*
     * version 5 : do_step( sys , x , t , dt , xerr )
     *
     * the two overloads are needed in order to solve the forwarding problem
     */
    template< class System , class StateInOut , class Err >
    void do_step( System system , StateInOut &x , time_type t , time_type dt , Err &xerr )
    {
        do_step_v5( system , x , t , dt , xerr );
    }

    /**
     * \brief Second version to solve the forwarding problem, can be called with Boost.Range as StateInOut.
     */
    template< class System , class StateInOut , class Err >
    void do_step( System system , const StateInOut &x , time_type t , time_type dt , Err &xerr )
    {
        do_step_v5( system , x , t , dt , xerr );
    }


    /*
     * version 6 : do_step( sys , x , dxdt , t , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateInOut , class DerivInOut , class Err >
    typename boost::disable_if< boost::is_same< StateInOut , time_type > , void >::type
    do_step( System system , StateInOut &x , DerivInOut &dxdt , time_type t , time_type dt , Err &xerr )
    {
        m_first_call = true;
        this->stepper().do_step_impl( system , x , dxdt , t , x , dxdt , dt , xerr );
    }




    /*
     * version 7 : do_step( sys , in , t , out , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class StateOut , class Err >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        if( m_resizer.adjust_size( in , detail::bind( &internal_stepper_base_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , in , t );
        }
        this->stepper().do_step_impl( system , in , m_dxdt.m_v , t , out , m_dxdt.m_v , dt , xerr );
    }


    /*
     * version 8 : do_step( sys , in , dxdt_in , t , out , dxdt_out , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class DerivIn , class StateOut , class DerivOut , class Err >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t ,
            StateOut &out , DerivOut &dxdt_out , time_type dt , Err &xerr )
    {
        m_first_call = true;
        this->stepper().do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt , xerr );
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
    }

    void reset( void )
    {
        m_first_call = true;
    }

    template< class DerivIn >
    void initialize( const DerivIn &deriv )
    {
        boost::numeric::odeint::copy( deriv , m_dxdt.m_v );
        m_first_call = false;
    }

    template< class System , class StateIn >
    void initialize( System system , const StateIn &x , time_type t )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        sys( x , m_dxdt.m_v , t );
        m_first_call = false;
    }

    bool is_initialized( void ) const
    {
        return ! m_first_call;
    }



private:

    template< class System , class StateInOut >
    void do_step_v1( System system , StateInOut &x , time_type t , time_type dt )
    {
        if( m_resizer.adjust_size( x , detail::bind( &internal_stepper_base_type::template resize_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , x , t );
        }
        this->stepper().do_step_impl( system , x , m_dxdt.m_v , t , x , m_dxdt.m_v , dt );
    }

    template< class System , class StateInOut , class Err >
    void do_step_v5( System system , StateInOut &x , time_type t , time_type dt , Err &xerr )
    {
        if( m_resizer.adjust_size( x , detail::bind( &internal_stepper_base_type::template resize_impl< StateInOut > , detail::ref( *this ) , detail::_1 ) ) || m_first_call )
        {
            initialize( system , x , t );
        }
        this->stepper().do_step_impl( system , x , m_dxdt.m_v , t , x , m_dxdt.m_v , dt , xerr );
    }

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        return adjust_size_by_resizeability( m_dxdt , x , typename is_resizeable<deriv_type>::type() );
    }


    stepper_type& stepper( void )
    {
        return *static_cast< stepper_type* >( this );
    }

    const stepper_type& stepper( void ) const
    {
        return *static_cast< const stepper_type* >( this );
    }


    resizer_type m_resizer;
    bool m_first_call;

protected:


    wrapped_deriv_type m_dxdt;
};


/******* DOXYGEN *******/

/**
 * \class explicit_error_stepper_fsal_base
 * \brief Base class for explicit steppers with error estimation and stepper fulfilling the FSAL (first-same-as-last)
 * property. This class can be used with controlled steppers for step size control.
 *
 * This class serves as the base class for all explicit steppers with algebra and operations and which fulfill the FSAL
 * property. In contrast to explicit_stepper_base it also estimates the error and can be used in a controlled stepper
 * to provide step size control.
 *
 * The FSAL property means that the derivative of the system at t+dt is already used in the current step going from
 * t to t +dt. Therefore, some more do_steps method can be introduced and the controlled steppers can explicitly make use
 * of this property.
 *
 * \note This stepper provides `do_step` methods with and without error estimation. It has therefore three orders,
 * one for the order of a step if the error is not estimated. The other two orders are the orders of the step and 
 * the error step if the error estimation is performed.
 *
 * explicit_error_stepper_fsal_base  is used as the interface in a CRTP (currently recurring template
 * pattern). In order to work correctly the parent class needs to have a method
 * `do_step_impl( system , in , dxdt_in , t , out , dxdt_out , dt , xerr )`. 
 * explicit_error_stepper_fsal_base derives from algebra_stepper_base.
 *
 * This class can have an intrinsic state depending on the explicit usage of the `do_step` method. This means that some
 * `do_step` methods are expected to be called in order. For example the `do_step( sys , x , t , dt , xerr )` will keep track 
 * of the derivative of `x` which is the internal state. The first call of this method is recognized such that one
 * does not explicitly initialize the internal state, so it is safe to use this method like
 *
 * \code
 * stepper_type stepper;
 * stepper.do_step( sys , x , t , dt , xerr );
 * stepper.do_step( sys , x , t , dt , xerr );
 * stepper.do_step( sys , x , t , dt , xerr );
 * \endcode
 *
 * But it is unsafe to call this method with different system functions after each other. Do do so, one must initialize the
 * internal state with the `initialize` method or reset the internal state with the `reset` method.
 *
 * explicit_error_stepper_fsal_base provides several overloaded `do_step` methods, see the list below. Only two of them are needed
 * to fulfill the Error Stepper concept. The other ones are for convenience and for better performance. Some of them
 * simply update the state out-of-place, while other expect that the first derivative at `t` is passed to the stepper.
 *
 * - `do_step( sys , x , t , dt )` - The classical `do_step` method needed to fulfill the Error Stepper concept. The
 *      state is updated in-place. A type modelling a Boost.Range can be used for x.
 * - `do_step( sys , x , dxdt , t , dt )` - This method updates the state x and the derivative dxdt in-place. It is expected
 *     that dxdt has the value of the derivative of x at time t.
 * - `do_step( sys , in , t , out , dt )` - This method updates the state out-of-place, hence the result of the step
 *      is stored in `out`.
 * - `do_step( sys , in , dxdt_in , t , out , dxdt_out , dt )` - This method updates the state and the derivative
 *     out-of-place. It expects that the derivative at the point `t` is explicitly passed in `dxdt_in`.
 * - `do_step( sys , x , t , dt , xerr )` - This `do_step` method is needed to fulfill the Error Stepper concept. The
 *     state is updated in-place and an error estimate is calculated. A type modelling a Boost.Range can be used for x.
 * - `do_step( sys , x , dxdt , t , dt , xerr )` - This method updates the state and the derivative in-place. It is assumed
 *      that the dxdt has the value of the derivative of x at time t. An error estimate is calculated.
 * - `do_step( sys , in , t , out , dt , xerr )` - This method updates the state out-of-place and estimates the error
 *      during the step.
 * - `do_step( sys , in , dxdt_in , t , out , dxdt_out , dt , xerr )` - This methods updates the state and the derivative
 *      out-of-place and estimates the error during the step. It is assumed the dxdt_in is derivative of in at time t.
 *
 * \note The system is always passed as value, which might result in poor performance if it contains data. In this
 *      case it can be used with `boost::ref` or `std::ref`, for example `stepper.do_step( boost::ref( sys ) , x , t , dt );`
 *
 * \note The time `t` is not advanced by the stepper. This has to done manually, or by the appropriate `integrate`
 *      routines or `iterator`s.
 *
 * \tparam Stepper The stepper on which this class should work. It is used via CRTP, hence explicit_stepper_base
 * provides the interface for the Stepper.
 * \tparam Order The order of a stepper if the stepper is used without error estimation.
 * \tparam StepperOrder The order of a step if the stepper is used with error estimation. Usually Order and StepperOrder have 
 * the same value.
 * \tparam ErrorOrder The order of the error step if the stepper is used with error estimation.
 * \tparam State The state type for the stepper.
 * \tparam Value The value type for the stepper. This should be a floating point type, like float,
 * double, or a multiprecision type. It must not necessary be the value_type of the State. For example
 * the State can be a `vector< complex< double > >` in this case the Value must be double.
 * The default value is double.
 * \tparam Deriv The type representing time derivatives of the state type. It is usually the same type as the
 * state type, only if used with Boost.Units both types differ.
 * \tparam Time The type representing the time. Usually the same type as the value type. When Boost.Units is
 * used, this type has usually a unit.
 * \tparam Algebra The algebra type which must fulfill the Algebra Concept.
 * \tparam Operations The type for the operations which must fulfill the Operations Concept.
 * \tparam Resizer The resizer policy class.
 */



    /**
     * \fn explicit_error_stepper_fsal_base::explicit_error_stepper_fsal_base( const algebra_type &algebra )
     * \brief Constructs a explicit_stepper_fsal_base class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn explicit_error_stepper_fsal_base::order( void ) const
     * \return Returns the order of the stepper if it used without error estimation.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::stepper_order( void ) const
     * \return Returns the order of a step if the stepper is used without error estimation.
     */


    /**
     * \fn explicit_error_stepper_fsal_base::error_order( void ) const
     * \return Returns the order of an error step if the stepper is used without error estimation.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     *
     * \note This method uses the internal state of the stepper.
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */


    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , StateInOut &x , DerivInOut &dxdt , time_type t , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. Additionally to the other methods
     * the derivative of x is also passed to this method. Therefore, dxdt must be evaluated initially:
     *
     * \code
     * ode( x , dxdt , t );
     * for( ... )
     * {
     *     stepper.do_step( ode , x , dxdt , t , dt );
     *     t += dt;
     * }
     * \endcode
     *
     * \note This method does NOT use the initial state, since the first derivative is explicitly passed to this method.
     *
     * The result is updated in place in x as well as the derivative dxdt. This method is disabled if
     * Time and StateInOut are of the same type. In this case the method could not be distinguished from other `do_step`
     * versions.
     * 
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param dxdt The derivative of x at t. After calling `do_step` dxdt is updated to the new value.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * This method is disabled if StateIn and Time are the same type. In this case the method can not be distinguished from
     * other `do_step` variants.
     *
     * \note This method uses the internal state of the stepper.
     *
     * \note This method does not solve the forwarding problem. 
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t , StateOut &out , DerivOut &dxdt_out , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the derivative of x at t is passed to the stepper and updated by the stepper to its new value at
     * t+dt.
     *
     * \note This method does not solve the forwarding problem.
     *
     * \note This method does NOT use the internal state of the stepper.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt_in The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dxdt_out The updated derivative of `out` at `t+dt`.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , StateInOut &x , time_type t , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper and estimates the error. The state of the ODE
     * is updated in-place.
     *
     *
     * \note This method uses the internal state of the stepper.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. x is updated by this method.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     * \param xerr The estimation of the error is stored in xerr.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , StateInOut &x , DerivInOut &dxdt , time_type t , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. Additionally to the other method
     * the derivative of x is also passed to this method and updated by this method.
     *
     * \note This method does NOT use the internal state of the stepper.
     *
     * The result is updated in place in x. This method is disabled if Time and Deriv are of the same type. In this
     * case the method could not be distinguished from other `do_step` versions. This method is disabled if StateInOut and
     * Time are of the same type.
     *
     * \note This method does NOT use the internal state of the stepper.
     * 
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param dxdt The derivative of x at t. After calling `do_step` this value is updated to the new value at `t+dt`.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     * \param xerr The error estimate is stored in xerr.
     */


    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the error is estimated.
     *
     * \note This method uses the internal state of the stepper.
     *
     * \note This method does not solve the forwarding problem. 
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     * \param xerr The error estimate.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::do_step( System system , const StateIn &in , const DerivIn &dxdt_in , time_type t , StateOut &out , DerivOut &dxdt_out , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the derivative of x at t is passed to the stepper and the error is estimated.
     *
     * \note This method does NOT use the internal state of the stepper.
     *
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt_in The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dxdt_out The new derivative at `t+dt` is written into this variable.
     * \param dt The step size.
     * \param xerr The error estimate.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::reset( void )
     * \brief Resets the internal state of this stepper. After calling this method it is safe to use all
     * `do_step` method without explicitly initializing the stepper.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::initialize( const DerivIn &deriv )
     * \brief Initializes the internal state of the stepper.
     * \param deriv The derivative of x. The next call of `do_step` expects that the derivative of `x` passed to `do_step`
     *              has the value of `deriv`.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::initialize( System system , const StateIn &x , time_type t )
     * \brief Initializes the internal state of the stepper.
     *
     * This method is equivalent to 
     * \code
     * Deriv dxdt;
     * system( x , dxdt , t );
     * stepper.initialize( dxdt );
     * \endcode
     *
     * \param system The system function for the next calls of `do_step`.
     * \param x The current state of the ODE.
     * \param t The current time of the ODE.
     */

    /**
     * \fn explicit_error_stepper_fsal_base::is_initialized( void ) const
     * \brief Returns if the stepper is already initialized. If the stepper is not initialized, the first 
     * call of `do_step` will initialize the state of the stepper. If the stepper is already initialized
     * the system function can not be safely exchanged between consecutive `do_step` calls.
     */

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_FSAL_BASE_HPP_INCLUDED

/* explicit_error_stepper_fsal_base.hpp
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
*/