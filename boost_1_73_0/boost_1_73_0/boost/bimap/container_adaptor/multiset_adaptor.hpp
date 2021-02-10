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
eGFtcGxlcy9tdWx0aXRocmVhZC5jVVQFAAG2SCRgrVVtb9s2EP6uX3Fz0c12FSsr9mFtXjAv2bpgbhLEDopgCQRaOllsaVIgqTjZkv++O4qek2BpvlRBTOp4r89zR2XDb/ckMIQXnzz85/TQGixOrfmMhf9/7Ty/g+6PrC5pfSlIBhuTu3wAL5vcQT+Y5DHKLu/z/KVAl5wb/2RseZnzliRkxpYHprm1clF76B8M4Md3736GLXi7/XY7hUOhJSqYetRztIsUdssg+aUWNzcjh/spoAehRtHVrJYOnKn8SlgE2itZoHZYgnBQoiusnNOL1OBrhEoqhIOT04uj4w8prGpZ1Ozk1rTgatOqEmpxjWCxQHnd+WiE9WAqMifnpXSeHLZeGj2i2Age7dKxDw4vlDMgroVUYk6BhIfa+8a9z7KitYqyz0pTuKxYlz+q/fK/Si4oiaW4BdN48AZahymwZgpLU8qKVwKEhE07V9LV6SYbCqXLzFhwqBT7IjuJrksbYRrhSVkNGspYel6c0Y5DrWqzfKRIOLKXqrWaAhEOpFQagjmFVpdog3KofB0iYhoAfpaaTb4lGE3JQG88haNpD+bCSZfCp6PZHyfnM/g0PjsbH88u4OR3GB9fsLM/j44PiXpJwSzgTWPRUXAL
*/