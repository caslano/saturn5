// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_multiset_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP

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

/// \brief Container adaptor to easily build a std::unordered_multiset signature compatible container.

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
class unordered_multiset_adaptor :

    public ::boost::bimaps::container_adaptor::
                unordered_associative_container_adaptor
    <
        Base,
        Iterator, ConstIterator, LocalIterator, ConstLocalIterator,
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
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
        BOOST_DEDUCED_TYPENAME Iterator::value_type,
        IteratorToBaseConverter, IteratorFromBaseConverter,
        LocalIteratorFromBaseConverter,
        ValueToBaseConverter, ValueFromBaseConverter,
        KeyToBaseConverter,
        FunctorsFromDerivedClasses

    > base_;

    // Access -----------------------------------------------------------------

    public:

    explicit unordered_multiset_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_multiset_adaptor unordered_multiset_adaptor_;

    public:

    BOOST_BIMAP_NON_UNIQUE_CONTAINER_ADAPTOR_INSERT_FUNCTIONS
};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_MULTISET_ADAPTOR_HPP


/* unordered_multiset_adaptor.hpp
YXN0ZXIvZG9jcy9leGFtcGxlcy9wZXJzaXN0ZW50LmNVVAUAAbZIJGDlVGFv2zYQ/a5fcfMwwA5UK+2ntXGDuY7XBDViw3ZbBAgg0OLJ4kaRGknZMZb+9x0pOXbaDR6wfpsMi9Lx3nvHx6OSs+93RXAGJ680/FO6aAyImdG/Yeb+PjtNH6H5EeqexlMiCRwgj2kPTkMeoRsgaasy8M9pekro3tfmb4lH3qf+kSIE88iRrnZGrAsH3VEPXr5+/TO8gFfnr85juGJKoISFQ7VCs45hwEPkl4I9PPQtXsaADpjst1TLQliwOndbZhDoWYoMlUUOzAJHmxmxohehwBUIuZAIo+ns7ub2fQzbQmSFJ9npGmyha8mhYBsEgxmKTcNRMeNA5wQnci6sI8LaCa36pI3g0JTWc3h5Jq0GtmFCshUJMQeFc5V9kyRZbSRVn3Cd2STbL79fuPJpJXdURMl2oCsHTkNtMQafGUOpucj9SIZQsKpXUtgiPlRDUoon2oBFKT0X4QTapmyERWtP7NOgooqF84PVynqpbaHLZ4nko2fJa6NIiHygJK7J5hhqxdGE5LDyvUTraTD4H7fmUC8HragY6AwXcLPowIpZYWP4fLO8nn5cwufhfD68Xd7B9FcY3t55sg83t1e09YLE
*/