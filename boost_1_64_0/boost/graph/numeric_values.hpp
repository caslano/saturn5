// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NUMERIC_VALUES_HPP
#define BOOST_GRAPH_NUMERIC_VALUES_HPP

#include <limits>

namespace boost
{

#define BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(type)          \
    template <> struct numeric_values< type >               \
    {                                                       \
        typedef type value_type;                            \
        static type zero() { return 0.0; }                  \
        static type infinity()                              \
        {                                                   \
            return std::numeric_limits< type >::infinity(); \
        }                                                   \
    };

/**
 * This generic type reports various numeric values for some type. In the
 * general case, numeric values simply treat their maximum value as infinity
 * and the default-constructed value as 0.
 *
 * Specializations of this template can redefine the notions of zero and
 * infinity for various types. For example, the class is specialized for
 * floating point types to use the built in notion of infinity.
 */
template < typename T > struct numeric_values
{
    typedef T value_type;

    static T zero() { return T(); }

    static T infinity() { return (std::numeric_limits< T >::max)(); }
};

// Specializations for floating point types refer to 0.0 and their infinity
// value defined by numeric_limits.
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(float)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(double)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(long double)

#undef BOOST_GRAPH_SPECIALIZE_NUMERIC_VALUE
}

#endif

/* numeric_values.hpp
qBau/6KEFvfre529PGsABI9iXgvG+YVqSZZDK3M0VxrNEa3j8UplWK9nDDBhcY/myLZGENGHG6R6VZ3+1w1krarQcI8SxEWLwBajWSfOrBUNiHHP21hVQRDndEYWsscEZtRTbZuWYWOVZiwVyMKrQTB6hp2dbkmsMfoahMyQe+LRddoUtooyS7QCGDiChb0oTtZL0Tzn/dUuGkhtMpI8Gxj6P1Dv5qpCffo14+wAgXRyaRkAESR3iLsnbpkKfUGQYTizFQ419XEE31Zyejg/uSxJ4Qxa7B7uLgjF0Ry6XBUD7QFlU6r/nr4I/BcMTjcYHabQAz5kQDG4sSv8ptw/FPYXq6gZ4ZmyAr8XX4+malJA9mZQzON0jjKS+oX/Mtp5QbdDBWVcgKrw9FMj8X1psY96cv4GG3hzl9y8DcUaE2qpXcykM9r90ePxUwiH72JlPA+HLasWtdXOKOSRGtuFN/h0o9L1YFHGL9XHFr0hMTMs2TPLX6LciqP44x2ABIG9f+EI7CUmiBrFj3MijxEXaUzZ8QHawy3XUc4cBWwoqmBVAQQhvuextytSbg==
*/