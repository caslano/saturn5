
/*
 [auto_generated]
 boost/numeric/odeint/iterator/n_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size performing exactly n steps.
 [end_description]

 Copyright 2009-2013 Karsten Ahnert
 Copyright 2009-2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_N_STEP_ITERATOR_HPP_INCLUDED


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
    class n_step_iterator : public n_step_iterator_impl<
            n_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef n_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        n_step_iterator( Stepper stepper , System sys , State &s , time_type t , time_type dt , size_t num_of_steps )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t , dt , num_of_steps )
        {}

        n_step_iterator( Stepper stepper , System sys , State &s )
            : n_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System, State > make_n_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps );
    }

    template< class Stepper , class System , class State >
    n_step_iterator< Stepper , System , State > make_n_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return n_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< n_step_iterator< Stepper , System , State > , n_step_iterator< Stepper , System , State > >
    make_n_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t ,
        typename traits::time_type< Stepper >::type dt ,
        size_t num_of_steps )
    {
        return std::make_pair(
            n_step_iterator< Stepper , System , State >( stepper , system , x , t , dt , num_of_steps ) ,
            n_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }


    /**
     * \class n_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE starting from t
     * with n steps and a constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_n_steps routine.
     *
     * n_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_n_step_iterator_begin( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , size_t num_of_steps )
     *
     * \brief Factory function for n_step_iterator. Constructs a begin iterator.
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
     * \fn make_n_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for n_step_iterator. Constructs an end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_n_step_range( Stepper stepper , System system , State &x , typename traits::time_type< Stepper >::type t , typename traits::time_type< Stepper >::type dt , , size_t num_of_steps )
     *
     * \brief Factory function to construct a single pass range of n-step iterators. A range is here a pair
     * of n_step_iterator.
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

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_N_STEP_ITERATOR_HPP_INCLUDED

/* n_step_iterator.hpp
Ue9ycgvDn9C7vLViF+eXJ1R6TmYK8ClXqMlcAU9zwTGuPD9uBN4nnkWiiBG2DGoq1ZZXW0oxjXFa3LvlgM5KEIiYRko97dN5yjNqWagIbfsxIDh1Vi6pn2yaYpjO4RdLqU5HhdKM4B69Oe196OWK3oadPaAoPJ5RO5B6I0qYgu3r0aDp/SXgMd05L3vp0oIFqggOodPpevTsNg/Bdl54L+SUiZBn3DQsMTwdDI96g7A3GDQdd9Yo4YdOtx8OL5pgXUof2LYqCzFkel5KOW7Jpo0Fo85pu1DsWFE1GupxR/EddHg1CX/3R0fDcd+H3UGlupFy1u+d9EcVo0Zpvwo0LvKE2l5gGeNCu4q5bYP2Fl+tesre+rZXxjT5YAvRXTLfSeByf402vYAzqdIqjG4Nuk6stg1lmXfqFBQa/4fsriAv3jtQB1yVqZ71SCDLivxNhAulVzpO5cuaYtc1KolSoEZ35L2KXO/XBdkRLW1JcpSvjqLQ0HeKVrrei/cPUEsDBAoAAAAIAC1nSlI3HmWK8wMAAHYJAAAiAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWI1MTMuY1VUBQABtkgkYK1VXZPaNhR951fc0BdgXEjy1IS0Uy+wCQ3FDHib2c7OaGRbYLXC
*/