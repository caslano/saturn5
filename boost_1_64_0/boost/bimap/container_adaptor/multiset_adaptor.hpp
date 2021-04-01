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
PoGY8w8AMAYfZw4n9XgDT+m+9wr8NOm2eODT5sAyrLTOfbcLxo8giAgcqjE0oK5af8e+fKv2qb7yxQR16UvM2A3Z448AF4pKzD+4ZQmg8eZq+t+EEmg24ZTNmyxqCYCRH9jIG9B8Sp+Trj4SEGxQe7RuSAv7gB3q8L8hAa8E2R9J+2vcTRw2l5seABvxQoELOzuD3dKX9uxh5ULgE6PFY/B4LYiLlTzhSjSYsRDRTYfr+ZTriHa1aWjytFwaj3ZHigdTEVkyQJ/03t4ad7NWUHc5va/zGY0fl0OkFFrEq1/v8rg6GlkQZeLKyFjUI+3qLsmejo7pyvLq7kEV2leO1hFzG93rWFxH2DxAVX4OeW+UutjCQK5legMImf8PN693UIzAxkiI2ZHtGV06oVA6YsnQaNJsjpKX2STZtMgb7SxndTyS7GkkuFEniUkr4OfnA8E4PO3jqzmTDXJmIc0Da5WvEttw7Bn9v+mLwZE6EmIoKyRvFrGGrmjeXUVbneoER3d5hPGXV4K1oeEGWfgiu2Yj7lXrCCLtPH8KPFLQjAJdq0/TCbpAzrwgDw==
*/