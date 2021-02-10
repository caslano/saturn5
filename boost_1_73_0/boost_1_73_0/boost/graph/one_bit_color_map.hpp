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
aQMPWwSJuCkbKkYJhrZ40ymMD7jXXZBcz1botB+EN+JO1C1mVMLNh5zsKI0gwo0CnJTnB+BMuK3YpTGBXTyh2eHmspAamChmKSSwXRazoNEZM2pmgF8UbSeOYcpdPYrujaajiJJtStwgt/hyYbHX8Y1had4zSM8XGDc72yi1gBiNwSujKU5brHMMumTFvi3wnOaTtwWl5G2yIWTPIcL/IfuC8PixdwmjtAqzoxg9J5D+wKHwR5BIhz//PTYN41xxm1TvEwGv6q1CmG0rWb1Z5FpIFBf7JMN0gVjKoeKV+WExKPeQDSyfwVikax3rWItgjLq5aDe7iPkxDEf6qNYT+fOmo8piv2+D0meyJGEOrSzzmfI7qBBP/4UMTQ80RNOdIVWW6Co9sjmurQHf38Aw/S9sVOA7YD7VqvBws8KD7QoVtgJr/O7oyMnUekF40GUzIz7K0qULCo9kbmAYWeiPzOGnPBnWtjM0mK1IyJdNNYfkNsOz2OmPondaFc/PZHy2WhzOQVJzKDhPsohE5FXmhJbiIJBSxmXJKnk3o1Mg4pqcHtmLxf7iJJrX3hKv0hEpFulaHTo4kmkBRPy1SrQpW1K7VUsV/ERBCd1UsvPaJcyAJ4Cu2RoPgaWMVZCkPbKMpmSm+dwvx8gsX6tG
*/