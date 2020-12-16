
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
d1qt0etvGd+jDvmy7iP2ZZ6mRVtQb3C3zi6Pu9Hgzq4uj9vAdjne+L1PWel6pBz8ES+rJtW2O8m7ptMsusL88fJp1Tisy+JsBY7+jv++Wc9aUYa/7Rzva3k//kYX50juP/LuKhb+zZ5rcah4cBfhak4bGx3FUR/C6+kv7Fxn/YXuwTSiLUfnuzSIZ7rIu7dP4MPTt75XRznbO8k6/FxD21vyFbo8r6OZvkJ4p6bNT+zpYAt9j+51k/E94pWlsEWU6w/jp+VZT/g90ocDDzqe5dnufQKm/ZuDNTrdEhR7s4Gk+4NsGnNxr39FU92BuCgYkQzgl+7771L9cClk1NTsHgSUyYnp8vf9y5YRf+A0L0+17oi0tk2nh7YDeLKucMY6NQ+zzHPMPPxcpiG3kA7TwLVxG1E+ef5My3gHTjjOx7i2tPgYE0NAjTmNq+llNI/kSce12LES9bG/13i7PxaezXyi7/tgOXVqCOUag77BNP7nXgbyCiVJr6viX4lNvvy48Kd9obNBC3Sl7yaiS/kPG/mPrLN08aYdYA3kt3HJZMZAWFHN6lRfLu91P3wLbGXc18mvk7eCtewKoZ4AX/RkjHwmvbmzj31u39zZD/iE+EEc/6Cy19Af4MXlcF40R5Iecez7OC8AjGuaCfUmvxtzAdt8lWrzC5PaTP/jRWXa/GLRXeID1+jmS+gDX8X+0Pjuva1LkK91/VLTbtIEbrzdl5l2W15lXEq7L9dlktvHeqTMK0y/mjLEF5lcwXnu4uP45rN+k5A0oPMoG2/Pq0WWxBtvV16r/KHUsXF7d5XoE/JoQ1R89KspZ+TRjqk0yr9hLus3Y1/35TWkMVpJmsaHr0Jb22mHxjxOv3pnt5gblfd0gds/nD4QqPd1RzJ7VX41Y+2t4vm169bp82u9+Eodi76Yw5TMDVtXxO9h9iz19qk3tSas723rmK6Re+rXT2q+dfMV21f6Dg8k7k1lkM6X2nAD6FWhDr63CwjuZkZt4FvKeBIYXLAVKo16+E3At0TlvWjzZrR5//nI4MZo/Eg55AE37tO8E3hSh/1NXMe7TR0aT9dxs/a3/Zv3Zk2b+jQmaeKHNK0O36rHFt8E1Ok7TPrCCpX2JEx6ejxdybgx4NWnrjlJxoSWiR6Tn6B9u01/W2u5GPxPKtlhjMAW8LyJsQefAp6lZX3xzxj52vceP7dO7np+yfuX7QH/xhhqz2tf7sTADaHeoWJBxiTe9xkcGihGY3g1x2Qp1uUXlD6vdfqMZbRYmCYFmjDu+STLOjl/yfh9XzZ+31eYBtz6a8BN7pOvi7+m9R/4FveI4JuCS7zyuN9OGCdJY/G7Bk/vS2q8O2Uu0nXTVlu6M4If6DklUUdwl4H6+33KlW0jvuVF2vZT4Ou3Rm3cvJ9Hc5XUOcr4ob9Ann4vAUXv02vZVo9/req6IUHPfxvlC88yjhFLeZ2J4VeN+tR7nxfORKyf2BpufsiPDY6VyqCrS6fnyzjCGGmPcB9a7vzrkdV6XG2TMeO/jf6sxsyO8D39kaLWe4K03pf6cF+Z7/a7jV4Qh/oRltN6ca/oG3Uy2X7fr3Rd4xXJi9aHv5pxoeu34+JBbduIa8fk3xNwTjD+0D/FnzPzo9DMaj7hzz1i5pD5nDP+5Wmhv8wcsoDpoC5M15l8m17E9HTiX8v0laR/r8E/06RbTPoipM18wTmDcyP76si6cBw/rk729yEH2kDxhbLPCO0tdZTpMa/DpbjtjweN+Yf0hTa3p0awX+LiK6fWrK/Bl5f/fmQ9R4GGe0VMfKXRoET/6LrJ+Fqafk3NWtJ3shkLpG9K7Zpdp9rFtG3XHMAWHGa9/wXvp9SSRonXixcKr0w=
*/