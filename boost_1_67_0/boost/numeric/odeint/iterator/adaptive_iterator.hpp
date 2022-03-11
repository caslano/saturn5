
/*
 [auto_generated]
 boost/numeric/odeint/iterator/adaptive_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with adaptive step size. The dereferenced types containes also the time.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED

#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/stepper/controlled_step_result.hpp>
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
    class adaptive_iterator : public adaptive_iterator_impl<
            adaptive_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef adaptive_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        adaptive_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        adaptive_iterator( Stepper stepper , System sys , State &s )
            : adaptive_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };




    template< class Stepper , class System , class State >
    adaptive_iterator< Stepper , System , State > make_adaptive_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return adaptive_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }


    template< class Stepper , class System , class State >
    adaptive_iterator< Stepper , System , State > make_adaptive_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return adaptive_iterator< Stepper , System , State >( stepper , system , x );
    }


    template< class Stepper , class System , class State >
    std::pair< adaptive_iterator< Stepper , System , State > , adaptive_iterator< Stepper , System , State > >
    make_adaptive_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            adaptive_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            adaptive_iterator< Stepper , System , State >( stepper , system , x )
            );
    }

    /**
     * \class adaptive_iterator
     *
     * \brief ODE Iterator with adaptive step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with an adaptive step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt where dt is controlled by the stepper.
     * This iterator can be used with ControlledSteppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_adaptive routine.
     *
     * adaptive_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */






    /**
     * \fn make_adaptive_iterator_begin( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for adaptive_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive iterator.
     */


    /**
     * \fn make_adaptive_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for adaptive_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \returns The adaptive iterator.
     */


    /**
     * \fn make_adaptive_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of adaptive iterators. A range is here a pair of adaptive_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The adaptive range.
     */






} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_ITERATOR_ADAPTIVE_ITERATOR_HPP_INCLUDED

/* adaptive_iterator.hpp
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
*/