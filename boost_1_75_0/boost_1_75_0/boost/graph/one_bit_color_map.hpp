// Copyright (C) 2005-2010 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// One bit per color property map (gray and black are the same, green is not
// supported)

#ifndef BOOST_ONE_BIT_COLOR_MAP_HPP
#define BOOST_ONE_BIT_COLOR_MAP_HPP

#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/detail/mpi_include.hpp>
#include <boost/shared_array.hpp>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <algorithm>
#include <limits>

namespace boost
{

enum one_bit_color_type
{
    one_bit_white = 0,
    one_bit_not_white = 1
};

template <> struct color_traits< one_bit_color_type >
{
    static one_bit_color_type white() { return one_bit_white; }
    static one_bit_color_type gray() { return one_bit_not_white; }
    static one_bit_color_type black() { return one_bit_not_white; }
};

template < typename IndexMap = identity_property_map > struct one_bit_color_map
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = std::numeric_limits< unsigned char >::digits);
    std::size_t n;
    IndexMap index;
    shared_array< unsigned char > data;

    typedef typename property_traits< IndexMap >::key_type key_type;
    typedef one_bit_color_type value_type;
    typedef void reference;
    typedef read_write_property_map_tag category;

    explicit one_bit_color_map(
        std::size_t n, const IndexMap& index = IndexMap())
    : n(n)
    , index(index)
    , data(new unsigned char[(n + bits_per_char - 1) / bits_per_char]())
    {
    }
};

template < typename IndexMap >
inline one_bit_color_type get(const one_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key)
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = one_bit_color_map< IndexMap >::bits_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    return one_bit_color_type(
        (pm.data.get()[i / bits_per_char] >> (i % bits_per_char)) & 1);
}

template < typename IndexMap >
inline void put(const one_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key,
    one_bit_color_type value)
{
    BOOST_STATIC_CONSTANT(
        int, bits_per_char = one_bit_color_map< IndexMap >::bits_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    BOOST_ASSERT(value >= 0 && value < 2);
    std::size_t byte_num = i / bits_per_char;
    std::size_t bit_position = (i % bits_per_char);
    pm.data.get()[byte_num]
        = (unsigned char)((pm.data.get()[byte_num] & ~(1 << bit_position))
            | (value << bit_position));
}

template < typename IndexMap >
inline one_bit_color_map< IndexMap > make_one_bit_color_map(
    std::size_t n, const IndexMap& index_map)
{
    return one_bit_color_map< IndexMap >(n, index_map);
}

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / one_bit_color_map.hpp >)

#endif // BOOST_ONE_BIT_COLOR_MAP_HPP

/* one_bit_color_map.hpp
Ak9LENGOHSh8Op5/fNiRt8vXeD0R2rl/nXH3CUW8TKbb7gIvQh2RX9cgYXDd+xtaaHmemiAuQNWnwGWDiWbSAQS8ZDo4MpX6s2xfez1Zpr6vca2tLLQhmMkZee2OWA4KEqvg1oBTezx9uEcQ/uUcsEik3tH9X2U7y7+eA3g+CHL/Q7ZrWpp/dfxnlzsuwFDXUxyqn3j1yzV/RCGNN4ig3DOVUfWPozFbQkEO+m4ZKT9o+W31J/KIL0Z1khmgopWJhpqHn351absv8Tk44LEmvyF/sMHaMisxbm9MSHD0CMI8ALYRDfHzk7SAHC3TY3c6oYo6n9caRftwf4337vjc9PkBe0+AotBt9zrwpTWROKJgXLdXgsGWU3u+upPMQP0zE+/EssSA+k79sVunv+d1+RkTawC1mdl25rlPzUjuSQ+mOnYFEjvqMvL5mzhek85lQakNtaUkayFJ10PUThZ5rh5HMrYtTCvl6cqmhuM1/u1tdaaLQo1Z0dGOHYMGjxuB/JNwrKNlfG1dhd70H+ZftRa3cd+rhtAbrvyROdTNAf05d+L30buZyJOtYC+pDGEp5y3i6/XrHcKc3pnRShxw/XB3wfK2QK6Ysh3f0dnNBaCyWxQEcNkG29bd7SiP3t1sCJDFo6veBNA1BFAJ2QS/9ljPRMDdBgh1f4Mlsg2Sn8gFzd25k1XPLAVZm1kAvRBS8HEUYZh9V996r62q
*/