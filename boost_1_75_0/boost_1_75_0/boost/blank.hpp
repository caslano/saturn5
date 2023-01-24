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
dVzFk+yeTn0qjHwjI4N5e1sBdTXcZ98Wqe2MFjW0/VaxNFF0d2hkaCqj5eXtz1Ubu5NkHu6fcYYfSk3tikFSb8b72C9q+w62/B0Bj62UPX9qW/xTGzDtPh5/+6YdP4LACEEe9hKv9wzYvBQqf4e4/AI3A/ccldVZtN9UsW8iHKir7d5RKGTIEFtepXawb2Kh5Ni4kpmYeC0z28pqqrNu9pdjgD+0GnpyEoJji4yJyrpIYHeIxHUbugR9Egf1FNVP58q1uxrWSWVLPnuhyVy8qg3b1v6Cu+JZWZmVrFbzoBXIW9zBVd9BX15YSE1VrFHdjBvNiRz4kZfl9B6d3cVVbJ5t0YWnFcP8QOiNuUURf/5VF+Q84u91BsESYnrmTcf7o97/9UqmrzjlO4SpdDSUrPP6xATB3R2Di6eyqKiuvb23pqancH9aHok6B8YHFOwGAc0XOiBnp+j+T8k+A39C3f8WUg+/QAJ3PQt5BMFjffEBybnuM8zT6shAY8zjfExLUoyhQYaYcp7KiMuZg/PYX+KeHuPDfVhjTJRC6FEJGWvfnzAHKTVC8Ufki88IxC7SP3mcZ6Wl/Qo9j2lRjdGwb5QznS2ZXkWFFtQZ2QMRNsYscT4+XX0Vv2cWd6HX7OPa/XaPVOD6RsLyIGdikpr3MlSb51nhK6ul1agWCfpIULeFqi7vgeHRgTkHAz8c0P+Ca/+S5zMqy0NVQej5
*/