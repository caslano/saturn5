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