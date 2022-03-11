
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