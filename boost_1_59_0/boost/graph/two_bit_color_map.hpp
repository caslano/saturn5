// Copyright (C) 2005-2006 The Trustees of Indiana University.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Jeremiah Willcock
//           Douglas Gregor
//           Andrew Lumsdaine

// Two bit per color property map

#ifndef BOOST_TWO_BIT_COLOR_MAP_HPP
#define BOOST_TWO_BIT_COLOR_MAP_HPP

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

enum two_bit_color_type
{
    two_bit_white = 0,
    two_bit_gray = 1,
    two_bit_green = 2,
    two_bit_black = 3
};

template <> struct color_traits< two_bit_color_type >
{
    static two_bit_color_type white() { return two_bit_white; }
    static two_bit_color_type gray() { return two_bit_gray; }
    static two_bit_color_type green() { return two_bit_green; }
    static two_bit_color_type black() { return two_bit_black; }
};

template < typename IndexMap = identity_property_map > struct two_bit_color_map
{
    std::size_t n;
    IndexMap index;
    shared_array< unsigned char > data;

    BOOST_STATIC_CONSTANT(
        int, bits_per_char = std::numeric_limits< unsigned char >::digits);
    BOOST_STATIC_CONSTANT(int, elements_per_char = bits_per_char / 2);
    typedef typename property_traits< IndexMap >::key_type key_type;
    typedef two_bit_color_type value_type;
    typedef void reference;
    typedef read_write_property_map_tag category;

    explicit two_bit_color_map(
        std::size_t n, const IndexMap& index = IndexMap())
    : n(n)
    , index(index)
    , data(new unsigned char[(n + elements_per_char - 1) / elements_per_char]())
    {
    }
};

template < typename IndexMap >
inline two_bit_color_type get(const two_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key)
{
    BOOST_STATIC_CONSTANT(int,
        elements_per_char = two_bit_color_map< IndexMap >::elements_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    std::size_t byte_num = i / elements_per_char;
    std::size_t bit_position = ((i % elements_per_char) * 2);
    return two_bit_color_type((pm.data.get()[byte_num] >> bit_position) & 3);
}

template < typename IndexMap >
inline void put(const two_bit_color_map< IndexMap >& pm,
    typename property_traits< IndexMap >::key_type key,
    two_bit_color_type value)
{
    BOOST_STATIC_CONSTANT(int,
        elements_per_char = two_bit_color_map< IndexMap >::elements_per_char);
    typename property_traits< IndexMap >::value_type i = get(pm.index, key);
    BOOST_ASSERT((std::size_t)i < pm.n);
    BOOST_ASSERT(value >= 0 && value < 4);
    std::size_t byte_num = i / elements_per_char;
    std::size_t bit_position = ((i % elements_per_char) * 2);
    pm.data.get()[byte_num]
        = (unsigned char)((pm.data.get()[byte_num] & ~(3 << bit_position))
            | (value << bit_position));
}

template < typename IndexMap >
inline two_bit_color_map< IndexMap > make_two_bit_color_map(
    std::size_t n, const IndexMap& index_map)
{
    return two_bit_color_map< IndexMap >(n, index_map);
}

} // end namespace boost

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/two_bit_color_map.hpp>)

#endif // BOOST_TWO_BIT_COLOR_MAP_HPP

/* two_bit_color_map.hpp
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
*/