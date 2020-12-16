
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
9XY8AY8/7as8SD6AQz9U6jDjEGMlXsc/kOa+ioqbSD9c3Zl4hLLZHNPb/qHCaLrYNyjvNjnZVvn4DVCE2JkS/xoBZkDoE+31v7TNoj5ZU6Pv0yW/k+XjbgAl1dR9entzanvHZl96PDjSyWBDfM6pQDoIwK+8180YFOGehcw5CI0dgqI2TENZO+f4SBdshEAm2HefRNv92+bkm+OEfa36nrqs9fUfS4LkOifBq38znHVSr72OPFqvbLr3YRFXcgPfLiS++/su4/c9AXng0/tQjfwesm89H72B7zXiX7aP4w3/AqbH25wNkldh8uYyXaHoUG7M5zhn2buM3OazPT8xtuNJgOtvyOORFjnIeHmyksNpx8ZpLDS8LmIa8FhckYVG9kuQ5ptOgg/ZL5W2eNr2TadlSk4nL4jXfSLrBpx1x/O/R/xdzCdvwI/ztlJ4U/TwhgzluMvgrzb4u4i/RtriebVtOVnl70rIP8XIdukyqXMV/i5gQyT/JI2DvYMNgnPFAnmzSuPUk67LtzHyXgUY20Ic3ktTvF6RwOszVb8cPyfOdxPrA5z1yTi6dx5jN6oz7PcgrcdRC+XeukH5ZSzL7xhTpjLYyjLbWEavQaEc8M2btpxDtrPcqSz39ti3UHp01Dtr4tNWqruuTwStqgBnjodxKnZ/iDMfsFkhbCCfgf0lrDqEOUcvmm+2oM65hNcMheXbAJsfwoZq6EPtAGxBCMP/jRRRPtob3ok82Rtu6m5f445S72zradvdmtqyq725u2Qhk/NgK0UevC+X7BsO4xx5ygU7yuRLJBVI2/rOyH5U4G/xm7o8XPSmm3ryrA1h3T2l8WbwnmXGxWnE20O82rL8xi+YawjX/qqfrfg7Y4P4aM/B39qfei7S+MXGwPPIR0rZy2cb3tOG916W6VNlulS9GVPvANIDpt69pDGoaJxh6j2LZdKU7dksk1Xz8DWzx785+Iw54U/Xl2NZ+GKx8Xj+08OxeM4GllHfSXnWvyqqQ8oBxje9OBfrNWpld1bxrXm9FrJf7B1sndguqWt6cFDh7DHvD99MnPNMPda+vUDl35yQf0FUB+3SE2VtBX/7Ol4InOTzuX4sNrVs1mOTaerli5VeXqT6uWG+1xVdN+o19hB1X3KIunft0XUzzbpfquq+TNXdfKzuf9/3kAvtq7HHL99APGPzLd4rqSeXb+AbjsdT7iJXn4+/ff6VxD9J6y7SjZKmbPw8yL5nGfb966jP4D82r7/ezOvI9/hXE7/l+Dj+Gw0+8j3+m0Q38GZkHKeRPLxZ6ddJCfp1reR7Odv8t2pfY+H4/OtVfmMC/bdvKO9bj6xJFbQ/LwCx8Tcae3OT8S3fSZm9i3i8t4H+9+esJA7LE/0dw1Ka6/I6noTf2zl7qP+A3MtQcVtmV/u1A7dtxLSPnxamic+5E9v9HhbqFdYtMtl+n343eFwaFHALJtXXq9ZvTlTzfy1jsbxHzbcrJiErbfvfqfxtnV5s8r2MmKY9YVrk/W7mQe5hnD7V3w5mz0F+yPe3vluBq4X6zKGPkTki/RD6NmiJxEv8iP5ejHyN9p5UU9dWsSYGqvbYFkDuWh4fk/agvrgsPsH2oUx8jiIdG3Ptk8DXPl/bHLE31uf71AbuARNX2VDu5yT4ipDGZ1BuS3mb2rqnp7Wr3ThdCRnRfajPKTv7eWVnlzo7c5Gs5Rsfljxa/mYGXwKNxHN+h+kXOh6/onj8quLxVPosInPDm5H5N4DvY/lwDwdM8k6r7oPQ3tuy3470ROYP9K/Xk++WfJPj7bwo8tLz4veJfyzxRYdkbima9DXAtTqI+smLlP+p+HqsS/gGjZju36XG4yJvD7ydUeMxFsM=
*/