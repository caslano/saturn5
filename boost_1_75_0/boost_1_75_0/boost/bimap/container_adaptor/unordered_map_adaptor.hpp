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
rCbh75WoBoS/oqhg4e++t3XCnztKL/zx7WQ5CH2vdQOSUlX8VDhIxX9zFE27hjqKOsAqDwizqA0EgB4m0XZLu2ao/5atpN4daqWp/6C9ZMHft7dS+ThX/+W9JZzhrW4VQvf3rF73x9kI9HbdoyDxaSemscHnKZ7efttfbBppisNwXXkuONzaqvHNr8vX61tgc0Vv06j6+l62VFXmScobXwRtSg3KhcC7zVNqzFr2ycHZd58Myp5WYw5USr2I7K4cEE/egtDWeZdaw3yqQRtRVon/N9j+zQvcCCubZ4riwEI+DNw7gGc7F7lWw3GMK9U2EMvUDQQnosvY7K7u6reth3YEYHjHmX2oGoUKQby/TCrBUzPr61DY+gNNA+96/X4jqptoYFBu3aHk0BHrO2a2ub6kiSNWGBydulBSWi0P2u0++lMQmg/9ihvkF5eIS+oHPg8qcmNwkQ9+DRqZ57E7J3HnBaHmRckLJ1hJDJkOSLNN/lW/sRY4SZ5BskaGUZvFpDfcpE0XhtE3dKrD4nVNqA4ttNeOhxYxcKA1X7aoI5LPuSJ7+4FBz3ssfD5ixG+d9jDToqoNKdL2kd8xiOH10DTWxTvTaobKafT6wxIxoMrq+4whcHDddA0HOgpmyxuqEvv9wjYmDr0qcZ8B5YESVCVuEfyyNKAz4apfLbC1hwY5duabAznfzfXOXxOUuVNRlbgLNRybVCYqz4Mm
*/