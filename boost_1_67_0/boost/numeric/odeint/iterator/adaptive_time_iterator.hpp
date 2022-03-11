
/*
 [auto_generated]
 boost/numeric/odeint/iterator/adaptive_time_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with adaptive step size. The dereferenced types containes also the time.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED



#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/iterator/impl/adaptive_iterator_impl.hpp>

namespace boost {
namespace numeric {
namespace odeint {

    /* use the adaptive_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class adaptive_time_iterator : public adaptive_iterator_impl<
            adaptive_time_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef adaptive_time_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        adaptive_time_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        adaptive_time_iterator( Stepper stepper , System sys , State &s )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };




    template< class Stepper , class System , class State >
    adaptive_time_iterator< Stepper , System , State > make_adaptive_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return adaptive_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    adaptive_time_iterator< Stepper , System , State > make_adaptive_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return adaptive_time_iterator< Stepper , System , State >( stepper , system , x );
    }


    template< class Stepper , class System , class State >
    std::pair< adaptive_time_iterator< Stepper , System , State > , adaptive_time_iterator< Stepper , System , State > >
    make_adaptive_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            adaptive_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            adaptive_time_iterator< Stepper , System , State >( stepper , system , x ) );
    }



    /**
     * \class adaptive_time_iterator
     *
     * \brief ODE Iterator with adaptive step size. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with an adaptive step size dt.
     * After each iteration the iterator dereferences to a pair containing state
     * and time at the next time point t+dt where dt is controlled by the stepper.
     * This iterator can be used with ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_adaptive routine.
     *
     * adaptive_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is a std::pair of  state and time of the stepper.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */



    /**
     * \fn make_adaptive_time_iterator_begin( Stepper stepper , System system , State &x ,
         typename traits::time_type< Stepper >::type t_start ,
         typename traits::time_type< Stepper >::type t_end ,
         typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for adaptive_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive time iterator.
     */


    /**
     * \fn make_adaptive_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for adaptive_time_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive_time_iterator stores a reference of s and changes its value during the iteration.
     * \returns The adaptive time iterator.
     */


    /**
     * \fn make_adaptive_time_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of adaptive time iterators. A range is here a pair of adaptive_time_iterators.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. adaptive_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive time range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_TIME_ITERATOR_HPP_INCLUDED

/* adaptive_time_iterator.hpp
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
*/