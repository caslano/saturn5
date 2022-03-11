
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