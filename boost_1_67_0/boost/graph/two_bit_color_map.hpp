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

#include BOOST_GRAPH_MPI_INCLUDE(< boost / graph / distributed / two_bit_color_map.hpp >)

#endif // BOOST_TWO_BIT_COLOR_MAP_HPP

/* two_bit_color_map.hpp
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
*/