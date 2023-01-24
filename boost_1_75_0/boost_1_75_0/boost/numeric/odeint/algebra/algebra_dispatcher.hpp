/*
 [auto_generated]
 boost/numeric/odeint/algebra/algebra_dispatcher.hpp

 [begin_description]
 Algebra dispatcher to automatically chose suitable algebra.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_ALGEBRA_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_ALGEBRA_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/config.hpp>

#include <complex>
#include <boost/type_traits/is_floating_point.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include <boost/numeric/odeint/algebra/range_algebra.hpp>
#include <boost/numeric/odeint/algebra/array_algebra.hpp>
#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

#include <boost/array.hpp>


namespace boost {
namespace numeric {
namespace odeint {
    
template< class StateType , class Enabler = void >
struct algebra_dispatcher_sfinae
{
    // range_algebra is the standard algebra
    typedef range_algebra algebra_type;
};

template< class StateType >
struct algebra_dispatcher : algebra_dispatcher_sfinae< StateType > { };

// specialize for array
template< class T , size_t N >
struct algebra_dispatcher< boost::array< T , N > >
{
    typedef array_algebra algebra_type;
};

//specialize for some integral types
template< typename T >
struct algebra_dispatcher_sfinae< T , typename boost::enable_if< typename boost::is_floating_point< T >::type >::type >
{
    typedef vector_space_algebra algebra_type;
};

template< typename T >
struct algebra_dispatcher< std::complex<T> >
{
    typedef vector_space_algebra algebra_type;
};

///* think about that again....
// specialize for ublas vector and matrix types
template< class T , class A >
struct algebra_dispatcher< boost::numeric::ublas::vector< T , A > >
{
    typedef vector_space_algebra algebra_type;
};

template< class T , class L , class A >
struct algebra_dispatcher< boost::numeric::ublas::matrix< T , L , A > >
{
    typedef vector_space_algebra algebra_type;
};
//*/

}
}
}

#ifdef BOOST_NUMERIC_ODEINT_CXX11

// c++11 mode: specialization for std::array if available

#include <array>

namespace boost {
namespace numeric {
namespace odeint {
    
// specialize for std::array
template< class T , size_t N >
struct algebra_dispatcher< std::array< T , N > >
{
    typedef array_algebra algebra_type;
};

} } }

#endif


#endif

/* algebra_dispatcher.hpp
tlAPGpjdR9PixiGuEANL+lNyNIaEKi60Ufoa+GeSibwHRDNu5R7gjV8AP7rCIO5sj6PF0aIsHLD+ShOu/WSJSPxGnhmD7Zan1pc1Bp3TpPzBcvAcAH9hD7h2y6cCSdAUcJ1GZYQZLCRPNSY7lMwoJ2RWi61Qi/MrQeP15GylCNjDtGQ2k/jGSKkTd2CNNNxdxwX+L1LTrzQYy8vEnsbx9Z+hzr4C+QxMuIRlz4AyXxhAq0Lmvgt85NMfPTaAZtKHNwv1m0UDaFEU5rQNUxKvpFUhWT5FbQOo4059RUiln/IVUUwfrcnBoZpvBAHk0d1fc+gIK7rA8FxJjlkccOSA974KzIcB6I2z/N70Gq2OC7N46uBsvjiy3eTm5ovjpxwzD2ASESRDlkYjSDqujHb7pTj7A5KiiY1xvxTXrma/IYcvgULUg/RFUMiOcucZrherWRCGMtas2Ufl8CWBmejoHc2emUPDKMOCmGh78nOcmak7KHWxzNDx13srZ3b7coj1kT6GU7UPmZ+0foARvfWKOXZqM9S/wG9sNAAmsv2z3Xwh5amv5lJAUAWPtqA92pMOarqBf3ft1WJZ5ar/vNJgsK9dGbf+8HDl4kHG+nucXhTcCyOKXricK7jZWk1TP42rtoWo4+PwBISrUbOP/xMgX22kZl69hIvBVXwjdwZZWh1sUTxBZFun+tiRTzhjMefDcloG7M4EggUWxrTQ
*/