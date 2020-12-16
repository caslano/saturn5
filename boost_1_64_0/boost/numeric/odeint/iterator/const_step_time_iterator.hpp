
/*
 [auto_generated]
 boost/numeric/odeint/iterator/const_step_time_iterator.hpp

 [begin_description]
 Iterator for iterating throught the solution of an ODE with constant step size. The dereferences types containes also the time.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/iterator/detail/ode_iterator_base.hpp>
#include <boost/numeric/odeint/iterator/impl/const_step_iterator_impl.hpp>

namespace boost {
namespace numeric {
namespace odeint {

    /* use the const_step_iterator_impl with the right tags */
    template< class Stepper , class System , class State
#ifndef DOXYGEN_SKIP
        , class StepperTag = typename base_tag< typename traits::stepper_category< Stepper >::type >::type
#endif
    >
    class const_step_time_iterator : public const_step_iterator_impl<
            const_step_time_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef const_step_time_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        const_step_time_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        const_step_time_iterator( Stepper stepper , System sys , State &s )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_time_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    template< class Stepper , class System , class State >
    const_step_time_iterator< Stepper , System , State > make_const_step_time_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return const_step_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    const_step_time_iterator< Stepper , System , State > make_const_step_time_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return const_step_time_iterator< Stepper , System , State >( stepper , system , x );
    }


    template< class Stepper , class System , class State >
    std::pair< const_step_time_iterator< Stepper , System , State > , const_step_time_iterator< Stepper , System , State > >
    make_const_step_time_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            const_step_time_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            const_step_time_iterator< Stepper , System , State >( stepper , system , x ) );
    }

    /**
     * \class const_step_time_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is a std::pair containing state and time.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with constant step size dt.
     * After each iteration the iterator dereferences to a pair containing
     * state and time at the next time point t+dt..
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_const routine.
     *
     * const_step_time_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is a pair with the state type and time type of the stepper.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_const_step_time_iterator_begin( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for const_step_time_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step time iterator.
     */


    /**
     * \fn make_const_step_time_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for const_step_time_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator store a reference of s and changes its value during the iteration.
     * \returns The const step time iterator.
     */


    /**
     * \fn make_const_step_time_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt)
     *
     * \brief Factory function to construct a single pass range of const_step_time_iterator. A range is here a pair of const_step_time_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_time_iterator stores a reference of s and changes its value during the iteration.
     * \param t The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step time range.
     */







} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_TIME_ITERATOR_HPP_INCLUDED

/* const_step_time_iterator.hpp
zz383cx/99PGoZ7Ixj2s205aj+hyaPujSNdP6WyTe0v45HBpHbpB2vyu0vYH0PVTpe1fKyZx0maf2XfAp4O2k+ubFtIvDILYOLvDjLMnIH33/2GcYTyUHWfVZcbZ7IRxNhPtnYM7Ie492pLvd2k1ZOPHnqRX67HHeIVV60VrG0s2K0lveyc/9g5l8/y+D+q1Y+8owPTYm4U0x57kUaefgHTi2JtCG5wOVK+njsjYQ13JY28O4IKTPPbmAs40+QzHHuqJxt483XbSmo+f1uHjpjw+3NirXWvHHsZANPaWkPaCKdP2Yy8kjjbUVoRjpXJV6Z0uuKHU0cev8t8puLzUi88+/TYpTgrhuJHea57FN6XkDFVhcKzYn9s/IrC54q/69HzoeTF/EGct0tBkwVvgzoOos02I21mk3+v36JcG7vsMB0ZyQQQ7MXDfcISRzgrQH8jgIwtBI8mrty+rHX1Xa38Qweo8DM8KFEOf/CzoQyPivPonVhUvLfSdl0NfUe20hWrMbQtQvRwMy4luyh3B89XdEP2+9OL15l1k3o9weUuZp9d9R+36Dd9FXrY+LPO0hDKzq5PLPJ1llq+Pn13z5/PoKzENbCe30aCe98pWqPZX+fYDH+99yWgVUJI8frm0zPn2SdJyfJ9EvrW92blI31Hk3KDyazivuD7lp26Mr58fq899UGYqv5YyQx7rljMllcr+OPpzEs5N1LP8BvJOfNSVjL+J+A3E92/tLfZ/yxug6j3wJuDZvC8t5BuD2maRx1Ejn1bWt0XVd8E8zavo4HSzvt3Gstu1DhKPMZBYRr5hdrDMTlOGtjuxTAfLdBoZFgORoX4ftYv43Qlj7Q1883yXpcV67fxxGmntScBPmm+eTfwzInkeMSc8RwAd5t+VC+S9p+f6cfXs3Ajvcz7Pp3dkEGctQJo6G16UXMV1qpSMRUinuxmv26faWvzIKSX8mHkz6zjBY+4/PZPOB0yj5/fvzI2InwIYaO1vSR/sGDgtkzlbw2d4eBClq4L923JjQutxoDU0MgaLKmVmBfu7M7gu2i8wyAl42exQwWeEa4dVYCWt2lMdpLpP7+5p3dnTtjN8JVyl0apVyXFGYavT/f15X6CU8DKonRAfL03WsowA7LptcjlbTJ3b7VvvcaPYdf1h2lfm0pkojfmFMX0HAFvgbaGjR0PYo9KgH7sLcUjcJP6LQ8MZrIl63vk3cEux5Qc9X6OZUgziMa+36KsRH+1TrRmnsEg8EsYUJQwxtotj7Osh0DkxnLtdJc7LjuCrvQwzkqNo1Lm6z8ZCllt3Z9zUs5RubPRt7t/r3MF+Fe9wHLSsnpQfK6+IjZUCuio1kB4eyh5U+jsthI/m8sVobFYSN5vbP4TrUR5+RjXGSAj3SinreB5W6EMExRTf6cquN/BCMT/WVwxqua4+rNq/4LD1dsIx5e1VjvZqeewOeHFfCoPV9xFhlQ42BiDqWk7f4BztGyTrmJ43gRNEa+azS/KmuFmXyDsUt4dtqqa8vVhDWGE9ZZ06N5OHT1jDu+RFbVMmHrfJ3yRT0DUnv32U35NiZ/fFB8aeU7Cd/vuB9ZPx330taOlZY/iqzfftK40Y59DL3hzqoa/HebpS+3xHBOdyPjpPze8reU8mgQZ9xziN80njAkVjiH83HEab+or5bH39mjVOX/+L8rU6TuT+9XEf6CLyDFssd44SfOqL11uZzQguYdlLWRZ1gI58C15maFqf+2WOZhCneTlpvlxoer5faL49X7le/PIlHjaWjb7T5vrzjkV9Du5VTv8PKbe9MLjch/Jq5HUokt3o+riP9Gry+hrV/pxq/+uMX3kV0g8v1e1FDCfSuHq9xD2ehjY=
*/