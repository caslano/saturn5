// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/set_adaptor.hpp
/// \brief Container adaptor to easily build a std::set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::set signature compatible container.

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
class set_adaptor :

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

    explicit set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef set_adaptor set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_SET_ADAPTOR_HPP



/* set_adaptor.hpp
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
*/