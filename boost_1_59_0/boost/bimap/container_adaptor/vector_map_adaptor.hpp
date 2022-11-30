// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/vector_map_adaptor.hpp
/// \brief Container adaptor.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/bimap/container_adaptor/vector_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/identity_converters.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor.

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

    class FunctorsFromDerivedClasses = mpl::vector<>
>
class vector_map_adaptor :

    public vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses
    >
{
    typedef vector_adaptor
    <
        Base,
        Iterator, ConstIterator, ReverseIterator, ConstReverseIterator,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        ReverseIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // MetaData -------------------------------------------------------------

    public:

    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::first_type  key_type;
    typedef BOOST_DEDUCED_TYPENAME Iterator::value_type::second_type data_type;
    typedef data_type mapped_type;

    // Access -----------------------------------------------------------------

    public:

    vector_map_adaptor() {}

    explicit vector_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef vector_map_adaptor vector_map_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_VECTOR_MAP_ADAPTOR_HPP


/* vector_map_adaptor.hpp
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
*/