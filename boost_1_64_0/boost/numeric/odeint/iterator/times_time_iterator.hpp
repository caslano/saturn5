
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
ytdXRZu1nOPxl7Hx2NLalWptb/Z9yr+5DrLQyAa0/HxgfYbf6G+oizh/G3y73//7Dfy2YxuBBxzBtfEH/wj85D3X8vz/WX/TsW9RD3Ql+ezC3aHcUU509169HkFei2yb6BPWOFnW75uWYr9tkP0R8WlkXhed5Jqm2HXua5r7FPiWrwGdo5ByxIp8W3CUP9KVb+QAbY+NiaOCf24Q+5BSfs6oPfui36mR72qtD1LWjJV/E38B9Yf9LG3neBX+pJ+nbSR9zZ+hXwkcyo1jguOL/QN4TG4zN+qz/uEais4/cqOyR7RDOja/1pGjNuozMxInzOr34w2e89X+PG883tGKN9QLnDhvsxUd0OAcQzxF55iNcTuxeFmYXgY8uz4OGGjIXrZt4zyRB77VfB9A18J1pMXz4rjHsd4znhLW+9kV1C/Wo99gnk59tfq1QPX5ZWZdCTR8nz9F5OTpWr90EfL30S56f53x8Zj2+9GFYqf7iM/4u3CEV4Vr9N1ugZsw3uvNZjPZoXPT7uRqVEzoVbs9ux2hqS3tRy7eqOMvdzd3nd7Z466pN+3s9tYpBmlspJzkzfGixDzkT32fQk5LN5bxvSdRlxuPyzbGfe+nGZ05kWnAzfqb6Dl+yfxh7D5jo9C+akWc9krSdnC7xn21wV1NXMDtGgBkZc+FsX708Mkbya/Fs/jk9xTRcxMD3+BCz9cBFzIE//H5YD3gSl+Rz7VT4l9t8DcKPtvIdVPRb8guYd1U5V+dkN+kZN+xLC7PZsoTcCNPYweMPLco+QA2oc3Yxvaijlh7t0t7yQPP4ar2OJhtz07VnpGnxdvTwfY4uP12zwHG+ojDs7hSn6dn6+tB/rKY/chFe8pYx/bvv/dhyDtYF8+z7N4Yu1+VKeJTEJF5gJg/6G/6jqJAyV0ul02/viEWT2cfj9KH9a/y9iud3ZvTdgvfpvtwGznlmJLzIHsUT7OEp0ROdP1dSXblv2yTX9c0NucMY3OewzTg7MsyZzOm0Ba/tmrqPdPUm2YacL3HAz7i+ttv9Bf54Tvo1PczDf5eg38m8QdDfYY8xLc8y5cVvTwbaauXWZZLqXIjplwuodwo+Vszjz658UVGkbC+SAFlFms9ZNxNmUNzfUV1v3BM63+4poFdhlSOF8E0wPdLiYfNoDUn0RdAZLlyc9wk6Lv2HjT9gbpMPVzHVX4V1rmAn8zPC8Q3AV4yrQuEls+7bG5cB55Fe/pCZYPcmt+aOfHvwBcbn/F++l12rfslwOP9Ffi6fL8C7ec6GTBknQx00DdYohmIx0edJes4vp7qoBfvCfSn84zfh3b6s0N5XORztErvd1yi+nx+SDc9Fi1jqTR6RN8/0N+9SHu5vXRjmbXmiejSl3mZ72feGZ4n+yCXE347Y01wDaO7p6mn1f1/F+/eVWh4Z1drCkHeTue9tmk6b1trE74qA39nbTw8LMY7bZU6v6Wpp8nn8r5arD7EMlJ5M2LlcJXPn7OaeexM3mN75cZQ+xmLwxn9YnihzUIlDsbFlMMWxq+4YqOKX8H+rWQ8E7mLi7Q/6iGwWQ42yrmQsGoVH1+/RzF6EEBVdn7IdV82XYiVXxDCEXEq1LVXbfQxfRGcd+iAxyNsKWHhjqjATwwKYwMGd4WHKVy2cbWL2Qt2df1rHczwX+dg0k4/5jY6GOMab2bMiSuV/jf6+0m+7zbv2pJq7tmTCtV1PNjbp1Ucs6/yNEDbH3eTNsDHCPkPM+7bQjv7Gm1npc7WPfEFuYQMsYuOvr1f9DrA8IvZsquQVjjgCz+DczXSieeSpigPx9cbS3qaRO8w23oNaWpb+ia2A+MgZkvfYmwu4CIXhXed2G5Py971f1sCHZE=
*/