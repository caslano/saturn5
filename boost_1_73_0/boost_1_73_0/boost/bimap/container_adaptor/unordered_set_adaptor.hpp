// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file container_adaptor/unordered_set_adaptor.hpp
/// \brief Container adaptor to easily build a std::unordered_set signature compatible container.

#ifndef BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP
#define BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/container_adaptor/unordered_associative_container_adaptor.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/vector.hpp>

namespace boost {
namespace bimaps {
namespace container_adaptor {

/// \brief Container adaptor to easily build a std::unordered_set signature compatible container.

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
class unordered_set_adaptor :

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

    explicit unordered_set_adaptor(Base & c) :
        base_(c) {}

    protected:

    typedef unordered_set_adaptor unordered_set_adaptor_;

};


} // namespace container_adaptor
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_CONTAINER_ADAPTOR_UNORDERED_SET_ADAPTOR_HPP


/* unordered_set_adaptor.hpp
DOBDZdCSuAFRVlIgbzW/35VEyRkMrsaL0aWXN/iitkKtqT8Ul2hbR66Xy1lwklaGypHvStFppe4IBg6SPUES/ShUJmuOMLCOC90vLo9CNfns+POYb5mmbygcCWIvmVDdjRa8F/0ZAYw+zidw5jMu2rdMc9+89iKigJ9I11KvmEyFEq7rM9L3k+m74SQdTia9pyx42yQjs7smtecZRd714R54MThKseioScNkHHSns2X6aTx/N12MY3g5CeiTgOvx8Go8b/MDgBxf0+FuDqqxjhzO6tL7Sv79C0YaYujsjxw+MOoN7Ge6TDpHEjM0uTZNwxv8o0brYm8abIWUTwUYdNT9EBxt1X3OsVNVQ9SYdLGnHxWY/Q40AWiMNnaPJjc9wQ9vQ7njdPqhFzXfyrwytLt5lzqAILSCbyV6kNNHBfkb+Mneq04cPf/aHvniTJD1Wr2vfGVKh9Pz5Gpu2nNvWUk3NBuabdp8H90LHRr7P+9F+AT+7zeEyS3bWcgkMlVX35raThzW8sVDWxPOL6Iv0V9QSwMECgAAAAgALWdKUuF8UYnYAwAAuggAACgACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3BvcDMtYXV0aHppZC5jVVQFAAG2SCRgrVVhb9pIEP3Or5jj
*/