
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