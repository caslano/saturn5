
/*
 [auto_generated]
 boost/numeric/odeint/iterator/const_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
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
    class const_step_iterator : public const_step_iterator_impl<
            const_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef const_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        const_step_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        const_step_iterator( Stepper stepper , System sys , State &s )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System, State > make_const_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System , State > make_const_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< const_step_iterator< Stepper , System , State > , const_step_iterator< Stepper , System , State > >
    make_const_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            const_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }



    /**
     * \class const_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_const routine.
     *
     * const_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_const_step_iterator_begin(
        Stepper stepper ,
        System system ,
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for const_step_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step iterator.
     */


    /**
     * \fn make_const_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for const_step_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_const_step_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of const step iterators. A range is here a pair
     * of const_step_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

//#include <boost/numeric/odeint/iterator/impl/const_step_iterator_dense_output_impl.hpp>

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED

/* const_step_iterator.hpp
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
*/