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
1UZYBDcgN3UlBe8wv95IguQYhheXy/E5wf+EBHO4XryF0XxCuSFAGCZ7gyR4IVVeNVzA0DoudVyePzmi9Lc1gMd4XsDRGINlozR7ezlaptlvl4vlZDYNX0fw6iSCQT94IYzB+/V83Ykdw3tSYb5vJF4dKBa8jl+dxANSoWKYjR76KKyUIJDKYSlJFd5pyfvBhwCA4K7huDzbr3ONxJqc9nnJDP6lrTvsaubQFrcl/ODRMvyG/TNAWdbUgdgpiiMlqh9t/oAtpoZ0AJBFeFT2A3oGjHBYQ/DSR0JPbCaLxYqVVVVeTe/Q5E8wMitciMXtSc5HizTDRQQ96iRspE6JONebhDgmEgty5xupR7qdtQSavCWw1sivwIbcMxA7Zxi+p3RbUGyDb4Lpqt+T45+jtf6U1tVsmUbwLQV6AnyEyPDBY9cG81CEvas91Cl8Y28V0iQf7wBt/MIIET4efvyEassN1f2vTOej9AqZUox/ZzpHi0eSZP43ko+He5JGcCxIZOnzz3CPtYhv5xdmN44TpjQ1d2JFrhX/8oySMEps8YmqOaMnxmv2v+pDNE8DOEDnlWCqqcOybSRyAerkrpc82a5nBmfBx+BPUEsDBAoAAAAIAC1nSlIP/U8mVAMAAJ0IAAAmAAkAY3VybC1t
*/