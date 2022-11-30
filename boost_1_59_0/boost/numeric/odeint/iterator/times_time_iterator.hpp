
/*
 [auto_generated]
 boost/numeric/odeint/iterator/times_time_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with oscillator calls at times from a given sequence.
 The dereferenced type contains also the time.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_TIME_ITERATOR_HPP_INCLUDED


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
    class times_time_iterator : public times_iterator_impl<
            times_time_iterator< Stepper , System , State , TimeIterator , StepperTag > ,
            Stepper , System , State , TimeIterator , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef times_time_iterator< Stepper , System , State , TimeIterator , StepperTag > iterator_type;

    public:
        times_time_iterator( Stepper stepper , System sys , State &s ,
                        TimeIterator t_start , TimeIterator t_end , time_type dt )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator, detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        times_time_iterator( Stepper stepper , System sys , State &s )
            : times_iterator_impl< iterator_type , Stepper , System , State , TimeIterator , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State , class TimeIterator >
    times_time_iterator< Stepper , System, State , TimeIterator > make_times_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return times_time_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt );
    }

    // ToDo: requires to specifically provide the TimeIterator template parameter, can this be improved?
    template< class TimeIterator , class Stepper , class System , class State >
    times_time_iterator< Stepper , System , State , TimeIterator > make_times_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
        //TimeIterator t_end )
    {
        return times_time_iterator< Stepper , System , State , TimeIterator >( stepper , system , x );
    }

    template< class Stepper , class System , class State , class TimeIterator >
    std::pair< times_time_iterator< Stepper , System , State , TimeIterator > ,
               times_time_iterator< Stepper , System , State , TimeIterator > >
    make_times_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            times_time_iterator< Stepper , System , State , TimeIterator >( stepper , system , x , t_start , t_end , dt ) ,
            times_time_iterator< Stepper , System , State , TimeIterator >( stepper , system , x )
            );
    }





    /**
     * \class times_time_iterator
     *
     * \brief ODE Iterator with given evaluation points. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE from *t_start
     * to *t_end evaluated at time points given by the sequence t_start to t_end.
     * t_start and t_end are iterators representing a sequence of time points
     * where the solution of the ODE should be evaluated.
     * After each iteration the iterator dereferences to a pair with the state
     * and the time at the next evaluation point *t_start++ until t_end is reached.
     * This iterator can be used with Steppers, ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_times routine.
     *
     * times_time_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is a pair of state and time type.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     * \tparam TimeIterator The iterator type for the sequence of time points.
     */



    /**
     * \fn make_times_time_iterator_begin( Stepper stepper ,
        System system ,
        State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for times_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times_time iterator.
     */


    /**
     * \fn make_times_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for times_time_iterator. Constructs an end iterator.
     *
     * \tparam TimesIterator The iterator type of the time sequence, must be specifically provided.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The times_time iterator.
     *
     * This function needs the TimeIterator type specifically defined as a
     * template parameter.
     */


    /**
     * \fn make_times_time_range( Stepper stepper , System system , State &x ,
        TimeIterator t_start ,
        TimeIterator t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of times_time iterators. A range is here a pair
     * of times_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start Begin iterator of the sequence of evaluation time points.
     * \param t_end End iterator of the sequence of evaluation time points.
     * \param dt The initial time step.
     * \returns The times_time iterator range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_TIMES_TIME_ITERATOR_HPP_INCLUDED

/* times_time_iterator.hpp
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
*/