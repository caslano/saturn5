/*
 [auto_generated]
 boost/numeric/odeint/stepper/explicit_error_generic_rk.hpp

 [begin_description]
 Implementation of the generic Runge Kutta error stepper. Base class for many RK error steppers.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED

#include <boost/numeric/odeint/stepper/base/explicit_error_stepper_base.hpp>

#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_algorithm.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_call_algebra.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_operations.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>



namespace boost {
namespace numeric {
namespace odeint {


template<
size_t StageCount,
size_t Order,
size_t StepperOrder ,
size_t ErrorOrder ,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
#ifndef DOXYGEN_SKIP
class explicit_error_generic_rk
: public explicit_error_stepper_base<
  explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
  Value , Deriv , Time , Algebra , Operations , Resizer > ,
  Order , StepperOrder , ErrorOrder , State , Value , Deriv , Time , Algebra ,
  Operations , Resizer >
#else
class explicit_error_generic_rk : public explicit_error_stepper_base
#endif
{

public:
#ifndef DOXYGEN_SKIP
    typedef explicit_error_stepper_base<
            explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
            Value , Deriv , Time , Algebra , Operations , Resizer > ,
            Order , StepperOrder , ErrorOrder , State , Value , Deriv , Time , Algebra ,
            Operations , Resizer > stepper_base_type;
#else
    typedef explicit_stepper_base< ... > stepper_base_type;
#endif
    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_type;
#ifndef DOXYGEN_SKIP
    typedef explicit_error_generic_rk< StageCount , Order , StepperOrder , ErrorOrder , State ,
            Value , Deriv , Time , Algebra , Operations , Resizer > stepper_type;
#endif
    typedef detail::generic_rk_algorithm< StageCount , Value , Algebra , Operations > rk_algorithm_type;

    typedef typename rk_algorithm_type::coef_a_type coef_a_type;
    typedef typename rk_algorithm_type::coef_b_type coef_b_type;
    typedef typename rk_algorithm_type::coef_c_type coef_c_type;

    static const size_t stage_count = StageCount;

private:


public:

    // we use an explicit_generic_rk to do the normal rk step
    // and add a separate calculation of the error estimate afterwards
    explicit_error_generic_rk( const coef_a_type &a ,
            const coef_b_type &b ,
            const coef_b_type &b2 ,
            const coef_c_type &c ,
            const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_rk_algorithm( a , b , c ) , m_b2( b2 )
    { }


    template< class System , class StateIn , class DerivIn , class StateOut , class Err >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt , Err &xerr )
    {
        // normal step
        do_step_impl( system , in , dxdt , t , out , dt );

        // additionally, perform the error calculation
        detail::template generic_rk_call_algebra< StageCount , algebra_type >()( stepper_base_type::m_algebra ,
                xerr , dxdt , m_F , detail::generic_rk_scale_sum_err< StageCount , operations_type , value_type , time_type >( m_b2 , dt) );
    }


    template< class System , class StateIn , class DerivIn , class StateOut >
    void do_step_impl( System system , const StateIn &in , const DerivIn &dxdt ,
            time_type t , StateOut &out , time_type dt )
    {
        m_resizer.adjust_size( in , detail::bind( &stepper_type::template resize_impl< StateIn > , detail::ref( *this ) , detail::_1 ) );

        // actual calculation done in generic_rk.hpp
        m_rk_algorithm.do_step( stepper_base_type::m_algebra , system , in , dxdt , t , out , dt , m_x_tmp.m_v , m_F );
    }


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
        bool resized( false );
        resized |= adjust_size_by_resizeability( m_x_tmp , x , typename is_resizeable<state_type>::type() );
        for( size_t i = 0 ; i < StageCount-1 ; ++i )
        {
            resized |= adjust_size_by_resizeability( m_F[i] , x , typename is_resizeable<deriv_type>::type() );
        }
        return resized;
    }


    rk_algorithm_type m_rk_algorithm;
    coef_b_type m_b2;

    resizer_type m_resizer;

    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_F[StageCount-1];

};


/********* DOXYGEN *********/

