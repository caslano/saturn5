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