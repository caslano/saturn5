// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_CONSTANT_PROPERTY_HPP
#define BOOST_GRAPH_CONSTANT_PROPERTY_HPP

#include <boost/property_map/property_map.hpp>

// TODO: This should really be part of the property maps library rather than
// the Boost.Graph library.

namespace boost
{

/**
 * A constant property is one, that regardless of the edge or vertex given,
 * will always return a constant value.
 */
template < typename Key, typename Value >
struct constant_property_map : public boost::put_get_helper< const Value&,
                                   constant_property_map< Key, Value > >
{
    typedef Key key_type;
    typedef Value value_type;
    typedef const Value& reference;
    typedef boost::readable_property_map_tag category;

    constant_property_map() : m_value() {}

    constant_property_map(const value_type& value) : m_value(value) {}

    constant_property_map(const constant_property_map& copy)
    : m_value(copy.m_value)
    {
    }

    inline reference operator[](const key_type&) const { return m_value; }

    value_type m_value;
};

template < typename Key, typename Value >
inline constant_property_map< Key, Value > make_constant_property(
    const Value& value)
{
    return constant_property_map< Key, Value >(value);
}

/**
 * Same as above, but pretends to be writable as well.
 */
template < typename Key, typename Value > struct constant_writable_property_map
{
    typedef Key key_type;
    typedef Value value_type;
    typedef Value& reference;
    typedef boost::read_write_property_map_tag category;

    constant_writable_property_map() : m_value() {}

    constant_writable_property_map(const value_type& value) : m_value(value) {}

    constant_writable_property_map(const constant_writable_property_map& copy)
    : m_value(copy.m_value)
    {
    }

    friend Value get(const constant_writable_property_map& me, Key)
    {
        return me.m_value;
    }
    friend void put(const constant_writable_property_map&, Key, Value) {}

    value_type m_value;
};

template < typename Key, typename Value >
inline constant_writable_property_map< Key, Value >
make_constant_writable_property(const Value& value)
{
    return constant_writable_property_map< Key, Value >(value);
}

} /* namespace boost */

#endif

/* constant_property_map.hpp
Qlt+8UKe5nREhBbc+Iyz8A2Lvd7LmIltxA2Z6CPXDhbd39eqGhatlVZOV0EXbGkaG09fVFpHOt8ew79s9jweee7e1HEtOy7/io7PqfwQk9doL3OmWWnA0Y/nkeOp1R7CotWBXAOUe5qNzpRpWR9KLqPukC7PATXvvUTv3b+KzQn7p06ieNpKL1HExGEmeNIC1ajsS94cVPefe6IrFMHaEg18LQKUxBA1sFCXJwKwc+LcBAthOtDPQ8YKn+F38Mei0K5QG5dCXV+JYAhevRbYgTiMP1FOKsWQHxfBxQRtTQzI9XgND5dMkVsJTtkXQemzQc5Qnx57Phkj7DGkiQK4kL9pUXc7f2b+OXmHTQxZf15jQtEw7o3d3Dkf0gWxYpb0pfRrfEe6TVmQ7YofjDjsicQhq9XykPOVFP3iIeKGB20YuhPmT2sypLcowT6jPVRDfyMnCoX2N6Y3tq1SqRP/r9aY9T8yXfhvWdbMzdb8H0dukC3wn42xYoRG+Nwsj5LJSPw7g7dsWjzHSjCTfHomZrqPBjyz5e3MrbCr2472T3G6u5wkJR7p7OFrA0pB+K5Bv3l//qmRFIs9WHDKVOnncxxSM5cLkOtZMVdJCo3NV9Qa+hawMb5+FZOvzpRVyPsLcd58nX2R4dSVltW6lPNssXUSgFgOcZp61RyrfLggzwwZUyGVKixnTHyNj9bMwsJSN0J6t8o66o91ScmN
*/