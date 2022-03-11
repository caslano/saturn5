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