/*
 [auto_generated]
 boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp

 [begin_description]
 Base class for all explicit Runge Kutta stepper which are also error steppers.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2012 Mario Mulansky
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_BASE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_BASE_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>


#include <boost/numeric/odeint/util/bind.hpp>
#include <boost/numeric/odeint/util/unwrap_reference.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>

#include <boost/numeric/odeint/stepper/base/algebra_stepper_base.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * base class for explicit stepper and error steppers
 * models the stepper AND the error stepper concept
 *
 * this class provides the following do_step variants:
    * do_step( sys , x , t , dt )
    * do_step( sys , x , dxdt , t , dt )
    * do_step( sys , in , t , out , dt )
    * do_step( sys , in , dxdt , t , out , dt )
    * do_step( sys , x , t , dt , xerr )
    * do_step( sys , x , dxdt , t , dt , xerr )
    * do_step( sys , in , t , out , dt , xerr )
    * do_step( sys , in , dxdt , t , out , dt , xerr )
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
class explicit_error_stepper_base : public algebra_stepper_base< Algebra , Operations >
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
    typedef explicit_error_stepper_tag stepper_category;
    #ifndef DOXYGEN_SKIP
    typedef state_wrapper< state_type > wrapped_state_type;
    typedef state_wrapper< deriv_type > wrapped_deriv_type;
    typedef explicit_error_stepper_base< Stepper , Order , StepperOrder , ErrorOrder ,
            State , Value , Deriv , Time , Algebra , Operations , Resizer > internal_stepper_base_type;
    #endif

    typedef unsigned short order_type;
    static const order_type order_value = Order;
    static const order_type stepper_order_value = StepperOrder;
    static const order_type error_order_value = ErrorOrder;


    explicit_error_stepper_base( const algebra_type &algebra = algebra_type() )
    : algebra_stepper_base_type( algebra )
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
     * Version 1 : do_step( sys , x , t , dt )
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
     * Version 2 : do_step( sys , x , dxdt , t , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateInOut , class DerivIn >
    typename boost::disable_if< boost::is_same< DerivIn , time_type > , void >::type
    do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt )
    {
        this->stepper().do_step_impl( system , x , dxdt , t , x , dt );
    }


    /*
     * named Version 2: do_step_dxdt_impl( sys , in , dxdt , t , dt )
     *
     * this version is needed when this stepper is used for initializing 
     * multistep stepper like adams-bashforth. Hence we provide an explicitely
     * named version that is not disabled. Meant for internal use only.
     */
    template < class System, class StateInOut, class DerivIn >
    void do_step_dxdt_impl( System system, StateInOut &x, const DerivIn &dxdt,
                            time_type t, time_type dt )
    {
        this->stepper().do_step_impl( system , x , dxdt , t , x , dt );
    }



    /*
     * Version 3 : do_step( sys , in , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateIn , class StateOut >
    typename boost::disable_if< boost::is_same< StateIn , time_type > , void >::type
    do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &internal_stepper_base_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v ,t );
        this->stepper().do_step_impl( system , in , m_dxdt.m_v , t , out , dt );
    }

    /*
     * Version 4 :do_step( sys , in , dxdt , t , out , dt )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateIn , class DerivIn , class StateOut >
    typename boost::disable_if< boost::is_same< DerivIn , time_type > , void >::type
    do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        this->stepper().do_step_impl( system , in , dxdt , t , out , dt );
    }
    
    /*
     * named Version 4: do_step_dxdt_impl( sys , in , dxdt , t , out, dt )
     *
     * this version is needed when this stepper is used for initializing 
     * multistep stepper like adams-bashforth. Hence we provide an explicitely
     * named version that is not disabled. Meant for internal use only.
     */
    template < class System, class StateIn, class DerivIn, class StateOut >
    void do_step_dxdt_impl( System system, const StateIn &in,
                            const DerivIn &dxdt, time_type t, StateOut &out,
                            time_type dt )
    {
        this->stepper().do_step_impl( system , in , dxdt , t , out , dt );
    }

    /*
     * Version  5 :do_step( sys , x , t , dt , xerr )
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
     * Version 6 :do_step( sys , x , dxdt , t , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     *
     * the disable is needed to avoid ambiguous overloads if state_type = time_type
     */
    template< class System , class StateInOut , class DerivIn , class Err >
    typename boost::disable_if< boost::is_same< DerivIn , time_type > , void >::type
    do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt , Err &xerr )
    {
        this->stepper().do_step_impl( system , x , dxdt , t , x , dt , xerr );
    }


    /*
     * Version 7 : do_step( sys , in , t , out , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class StateOut , class Err >
    void do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( in , detail::bind( &internal_stepper_base_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );
        sys( in , m_dxdt.m_v ,t );
        this->stepper().do_step_impl( system , in , m_dxdt.m_v , t , out , dt , xerr );
    }


    /*
     * Version 8 : do_step( sys , in , dxdt , t , out , dt , xerr )
     *
     * this version does not solve the forwarding problem, boost.range can not be used
     */
    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        this->stepper().do_step_impl( system , in , dxdt , t , out , dt , xerr );
    }

    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
    }



