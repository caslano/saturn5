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
wc8R9Wenp6et1jfaJHmZKmqz2H7WvrWCWpLz6mH5hdu7gfMxNr9qtbTxYlAnyeKCToBVt/UXLOV1idWsNAYOn2HtHE8v6ETY9U5YRS9p+mEyqR/SCdPv1mJiU0bJYZl/jqLL3xph8myDh2eVSoRfgX1nLfxe53YZ55E22nd4d/R2cvl6OImGk0lXNgSay/Mjm8IzILwPj9ikozWnPEqgrPbEiMv3i+j30ez15XzUo2cs+qGd+OgRR0kkDjiDmaecQ04V1zX4md2qVclsZ06DQ55DsAVzhQoov0yi5ClKlxOs4f5KVEX364aSaD6awdh5j9qnfflrd+nlIbLdlvRhmAW4lbBf+g7kCfcOdqLQQ3e5kU1cQXe2CPmOxKS4VXXaJo3FLU6lpaoqSY586Og+SkLwoys5WLpeffaBWlS1Q46LpBQhB0wITUjqoPVgxZ8lZw2yA+wAeU2qOUnQUnriW9xsqRhEEaeRKiI23NS5zC9JP6ytm63oqrtQfGiF5gokxIhgbF1g4DSeI6q2QP/2+b6WJ/bXIFIj9OUdaXtCz4VdOSrCXzVS41VVpFA/HoJJAKiwQglc6XVZhN7JBeZ+wCD2DsikENVVrTlzqHr0aOXrVuGHSX+ULlSRoPRIxIPtCPHkwomuznMABGGB
*/