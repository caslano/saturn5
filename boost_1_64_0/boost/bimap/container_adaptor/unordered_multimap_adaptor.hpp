// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class LocalIterator,
    class ConstLocalIterator,

    class IteratorToBaseConverter        = ::boost::mpl::na,
    class IteratorFromBaseConverter      = ::boost::mpl::na,
    class LocalIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter           = ::boost::mpl::na,
    class ValueFromBaseConverter         = ::boost::mpl::na,
    class KeyToBaseConverter             = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class unordered_multimap_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multimap_adaptor unordered_multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};



} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP



/* unordered_multimap_adaptor.hpp
mq2FNvhGDqH7oqyTfUUjOcz7dupf+EM8RorZvdwupZTHli4OaqyFv7+QpBGnbGkp5rV69Ia0dtmhkCis4APgXvwc2+bY2KXtUEhjLr1hGfv0BlcnfHZcUvNQdGi/je3J/r9o8Q5TbMqQpTy2qyBi2EnwbG51hCUzJkucMtE/N2ZocMetUnoD3+NsAy+2/P9vlnJVVvsWZjE4GAeiR5eeEBmTuD3n1LNK8IjWHjNgy7A1EZonuJJz6q8kCJbpnwEZ/iUYFDygRVddkkpzA1YD9JnEdLnviHm6JVR8NjiIOUWKXcVn8obkmj8HeRLt5QMug5lx6/rp3SVPlW55lFVw6l8iOQnXgwuJYT5PBgx4AJasIRVefjk9NnLHhT9DTncMikS7iKl1NpCJbUs2VUYKSlR+uV4MItAHr+awd+TjPPJOBWqSmmG64pxWncsxnpjwRiWu73XjbihMTAmOI5qx5JN1rEX2Kxcd40us/HbE2DFVzIqxXnmQUj4zEVxcEqBivkDex9uSlT7JY/YXbNnbMPU76Q404V7cRQYy+itwjVSztbyhuxLE17zwgA==
*/