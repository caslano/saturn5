
/*
 [auto_generated]
 boost/numeric/odeint/iterator/n_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size performing exactly n steps.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/n_step_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the n_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
     , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
     >
    class n_step_iterator : public n_step_iterator_impl<
            n_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef n_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        n_step_iterator( Stepper stepper , System sys , State &s , time_type t , time_type dt , size_t num_of_steps )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t , dt , num_of_steps )
        {}

        n_step_iterator( Stepper stepper , System sys , State &s )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System, State > make_n_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps );
    }

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System , State > make_n_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< n_step_iterator< Stepper , System , State > , n_step_iterator< Stepper , System , State > >
    make_n_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return std::make_pair(
            n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps ) ,
            n_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }


    /**
     * \class n_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE starting from t
     * with n steps and a constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_n_steps routine.
     *
     * n_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_n_step_iterator_begin( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function for n_step_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step iterator.
     */


    /**
     * \fn make_n_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for n_step_iterator. Constructs an end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_n_step_range( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , , size_t num_of_steps )
     *
     * \brief Factory function to construct a single pass range of n-step iterators. A range is here a pair
     * of n_step_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_N_STEP_ITERATOR_HPP_INCLUDED

/* n_step_iterator.hpp
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
*/