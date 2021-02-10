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
iJjzQRmVo5gNXCgZcfbaaGry2DSxjgFJ1mHV1+iKHVFtHiWVGtFxzctefwyK0dXl2D62bXn9bEiYEbeq+u/WSdMSThUJA7TQ27XCwzfrox01np+UoCtpkWeLpv1g7qNAM8hZDEQSao1Rhc0OVWBVyBtnNOZGd3JuIPejY4M8dMgkU2gOnXjXrleLC7vv9xdxGKJQJ9Ro8aQL4aJY5mUiCTAc9gd2cFyZprW4f95UX8SCX6L6rdTu7p+ScIN0hJY4/0LFMBfvdWprrfZs7kNxJGq3oiS46nQZPjGszPGsRKw4DYirQrSEfVTps6/ULloOVgLRGeFLYLQPCcU8Y0PcvAqa7Cq7Gtnrk0Obu5+EO6eDcnLxWAnrL94IAyW/yhZYpo+3TjCtXLV4RcpJpmxppSNDvPFFQVx6ZQjkZtUe2tgkn5jGOWMzXHFGadh93e6fjl6333SNCIWX5yCAKHMkSLQWexjh/yjZKE+nuI2TD7tuQhfWoyIYxbd74iz4xJIRim4bLlNQWzEL3617ty1PVAKAmzj0RQiqYDwlaDpIoJy7udoLQNNCGijpT11WyYILgPxHacH4H0faK6D51SSuqekZTsQ6+kuPc6TGADSEQB4qQ20B6bcMPbKTF1wN5dEyTCZVdw5TgnbuTOOx
*/