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
DPcTOPU5ygYA0amZPtmzov9beRXo4NEEha9dygJVh/NYbJ/rB3jrX5mYxwmtg5/aHRpNb8q95xoPb1n1ss9g0nNRNBfVakqSLECVyc1Otir0OoiTw3gIHQmQZMhsHcHh739ftc6mHQPiQeKq0/R8HA1qc7K55q+BSNXSi3e18K3zXpan2ifx5AjqLrUnoXmNfnx7DyJ5MGgfDZdUGSGq6C6jrXgqf3SK0e38c7OBdIK4NaAzy+qANpn4nyyEfj140KMBGmfa111UvlUc7LvtL2DfChJf7zq7vQLMThieuE/H3k9VEJiYUfbcRZ+vGc/PEV7PORgAf9Gfo8bCHcAPiyK+oh2+1TmEgOGcHgCujS6O7uZ/nAzr3LttkTG8AQ563+AYI9JLwAp/RFxRTfLQXgwoPMUYslN2y82d168xUWBawPkIcWjUuDtOdJP5jOT2vv80RnQgz8tn6bwWY/Lz+l3VitBiejvJmXDJcGDdo21K4RdZsaEuftFUN1kxHoaqI5mRGfrOtTH/8MhNscrK6OSz8KRclqGmt+tvFRyWJj1bG+wARBHnrooC8g==
*/