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