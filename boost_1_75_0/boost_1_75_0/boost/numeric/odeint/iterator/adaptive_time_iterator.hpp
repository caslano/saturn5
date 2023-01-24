
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
R0jte/HGf46zrI4qmSffKoUVHv0loq1aTzRpg1g6ATRjklazIeAfyvTpRLqi/Nfm0m1WwCuCdet/cCn639sqm8HFcUohO7vPurYhh54wpXoLh2jo98FEWFkqwlYyE5cy8JrGuhK71r15oqIhj3ey4vQEKBYbl7ThaR+zMg3p4wx1ku6hsZVCp7EzEH8VUgC8BqCELG39ICqYqtzKi/rPcurximO5bSwzoILr+tHpErqcVfOuEbFuiyZUrpQgNyJxarlXYqgz9WYRlwTfg93GPlFxzLNppyBIFt7N8+jix9SHwREJdET9VyRq5yoH3uJFY1JPIBkYp6BC6OS+FLUEhjw3X/IwI0jL74Lo24NNemhlDzbQ9Zq0uLmagh0MsLg84s3VVXhJnyh1M2xVRBVYFx3t5+pNZhHNRJH+U/CY/tcuLyXuNqUkmpmuNxEk8msrz6UJXlIut7pBbiv/e9TtexjeMX9D62/pDU7+3A15JOSvEcJLwS3tW6k1JBUDd6XoY91ZXWHDqmPMNyY9FNsRQdxfVOInyNJfLQL+jOBC61W+G7d8IP5qQ76g1w9v+KfnjYbp8GG6L6dDiaPJ4kq/iU0giMvi+h3BoiRm7wY0EyIjqZIMR4Ih70GyPwG0W2SthFiHtb3m3PMtt71GZcRTWrR3+dmGI96K82/Kjn/EtEm/PmbBrYOKKSlnFnb57PT53rZFLFCqFoJWEuFy
*/