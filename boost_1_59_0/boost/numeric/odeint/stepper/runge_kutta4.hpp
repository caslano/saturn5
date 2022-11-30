/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta4.hpp

 [begin_description]
 Implementation of the classical Runge-Kutta stepper with the generic stepper.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_HPP_INCLUDED




#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>

#include <boost/numeric/odeint/stepper/explicit_generic_rk.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/array.hpp>

#include <boost/numeric/odeint/util/resizer.hpp>



namespace boost {
namespace numeric {
namespace odeint {

#ifndef DOXYGEN_SKIP
template< class Value = double >
struct rk4_coefficients_a1 : boost::array< Value , 1 >
{
    rk4_coefficients_a1( void )
    {
        (*this)[0] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
    }
};

template< class Value = double >
struct rk4_coefficients_a2 : boost::array< Value , 2 >
{
    rk4_coefficients_a2( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
    }
};


template< class Value = double >
struct rk4_coefficients_a3 : boost::array< Value , 3 >
{
    rk4_coefficients_a3( void )
            {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast<Value>(0);
        (*this)[2] = static_cast<Value>(1);
            }
};

template< class Value = double >
struct rk4_coefficients_b : boost::array< Value , 4 >
{
    rk4_coefficients_b( void )
    {
        (*this)[0] = static_cast<Value>(1)/static_cast<Value>(6);
        (*this)[1] = static_cast<Value>(1)/static_cast<Value>(3);
        (*this)[2] = static_cast<Value>(1)/static_cast<Value>(3);
        (*this)[3] = static_cast<Value>(1)/static_cast<Value>(6);
    }
};

template< class Value = double >
struct rk4_coefficients_c : boost::array< Value , 4 >
{
    rk4_coefficients_c( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[2] = static_cast< Value >( 1 ) / static_cast< Value >( 2 );
        (*this)[3] = static_cast<Value>(1);
    }
};
#endif



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
class runge_kutta4 : public explicit_generic_rk< 4 , 4 , State , Value , Deriv , Time ,
Algebra , Operations , Resizer >
#else
class runge_kutta4 : public explicit_generic_rk
#endif
{

public:

#ifndef DOXYGEN_SKIP
    typedef explicit_generic_rk< 4 , 4 , State , Value , Deriv , Time ,
            Algebra , Operations , Resizer > stepper_base_type;
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

    runge_kutta4( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
            boost::fusion::make_vector( rk4_coefficients_a1<Value>() , rk4_coefficients_a2<Value>() , rk4_coefficients_a3<Value>() ) ,
            rk4_coefficients_b<Value>() , rk4_coefficients_c<Value>() , algebra )
    { }

};

/**
 * \class runge_kutta4
 * \brief The classical Runge-Kutta stepper of fourth order.
 *
 * The Runge-Kutta method of fourth order is one standard method for
 * solving ordinary differential equations and is widely used, see also
 * <a href="http://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods">en.wikipedia.org/wiki/Runge-Kutta_methods</a>
 * The method is  explicit and fulfills the Stepper concept. Step size control
 * or continuous output are not provided.
 * 
 * This class derives from explicit_stepper_base and inherits its interface via CRTP (current recurring template pattern).
 * Furthermore, it derivs from explicit_generic_rk which is a generic Runge-Kutta algorithm. For more details see
 * explicit_stepper_base and explicit_generic_rk.
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
 * \fn runge_kutta4::runge_kutta4( const algebra_type &algebra = algebra_type() )
 * \brief Constructs the runge_kutta4 class. This constructor can be used as a default
 * constructor if the algebra has a default constructor.
 * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
 */

}
}
}


#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA4_HPP_INCLUDED

/* runge_kutta4.hpp
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
*/