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
Imi74xq802nHKjHZ+so0Kt9ONdTkqKjnQYZu1vuiTKYHwRcd8QL5tTWsFgolP3zVEcOrQKOYnAcpFOs7WJnR5/E3KS98KfePuydT47xBbkeWn0yyLDSIoi0Pamg7drfTovO6sLn8D/xhPrCr7o9XzhdvPWrkupyVcnWdmmduhQbfZuiM+vt4vLg5vmytxxvwqrX+WpK2e7r73/R4lWzN/45P87/v6V72ET7j3tSKz33anE992hVNPu36jwC216dd4tQuiWlzvtEq9gIwRSvroY2H4nRZuk8bnxL2v6j5t4T9z2v+N8P+l0ngZMmbnMui1Sm+Al3zv6w4l0erUwt2jYi4+karM30F9b7w+BqEjgSSl6N13RCj+Z9XnK8g/mUkK2jGxz5I4yuoUyKuIUjUH5kQSJTBtyH2BAKsj7iOAVx/KsiLyJKwN+NVcdYCsKABcOlcjmq8uRnjrpKIK5kBG/B2PIHV4cULMMkk7N+C0ltYw/53nP7nOUE1Y66WEiPN6Yy6mUqN/28iRgq9C/WqQehsTqXjra8UO+IqoiRcrmO5TfBSAKiC5ohrMJc44uoOEGmjlBEISTOU4I3g6hGVxmVGw6qh62sdnoWLIDHzhS9x+gu2+ML+94Oaf224rIcaKesRHu9RIuO8vnBZeviSWCBSfFZ4zjfhir2+MPo6jL4Oo6/D138ULIrOTEWCN9Wi6IwLgpHxb7Kb5rK8+iAiy/LqkNTr0za38FdXvIs90yXy4whw02L4rNtP7unUevq8DaF6hEZjfmh0VLwWgKPSomVzelsoM+apefWeE+YRvhGaK9UBHAEXu6vbJV4wAakP/JbWBWV9SK2335m0JniQWUJAu7gwoM0oDmi3QjbzvvgMUiYdbkfy/yG/4vHjaKg3VJGps35JH3OoB281hzoc01bThKuq0W0ptEYMk+EWGHoxazZ5fd5qjzforce4XkKhbRjPT1HMLjBuYgrViKgnRjtRzs3ZQ/gzORPlpi7LXWQWP/+c46Unvrvpie8JeMbpA/KmSMlZamT8EnhGnNlfjfjfUotqpuea3zVYode4+vsiS7AYxlTtnf5x04grW9AXvuFvuuHyMIgQxT2FvyO9SJxtfXiKzPIYx0qPlyqHenWH0B+iuKmIQL1gvYHYevJuONtHdko+zBHlPpobUPF5GK53gNVVanMWaBXz0AyLtLIHtfGLwR7vBa9bhDbJAbLLaVozTxMKsWC8jq/NIT188NVW8nZwKuF/AGnDAOvIVejpCHbz4ZQil5lDnQbszAMRY2eCwrwKiQkCQqCqhZ+UmGxwhMEHpaA5FifEu7BC4TlpBNwAnihsCjHHA1CY2ZHMVUYIwzRzCqPWqIoNNWKmOvGFmFED51UjxbfzQ9SA/ky2c0RUuD2WqAhPpDJIHbhYA2w80WcxRWq3skUoYqo0C1K4TaaYKEyROiQE72VgizeDLYbRSbKlKQyXPRhGl4bRpWF0d/iSyvCcBeGKeb4wEUWYiCJMREHLuSsXEa0lEcUFXZMNrhZEmGKf4thpVizIrzpbhR+72atsrnzn7CW2BfuIoEbjUFtFpBl614HVJRz5Eo3CYzcOZNR1uurEkhGQWHQmj/B0d6US0eIlmOolqsWbLzWbw/lq0fk5Ez23PwwdWRhgWW6Z3fw0xqQmY5TW1tn8lDFsctQl+nt7mKPuIo76dj5LzYirXPw/yjoPy483MGyiIzufLScKBw6zmepuduRYpn1Gi/HJdLIU/TApqL0XBDFNLdN02pMWBbU1cf7meY4nu7DT85yyL7rNnUov+6PbvPwSi27LSmUOGaCpc32Q1nyB0D7HTb0D2s6yyKyYGt0OJr+hTHtFzePrB7c=
*/