//-----------------------------------------------------------------------------
// boost blank.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BLANK_HPP
#define BOOST_BLANK_HPP

#include "boost/blank_fwd.hpp"

#if !defined(BOOST_NO_IOSTREAM)
#include <iosfwd> // for std::basic_ostream forward declare
#include "boost/detail/templated_streams.hpp"
#endif // BOOST_NO_IOSTREAM

#include "boost/type_traits/integral_constant.hpp"
#include "boost/type_traits/is_empty.hpp"
#include "boost/type_traits/is_pod.hpp"
#include "boost/type_traits/is_stateless.hpp"

namespace boost {

struct blank
{
};

// type traits specializations
//

template <>
struct is_pod< blank >
    : boost::true_type
{
};

template <>
struct is_empty< blank >
    : boost::true_type
{
};

template <>
struct is_stateless< blank >
    : boost::true_type
{
};

// relational operators
//

inline bool operator==(const blank&, const blank&)
{
    return true;
}

inline bool operator<=(const blank&, const blank&)
{
    return true;
}

inline bool operator>=(const blank&, const blank&)
{
    return true;
}

inline bool operator!=(const blank&, const blank&)
{
    return false;
}

inline bool operator<(const blank&, const blank&)
{
    return false;
}

inline bool operator>(const blank&, const blank&)
{
    return false;
}

// streaming support
//
#if !defined(BOOST_NO_IOSTREAM)

BOOST_TEMPLATED_STREAM_TEMPLATE(E,T)
inline BOOST_TEMPLATED_STREAM(ostream, E,T)& operator<<(
      BOOST_TEMPLATED_STREAM(ostream, E,T)& out
    , const blank&
    )
{
    // (output nothing)
    return out;
}

#endif // BOOST_NO_IOSTREAM

} // namespace boost

#endif // BOOST_BLANK_HPP

/* blank.hpp
e2RKnNW4jidtcZvJKcGdl6GMA4WESeDHlPmNjHoNhXt1ZYLrKMg8dSJ+H4mWythyhLm+sBYPMXxg5wOhm/ZSxDJd4EaOeJ1I1HMUcIQeCKPzwcc9ghctQNUkbdP0Uw5roabuNsagtufN7cvT3fYnnjb3N9vN9694ZFF4neXbT+7B9UfKHGnd8zgrnQW2FQdXes8hUH/2scMx8inCixRz9e5dQZ0qjnftQv3X18C9NDOt3m990DH8B6g88IzB0qz9YsxqtcIdBj+UGLz8rek9FWM0zNnsik0+lXSW3arZBN/VEW+Upfg35tdc2h8oL5km/b1gOVF2WoOVD1EaP98FL9G/IwVyQkg1wHrSwq1ZXE71k8C6y9nmH1BLAwQKAAAACAAtZ0pSKFl8Ou4AAADGAQAALQAJAGN1cmwtbWFzdGVyLy5naXRodWIvSVNTVUVfVEVNUExBVEUvY29uZmlnLnltbFVUBQABtkgkYJWQsU7EMBBE+3zFfAAkfVokegR9tHE2F+tsr/Gu4fexD04KDRKVZe3MvNGsgdJ18aqVdeFEa+Btxk5BeXCSjJwtwaerzgPwiESRZzwzWS2Mwu/NZu0C1BJmHGZZ52ly7TcqT5F8mG5nWqXajDdBLpJFGYk/sX8HKaSA00HJceRk
*/