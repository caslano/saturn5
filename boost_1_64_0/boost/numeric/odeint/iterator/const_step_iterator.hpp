
/*
 [auto_generated]
 boost/numeric/odeint/iterator/const_step_iterator.hpp

 [begin_description]
 Iterator for iterating through the solution of an ODE with constant step size.
 [end_description]

 Copyright 2012-2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED


#include <boost/numeric/odeint/util/stepper_traits.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
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
    class const_step_iterator : public const_step_iterator_impl<
            const_step_iterator< Stepper , System , State , StepperTag > ,
            Stepper , System , State , detail::ode_state_iterator_tag , StepperTag
        >
    {
        typedef typename traits::time_type< Stepper >::type time_type;
        typedef const_step_iterator< Stepper , System , State , StepperTag > iterator_type;

    public:
        const_step_iterator( Stepper stepper , System sys , State &s , time_type t_start , time_type t_end , time_type dt )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s , t_start , t_end , dt )
        {}

        const_step_iterator( Stepper stepper , System sys , State &s )
            : const_step_iterator_impl< iterator_type , Stepper , System , State , detail::ode_state_iterator_tag , StepperTag >( stepper , sys , s )
        {}
    };

    /* make functions */

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System, State > make_const_step_iterator_begin(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt );
    }

    template< class Stepper , class System , class State >
    const_step_iterator< Stepper , System , State > make_const_step_iterator_end(
        Stepper stepper ,
        System system , 
        State &x )
    {
        return const_step_iterator< Stepper , System , State >( stepper , system , x );
    }

    template< class Stepper , class System , class State >
    std::pair< const_step_iterator< Stepper , System , State > , const_step_iterator< Stepper , System , State > >
    make_const_step_range(
        Stepper stepper ,
        System system , 
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
    {
        return std::make_pair(
            const_step_iterator< Stepper , System , State >( stepper , system , x , t_start , t_end , dt ) ,
            const_step_iterator< Stepper , System , State >( stepper , system , x )
            );
    }



    /**
     * \class const_step_iterator
     *
     * \brief ODE Iterator with constant step size. The value type of this iterator is the state type of the stepper.
     *
     * Implements an iterator representing the solution of an ODE from t_start
     * to t_end evaluated at steps with constant step size dt.
     * After each iteration the iterator dereferences to the state x at the next
     * time t+dt.
     * This iterator can be used with Steppers and
     * DenseOutputSteppers and it always makes use of the all the given steppers
     * capabilities. A for_each over such an iterator range behaves similar to
     * the integrate_const routine.
     *
     * const_step_iterator is a model of single-pass iterator.
     *
     * The value type of this iterator is the state type of the stepper. Hence one can only access the state and not the current time.
     *
     * \tparam Stepper The stepper type which should be used during the iteration.
     * \tparam System The type of the system function (ODE) which should be solved.
     * \tparam State The state type of the ODE.
     */


    /**
     * \fn make_const_step_iterator_begin(
        Stepper stepper ,
        System system ,
        State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function for const_step_iterator. Constructs a begin iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step iterator.
     */


    /**
     * \fn make_const_step_iterator_end( Stepper stepper , System system , State &x )
     * \brief Factory function for const_step_iterator. Constructs a end iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator stores a reference of s and changes its value during the iteration.
     * \returns The const_step_iterator.
     */


    /**
     * \fn make_const_step_range( Stepper stepper , System system , State &x ,
        typename traits::time_type< Stepper >::type t_start ,
        typename traits::time_type< Stepper >::type t_end ,
        typename traits::time_type< Stepper >::type dt )
     *
     * \brief Factory function to construct a single pass range of const step iterators. A range is here a pair
     * of const_step_iterator.
     *
     * \param stepper The stepper to use during the iteration.
     * \param system The system function (ODE) to solve.
     * \param x The initial state. const_step_iterator store a reference of s and changes its value during the iteration.
     * \param t_start The initial time.
     * \param t_end The end time, at which the iteration should stop.
     * \param dt The initial time step.
     * \returns The const step range.
     */


} // namespace odeint
} // namespace numeric
} // namespace boost

//#include <boost/numeric/odeint/iterator/impl/const_step_iterator_dense_output_impl.hpp>

#endif // BOOST_NUMERIC_ODEINT_ITERATOR_CONST_STEP_ODE_ITERATOR_HPP_INCLUDED