private:

    template< class System , class StateInOut >
    void do_step_v1( System system , StateInOut &x , time_type t , time_type dt )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( x , detail::bind( &internal_stepper_base_type::template resize_impl<StateInOut> , detail::ref( *this ) , detail::_1 ) );
        sys( x , m_dxdt.m_v , t );
        this->stepper().do_step_impl( system , x , m_dxdt.m_v , t , x , dt );
    }

    template< class System , class StateInOut , class Err >
    void do_step_v5( System system , StateInOut &x , time_type t , time_type dt , Err &xerr )
    {
        typename odeint::unwrap_reference< System >::type &sys = system;
        m_resizer.adjust_size( x , detail::bind( &internal_stepper_base_type::template resize_impl<StateInOut> , detail::ref( *this ) , detail::_1 ) );
        sys( x , m_dxdt.m_v ,t );
        this->stepper().do_step_impl( system , x , m_dxdt.m_v , t , x , dt , xerr );
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

protected:

    wrapped_deriv_type m_dxdt;
};




/******** DOXYGEN *******/

/**
 * \class explicit_error_stepper_base
 * \brief Base class for explicit steppers with error estimation. This class can used with 
 * controlled steppers for step size control.
 *
 * This class serves as the base class for all explicit steppers with algebra and operations. In contrast to
 * explicit_stepper_base it also estimates the error and can be used in a controlled stepper to provide
 * step size control.
 *
 * \note This stepper provides `do_step` methods with and without error estimation. It has therefore three orders,
 * one for the order of a step if the error is not estimated. The other two orders are the orders of the step and 
 * the error step if the error estimation is performed.
 *
 * explicit_error_stepper_base  is used as the interface in a CRTP (currently recurring template
 * pattern). In order to work correctly the parent class needs to have a method
 * `do_step_impl( system , in , dxdt_in , t , out , dt , xerr )`. 
 * explicit_error_stepper_base derives from algebra_stepper_base.
 *
 * explicit_error_stepper_base provides several overloaded `do_step` methods, see the list below. Only two of them
 * are needed to fulfill the Error Stepper concept. The other ones are for convenience and for performance. Some
 * of them simply update the state out-of-place, while other expect that the first derivative at `t` is passed to the
 * stepper.
 *
 * - `do_step( sys , x , t , dt )` - The classical `do_step` method needed to fulfill the Error Stepper concept. The
 *      state is updated in-place. A type modelling a Boost.Range can be used for x.
 * - `do_step( sys , x , dxdt , t , dt )` - This method updates the state in-place, but the derivative at the point `t`
 *      must be explicitly passed in `dxdt`.
 * - `do_step( sys , in , t , out , dt )` - This method updates the state out-of-place, hence the result of the step
 *      is stored in `out`.
 * - `do_step( sys , in , dxdt , t , out , dt )` - This method update the state out-of-place and expects that the
 *     derivative at the point `t` is explicitly passed in `dxdt`. It is a combination of the two `do_step` methods
 *     above.
 * - `do_step( sys , x , t , dt , xerr )` - This `do_step` method is needed to fulfill the Error Stepper concept. The
 *     state is updated in-place and an error estimate is calculated. A type modelling a Boost.Range can be used for x.
 * - `do_step( sys , x , dxdt , t , dt , xerr )` - This method updates the state in-place, but the derivative at the
 *      point `t` must be passed in `dxdt`. An error estimate is calculated.
 * - `do_step( sys , in , t , out , dt , xerr )` - This method updates the state out-of-place and estimates the error
 *      during the step.
 * - `do_step( sys , in , dxdt , t , out , dt , xerr )` - This methods updates the state out-of-place and estimates
 *      the error during the step. Furthermore, the derivative at `t` must be passed in `dxdt`.
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
     * \fn explicit_error_stepper_base::explicit_error_stepper_base( const algebra_type &algebra = algebra_type() )
     *
     * \brief Constructs a explicit_error_stepper_base class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

    /**
     * \fn explicit_error_stepper_base::order( void ) const
     * \return Returns the order of the stepper if it used without error estimation.
     */

    /**
     * \fn explicit_error_stepper_base::stepper_order( void ) const
     * \return Returns the order of a step if the stepper is used without error estimation.
     */

    /**
     * \fn explicit_error_stepper_base::error_order( void ) const
     * \return Returns the order of an error step if the stepper is used without error estimation.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , StateInOut &x , time_type t , time_type dt )
     * \brief This method performs one step. It transforms the result in-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ordinary differential equation. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. Additionally to the other method
     * the derivative of x is also passed to this method. It is supposed to be used in the following way:
     *
     * \code
     * sys( x , dxdt , t );
     * stepper.do_step( sys , x , dxdt , t , dt );
     * \endcode
     *
     * The result is updated in place in x. This method is disabled if Time and Deriv are of the same type. In this
     * case the method could not be distinguished from other `do_step` versions.
     * 
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * This method is disabled if StateIn and Time are the same type. In this case the method can not be distinguished from
     * other `do_step` variants.
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
     * \fn explicit_error_stepper_base::do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the derivative of x at t is passed to the stepper. It is supposed to be used in the following way:
     *
     * \code
     * sys( in , dxdt , t );
     * stepper.do_step( sys , in , dxdt , t , out , dt );
     * \endcode
     *
     * This method is disabled if DerivIn and Time are of same type.
     *
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , StateInOut &x , time_type t , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper and estimates the error. The state of the ODE
     * is updated in-place.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. x is updated by this method.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     * \param xerr The estimation of the error is stored in xerr.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , StateInOut &x , const DerivIn &dxdt , time_type t , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. Additionally to the other method
     * the derivative of x is also passed to this method. It is supposed to be used in the following way:
     *
     * \code
     * sys( x , dxdt , t );
     * stepper.do_step( sys , x , dxdt , t , dt , xerr );
     * \endcode
     *
     * The result is updated in place in x. This method is disabled if Time and DerivIn are of the same type. In this
     * case the method could not be distinguished from other `do_step` versions.
     * 
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param x The state of the ODE which should be solved. After calling do_step the result is updated in x.
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param dt The step size.
     * \param xerr The error estimate is stored in xerr.
     */

    /**
     * \fn explicit_error_stepper_base::do_step( System system , const StateIn &in , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the error is estimated.
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
     * \fn explicit_error_stepper_base::do_step( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief The method performs one step with the stepper passed by Stepper. The state of the ODE is updated out-of-place.
     * Furthermore, the derivative of x at t is passed to the stepper and the error is estimated. It is supposed to be used in the following way:
     *
     * \code
     * sys( in , dxdt , t );
     * stepper.do_step( sys , in , dxdt , t , out , dt );
     * \endcode
     *
     * This method is disabled if DerivIn and Time are of same type.
     *
     * \note This method does not solve the forwarding problem.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     * \param xerr The error estimate.
     */


    /**
     * \fn explicit_error_stepper_base::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_STEPPER_BASE_EXPLICIT_ERROR_STEPPER_BASE_HPP_INCLUDED

/* explicit_error_stepper_base.hpp
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
*/