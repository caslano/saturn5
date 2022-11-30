// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP

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

/// \brief Container adaptor to easily build a std::multiset signature compatible container.

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
class multiset_adaptor :

    public ::boost::bimaps::container_adaptor::
                ordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
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
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef multiset_adaptor multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MULTISET_ADAPTOR_HPP


/* multiset_adaptor.hpp
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
*/