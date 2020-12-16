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
HV8b0MV6vgcRFtN3oCJMtZFaiPtTNiFNW7BgR9g/7xz8bowuj68WMfVlvqvx8zbi56gkTszXCcTUGYL2Zt0A7Q5B2xYRoN0paCM0190laEn1ArR7BG1LeIA2W9CGavg9KGhTwgK0eYLWO8xofLcHydWbdHnlCWRcnKyeZ/6w+lkfQXtCQ3tK0PI0tKWC1iUsQFvmp6ErzXVPC9pNCs3gPLzSebyrm8dKZIxO5lP47jAmI0ju/0AnY73It7fDd6cxGeRbmYwdOhlvIqP1cJ6d9MtQaW8LWkVYgLZZ0GZortsiaP3CDI8v3y4d327d+LYjYy4yRsD341ri4VL6bLzqWXamzDC2hhcP2sn27faa4mUvkdWeXxiuaeAl4fOlTn8n0N+NKSo2/kzQfoO2ElpnhVbbdXNwoEf5h5Ni+t7JQeM4uJqfcpxNx++wbh7nXMZzvSPUWnxPrWX0U74UCRJdHTExZj+/IM8Kf6cbc1PG/JUY875ay4hRvoKM+biJMfv5BRnzj7oxd2LMU0ZyYga++wWti6A1Vmi1lFtSZPMVqf9K5vGz4f5NNT9KeVu5tNb9Vb8/zbjbpKq2/1Utx13sKMjjjb9RtEklvaw/DOsffsqXvOdEeXrmmEcw5ptS1bxyoJZxRZFRxD/68Ubo+OfCfzn8B1jwWkEbDW0XtEYa2lho7dN4Hlyh1TIm0R2R2Fh93Rj+IsYwPjwgzw0tG3ltkXGolrp1OZy2PJd6BFKv24ZNja6V4BfkzGcjs/w4Uimz10iz/IKcIW1iml++XTa+Zrp1u5k1+nu6ahNHa2mbRaU2u/8fXYxvqeP/EPz7ZKj8v6vlHAT/IM+AtDasE8EvyFnutroxL2TMczPwFQuUajwraE0UWi315KwK9i7BDobn4KzkWUnl/9JeZSdT/Pz6le71XBwCP9l++iUh8CuQ8Otqjl/QZ/67m+QX7Dn8Hmb5OW0l0nNaJvnxmXR8fZoaxbl+flJbiTbJi5P+Ol4xJnk5nHpesTq/vr0HMShL3a/8o7ouh8a+P7+HIUC7y0+Di0Izou9+/rNIsncrmVs/lZ/sDJZubo8y5unZyrPR/AkTcUzQqO+g1V6f/h0fnT7jTK0NvyhHclYgQTf+lf61UffRwsNqryP/CR7cWi9jmCmdw4+nnWU+M9wkP/WJHP34Rpjkx5N90hiRapKfUrDJ+KXr1mgja7QnRz37fk5Y7TB+tYx+QfV6lUm7gqf+nUumecXoeOWa5hWt4zXa1NrwFeQ82Vjd2uxmbZbkqmvT0ID/+GXky+rSPNNjlu/vX2Oan7wWuNY0P3ndlm+en/SZNYdpfvayAgm/At2aj+ypxswoC7jUyJqX2enYyXzRpZORh4y6o9V6u6kRGdYqahCrJO6V6GRci4wBo9W83MyQDOWlB7J5uE35rtPqtetjygTdePN7oikx3haMd5AB/jFWpRpRgpds3OU6WQXIunqM6tctDeRwRZY+pk3U8S+C/x3wb2thPgb56+PcdSb17i7RP991vTn/CZofp+jmPp65F4xVddvGkN0pVbZMxs06GZXImIOMZhZ0bEgGPfW+MhnTmp65B3U9MjYhgw8s7QytoUOC827T8Z8K/9xxqp7aC2w5XdAeELQhtZZpL7LxN7qPteZpOH2su0OnxzuEvN80Y5gJbdY41XYvErR7ob0FrYVCM6Rvu80nra3v0Y1lNjJ+GgcVvh2E3Ieg9bkaO1JoBrARckHbJSUu1Z44U/D/cZaiFixrzhQE4a3uO3WolSZqd5XK8b/xOAdnCgydr/hXneuopTjfv/g4h+VYe84U1POfKSDG4IGz+ZrDV3fxO1BHoY+5/Pzv3e+/X/j+g3xX/Xw=
*/