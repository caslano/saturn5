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
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
*/