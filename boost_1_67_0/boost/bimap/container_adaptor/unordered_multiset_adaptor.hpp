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
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
*/