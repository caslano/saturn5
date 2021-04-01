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
DELtnnkhElQCVJbrEEhuHjwIFDB5zgdHZO7YMVjttqQ/SXy1yMGBU8uUif8TJgglLf+AtMgb1cVWeFvw7ji83zHG8iaVX9IU12cs3Ao+zTRZ30i+U5GK56vMbbJ0TlNKXitx3CxHIx1ErUGXJp/92JZWD3NC2lnQVBx8eYeJOLA5mDf7y4PKXSLNa3VwI9NXQzt+we7hxA1EKS8fgeVX79QGRMUc1MGcx3NWa+vu3arZeHkXHqZEbiZWafyKfWbr6VQTmR/s67R6dQBVnaSNbeNdTDcpA0xsgrWPqt50uGq0w7Nq39wXcpfjrfSqtFYZdENzcgiYP3IzKATnyuS4upOL5PRrmVnY32el9H/9bi+aJXg37pRNWL71mIr96sT5quZoUv8K4bQoRs3wfr43b4HLhstLEat1QY4dspbEMIxV+SycjLIi/f/ggPkMJrdEJTJOJRBETxeaOnZGhPvDXXPw4KUyDpz2t8jitKo0w9OjFn0KRpkg+lZb/h2KINTTBib3XvDZOtTkq4rd1Ycs4PX0PIv2BNQIrGxl+Aes3tSMN7G3FiR4FuTUZA==
*/