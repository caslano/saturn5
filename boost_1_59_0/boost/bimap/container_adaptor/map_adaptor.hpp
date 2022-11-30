// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/map_adaptor.hpp
/// \brief Container adaptor to easily build a std::map signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/ordered_associative_container_adaptor.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/call_traits.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::map signature compatible container.

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
class map_adaptor :

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

    explicit map_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef map_adaptor map_adaptor_;

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


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_MAP_ADAPTOR_HPP


/* map_adaptor.hpp
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
*/