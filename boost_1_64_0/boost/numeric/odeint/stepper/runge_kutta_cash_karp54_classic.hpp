/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta_cash_karp54_classic.hpp

 [begin_description]
 Classical implementation of the Runge-Kutta Cash-Karp 5(4) method.
 [end_description]

 Copyright 2010-2013 Mario Mulansky
 Copyright 2010-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED


#include <boost/numeric/odeint/util/bind.hpp>

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/stepper_categories.hpp>
#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

namespace boost {
namespace numeric {
namespace odeint {




template<
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class runge_kutta_cash_karp54_classic
: public explicit_error_stepper_base<
  runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
  5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class runge_kutta_cash_karp54_classic : public explicit_error_stepper_base
#endif 
{


public :

    #ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_base<
    runge_kutta_cash_karp54_classic< State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
    5 , 5 , 4 , State , Value , Deriv , Time , Algebra , Operations , Resizer > stepper_base_type;
    #else
    typedef explicit_error_stepper_base< runge_kutta_cash_karp54_classic< ... > , ... > stepper_base_type;
    #endif

    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;

    #ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::stepper_type stepper_type;
    #endif


    runge_kutta_cash_karp54_classic( const algebra_type &algebra = algebra_type() ) : stepper_base_type( algebra )
    { }



    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        const value_type dc1 = c1 - static_cast<value_type> ( 2825 ) / static_cast<value_type>( 27648 );
        const value_type dc3 = c3 - static_cast<value_type> ( 18575 ) / static_cast<value_type>( 48384 );
        const value_type dc4 = c4 - static_cast<value_type> ( 13525 ) / static_cast<value_type>( 55296 );
        const value_type dc5 = static_cast<value_type> ( -277 ) / static_cast<value_type>( 14336 );
        const value_type dc6 = c6 - static_cast<value_type> ( 1 ) / static_cast<value_type> ( 4 );

        do_step_impl( system , in , dxdt , t , out , dt );

        //error estimate
        stepper_base_type::m_algebra.for_each6( xerr , dxdt , m_k3.m_v , m_k4.m_v , m_k5.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< time_type , time_type , time_type , time_type , time_type >( dt*dc1 , dt*dc3 , dt*dc4 , dt*dc5 , dt*dc6 ));

    }



    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
    {
        const value_type a2 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type a3 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type a4 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 5 );
        const value_type a5 = static_cast<value_type> ( 1 );
        const value_type a6 = static_cast<value_type> ( 7 ) / static_cast<value_type> ( 8 );

        const value_type b21 = static_cast<value_type> ( 1 ) / static_cast<value_type> ( 5 );
        const value_type b31 = static_cast<value_type> ( 3 ) / static_cast<value_type>( 40 );
        const value_type b32 = static_cast<value_type> ( 9 ) / static_cast<value_type>( 40 );
        const value_type b41 = static_cast<value_type> ( 3 ) / static_cast<value_type> ( 10 );
        const value_type b42 = static_cast<value_type> ( -9 ) / static_cast<value_type> ( 10 );
        const value_type b43 = static_cast<value_type> ( 6 ) / static_cast<value_type> ( 5 );
        const value_type b51 = static_cast<value_type> ( -11 ) / static_cast<value_type>( 54 );
        const value_type b52 = static_cast<value_type> ( 5 ) / static_cast<value_type> ( 2 );
        const value_type b53 = static_cast<value_type> ( -70 ) / static_cast<value_type>( 27 );
        const value_type b54 = static_cast<value_type> ( 35 ) / static_cast<value_type>( 27 );
        const value_type b61 = static_cast<value_type> ( 1631 ) / static_cast<value_type>( 55296 );
        const value_type b62 = static_cast<value_type> ( 175 ) / static_cast<value_type>( 512 );
        const value_type b63 = static_cast<value_type> ( 575 ) / static_cast<value_type>( 13824 );
        const value_type b64 = static_cast<value_type> ( 44275 ) / static_cast<value_type>( 110592 );
        const value_type b65 = static_cast<value_type> ( 253 ) / static_cast<value_type>( 4096 );

        const value_type c1 = static_cast<value_type> ( 37 ) / static_cast<value_type>( 378 );
        const value_type c3 = static_cast<value_type> ( 250 ) / static_cast<value_type>( 621 );
        const value_type c4 = static_cast<value_type> ( 125 ) / static_cast<value_type>( 594 );
        const value_type c6 = static_cast<value_type> ( 512 ) / static_cast<value_type>( 1771 );

        typename odeint::unwrap_reference< System >::type &sys = system;

        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl<StateIn> , detail::ref( *this ) , detail::_1 ) );

