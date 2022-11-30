/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta_fehlberg87.hpp

 [begin_description]
 Implementation of the Runge-Kutta-Fehlberg stepper with the generic stepper.
 [end_description]

 Copyright 2011-2013 Mario Mulansky
 Copyright 2012-2013 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_FEHLBERG87_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_FEHLBERG87_HPP_INCLUDED


#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>

#include <boost/numeric/odeint/stepper/explicit_error_generic_rk.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/array.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>




namespace boost {
namespace numeric {
namespace odeint {


#ifndef DOXYGEN_SKIP
template< class Value = double >
struct rk78_coefficients_a1 : boost::array< Value , 1 >
{
    rk78_coefficients_a1( void )
            {
        (*this)[0] = static_cast< Value >( 2 )/static_cast< Value >( 27 );
            }
};

template< class Value = double >
struct rk78_coefficients_a2 : boost::array< Value , 2 >
{
    rk78_coefficients_a2( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 36 );
        (*this)[1] = static_cast< Value >( 1 )/static_cast< Value >( 12 );
            }
};


template< class Value = double >
struct rk78_coefficients_a3 : boost::array< Value , 3 >
{
    rk78_coefficients_a3( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 24 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 1 )/static_cast< Value >( 8 );
            }
};

template< class Value = double >
struct rk78_coefficients_a4 : boost::array< Value , 4 >
{
    rk78_coefficients_a4( void )
            {
        (*this)[0] = static_cast< Value >( 5 )/static_cast< Value >( 12 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( -25 )/static_cast< Value >( 16 );
        (*this)[3] = static_cast< Value >( 25 )/static_cast< Value >( 16 );
            }
};

template< class Value = double >
struct rk78_coefficients_a5 : boost::array< Value , 5 >
{
    rk78_coefficients_a5( void )
            {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 20 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 1 )/static_cast< Value >( 4 );
        (*this)[4] = static_cast< Value >( 1 )/static_cast< Value >( 5 );
            }
};


template< class Value = double >
struct rk78_coefficients_a6 : boost::array< Value , 6 >
{
    rk78_coefficients_a6( void )
            {
        (*this)[0] = static_cast< Value >( -25 )/static_cast< Value >( 108 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 125 )/static_cast< Value >( 108 );
        (*this)[4] = static_cast< Value >( -65 )/static_cast< Value >( 27 );
        (*this)[5] = static_cast< Value >( 125 )/static_cast< Value >( 54 );
            }
};

template< class Value = double >
struct rk78_coefficients_a7 : boost::array< Value , 7 >
{
    rk78_coefficients_a7( void )
            {
        (*this)[0] = static_cast< Value >( 31 )/static_cast< Value >( 300 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 61 )/static_cast< Value >( 225 );
        (*this)[5] = static_cast< Value >( -2 )/static_cast< Value >( 9 );
        (*this)[6] = static_cast< Value >( 13 )/static_cast< Value >( 900 );
            }
};

template< class Value = double >
struct rk78_coefficients_a8 : boost::array< Value , 8 >
{
    rk78_coefficients_a8( void )
            {
        (*this)[0] = static_cast< Value >( 2 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -53 )/static_cast< Value >( 6 );
        (*this)[4] = static_cast< Value >( 704 )/static_cast< Value >( 45 );
        (*this)[5] = static_cast< Value >( -107 )/static_cast< Value >( 9 );
        (*this)[6] = static_cast< Value >( 67 )/static_cast< Value >( 90 );
        (*this)[7] = static_cast< Value >( 3 );
            }
};

template< class Value = double >
struct rk78_coefficients_a9 : boost::array< Value , 9 >
{
    rk78_coefficients_a9( void )
            {
        (*this)[0] = static_cast< Value >( -91 )/static_cast< Value >( 108 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 23 )/static_cast< Value >( 108 );
        (*this)[4] = static_cast< Value >( -976 )/static_cast< Value >( 135 );
        (*this)[5] = static_cast< Value >( 311 )/static_cast< Value >( 54 );
        (*this)[6] = static_cast< Value >( -19 )/static_cast< Value >( 60 );
        (*this)[7] = static_cast< Value >( 17 )/static_cast< Value >( 6 );
        (*this)[8] = static_cast< Value >( -1 )/static_cast< Value >( 12 );
            }
};

template< class Value = double >
struct rk78_coefficients_a10 : boost::array< Value , 10 >
{
    rk78_coefficients_a10( void )
            {
        (*this)[0] = static_cast< Value >( 2383 )/static_cast< Value >( 4100 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -341 )/static_cast< Value >( 164 );
        (*this)[4] = static_cast< Value >( 4496 )/static_cast< Value >( 1025 );
        (*this)[5] = static_cast< Value >( -301 )/static_cast< Value >( 82 );
        (*this)[6] = static_cast< Value >( 2133 )/static_cast< Value >( 4100 );
        (*this)[7] = static_cast< Value >( 45 )/static_cast< Value >( 82 );
        (*this)[8] = static_cast< Value >( 45 )/static_cast< Value >( 164 );
        (*this)[9] = static_cast< Value >( 18 )/static_cast< Value >( 41 );
            }
};

template< class Value = double >
struct rk78_coefficients_a11 : boost::array< Value , 11 >
{
    rk78_coefficients_a11( void )
            {
        (*this)[0] = static_cast< Value >( 3 )/static_cast< Value >( 205 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( -6 )/static_cast< Value >( 41 );
        (*this)[6] = static_cast< Value >( -3 )/static_cast< Value >( 205 );
        (*this)[7] = static_cast< Value >( -3 )/static_cast< Value >( 41 );
        (*this)[8] = static_cast< Value >( 3 )/static_cast< Value >( 41 );
        (*this)[9] = static_cast< Value >( 6 )/static_cast< Value >( 41 );
        (*this)[10] = static_cast< Value >( 0 );
            }
};

template< class Value = double >
struct rk78_coefficients_a12 : boost::array< Value , 12 >
{
    rk78_coefficients_a12( void )
            {
        (*this)[0] = static_cast< Value >( -1777 )/static_cast< Value >( 4100 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( -341 )/static_cast< Value >( 164 );
        (*this)[4] = static_cast< Value >( 4496 )/static_cast< Value >( 1025 );
        (*this)[5] = static_cast< Value >( -289 )/static_cast< Value >( 82 );
        (*this)[6] = static_cast< Value >( 2193 )/static_cast< Value >( 4100 );
        (*this)[7] = static_cast< Value >( 51 )/static_cast< Value >( 82 );
        (*this)[8] = static_cast< Value >( 33 )/static_cast< Value >( 164 );
        (*this)[9] = static_cast< Value >( 12 )/static_cast< Value >( 41 );
        (*this)[10] = static_cast< Value >( 0 );
        (*this)[11] = static_cast< Value >( 1 );
            }
};

template< class Value = double >
struct rk78_coefficients_b : boost::array< Value , 13 >
{
    rk78_coefficients_b( void )
            {
        (*this)[0] = static_cast< Value >( 0 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( 34 )/static_cast<Value>( 105 );
        (*this)[6] = static_cast< Value >( 9 )/static_cast<Value>( 35 );
        (*this)[7] = static_cast< Value >( 9 )/static_cast<Value>( 35 );
        (*this)[8] = static_cast< Value >( 9 )/static_cast<Value>( 280 );
        (*this)[9] = static_cast< Value >( 9 )/static_cast<Value>( 280 );
        (*this)[10] = static_cast< Value >( 0 );
        (*this)[11] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[12] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
            }
};

template< class Value = double >
struct rk78_coefficients_db : boost::array< Value , 13 >
{
    rk78_coefficients_db( void )
            {
        (*this)[0] = static_cast< Value >( 0 ) - static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[1] = static_cast< Value >( 0 );
        (*this)[2] = static_cast< Value >( 0 );
        (*this)[3] = static_cast< Value >( 0 );
        (*this)[4] = static_cast< Value >( 0 );
        (*this)[5] = static_cast< Value >( 0 );
        (*this)[6] = static_cast< Value >( 0 );
        (*this)[7] = static_cast< Value >( 0 );
        (*this)[8] = static_cast< Value >( 0 );
        (*this)[9] = static_cast< Value >( 0 );
        (*this)[10] = static_cast< Value >( 0 ) - static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[11] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
        (*this)[12] = static_cast< Value >( 41 )/static_cast<Value>( 840 );
            }
};


template< class Value = double >
struct rk78_coefficients_c : boost::array< Value , 13 >
{
    rk78_coefficients_c( void )
            {
        (*this)[0] = static_cast< Value >( 0 );
        (*this)[1] = static_cast< Value >( 2 )/static_cast< Value >( 27 );
        (*this)[2] = static_cast< Value >( 1 )/static_cast< Value >( 9 );
        (*this)[3] = static_cast< Value >( 1 )/static_cast<Value>( 6 );
        (*this)[4] = static_cast< Value >( 5 )/static_cast<Value>( 12 );
        (*this)[5] = static_cast< Value >( 1 )/static_cast<Value>( 2 );
        (*this)[6] = static_cast< Value >( 5 )/static_cast<Value>( 6 );
        (*this)[7] = static_cast< Value >( 1 )/static_cast<Value>( 6 );
        (*this)[8] = static_cast< Value >( 2 )/static_cast<Value>( 3 );
        (*this)[9] = static_cast< Value >( 1 )/static_cast<Value>( 3 );
        (*this)[10] = static_cast< Value >( 1 );
        (*this)[11] = static_cast< Value >( 0 );
        (*this)[12] = static_cast< Value >( 1 );
            }
};
#endif // DOXYGEN_SKIP





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
class runge_kutta_fehlberg78 : public explicit_error_generic_rk< 13 , 8 , 8 , 7 , State , Value , Deriv , Time ,
Algebra , Operations , Resizer >
#else
class runge_kutta_fehlberg78 : public explicit_error_generic_rk
#endif
{

public:
#ifndef DOXYGEN_SKIP
    typedef explicit_error_generic_rk< 13 , 8 , 8 , 7 , State , Value , Deriv , Time ,
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
    typedef typename stepper_base_type::stepper_type stepper_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    #endif // DOXYGEN_SKIP


    runge_kutta_fehlberg78( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
            boost::fusion::make_vector( rk78_coefficients_a1<Value>() , rk78_coefficients_a2<Value>() , rk78_coefficients_a3<Value>() ,
                    rk78_coefficients_a4<Value>() , rk78_coefficients_a5<Value>() , rk78_coefficients_a6<Value>() ,
                    rk78_coefficients_a7<Value>() , rk78_coefficients_a8<Value>() , rk78_coefficients_a9<Value>() ,
                    rk78_coefficients_a10<Value>() , rk78_coefficients_a11<Value>() , rk78_coefficients_a12<Value>() ) ,
            rk78_coefficients_b<Value>() , rk78_coefficients_db<Value>() , rk78_coefficients_c<Value>() , algebra )
    { }
};



/************* DOXYGEN *************/

/**
 * \class runge_kutta_fehlberg78
 * \brief The Runge-Kutta Fehlberg 78 method.
 *
 * The Runge-Kutta Fehlberg 78 method is a standard method for high-precision applications.
 * The method is explicit and fulfills the Error Stepper concept. Step size control
 * is provided but continuous output is not available for this method.
 * 
 * This class derives from explicit_error_stepper_base and inherits its interface via CRTP (current recurring template pattern).
 * Furthermore, it derivs from explicit_error_generic_rk which is a generic Runge-Kutta algorithm with error estimation.
 * For more details see explicit_error_stepper_base and explicit_error_generic_rk.
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
     * \fn runge_kutta_fehlberg78::runge_kutta_fehlberg78( const algebra_type &algebra )
     * \brief Constructs the runge_kutta_cash_fehlberg78 class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */

}
}
}

#endif //BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_FEHLBERG87_HPP_INCLUDED

/* runge_kutta_fehlberg78.hpp
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
*/