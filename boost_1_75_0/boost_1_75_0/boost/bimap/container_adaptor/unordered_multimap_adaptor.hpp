// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multimap_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/bimap/container_adaptor/detail/non_unique_container_helper.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_multimap signature compatible container.

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
class unordered_multimap_adaptor :

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

    explicit unordered_multimap_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multimap_adaptor unordered_multimap_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};



} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTIMAP_ADAPTOR_HPP



/* unordered_multimap_adaptor.hpp
le0bwgNqGOq3LThlNlQPVGrXgiJxHnHeECPTxdzwweqie0mTuDoitCakiyRPClBvVLJtiOdn3H0wzEC8a7ctUK+4VzlxY8NaxVC1NaAsuRgRQquYGN4gvlWd4rWRTekUTU+HB9YtRp9M1eTfwN+mxM9nkNO9cxzn1S8wr5jg1rkap/Dzb4opbFsWxFzdx4Om8MmfsciS10SR458GFbEHF1n+cyhW+tRUnEju7HoKRY2DHl/dsE6xi4lm6syfNZmujUnTKX4Sxtje5KZ0ij7TLWGEw5pgHP5SH4fIm+4/FoDDfVWIkPmvCoTs/iSIDSYeC0LIW1TkHrXIouAiF44GFZlYFYoD3pBDOLwnpHpRw+Mrqxrnet+HEy6vrdJwuZO9q/KjA4y+Dxgb1DCGmgn//aTZYgxJ2KBnGKs0oWHkLrZE4AxwddyS7SSdPGpK/cjl9X1Bq7c/Wrm029dss5vTVgSlhd3Ejyc5JLl6SHI1SMi711LehyVCuBDXhNG7F/pyTtqulI8ma35jKDcZP71Fhpdt3jGJkB1730IbzPNv4+OvtynDL2+rGf5NGQ7yL1e/S89tLK1c9jBFXV0HCRtPfMZzmnjON3j6r3fo+SxkVsbyGOWQOMgTT2qt9qdWH+JlR/NnJmT/iGeXILGYJ1J4jvm8lQSensXTXSDzZJ65DSQe4gmj1mrZm9jqb9S4wrHVH6vYphx4i567+PsK
*/