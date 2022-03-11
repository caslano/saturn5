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