/* const_step_iterator.hpp
G17xf6hn0WHWc/i8nlyXJOfVSs7zjZznJ8j5OMBWPwb1ttAfe8tJnDfEJojvZL5RnlyX7F/Z7+aFwCMtiW9vaJ3AMbW4Ts2NQtfQljdPl9bRHhNXfsbXoz1epnjWuJbnE4FHHsrTJA/LLS7xhK7grgAu7aihKz/7Lb2qLu6r27dFVtfpb33xJ2ReRvwVoQE7LbYa/3oaa+voQzBf+3m1dYJr/TzAEv289exP5MfeB9gA+PRKKSN0MXrqrA8X0rc+XINqL31I4MXrb5Q+Ia0EeuyTzYm4yfNpi+ZR4xoetyTQRF4izW2WJnEtze2qj/aZPtpRx3RlPL0voc8A89/lwI2Nwc66OE7P0vE4XUYXMXfGdLFHaCA/+WzgbmkH9VTasQd5mt7v9Tec6m87Xs9gOeTxe0ylac8033bvLcXyqIP4zJc06Yk8df6jTE9P4FuPbcv3gMiTbYvTGUS+lv9nFF1rF7WunC39IHimH4ZLba4UGUjfJY/rUV+G/jx9MClD+2XeIy8IXeQlf1+PCS+Utx7jxpayzAHRFaZFluc9kbJUfXwe8s13PvDiNF6QZAuIZ8ftBXbcWjz2xQuNXIsJY+LFCfMSxhZ+cX15ifCncAwu+bvEjInBMm37Hnkiri97GXD5Zjtx7S/J568KLqd+oEy0bqS/l8YCU958L73S8Mg9+sTv4leFdsSP2Wlcs3i18R9Qz4Q0XqvHPaicPy++zjqIda2E9YpEO351nfre4duEnOuTvhVpX7XcZwZvqrO8ezxfl317483i+yTi2vOA1wK/NrZmPISgLgcyBRV/DWeoMqMIXq7exR46N4MYIVxXfWudWlfl2jC/n3F3XZaIFXCC93KJOprLZX1RlUapxPu4U6jzLLb1es+zI8o4fkjPDcLC8lbwGG5aynoc3urO51mBrNsVc7nUcHrkoFq345pDaT/27Uo+qxWvhsvGkv/9JepZYwVkfCgZpYaKmWGhpIDRmt1N1P8atv1Gzw/e1uFa4zvrXF24WLpP0i0VIwjwI338LtWGbRWTr9+fUSRNjJxMul/qwJm5sXweZwyARxh0q5geysp9ylm+DyRdTd2r4RroexRfcw+hO/QvOEbFv3ivsok67fAC9f4ZdCa29nkr0prOB2Su8Xl2HexDJn/MvFPwEfrHN5h6Pmbq+bjYJ6ZJl7h2nf920749tEm/PEbWQHT6DknLOr6kQdKkp6s0n1kvxaAI62wK+DeymsL1OqYRp4x5Ps5Ijnf+uS5ZHCqli3zPaQzHKPMKZ768CeXnjQWBH0s+nUN6UbjG159C2H79RsLSwB+auK+e73x/QenRia5MbxaGcGgkej1Ug/S6IO34C+QbQs6kG18gEQ8S+YrYbOR7uw3cEC+nvsuQ523218RXBn5cN77B+e/5S2Rv+VtGn76NtH4n5DsJPksSn9/TvhXrsr4hyguvkMEPRDc9Tfs2x490vq6T+T8ps54wZtbffmb8Sf5ivuFdImfSiv/s3PhL4Y345p0t5G+PrSlhjuQ69CJQ49/QpwGeB/H2f2xAza2jLs3YpqV9nd+KLoJKbzZ9dqamoNeoNYi6WOLj9YqPOr8eXoz+7iQfCyDnMw0fdyXw8XvFx+/JR6/lQ0DR/LVluay96jfoZyDNGEWQj8RGSKHevc6/ILzCnUUjkGMWcH9zMD2Ct040bLryTY5c6t8KzqQHWJjt+5OfV0ZwNCuVGxgoZIqBlH9CCAeReF1Hww9CQDMS4py11M8/6WxR0oj3h7PguZF0FnMlbcmfldwWRf2HWPlp2TI3wPJ7c5Psf/+ufZ0630P/9h7z7Xyv2A6TB2uBdKK/MYU2uP7+a535DmRdSWerHgRccJI=
*/