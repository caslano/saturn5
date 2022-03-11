
/*
 [auto_generated]
 boost/numeric/odeint/iterator/times_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with oscillator calls at times from a given sequence.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/times_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the times_iterator_impl with the right tags */
    template< class Stepper , class System , class State , class TimeIterator
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class times_iterator : public times_iterator_impl<
            times_iterator< Stepper , System , State , TimeIterator , StepperTag > ,
            Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef times_iterator< Stepper , System , State , TimeIterator , StepperTag > iterator_type;

    public:
        times_iterator( Stepper stepper , System sys , State &s ,
                        TimeIterator t_start , TimeIterator t_end , time_type dt )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator, detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        times_iterator( Stepper stepper , System sys , State &s )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State , class TimeIterator >
    times_iterator< Stepper , System, State , TimeIterator > make_times_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt );
    }

    // ToDo: requires to specifically provide the TimeIterator template parameter, can this be improved?
    template< class TimeIterator , class Stepper , class System , class State >
    times_iterator< Stepper , System , State , TimeIterator > make_times_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
        //TimeIterator t_end )
    {
        return times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x );
    }

    template< class Stepper , class System , class State , class TimeIterator >
    std::pair< times_iterator< Stepper , System , State , TimeIterator > ,
               times_iterator< Stepper , System , State , TimeIterator > >
    make_times_range(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt ) ,
            times_iterator< Stepper , System , State , TimeIterator >( stepper , system , x )
            );
    }


    /**
     * \class times_iterator
     *
     * \brief ODE Iterator with given evaluation points. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from *t_start
     * to *t_end evaluated at time points given by the sequence t_start to t_end.
     * t_start and t_end are iterators representing a sequence of time points
     * where the solution of the ODE should be evaluated.
     * After each iteration the iterator dereferences to the state x at the next
     * time *t_start++ until t_end is reached.
     * This iterator can be used with Steppers, ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_times routine.
     *
     * times_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     * \tparam TimeIterator The iterator type for the sequence of time points.
     */



    /**
     * \fn make_times_iterator_begin( Stepper stepper ,
        System system ,
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for times_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator.
     */


    /**
     * \fn make_times_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for times_iterator. Constructs an end iterator.
     *
     * \tparam TimesIterator The iterator type of the time sequence, must be specifically provided.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The times iterator.
     *
     * This function needs the TimeIterator type specifically defined as a
     * template parameter.
     */


    /**
     * \fn make_times_range( Stepper stepper , System system , State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of times iterators. A range is here a pair
     * of times_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times iterator range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_ITERATOR_HPP_INCLUDED

/* times_iterator.hpp
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
*/