//  Boost integer/static_min_max.hpp header file  ----------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_STATIC_MIN_MAX_HPP
#define BOOST_INTEGER_STATIC_MIN_MAX_HPP

#include <boost/integer_fwd.hpp>  // self include

namespace boost
{

//  Compile-time extrema class declarations  ---------------------------------//
//  Get the minimum or maximum of two values, signed or unsigned.

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_min
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_max
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 < Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_min
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_max
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 < Value2) ? Value2 : Value1 );
};


}  // namespace boost


#endif  // BOOST_INTEGER_STATIC_MIN_MAX_HPP

/* static_min_max.hpp
KGGq6gESdYBlQ6+E0O0HEorctr1JYrMPaUI3MjGUUBGK/ySUOJxKyG6MbatvIqJTuiwCY19UhLbMBtVG5+tZdFk9RVVez3otraN+lMU3sD3kxDYeFTzPybdvbUYdf7bkBIQzhuEvoRmQFFYjaWJUYTGawSt0dWCTin62MWTqBVp/jM3AEGHXV/AYDm1eSZHDkfsTdWGo7I5WDk4IDPWUQO+mZtdNCs+E3KGh6mMSasKQD2Fa
*/