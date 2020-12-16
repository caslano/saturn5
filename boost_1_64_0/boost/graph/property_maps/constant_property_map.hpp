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
VyHPzuO3jCFP9Ypqfgr8Cd9A8s0XWd3wNxPHAfXNRG17zFvKqlK10/wDb5Dff4TjJ34sx1R3IW3HaFezCA+YV8Ef7YH4i9gvK6yqwBSto07VUg4iL8RuiNoxH/TdzjG00++mDNgXdM9NHRY6LDT0bdLVQo8WeqnQ04Re6elz3m1h8K8lTCpMGsxk8Gwlfy1Gi/mRiWw8Nza/cEl5ja8uBlkiflpGx9Csh+ipxD1g2O52PbV2btrvsQmPlu2mU79XP8G/r7XzGGmBPdPi2Ttqx893rkWnfTA7GvhiJKAN8GLglIhcjZ0n+WA5Vb6Iv+4qHz8kPcr0ySfh76Lt+3ekJ5gx8k1l3lHyPAW5XS15aYXT0SFHqNLpe9Jv0/18M0KXKX+OV5/ScViXJhH3sTytMNyI07efn6f9xSizC6lTfdDC4AUoW6Pjmw+dOlWyff5AdY5n6X+OEQ/XGGFSD7PC3dJSdLW42vc49hX7PbC/B/aBZYnBQIeUqYkJQVzH5J4jvDfNHrvVnUHf7TeuoryPUb/yYtQvznmrvZQD2uXCJu5xVnUT97js0SbucdmrHv43lN/drne1NfiHd6wgxWGAdeDJbequw5XLsDP51PVX/HTSMW0x6a/MNJTTZhi/9pwJjPrtreexFpG+1jwJSbPGTNR9vCWMO9kRFh4MXmq9W4z6rOl4wSzFKaFCczrr6TR8U5IxPww2fS/1KPnWcS4oJAVZSLs1RjbtTNp9QbsisxI68ScwjrqpY8XPyZNgndcRP5chp2c79I/5xYxfzgD+kDwPcr57O2RJXhtr3qHu7OCcWuw/K4Cswdx2a8ybtJFxTt3ZGOg0wWxDW8w2JAX6YtooEEw8K5AJq1Yp4zkBEbFD6Z7JPIR8B9oGdX+hrfxOY3udjnR0a2O117rdfu1VwkIN4/yYNyy2tWwJb1ybaHvDmC2jbnQwvrnhHk9ZeRN28NXW2XyWnn1Dw/VsXY9CGbn3bPuMl8fVa6fe9qt1kG1tF8PFnJ20vdeFXis04nW1zUCauy2PFvoaoacJfa3Q29Lc/h/1+DfS3bKgZbqbv73Qsz3jhF7tDf6dgOkM80uY68ATTldZgIHgopJFopsdzJD3Uu11SeHtrTr7XaSfc7TXRYXLkbl227f89FCd83bS3eStYpzvIn2PMRqpLTTSvXND2p63kO8l0nmalm6+54Q7Mv3pQmN2lXQn8l8fXVfAZnz7DW+7zUgeWOtZjGdXzLMJzYAJDBf9oPTT75N/FuroWbCLyqyXaNcKMirR892FsEuCHXjlHGQjhpeLXE7R92gPkzfR6IL2kIQ47kc6t8E8APMgzEMwD8Pc5JiXGHIGawsF+I3yBh0pb9GDdW1By5S84Xidi1K7HCDyFHbMU1e9W87Fcb5/Z2QRYcAb5nfWziutDC8J52M8VR0tg7uay9jSrnfC29OeqyNdbT5umLJW4z7LMlH9DNP59MTM6NvfmZBZyaJzYU6K7mPAfy35V5t73Oukqp9soXu5+bCRYp8VhS6Fx3aLLR0sE3gD45mMPEgQO1fcOr71ri2tJM/NWKlYzvmvvmivb2CAeCd4AwMS4wPNUzrj/94Q/ylQ+/3mIHznL3Yz/Rfh23JFZlvpClDWWvJ+ewPkK8+zNdN5jP6GY54S5adrVKobJdpnXygjM3Qug3RmplsGvq60W595u4soZCa+H3ge8DvgSWsWrUuV4RX5ePoYW26whF5txHwn+izy9jBbm6bUL8t/O+ZdFfmrShbr+oy4I9Y5xjsOWcfocN6pRM4wQ8aSr5e5Hmvdbc04ab+W/9Z658Au0hmUPQUie+6nTELqq+3+eiH5EnWPzWLST8eUeenAKWw7jZk=
*/