/**
 * \class explicit_error_generic_rk
 * \brief A generic implementation of explicit Runge-Kutta algorithms with error estimation. This class is as a
 * base class for all explicit Runge-Kutta steppers with error estimation.
 *
 * This class implements the explicit Runge-Kutta algorithms with error estimation in a generic way.
 * The Butcher tableau is passed to the stepper which constructs the stepper scheme with the help of a
 * template-metaprogramming algorithm. ToDo : Add example!
 * 
 * This class derives explicit_error_stepper_base which provides the stepper interface.
 *
 * \tparam StageCount The number of stages of the Runge-Kutta algorithm.
 * \tparam Order The order of a stepper if the stepper is used without error estimation.
 * \tparam StepperOrder The order of a step if the stepper is used with error estimation. Usually Order and StepperOrder have 
 * the same value.
 * \tparam ErrorOrder The order of the error step if the stepper is used with error estimation.
 * \tparam State The type representing the state of the ODE.
 * \tparam Value The floating point type which is used in the computations.
 * \tparam Time The type representing the independent variable - the time - of the ODE.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */


    /**
     * \fn explicit_error_generic_rk::explicit_error_generic_rk( const coef_a_type &a , const coef_b_type &b , const coef_b_type &b2 , const coef_c_type &c , const algebra_type &algebra )
     * \brief Constructs the explicit_error_generik_rk class with the given parameters a, b, b2 and c. See examples section for details on the coefficients.
     *
     * \param a Triangular matrix of parameters b in the Butcher tableau.
     * \param b Last row of the butcher tableau.
     * \param b2 Parameters for lower-order evaluation to estimate the error.
     * \param c Parameters to calculate the time points in the Butcher tableau.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */


    /**
     * \fn explicit_error_generic_rk::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt , Err &xerr )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`. Futhermore, an
     * estimation of the error is stored in `xerr`. `do_step_impl` is used by explicit_error_stepper_base.
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
     * \fn explicit_error_generic_rk::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out-of-place, hence the input is in `in` and the output in `out`.
     * Access to this step functionality is provided by explicit_stepper_base and 
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

    /**
     * \fn explicit_error_generic_rk::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

}
}
}


#endif // BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_ERROR_GENERIC_RK_HPP_INCLUDED

/* explicit_error_generic_rk.hpp
X1nAes0gfzegz3Q/tA2M7T3iMPmiFXo5+Bk6dZAPtlPzKjH9J/p12NGn19DTIH83nIFuPidGkmeuAv/0wGYvLocX///+W2xqL9j7MfDDKXrPxOgG7BmPt1DPEx8/CafXcB42sYt53UvvHyyzrhU9YB8Y/C6w8mBiKbX88rnolh7DokJi2XzwQhr9Fyvxipx7O3mwABvsdQ8xjn76nt/J9dSN0xaD3+j33v4FOeEQPv4Q8c6JzZOTtoDx0rfQm5xOXHOgp8b09530Atuz/rnkdbC3M4scpvTXviEHEuenRtDf+R4dFuJje/C1OLAv+waJl9FzikevrF1yEnlhA2dBBqhnyx9vRE9lCXH+GXDpHcx7Kf4Ez5z99GF3gBOJh3b0snQPfQR6uUXnYg9g19Q2xDwL+eAr+j+MSdHNemJ3JPIt11MXTFTeL8Ic0NdP7O/OrCLngdv+foK1oedUF3olZxFaFpPn0M2yUcRqbGk/MeYN8OVPn9JvWQQmGAYWID7t7s7njYiVc8LBdWCyAuwFnHU3WP4C1mf+O2DSCcQAxlq5ADo549JDxDLi5wkwafhx8Ce9LW6xtG0B3Yo/wWsU912Qgv4KWBs3e6OMZ8xB9s8vpUd5H3YVR2/kUnRBf6P+cuwyjf3iLTy7S4zMB18XVHI2NZJe9VFwNHZ7lH5MGDXa/S7whoKxyCEP0ttZOws7eIFcNhMcyTMtMfSYMu/B/zYxX/xtzQpwLlj0m3s5j5NMvltKvIpW+uTEEPz7EPhj8VZyKv3T26hTs4vAj/SqD/wCJmIt7i8Ga32Jb72KbxIjvo0kXt/FHMC1v7+l5qT3NlCXUSe/243Y+ANrSxxsRax6bj1+dAmYYxdxgRp8zXOsDbHivmbg5ChwciLxFry7cyv6orZ/IIkc46KHSHx5ht5mSi98ZyXPaVIv9QHbfPor2H4YNnUKm25F3kX2Buz6qvpgcvJx6Sri9N1gpUXs/SLLylxfmIcPsUaDqdkr0EvD9uQ1C/NmXsuJ8wux9Y8PsK7HiW9gkOb09NuRJyL/hi02Br/EQHuZ/AX2e/oh6p0/6DlRh+9Gl+mHOYfcCwwwBcxJLJmTxhxzyaXTGN9xasRj9IMcrMsYbHo1WG4SvruW9YwD0zLOhw8RyzoTW4lHv7WjZ0Icekzx9c+Zz7vkrsfoMaWQ68jnX1LfFL9OfFrDetYByxCb9l2HLUxnPxDM0OZtfP0OrpvEmm3nnJGFvsECdN0PG6POf4NYeGAA4xxITAV79WdPYhV92qPPsCdMDf7NCOLTL5zngb+HHPysEzwIhrQT075qSq6+gHH1ZF7UUuXtyHuHqCXQaSQ+lTKNOvYTnhU9iH92ABuPxQaxxUl1WZ9biBnPEA/Ib0ecxG9iZw/i02sP0ONYSC4hvt02k5q0nDy8mZppLHZ5GfK6giNeRSa07F5gTfrMD6P7AznMGZ7ucPIbsWEyub3qd+InOScMnX5L3v4O3LT2PnwfbFRGDDveCKzDGdb7w8jNc8Gd9NXfTwZLYd9RX9E3wT5uhWce+GU0NU3qLGLWPmWfm9wGDl1k47wztWzyUvCM8nsxiCmvfkztmk+PANwyjLrjInBXxnLW/if0eCO5+2PwRh51Wz32jHbRWzpJjfQpPa4f6TlNBF9eS96eBabYSQ+GufX9gx7htcS6xAjyI37A/FLLiPnQj+NXudfQ046lJxnB3vBrxAzixwmw+v632F+cAw/yiKclPdVoYsVuYg/r2qgPveE92B1nevejq4JY+iB10C8x6VliWhq1p5f7+/2VHtQa9AC/12+k9rMTm8KoMT+kxuLn3e+AW8mtvfHdzm4LdkWcGkFO+JXc42CM1Cc=
*/