        //m_x1 = x + dt*b21*dxdt
        stepper_base_type::m_algebra.for_each3( m_x_tmp.m_v , in , dxdt ,
                typename operations_type::template scale_sum2< value_type , time_type >( 1.0 , dt*b21 ) );

        sys( m_x_tmp.m_v , m_k2.m_v , t + dt*a2 );
        // m_x_tmp = x + dt*b31*dxdt + dt*b32*m_x2
        stepper_base_type::m_algebra.for_each4( m_x_tmp.m_v , in , dxdt , m_k2.m_v ,
                typename operations_type::template scale_sum3< value_type , time_type , time_type >( 1.0 , dt*b31 , dt*b32 ));

        sys( m_x_tmp.m_v , m_k3.m_v , t + dt*a3 );
        // m_x_tmp = x + dt * (b41*dxdt + b42*m_x2 + b43*m_x3)
        stepper_base_type::m_algebra.for_each5( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v ,
                typename operations_type::template scale_sum4< value_type , time_type , time_type , time_type >( 1.0 , dt*b41 , dt*b42 , dt*b43 ));

        sys( m_x_tmp.m_v, m_k4.m_v , t + dt*a4 );
        stepper_base_type::m_algebra.for_each6( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b51 , dt*b52 , dt*b53 , dt*b54 ));

        sys( m_x_tmp.m_v , m_k5.m_v , t + dt*a5 );
        stepper_base_type::m_algebra.for_each7( m_x_tmp.m_v , in , dxdt , m_k2.m_v , m_k3.m_v , m_k4.m_v , m_k5.m_v ,
                typename operations_type::template scale_sum6< value_type , time_type , time_type , time_type , time_type , time_type >( 1.0 , dt*b61 , dt*b62 , dt*b63 , dt*b64 , dt*b65 ));

        sys( m_x_tmp.m_v , m_k6.m_v , t + dt*a6 );
        stepper_base_type::m_algebra.for_each6( out , in , dxdt , m_k3.m_v , m_k4.m_v , m_k6.m_v ,
                typename operations_type::template scale_sum5< value_type , time_type , time_type , time_type , time_type >( 1.0 , dt*c1 , dt*c3 , dt*c4 , dt*c6 ));

    }

    /**
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */
    template< class StateIn >
    void adjust_size( const StateIn &x )
    {
        resize_impl( x );
        stepper_base_type::adjust_size( x );
    }

private:

    template< class StateIn >
    bool resize_impl( const StateIn &x )
    {
        bool resized = false;
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        resized |= adjust_size_by_resizeability( m_k2 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k3 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k4 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k5 , x , typename is_resizeable<deriv_type>::type() );
        resized |= adjust_size_by_resizeability( m_k6 , x , typename is_resizeable<deriv_type>::type() );
        return resized;
    }


    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_k2, m_k3, m_k4, m_k5, m_k6;
    resizer_type m_resizer;

};



/************ DOXYGEN *************/

/**
 * \class runge_kutta_cash_karp54_classic
 * \brief The Runge-Kutta Cash-Karp method implemented without the generic Runge-Kutta algorithm.
 *
 * The Runge-Kutta Cash-Karp method is one of the standard methods for
 * solving ordinary differential equations, see
 * <a href="http://en.wikipedia.org/wiki/Cash%E2%80%93Karp_method">en.wikipedia.org/wiki/Cash-Karp_method</a>.
 * The method is explicit and fulfills the Error Stepper concept. Step size control
 * is provided but continuous output is not available for this method.
 * 
 * This class derives from explicit_error_stepper_base and inherits its interface via CRTP (current recurring
 * template pattern). This class implements the method directly, hence the generic Runge-Kutta algorithm is not used.
 *
 * \tparam State The state type.
 * \tparam Value The value type.
 * \tparam Deriv The type representing the time derivative of the state.
 * \tparam Time The time representing the independent variable - the time.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */


    /**
     * \fn runge_kutta_cash_karp54_classic::runge_kutta_cash_karp54_classic( const algebra_type &algebra )
     * \brief Constructs the runge_kutta_cash_karp54_classic class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn runge_kutta_cash_karp54_classic::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     *
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`. Futhermore, an
     * estimation of the error is stored in `xerr`. 
     * Access to this step functionality is provided by explicit_error_stepper_base and 
     * `do_step_impl` should not be called directly.

     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     * \param xerr The result of the error estimation is written in xerr.
     */

    /**
     * \fn runge_kutta_cash_karp54_classic::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_error_stepper_base and 
     * `do_step_impl` should not be called directly.
     *
     * \param system The system function to solve, hence the r.h.s. of the ODE. It must fulfill the
     *               Simple System concept.
     * \param in The state of the ODE which should be solved. in is not modified in this method
     * \param dxdt The derivative of x at t.
     * \param t The value of the time, at which the step should be performed.
     * \param out The result of the step is written in out.
     * \param dt The step size.
     */

} // odeint
} // numeric
} // boost




