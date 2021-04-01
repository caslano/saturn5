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
RNTHSfvrxwy5h7glgbhF9jrRz4LpUXQAAYqBUivfAjQqMLApwFZL0g0eYcri8xsKnNCNGrTNovmkIbf/hslwnK660dmACfVcsTF3HE99gvCXi72xGPb2fxzRgH47skAh1tlUm9qVUa20C2M/fNANjBvXmYD/ERQdiH7PVUkap50bRVVszrdUDj3y6uuGmikJPWyvUTD5fe24RmU8xfrzm51D1njbkQXgzaNER7427oRWI17G/bmEZf1yxmLgLZ18ka1w4+g11RG9ZELLph0tOruZ7m7JyliaVmnnk9kqwIA52Tkh6Kmb867ndbkCcVw9eKmtQlX4OV3QQpnrqWjy/11exlSD8KiFIMt/B6JnSogptmqn32PD/r8/rhunwgQW7etKVVaRWZsISopmRTHnzch5hTJqGQRhHYsfUcxsZAoJCqomQ+shFw/Ml2avxtExM0xtTI+KZd+w3oqqcbC+l2IQbqj/+Ly1oGO/I5kIzqcTApQLX7Oc95FP2dkLttBOmz7Ys32v8EuChQh64Dy7kDUlIw8Lb3AMWE5r5HSQ0vKw/lTV659S54k8DQ==
*/