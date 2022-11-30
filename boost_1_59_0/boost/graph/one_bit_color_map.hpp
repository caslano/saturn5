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

#include BOOST_GRAPH_MPI_INCLUDE(<boost/graph/distributed/one_bit_color_map.hpp>)

#endif // BOOST_ONE_BIT_COLOR_MAP_HPP

/* one_bit_color_map.hpp
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
*/