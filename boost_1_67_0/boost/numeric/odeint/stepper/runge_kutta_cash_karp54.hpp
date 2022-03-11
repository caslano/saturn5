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