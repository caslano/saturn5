
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
IEJIW0eqs6mruzXV2YU/t3V094Cuy6uwed2tXbt9jIeZ3s442m9cH1IYzBWKbu0kNZofcpFMh8KnBE5bWyazEe2tifGwo6Pj1F2dqeYdba3tPQHrF7iru7UrqFV1X8O6s7nc2WOjKR+Ew9dpgK6u5PnH2Zyh0i1eJuT+7lsoq/fHzomnh1L+c1q+dysdjOZS7joB5sya50p/rwPuAnbn+nJZtRZeDbg3o/LmmB8Xcx28D0tjI/KW9MV+jiI+aVzr/RXA3DQP2Cr6ctcpu7towvZWoL2iU28z/vVt1cnn0G+gXr2d+LfHZIV9a3ihIif6LjK3qLUNv6zkVcW3VOXNYp5ToaE+oVcd0Qt9FMoBMvNzyYCL+1Kic72XWTjHFBmz+B1eZk4EqWixpZ5yu1HLzc89rEtPPARNuJ43ybJOhu80tuhdxha9m2nAuUccj4/QVB0f8z9ZHvbNLcpuDKo+fr+aP95hbAhoon4TQwxpvi+PfPFNVf9mc9g51z5kVeDjEqu9dS7TAsfsr4vO630irlf50DCA1dAP/bD0D/10swak1oH0vvVItToD+lRYc/5r41B8bH08nuvDc8fr/ieAQ3kRx+yBIz/Z/0vmV+vCHXZthfFbLU9j9n4Yyj0lZle7O5pPTbW1b+lINbW0dLV2dwcNsKEVtKGfow11pirlh4I2oxYO9h7g2/El+0B9+ALSoT11dn0G6OM9JcAqDfUxPxsamPvmqZjIbqT7+rCIP97G9mJzPBz8kX0lbkbgXqeqaUM8h9q+KtsSe+uRdDyb2saWsS2LjG1x8lka9OGaeiYVUsImvq9d9LxxXD5tPPNbbL7nEvmkv435bhSGpKVd/TrPk5W8QZ3nScoabza0V4NpeOa1XGv9shproz6fshH1FQj6MvEbfxLlnF591djArxkb+HWmAacNVDaP51/9+YMEe0ZaEg+Pc9fGhfE6v2fqvJPpR1fG0w+Z9IMmfa9JP2DSf5E0+aTPzzaBD8/nz1S+g4GPWDvuMvkPmfxfmvwHTf6vTf69Jv+3Jv8Bk/97k/8Xk/9HyvkRwB93EWUr68XhWxDM43xGWy1pjfvipwvu41eFuLcTF/rNNOthekTSievUxcp4XQ+S53vIl9jdZD/oH8DXMf2S10Irg4fZ9+hj8il0mKYeAntVXB7/ZtklMpdZvpBW7QRf0+rN+jnjoN2f0C5XxrZrRn1cTpB3rP+qTD7kH8t/nMmfbvJnId+2YbqNTSY06Iea2GSGhsRYUvuO9WG7/8x267O12yricchORHpxzI/N5unDcD7K7nfpWq63zKvX6y0jzqwVVYg7DSi/BjqJco7/4+rj79aE+p5zDpPw59Mp71TJXOlhcMYQr4Hr1scrvmd5+4zDZhmgYfOOe81Y+xJbnZQLzpLfWvkv6Ll2PpntfEOsH4ZMu2xb+S3h8QK9R8q2C6w6hMEZVX6nkeN8pG25BQ7Gctv5rbCw3n4rDKSSW52cV/aNvsOk5eR3AuW3e1rJF2zr7Ozq6HEf+J0dnT3dpW/8CN7WvLMz8LBpAttagk2PYFu3drJspeB17l4b4s2IYD3NJbxZEaxzVwk2O4LtainBnij0ItjTdR21YR3PiGBdHbt62tq3EndFBN/S1bR1J5YRQvyaCN7aXaJ7cgRr2hY8EMLqY7JAbYRviODtHe2tIc2NEaylu0fJc6fgtpTKtyu6O7bs2byTuP+WdjSdRlhQUYLtbNpDWAVgxGv1yyAtrgD7alweBNXd2lyqe3qZ/I4tW3Z0NLUEvh/H45zWvjukf8S4PM/YfcvwDfEkfkMsga4RK/xwYMKtu6j9Of+NYO3yU5XtHjPrfy49EzhPo+0+kTqtad4=
*/