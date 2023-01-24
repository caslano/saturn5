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
eNrl7cp6/qI9b6sVL/Aef3/ubUq/JArM4x+Ovx2A2yep3e2QVMoeuuBXNjxEMI5+S4XxMoJxGOVNEzBqGYyU4Ur+ZSavvDNLK5N4fa0h8SBPGHjOO3jOmjfpmcbTR1lauZFn3guJKx9S/cHV8z1++cQA3+N2+SzcVUVf8HIVOBIF9TIPMjYRXTzBHFB+NHMDXQt+AJVj8gzJWlDSkqI9JXPL6Erl2e4XsHCqU349hh/EJsN0vE2SByW6UmrcA2CuXoPch0T2SmdCmXVl27EpHYyeNpJ3Q9hYtiX51S6XV5u6lHorjAWlORNnsh3t3dGgHCgBUabAa1B1G6ylAuR5UOMK3I8tzBUiz1uYpoad0HAKZrvCGNxwh4CGW7HWLNXFvHlr4VlWnwbCJ1i1hFXfjZ2LFbzGAql2WkpVWAGg9i/7ABws49PW+f32tcAcHcAY9pFt74w+aNsrXmQp31/JrXjjtbfxyotX8bex2ttYxdI3oHCG8nACzyZpbyXl9b58rSEjvG8YCHn+FQwSzxPikIJrn9BtNu35fgQ5GbptqYqAsQxyQw+cDR0uxq8woYAjC8a4H3uNsVbYJtCg+UOcd5xx0yq42Jnn3wTLdsEsI28ZwrQVx3JN/VMWcIyaFpcz9syBLnu8x015G99FPVh4mrwRBVZguJDzTgucg/RkiK26DqsSZ+YvYRf/FcakvpF5/jx4Ds/zTweLioKW
*/