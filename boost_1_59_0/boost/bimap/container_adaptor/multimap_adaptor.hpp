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
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
*/