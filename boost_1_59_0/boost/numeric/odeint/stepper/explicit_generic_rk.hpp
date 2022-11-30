/*
 [auto_generated]
 boost/numeric/odeint/stepper/explicit_generic_rk.hpp

 [begin_description]
 Implementation of the generic Runge-Kutta steppers. This is the base class for many Runge-Kutta steppers.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 Copyright 2012 Christoph Koke

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_GENERIC_RK_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_GENERIC_RK_HPP_INCLUDED


#include <boost/array.hpp>


#include <boost/numeric/odeint/stepper/base/explicit_stepper_base.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>
#include <boost/numeric/odeint/stepper/detail/generic_rk_algorithm.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

namespace boost {
namespace numeric {
namespace odeint {

//forward declarations

#ifndef DOXYGEN_SKIP
template<
size_t StageCount,
size_t Order,
class State ,
class Value = double ,
class Deriv = State ,
class Time = Value ,
class Algebra = typename algebra_dispatcher< State >::algebra_type ,
class Operations = typename operations_dispatcher< State >::operations_type ,
class Resizer = initially_resizer
>
class explicit_generic_rk;


struct stage_vector;

template< class T , class Constant >
struct array_wrapper
{
    typedef const typename boost::array< T , Constant::value > type;
};

template< class T , size_t i >
struct stage
{
    T c;
    boost::array< T , i > a;
};


template< class T , class Constant >
struct stage_wrapper
{
    typedef stage< T , Constant::value > type;
};
#endif


template<
size_t StageCount,
size_t Order,
class State ,
class Value ,
class Deriv ,
class Time ,
class Algebra ,
class Operations ,
class Resizer
>
#ifndef DOXYGEN_SKIP
class explicit_generic_rk : public explicit_stepper_base<
explicit_generic_rk< StageCount , Order , State , Value , Deriv , Time , Algebra , Operations , Resizer > ,
Order , State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else
class explicit_generic_rk : public explicit_stepper_base
#endif
{

public:

    #ifndef DOXYGEN_SKIP
    typedef explicit_stepper_base<
            explicit_generic_rk< StageCount , Order , State , Value , Deriv ,Time , Algebra , Operations , Resizer > ,
            Order , State , Value , Deriv , Time , Algebra ,
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
    typedef explicit_generic_rk< StageCount , Order , State , Value , Deriv ,Time , Algebra , Operations , Resizer > stepper_type;
    #endif 

    typedef detail::generic_rk_algorithm< StageCount , Value , Algebra , Operations > rk_algorithm_type;

    typedef typename rk_algorithm_type::coef_a_type coef_a_type;
    typedef typename rk_algorithm_type::coef_b_type coef_b_type;
    typedef typename rk_algorithm_type::coef_c_type coef_c_type;

    #ifndef DOXYGEN_SKIP
    static const size_t stage_count = StageCount;
    #endif

public:

    explicit_generic_rk( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c ,
            const algebra_type &algebra = algebra_type() )
    : stepper_base_type( algebra ) , m_rk_algorithm( a , b , c )
    { }


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

    resizer_type m_resizer;

    wrapped_state_type m_x_tmp;
    wrapped_deriv_type m_F[StageCount-1];

};



/*********** DOXYGEN *************/

/**
 * \class explicit_generic_rk
 * \brief A generic implementation of explicit Runge-Kutta algorithms. This class is as a base class
 * for all explicit Runge-Kutta steppers.
 *
 * This class implements the explicit Runge-Kutta algorithms without error estimation in a generic way.
 * The Butcher tableau is passed to the stepper which constructs the stepper scheme with the help of a
 * template-metaprogramming algorithm. ToDo : Add example!
 * 
 * This class derives explicit_stepper_base which provides the stepper interface.
 *
 * \tparam StageCount The number of stages of the Runge-Kutta algorithm.
 * \tparam Order The order of the stepper.
 * \tparam State The type representing the state of the ODE.
 * \tparam Value The floating point type which is used in the computations.
 * \tparam Time The type representing the independent variable - the time - of the ODE.
 * \tparam Algebra The algebra type.
 * \tparam Operations The operations type.
 * \tparam Resizer The resizer policy type.
 */

    /**
     * \fn explicit_generic_rk::explicit_generic_rk( const coef_a_type &a , const coef_b_type &b , const coef_c_type &c , const algebra_type &algebra )
     * \brief Constructs the explicit_generic_rk class. See examples section for details on the coefficients.
     * \param a Triangular matrix of parameters b in the Butcher tableau.
     * \param b Last row of the butcher tableau.
     * \param c Parameters to calculate the time points in the Butcher tableau.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */
    
    /**
     * \fn explicit_generic_rk::do_step_impl( System system , const StateIn &in , const DerivIn &dxdt , time_type t , StateOut &out , time_type dt )
     * \brief This method performs one step. The derivative `dxdt` of `in` at the time `t` is passed to the method.
     * The result is updated out of place, hence the input is in `in` and the output in `out`.
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
     * \fn explicit_generic_rk::adjust_size( const StateIn &x )
     * \brief Adjust the size of all temporaries in the stepper manually.
     * \param x A state from which the size of the temporaries to be resized is deduced.
     */

}
}
}
#endif // BOOST_NUMERIC_ODEINT_STEPPER_EXPLICIT_GENERIC_RK_HPP_INCLUDED

/* explicit_generic_rk.hpp
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
*/