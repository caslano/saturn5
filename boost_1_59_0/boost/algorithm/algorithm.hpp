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
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
*/