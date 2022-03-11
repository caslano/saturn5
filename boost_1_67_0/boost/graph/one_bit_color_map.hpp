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
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
*/