/*
 [auto_generated]
 boost/numeric/odeint/stepper/euler.hpp

 [begin_description]
 Implementation of the classical explicit Euler stepper. This method is really simple and should only
 be used for demonstration purposes.
 [end_description]

 Copyright 2010-2013 Karsten Ahnert
 Copyright 2010-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED


#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {


template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class euler
: public explicit_stepper_base<
  euler< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  1 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class euler : public explicit_stepper_base
#endif
{
public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_stepper_base< euler< State , Value , Deriv , Time , Algebra , Operations , Resizer > , 1 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_stepper_base< euler< ... > , ... > stepper_base_type;
    #endif
    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;

    #ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::stepper_type stepper_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    #endif 


    euler( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }

    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System /* system */ , const StateIn &in , const DerivIn &dxdt , time_type /* t */ , StateOut &out , time_type dt )
    {
        stepper_base_type::m_algebra.for_each3( out , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt ) );

    }

    template< class StateOut , class StateIn1 , class StateIn2 >
    void calc_state( StateOut &x , time_type t ,  const StateIn1 &old_state , time_type t_old , const StateIn2 & /*current_state*/ , time_type /* t_new */ ) const
    {
        const time_type delta = t - t_old;
        stepper_base_type::m_algebra.for_each3( x , old_state , stepper_base_type::m_dxdt.m_v ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , delta ) );
    }

    template< class StateType >
    void adjust_size( const StateType &x )
    {
        stepper_base_type::adjust_size( x );
    }
};



/********** DOXYGEN ***********/

/**
 * \class euler
 * \brief An implementation of the Euler method.
 *
 * The Euler method is a very simply solver for ordinary differential equations. This method should not be used
 * for real applications. It is only useful for demonstration purposes. Step size control is not provided but
 * trivial continuous output is available.
 * 
 * This class derives from explicit_stepper_base and inherits its interface via CRTP (current recurring template pattern),
 * see explicit_stepper_base
 *
 * \tparam State The state type.
 * \tparam Value The value type.
 * \tparam Deriv The type representing the time derivative of the state.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */

    /**
     * \fn euler::euler( const algebra_type &algebra )
     * \brief Constructs the euler class. This constructor can be used as a default
     * constructor of the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */
    
    /**
     * \fn euler::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out of place, hence the input is in `in` and the output in `out`.
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
     * \fn euler::calc_state( StateOut &x , time_type t ,  const StateIn1 &old_state , time_type t_old , const StateIn2 &current_state , time_type t_new ) const
     * \brief This method is used for continuous output and it calculates the state `x` at a time `t` from the 
     * knowledge of two states `old_state` and `current_state` at time points `t_old` and `t_new`.
     */

    /**
     * \fn euler::adjust_size( const StateType &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_EULER_HPP_INCLUDED

/* euler.hpp
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
*/