#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_CLASSIC_HPP_INCLUDED

/* runge_kutta_cash_karp54_classic.hpp
+RM2tNNLG3J/Fj5TySNJ5jFF5mFyyXA3wgWQ1zNVjXfNPZ7T3faknuODniplneF9kut9luf+PH+eopMrqH/wDOudteeq+F0+a1cteXDdW/cmJZ8rZT49zHyq2r5pJcyMzrQ/+0LvdWPJO8P+7Df7Kg8FuPWZJT7Lc9/vfamv8tLd67vc+zmN3D0M+8rLQ41qbHxrU2+/b/l7mfmeEldd3naOZUWlSllXn6PMdJffhFx7rjJddHr7ucqcpPbPDecgU56o7755bZ+TyrKyMovlQZG32esy2vLO9J3nOxW/tL4fPXUWT/uRvffUnEJyv5pcFX3VpAL+pVYM6B1a5PZem/e6qZQ3ubDYdTy+z+s1JkteSbG6pvKAj2UrubLY9dnuQ76W7UrVBh72tWw5niy3uGO70v4vyrb+Frn7vWrrYr736Vb/x3ws85n2UXnCR3ln+o7hXxUdfC518BFy3/dKB+SRn+mSx04fy8zXcl1t6lmlzA36s/bLQkCkxpxU9tsAye1zcIGSe8PBNZHcfN3mgiR3nYNrJrlZhs21lNxVJlfFeNGqG1+3UN8187Gv5Lush73qo8756rKrzl/3tWwu66dv+ijLbf1tr4/1zC0udP1O9ds+yqN3ZRYXuLyH5qO87Kxe+W7l2++j7rLT1XY44GPZMiuKXPftP+hj2ZCnlO2QlPVkYy9luaypHvGxXBmeckXWUV9lubx/f8xH/Z/p3dLjil/c0J/Z/w3WfmEnTsUzkrvYwW2VXEcHd6/kLjA5r3yb2zPSEz7WlQV/170ZvlTHbsp74AZr7v6lV+PWpDweoLu9R+ZjW6eV5Cv1/9ZXWRlqv/2HUvePqfvG+dY7v99Ucd4+KS8tN5NfTUy1TkpU+/xRyecTmc9FyD7pWz6TXN4PU2MQmU87gea8y0fWxq1/iCDlXQPyuXgBF2Q+JqcPsLjhDq7OAKs8/eC+86U8rnP4Gkp5Wsm8u8l8TK6t5JIcXDu45QtZGYX7R1Vt3QNKWC8vTM9V26BukNf9U8ozd71X5fkrdetBmf+yiCeTyP3ByzK7/z5pQ5/LzFN/F3mNfJaX5XHbCy7Qd3musX9TRacT0elvyPTo9CJpG5PgniEenSBsLlvayygHlwv3HO2R6eAKBljflb7bwRXD/UC6bQ6uTOY7xczXy7bM4P0l1T+2Veo2RZbvWUe+10ouw1HfWZJb7eAWSy6tls2tgru9lhXT/yq5NZK70cGtt+pGnG9zd8ItuBkLEXBe1pcRzO135JT6PkoeO8ljgCB/L/Pg6Pa+hZLH87K+G3QE6xa3S3LrHNzLcN9QFm6E864sabwAotY3xLe+4Ck8w3cXe/ksz/15XJjP8tyfMfX1WZ77em9/3+RlSfeslG+gYhvNBzLeLrH2gqvpTZuTh7v9DVbyaE0eCeQRgtxa3uWRx0KeSx7DlDzaDbR83aXIre1dHmThlkeEkkfHgZaPeABfWcebPCpH314ueYxQ8ug30PK7eeRRV/bLAZL7TMB5na+bXY3yza7OuJ4U46O8jLJ81/WzWEUv10gdCPRS3ysdEEu7zpsu8b7MWfyTj6JUeYk+ypOPohSdjgnyeu5gynN9FjfWV1kuz0zG+1jP9DPU81KlrXfR1uuXWvF54KmxSfa9oZrNvQb3PukGOtLtGWjFMpGGzb0n04U40h2UXJdKrmqxfVrJlIJ06//UyWkel/EuPcjb5xVOme5jSqY6f5Flb4/sprI+xoUWN9zkqtg/HHm75OsJ8vY5npRXnJ5zSkkelxgoN8jb3xtR5BYVlngqXN9fOfcyM3Kqa7SFXtu8+T5CSkVqufvv617pq7ySolyPS1uV+CzPk+1WvjJf5Z1h3+k=
*/