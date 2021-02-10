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
eIw1AgAA3QQAABsACQBjdXJsLW1hc3Rlci9saWIvdnRscy9ndGxzLmhVVAUAAbZIJGCtVFtP2zAUfu+v+FReAGUN42lsaFpVGFRDBfUiVAnJcuMT4sm1I9uBVuLH7zgUyjSmvuAqtXP8XY7PUbynS6uoxOV5/+x8LAaz8ZW4mF5NxGVnj+Pa0ntb+eHHjQ4OsXOI9hE8eG4ZN979piK+jxbiCc8/Zt3xvMskx5byJA6wm/KE/ZYiNi6naS3ELqO7lFv6yxPzTqQlR5iWmANXr72+ryL2Bwf4fHLyBZ9wfHR8lOFMWk0Gk0h2Qf4+w6lqIz8quVr1An3PQBHS9DZS00oHBFfGR+kJvDa6IBtIQQYoCoXXC37RFrEilNoQBtc38+HoIsNjpYsqiaxdg1C5xihU8oHgqSD98KxRSx/hSqazuNIhsmATtbM99iZE8suQNJK9NMFBPkht5IKNZEQVYx2+5nnReMPZ58oVIS9ejt+r4vL1JHNOYinXcHVEdGgCZUjIDEundJlmLggH62ZhdKiybTZsZVXuPAIZk7SYpyk8p02YbMqTJRhqzljHNAVnQ7J6rNzyLyDXMamUjbdsxHVgkHJc5gwNf0a+Bbcnf7HY1LQt8H9bs81XwVlOBt3+BMNJFwsZdMhwO5xe
*/