
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
/xzl6ckdi1m1ctdvuDr82diSj6/lWSPi1ERxKwUXdPxZo6Nr4+9oFMfh4AyXwgHM1MmzvIDLG8KaBs/+1sbb8CzGMijXhnnSBuCbWJzmvNRxhr9FCbE0jxccVb95d9XI4rQF42WxsFbOnAKWzD80/wSFd8ts6QehF+ItUe0EP+BL8G1fPVXhfnJJHN/iPs3I2+E8PL+8vJ9u5K3LWHk/o5Y2grj6PNpKI8MkXTmJZZBH3YjL9CtLbP8wvrfCQ/vBW8jj+w3eWqOL9txxbcg/fHb1Nitg2vatN+2qF5rIE/367JKQ5kbS/Lqi2WBoPtPQbBSayBOaXyHNzaR5u6LZYmi2GppbFM1WRfOTpLlN5TuYvTe/3ejYZThP/VL87nlS+NMxB3awbqxl+brvWMKz7E+Kp2HDmY73303Hgv7x4b+6/55Va2IMGJ7tvYYeo7scFxy/qv3geTft9M2z4+em91BW1m6cbuq+2cjrDDUW9pi+eC7TnzyFY4Np6KwZKzLe7FhJS/0ex7a9T48l0iS+Xxe1/TsgYwj55ftg0PAmchfezjKyOcnUlZV80ojnj5D3+5V8ND0b3+McJev7zd2GgvDLdo/vyzGOp4+p8bTfjKcDpg8PCk/IE5oVnNfOI81PKJovMDTPNzQvEJrIE5of4Rh9odIbe0/DwawcL5K2w3Ymz38X10qMxVmskz/i+/lJ2Z+ZwaVGBxzc0r1Mxh7fLpE5GusNsXnjcmm3/9637/q/Qo17PV5QN+Wg4wVLOxYfH9fdK8VvJR2+IUb/VmQtebcxT+urHTuvN/p8pcl/gxqLemxibMXas3W2rrsCPp7ozluM7lxrylzH9PsVDc3TVsPT9Sbfjqm31+p4VqFcVxm/6EZjY07hvY3XAq7bdcS8ePoqyZeY0wk26WbJ9zbE5t/CPnqZ6aP3J/TRrULL2zSb/0HSgixi9v/DtYxBZ/y9jxj52RgGH2NbP54wVgHjd4Lg38b0bQn4DvYRMybuUPV/NmG+/jTbc94p6juBuGi//3221th4+nyfSxjfKBfr+y8Y2wIfwNDBfh/b9CnO+19dQj5MGfwS+fgqy2NNk+XZZpa3bf6GyIS+Yjz/W6bPrJ35jsyBpB/SsD7894SOPxdo6/l+rY75r2wf8e1bej809GoMvR+rfMhC9QXvMxu/dpaxNz9X+amnMl+V/4Vq9w1zQ53/yTLeIVbfJL8SPNRTHu83Up+nd62p73eGX5v/B1MP6CbGjfyTmge8r/3UON0Pm/y7dT2Uy+aJzlZlhkaLhS353LB8kBu4rCfSbuyWdSquS3FhWi+0ci3k/lp/DkLR4xoqOKqK4D1+Lbx0luyBWruWSn66MueMYU1LOE3I8e8n6LUZvKjckd8ylC8Ue4bUnrSfl1j/jiFQlHNef6ud3HpVub28B2vj61QPqfZUTVHu+8qtM3GdrNKsk8meSvl+kbUl2Y/oLu3u81xnPfed/6F4r9a8J7B96D3GqfWjXxulzmk/i74b+hA/2tNH+O3/qPKTHzE+1b85X6CM0CSes8vFSmCtC3/6W28a0lKH8UmXoLwZc0es451k8q5xZyJP41Yhre21tVuPQ37ivdBJ9oWf70FDz/fgg/6qiacJPM2r9bWrkU8aaIf4DCIb6Kmi8UiCzzAX+frO3utxr1qnL0Va7FlFcOMKfldPYn51PtjH55m3AIVn4CfHXlywTs2J5rtf2+KnGLxy34+LdJ2Uta1z8TrG81G+qb1zijHqx3hj7NvkyGCpok9fnfSJA/rLqGffMN/fwPPpI58Y9yOsb7x8nYyjv9q79KQNOGnrNSxZc7U+xUkiP+xrlsdbI3UDL+5/n4w8rR+ZRXZ9dvw=
*/