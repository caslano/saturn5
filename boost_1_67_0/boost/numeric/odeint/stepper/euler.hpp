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