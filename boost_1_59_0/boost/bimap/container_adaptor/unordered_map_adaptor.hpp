// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_map_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_map signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_map signature compatible container.

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
class unordered_map_adaptor :

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

    explicit unordered_map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_map_adaptor unordered_map_adaptor_;

    // Interface --------------------------------------------------------------

    public:

    template< class CompatibleKey >
    data_type& operator[](const CompatibleKey & k)
    {
        return this->base()
            [this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k)];
    }

    template< class CompatibleKey >
    data_type& at(const CompatibleKey & k)
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

    template< class CompatibleKey >
    const data_type& at(const CompatibleKey & k) const
    {
        return this->base().
            at(this->template functor<BOOST_DEDUCED_TYPENAME base_::key_to_base>()(k));
    }

};



} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MAP_ADAPTOR_HPP


/* unordered_map_adaptor.hpp
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
*/