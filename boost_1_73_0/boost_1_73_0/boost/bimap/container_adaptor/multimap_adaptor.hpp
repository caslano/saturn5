// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::multimap signature compatible container.

template
<
    class Base,

    class Iterator,
    class ConstIterator,
    class ReverseIterator,
    class ConstReverseIterator,

    class IteratorToBaseConverter          = ::boost::mpl::na,
    class IteratorFromBaseConverter        = ::boost::mpl::na,
    class ReverseIteratorFromBaseConverter = ::boost::mpl::na,
    class ValueToBaseConverter             = ::boost::mpl::na,
    class ValueFromBaseConverter           = ::boost::mpl::na,
    class KeyToBaseConverter               = ::boost::mpl::na,

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class multimap_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
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

    explicit multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multimap_adaptor multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTIMAP_ADAPTOR_HPP



/* multimap_adaptor.hpp
/4k/4O1V5C+DhncrBlO8FduOWjEaQSmtDiqxDmp4dEqH7Bbc2YbXbo92996M4mD78mGq2rlQAXpf0M3Phnn1wgJd+e6aga1T3Q0a5bw2Ok3gyjkdXo+HQ6zw491DzMU9p4ORPa+bYu8jaCb82zqyp9YdyTHsu1IpNxiqO5lSYr5VNIihZ5DxazY4dsw04yv8cFqz3CWcxQfbVaWRdV/jRZ/3Mrv2aTW7Zm7zqmrc1lXCSAlqs8AOkHJ8bCF/078af7QLFZrpsqKcbRvlVIneFvxN3zHULCmH1t7b044MF8H6HH41VKO74dDfTMOKf7URy6YysxeF58Z2oVFSL5lIPV072TwK7IrcxC9rUxh038UsRBSsXP0PDZ7vph6xwQk2GL9yc7EVgj9rs+eJnDJzjdY1HH4Yjn/pDcMeuvDiPelc/8sirYXEpxHZbANWzfvSr7L3aCX2kr5pm67C6zcp19hrVyk7XMwdZ2eqXNFNx0yWy7sRrnrjUVDvUt8liYbTzUZQbZr4lasFoXx0BGcIs8WrdiumcP1GNL8HOo5+FRccbBYQqqy7UXjRv+zdDSfbhrqNr2Kp393Omf8DUEsDBAoAAAAIAC1nSlJYDZoAlAQAAFoKAAAnAAkAY3VybC1tYXN0ZXIvZG9jcy9l
*/