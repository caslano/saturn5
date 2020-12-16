
/*
 [auto_generated]
 boost/numeric/odeint/iterator/n_step_time_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size performing exactly n steps.
 The dereferenced type contains also the time.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_TIME_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/n_step_iterator_impl.hpp>


namespace boost {
namespace numeric {
namespace odeint {


    /* use the n_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class n_step_time_iterator : public n_step_iterator_impl<
            n_step_time_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef n_step_time_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        n_step_time_iterator( Stepper stepper , System sys , State &s , time_type t , time_type dt , size_t num_of_steps )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t , dt , num_of_steps )
        {}

        n_step_time_iterator( Stepper stepper , System sys , State &s )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    n_step_time_iterator< Stepper , System, State > make_n_step_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return n_step_time_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps );
    }

    template< class Stepper , class System , class State >
    n_step_time_iterator< Stepper , System , State > make_n_step_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return n_step_time_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< n_step_time_iterator< Stepper , System , State > , n_step_time_iterator< Stepper , System , State > >
    make_n_step_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return std::make_pair(
            n_step_time_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps ) ,
            n_step_time_iterator< Stepper , System , State >( stepper , system , x )
            );
    }


    /**
     * \class n_step_time_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE starting from t
     * with n steps and a constant step size dt.
     * After each iteration the iterator dereferences to a pair of state and time at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_n_steps routine.
     *
     * n_step_time_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is pair of state and time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_n_step_time_iterator_begin( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function for n_step_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step iterator.
     */


    /**
     * \fn make_n_step_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for n_step_time_iterator. Constructs an end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_n_step_time_range( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function to construct a single pass range of n-step iterators. A range is here a pair
     * of n_step_time_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param dt The initial time step.
     * \param num_of_steps The number of steps to be executed.
     * \returns The n-step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_N_STEP_TIME_ITERATOR_HPP_INCLUDED

/* n_step_time_iterator.hpp
mkBzuaaZuP4HXSHNlaTJPLkLpeqve3qIu5q4yXs5p3U3hS8fYWzyb47FGpSze9UVmGN0+oUBzy/L/uBuBnyV9Xfs8w3tHYzB19b7NfhzWzKFvjxif7oMBz8F8CMqCud2HyzgWHx3EfFdC3ot/+KKoZ3pA91+76cQCPxSD9/VP9qyN7Knl1dkR3fj3V2+XHffcn6D1yq7d0VFcvtHYvPUYEqt7fjv10rA0tmhdAHrhaX9hyrA3OcMvjg9LuGQ5aCc2WL5WcRNZcM4vst5jrRO8VYduFWlzEhoN/k3eNM+t/12r6+Pp7c/jT4I/XN793UT8HX+CSb/mfXi151AXTyB3yxN1MXNE+pXchv82yhKh1vr1VoQ0zOZ9nGSiFuj9y4n+Y3uyrcljMHPY3xtB1yPwVNVWo/hnb48ZUVZnKxxIasO4nYm1DUnwT/s0uOdOIsr4/X3kOYu0tT+ovfF7TmDevHnobuga/BoK04HnqU1avg7Azh6rEPB77O0pZzQfl4972hTP/GTe9qVCWXQ0jOVnjWR1yZ+L/TWyx6TpWfvo/XXS6woi9uUeJdUYkUNTFD2mEOUHaznfT9blu1NLAeBnkUdalIxbvX+U6/0E8+JjNejEepIzuuI6n+kp6v6dR+do+jeMNfgkG5BdIk6knxXdkz1j63T9s9+o1MnVFCnDB+2jnNVHfpbdlGCDjwfuF0x+11IsN+FBPtd8LvE8TX8QrjtQRsN0LTzYzban7ylfePf6v7U9fz2xXzv+/NCsRlMq7dDzPrNi+v1fhrS7OeXKLt5vaHrfAZL9wuG7ktV3q3mbO3LZD4QH0XF0Xu55Hu6LzNrU68kH19Q61wsT/rUO9KfnhCT9NXS1/S9RPdPsPdPWR/gpC9y0OmLmX4pZXit2XudTf1+83rRrTcAV99xeWMoN8xbshdxjfKRUD46l5A8FybriufHjF3yA/0hH+r85VvZhrcpPbjOzZf+HCLPGY6jJ3bpTbrPQO8dMs7Z54Kr8W4yY7eikvdzxVfFmPF5/Nf4r/jvu8n7ezx/ooebRE+8rr+XeLfUq34iPasPtp/ez/Q5lcqmgu9zyPe0KuF7MWkt5t/neL6l7YvJ94fIz4fJj/v7rSZO6Efrk+O2fizUG+CL3nyivnzc1tvqk2OY3g54Mn5y3NY7AFd3soAXX8P6dNTvpEccG2PhszKfm3rLx239PPL4NirfWB0Y6s2bPVWEpMSGR3Q2+Iux9ah04eBIX8qXKq0sxUFyZ1bOWxX0Xsvx1T4qQwrQ0XT/Gg87xtMGzJv/vdGe9QLgVke4NUEDbf2XFU8Xyvkfdyg+vTfjubLACdbKBvq5v19qkQDUWtlXzVrZ1+rDsvF75jh/jlrje5aA9WeygEV3kb+u18oo0/3poVgYt3HQcmeZptB+N96+WS8xDHiXnOdQ9w7AO8eW00C6j/tGDrfKwffmc2Oj/HZEn1zqYAPcJ2f5yx0MTS3k+3yffgtlr3Cwgv+YguzDb6lv63m6whOG8mRRr+dbAyLZ93NeSGz/FOTnaH3P2OA7kZ7HteTpJobm92lffsAy3K8GPuPN69it0AV9P7cKd8Mh+2F99+CHoDMr6MPFoxGIU8eqRVfF7glDYVyaejbfn7eEDPmt/CMlwwWT0N/EswSTHMt5tvknvk6fFcWCb/TnkwbGRvqCqN2zfBoXSwp6fRR3RGLtK8TWEO70bXR9BdLAK52P/KluJ/k9K9cr3Aqg/PieRDnXxz+XuQ9/y5zwCzMn/pL2+i5+G/+KOvJr4kVlLgr//q35Rv0d0vjF97xI4w+mLtQR8xH/RLw/G5rU4RjNu5U/eaehc6/4ez7v7urx/t794u8pHIvL2I0=
*/