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