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