// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP

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

/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

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
class unordered_multiset_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
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
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multiset_adaptor unordered_multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP


/* unordered_multiset_adaptor.hpp
vuiJR8ta0kIXSu1Llt665cRJJSSrgIMYL3ybO9ktl8ZelKI2ouz+r0zG63Bo0r9U5x5avimMn2Z4vREqiXaZ0CbtHRb/oM89MuwY4Y8TiCDsRk/RzxUZ4zJBdGuwOpntSxxKtB1RQ+uOPRtWSjcuZAqZgxI7V92DXqr/c9HzpaxoOebqyuzoqcQVprzfgoXA2j8fC+PtI0NzSxpTPyL3oMHQWRGEZYvMn5xRCQTErgHGf6dX2SxXGjeTTAv8d42pTrbc/sD2YVY2ad4bpXjtkjXah13n7dH5eRvRXjlWhsepltD17Dp4Zyie6nWRFeIM7TtfARxWwvW3mVJVCj1hrMYCrPJGQdKyTHSBOnIm8xBBhrsbfSuGrnl9yYdBEHY0/qAe5tAzxQ1PXqw+zYWwgoOZc63IxhNnZklo1EtymqVByHWA/cvlrbF+wLFtOsrs7UsfllmrjMDwcS7rTW+CYFWrwBr5meH3zM0SaLf60Y/8AGpMJy1jPrlt14IWM0kYOZnrk6xiGxE9RXfsG4gzyAawSuaEO9l72fdCMPPDIO+ag5SHXLTaXromLg==
*/