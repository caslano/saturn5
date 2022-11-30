/*
 [auto_generated]
 boost/numeric/odeint/stepper/explicit_error_generic_rk.hpp

 [begin_description]
 Implementation of the generic Runge Kutta error stepper. Base class for many RK error steppers.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp>

#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_algorithm.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_operations.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>



namespace boost {
namespace numeric {
namespace odeint {


template<
size_t StageCount,
size_t Order,
size_t StepperOrder ,
size_t ErrorOrder ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class explicit_error_generic_rk
: public explicit_error_stepper_base<
  explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
  Value , Deriv , Time , Algebra , Operations , Resizer > ,
  Order , StepperOrder , ErrorOrder , State , Value , Deriv , Time , Algebra ,
  Operations , Resizer >
#else
class explicit_error_generic_rk : public explicit_error_stepper_base
#endif
{

public:
#ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_base<
            explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
            Value , Deriv , Time , Algebra , Operations , Resizer > ,
            Order , StepperOrder , ErrorOrder , State , Value , Deriv , Time , Algebra ,
            Operations , Resizer > stepper_base_type;
#else
    typedef explicit_stepper_base< ... > stepper_base_type;
#endif
    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;
#ifndef DOXYGEN_SKIP
    typedef explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
            Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;
#endif
    typedef detail::generic_rk_algorithm< StageCount , Value , Algebra , Operations > rk_algorithm_type;

    typedef typename rk_algorithm_type::coef_a_type coef_a_type;
    typedef typename rk_algorithm_type::coef_b_type coef_b_type;
    typedef typename rk_algorithm_type::coef_c_type coef_c_type;

    static const size_t stage_count = StageCount;

private:


public:

    // we use an explicit_generic_rk to do the normal rk step
    // and add a separate calculation of the error estimate afterwards
    explicit_error_generic_rk( const coef_a_type &a ,
            const coef_b_type &b ,
            const coef_b_type &b2 ,
            const coef_c_type &c ,
            const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_rk_algorithm( a , b , c ) , m_b2( b2 )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        // normal step
        do_step_impl( system , in , dxdt , t , out , dt );

        // additionally, perform the error calculation
        detail::template generic_rk_call_algebra< StageCount , algebra_type >()( stepper_base_type::m_algebra ,
                xerr , dxdt , m_F , detail::generic_rk_scale_sum_err< StageCount , operations_type , value_type , time_type >( m_b2 , dt) );
    }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt )
    {
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        // actual calculation done in generic_rk.hpp
        m_rk_algorithm.do_step( stepper_base_type::m_algebra , system , in , dxdt , t , out , dt , m_x_tmp.m_v , m_F );
    }


    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }


private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < StageCount-1 ; ++i )
        {
            resized |= adjust_size_by_resizeability( m_F[i] , x , typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    }


    rk_algorithm_type m_rk_algorithm;
    coef_b_type m_b2;

    resizer_type m_resizer;

    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_F[StageCount-1];

};


/********* DOXYGEN *********/

/**
 * \class explicit_error_generic_rk
 * \brief A generic implementation of explicit Runge-Kutta algorithms with error estimation. This class is as a
 * base class for all explicit Runge-Kutta steppers with error estimation.
 *
 * This class implements the explicit Runge-Kutta algorithms with error estimation in a generic way.
 * The Butcher tableau is passed to the stepper which constructs the stepper scheme with the help of a
 * template-metaprogramming algorithm. ToDo : Add example!
 * 
 * This class derives explicit_error_stepper_base which provides the stepper interface.
 *
 * \tparam StageCount The number of stages of the Runge-Kutta algorithm.
 * \tparam Order The order of a stepper if the stepper is used without error estimation.
 * \tparam StepperOrder The order of a step if the stepper is used with error estimation. Usually Order and StepperOrder have 
 * the same value.
 * \tparam ErrorOrder The order of the error step if the stepper is used with error estimation.
 * \tparam State The type representing the state of the ODE.
 * \tparam Value The floating point type which is used in the computations.
 * \tparam Time The type representing the independent variable - the time - of the ODE.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */


    /**
     * \fn explicit_error_generic_rk::explicit_error_generic_rk( const coef_a_type &a , const coef_b_type &b , const coef_b_type &b2 , const coef_c_type &c , const algebra_type &algebra )
     * \brief Constructs the explicit_error_generik_rk class with the given parameters a, b, b2 and c. See examples section for details on the coefficients.
     *
     * \param a Triangular matrix of parameters b in the Butcher tableau.
     * \param b Last row of the butcher tableau.
     * \param b2 Parameters for lower-order evaluation to estimate the error.
     * \param c Parameters to calculate the time points in the Butcher tableau.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn explicit_error_generic_rk::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`. Futhermore, an
     * estimation of the error is stored in `xerr`. `do_step_impl` is used by explicit_error_stepper_base.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     * \param xerr The result of the error estimation is written in xerr.
     */

    /**
     * \fn explicit_error_generic_rk::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_stepper_base and 
     * `do_step_impl` should not be called directly.
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
     * \fn explicit_error_generic_rk::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

}
}
}


#endif // BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED

/* explicit_error_generic_rk.hpp
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
*/