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
XMcp4Fm/WMMhpWmsUQPxHPDBE/T3qpge47+Z5TAfJoeJvJNH2/GhzMk/nja1hit8UOVXfZ6pwSRpOxZ2CCp0lDNu+HLbark2DK57Zoyu1Z3YiTyX+IEviJPzQTjY8i0FJ466qMePjrkE6AtXJtpZb7IVCtbAqMxGdN0FIFkgYlco/TuEJMt76oxIHK8GXfOXopB01Grtkbm34I7K1JqwKjb9sM+GrllsqufR7/TXligT390zdoUaHAjv916UjJFKnJrnbBTfSYwkazhH48oC5rFTTr1hRu56JCHI6A5vtpG+z4+FAcO4mWoONIe2oYiLRfW0WOWnww8xiwPE8nlp0KfAGSlNNC90zZc287xZprfiKeyGPmvVx7qtKvCWRV1sd/CEW1hc80Lh6QoQFQOUYJu0jQR5CXZSKAdTCPYQVCry6ibzRvqZiNFXj5EFcr+qB92haE0cYt8HyDbt19oFtegXKYwCXGeYuG8PWj7e4eVaDKia/yl7XxR9aMYtFH6w47Tf6v5rRE5v+ERFuMDgiFXcnKtLP6gkcp5L7w3ZQYls8GvcpRYcGLR0awuL/4iZ95KqOQrsjXdIyfmtp8Wo5pqyU7RPDn978VPv99Dg6aUzDECDEOPBOx0yfjU66uBO+YmrP+pZv+krtZ/2hekRJ1i4O5T2uWfkxC62zIv3BaP9+XzHuAIwe3FltD8fzTy/pU5b/RJrNCc4eEjl
*/