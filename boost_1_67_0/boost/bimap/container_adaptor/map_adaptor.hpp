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