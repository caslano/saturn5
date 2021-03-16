// (C) Copyright Andrew Sutton 2007
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NULL_PROPERTY_HPP
#define BOOST_GRAPH_NULL_PROPERTY_HPP

#include <boost/property_map/property_map.hpp>

// TODO: This should really be part of the property maps library rather than
// the Boost.Graph library.

namespace boost
{
// A null property is somewhat like the inverse of the constant
// property map except that instead of returning a single value,
// this eats any writes and cannot be read from.

template < typename Key, typename Value > struct null_property_map
{
    typedef Key key_type;
    typedef Value value_type;
    typedef void reference;
    typedef boost::writable_property_map_tag category;
};

// The null_property_map<K,V> only has a put() function.
template < typename K, typename V >
void put(
    null_property_map< K, V >& /*pm*/, const K& /*key*/, const V& /*value*/)
{
}

// A helper function for intantiating null property maps.
template < typename Key, typename Value >
inline null_property_map< Key, Value > make_null_property()
{
    return null_property_map< Key, Value >();
}
}

#endif

/* null_property_map.hpp
ZCY1cc6LMCq7jOA/OfvZJz58+7K3Ng0dc/hdF68G2G8I3nTPjsbfffj1+r/d9oVrim4//kuMzRpF/Lxz5H0nnnrpu3O+VHj7qvB1P2Csg+A/v+KlJ6pj8Rs3v3lW+51TvwZlvIbgi/5ZdmJ4zzmfvaPujEmvjxo6n7FnCP5N7+SllWs33LRo4ZLF26+4+RjG3iP47avOan195KW3nLdj3AtP3XrFbsbeBLk9GdfQdixck0j2r01Ge0vonoKSssE=
*/