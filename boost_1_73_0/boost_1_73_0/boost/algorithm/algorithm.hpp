/* 
   Copyright (c) Marshall Clow 2014.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

 Revision history:
    2 Dec 2014 mtc First version; power
   
*/

/// \file algorithm.hpp
/// \brief Misc Algorithms
/// \author Marshall Clow
///

#ifndef BOOST_ALGORITHM_HPP
#define BOOST_ALGORITHM_HPP

#include <functional> // for plus and multiplies

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp> // for boost::disable_if
#include <boost/type_traits/is_integral.hpp>

namespace boost { namespace algorithm {

template <typename T>
BOOST_CXX14_CONSTEXPR T identity_operation ( std::multiplies<T> ) { return T(1); }

template <typename T>
BOOST_CXX14_CONSTEXPR T identity_operation ( std::plus<T> ) { return T(0); }


/// \fn power ( T x, Integer n )
/// \return the value "x" raised to the power "n"
/// 
/// \param x     The value to be exponentiated
/// \param n     The exponent (must be >= 0)
///
//  \remark Taken from Knuth, The Art of Computer Programming, Volume 2:
//  Seminumerical Algorithms, Section 4.6.3
template <typename T, typename Integer>
BOOST_CXX14_CONSTEXPR typename boost::enable_if<boost::is_integral<Integer>, T>::type
power (T x, Integer n) {
    T y = 1; // Should be "T y{1};" 
    if (n == 0) return y;
    while (true) {
        if (n % 2 == 1) {
            y = x * y;
            if (n == 1)
                return y;
            }
        n = n / 2;
        x = x * x;
        }
    return y;
    }

/// \fn power ( T x, Integer n, Operation op )
/// \return the value "x" raised to the power "n"
/// using the operation "op".
/// 
/// \param x     The value to be exponentiated
/// \param n     The exponent (must be >= 0)
/// \param op    The operation used
///
//  \remark Taken from Knuth, The Art of Computer Programming, Volume 2:
//  Seminumerical Algorithms, Section 4.6.3
template <typename T, typename Integer, typename Operation>
BOOST_CXX14_CONSTEXPR typename boost::enable_if<boost::is_integral<Integer>, T>::type
power (T x, Integer n, Operation op) {
    T y = identity_operation(op);
    if (n == 0) return y;
    while (true) {
        if (n % 2 == 1) {
            y = op(x, y);
            if (n == 1)
                return y;
            }
        n = n / 2;
        x = op(x, x);
        }
    return y;
    }

}}

#endif // BOOST_ALGORITHM_HPP

/* algorithm.hpp
Gl8ux3Or99GoOg5MSvYoW2QXN+YwrJxi4f66iKdm/bkPBXIDQhuvluPQGomLq9AaHIzbY+YKl8t5bAvORRxP85KTXqaLXNUw4R1DdRNEFpdh+j/8biFOSVifJjFuNkpZqZ1/sJLMz/ItTGG4SGrntUfRJXz1KHDj8P3Qp6D//tta9vCCNle/qz2CnSO6zJfqnLTzhWh0CssM29328ShXSs51LIdPQ00ogOSEQ0ue9TqwFPpv97RCctYWV9Q//r7tqEhIgbNcrz0CZXjkd3pGOX1Kryn3TUHBb0o4PevluFzpNdGjUPaegWMDVJJ9kLnlapyuQI736WkA9ULz+Brm9ximL/RUNOad5RgfgxqO9L3jh+ag02x1QKFuHg/6Q8yF4uAPO39v+yNtO8Lh1gsCODyDocTPPzS7nPJDe9B5/d4fnPXwMym1teY7qPTktNNty4JAuf96F4Nf+eleYfo0nl8Vp0bzkqLJdbwsSUYZLas5vrzE5Fp8pKxcNSMMdbIcI6ySY6aZjYtIkmmG6OLLX9lo4/dDGPI0nOGQAxjOjAZxLdtMcUioRzz8D5ktzu0IrP3eG/wfmnCkYcsKxIq7tJIPYYZK6OtjRfuxh8iRBOzgw96HGq198yv8n7Di7+lHOuRIhIa7HZkrM9+5
*/