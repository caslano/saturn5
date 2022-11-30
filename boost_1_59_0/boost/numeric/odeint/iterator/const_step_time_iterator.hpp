
/*
 [auto_generated]
 boost/numeric/odeint/iterator/const_step_time_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with constant step size. The dereferences types containes also the time.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/const_step_iterator_impl.hpp>

namespace boost {
namespace numeric {
namespace odeint {

    /* use the const_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class const_step_time_iterator : public const_step_iterator_impl<
            const_step_time_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef const_step_time_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        const_step_time_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        const_step_time_iterator( Stepper stepper , System sys , State &s )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    template< class Stepper , class System , class State >
    const_step_time_iterator< Stepper , System , State > make_const_step_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return const_step_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    const_step_time_iterator< Stepper , System , State > make_const_step_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return const_step_time_iterator< Stepper , System , State >( stepper , system , x );
    }


    template< class Stepper , class System , class State >
    std::pair< const_step_time_iterator< Stepper , System , State > , const_step_time_iterator< Stepper , System , State > >
    make_const_step_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            const_step_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            const_step_time_iterator< Stepper , System , State >( stepper , system , x ) );
    }

    /**
     * \class const_step_time_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with constant step size dt.
     * After each iteration the iterator dereferences to a pair containing
     * state and time at the next time point t+dt..
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_const routine.
     *
     * const_step_time_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is a pair with the state type and time type of the stepper.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_const_step_time_iterator_begin( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for const_step_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step time iterator.
     */


    /**
     * \fn make_const_step_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for const_step_time_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator store a reference of s and changes its value during the iteration.
     * \returns The const step time iterator.
     */


    /**
     * \fn make_const_step_time_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt)
     *
     * \brief Factory function to construct a single pass range of const_step_time_iterator. A range is here a pair of const_step_time_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step time range.
     */







} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED

/* const_step_time_iterator.hpp
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
*/