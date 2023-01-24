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
mNQCSy0r2bCG8e/YDGZqhVzu/c2l4nZmCZ5SmALJOOPHH0QZWV1klRzEUvMvoiiVIFNaCqvOmSIO2uQ/Tmo0c7wZH+4shl1XpTjCyaLkJGYzIj1KDz5Pr67IjxxIUYtMdX/bFraTjLFqUxjtfXk80sw7EVPdsIVR6dJdIow5aIkz3jISYXtKOQ1hqv5oIHA60iKJubqlT10+le0PqX1zImu2vb6vLmDmvqhhOU6iEjPucjDRHzD+QXRFcXxggkdYxKnbvdbDDR2/cUKAXWT+tLY9Y6GNkpyYsMD7dTPWR0jhFq0iHehFgKQgDGDBkoAdEZNfcHTE5H6uLPk1jR9n+su71cHtZBf4K/d86/mBBXuELBOf96zXUhpR1CrkUOnalo60kcd6FVPB74da+0/M01RG4fIO8PFb42ozj+GxSa6bGwCg+WblfuipSu68Y3BpijZADTpNjMuSCEVfeqPilvvGXH8IBlGJSwvm6kWjmY+sTO1ro3XTqqeNR6ckWHm+MJ19rkOEQ+vtxMRzYj62+Ty89dWr1g2SfNSttorelgTaL/7R0gaorR+cLz85n1VImj1LjRso5rRjrrXVvsAm27d1FSOP/ibu+SZddVFGxCM5hF9baMPvSstRZWgwTtJAf0Eye0L3y01MyRdIsN3QbOu3X6+cCBkXr8mybgzoTrU8dtW/fK/hEbfGBp4Em68CRfErx2LO+Dp4ptdW
*/