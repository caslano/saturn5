
/*
 [auto_generated]
 boost/numeric/odeint/iterator/n_step_time_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size performing exactly n steps.
 The dereferenced type contains also the time.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_TIME_ITERATOR_HPP_INCLUDED


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
    class n_step_time_iterator : public n_step_iterator_impl<
            n_step_time_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef n_step_time_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        n_step_time_iterator( Stepper stepper , System sys , State &s , time_type t , time_type dt , size_t num_of_steps )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t , dt , num_of_steps )
        {}

        n_step_time_iterator( Stepper stepper , System sys , State &s )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    n_step_time_iterator< Stepper , System, State > make_n_step_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return n_step_time_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps );
    }

    template< class Stepper , class System , class State >
    n_step_time_iterator< Stepper , System , State > make_n_step_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return n_step_time_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< n_step_time_iterator< Stepper , System , State > , n_step_time_iterator< Stepper , System , State > >
    make_n_step_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return std::make_pair(
            n_step_time_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps ) ,
            n_step_time_iterator< Stepper , System , State >( stepper , system , x )
            );
    }


    /**
     * \class n_step_time_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE starting from t
     * with n steps and a constant step size dt.
     * After each iteration the iterator dereferences to a pair of state and time at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_n_steps routine.
     *
     * n_step_time_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is pair of state and time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_n_step_time_iterator_begin( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function for n_step_time_iterator. Constructs a begin iterator.
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
     * \fn make_n_step_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for n_step_time_iterator. Constructs an end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_n_step_time_range( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function to construct a single pass range of n-step iterators. A range is here a pair
     * of n_step_time_iterator.
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

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_N_STEP_TIME_ITERATOR_HPP_INCLUDED

/* n_step_time_iterator.hpp
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
*/