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
1zEm1xWDWNTumdWSmKHb8iEGGpGXv81EC09wG7aNUBXZD2d7WvoyxeIZAAg1biJDaJx+6X5+WKh/bbAKbS22kjrdmrgp4iafn5OrINSMYdvwsU6y6IlPr0Slv8JYTd2CxhgMbX+e3Elr4EzOUSaxcYfwyISJv8vfcBszmhjR3pLzqDfrkRftwmIhjVYVk/rnBEI6YEe4abFvuMzyDX48MWUVXPwkMEHlQ1BaYFjj3BnVzWHc7zXBbxOy+NBz8Obnt3Wmil8TekQvdZkvHCF31Z1JZW/ceUAyn2H1Jt/020E3CIKMjqkk6Ei5zXfGKfYR+7EJf4mtmX5FcXkWgtblTwOF1KARzkFiMy3ng1dwLZ3va7dRx/XKipdjTWCHsclTRwhI1nkL61cKntEoVy0+bs6hPVDItbm3V+/1PB8nBzhKzOz+IMf/A8PgZ48ZOTR2iJjljY2OQdX1gxyMyXi9kWwVoy4Y/J6o0dWcx5T1RU6Asu6F0LmU3jlHwFx6BjnGHVcvpeKCcQ+SQZ3EZuh5f/q66GFA8QzDnxKaZdguqrv5KnL1V7vP2x2/liF8kU0AFFt+mMDfl0H/O1yI+AWazl07NUnYg38c+FymYcxgUD1SjHqLUbdd3JM3urLhPhQrUDgo8H0OO+1MzyFLzOk1629puMA2y3S3GO0JJMf0gln3lzXTOPZBrRKiFAn0DpnLSwnd4TOxBB0x+mHa
*/