/*
 [auto_generated]
 boost/numeric/odeint/stepper/runge_kutta_cash_karp54.hpp
 
 [begin_description]
 Implementation of the Runge Kutta Cash Karp 5(4) method. It uses the generic error stepper.
 [end_description]
 
 Copyright 2011-2013 Mario Mulansky
 Copyright 2011-2013 Karsten Ahnert
 
 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>

#include <boost/numeric/odeint/stepper/explicit_error_generic_rk.hpp>
#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>
#include <boost/numeric/odeint/algebra/operations_dispatcher.hpp>

#include <boost/numeric/odeint/util/state_wrapper.hpp>
#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resizer.hpp>

#include <boost/array.hpp>




namespace boost {
namespace numeric {
namespace odeint {


#ifndef DOXYGEN_SKIP
template< class Value = double >
struct rk54_ck_coefficients_a1 : boost::array< Value , 1 >
{
    rk54_ck_coefficients_a1( void )
    {
        (*this)[0] = static_cast< Value >( 1 )/static_cast< Value >( 5 );
    }
};

template< class Value = double >
struct rk54_ck_coefficients_a2 : boost::array< Value , 2 >
{
    rk54_ck_coefficients_a2( void )
    {
        (*this)[0] = static_cast<Value>( 3 )/static_cast<Value>( 40 );
        (*this)[1] = static_cast<Value>( 9 )/static_cast<Value>( 40 );
    }
};


template< class Value = double >
struct rk54_ck_coefficients_a3 : boost::array< Value , 3 >
{
    rk54_ck_coefficients_a3( void )
    {
        (*this)[0] = static_cast<Value>( 3 )/static_cast<Value>( 10 );
        (*this)[1] = static_cast<Value>( -9 )/static_cast<Value>( 10 );
        (*this)[2] = static_cast<Value>( 6 )/static_cast<Value>( 5 );
    }
};

template< class Value = double >
struct rk54_ck_coefficients_a4 : boost::array< Value , 4 >
{
    rk54_ck_coefficients_a4( void )
    {
        (*this)[0] = static_cast<Value>( -11 )/static_cast<Value>( 54 );
        (*this)[1] = static_cast<Value>( 5 )/static_cast<Value>( 2 );
        (*this)[2] = static_cast<Value>( -70 )/static_cast<Value>( 27 );
        (*this)[3] = static_cast<Value>( 35 )/static_cast<Value>( 27 );
    }
};

template< class Value = double >
struct rk54_ck_coefficients_a5 : boost::array< Value , 5 >
{
    rk54_ck_coefficients_a5( void )
    {
        (*this)[0] = static_cast<Value>( 1631 )/static_cast<Value>( 55296 );
        (*this)[1] = static_cast<Value>( 175 )/static_cast<Value>( 512 );
        (*this)[2] = static_cast<Value>( 575 )/static_cast<Value>( 13824 );
        (*this)[3] = static_cast<Value>( 44275 )/static_cast<Value>( 110592 );
        (*this)[4] = static_cast<Value>( 253 )/static_cast<Value>( 4096 );
    }
};

template< class Value = double >
struct rk54_ck_coefficients_b : boost::array< Value , 6 >
{
    rk54_ck_coefficients_b( void )
    {
        (*this)[0] = static_cast<Value>( 37 )/static_cast<Value>( 378 );
        (*this)[1] = static_cast<Value>( 0 );
        (*this)[2] = static_cast<Value>( 250 )/static_cast<Value>( 621 );
        (*this)[3] = static_cast<Value>( 125 )/static_cast<Value>( 594 );
        (*this)[4] = static_cast<Value>( 0 );
        (*this)[5] = static_cast<Value>( 512 )/static_cast<Value>( 1771 );
    }
};

template< class Value = double >
struct rk54_ck_coefficients_db : boost::array< Value , 6 >
{
    rk54_ck_coefficients_db( void )
    {
        (*this)[0] = static_cast<Value>( 37 )/static_cast<Value>( 378 ) - static_cast<Value>( 2825 )/static_cast<Value>( 27648 );
        (*this)[1] = static_cast<Value>( 0 );
        (*this)[2] = static_cast<Value>( 250 )/static_cast<Value>( 621 ) - static_cast<Value>( 18575 )/static_cast<Value>( 48384 );
        (*this)[3] = static_cast<Value>( 125 )/static_cast<Value>( 594 ) - static_cast<Value>( 13525 )/static_cast<Value>( 55296 );
        (*this)[4] = static_cast<Value>( -277 )/static_cast<Value>( 14336 );
        (*this)[5] = static_cast<Value>( 512 )/static_cast<Value>( 1771 ) - static_cast<Value>( 1 )/static_cast<Value>( 4 );
    }
};


template< class Value = double >
struct rk54_ck_coefficients_c : boost::array< Value , 6 >
{
    rk54_ck_coefficients_c( void )
    {
        (*this)[0] = static_cast<Value>(0);
        (*this)[1] = static_cast<Value>( 1 )/static_cast<Value>( 5 );
        (*this)[2] = static_cast<Value>( 3 )/static_cast<Value>( 10 );
        (*this)[3] = static_cast<Value>( 3 )/static_cast<Value>( 5 );
        (*this)[4] = static_cast<Value>( 1 );
        (*this)[5] = static_cast<Value>( 7 )/static_cast<Value>( 8 );
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
class runge_kutta_cash_karp54 : public explicit_error_generic_rk< 6 , 5 , 5 , 4 ,
        State , Value , Deriv , Time , Algebra , Operations , Resizer >
#else 
class runge_kutta_cash_karp54 : public explicit_error_generic_rk
#endif
{

public:
#ifndef DOXYGEN_SKIP
    typedef explicit_error_generic_rk< 6 , 5 , 5 , 4 , State , Value , Deriv , Time ,
                               Algebra , Operations , Resizer > stepper_base_type;
#endif
    typedef typename stepper_base_type::state_type state_type;
    typedef typename stepper_base_type::value_type value_type;
    typedef typename stepper_base_type::deriv_type deriv_type;
    typedef typename stepper_base_type::time_type time_type;
    typedef typename stepper_base_type::algebra_type algebra_type;
    typedef typename stepper_base_type::operations_type operations_type;
    typedef typename stepper_base_type::resizer_type resizer_typ;

    #ifndef DOXYGEN_SKIP
    typedef typename stepper_base_type::stepper_type stepper_type;
    typedef typename stepper_base_type::wrapped_state_type wrapped_state_type;
    typedef typename stepper_base_type::wrapped_deriv_type wrapped_deriv_type;
    #endif


    runge_kutta_cash_karp54( const algebra_type &algebra = algebra_type() ) : stepper_base_type(
        boost::fusion::make_vector( rk54_ck_coefficients_a1<Value>() ,
                                 rk54_ck_coefficients_a2<Value>() ,
                                 rk54_ck_coefficients_a3<Value>() ,
                                 rk54_ck_coefficients_a4<Value>() ,
                                 rk54_ck_coefficients_a5<Value>() ) ,
            rk54_ck_coefficients_b<Value>() , rk54_ck_coefficients_db<Value>() , rk54_ck_coefficients_c<Value>() ,
            algebra )
    { }
};


/********** DOXYGEN **********/

/**
 * \class runge_kutta_cash_karp54
 * \brief The Runge-Kutta Cash-Karp method.
 *
 * The Runge-Kutta Cash-Karp method is one of the standard methods for
 * solving ordinary differential equations, see
 * <a href="http://en.wikipedia.org/wiki/Cash%E2%80%93Karp_methods">en.wikipedia.org/wiki/Cash-Karp_methods</a>.
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
     * \fn runge_kutta_cash_karp54::runge_kutta_cash_karp54( const algebra_type &algebra )
     * \brief Constructs the runge_kutta_cash_karp54 class. This constructor can be used as a default
     * constructor if the algebra has a default constructor.
     * \param algebra A copy of algebra is made and stored inside explicit_stepper_base.
     */
}
}
}

#endif // BOOST_NUMERIC_ODEINT_STEPPER_RUNGE_KUTTA_CASH_KARP54_HPP_INCLUDED

/* runge_kutta_cash_karp54.hpp
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
*/